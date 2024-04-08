#pragma once
#include "TNode.h"
#include <iostream>
using namespace std;

template<class T>
class TList
{
protected:
	TNode<T>* pFirst; // ïåðâîå çâåíî
	TNode<T>* pCurrent; // òåêóùåå çâåíî
	TNode<T>* pPrevious; // çâåíî ïåðåä òåêóùèì
	TNode<T>* pLast; // ïîñëåäíåå çâåíî
	TNode<T>* pStop; // çíà÷åíèå óêàçàòåëÿ, îçíà÷àþùåãî êîíåö ñïèñêà
	int length; // êîëè÷åñòâî çâåíüåâ â ñïèñêå

public:
	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // ñïèñîê ïóñò ?
	// âñòàâêà çâåíüåâ
	void InsertFirst(T item); // ïåðåä ïåðâûì
	void InsertCurrent(T item); // ïåðåä òåêóùèì 
	void InsertLast(T item);  // âñòàâèòü ïîñëåäíèì 
	// óäàëåíèå çâåíüåâ
	void DeleteFirst(); // óäàëèòü ïåðâîå çâåíî 
	void DeleteCurrent(); // óäàëèòü òåêóùåå çâåíî

	void GoNext(); // ñäâèã âïðàâî òåêóùåãî çâåíà
	// (=1 ïîñëå ïðèìåíåíèÿ GoNext äëÿ ïîñëåäíåãî çâåíà ñïèñêà)

	void Reset(); // óñòàíîâèòü íà íà÷àëî ñïèñêà
	bool IsEnd();  // ñïèñîê çàâåðøåí ?

	T GetCurrentItem();
	void SetCurrentItem(T item) { pCurrent->value = item; }
};


template <class T>
TList<T>::TList() : pFirst(nullptr), pCurrent(nullptr), pPrevious(nullptr), pLast(nullptr), pStop(nullptr), length(0) { }


template <class T>
TList<T>::~TList()
{
	while (!IsEmpty()) {
		DeleteFirst();
	}
}


template <class T>
bool TList<T>::IsEmpty()
{
	return pFirst == nullptr;
}


template <class T>
void TList<T>::InsertFirst(T item)
{
	TNode<T>* New_Node = new TNode<T>{ item, pFirst };
	pFirst = New_Node;
	if (length == 0) { pLast = pFirst; }
	length++;
}


template <class T>
void TList<T>::InsertLast(T item)
{
	TNode<T>* New_Node = new TNode<T>{ item, nullptr };
	if (IsEmpty()) { pFirst = pLast = New_Node; }
	else {
		pLast->pNext = New_Node;
		pLast = New_Node;
	}
	length++;
}


template <class T>
void TList<T>::InsertCurrent(T item)
{
	if (pCurrent == nullptr || pCurrent == pFirst) {
		InsertFirst(item);
		return;
	}
	TNode<T>* New_Node = new TNode<T>{ item, pCurrent };
	pPrevious->pNext = New_Node;
	length++;
}


template <class T>
void TList<T>::DeleteFirst()
{
	if (IsEmpty()) throw runtime_error("List is empty");
	TNode<T>* temp = pFirst;
	pFirst = pFirst->pNext;
	if (pFirst == nullptr) pLast = nullptr;
	delete temp;
	length--;
}


template <class T>
void TList<T>::DeleteCurrent()
{
	if (pCurrent == nullptr) throw runtime_error("Current node is null");
	if (pCurrent == pFirst) {
		DeleteFirst();
		return;
	}
	if (pCurrent == pLast) {
		delete pCurrent;
		pPrevious->pNext = nullptr;
		pLast = pPrevious;
		pCurrent = nullptr;
	}
	else {
		pPrevious->pNext = pCurrent->pNext;
		delete pCurrent;
		pCurrent = pPrevious->pNext;
	}
}


template <class T>
T TList<T>::GetCurrentItem()
{
	if (pCurrent == nullptr) throw runtime_error("Current node is null");
	return pCurrent->value;
}


template <class T>
void TList<T>::Reset()
{
	pCurrent = pFirst;
	pPrevious = nullptr;
}

template <class T>
void TList<T>::GoNext() {
	pPrevious = pCurrent;
	if (pCurrent != nullptr) {
		pCurrent = pCurrent->pNext;
	}
}


template <class T>
bool TList<T>::IsEnd()
{
	return pCurrent == pStop;
}