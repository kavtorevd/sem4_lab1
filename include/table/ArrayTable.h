#pragma once
#include <vector>
#include <iostream>
#include <table/SimpleTable.h>


using namespace std;

template <typename TKey, typename TValue> 
class ArrayTable : public SimpleTable<TKey, TValue>{
public:
	size_t current;
	struct TTableRec {
		TKey key;
		TValue value;
	};
	vector<TTableRec> data{};
	ArrayTable() : current(0) { count = 0; }
	size_t size() const noexcept { return data.size(); }
	TValue& operator[](size_t pos) { return data[pos].value; }

	void Delete(TKey key) override{
		for (size_t i = 0; i < data.size(); i++)
			if (data[i].key == key) {
				data[i] = data[data.size() - 1];
				data.pop_back();
				return;
			}
		/*this->*/count--;
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
		/*this->*/count++;
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
	TValue GetValuePtr(void) const override { return data[current].value; }
};


