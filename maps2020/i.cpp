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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5 + 1;
int cnt[N], in[N];

int low[N], vis[N], scomp[N], scompNum, I;
vector<int> adj[N]; stack<int> verts;
void scc(int u) {
  low[u] = vis[u] = ++I; verts.push(u);
  for(int v : adj[u]) {
    if(!vis[v]) scc(v);
    if(scomp[v] == -1) low[u] = min(low[u], low[v]);
  }
  if(vis[u] <= low[u]) {
    int v;
    do {
      v = verts.top(); verts.pop();
      scomp[v] = scompNum;
    } while(v != u);
    ++scompNum;
  }
}
void get_scc(int n) {
  memset(vis, 0, sizeof vis);
  memset(scomp, -1, sizeof scomp);
  scompNum = I = 0;
  for(int i=0; i<n; ++i) if(!vis[i]) scc(i);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }
  get_scc(n);

  for(int i=0; i<n; i++) {
    cnt[scomp[i]]++;
    for(int j : adj[i]) {
      if(scomp[i] == scomp[j]) continue;
      in[scomp[j]]++;
    }
  }

  ll ans = 0;
  int seen = 0;
  for(int i=0; i<scompNum; i++) {
    seen += cnt[i];
    ans += (ll)cnt[i] * (n-seen) - in[i];
  }
  cout << ans << nl;

  return 0;
}
