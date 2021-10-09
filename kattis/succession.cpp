//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 500;
ld val[N];
int deg[N];
vector<int> adj[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  string init;
  cin >> init;

  unordered_map<string,int> idx;
  idx[init] = 0;
  val[0] = 1;
  int id = 0;
  for(int i=0; i<n; i++) {
    string a, b, c;
    cin >> a >> b >> c;
    if(!idx.count(a)) idx[a] = ++id;
    if(!idx.count(b)) idx[b] = ++id;
    if(!idx.count(c)) idx[c] = ++id;
    deg[idx[a]] = 2;
    adj[idx[b]].push_back(idx[a]);
    adj[idx[c]].push_back(idx[a]);
  }

  queue<int> bfs;
  for(int i=0; i<=id; i++) {
    if(deg[i] == 0) {
      bfs.push(i);
    }
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      val[v] += val[u] / 2;
      if(--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }

  ld best = -1;
  string res;
  for(int i=0; i<m; i++) {
    string s;
    cin >> s;
    ld cur = (idx.count(s) ? val[idx[s]] : 0);
    if(cur > best) {
      best = cur;
      res = s;
    }
  }
  cout << res << nl;

  return 0;
}
