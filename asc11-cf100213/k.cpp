//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "swimming"

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

int get_perim(int a, int b, int x, int y) {
  return 2 * (abs(a-x) + abs(b-y));
}

ll get_volume(int a, int b, int x, int y, int d) {
  return (ll) abs(a-x) * abs(b-y) * d;
}

int get_overlap(int a, int as, int at, int b, int bs, int bt) {
  if(a != b) return 0;
  assert(as < at && bs < bt);
  return max(0, min(at, bt) - max(as, bs));
}

int get_length(int a, int b, int x, int y, int c, int d, int z, int w) {
  int res = 0;
  for(int ax : {a, x}) {
    for(int cz : {c, z}) {
      res += get_overlap(ax, b, y, cz, d, w);
    }
  }
  for(int by : {b, y}) {
    for(int dw : {d, w}) {
      res += get_overlap(by, a, x, dw, c, z);
    }
  }
  return res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, x, y, p, s; // p = source, s = speed
  cin >> n >> x >> y >> p >> s;
  s *= 1000;

  vector<tuple<int,int,int,int>> rects;
  vector<int> depth(n+1);
  rects.emplace_back(0, 0, x * 100, y * 100);
  depth[0] = INF;
  for(int i=1; i<=n; i++) {
    int ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by >> depth[i];
    rects.emplace_back(ax * 100, ay * 100, bx * 100, by * 100);
  }

  vector<vector<pair<int,int>>> adj(n+1);
  vector<int> perim(n+1);
  vector<ld> volume(n+1);
  for(int i=0; i<=n; i++) {
    perim[i] = apply(get_perim, rects[i]);
    volume[i] = apply(get_volume, tuple_cat(rects[i], tie(depth[i])));
    for(int j=0; j<i; j++) {
      int length = apply(get_length, tuple_cat(rects[i], rects[j]));
      if(length) {
        adj[i].emplace_back(j, length);
        adj[j].emplace_back(i, length);
      }
    }
  }

  vector<int> dsu(n+1, -1);

  function<int(int)> find = [&](int i) -> int {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };

  function<void(int,int)> link = [&](int i, int j) -> void {
    i = find(i);
    j = find(j);
    if(i == j) return;
    int overlap = 0;
    for(int k=0; k<=n; k++) {
      if(find(k) != i) continue;
      overlap += apply(get_length, tuple_cat(rects[k], rects[j]));
    }
    perim[i] = perim[i] + perim[j] - 2*overlap;
    dsu[j] = i;
  };

  vector<bool> vis(n+1);
  vector<ld> inflow(n+1);
  vector<ld> event(n+1, INF);
  inflow[p] = s;
  event[p] = volume[p] / s;

  ld last = 0;
  for(int done=0; done<n; done++) {
    ld t = INF;
    int i = -1;
    for(int j=1; j<=n; j++) {
      if(!vis[j] && event[j] < t) {
        t = event[j];
        i = j;
      }
    }
    assert(i != -1);

    link(p, i);
    vis[i] = true;
    for(int j=0; j<=n; j++) {
      if(vis[j]) continue;
      volume[j] -= inflow[j] * (t - last);
      inflow[j] = 0;
      for(int k=0; k<=n; k++) {
        if(!vis[k]) continue;
        inflow[j] += apply(get_length, tuple_cat(rects[j], rects[k]));
      }
      inflow[j] *= (ld) s / perim[find(p)];
      event[j] = t + volume[j] / inflow[j];
    }
    last = t;
  }

  cout << last << nl;

  return 0;
}
