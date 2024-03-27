#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <typename TKey, typename TValue> 
class ArrayTable {
	struct TTableRec {
		TKey key;
		TValue* value;
	};
	vector<TTableRec> data{};
public:
	ArrayTable() = default;
	size_t size() const noexcept { return data.size(); }
	TValue& operator[](size_t pos) { return data[pos].value; }

	void Delete(TKey key) {
		for (size_t i = 0; i < data.size(); i++)
			if (data[i].key == key) {
				data[i] = data[data.size() - 1];
				data.pop_back();
				return;
			}
	}

	TValue* Find(TKey key) {
		for (auto& val : data)
			if (val.key == key)
				return &val.value;
		return nullptr;
	}

	void Insert(TKey key, TValue value) {
		if (Find(key))
			return;
		data.push_back({ key, value });
	}

	friend ostream& operator <<(ostream& os, ArrayTable& tab) {
		cout << "\nTable:";
		for (size_t i = 0; i < tab.size(); i++) {
			os << "\nkey: " << tab.data[i].key << " value: " << tab.data[i].value;
		}
		return os;
	}
};

