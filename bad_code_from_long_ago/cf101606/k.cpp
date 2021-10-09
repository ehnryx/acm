#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 308;
const int M = N*N+3;

int par[N], first[N], nxt[2*M], ep[2*M], m;
ll flo[2*M], cap[2*M], cost[2*M];
void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
  nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
  nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }

// Dinic's fast maximum flow: tested on NAIPC 2015 F but not theoretically
// proven to be floating-point-safe.
// USAGE: 1) init(); 2) add edges
// 3) ll flow=0; while (bfs(S, T)) flow += dfs(S, T, INF);
// V^2E in general, min(V^(2/3),sqrt(E))E on unit caps, sqrt(V)E on bipartite
int L[N], cur[N];
bool bfs(int s, int t) {
  memset(L, INF, sizeof L);
  queue<int> q; q.push(s); L[s] = 0;
  while (!q.empty()) { int u = q.front(); q.pop();
    for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
      if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
        q.push(v), L[v] = L[u]+1;
  } return L[t] < INF; }
ll dfs(int u, int t, ll f) {
  if (u == t) return f;
  ll cf, df = 0;
  for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
    if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
      cf = dfs(v, t, min(cap[e]-flo[e], f-df));
      flo[e] += cf; flo[e^1] -= cf; df += cf;
    } return df; }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;

  pii c[n];
  for (int i = 0; i < n; i++) {
    cin >> c[i].first >> c[i].second;
  }

  int k;
  cin >> k;
  int a[k];
  for (int i = 0; i < k; i++) {
    cin >> a[i];
  }

  int source = 2*n+k; 
  int sink = source + 1;

  init();

  for (int i = 0; i < n; i++) {
    add_edge(2*i, 2*i+1);
    if (c[i].first == 0) {
      add_edge(source, 2*i);
    }
    for (int j = 0; j < n; j++) {
      if (i != j) {
        if (c[j].first <= c[i].second) {
          add_edge(2*i+1, 2*j);
        }
      }
    }
    for (int j = 0; j < k; j++) {
      if (a[j] <= c[i].second) {
        add_edge(2*i+1, 2*n+j);
      }
    }
  }

  for (int i = 0; i < k; i++) {
    add_edge(2*n+i, sink);
  }

  int flow = 0;
  while (bfs(source, sink)) {
    flow += dfs(source, sink, INF);
  }

  if (flow == k) {
    vector<int> ans;
    for (int i = 0; i < k; i++) {
      ans.clear();
      int cur = 2*n+i;
      while (cur != source) {
        if (cur < 2*n && cur % 2 == 0) {
          ans.push_back(1 + cur/2);
        }
        for (int j = first[cur]; j != -1; j = nxt[j]) {
          if (flo[j] < 0) {
            flo[j]++;
            cur = ep[j^1];
            break;
          }
        }
      }

      for (int j = ans.size()-1; j >= 0; j--) {
        cout << ans[j] << " ";
      }
      cout << nl;
    }
  }
  else {
    cout << "impossible" << nl;
  }


  return 0;
}
