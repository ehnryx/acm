//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "brackets"

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

const int N = 2e5 + 1;
vector<int> adj[N];
int par[N];
char open[N], close[N];
int oid[N], cid[N];
bool ok[N];
pair<int,int> info[N];
vector<pair<int,int>> good;

bool solve(int u) {
  ok[u] = (open[u] == '(' && close[u] == ')') || (open[u] == '[' && close[u] == ']');
  for(int v : adj[u]) {
    ok[u] &= solve(v);
  }
  int len = cid[u] - oid[u] + 1;
  if(ok[u]) {
    info[u] = make_pair(oid[u], len);
  } else {
    for(int v : adj[u]) {
      if(ok[v]) {
        good.push_back(info[v]);
      }
    }
  }
  return ok[u];
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  string s;
  cin >> s;

  string t(s.size(), '{');
  s = t + s;

  int cur = 0;
  int id = 0;
  for(int i=0; i<s.size(); i++) {
    if(s[i] == '(' || s[i] == '[' || s[i] == '{') {
      adj[cur].push_back(++id);
      par[id] = cur;
      cur = id;
      open[cur] = s[i];
      oid[cur] = i;
    } else {
      close[cur] = s[i];
      cid[cur] = i;
      cur = par[cur];
    }
  }

  solve(0);
  pair<int,int> ans(0, 0);
  sort(good.begin(), good.end());
  for(int i=0; i<good.size(); i++) {
    if(i > 0 && good[i-1].first + good[i-1].second == good[i].first) {
      good[i].first = good[i-1].first;
      good[i].second += good[i-1].second;
    }
    if(good[i].second > ans.second) {
      ans = good[i];
    }
  }
  cout << s.substr(ans.first, ans.second) << nl;

  return 0;
}
