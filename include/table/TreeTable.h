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
    typename ::TreeNode<TKey, TValue>* root;
    typename ::TreeNode<TKey, TValue>** ref;
    typename ::TreeNode<TKey, TValue>* cur;
    int curpos;
    stack<typename ::TreeNode<TKey, TValue>*> st;

public:
    TreeTable()
        : SimpleTable<TKey, TValue>(),
        root(nullptr),
        curpos(0),
        cur(nullptr),
        ref(nullptr) {}
    ~TreeTable() {
    }

    bool IsFull() const override { return false; }

    TValue* Find(TKey k) override {
        typename ::TreeNode<TKey, TValue>* node = root;
        ref = &root;
        while (node != nullptr) {
            if (node->key == k) break;
            if (node->key < k)
                ref = &node->right;
            else
                ref = &node->left;
            node = *ref;
        }
        if (node == nullptr) return nullptr;
        TValue* tmp = node->value;
        return tmp;
    }

    void Insert(TKey key, TValue d) override {
        if (Find(key) != nullptr) {
            return;
        }
        root = InsertRecursive(root, key, d);
        this->count++;
    }

    void Delete(TKey k) override {
        if (root == nullptr) return;
        root = DeleteRecursive(root, k);
        this->count--;
    }

    int Reset() override {
        while (!st.empty()) {
            st.pop();
        }
        curpos = 0;
        cur = root;
        return IsTabEnded();
    }


    int IsTabEnded() const override { return curpos >= count; }

    int GoNext() override {
        if (cur == nullptr && !st.empty()) {
            cur = st.top();
            st.pop();
            return 0;
        }

        if (cur != nullptr && cur->right != nullptr) {
            cur = cur->right;
            while (cur->left != nullptr) {
                st.push(cur);
                cur = cur->left;
            }
            return 0;
        }

        cur = nullptr;
        curpos++;
        return IsTabEnded();
    }

    TKey GetKey() const override {
        if (cur != nullptr) {
            return cur->key;
        }
        else {
            return TKey();
        }
    }

    TValue GetValuePtr() const override {
        if (cur != nullptr) {
            return *(cur->value);
        }
        else {
            return TValue();
        }
    }

    
    template<typename TKey, typename TValue>
    TreeNode<TKey, TValue>* RotateLeft(TreeNode<TKey, TValue>* node) {
        auto newRoot = exchange(node->right, exchange(node->right->left, node));
        return newRoot;
    }
 
    template<typename TKey, typename TValue>
    TreeNode<TKey, TValue>* RotateRight(TreeNode<TKey, TValue>* node) {
        auto newRoot = exchange(node->left, exchange(node->left->right, node));
        return newRoot;
    }
  

    template<typename TKey, typename TValue>
    int Height(TreeNode<TKey, TValue>* node) {
        return (node == nullptr) ? 0 : max(Height(node->left), Height(node->right)) + 1;
    }

    template<typename TKey, typename TValue>
    int BalanceFactor(TreeNode<TKey, TValue>* node) {
        if (node == nullptr) return 0;
        return max(Height(node->right), Height(node->left));
    }

    template<typename TKey, typename TValue>
    TreeNode<TKey, TValue>* InsertRecursive(TreeNode<TKey, TValue>* node, TKey key, TValue d) {
        if (node == nullptr) {
            return new typename ::TreeNode<TKey, TValue>(key, new TValue(d), nullptr, nullptr);
        }

        if (key < node->key) {
            node->left = InsertRecursive(node->left, key, d);
        } else if (key > node->key) {
            node->right = InsertRecursive(node->right, key, d);
        } else {
            delete node->value;
            node->value = new TValue(d);
            return node;
        }

        int balance = BalanceFactor(node);

        if (balance > 1 && key < node->left->key) {
            return RotateRight(node);
        }

        if (balance < -1 && key > node->right->key) {
            return RotateLeft(node);
        }

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


    template<typename TKey, typename TValue>
    TreeNode<TKey, TValue>* DeleteRecursive(TreeNode<TKey, TValue>* node, TKey k) {
        if (node == nullptr) return nullptr;

        if (k < node->key) {
            node->left = DeleteRecursive(move(node->left), k);
        }
        else if (k > node->key) {
            node->right = DeleteRecursive(move(node->right), k);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                TreeNode<TKey, TValue>* temp = (node->left != nullptr) ? node->left : node->right;
                if (temp == nullptr) {
                    delete node;
                    return nullptr;
                }
                else {
                    *node = *temp;
                    delete temp;
                    node->left = nullptr;
                    node->right = nullptr;
                    return node;
                }
            }
            else {
                TreeNode<TKey, TValue>* temp = FindMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = DeleteRecursive(move(node->right), temp->key);
            }
        }

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
  
    template<typename TKey, typename TValue>
    TreeNode<TKey, TValue>* FindMin(TreeNode<TKey, TValue>* node) {
        return (node->left != nullptr) ? FindMin(node->left) : node;
    }
};

