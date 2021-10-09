//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

namespace ET {
  const int N = 1<<20;
  vector<pair<int,int>> adj[N];
  vector<pair<int,int>>::iterator cur[N]; int eid, in[N];
  void init(int n=N) {
    eid = 0; for(int i=0; i<n; i++) { adj[i].clear(); in[i] = 0; }
  }
  void add_edge(int a, int b, bool bi) {
    if(bi) adj[b].emplace_back(a, eid); else in[b]++;
    adj[a].emplace_back(b, eid++);
  }
  bool is_bad(int u, bool bi) {
    return bi ? adj[u].size() % 2 : in[u] != adj[u].size();
  }
  vector<pair<int,int>> euler_tour(int r, bool bi, int n=N) {
    int bad = 0;
    for(int i=0; i<n && bad<=1; i++) if(i!=r) bad += is_bad(i, bi);
    if(bad > 1) return {};
    vector<bool> vis(eid); // only needed for undirected graphs
    for(int i=0; i<n; i++) cur[i] = adj[i].begin();
    vector<pair<int,int>> res; stack<pair<int,int>> stk;
    for(stk.emplace(r, -1); !stk.empty(); ) {
      int u = stk.top().first; auto end = adj[u].end(), &i = cur[u];
      while(i != end && vis[i->second]) i++;
      if(i != end) { stk.push(*i); vis[i->second] = true; }
      else { res.push_back(stk.top()); stk.pop(); }
    }
    if(res.size() != eid+1) return {};
    reverse(res.begin(), res.end());
    return res;
  }
}

bool solve(int n, int len, ll path) {
  ET::init(1<<(n-1));
  int mask = (1<<(n-1)) - 1;
  set<pair<int,int>> forbid;
  vector<pair<int,int>> have;
  for(int i=0; i<len-(n-1); i++) {
    int u = mask & path>>(i+1);
    int v = mask & path>>i;
    if(forbid.count(make_pair(u, v))) return false;
    forbid.insert(make_pair(u, v));
    have.emplace_back(u, -1);
  }
  reverse(have.begin(), have.end());

  for(int i=0; i<1<<(n-1); i++) {
    for(int t=0; t<2; t++) {
      int j = (i<<1 | t) & mask;
      if(forbid.count(make_pair(i, j))) continue;
      ET::add_edge(i, j, false);
    }
  }

  vector<pair<int,int>> res = ET::euler_tour(path & mask, false, 1<<(n-1));
  if(res.empty()) return false;
  res.insert(res.end(), have.begin()+1, have.end());

  for(auto [v, _] : res) {
    cout << (v&1 ? 'B' : 'A');
  }
  cout << nl;

  return true;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  string s, t;
  cin >> s >> t;
  function<char(char)> Ato0 = [](char c) { return c-'A'+'0'; };
  transform(s.begin(), s.end(), s.begin(), Ato0);
  transform(t.begin(), t.end(), t.begin(), Ato0);
  int a = stoi(s, 0, 2);
  int b = stoi(t, 0, 2);

  int mask = (1<<n) - 1;
  for(int shift=0; shift<=n; shift++) {
    if((a & mask>>shift) != b>>shift) continue;
    if(solve(n, n + shift, (ll)a << shift | b)) return 0;
  }

  for(int len=1; len<=2; len++) {
    for(int i=0; i<1<<len; i++) {
      if(solve(n, 2*n + len, (ll)a << (n+len) | b | i<<n)) return 0;
    }
  }

  for(int shift=2; shift>0; shift--) {
    if((b & mask>>shift) != a>>shift) continue;
    if(solve(n, n + shift, (ll)b << shift | a)) return 0;
  }

  assert(false);

  return 0;
}
