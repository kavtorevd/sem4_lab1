#pragma once
#include "table/SimpleTable.h"
#include "table/ArrayTable.h"
#include "table/ListTable.h"
#include "table/TreeTable.h"
#include "table/ListHashTable.h"

#include "polinom/TPolinom.h"
#include "string.h"
#include <string.h>


using namespace std;

string AddPolinom() {
	string pol;
	cin >> pol;
	cout << endl;
	return pol;
};

int main() {
	cout << "1. Add Polinom" << endl
		<< "2. Find Polinom" << endl
		<< "3. Delete Polinom" << endl
		<< "4. Sub Polinom" << endl
		<< "5. Mult on Const" << endl
		<< "6. Calculate in point" << endl
		<< "7. EXIT" << endl;
	int t;
	switch (t) {
	case 1:

		AddPolinom();

	}
	//TPolinom p1("4x^5y^2z^4+3x^9y^9z^9");
	//cout << p1.ToString() << endl;


	//ArrayTable<int, string> t;
	//t.Insert(11, "4x^5y^2z^4+3x^9y^9z^9");
	//t.Insert(2, "3x^6y^2z^1+4x^7y^1z^5");
	//
	//cout << t << endl;
	//t.Delete(4);
	//cout << t;

	//ListTable<int, string> t;
	//t.Insert(11, "0000");
	//cout << (t.Find(11));
	//t.Insert(2, "xsds");
	//t.Insert(4, "vsdvxs");
	//t.Insert(32, "mmsds");
	//t.Insert(21, "22s2dsds");
	//cout << t << endl;
	//t.Delete(4);
	//cout << t;

	//TreeTable<int, string> t;
	//t.Insert(11, "4x^5y^2z^4+3x^9y^9z^9");
	//t.Insert(2, "3x^6y^2z^1+4x^7y^1z^5");

	//cout << t << endl;
	//t.Delete(4);
	//cout << t;
	ListHashTable<string, string> t(20);
	//t.Insert("11", "4x^5y^2z^4+3x^9y^9z^9");
	//t.Insert("2", "3x^6y^2z^1+4x^7y^1z^5");

	//cout << t << endl;
	//t.Delete("2");
	//cout << t;

}

