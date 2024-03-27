#pragma once

#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <typename TKey, typename TValue>
class SimpleTable {
	
public:
	SimpleTable() = default;
	//virtual size_t size() const noexcept = 0;
	//virtual TValue& operator[](size_t pos) = 0;
	virtual void Delete(TKey key) = 0;
	virtual TValue* Find(TKey key) = 0;
	virtual void Insert(TKey key, TValue value) = 0;
	virtual bool IsFull() const = 0;
};

