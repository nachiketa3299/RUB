#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>

using namespace std;

template <size_t N>
void test_bitset() {
  cout << "* sizeof(bitset<" << N << ">): ";
  cout << "required: " << (size_t)ceil(N / (float)8) << "B, ";
  cout << "real: " << sizeof(bitset<N> {}) << "B" << '\n';

  cout << "* sizeof(vector<bool>("<< N << ")): ";
  cout << "required: " << (size_t)ceil(N / (float)8) << "B, ";
  cout << "real: " << vector<bool>(N).capacity() / 8 << "B" << '\n';
  cout << '\n';
}

int main() {
  bitset<3> b{33};
  bitset<128> b2{33};
  cout << b << '\n';
  cout << b2 << '\n';

}