#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vs = vector<string>;
using Pos = pair<ll, ll>;
using Move = tuple<vs, Pos, ll>;
using vb = vector<bool>;
using vvb = vector<vb>;

ll r, c;
vs Map;

vl dr{-1, 1, 0, 0};
vl dc{0, 0, -1, 1};
vvb visit;
ll solve(Pos s, Pos d) {
  queue<Move> Q{};
  Q.push({Map, s, 0});
  visit[s.first][s.second] = true;

  while (!Q.empty()) {
    auto [mp, f, t] = Q.front();
    auto [fr, fc] = f;
    Q.pop();

    if (fr == d.first && fc == d.second) {
      return t;
    }

    if (mp[fr][fc] == '*') continue;

    for (auto p = 0; p < 4; ++p) {
      const auto& nr = fr + dr[p];
      const auto& nc = fc + dc[p];

      if (nr < 0 || r <= nr || nc < 0 || c <= nc) continue;
      if (visit[nr][nc]) continue;
      if (mp[nr][nc] != '.' && mp[nr][nc] != 'D') continue;

      auto cpmp = mp;
      for (auto i = 0; i < r; ++i) {
        for (auto j = 0; j < c; ++j) {
          if (mp[i][j] != '.') continue;

          for (auto pp = 0; pp < 4; ++pp) {
            const auto& ni = i + dr[pp];
            const auto& nj = j + dc[pp];

            if (ni < 0 || r <= ni || nj < 0 || c <= nj) continue;

            if (mp[ni][nj] == '*') {
              cpmp[i][j] = '*';
            }
          }
        }
      }

      Q.push({cpmp, {nr, nc}, t + 1});
      visit[nr][nc] = true;
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> r >> c;
  Map = vs(r);
  for (auto&& x : Map) {
    cin >> x;
  }

  Pos s, d;
  for (auto i = 0; i < r; ++i) {
    for (auto j = 0; j < c; ++j) {
      if (Map[i][j] == 'S') {
        s = {i, j};
        Map[i][j] = '.';
      } else if (Map[i][j] == 'D') {
        d = {i, j};
      }
    }
  }

  visit = vvb(r, vb(c, false));
  const auto& ans = solve(s, d);

  if (ans > 0) {
    cout << ans;
  } else {
    cout << "KAKTUS";
  }

  return 0;
}