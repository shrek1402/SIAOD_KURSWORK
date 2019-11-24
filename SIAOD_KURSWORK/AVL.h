#pragma once
#include <iostream> // ubrat'
#include <functional>
#include "vertex.h"


namespace mi {
template <typename T>
class AVL{
 public:
  

 private:
  using Vertex = vertex<T>;
  Vertex* _Root = nullptr;
  bool rost = 0;
  bool umen = 0;

 private:
  void __addNode(T* toAdd, Vertex*& vertex) {
    if (vertex == nullptr) {
      vertex = new Vertex();
      vertex->Data = toAdd;
      rost = true;
    } else {
      std::string dataName(vertex->Data->name, 3);
      std::string toAddName(toAdd->name, 3);

      if (dataName > toAddName) {
        __addNode(toAdd, vertex->Left);

        if (rost) {
          if (vertex->Balance > 0) {
            vertex->Balance = 0;
            rost = false;
          } else if (vertex->Balance == 0) {
            vertex->Balance = -1;
            rost = true;
          } else if (vertex->Left->Balance < 0) {
            LL(vertex, this);
            rost = false;
          } else {
            LR(vertex, this);
            rost = false;
          }
        }
      } else if (dataName < toAddName) {
        __addNode(toAdd, vertex->Right);

        if (rost) {
          if (vertex->Balance < 0) {
            vertex->Balance = 0;
            rost = false;
          } else if (vertex->Balance == 0) {
            vertex->Balance = 1;
            rost = true;
          } else if (vertex->Right->Balance > 0) {
            RR(vertex, this);
            rost = false;
          } else {
            RL(vertex, this);
            rost = false;
          }
        }
      } else {
        __addNode(toAdd, vertex->Right);

        if (rost) {
          if (vertex->Balance < 0) {
            vertex->Balance = 0;
            rost = false;
          } else if (vertex->Balance == 0) {
            vertex->Balance = 1;
            rost = true;
          } else if (vertex->Right->Balance > 0) {
            RR(vertex, this);
            rost = false;
          } else {
            RL(vertex, this);
            rost = false;
          }
        }
      }
    }
  };
  void __delNode(Vertex** vertex, char* toDel) {
    Vertex* q = nullptr;
    std::string name = "";
    char* nameChar = nullptr;
    if ((*vertex) != nullptr) {
      // name = (*vertex)->Data;
      nameChar = &name[0];
    }

    if ((*vertex) == nullptr) {
      umen = false;
    } else if (strcmp(nameChar, toDel) > 0) {
      __delNode(&(*vertex)->Left, toDel);
      if (umen) BL(&(*vertex), this);
    } else if (strcmp(nameChar, toDel) < 0) {
      __delNode(&(*vertex)->Right, toDel);
      if (umen) BR(&(*vertex), this);
    } else {
      q = (*vertex);
      if (q->Left == nullptr) {
        (*vertex) = q->Right;
        umen = true;
      } else if (q->Right == nullptr) {
        (*vertex) = q->Left;
        umen = true;
      } else {
        __delNodewth(&(q->Left), this, &q);
        if (umen) {
          BL(&(*vertex), this);
        }
      }
      q = nullptr;
    }
  };

  friend void __delNodewth(Vertex** r, AVL<T>* tree, Vertex** q) {
    if ((*r)->Right != nullptr) {
      __delNodewth(&(*r)->Right, tree, q);
      if (tree->umen) {
        BR(&(*r), tree);
      }
    } else {
      (*q)->Data = (*r)->Data;
      (*q) = (*r);
      (*r) = (*r)->Left;
      tree->umen = true;
    }
  };
  friend void LL(Vertex*& vertex, AVL<T>*) {
    Vertex* q = vertex->Left;
    vertex->Balance = 0;
    q->Balance = 0;
    vertex->Left = q->Right;
    q->Right = vertex;
    vertex = q;
  };
  friend void LR(Vertex*& vertex, AVL<T>*) {
    Vertex* r;
    Vertex* q = vertex->Left;
    r = q->Right;

    if (r->Balance < 0) {
      vertex->Balance = 1;
    } else {
      vertex->Balance = 0;
    }

    if (r->Balance > 0) {
      q->Balance = 1;
    } else {
      q->Balance = 0;
    }

    r->Balance = 0;
    q->Right = r->Left;
    vertex->Left = r->Right;
    r->Left = q;
    r->Right = vertex;
    vertex = r;
  };
  friend void RL(Vertex*& vertex, AVL<T>*) {
    Vertex* r;
    Vertex* q = vertex->Right;
    r = q->Left;
    if (r->Balance > 0) {
      vertex->Balance -= 1;
    } else {
      vertex->Balance = 0;
    }
    if (r->Balance < 0) {
      q->Balance += 1;
    } else {
      q->Balance = 0;
    }

    r->Balance = 0;
    vertex->Right = r->Left;
    q->Left = r->Right;
    r->Right = q;
    r->Left = vertex;
    vertex = r;
  };
  friend void RR(Vertex*& vertex, AVL<T>*) {
    Vertex* q = vertex->Right;
    vertex->Balance = 0;
    q->Balance = 0;
    vertex->Right = q->Left;
    q->Left = vertex;
    vertex = q;
  };

