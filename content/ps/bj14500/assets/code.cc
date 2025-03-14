#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Tet {
  pair<int, int> poss[4];

  inline static Tet get_global_tet(const Tet& tet, pair<int, int> pivot)  {
    Tet ret{tet};
    for (auto& [x, y]: ret.poss) {
      x += pivot.first;
      y += pivot.second;
    }
    return ret;
  }

  inline static Tet gen_flipped_tets(const Tet& tet) {
    Tet ret{tet};
    for (auto& [x, y]: ret.poss) {
      x = -x;
    }
    return ret;
  }

  inline static vector<Tet> gen_rotated_tets(const Tet& tet) {
    vector<Tet> ret;
    // 0, 90, 180, 270 일 때 값
    static constexpr int cos[] { 1, 0, -1, 0 }; 
    static constexpr int sin[] { 0, 1, 0, -1 };

    for (int i = 0; i < sizeof(cos)/ sizeof(cos[0]); ++i) {
      Tet ctet{tet};

      for (auto& [x, y]: ctet.poss) {
        int n_x = x * cos[i] - y * sin[i];
        int n_y = y * cos[i] + x * sin[i];

        x = n_x;
        y = n_y;
      }

      ret.push_back(ctet);
    }
    return ret;
  }

  inline static vector<Tet> gen_all_transformed_tets(const Tet& tet) {
    vector<Tet> normal_rotated = gen_rotated_tets(tet);
    vector<Tet> flipped_rotated = gen_rotated_tets(gen_flipped_tets(tet));

    normal_rotated.insert(normal_rotated.end(), 
      make_move_iterator(flipped_rotated.begin()),
      make_move_iterator(flipped_rotated.end())
    );
    return normal_rotated;
  }

  inline static bool is_valid_global_tet(int mx, int my, const Tet& g_tet) {
    for (auto& [x, y]: g_tet.poss) {
      if (!(0 <= x && x < mx) || !(0 <= y && y < my)) {
        return false;
      }
    }
    return true;
  }

  inline static int process_score(const vector<vector<int>>& board, const Tet& g_tet) {
    int score{0};

    for (const auto& [x, y]: g_tet.poss) {
      score += board[x][y];
    }

    return score;
  }
};

// 5개 테트로미노의 장의
constexpr Tet T0 {{{ 0,  0}, { 1,  0}, { 2,  0}, { 3,  0}}};
constexpr Tet T1 {{{ 0,  0}, { 1,  0}, { 0,  1}, { 1,  1}}};
constexpr Tet T2 {{{ 0,  0}, { 1,  0}, { 0,  1}, { 0,  2}}};
constexpr Tet T3 {{{ 0,  0}, { 1,  0}, { 1, -1}, { 0,  1}}};
constexpr Tet T4 {{{ 0,  0}, { 1,  0}, { 2,  0}, { 1, -1}}};

// 전체 테트로미노 배열
constexpr Tet TETS[] { T0, T1, T2, T3, T4 };


int main() {
  int N, M; cin >> N >> M; // [4, 500] 한번 순회시 10^4
  // 테트로미노 전체에 대해 매 셀마다 검증해도 10^2 * 10^4 = 10^6 ; 제한시간 OK

  // 점수 입력
  vector<vector<int>> score_map(N, vector<int>(M));
  for (vector<int>& v: score_map) {
    for (int& e: v) {
      cin >> e;
    }
  }

  int max_score{INT_MIN};

  // 모든 테트로미노에 대해 모든 회전 및 대칭 변환을 적용한 결과를 저장
  vector<Tet> all_local_tets;
  for (const Tet& tet: TETS) {
    vector<Tet> c_all = Tet::gen_all_transformed_tets(tet);

    all_local_tets.insert(
      all_local_tets.end(),
      make_move_iterator(c_all.begin()), 
      make_move_iterator(c_all.end())
    );
  }

  // 점수판의 모든 셀에 대해 모든 테트로미노를 넣어보고, 가능한 경우 최대값 찾기
  for (int x = 0; x < score_map.size(); ++x) {
    for (int y = 0; y < score_map[x].size(); ++y) {
      for (const Tet& tet: all_local_tets) {
        Tet g_tet = Tet::get_global_tet(tet, {x, y});

        if (!Tet::is_valid_global_tet(N, M, g_tet)) 
          continue;

        max_score = max(max_score, Tet::process_score(score_map, g_tet));
      }
    }
  }

  // 최대값 출력
  cout << max_score;

  return 0;
}