#pragma once
#include "table/SimpleTable.h"
#include "table/ArrayTable.h"
#include "table/ListTable.h"
#include "polinom/TPolinom.h"
#include "string.h"
#include "table/OpenAdressingHashTable.h"
#include <table/AllTables.h>


using namespace std;

int MenuValue() {
	int i;
	cout << " 1. Add Polinom \n 2. Search Polinom \n 3. Erase Polinom \n 4. Sum Polinom \n 5. Multiply by Const \n 6. Exit \n";
	cout << " Enter the value: ";
	cin >> i;
	return i;
}

void GetTablest(AllTable<string, string> tab) {
    system("CLS");
    vector<vector<string>> pols;
    vector<vector<string>> keys;
    int c = 0;
    for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext()) {
        vector<string> a;
        vector<string> a1;
        a = tab.GetValuePtr();
        a1 = tab.GetKey();
        pols.push_back(a);
        keys.push_back(a1);
        c++;
    }
    for (int i = 0; i < 6; i++) {
        switch (i) {
        case 0:
            cout << "ArrayTable"
                << "\n\n";
            break;
        case 1:
            cout << "ListTable"
                << "\n\n";
            break;
        case 2:
            cout << "ListHashTable"
                << "\n\n";
            break;
        case 3:
            cout << "OpenAddrHashTable"
                << "\n\n";
            break;
        case 4:
            cout << "SortArrayTable"
                << "\n\n";
            break;
        case 5:
            cout << "TreeTable"
                << "\n\n";
            break;
        }
        for (int j = 0; j < c; j++) {
            //TPolinom pol(pols[j][i]);
            cout << keys[j][i] << "  " << pols[j][i] << "     ";
            cout << "\n\n";
        }
    }
}

int main() {

	
    AllTable<string, string> tab;
    tab.Insert("5", "3x^4y^7z^1+1x^3y^7z^1");
    tab.Insert("6", "1x^3y^7z^1");
    tab.Insert("4", "2x^5y^9z^4");
    //tab.Insert("59", "6x^4y^8z^9+5x^5y^7z^9");
	cout << "Welcome to the program PolinomTable! \n\n";
	cout << "Menu of the program: \n";
	//MenuValue();
    int menu;
    menu = MenuValue();
    while (menu != 7) {
        switch (menu) {
        case 1: {
            cout << "Enter the key";
            cout << "\n";
            string key;
            cin >> key;
            cout << "\n";
            string str;
            cout << "Enter the polynomial\n";
            cin >> str;
            tab.Insert(key, str);
            GetTablest(tab);
            cout << "\n\n";
            menu = MenuValue();
            break;
        }
        case 2: {
            cout << "Enter the key";
            cout << "\n";
            string key;
            cin >> key;
            cout << "\n";
            vector<string*> a = tab.Find(key);
            vector<string> b;
            for (int i = 0; i < 6; i++) b.push_back(*a[i]);
            GetTablest(tab);
            cout << "\n\n";
            TPolinom pol(b[0]);
            cout << "Your result:  " << pol.ToString();
            cout << "\n\n\n";
            menu = MenuValue();
            break;
        }
        case 3: {
            cout << "Enter the key";
            cout << "\n";
            string key;
            cin >> key;
            cout << "\n";
            tab.Delete(key);
            GetTablest(tab);
            cout << "\n\n";
            menu = MenuValue();
            break;
        }
        case 4: {
            cout << "Enter the first key";
            cout << "\n";
            string key1;
            cin >> key1;
            cout << "\n";
            cout << "Enter the second key";
            cout << "\n";
            string key2;
            cin >> key2;
            cout << "\n";
            vector<string*> a = tab.Find(key1);
            vector<string> b;
            vector<string*> a1 = tab.Find(key2);
            vector<string> b1;
            for (int i = 0; i < 6; i++) b.push_back(*a[i]);
            for (int i = 0; i < 6; i++) b1.push_back(*a1[i]);
            TPolinom pol1(b[0]);
            TPolinom pol2(b1[0]);
            TPolinom pol(b1[0]);
            pol = pol1 + pol2;
            GetTablest(tab);
            cout << "\n\n";
            cout << "Your result:  " << pol.ToString();
            cout << "\n\n\n";
            menu = MenuValue();
            break;
        }
        case 5: {
            cout << "Enter the key";
            cout << "\n";
            string key;
            cin >> key;
            cout << "\n";
            cout << "Enter the coef";
            cout << "\n";
            int coef;
            cin >> coef;
            cout << "\n";
            vector<string*> a = tab.Find(key);
            vector<string> b;
            for (int i = 0; i < 6; i++) b.push_back(*a[i]);
            TPolinom pol(b[0]);
            pol = pol * coef;
            GetTablest(tab);
            cout << "\n\n";
            cout << "Your result:  " << pol.ToString();
            cout << "\n\n\n";
            menu = MenuValue();
            break;
        }
        /*case 6: {
            cout << "Enter the key";
            cout << "\n";
            string key;
            cin >> key;
            cout << "\n";
            cout << "Enter the coefs";
            cout << "\n";
            int x;
            int y;
            int z;
            cin >> x >> y >> z;
            cout << "\n";
            vector<string*> a = tab.Find(key);
            vector<string> b;
            for (int i = 0; i < 6; i++) b.push_back(*a[i]);
            TPolinom pol(b[0]);
            double Point = pol.Evaluate(x, y, z);
             GetTablest(tab);
            cout << "\n\n";
            cout << "Your result:  " << Point;
            cout << "\n\n\n";
            menu = CheckMenu();
            break;
        }*/
        }
    }
    return 0;

    

    
        
        
        
	//TPolinom p1("4x^5y^2z^4+3x^9y^9z^9");
	//cout << p1.ToString() << endl;


	/*ArrayTable<int, string> t;
	t.Insert(11, "4x^5y^2z^4+3x^9y^9z^9");
	t.Insert(2, "3x^6y^2z^1+4x^7y^1z^5");*/
	
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

