#pragma once
#ifndef MY_LIST
#define MY_LIST

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "AVL.h"

struct with_separator {
  with_separator(std::string sep) : sep(std::move(sep)) {}

  std::string sep;
};
struct separated_stream {
  separated_stream(std::ostream &stream, std::string sep)
      : _stream(stream), _sep(std::move(sep)), _first(true) {}

  template <class Rhs>
  separated_stream &operator<<(Rhs &&rhs) {
    if (_first)
      _first = false;
    else
      _stream << _sep;

    _stream << std::forward<Rhs>(rhs);
    return *this;
  }

  separated_stream &operator<<(std::ostream &(*manip)(std::ostream &)) {
    manip(_stream);
    return *this;
  }

 private:
  std::ostream &_stream;
  std::string _sep;
  bool _first;
};
separated_stream operator<<(std::ostream &stream, with_separator wsep) {
  return separated_stream(stream, std::move(wsep.sep));
}

template <typename T>
class myList {
  typedef vertex<T> Vertex;
 private:
  struct element {
    element(element *next_, T str_) : next(next_), str(str_){};

    element *next;
    union {
      T str;
      uint8_t digit[sizeof(T)];
    };
  };

  struct queue {
    element *head;
    element *tail;
  } Queue;

  std::vector<element *> _vec;

  void __sort(element **head, element **tail);


 public:
  myList();
  void sort();
  void push_back(T _str);
  void print();
  void toMas();
  int binSearch(int);
  void createAVL(int);
  ~myList();
};

template <typename T>
void myList<T>::sort() {
  __sort(&Queue.head, &Queue.tail);
}

template <typename T>
void myList<T>::__sort(element **head, element **tail) {
  std::vector<int> a{29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,
                     18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  8,
                     7,  6,  5,  4,  3,  2,  1,  0,  31, 30};
  int d, i, k;
  element *p;
  queue q[256];

  for (auto j : a) {
    for (i = 0; i < 256; i++) q[i].tail = (element *)&q[i].head;

    p = *head;
    k = j;
    while (p != NULL) {
      d = p->digit[k];
      q[d].tail->next = p;
      q[d].tail = p;
      p = p->next;
    }

    p = (element *)&(*head);
    for (i = 0; i < 256; i++) {
      if (q[i].tail != (element *)&q[i].head) {
        p->next = q[i].head;
        p = q[i].tail;
      }
    }
    p->next = NULL;
  }
}

template <typename T>
myList<T>::myList() {
  Queue.head = NULL;
  Queue.tail = NULL;
}

template <typename T>
void myList<T>::toMas() {
  for (element *it = Queue.head; it != NULL; it = it->next) {
    _vec.push_back(it);
  }
}

template <typename T>
void myList<T>::createAVL(int start) {
  element *temp = _vec.at(start);
  uint16_t N = 0;
  auto avl = AVL<T>::createTree();

  for (size_t i = start; _vec.at(i)->str.office == temp->str.office; i++) {
    avl->addNode(&_vec.at(i)->str);
  }
  avl->leftTravers(avl->getRoot(), [&N](T* data) { 
	  std::cout << N++ << data->name << std::endl;
  });
}

template <typename T>
int myList<T>::binSearch(int key) {
  int l = 0;
  int r = _vec.size() - 1;
  int mid;
  int mid_L = 0;

  while (l < r) {
    mid = (l + r) / 2;
    if (_vec.at(mid)->str.office < key) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  if (_vec.at(mid)->str.office == key) {
    mid_L = mid;
  } else {
    return mid_L;
  }
}

template <typename T>
void myList<T>::push_back(T _str) {
  element *temp = new element(NULL, _str);

  if (Queue.head == NULL)
    Queue.head = temp;
  else
    Queue.tail->next = temp;
  Queue.tail = temp;
}

template <typename T>
void myList<T>::print() {
  uint32_t n = 1;
  std::cout.setf(ios::left);
  for (element *it = Queue.head; it != NULL; it = it->next) {
    std::cout.width(5);
    std::cout << n++;
    std::cout << with_separator("    ") << it->str.name << it->str.office
              << it->str.position << it->str.birthDay << std::endl;
  }
}

template <typename T>
myList<T>::~myList() {
  element *element_to_delete = Queue.head;
  for (element *sn = Queue.head; sn != Queue.tail;) {
    sn = sn->next;
    delete element_to_delete;
    element_to_delete = sn;
  }
  delete element_to_delete;
}

#endif