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

int get(ll bm, int j) {
  return bm >> (4*j) & 0b1111;
}

int get_walk(ll bm, int j) {
  return bm >> (4*j) & 0b111;
}

ll put(ll bm, int j, int v) {
  return bm ^ (ll)(get(bm, j) ^ v) << (4*j);
}

ll put_walk(ll bm, int j, int v) {
  return bm ^ (ll)((get(bm, j) & 0b111) ^ v) << (4*j);
}

bool walkable(ll bm, int j) {
  return get(bm, j) > 1;
}

bool connected(ll bm, int j) {
  return walkable(bm, j) && (get(bm, j) < 0b1000 || get(bm, j) > 0b1100);
}

ll renumerate(int m, ll bm) {
  map<int,int> remap;
  for(int i=0, rid=0; i<m; i++) {
    if(walkable(bm, i) && !connected(bm, i)) {
      if(!remap.count(get(bm, i))) {
        remap[get(bm, i)] = rid++;
      }
    }
  }
  for(int i=0; i<m; i++) {
    if(remap.count(get(bm, i))) {
      bm = put(bm, i, remap[get(bm, i)] | 0b1000);
    }
  }
  return bm;
}

pair<ll,int> escalator(int m, int r, ll bm, int t) {
  int value = t;
  if(r > 0 && connected(bm, 0)) {
    value |= get_walk(bm, 0);
  }
  if(connected(bm, m-1)) {
    value |= get_walk(bm, m-1);
  }

  int cons = 0;
  if(r > 0 && walkable(bm, 0)) {
    cons |= 1 << get_walk(bm, 0);
  }
  if(walkable(bm, m-1)) {
    cons |= 1 << get_walk(bm, m-1);
  }

  for(int j=0; j<m; j++) {
    if(walkable(bm, j) && (cons & 1 << get_walk(bm, j))) {
      bm = put_walk(bm, j, value);
    }
  }
  bm = (bm << 4 | value) & ((1LL << (4*m)) - 1);
  bm = renumerate(m, bm);

  return pair(bm, 0);
}

pair<ll,int> hallway(int m, int r, ll bm) {
  int add = 0;
  add += (r > 0 && get(bm, 0) == 1);
  add += (get(bm, m-1) == 1);

  int value = 0;
  if(r > 0 && connected(bm, 0)) {
    value |= get_walk(bm, 0);
  }
  if(connected(bm, m-1)) {
    value |= get_walk(bm, m-1);
  }
  if(value == 0) {
    value = -1;
    if(r > 0 && walkable(bm, 0)) {
      value = get_walk(bm, 0);
    }
    if(walkable(bm, m-1)) {
      value = get_walk(bm, m-1);
    }
    if(value == -1) {
      value = 4; // ???
    }
  }

  int cons = 0;
  if(r > 0 && walkable(bm, 0)) {
    cons |= 1 << get_walk(bm, 0);
  }
  if(walkable(bm, m-1)) {
    cons |= 1 << get_walk(bm, m-1);
  }

  for(int j=0; j<m; j++) {
    if(walkable(bm, j) && (cons & 1 << get_walk(bm, j))) {
      bm = put_walk(bm, j, value);
    }
  }
  bm = (bm << 4 | value | 0b1000) & ((1LL << (4*m)) - 1);
  bm = renumerate(m, bm);

  return pair(bm, add);
}

