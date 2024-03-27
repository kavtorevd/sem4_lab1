#pragma once
#include "table/SimpleTable.h"
#include "table/ArrayTable.h"
#include "table/ListTable.h"
#include "string.h"
#include <string.h>


using namespace std;

int main() {
	//ArrayTable<int, string> t;
	//t.Insert(11, "0000");
	//t.Insert(2, "xsds");
	//t.Insert(4, "vsdvxs");
	//t.Insert(32, "mmsds");
	//t.Insert(21, "22s2dsds");
	//cout << t << endl;
	//t.Delete(4);
	//cout << t;

	ListTable<int, string> t;
	t.Insert(11, "0000");
	cout << *(t.Find(11));
	t.Insert(2, "xsds");
	t.Insert(4, "vsdvxs");
	t.Insert(32, "mmsds");
	t.Insert(21, "22s2dsds");
	cout << t << endl;
	t.Delete(4);
	cout << t;
}

