#pragma once
#include <cstdint>



class ITree {

 private:

 public:
  virtual void addNode(char*) = 0;
  virtual void print() = 0;
  std::shared_ptr<ITree> createTree() {};
  
  // void printTree();
  // void getSize();
  // double getAverageHeight();
  // uint64_t getChecksum();
  // uint64_t getHeight();

  /*template <typename LYAMBDA>
  void leftTravers(LYAMBDA f, Vertex* vertex = this->_Root) {
    if (vertex == nullptr) {
      return;
    }

    __doForEach(vertex->Left, f);
    f(vertex->Data);
    __doForEach(vertex->Right, f);
  }

  template <typename LYAMBDA>
  void rightTravers(LYAMBDA f, Vertex* vertex = this->_Root) {
    if (vertex == nullptr) {
      return;
    }

    __doForEach(vertex->Right, f);
    f(vertex->Data);
    __doForEach(vertex->Left, f);
  }

  template <typename LYAMBDA>
  void upperTravers(LYAMBDA f, Vertex* vertex = this->_Root) {
    if (vertex == nullptr) {
      return;
    }

    f(vertex->Data);
    __doForEach(vertex->Left, f);
    __doForEach(vertex->Right, f);
  }
  */
};