pair<ll,int> pillar(int m, int r, ll bm, bool window) {
  if(walkable(bm, m-1) && get_walk(bm, m-1) != 7) {
    int cnt = 0;
    for(int j=0; j<m; j++) {
      if(walkable(bm, j)) {
        cnt += (get_walk(bm, j) == get_walk(bm, m-1));
      }
    }
    if(cnt == 1) {
      return pair(-1, 0);
    }
  }

  int add = 0;
  if(window) {
    add += (walkable(bm, m-1) && (get(bm, m-1) & 0b1000));
    add += (r > 0 && walkable(bm, 0) && (get(bm, 0) & 0b1000));
  }

  bm = (bm << 4 | window) & ((1LL << (4*m)) - 1);
  bm = renumerate(m, bm);

  return pair(bm, add);
}

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

  int n, m;
  cin >> n >> m;
  vector g(n, vector<char>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
    }
  }
  bool transpose = false;
  if(n < m) {
    transpose = true;
    vector ng(m, vector<char>(n));
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        ng[j][i] = g[i][j];
      }
    }
    g = move(ng);
    swap(n, m);
  }
  g.insert(begin(g), vector<char>(m, '#'));
  g.insert(end(g), vector<char>(m, '#'));

  // 1xxx = walkable
  //        0, 1, 2, 3, 4 -> connectivity
  //        5 -> escalator 1
  //        6 -> escalator 2
  //        7 -> both
  // 0110 = escalator 1
  // 0101 = escalator 2
  // 0111 = escalator something
  // 0000 = pillar
  // 0001 = shop

  vector<map<ll,int>> dp((n+2) * m);
  vector<map<ll,ll>> pre((n+2) * m);
  dp[m-1][0] = 0;
  for(int i=1; i<=n+1; i++) {
    for(int j=0; j<m; j++) {
      int u = i*m + j;
      for(auto [state, val] : dp[u-1]) {
        if(g[i][j] == 'U') {
          auto [bm, add] = escalator(m, j, state, 0b101);
          if(bm != -1) {
            dp[u][bm] = max(dp[u][bm], val + add);
            if(dp[u][bm] == val + add) {
              pre[u][bm] = state;
            }
          }
        } else if(g[i][j] == 'D') {
          auto [bm, add] = escalator(m, j, state, 0b110);
          if(bm != -1) {
            dp[u][bm] = max(dp[u][bm], val + add);
            if(dp[u][bm] == val + add) {
              pre[u][bm] = state;
            }
          }
        } else if(g[i][j] == '#') {
          auto [bm, add] = pillar(m, j, state, false);
          if(bm != -1) {
            dp[u][bm] = max(dp[u][bm], val + add);
            if(dp[u][bm] == val + add) {
              pre[u][bm] = state;
            }
          }
        } else { // g[i][j] == '.'
          // shop
          {
            auto [bm, add] = pillar(m, j, state, true);
            if(bm != -1) {
              dp[u][bm] = max(dp[u][bm], val + add);
              if(dp[u][bm] == val + add) {
                pre[u][bm] = state;
              }
            }
          }
          // hallway
          {
            auto [bm, add] = hallway(m, j, state);
            if(bm != -1) {
              dp[u][bm] = max(dp[u][bm], val + add);
              if(dp[u][bm] == val + add) {
                pre[u][bm] = state;
              }
            }
          }
        }
      }
    }
  }

  assert(dp[(n+2)*m - 1].count(0));
  cout << dp[(n+2)*m - 1][0] << nl;

  // reconstruction

  vector ans(n+2, vector<char>(m));
  function<char(int)> to_char = [](int v) {
    if(v == 0) assert(false);
    else if(v == 1) return 'S';
    else return '.';
  };

  ll bm = 0;
  for(int i=n+1; i>0; i--) {
    for(int j=m-1; j>=0; j--) {
      if(g[i][j] == '.') {
        ans[i][j] = to_char(bm & 0b1111);
      } else {
        ans[i][j] = g[i][j];
      }
      bm = pre[i*m + j][bm];
    }
  }

  cerr << dp[(n+2)*m - 1][0] << nl;
  if(transpose) {
    for(int j=0; j<m; j++) {
      for(int i=1; i<=n; i++) {
        cerr << ans[i][j];
      }
      cerr << nl;
    }
  } else {
    for(int i=1; i<=n; i++) {
      for(int j=0; j<m; j++) {
        cerr << ans[i][j];
      }
      cerr << nl;
    }
  }

  return 0;
}
