#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int M = 1e9+7;

const int MAXN = 1e5+210;
const int MAXT = 101;
int n, m, k, t;

int w[MAXN], c[MAXN];
vector<int> adj[MAXN];
vector<int> radj[MAXN];

int cnt[MAXN];

ll maxc[MAXN][MAXT];
ll inp[MAXN][MAXT];
ll outp[MAXN][MAXT];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> T;
  while(T--) {
    cin >> n >> m;
    for(int i=1;i<=n;i++) {
      cin >> w[i] >> c[i];
      cnt[i] = 0;
      adj[i].clear();
      radj[i].clear();
      good[i].clear();
      rgood[i].clear();
    }
    for(int i=0;i<m;i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      radj[v].push_back(u);
      cnt[v]++;
    }
    cin >> k >> t;
    queue<int> q;
    for(int i=1;i<=n;i++) {
      if (cnt[v]==0) q.push(i);
    }
    vector<int> topo;
    while(!q.empty()) {
      int u = q.front(); q.pop();
      topo.push_back(u);
      for(int v: adj[u]) {
        cnt[v]--;
        if (cnt[v]==0) q.push(v);
      }
    }
    reverse(topo.begin(), topo.end());
    for(int u: topo) {
      for(int kp=0;kp<k;kp++) {
        maxc[u][kp] = -INFLL;
        if (u==n && (kp+w[u])%k == t) maxc[u][kp] = 0;
        for(int v:adj[u]) {
          maxc[u][kp] = max(maxc[u][kp],maxc[v][(kp+w[u])%k]+c[u]);
        }
      }
    }

    for(int u:topo) {
      for(int kp=0;kp<k;kp++) {
        outp[u][kp] = 0;
        if (u==n && (kp+w[u])%k == t) outp[u][kp] = 1;
        for(int v:adj[u]) {
          if(maxc[u][kp] != maxc[v][(kp+w[u])%k]+c[u]) continue;
          outp[u][kp]=(outp[u][kp]+outp[v][(kp+w[u])%k])%M;
        }
      }
    }

    reverse(topo.begin(), topo.end());
    for(int v:topo) {
      for(int kp=0;kp<k;kp++) {
        inp[v][kp] = 0;
        if (v==1 && kp == 0) inp[v][kp] = 1;
        for(int u:radj[u]) {
          if(maxc[v][kp]+c[u] != maxc[u][(kp-w[u]+k)%k]) continue;
          inp[v][kp] = (inp[v][kp]+inp[u][(kp-w[u]+k)%k])%M;
        }
      }
    }
    cout << maxc[u][
  }

  return 0;
}
