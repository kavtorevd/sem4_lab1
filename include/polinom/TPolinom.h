#pragma once
#include "list/THeadList.h"
#include "TMonom.h"
#include <string>
#include<sstream>
#include <vector>
using namespace std;

const int nonDisplayedZeros = 1; // ���������� �������������� ����� ��� ������ ������������ ��������
// ���-�� �������� ����� ������� = 6 - nonDisplayedZeros
const double EPSILON = 1e-6;


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(vector<int> a);
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other); // ������������
	TPolinom& operator+(TPolinom& q); // �������� ���������
	void AddMonom(TMonom newMonom); // ���������� ������
	TPolinom MultMonom(TMonom monom); // ��������� �������
	TPolinom& operator*(double coef); // ��������� �������� �� �����
	bool operator==(TPolinom& other);  // ��������� ��������� �� ���������
	string ToString(); // ������� � ������
};


TPolinom::TPolinom() :THeadList<TMonom>::THeadList() {}


TPolinom::TPolinom(TPolinom& other)
{
	pHead = new TNode<TMonom>;
	TNode<TMonom>* h = other.pHead->pNext;
	while (h != other.pStop) {
		this->AddMonom(h->value);
		h = h->pNext;
	}
}


TPolinom::TPolinom(string str) {
	string a;
	int sz = size(str);
	TMonom mon;

	for (int i = 0; i < sz; i++)
	{
		if (str[i] >= '1' || str[i] <= '9')
		{
			if (i == 0)
			{
				mon.coef = (str[i] - '0');
			}
			else {
				if (str[i - 1] == '+')
				{
					AddMonom(mon);
					mon.coef = (str[i] - '0');
				}
				if (str[i - 1] == '-')
				{
					AddMonom(mon);
					mon.coef = (-1) * (str[i] - '0');
				}
				if (str[i - 1] == '^')
				{
					if ((str[i - 2] == 'x') || (str[i - 2] == 'X'))
					{
						mon.index = (str[i] - '0') * 100;
					}
					if ((str[i - 2] == 'y') || (str[i - 2] == 'Y'))
					{
						mon.index += (str[i] - '0') * 10;
					}
					if ((str[i - 2] == 'z') || (str[i - 2] == 'Z'))
					{
						mon.index += str[i] - '0';
					}

				}
			}
		}
	}

	AddMonom(mon);
}


TPolinom& TPolinom::operator=(TPolinom& other)
{
	if (this != &other) {
		while (!this->IsEmpty()) {
			this->DeleteFirst();
		}
		TNode<TMonom>* current = other.pHead->pNext;
		while (current != nullptr) {
			this->AddMonom(current->value);
			current = current->pNext;
		}
	}
	return *this;
}


void TPolinom::AddMonom(TMonom m)
{
	if (m.coef == 0) throw invalid_argument("Cannot add monom with zero coefficient");
	this->Reset();
	bool isAdded = false;
	while (!this->IsEnd()) {
		if (this->pCurrent->value.index == m.index) {
			this->pCurrent->value.coef += m.coef;
			isAdded = true;
			break;
		}
		this->GoNext();
	}
	if (!isAdded) this->InsertLast(m);
	pHead->pNext = this->pFirst;
}



TPolinom& TPolinom::operator+(TPolinom& other)
{
	if (other.IsEmpty()) throw invalid_argument("Cannot add an empty polynomial");
	TNode<TMonom>* current = other.pHead->pNext;
	while (current != nullptr) {
		this->AddMonom(current->value);
		current = current->pNext;
	}
	return *this;
}


TPolinom& TPolinom::operator*(double coef)
{
	if (this->IsEmpty()) throw invalid_argument("Cannot multiply an empty polynomial");
	TNode<TMonom>* current = this->pHead->pNext;
	while (current != nullptr) {
		current->value.coef *= coef;
		if (current->pNext == nullptr) break;
		current = current->pNext;
	}
	return *this;
}


bool TPolinom::operator==(TPolinom& other) {
	if (this->GetLength() != other.GetLength()) return false;
	TNode<TMonom>* thisCurrent = this->pHead->pNext;
	TNode<TMonom>* otherCurrent = other.pHead->pNext;
	while (thisCurrent != nullptr && otherCurrent != nullptr) {
		if (!(thisCurrent->value == otherCurrent->value)) { return false; }
		thisCurrent = thisCurrent->pNext;
		otherCurrent = otherCurrent->pNext;
	}
	return thisCurrent == otherCurrent;
}


string TPolinom::ToString() {
	string result;
	int sz = GetLength();
	Reset();
	for (int i = 0; i < sz; i++) {
		TMonom mon;
		mon = GetCurrentItem();
		double A = mon.GetCoef();
		int ind = mon.GetIndex();
		result += to_string(mon.GetCoef());
		result += "x^";
		result += to_string((ind - ind % 100) / 100);
		result += " y^";
		result += to_string(((ind % 100) - (ind % 10)) / 10);
		result += " z^";
		result += to_string(ind % 10);
		if (i < sz - 1)
			GoNext();
		mon = GetCurrentItem();
		if (i != sz - 1)
			if (mon.GetCoef() > 0)
				result += " + ";
		if (mon.GetCoef() < 0)
			result += " ";

	}
	Reset();
	return result;
}

TPolinom::TPolinom(vector<int> a) {
	pStop = nullptr;
	int c = 1;
	int i1 = 1;
	int sz = a.size();
	TMonom start(a[0], a[1]);
	InsertFirst(start);
	Reset();
	TMonom mon;
	for (int i = 2; i < sz; i += 2) {
		int ind1 = a[i + 1];
		mon = GetCurrentItem();
		Reset();
		TMonom first;
		first = GetCurrentItem();
		int ind = first.GetIndex();
		if (ind1 > ind) {
			InsertFirst(TMonom(a[i], a[i + 1]));
			c++;
		}
		else {
			while (ind1 < ind) {
				if (i1 < c) {
					GoNext();
					i1++;
					mon = GetCurrentItem();
					ind = mon.GetIndex();
				}
				else {
					InsertLast(TMonom(a[i], a[i + 1]));
					c++;
					break;
				}
			}

			if (ind == ind1) {
				if (i1 == 1) {
					first.SetCoef(first.GetCoef() + a[i]);
					InsertFirst(first);
					Reset();
					GoNext();
					DeleteCurrent();
				}
				else {
					mon.SetCoef(mon.GetCoef() + a[i]);
					DeleteCurrent();
					InsertCurrent(mon);
				}
			}
			else {
				InsertCurrent(TMonom(a[i], a[i + 1]));
				c++;
			}
		}
		i1 = 1;
	}
	Reset();
}
