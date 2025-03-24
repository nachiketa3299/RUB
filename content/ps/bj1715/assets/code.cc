#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N; 
vector<int> card_packs;
priority_queue<int, vector<int>, greater<int>> pq; 

int main() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    int card_pack; cin >> card_pack;
    pq.push(card_pack);
  }

  int comparison_count = 0;

  while (pq.size() > 1) {

    int l = pq.top(); 
    pq.pop();

    int r = pq.top();
    pq.pop();

    int sum = l + r;

    comparison_count += sum;
    pq.push(sum);
  }

  cout << comparison_count;
}