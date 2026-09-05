vector<int> seq(N); // 주어진 수열
for (int &e: seq) cin >> e;
 
for (auto it = seq.cbegin(); it != seq.cend(); ++it) {
  // 무식하게 다음 요소부터 끝 요소 범위에서 오큰수를 찾아내기
  auto ocs_it = find_if(
    seq.cbegin() + 1, seq.cend(),
    [&it](int const &e) { return *it < e; }
  );

  if (ocs_it == seq.cend()) cout << -1;
  else                      cout << *ocs_it;
  cout << ' ';
}