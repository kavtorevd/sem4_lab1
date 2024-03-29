#pragma once
#include <vector>
#include <iostream>
#include <table/SimpleTable.h>


using namespace std;

template <typename TKey, typename TValue> 
class ArrayTable : public SimpleTable<TKey, TValue>{
public:
	struct TTableRec {
		TKey key;
		TValue value;
	};
	vector<TTableRec> data{};
	ArrayTable() = default;
	size_t size() const noexcept { return data.size(); }
	TValue& operator[](size_t pos) { return data[pos].value; }

	void Delete(TKey key) override{
		for (size_t i = 0; i < data.size(); i++)
			if (data[i].key == key) {
				data[i] = data[data.size() - 1];
				data.pop_back();
				return;
			}
	}

	TValue* Find(TKey key) override {
		for (auto& val : data)
			if (val.key == key)
				return &val.value;
		return nullptr;
	}

	void Insert(TKey key, TValue value) override {
		//TValue* newValue = new TValue(value);
		//TTableRec tab = { key, newValue };
		if (Find(key))
			return;
		data.push_back({ key, value });
	}
	bool IsFull() const override { return false; }

	friend ostream& operator <<(ostream& os, ArrayTable& tab) {
		cout << "\nTable:";
		for (size_t i = 0; i < tab.size(); i++) {
			os << "\nkey: " << tab.data[i].key << " value: " << tab.data[i].value;
		}
		return os;
	}
};

