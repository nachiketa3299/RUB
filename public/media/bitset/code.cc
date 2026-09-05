#include <bitset>
#include <iostream>

using namespace std;

int main() {
bitset<3> b; // 000
b[1] = 1;    // 010

// 특정 비트 또는 전체 비트를 1로 바꾼다
b.set(2);    // 110

b.flip();    // 001

cout << b << '\n'; // 출력: 001
cout << b.flip().to_ulong() << '\n'; // 출력: 110의 정수형
}