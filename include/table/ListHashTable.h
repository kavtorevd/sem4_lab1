#pragma once
#include <table/SimpleTable.h>
#include <list>

template <typename TKey, typename TValue>
struct HashEntry {
    TKey key;
    TValue* value;
    HashEntry(TKey k = TKey(), TValue* d = nullptr) : key(k), value(d) {}
};

template <typename TKey, typename TValue>
class HashTable : public SimpleTable<TKey, TValue> {
public:
    virtual unsigned long HashFunc(const TKey key) {
        unsigned long hashval = 0;
        int len = key.size();
        for (int i = 0; i < len; ++i)
            hashval = (hashval << 3) + key[i];
        return hashval;
    }

protected:
    int tableSize;
    int currentList;
    std::list<HashEntry<TKey, TValue>>* table;
    typename std::list<HashEntry<TKey, TValue>>::iterator chainStart;

public:
    HashTable(int size) {
        table = new std::list<HashEntry<TKey, TValue>>[size];
        tableSize = size;
        currentList = 0;
        for (int i = 0; i < tableSize; i++)
            table[i] = std::list<HashEntry<TKey, TValue>>();
    }

    ~HashTable() { delete[] table; }

    bool IsFull() const override { return false; }

    TValue* Find(TKey key) override {
        HashEntry<TKey, TValue>* tmp = nullptr;
        currentList = HashFunc(key) % tableSize;
        std::list<HashEntry<TKey, TValue>>* lst = table + currentList;
        for (auto& rec : *lst) {
            if (rec.key == key) {
                tmp = new HashEntry<TKey, TValue>(rec.key, rec.value);
                break;
            }
        }
        if (tmp == nullptr) return nullptr;
        TValue* val = tmp->value;
        return val;
    }

    void Insert(TKey key, TValue value) override {
        currentList = HashFunc(key) % tableSize;
        std::list<HashEntry<TKey, TValue>>* lst = table + currentList;
        TValue* val = new TValue(value);
        HashEntry<TKey, TValue> entry(key, val);
        lst->push_back(entry);
    }

    void Delete(TKey key) override {
        currentList = HashFunc(key) % tableSize;
        std::list<HashEntry<TKey, TValue>>* lst = table + currentList;
        for (auto it = lst->begin(); it != lst->end(); ++it) {
            if (it->key == key) {
                it = lst->erase(it);
                return;
            }
        }
    }

    int Reset() override {
        currentList = 0;
        while (table[currentList].empty()) {
            currentList++;
            if (IsTabEnded()) {
                return false;
            }
        }
        chainStart = table[currentList].begin();
        return !IsTabEnded();
    }

    int IsTabEnded() const override { return currentList >= tableSize; }

    int GoNext() override {
        chainStart++;
        if (chainStart != table[currentList].end()) {
            return !IsTabEnded();
        }
        currentList++;
        while (table[currentList].empty() && !IsTabEnded()) {
            currentList++;
        }
        if (IsTabEnded()) {
            return false;
        }
        chainStart = table[currentList].begin();
        return !IsTabEnded();
    }

    TKey GetKey() const override {
        if (currentList == tableSize) {
            throw std::out_of_range("No key at this position");
        }
        return (table + currentList)->front().key;
    }

    TValue GetValuePtr() const override {
        if (currentList == tableSize) {
            throw std::out_of_range("No value at this position");
        }
        return *(table + currentList)->front().value;
    }
};
