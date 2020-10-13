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

ll sqr(ll x) { return x*x; }

struct Point {
  int x, y, r;
  Point(int _x=0, int _y=0, int _r=0): x(_x), y(_y), r(_r) {}
  ll dist2(const Point& o) const {
    return sqr(x-o.x) + sqr(y-o.y);
  }
};

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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<Point> v;
    vector adj(n, vector<int>());
    for(int i=0; i<n; i++) {
      int x, y, r;
      cin >> x >> y >> r;
      v.emplace_back(x, y, r);
      for(int j=0; j<i; j++) {
        if(v[j].dist2(v[i]) == sqr(v[j].r + v[i].r)) {
          adj[i].push_back(j);
          adj[j].push_back(i);
        }
      }
    }

    vector<tuple<ll,ll,bool>> answer(n);
    queue<int> bfs;
    answer[0] = make_tuple(1, 1, 0);
    bfs.push(0);
    while(!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();
      auto [p, q, dir] = answer[u];
      for(int x : adj[u]) {
        if(get<0>(answer[x])) continue;
        // p/q * u.r/x.r
        ll np = p * v[u].r;
        ll nq = q * v[x].r;
        ll g = __gcd(np, nq);
        answer[x] = make_tuple(np/g, nq/g, !dir);
        bfs.push(x);
      }
    }

    for(auto [p, q, dir] : answer) {
      if(!p) {
        cout << "not moving" << nl;
        continue;
      }
      cout << p;
      if(q > 1) {
        cout << "/" << q;
      }
      if(dir) cout << " counterclockwise" << nl;
      else cout << " clockwise" << nl;
    }
  }

  return 0;
}
