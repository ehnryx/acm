#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef pair<int,int> pii;

const int N = 1e5+1;
const int M = 1e5+1;

namespace BCC {
  int vcompNum, ecompNum, I, m;
  int first[N], low[N], vis[N], ecomp[N];
  int nxt[2*M], ep[2*M], vcomp[2*M];
  stack<int> edges, verts;
  void init() { m=0; memset(first, -1, sizeof first); }
  void add_edge(int a, int b) {
    nxt[m] = first[ep[m]=a], first[ep[m]] = m; ++m;
    nxt[m] = first[ep[m]=b], first[ep[m]] = m; ++m;
  }
  void biconnected(int u, int par) { int v,E; low[u] = vis[u] = ++I; verts.push(u);
    for (int e=first[u]; e!=-1; e=nxt[e]) { v=ep[e^1];
      if (!vis[v]) { edges.push(e); biconnected(v,e); low[u] = min(low[u],low[v]);
        if (vis[u] <= low[v]) {
          do { E = edges.top(); edges.pop(); vcomp[E] = vcomp[E^1] = vcompNum; }
          while (e != E && e != (E^1)); ++vcompNum;
        }
      }
      else if (vis[v] < vis[u] && e != (par^1)) {
        low[u] = min(low[u], vis[v]); edges.push(e); }
      else if (v == u) vcomp[e] = vcomp[e^1] = vcompNum++;
    }
    if (vis[u] <= low[u]) {
      do { v=verts.top(); verts.pop(); ecomp[v] = ecompNum; }
      while (v != u); ++ecompNum;
    }
  }
  void get_bcc(int n) {
    memset(vis, 0, sizeof vis); vcompNum=ecompNum=I=0;
    for (int i=1; i<=n; i++) if (!vis[i]) biconnected(i,-1);
  }
  bool isCutVertex(int u) {
    for (int e=first[u]; e!=-1; e=nxt[e]) if (vcomp[e] != vcomp[first[u]]) return true;
    return false;
  }
  bool isCutEdge(int e) { return ecomp[ep[e]] != ecomp[ep[e^1]]; }
}

int cutv[N], cute[N];
unordered_set<int> subg[N], arts[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  for (int n, tt=1; cin >> n && n; tt++) {
    BCC::init();

    int maxv = 0;
    for (int i=0; i<n; i++) {
      int a, b;
      cin >> a >> b;
      BCC::add_edge(a,b);
      maxv = max(maxv, max(a,b));

      arts[i].clear();
      subg[i].clear();
    }

    cout << "Case " << tt << ": ";
    {
      using namespace BCC;
      get_bcc(maxv);

      if (vcompNum == 1) {
        cout << 2 << " " << (ll)maxv*(maxv-1)/2 << nl;
      }

      else {
        for (int i=1; i<=2*n; i++) {
          cutv[i] = isCutVertex(i);
        }
        for (int i=0; i<n; i++) {
          int e = 2*i;
          cute[i] = isCutEdge(e);
          subg[vcomp[e]].insert(ep[e]);
          subg[vcomp[e]].insert(ep[e^1]);
          if (cutv[ep[e]]) arts[vcomp[e]].insert(ep[e]);
          if (cutv[ep[e^1]]) arts[vcomp[e]].insert(ep[e^1]);
        }

        int leaf = 0;
        ll ans = 1;
        for (int i=0; i<vcompNum; i++) {
          assert(!arts[i].empty());
          if (arts[i].size() == 1) {
            leaf++;
            if (subg[i].size() > 2) {
              ans *= subg[i].size()-1;
            }
          }
        }
        cout << leaf << " " << ans << nl;
      }
    }
  }

  return 0;
}
