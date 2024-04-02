#pragma once
#include <table/SimpleTable.h>

template <typename TKey, typename TValue>
struct KeyValuePair {
	TKey key;
	TValue* value;
	KeyValuePair(TKey k = TKey(), TValue* d = nullptr) : key(k), value(d) {}
};

template <typename TKey, typename TValue>
class OpenAdressingHashTable : public SimpleTable<TKey, TValue> {
public:
	int count = 0;

	OpenAdressingHashTable(int size, int step) : SimpleTable<TKey, TValue>(), tabSize(size), hashStep(step) {
		table = new KeyValuePair<TKey, TValue>* [tabSize]();
		mark = new KeyValuePair<TKey, TValue>(TKey(), nullptr);
	}

	~OpenAdressingHashTable() {
		for (int i = 0; i < tabSize; ++i) {
			if (table[i] && table[i] != mark)
				delete table[i];
		}
		delete[] table;
		delete mark;
	}

	bool IsFull() const override { return count == tabSize; }

	TValue* Find(TKey key) override {
		int position = HashFunction(key) % tabSize;
		int initialPosition = position;
		while (table[position] != nullptr) {
			if (table[position]->key == key)
				return table[position]->value;
			position = GetNextPosition(position);
			if (position == initialPosition) break;
		}
		return nullptr;
	}

	void Insert(TKey key, TValue value) override {
		if (IsFull()) return;
		int position = HashFunction(key) % tabSize;
		int initialPosition = position;
		while (table[position] != nullptr && table[position] != mark) {
			if (table[position]->key == key)
				return;
			position = GetNextPosition(position);
			if (position == initialPosition) return;
		}
		if (table[position] == mark) --count;
		table[position] = new KeyValuePair<TKey, TValue>(key, new TValue(value));
		++count;
	}

	void Delete(TKey key) override {
		int position = HashFunction(key) % tabSize;
		int initialPosition = position;
		while (table[position] != nullptr) {
			if (table[position]->key == key) {
				delete table[position];
				table[position] = mark;
				--count;
				return;
			}
			position = GetNextPosition(position);
			if (position == initialPosition) return;
		}
	}

	int Reset() override {
		position = 0;
		while (!IsTabEnded() && (table[position] == nullptr || table[position] == mark)) {
			++position;
		}
		return IsTabEnded();
	}

	int IsTabEnded() const override { return position >= tabSize; }

	int GoNext() override {
		if (!IsTabEnded()) {
			while (++position < tabSize) {
				if (table[position] != nullptr && table[position] != mark) break;
			}
		}
		return IsTabEnded();
	}

	TKey GetKey() const override {
		if (table[position] != nullptr && table[position] != mark)
			return table[position]->key;
		return TKey();
	}

	TValue GetValuePtr() const override {
		if (table[position] != nullptr && table[position] != mark)
			return *(table[position]->value);
		return TValue();
	}

private:
	int tabSize;
	int hashStep;
	int position;
	KeyValuePair<TKey, TValue>** table;
	KeyValuePair<TKey, TValue>* mark;

	unsigned long HashFunction(const TKey key) {
		unsigned long hashval = 0;
		int len = key.size();
		for (int i = 0; i < len; ++i)
			hashval = (hashval << 3) + key[i];
		return hashval;
	}

	int GetNextPosition(int pos) { return (pos + hashStep) % tabSize; }
};