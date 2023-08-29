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

struct pt {
  int x, y;
};
int dist(const pt a, const pt b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<pt> p(n);
  for(int i=0; i<n; i++) {
    cin >> p[i].x >> p[i].y;
  }

  uniform_int_distribution<int> distro(0, n-1);
  int sqrd = numeric_limits<int>::max();
  for(int i=0; i<n; i++) {
    int a = distro(rng);
    int b = distro(rng);
    while(b == a) b = distro(rng);
    sqrd = min(sqrd, dist(p[a], p[b]));
  }
  if(sqrd == 0) {
    return void(cout << 0 << nl);
  }
  int d = ceil(sqrt(sqrd));

  unordered_map<int, unordered_map<int, vector<int>>> hash;
  static constexpr int shift = 1e4;
  for(int i=0; i<n; i++) {
    int hx = (p[i].x + shift) / d;
    int hy = (p[i].y + shift) / d;
    hash[hx][hy].push_back(i);
  }

  int ans = sqrd;
  for(int i=0; i<n; i++) {
    int hx = (p[i].x + shift) / d;
    int hy = (p[i].y + shift) / d;
    for(int dx=-1; dx<=1; dx++) {
      auto it = hash.find(hx + dx);
      if(it == end(hash)) continue;
      for(int dy=-1; dy<=1; dy++) {
        auto jt = it->second.find(hy + dy);
        if(jt == end(it->second)) continue;
        for(int j : jt->second) {
          if(i == j) continue;
          ans = min(ans, dist(p[i], p[j]));
        }
      }
    }
  }

  cout << ans << nl;
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
