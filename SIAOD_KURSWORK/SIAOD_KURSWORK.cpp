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


uint16_t printMenu() {
  uint16_t n = 1;
  uint16_t key;
  std::cout << n++ << " Считать базу" << std::endl;
  std::cout << n++ << " Отсортировать базу" << std::endl;
  std::cout << n++ << " Построить дерево" << std::endl;
  std::cout << n++ << " Поиск по дереву" << std::endl;
  std::cout << n++ << " Выход" << std::endl;
  std::cin >> key;
  return key;
}

int main() {
  
  
  
  //list.print();
  
  
	bool exit = 1;
  while (exit) {

    switch (printMenu()) {
      case 1: {
        mi::myList<record> list;
        ifstream dataIn("testBase2.dat", ios::binary);
        size_t i = 0;
        record record_tmp;

        for (int j = 0; j < 4000; j++, i++) {
          dataIn.read((char *)&record_tmp, sizeof(record));
          list.push_back(record_tmp);
        }
        dataIn.close();
        break;
      }
      case 2: {
        mi::myList<record> list;
        ifstream dataIn("testBase2.dat", ios::binary);
        size_t i = 0;
        record record_tmp;

        for (int j = 0; j < 4000; j++, i++) {
          dataIn.read((char *)&record_tmp, sizeof(record));
          list.push_back(record_tmp);
        }
        list.sort();
        dataIn.close();
        break;
      }
        
      case 3: {
        mi::myList<record> list;
        ifstream dataIn("testBase2.dat", ios::binary);
        size_t i = 0;
        record record_tmp;

        for (int j = 0; j < 4000; j++, i++) {
          dataIn.read((char *)&record_tmp, sizeof(record));
          list.push_back(record_tmp);
        }
        list.sort();
        list.toMas();
        list.createAVL(list.binSearch(0));
        dataIn.close();
        break;
      }
      case 4: {
        mi::myList<record> list;
        ifstream dataIn("testBase2.dat", ios::binary);
        size_t i = 0;
        record record_tmp;

        for (int j = 0; j < 4000; j++, i++) {
          dataIn.read((char *)&record_tmp, sizeof(record));
          list.push_back(record_tmp);
        }
        list.sort();
        list.toMas();
        list.createAVL(list.binSearch(0));
        char a[30];
        std::cin >> a;
        std::string searchName(a, 3);
        std::vector<record *> vecSearch = list.search(searchName);
        for (size_t i = 0; i < vecSearch.size(); i++) {
          std::cout << vecSearch.at(i)->name << "\t"
                    << vecSearch.at(i)->birthDay << "\t"
                    << vecSearch.at(i)->office << "\t"
                    << vecSearch.at(i)->position << std::endl;
        }
        dataIn.close();
        break;
      }
        
      default:
        exit = 0;
        break;
    }
  }

}