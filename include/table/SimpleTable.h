#pragma once

#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <typename TKey, typename TValue>
class SimpleTable {
	
public:
	int count = 0;
	int GetDataCount() const {
		return count;
	}
	bool IsEmpty() const {
		if (count == 0) return true;
		else return false;
	}
	virtual bool IsFull() const = 0;                       // заполнена?
	// основные методы
	virtual TValue* Find(TKey) = 0;         // найти запись
	virtual void Insert(TKey, TValue) = 0; // вставить
	virtual void Delete(TKey) = 0;         // удалить запись
	// навигация
	virtual int Reset(void) = 0; // установить на первую запись
	virtual int IsTabEnded(void) const = 0; // таблица завершена?
	virtual int GoNext(void) = 0; // переход к следующей записи
	// (=1 после применения GoNext для последней записи таблицы)
	// доступ
	virtual TKey GetKey(void) const = 0;
	virtual TValue GetValuePtr(void) const = 0;
	// Печать таблицы
	friend ostream& operator<<(ostream& os, SimpleTable& tab)
	{
		cout << "Table printing" << endl;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			os << " Key: " << tab.GetKey() << " Val: " << tab.GetValuePtr() << endl;
		}
		return os;
	}

};

