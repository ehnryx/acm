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

struct ST {
  vector<int> st;
  int n;
  ST(unsigned n_) {
    n = 1 << bit_width(n_);
    st.resize(2 * n);
  }
  void update(int l, int r, int c) {
    return update(l, r, c, 1, 0, n-1);
  }
  void update(int l, int r, int c, int i, int s, int e) {
    if(e<l || r<s) return;
    if(l<=s && e<=r) {
      st[i] = c;
      return;
    }
    push(i);
    int m = (s+e) / 2;
    update(l, r, c, 2*i, s, m);
    update(l, r, c, 2*i+1, m+1, e);
  }
  void push(int i) {
    if(st[i]) {
      st[2*i] = st[2*i+1] = st[i];
      st[i] = 0;
    }
  }
  void push_all() {
    for(int i=1; i<n; i++) {
      push(i);
    }
  }
  int operator[](int i) const {
    return st[i + n];
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<tuple<int, int, int, int, int>> rects;
  map<int, int> xremap, yremap;
  for(int i=0; i<n; i++) {
    int a, b, x, y, c;
    cin >> a >> b >> x >> y >> c;
    xremap[a];
    xremap[x];
    yremap[b];
    yremap[y];
    rects.emplace_back(min(a, x), min(b, y), max(a, x), max(b, y), c);
  }
  int xrid = 0;
  for(auto& it : xremap) {
    it.second = xrid++;
  }
  int yrid = 0;
  for(auto& it : yremap) {
    it.second = yrid++;
  }

  vector<ST> cols;
  for(int i=0; i<xrid-1; i++) {
    cols.emplace_back(yrid-1);
  }
  for(auto [a, b, x, y, c] : rects) {
    int l = yremap[b];
    int r = yremap[y] - 1;
    int xlim = xremap[x];
    for(int i=xremap[a]; i<xlim; i++) {
      cols[i].update(l, r, c);
    }
  }

  vector<int> all;
  for(auto& st : cols) {
    st.push_all();
    for(int i=0; i<yrid-1; i++) {
      if(st[i]) {
        all.push_back(st[i]);
      }
    }
  }
  sort(begin(all), end(all));
  cout << distance(begin(all), unique(begin(all), end(all))) << nl;
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
