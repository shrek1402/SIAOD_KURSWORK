#pragma once
#include <iostream> // ubrat'

template <typename T>
struct vertex {
  T* Data;
  int8_t Balance = 0;
  vertex* Left = nullptr;
  vertex* Right = nullptr;
};

template <typename T>
class AVL{
  typedef vertex<T> Vertex;
 private:
  Vertex* _Root = nullptr;
  bool rost = 0;
  bool umen = 0;
  uint16_t n = 0; //ubrat
 
private:
  void __print(Vertex* vertex);
  // ubr
  void __addNode(T* inputData, Vertex*& vertex);
  void __delNode(Vertex** vertex, char* toDel);

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
  static std::shared_ptr<AVL<T>> createTree();

  void addNode(T*);
  void delNode(std::string toDel);
  void print();
  Vertex* getRoot(){ return _Root; };

  template <typename LYAMBDA>
  void leftTravers(Vertex* vertex, LYAMBDA f);

  template <typename LYAMBDA>
  void rightTravers(LYAMBDA f, Vertex* vertex);

  template <typename LYAMBDA>
  void upperTravers(LYAMBDA f, Vertex* vertex);
};

template <typename T>
AVL<T>::AVL() {}

template <typename T>
void AVL<T>::__addNode(T* toAdd, Vertex*& vertex) {
  if (vertex == nullptr) {
    vertex = new Vertex();
    vertex->Data = toAdd;
    rost = true;
  } else if (strcmp(vertex->Data->name, toAdd->name) > 0) {
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
  } else if(strcmp(vertex->Data->name, toAdd->name) < 0) {
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

template <typename T>
void AVL<T>::addNode(T* toAdd) { __addNode(toAdd, _Root); }

template <typename T>
void AVL<T>::__delNode(Vertex** vertex, char* toDel) {
  Vertex* q = nullptr;
  std::string name = "";
  char* nameChar = nullptr;
  if ((*vertex) != nullptr) {
    //name = (*vertex)->Data;
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
}

template <typename T>
void AVL<T>::delNode(std::string toDel) {
  std::string toDelCrop(toDel, sizeof(char) * 3);
  char* toDelChar = &toDelCrop[0];
  __delNode(&_Root, toDelChar);
}

template <typename T>
void AVL<T>::print() {
  __print(_Root);
  std::cout << std::endl;
}

template <typename T>
void AVL<T>::__print(Vertex* vertex) {
  if (vertex == nullptr) return;
  
  __print(vertex->Left);
  std::cout << n++ << vertex->Data->name << std::endl;
  __print(vertex->Right);
}

template <typename T>
template <typename LYAMBDA>
void AVL<T>::leftTravers(Vertex* vertex, LYAMBDA f) {
  if (vertex == nullptr) {
    return;
  }

  leftTravers(vertex->Left, f);
  f(vertex->Data);
  leftTravers(vertex->Right, f);
}

template <typename T>
template <typename LYAMBDA>
void AVL<T>::rightTravers(LYAMBDA f, Vertex* vertex) {
  if (vertex == nullptr) {
    return;
  }

  rightTravers(vertex->Right, f);
  f(vertex->Data);
  rightTravers(vertex->Left, f);
}

template <typename T>
template <typename LYAMBDA>
void AVL<T>::upperTravers(LYAMBDA f, Vertex* vertex) {
  if (vertex == nullptr) {
    return;
  }

  f(vertex->Data);
  upperTravers(vertex->Left, f);
  upperTravers(vertex->Right, f);
}

template <typename T>
std::shared_ptr<AVL<T>> AVL<T>::createTree() {
  return std::make_shared<AVL<T>>();
};