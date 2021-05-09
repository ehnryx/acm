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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Item {
  int i, j; ll d;
  Item() = default;
  Item(int _i, int _j, ll _d): i(_i), j(_j), d(_d) {}
  bool operator < (const Item& o) const {
    return d > o.d;
  }
};

const vector<pair<int,int>> transitions = {
  {0, 1}, {0, -1}, {1, 0}, {-1, 0},
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m, xs, ys, xt, yt;
  cin >> n >> m >> xs >> ys >> xt >> yt;
  vector a(n, vector<int>(m));
  vector b(n, vector<int>(m));
  vector c(n, vector<int>(m));
  vector w(n, vector<int>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[i][j];
    }
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> b[i][j];
    }
  }
  for(int i=0; i<n; i++) {
    for(int j=1; j<m; j++) {
      cin >> c[i][j];
    }
  }
  for(int i=1; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> w[i][j];
    }
  }

  vector dist(n, vector<ll>(m, -1));
  priority_queue<Item> dijk;
  dijk.emplace(xs - 1, ys - 1, 0);
  while(!empty(dijk)) {
    auto [i, j, d] = dijk.top();
    dijk.pop();
    if(dist[i][j] != -1) continue;
    dist[i][j] = d;
    for(auto [di, dj] : transitions) {
      if(i+di < 0 || n <= i+di || j+dj < 0 || m <= j+dj) continue;
      if(dist[i+di][j+dj] != -1) continue;
      ll t = d;
      if(di == 0) {
        ll rem = d % (a[i][j] + b[i][j]);
        if(rem < a[i][j]) {
          t += a[i][j] - rem;
        }
        t += c[i][max(j,j+dj)];
      } else {
        ll rem = d % (a[i][j] + b[i][j]);
        if(a[i][j] <= rem) {
          t += a[i][j] + b[i][j] - rem;
        }
        t += w[max(i,i+di)][j];
      }
      dijk.emplace(i+di, j+dj, t);
    }
  }

  cout << dist[xt - 1][yt - 1] << nl;

  return 0;
}
