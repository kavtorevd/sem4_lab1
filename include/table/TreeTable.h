#pragma once
#include <table/SimpleTable.h>
#include <iostream>
#include <stack>

using namespace std;

template <typename TKey, typename TValue>
struct TreeNode {
    TKey key;
    TValue* value;
    TreeNode* left, * right;
    int height;

    TreeNode(TKey key, TValue* value, TreeNode* l, TreeNode* r)
        : key(key), value(value), left(l), right(r), height(1) {}

    TreeNode* GetLeft() const { return left; }
    TreeNode* GetRight() const { return right; }
};

template <typename TKey, typename TValue>
class TreeTable : public SimpleTable<TKey, TValue> {
public:
    typename TreeNode<TKey, TValue>* root;
    stack<typename TreeNode<TKey, TValue>*> st;

    TreeTable() : SimpleTable<TKey, TValue>(), root(nullptr) {}

    ~TreeTable() {}

    bool IsFull() const override { return false; }

    TValue* Find(TKey k) override {
        TreeNode<TKey, TValue>* node = root;
        while (node != nullptr) {
            if (node->key == k)
                return node->value;
            else if (k < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    void Insert(TKey key, TValue d) override {
        if (Find(key) != nullptr)
            return;

        TValue* value_copy = new TValue(d);
        root = InsertRecursive(root, key, value_copy);
        this->count++;
    }

    void Delete(TKey k) override {
        if (root == nullptr)
            return;

        root = DeleteRecursive(root, k);
        this->count--;
    }

    int Reset() override {
        st = stack<TreeNode<TKey, TValue>*>();
        if (root != nullptr)
            st.push(root);
        return 0;
    }

    int IsTabEnded() const override { return st.empty(); }

    int GoNext() override {
        if (st.empty())
            return 1;

        TreeNode<TKey, TValue>* current = st.top();
        st.pop();

        if (current->right != nullptr)
            st.push(current->right);
        if (current->left != nullptr)
            st.push(current->left);

        return 0;
    }

    TKey GetKey() const override {
        if (st.empty() || st.top() == nullptr)
            return TKey();
        return st.top()->key;
    }

    TValue GetValuePtr() const override {
        if (st.empty() || st.top() == nullptr)
            return TValue();
        return *(st.top()->value);
    }

    TreeNode<TKey, TValue>* InsertRecursive(TreeNode<TKey, TValue>* node, TKey key, TValue* d) {
        if (node == nullptr)
            return new TreeNode<TKey, TValue>(key, d, nullptr, nullptr);

        if (key < node->key)
            node->left = InsertRecursive(node->left, key, d);
        else if (key > node->key)
            node->right = InsertRecursive(node->right, key, d);
        else {
            delete node->value;
            node->value = d;
            return node;
        }

        node->height = 1 + max(Height(node->left), Height(node->right));

        int balance = BalanceFactor(node);

        if (balance > 1 && key < node->left->key)
            return RotateRight(node);
        if (balance < -1 && key > node->right->key)
            return RotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = RotateLeft(node->left);
            return RotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = RotateRight(node->right);
            return RotateLeft(node);
        }

        return node;
    }

    TreeNode<TKey, TValue>* DeleteRecursive(TreeNode<TKey, TValue>* node, TKey k) {
        if (node == nullptr) return nullptr;

        if (k < node->key) {
            node->left = DeleteRecursive(node->left, k);
        }
        else if (k > node->key) {
            node->right = DeleteRecursive(node->right, k);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                TreeNode<TKey, TValue>* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else {
                TreeNode<TKey, TValue>* temp = FindMin(node->right);
                node->key = temp->key;
                node->right = DeleteRecursive(node->right, temp->key);
            }
        }

        // Обновление высоты узла
        node->height = 1 + max(Height(node->left), Height(node->right));

        // Балансировка дерева
        int balance = BalanceFactor(node);

        if (balance > 1 && BalanceFactor(node->right) >= 0) {
            return RotateLeft(node);
        }

        if (balance < -1 && BalanceFactor(node->left) <= 0) {
            return RotateRight(node);
        }

        if (balance > 1 && BalanceFactor(node->right) < 0) {
            node->right = RotateRight(node->right);
            return RotateLeft(node);
        }

        if (balance < -1 && BalanceFactor(node->left) > 0) {
            node->left = RotateLeft(node->left);
            return RotateRight(node);
        }

        return node;
    }

    TreeNode<TKey, TValue>* FindMin(TreeNode<TKey, TValue>* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    TreeNode<TKey, TValue>* RotateLeft(TreeNode<TKey, TValue>* node) {
        TreeNode<TKey, TValue>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    TreeNode<TKey, TValue>* RotateRight(TreeNode<TKey, TValue>* node) {
        TreeNode<TKey, TValue>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    int Height(TreeNode<TKey, TValue>* node) {
        if (node == nullptr)
            return 0;
        return max(Height(node->left), Height(node->right));
    }

    int BalanceFactor(TreeNode<TKey, TValue>* node) {
        if (node == nullptr)
            return 0;
        return Height(node->right) - Height(node->left);
    }
};
