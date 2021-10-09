#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int M = 1e9+7;
const int MAXN = 3e5+10;

vector<int> adj[MAXN];
int n, m, k;
ll fact[MAXN];
ll inv[MAXN];
ll powmod(ll p, ll b) {
  if (p==0) return 1;
  ll ans = powmod(p/2, b);
  ans = ans*ans%M;
  if (p%2==1) {
    ans = ans*b%M;
  }
  return ans;
}

ll ans = 0;

set<int> paths[MAXN];
vector<int> stupid[MAXN];

ll choose(int _n, int _k) {
  if (_k>_n) return 0;
  return fact[_n]*inv[_n-_k]%M*inv[_k]%M;
}

// a should contain answer
vector<int> merge(set<int> &a, set<int> &b) {
  vector<int> rem;
  if (a.size() < b.size()) swap(a, b);
  for(int i:b) {
    if (a.count(i)) rem.push_back(i);
    else a.insert(i);
  }
  b.clear();
  return rem;
}

void dfs(int u, int p = -1) {
  vector<int> toremove;
  for(int i: stupid[u]) toremove.push_back(i);
  stupid[u].clear();
  for(int v: adj[u]) {
    if (v==p) continue;
    dfs(v, u);
    for(int i: merge(paths[u], paths[v])) {
      toremove.push_back(i);
    }
  }
  //cerr << "@ " << u+1 <<endl;
  //for(int i:paths[u]) cerr << i << " "; cerr << endl;
  for(int i:toremove) {
    paths[u].erase(i);
    //cerr<< "@ " << u+1 << " removing " << i << " total " << paths[u].size() << " adding " << choose(paths[u].size(), k-1) << endl;
    ans = (ans + choose(paths[u].size(), k-1))%M;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  fact[0] = inv[0] = 1;
  for(int i=1;i<MAXN;i++) {
    fact[i] = fact[i-1]*i%M;
    inv[i] = powmod(M-2,fact[i]);
//    if (i<10) cerr << fact[i] << " " << inv[i] << " " << fact[i]*inv[i]%M <<endl;
  }
  int t;
  cin >> t;
  while(t--) {
    cin >> n >> m >> k;
    // reset
    ans = 0;
    for(int i=0;i<n;i++) {
      adj[i].clear();
      paths[i].clear();
      stupid[i].clear();
    }
    for(int i=0;i<n-1;i++) {
      int u, v; cin >> u >> v; u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    for(int i=0;i<m;i++) {
      int u, v; cin >> u >> v; u--, v--;
      paths[u].insert(i);
      paths[v].insert(i);
      if (u==v) stupid[u].push_back(i);
    }
    dfs(0);
    cout << ans <<endl;
  }

  return 0;
}
