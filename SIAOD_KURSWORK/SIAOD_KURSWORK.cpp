#include <algorithm>
#include <iostream>
#include <fstream>
#include "myList.h"

struct record {
  char name[30];
  short int office;
  char position[22];
  char birthDay[10];
};

using namespace std;

int main() {
  myList<record> list;
  ifstream dataIn("testBase2.dat", ios::binary);
  size_t i = 0;
  record record_tmp;

    for (int j = 0; j < 4000; j++, i++) {
      dataIn.read((char *)&record_tmp, sizeof(record));
      list.push_back(record_tmp);
    }

  list.sort();
  //list.print();
  list.toMas();
  list.createAVL(list.binSearch(0));
 

  dataIn.close();
}