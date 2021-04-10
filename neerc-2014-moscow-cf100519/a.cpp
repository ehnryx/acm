//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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

const int N = 100 + 2;
int g[N][N];

vector<int> convert(const vector<int>& in, ll& res) {
  vector<int> v;
  bool match = false;
  for(int it : in) {
    if(!it) continue;
    if(match && it == v.back()) {
      v.back() += it;
      res += it;
      match = false;
    } else {
      v.push_back(it);
      match = true;
    }
  }
  return v;
}

const vector<pair<char,function<ll(int)>>> func = {
  make_pair('L', [](int n) {
    ll res = 0;
    for(int i=1; i<=n; i++) {
      vector<int> v;
      for(int j=1; j<=n; j++) {
        v.push_back(g[i][j]);
        g[i][j] = 0;
      }
      v = convert(v, res);
      for(int j=0; j<v.size(); j++) {
        g[i][j+1] = v[j];
      }
    }
    return res;
  }),

  make_pair('U', [](int n) {
    ll res = 0;
    for(int i=1; i<=n; i++) {
      vector<int> v;
      for(int j=1; j<=n; j++) {
        v.push_back(g[j][i]);
        g[j][i] = 0;
      }
      v = convert(v, res);
      for(int j=0; j<v.size(); j++) {
        g[j+1][i] = v[j];
      }
    }
    return res;
  }),

  make_pair('R', [](int n) {
    ll res = 0;
    for(int i=1; i<=n; i++) {
      vector<int> v;
      for(int j=n; j>0; j--) {
        v.push_back(g[i][j]);
        g[i][j] = 0;
      }
      v = convert(v, res);
      for(int j=0; j<v.size(); j++) {
        g[i][n-j] = v[j];
      }
    }
    return res;
  }),

  make_pair('D', [](int n) {
    ll res = 0;
    for(int i=1; i<=n; i++) {
      vector<int> v;
      for(int j=n; j>0; j--) {
        v.push_back(g[j][i]);
        g[j][i] = 0;
      }
      v = convert(v, res);
      for(int j=0; j<v.size(); j++) {
        g[n-j][i] = v[j];
      }
    }
    return res;
  }),

};

const map<char,function<ll(int)>> make_move(func.begin(), func.end());

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

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int v, x, y;
    cin >> v >> x >> y;
    g[x][y] = v;
  }

  int q;
  cin >> q;
  ll ans = 0;
  while(q--) {
    char t;
    cin >> t;
    ans += make_move.at(t)(n);
    int v, x, y;
    cin >> v >> x >> y;
    g[x][y] = v;
  }
  cout << 2*ans << nl;

  return 0;
}
