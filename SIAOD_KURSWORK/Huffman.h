#pragma once
#include <cstdint>
#include <vector>
#include <map>
class Huffman {
 private:
  std::vector<std::vector<bool>> _C;
  std::vector<uint16_t> _L;
  std::vector<double> _P;

 public:
	 std::vector<uint16_t> getL() { return _L;
  }

  std::map<char, std::vector<bool>> getMap(
      std::vector<std::pair<char, double>> kolvo) {
		std::map<char, std::vector<bool>> myMap;
    
		for (size_t i = 0; i < kolvo.size(); i++) {
                  myMap[(char)(kolvo[i].first + 128)] = _C[i];  
		}
               
                return myMap;
  }
  Huffman(uint64_t n, std::vector<double> P) : _P(P) { 
	   std::vector<uint16_t> A(_P.size());
      _L = A;
	  for (size_t i = 0; i < _P.size(); i++) {
        std::vector<bool> temp = {0};
                  _C.push_back(temp);
		}
	  
	  Huf(n, _P);

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
  void Huf(uint64_t n, std::vector<double> &P) {
    if (n == 1) {
      _C[0][0] = 0;
      _C[1][0] = 1;
      _L[0] = 1;
      _L[1] = 1;
    } else {
      double q = P[P.size() - 1] + P[P.size() - 2];
      uint16_t j = Up(n, q);
      P.pop_back();
      P.pop_back();
      Huf(n - 1, P);
      Down(n, j);
    }
  }

  uint16_t Up(uint64_t n, double q) {
    for (std::vector<double>::iterator it = _P.begin(); it < _P.end(); it++) {
      if (*it < q) {
        auto a = (uint16_t)std::distance(_P.begin(), it);
        _P.insert(it, q);
		
        return a;
      }
    }
    return _P.size();
  }
  //   3 2 1 
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
