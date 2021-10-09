#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

namespace Dinic {
  const int N = 204;
  const int M = N*N;
  int par[N], first[N], nxt[2*M], ep[2*M], m;
  ll flo[2*M], cap[2*M];
  void init() { m = 0; memset(first, -1, sizeof first); memset(flo, 0, sizeof flo); }
  void clear_flow() { memset(flo, 0, sizeof flo); }
  void add_edge(int a, int b, ll c=1) {
    nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, ++m;
    nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, ++m;
  }
  int L[N], cur[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L);
    queue<int> q; q.push(s), L[s] = 0;
    while (!q.empty()) { int u = q.front(); q.pop();
    for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e]) 
      if (L[v=ep[e^1]] == INF && flo[e] < cap[e]) 
        q.push(v), L[v] = L[u]+1;
    } return L[t] < INF;
  }
  ll dfs(int u, int t, ll f) {
    if (u == t) return f;
    ll cf, df = 0;
    for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
      if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
        cf = dfs(v, t, min(cap[e]-flo[e], f-df));
        flo[e] += cf; flo[e^1] -= cf; df += cf;
      } return df;
  }
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, m;
  cin >> n >> m;

  Dinic::init();

  int a, b;
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    Dinic::add_edge(a<<1|1, b<<1);
    Dinic::add_edge(b<<1|1, a<<1);
  }
  for (int i = 1; i <= n; i++) {
    Dinic::add_edge(i<<1, i<<1|1);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      Dinic::clear_flow();
      ll flow = 0;
      while (Dinic::bfs(i<<1|1, j<<1)) {
        flow += Dinic::dfs(i<<1|1, j<<1, INF);
      }

      if (flow < n/2) {
        cout << -1 << nl;
        return 0;
      }
    }
  }
  cout << 1 << nl;

  return 0;
}
