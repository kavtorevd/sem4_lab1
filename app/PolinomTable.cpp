#pragma once
#include "table/SimpleTable.h"
#include "table/ArrayTable.h"
#include "table/ListTable.h"
#include "polinom/TPolinom.h"
#include "string.h"
#include <string.h>
#include "table/OpenAdressingHashTable.h"


using namespace std;

int main() {

	//TPolinom p1("4x^5y^2z^4+3x^9y^9z^9");
	//cout << p1.ToString() << endl;


	ArrayTable<int, string> t;
	t.Insert(11, "4x^5y^2z^4+3x^9y^9z^9");
	t.Insert(2, "3x^6y^2z^1+4x^7y^1z^5");
	OpenAdressingHashTable<string, string> bob(20, 20);
	bob.Insert("11", "4x^5y^2z^4+3x^9y^9z^9");
	bob.Insert("2", "3x^6y^2z^1+4x^7y^1z^5");
	cout << bob << endl;
	bob.Delete("2");
	cout << bob << endl;
	
	/*cout << t << endl;
	t.Delete(4);
	cout << t;*/

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


}

