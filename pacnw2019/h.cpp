#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct pt {
  int x, y;
  pt operator + (const pt& o) const {
    return pt(x + o.x, y + o.y);
  }
  pt operator - (const pt& o) const {
    return pt(x - o.x, y - o.y);
  }
  int operator * (const pt& o) const {
    return x * o.y - y * o.x;
  }
  complex<ld> operator / (const pt& o) const {
    return complex<ld>(x, y) / complex<ld>(o.x, o.y);
  }
  bool operator < (const pt& o) const {
    return x < o.x || (x == o.x && y < o.y);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<pt> p(n);
  for(int i=0; i<n; i++) {
    cin >> p[i].x >> p[i].y;
  }

  vector to(n, vector<pair<int, int>>(n, pair(-1, -1)));
  for(int bi=0; bi<n; bi++) {
    auto base = p[bi];
    vector<pair<pt, int>> v;
    for(int i=0; i<n; i++) {
      if(i == bi) continue;
      v.emplace_back(p[i], i);
    }
    sort(begin(v), end(v), [base](auto a, auto b) -> bool {
        if(a.first < base) a.first = base + base - a.first;
        if(b.first < base) b.first = base + base - b.first;
        return (a.first - base) * (b.first - base) > 0; });
    for(int i=0; i<n-1; i++) {
      int ni = i+1 < n-1 ? i+1 : 0;
      to[bi][v[i].second] = pair(v[ni].second, bi);
    }
  }

  int ans = 0;
  vector vis(n, vector<bool>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(i == j || vis[i][j]) continue;
      map<int, int> cnt;
      pair start(i, j);
      ld angle = 0;
      for(auto v = start; angle == 0 || v != start; ) {
        vis[v.first][v.second] = true;
        cnt[v.first]++;
        auto w = to[v.first][v.second];
        //cerr << "GO " << v.first << " " << v.second << " -> " << w.first << " " << w.second << nl;
        auto first = p[v.second] - p[v.first];
        auto second = p[w.first] - p[w.second];
        ld cur = arg(second / first);
        if(cur < 0) cur += numbers::pi;
        angle += cur;
        v = w;
      }
      int mul = round(numbers::pi * 2 / angle);
      assert(mul == 1 || mul == 2);
      //cerr << "GOT mul " << mul << " from angle " << angle << nl;
      for(auto [_, c] : cnt) {
        ans = max(ans, c * mul);
      }
    }
  }
  cout << ans << nl;

  return 0;
}
