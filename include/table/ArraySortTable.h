#pragma once

#include <vector>
#include <iostream>
#include <table/SimpleTable.h>
#include <algorithm>


using namespace std;

template <typename TKey, typename TValue>
class ArraySortTable : public SimpleTable<TKey, TValue> {
public:
    size_t current;
    struct TTableRec {
        TKey key;
        TValue* value;
    };
    vector<TTableRec> data{};
    ArraySortTable() = default;
    size_t size() const noexcept { return data.size(); }
    TValue& operator[](size_t pos) { return data[pos].value; }

    void Delete(TKey key) override {
        for (size_t i = 0; i < data.size(); i++)
            if (data[i].key == key) {
                data.erase(data.begin() + i);
                count--;
                return;
            }
    }

    TValue* Find(TKey key) override {
        for (auto& val : data)
            if (val.key == key)
                return val.value;
        return nullptr;
    }

    void Insert(TKey key, TValue value) override { //
        TValue* newValue = new TValue(value);
        TTableRec tab = { key, newValue };

        data.push_back(tab);
        count++;

        sort(data.begin(), data.end(), [](const TTableRec& a, const TTableRec& b) {return a.key < b.key; });
        current = data.size() - 1;
    }
    bool IsFull() const override { return false; }
    // навигация

    int Reset() override {
        current = 0;
        return current;
    }

    int IsTabEnded() const override { return current >= data.size(); }

    int GoNext(void) override {
        current++;
        return current;
    }
    // доступ
    TKey GetKey(void) const override { return data[current].key; }
    TValue GetValuePtr(void) const override { return *data[current].value; }
};