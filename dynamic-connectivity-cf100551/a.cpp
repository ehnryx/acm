#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

const int N = 1<<19;
int dsu[N], sz[N];
int ans[N];
bool down[2*N];
vector<pair<int,int>> edges[2*N];

int find(int i) {
  assert(i > 0);
  if(dsu[i] == 0) return i;
  return find(dsu[i]);
}

void add_range(int l, int r, pair<int,int> v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l || !down[i]) return;
  if(l<=s && e<=r) {
    edges[i].push_back(v);
    return;
  }
  int m = (s+e) / 2;
  add_range(l, r, v, 2*i, s, m);
  add_range(l, r, v, 2*i+1, m+1, e);
}

void add_flag(int x, int i=1, int s=0, int e=N-1) {
  down[i] = true;
  if(s == e) return;
  int m = (s+e) / 2;
  if(x <= m) add_flag(x, 2*i, s, m);
  else add_flag(x, 2*i+1, m+1, e);
}

void solve(int l, int r, int res, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l || !down[i]) return;
  vector<int> memo;
  for(auto [a, b] : edges[i]) {
    a = find(a);
    b = find(b);
    if(a != b) {
      if(sz[a] > sz[b]) swap(a, b);
      dsu[a] = b;
      memo.push_back(a);
      res -= 1;
    }
  }

  if(s == e) {
    ans[s] = res;
  } else {
    int m = (s+e) / 2;
    solve(l, r, res, 2*i, s, m);
    solve(l, r, res, 2*i+1, m+1, e);
  }

  for(int a : memo) {
    dsu[a] = 0;
  }
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
  freopen("connect.in", "r", stdin);
  freopen("connect.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  map<pair<int,int>,vector<int>> ev;
  vector<char> t(m);
  for(int i=0; i<m; i++) {
    cin >> t[i];
    if(t[i] == '?') {
      add_flag(i);
    } else {
      int a, b;
      cin >> a >> b;
      if(a > b) swap(a, b);
      ev[make_pair(a, b)].push_back(i);
    }
  }

  for(const auto& [e, v] : ev) {
    bool in = false;
    int pre = -1;
    for(int i : v) {
      if(in) {
        add_range(pre, i, e);
      }
      in ^= 1;
      pre = i;
    }
    if(in) {
      add_range(pre, m-1, e);
    }
  }
  solve(0, m-1, n);

  for(int i=0; i<m; i++) {
    if(t[i] == '?') {
      cout << ans[i] << nl;
    }
  }

  return 0;
}
