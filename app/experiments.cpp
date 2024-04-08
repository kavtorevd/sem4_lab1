#pragma once
#include "table/SimpleTable.h"
#include "table/ArrayTable.h"
#include "table/ArraySortTable.h"
#include "table/ListTable.h"
#include "table/TreeTable.h"
#include "table/ListHashTable.h"
#include "table/OpenAdressingHashTable.h"

#include <string.h>


using namespace std;
#include <chrono>
#include <ctime>
#include <random>

#include "polinom/TPolinom.h"


string generateRandomNumber() {
    random_device rd;
    mt19937 gen(rd());

    static const int minStringLength = 4;
    static const int maxStringLength = 12;

    uniform_int_distribution<> lengthDis(minStringLength / 4,
        maxStringLength / 4);
    int length = lengthDis(gen) * 4;

    std::uniform_int_distribution<> digitDis(1, 9);
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += std::to_string(digitDis(gen));
    }
    return result;
}

string generateRandomString() {
    static const std::string characters =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const int minLength = 5;
    static const int maxLength = 9;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> lengthDis(minLength, maxLength);
    int length = lengthDis(gen);

    std::uniform_int_distribution<> charDis(0, characters.size() - 1);
    std::string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += characters[charDis(gen)];
    }
    return randomString;
}

int main() {
    ListTable<string, string> listTable;
    ArrayTable<string, string> arrayTable;
    TreeTable<string, string> treeTable;
    HashTable<string, string> listhashTable(25);
    OpenAdressingHashTable<string, string> openHashTable(25, 2);
    ArraySortTable<string, string> sortArrayTable;
    const int tableSize = 2000;
    string key;
    TPolinom value, value1;
    string s1;
    vector<int> v;
    for (int i = 0; i < tableSize; i++) {
        key = generateRandomString();
        s1 = generateRandomNumber();

        if (i == tableSize / 2) {
            listTable.Insert("100", "23");
            arrayTable.Insert("100", "23");
            treeTable.Insert("100", "23");
            listhashTable.Insert("100", "23");
            openHashTable.Insert("100", "23");
            sortArrayTable.Insert("100", "23");
            listTable.Insert("101", "23");
            arrayTable.Insert("101", "23");
            treeTable.Insert("101", "23");
            listhashTable.Insert("101", "23");
            openHashTable.Insert("101", "23");
            sortArrayTable.Insert("101", "23");
        }
        else {
            listTable.Insert(key, s1);
            arrayTable.Insert(key, s1);
            treeTable.Insert(key, s1);
            listhashTable.Insert(key, s1);
            openHashTable.Insert(key, s1);
            sortArrayTable.Insert(key, s1);
        }
    }

    auto start = std::chrono::steady_clock::now();
    arrayTable.Insert(generateRandomString(), "123");
    auto end = std::chrono::steady_clock::now();
    std::cout << "Insert | ArrayTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    listTable.Insert(generateRandomString(), "123");
    end = std::chrono::steady_clock::now();
    std::cout << "Insert | ListTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    treeTable.Insert(generateRandomString(), "123");
    end = std::chrono::steady_clock::now();
    std::cout << "Insert | treeTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    listhashTable.Insert(generateRandomString(), "123");
    end = std::chrono::steady_clock::now();
    std::cout << "Insert | listhashTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    openHashTable.Insert(generateRandomString(), "123");
    end = std::chrono::steady_clock::now();
    std::cout << "Insert | openAddrHashTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    sortArrayTable.Insert(generateRandomString(), "123");
    end = std::chrono::steady_clock::now();
    std::cout << "Insert | sortArrayTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;
    std::cout << std::endl;

    start = std::chrono::steady_clock::now();
    arrayTable.Delete("101");
    end = std::chrono::steady_clock::now();
    std::cout << "Delete | arrayTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    listTable.Delete("101");
    end = std::chrono::steady_clock::now();
    std::cout << "Delete | listTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    treeTable.Delete("101");
    end = std::chrono::steady_clock::now();
    std::cout << "Delete | treeTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    listhashTable.Delete("101");
    end = std::chrono::steady_clock::now();
    std::cout << "Delete | listhashTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    openHashTable.Delete("101");
    end = std::chrono::steady_clock::now();
    std::cout << "Delete | openAddrHashTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    sortArrayTable.Delete("101");
    end = std::chrono::steady_clock::now();
    std::cout << "Delete | SortArrayTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    std::cout << std::endl;

    start = std::chrono::steady_clock::now();
    arrayTable.Find("100");
    end = std::chrono::steady_clock::now();
    std::cout << "Search | ArrayTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    listTable.Find("100");
    end = std::chrono::steady_clock::now();
    std::cout << "Search | listTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    treeTable.Find("100");
    end = std::chrono::steady_clock::now();
    std::cout << "Search | treeTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    listhashTable.Find("100");
    end = std::chrono::steady_clock::now();
    std::cout << "Search | listhashTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    openHashTable.Find("100");
    end = std::chrono::steady_clock::now();
    std::cout << "Search | openAddrHashTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    sortArrayTable.Find("100");
    end = std::chrono::steady_clock::now();
    std::cout << "Search | sortArrayTable: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end -
            start)
        .count()
        << " microseconds" << std::endl;

    return 0;
}
