#pragma once
namespace mi {
template <typename T_DATA_VERTEX>
class vertex {
 public:

  template <typename T>
  friend class myList;

  template <typename T>
  friend class AVL;

 public:
  T_DATA_VERTEX* Data;
  int8_t Balance = 0;
  vertex* Left = nullptr;
  vertex* Right = nullptr;
};
 
}  // namespace mi