//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "kids"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 1000;

pair<int,int> operator + (const pair<int,int>& a, const pair<int,int>& b) {
  return make_pair(a.first + b.first, a.second + b.second);
}

struct Grid {
  vector<vector<bool>> g;
  int top, left;
  pair<int,int> shift(const Grid& o) const {
    return make_pair(top - o.top, left - o.left);
  }
  bool empty() const {
    return top < 0;
  }
};

Grid read_grid() {
  int n, m;
  cin >> n >> m;
  Grid out;
  bool assigned = false;
  out.g.resize(n + 2*M, vector<bool>(m + 2*M));
  for(int i=0; i<n; i++) {
    string line;
    cin >> line;
    for(int j=0; j<m; j++) {
      out.g[M + i][M + j] = (line[j] == '*');
      if(!assigned && out.g[M + i][M + j]) {
        tie(out.top, out.left) = make_pair(M + i, M + j);
        assigned = true;
      }
    }
  }
  return out;
}

Grid combine(const Grid& a, const Grid& b) {
  // shift b by b.(-top, -left) + a.(top, left)
  Grid out = a;
  bool assigned = false;
  for(int i=0; i<a.g.size(); i++) {
    for(int j=0; j<a.g[i].size(); j++) {
      int bi = i - a.top + b.top;
      int bj = j - a.left + b.left;
      if(0 <= bi && bi < b.g.size() && 0 <= bj && bj < b.g[0].size()) {
        out.g[i][j] = out.g[i][j] ^ b.g[bi][bj];
      }
      if(!assigned && out.g[i][j]) {
        tie(out.top, out.left) = make_pair(i, j);
        assigned = true;
      }
    }
  }
  if(!assigned) {
    out.top = out.left = -1;
  }
  return out;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  Grid a = read_grid();
  Grid b = read_grid();
  Grid c = read_grid();

  Grid ab = combine(a, b);
  Grid bc = combine(b, c);
  Grid ac = combine(a, c);

  if(!ab.empty() && combine(ab, c).empty()) {
    cout << "YES" << nl;
    auto [x, y] = a.shift(b);
    cout << y << " " << x << nl;
  } else if(!bc.empty() && combine(bc, a).empty()) {
    cout << "YES" << nl;
    auto [x, y] = a.shift(bc);
    cout << y << " " << x << nl;
  } else if(!ac.empty() && combine(ac, b).empty()) {
    cout << "YES" << nl;
    auto [x, y] = ac.shift(b);
    cout << y << " " << x << nl;
  } else {
    cout << "NO" << nl;
  }

  return 0;
}
