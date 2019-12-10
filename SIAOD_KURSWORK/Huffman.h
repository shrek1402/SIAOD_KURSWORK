#pragma once
#include <cstdint>
#include <vector>
#include <map>

class Huffman {
 private:
  std::vector<std::vector<bool>> _C;
  std::vector<uint16_t> _L;
  std::vector<std::pair<char, double>> _P;

 public:
	 std::map<char, std::vector<bool>> getMap() {
    std::map<char, std::vector<bool>> myMap;
           for (size_t i = 0; i < _P.size(); i++) {
				
           }
  }
         Huffman(uint64_t n, std::vector<std::pair<char, double>> P) : _P(P) { 
	   std::vector<uint16_t> A(_P.size());
      _L = A;
	  for (size_t i = 0; i < _P.size(); i++) {
        std::vector<bool> temp = {0};
                  _C.push_back(temp);
		}
	  
	  Huf(n, P);

    for (size_t i = 0; i < _C.size(); i++) {
            for (size_t j = 0; j < _C[i].size(); j++) {
               std::cout << _C[i][j];
            }
            std::cout << std::endl;
    }

	for (size_t i = 0; i < _L.size(); i++) {
      std::cout << i << "\t" << _L[i] << std::endl;
    }
  }

 private:
  void Huf(uint64_t n, std::vector<std::pair<char, double>> P) {
    if (n == 1) {
      _C[0][0] = 0;
      _L[0] = 1;
      _C[1][0] = 1;
      _L[1] = 1;
    } else {
      double q = P[n - 1].second + P[n].second;
      uint16_t j = Up(n, q);
      _P.pop_back();
      _P.pop_back();
      Huf(n - 1, P);
      Down(n, j);
    }
  }

  uint16_t Up(uint64_t n, double q) {
    for (std::vector<pair<char, double>>::iterator it = _P.begin();
         it < _P.end(); it++) {
      if ((*it).second <= q) {
        auto a = (uint16_t)std::distance(_P.begin(), it);
        auto tempit = it--;
        (*tempit).second = q;
        _P.insert(it, *tempit);
		
        return a;
      }
    }
  }

  void Down(uint64_t n, uint16_t j) {
    auto S = _C[j];
    auto L = _L[j];
    for (size_t i = j; i < n - 1; i++) {
      _C[i] = _C[i + 1];
      _L[i] = _L[i + 1];
    }
    _C[n - 1] = S;
    _C[n] = S;
    _C[n - 1].push_back(0);
    _C[n].push_back(1);
    _L[n - 1] = L + 1;
    _L[n] = L + 1;
  }
};
