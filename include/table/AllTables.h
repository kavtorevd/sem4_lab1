#pragma once
#include <table/ListHashTable.h>
#include <table/ListTable.h>
#include <table/OpenAdressingHashTable.h>
#include <table/TreeTable.h>
#include <table/ArrayTable.h>
#include <table/ArraySortTable.h>

using namespace std;

#define MaxSize 100
template <typename TKey, typename TValue>
class AllTable {
private:
    vector<SimpleTable<TKey, TValue>*> tables;
    int count;

public:
    AllTable() {
        count = 0;
        tables.push_back(new ArrayTable<TKey, TValue>());
        tables.push_back(new ListTable<TKey, TValue>());
        tables.push_back(new HashTable<TKey, TValue>(25));
        tables.push_back(new OpenAdressingHashTable<TKey, TValue>(25, 5));
        tables.push_back(new ArraySortTable<TKey, TValue>());
        tables.push_back(new TreeTable<TKey, TValue>());
    }

    int GetDataCount() const { return count; }

    bool IsEmpty() const {
        if (count == 0)
            return true;
        else
            return false;
    }

    bool IsFull() const {
        if (count == MaxSize)
            return true;
        else
            return false;
    }

    vector<TValue*> Find(TKey key) {
        vector<TValue*> a;
        for (int i = 0; i < 6; i++) a.push_back(tables[i]->Find(key));
        return a;
    }

    void Insert(TKey key, TValue value) {
        for (int i = 0; i < 6; i++) tables[i]->Insert(key, value);
        count++;
    }

    void Delete(TKey key) {
        for (int i = 0; i < 6; i++) tables[i]->Delete(key);
        count--;
    }

    vector<int> Reset() {
        vector<int> a;
        for (int i = 0; i < 6; i++) a.push_back(tables[i]->Reset());
        return a;
    }

    int IsTabEnded() const {
        vector<int> a;
        for (int i = 0; i < 6; i++) a.push_back(tables[i]->IsTabEnded());
        return a[0];
    }

    vector<int> GoNext() {
        vector<int> a;
        for (int i = 0; i < 6; i++) a.push_back(tables[i]->GoNext());
        return a;
    }

    vector<TKey> GetKey() const {
        vector<TKey> a;
        for (int i = 0; i < 6; i++) a.push_back(tables[i]->GetKey());
        return a;
    }

    vector<TValue> GetValuePtr() const {
        vector<TValue> a;
        for (int i = 0; i < 6; i++) a.push_back(tables[i]->GetValuePtr());
        return a;
    }
};