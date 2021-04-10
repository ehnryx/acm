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

const int N = 2e5 + 1;
int adj[N];
bool vis[N];
vector<int> rev[N];

vector<int> get_cyc(int u) {
  vector<int> path;
  while(!vis[u]) {
    path.push_back(u);
    vis[u] = true;
    u = adj[u];
  }
  reverse(path.begin(), path.end());
  while(path.back() != u) {
    path.pop_back();
  }
  for(int i=(int)path.size()-1, j=0; j<path.size(); i=j++) {
    rev[path[i]].erase(find(rev[path[i]].begin(), rev[path[i]].end(), path[j]));
  }
  return path;
}

int get_depth(int u) {
  vis[u] = true;
  int res = 0;
  for(int v : rev[u]) {
    res = max(res, 1 + get_depth(v));
  }
  return res;
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

  int n;
  cin >> n;
  unordered_map<string,int> idx;
  unordered_map<string,vector<pair<int,string>>> nodes;
  for(int i=1; i<=n; i++) {
    string fam, nom, par, _;
    cin >> fam >> nom >> _ >> _ >> par;
    idx[fam + " " + nom] = i;
    nodes[fam].emplace_back(i, fam + " " + par);
  }

  int ans = 1;
  for(const auto& [_, vec] : nodes) {
    n = vec.size();
    for(const auto& [a, bs] : vec) {
      int b = (idx.count(bs) ? idx[bs] : a);
      adj[a] = b;
      rev[b].push_back(a);
    }
    for(const auto& [a, __] : vec) {
      if(vis[a]) continue;
      vector<int> cyc = get_cyc(a);
      for(int it : cyc) {
        ans = max(ans, get_depth(it) + (int)cyc.size());
      }
    }
  }
  cout << ans << nl;

  return 0;
}
