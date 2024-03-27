#pragma once

using namespace std;

template <typename TKey, typename TValue> class ArrayTable {
	struct TTableRec {
		TKey key;
		TValue value;
	};
	vector<TTableRec> data{};
public:
	ArrayTable() {}

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
};

