#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int get_dist(int x, int y) {
  int s = max(abs(x), abs(y));
  int offset = (2*s - 1) * (2*s - 1) - 1;
  if(x == s) {
    return offset + 2*s + abs(y - s);
  } else if(y == -s) {
    return offset + 4*s + abs(x - s);
  } else if(x == -s) {
    return offset + 6*s + abs(y - -s);
  } else {
    return offset + 0*s + abs(x - -s);
  }
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> xs;
  for(int i=1; i<=m; i++) {
    for(int j=1; j<=n; j++) {
      char c;
      cin >> c;
      if(c == 'X') {
        xs.emplace_back(j, m-i + 1);
      }
    }
  }

  vector<pair<vector<int>, pair<int, int>>> all;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      vector<int> pattern;
      for(auto [x, y] : xs) {
        pattern.push_back(get_dist(x-i, y-j));
      }
      sort(begin(pattern), end(pattern));
      all.emplace_back(move(pattern), pair(i, j));
    }
  }
  sort(begin(all), end(all));

  int worst = -1;
  vector<pair<int, int>> ans;
  int sum = 0;
  for(int i=0; i<size(all); i++) {
    int diff = 0;
    if(i > 0) {
      for(int j=0; j<size(xs); j++) {
        if(all[i].first[j] != all[i-1].first[j]) {
          diff = max(diff, min(all[i].first[j], all[i-1].first[j]));
          break;
        }
      }
    }
    if(i+1 < size(all)) {
      for(int j=0; j<size(xs); j++) {
        if(all[i].first[j] != all[i+1].first[j]) {
          diff = max(diff, min(all[i].first[j], all[i+1].first[j]));
          break;
        }
      }
    }
    if(diff > worst) {
      worst = diff;
      ans.clear();
    }
    if(worst == diff) {
      ans.push_back(all[i].second);
    }
    sum += diff;
  }

  cout << (ld)sum / n / m << nl;
  cout << worst << nl;
  sort(begin(ans), end(ans), [](const auto& a, const auto& b) {
      return a.second < b.second or (a.second == b.second and a.first < b.first); });
  for(auto [a, b] : ans) {
    cout << "(" << a << "," << b << ")" << " ";
  }
  cout << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