  friend void BL(Vertex** vertex, AVL<T>* tree) {
    if ((*vertex)->Balance == -1) {
      (*vertex)->Balance = 0;
    } else if ((*vertex)->Balance == 0) {
      (*vertex)->Balance = 1;
      tree->umen = false;
    } else if ((*vertex)->Balance == 1) {
      if ((*vertex)->Right->Balance >= 0) {
        RR1(&(*vertex), tree);
      } else {
        RL((*vertex));
      }
    }
  };
  friend void BR(Vertex** vertex, AVL<T>* tree) {
    if ((*vertex)->Balance == 1) {
      (*vertex)->Balance = 0;
    } else if ((*vertex)->Balance == 0) {
      (*vertex)->Balance = -1;
      tree->umen = false;
    } else if ((*vertex)->Balance == -1) {
      if ((*vertex)->Left->Balance <= 0) {
        LL1(&(*vertex), tree);
      } else {
        LR((*vertex));
      }
    }
  };
  friend void LL1(Vertex** vertex, AVL<T>* tree) {
    Vertex* q = (*vertex)->Left;

    if (q->Balance == 0) {
      (*vertex)->Balance = -1;
      q->Balance = 1;
      tree->umen = false;
    } else {
      (*vertex)->Balance = 0;
      q->Balance = 0;
    }

    (*vertex)->Left = q->Right;
    q->Right = (*vertex);
    (*vertex) = q;
  };
  friend void RR1(Vertex** vertex, AVL<T>* tree) {
    Vertex* q = (*vertex)->Right;

    if (q->Balance == 0) {
      (*vertex)->Balance = 1;
      q->Balance = -1;
      tree->umen = false;
    }

    (*vertex)->Right = q->Left;
    q->Left = (*vertex);
    (*vertex) = q;
  };

 public:
  AVL<T>();
  ~AVL<T>();

  static std::shared_ptr<AVL<T>> createTree();

  void addNode(T*);
  void delNode(std::string toDel);
  Vertex* getRoot() { return _Root; };

  template <typename LYAMBDA>
  void leftTravers(Vertex* vertex, LYAMBDA f);

  template <typename LYAMBDA>
  void rightTravers(Vertex* vertex, LYAMBDA lyambda);

  template <typename LYAMBDA>
  void upperTravers(Vertex* vertex, LYAMBDA lyambda);
};

template <typename T>
AVL<T>::AVL() {} 

template <typename T>
void AVL<T>::addNode(T* toAdd) {
  __addNode(toAdd, _Root);
}

template <typename T>
void AVL<T>::delNode(std::string toDel) {
  std::string toDelCrop(toDel, sizeof(char) * 3);
  char* toDelChar = &toDelCrop[0];
  __delNode(&_Root, toDelChar);
}

template <typename T>
template <typename LYAMBDA>
void AVL<T>::leftTravers(Vertex* vertex, LYAMBDA lyambda) {
  if (vertex == nullptr) {
    return;
  }

  leftTravers(vertex->Left, lyambda);
  lyambda(vertex);
  leftTravers(vertex->Right, lyambda);
}

template <typename T>
template <typename LYAMBDA>
void AVL<T>::rightTravers(Vertex* vertex, LYAMBDA lyambda) {
  if (vertex == nullptr) {
    return;
  }

  rightTravers(vertex->Right, lyambda);
  lyambda(vertex->Data);
  rightTravers(vertex->Left, lyambda);
}

template <typename T>
template <typename LYAMBDA>
void AVL<T>::upperTravers(Vertex* vertex, LYAMBDA lyambda) {
  if (vertex == nullptr) {
    return;
  }

  lyambda(vertex->Data);
  upperTravers(vertex->Left, lyambda);
  upperTravers(vertex->Right, lyambda);
}

template <typename T>
std::shared_ptr<AVL<T>> AVL<T>::createTree() {
  return std::make_shared<AVL<T>>();
};

template <typename T>
AVL<T>::~AVL() {
  leftTravers(_Root, [](Vertex* vertex) { vertex = nullptr; });
}
}  // namespace mi