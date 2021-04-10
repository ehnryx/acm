//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "mole"

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

const int N = 1 << 17;
pair<int,int> st[2*N];
int z[2*N];

void push(int i) {
  if(z[i]) {
    st[2*i].first += z[i];
    st[2*i+1].first += z[i];
    z[2*i] += z[i];
    z[2*i+1] += z[i];
    z[i] = 0;
  }
}

void pull(int i) {
  st[i] = min(st[2*i], st[2*i+1]);
}

void insert(int l, int r, int v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    st[i].first += v;
    z[i] += v;
    return;
  }
  push(i);
  int m = (s+e) / 2;
  insert(l, r, v, 2*i, s, m);
  insert(l, r, v, 2*i+1, m+1, e);
  pull(i);
}

pair<int,int> query(int l, int r, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return make_pair(INF, -1);
  if(l<=s && e<=r) return st[i];
  push(i);
  int m = (s+e) / 2;
  return min(query(l, r, 2*i, s, m), query(l, r, 2*i+1, m+1, e));
}

vector<int> adj[N];
int cap[N], flow[N];
int sz[N], start[N];

int sid = 0;
int build(int u) {
  start[u] = ++sid;
  sz[u] = 1;
  for(int v : adj[u]) {
    sz[u] += build(v);
  }
  return sz[u];
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

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    cin >> cap[i];
    if(i > 1) {
      adj[i/2].push_back(i);
    }
  }
  build(1);
  for(int i=1; i<=n; i++) {
    st[start[i] + N].second = i;
    if(cap[i]) {
      insert(start[i], start[i], 32 - __builtin_clz(i));
    } else {
      insert(start[i], start[i], INF);
    }
  }

  vector<int> out;
  int ans = 0;
  for(int i=0; i<m; i++) {
    int s;
    cin >> s;

    tuple<int,int,int> best(INF, -1, -1);
    int down = 0;
    for(int u=s; u; u/=2) {
      down += (flow[u] < 0 ? -1 : 1);
    }
    int cur = 0;
    for(int u=s; u; u/=2) {
      int l = start[u];
      int r = start[u] + sz[u] - 1;
      auto [depth, v] = query(l, r);
      if(v != -1) {
        int len = cur + depth - down;
        best = min(best, make_tuple(len, u, v));
      }
      cur += (flow[u] > 0 ? -1 : 1);
      down -= (flow[u] < 0 ? -1 : 1);
    }
    auto [len, c, t] = best;
    assert(c != -1 && t != -1);
    ans += len;
    out.push_back(ans);

    for(int u=s; u!=c; u/=2) {
      flow[u] -= 1;
      if(flow[u] == -1) {
        insert(start[u], start[u] + sz[u] - 1, -2);
      }
    }
    for(int u=t; u!=c; u/=2) {
      flow[u] += 1;
      if(flow[u] == 0) {
        insert(start[u], start[u] + sz[u] - 1, 2);
      }
    }

    if(--cap[t] == 0) {
      insert(start[t], start[t], INF);
    }
  }

  for(int it : out) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
