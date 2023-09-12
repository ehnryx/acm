#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/nd_array.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Point {
  int x, y, h;
  bool operator<(const Point& o) const {
    return x < o.x;
  }
};

struct Node {
  int y, h;
  bool operator<(const Node& o) const {
    return y < o.y;
  }
};

const int N = 1 << 17;
const int L = 45;
vector<Node> st[2*N];
// avoid default values or typo bugs (missing an arg or two) are very hard to catch
void query(vector<int>& res, int lval, int rval, int l, int r, int i, int s, int e) {
  if(r < s or e < l) return; // return if out of query range
  if(l <= s and e <= r) { // interesting segment
    if(size(res) < L) {
      auto li = lower_bound(begin(st[i]), end(st[i]), Node{lval, 0});
      auto ri = upper_bound(begin(st[i]), end(st[i]), Node{rval, 0});
      for(auto it = li; it != ri and size(res) < L; it++) {
        res.push_back(it->h);
      }
    }
    return;
  }
  int m = (s + e) / 2;
  query(res, lval, rval, l, r, 2*i, s, m);
  query(res, lval, rval, l, r, 2*i+1, m+1, e);
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, q;
  cin >> n >> q;
  vector<Point> p;
  for(int i=0; i<n; i++) {
    int x, y, h;
    cin >> x >> y >> h;
    p.push_back(Point{x, y, h});
  }
  sort(begin(p), end(p));

  for(int i=0; i<n; i++) {
    st[N+i].push_back(Node{p[i].y, p[i].h});
  }
  for(int i=N-1; i>0; i--) {
    merge(
        begin(st[2*i]), end(st[2*i]),
        begin(st[2*i+1]), end(st[2*i+1]),
        back_inserter(st[i]));
  }

  while(q--) {
    int xl, yl, xr, yr;
    cin >> xl >> yl >> xr >> yr;
    auto l = lower_bound(begin(p), end(p), Point{xl, 0, 0}) - begin(p);
    auto r = upper_bound(begin(p), end(p), Point{xr, 0, 0}) - begin(p);
    vector<int> res;
    query(res, yl, yr, l, r-1, 1, 0, N-1);
    sort(begin(res), end(res));
    bool ok = false;
    for(int i=2; i<size(res); i++) {
      ok |= (res[i-2] + res[i-1] > res[i]);
    }
    cout << ok << nl;
  }
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
