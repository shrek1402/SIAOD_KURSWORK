#include <algorithm>
#include <fstream>
#include <iostream>
#include "Huffman.h"
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
  std::cout << n++ << " Reed data base" << std::endl;
  std::cout << n++ << " Sort data base" << std::endl;
  std::cout << n++ << " Create tree" << std::endl;
  std::cout << n++ << " Search" << std::endl;
  std::cout << n++ << " Exit" << std::endl;
  std::cin >> key;
  return key;
}

int main() {
  // list.print();
  union {
    record rec[4000];
    char bayt[4000 * sizeof(record)];
  };

  ifstream dataIn("testBase2.dat", ios::binary);
  size_t i = 0;
  record record_tmp;

  for (int j = 0; j < 4000; j++, i++) {
    dataIn.read((char *)&rec[i], sizeof(record));
  }

  std::vector<pair<char, double>> kolvo(256);

  for (size_t i = 0; i < 4000 * 64; i++) {
    kolvo[(int)bayt[i] + 128].second++;
    kolvo[(int)bayt[i] + 128].first = (int)bayt[i] + 128;
  }

  std::sort(
      kolvo.begin(), kolvo.end(),
      [](pair<char, int> a, pair<char, int> b) { return a.second > b.second; });

  while (kolvo.at(kolvo.size() - 1).second == 0) {
    kolvo.pop_back();
  }

  int sum = 0;
  double one = 1.0;
  for (int i = 0; i < kolvo.size(); i++) {
    std::cout << i << "\t" << (char)(kolvo[i].first - 128) << "\t"
              << "\t" << kolvo[i].second << std::endl;
    sum += kolvo[i].second;
  }

  for (int i = 0; i < kolvo.size(); i++) {
    if (i == kolvo.size() - 1) {
      kolvo[i].second = one;
      break;
    }
    kolvo[i].second /= sum;
    one -= kolvo[i].second;
  }
  double a = 0;
  for (int i = 0; i < kolvo.size(); i++) {
    std::cout << i << "\t" << (char)(kolvo[i].first - 128) << "\t"
              << "\t" << kolvo[i].second << std::endl;
    a += kolvo[i].second;
  }
  // std::cout << a;
  std::vector<double> ver;

  for (size_t i = 0; i < kolvo.size(); i++) {
    ver.push_back(kolvo[i].second);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////////////////

   ofstream out("zap.dat",ios::binary|ios::out); //Открываем файл в двоичном режиме для записи
   

  auto huf = Huffman::Huffman(ver.size() - 1, ver);
  auto myMap = huf.getMap(kolvo);

  for (size_t i = 0; i < 4000*64; i++) {
    auto it = myMap.find((char)(bayt[i] ));
    auto bits = it->second;
    for (size_t j = 0; j < bits.size(); j++) {
      char a = (char)(bits[j]);
      out.write((char *)&a, sizeof a);
    }
  }
  out.close();

    std::map<std::vector<bool>, char> mapDecode;

  for (auto it = myMap.begin(); it != myMap.end(); it++) {
    std::cout << it->first << "\t";
    for (size_t i = 0; i < it->second.size(); i++) {
      std::cout << it->second.at(i);
    }
    mapDecode[it->second] = it->first;
    std::cout << std::endl;
  }


  ifstream dataDecode("zap.dat", ios::binary);
  
  std::vector<bool> vDecode;
  int tempBool;
  for (int j = 0; j < 1*64; j++) {
    tempBool = 0;

    dataIn.read((char *)&tempBool, sizeof(char));
    std::cout << tempBool;
  }

  








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
        list.print();
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
        cin.ignore();
        cin.getline(a, 30);
        std::string searchName(a);
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