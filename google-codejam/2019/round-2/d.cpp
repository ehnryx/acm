#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; 
  return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
  return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

const int N = 1e5+1;
vector<int> adj[N], rev[N];
int cyc[N], esz[N], vsz[N], deg[N];
ll dp[N];

void caseinit(int n) {
  for (int i=1; i<=n; i++) {
    adj[i].clear();
    rev[i].clear();
    cyc[i] = 0;
    esz[i] = 0;
    vsz[i] = 0;
  }
}

int low[N],vis[N],scomp[N],scompNum,I;
stack<int> verts;
void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
  for (int v : adj[u]) {
    if (!vis[v]) scc(v);
    if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
  if (vis[u] <= low[u]) { int v;
    do { v=verts.top(); verts.pop(); scomp[v]=scompNum; } while (v != u);
    ++scompNum; }
}
void get_scc(int n) { memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
  scompNum=I=0; for (int i=1; i<=n; ++i) if (!vis[i]) scc(i);
}

bool findpos(int u) {
  if (dp[u]) return true;
  vis[u] = true;
  for (int v : rev[u]) {
    if (!vis[v] && findpos(v)) return true;
  }
  return false;
}

bool solve(int u, int s) {
  if (scomp[u] != scomp[s] && esz[scomp[u]] >= vsz[scomp[u]]) {
    if (findpos(u)) return true;
  }
  vis[u] = true;
  for (int v : rev[u]) {
    if (!vis[v] && solve(v, s)) {
      return true;
    }
  }
  return false;
}

void solve() {
  int n;
  cin >> n;

  caseinit(n);

  memset(deg, 0, sizeof deg);
  for (int i=1; i<=n; i++) {
    int a, b;
    cin >> a >> b;
    adj[i].push_back(a);
    adj[i].push_back(b);
    rev[a].push_back(i);
    rev[b].push_back(i);
    deg[a]++;
    deg[b]++;
  }

  for (int i=1; i<=n; i++) {
    cin >> dp[i];
  }

  get_scc(n);
  for (int i=1; i<=n; i++) {
    vsz[scomp[i]]++;
    for (int j : adj[i]) {
      if (scomp[i] == scomp[j]) {
        esz[scomp[i]]++;
      }
    }
  }

  int vs = vsz[scomp[1]];
  int es = esz[scomp[1]];
  if (es > vs) {
    memset(vis, 0, sizeof vis);
    if (findpos(1)) {
      cout << "UNBOUNDED" << nl;
      return;
    } else {
      cout << 0 << nl;
      return;
    }
  } else {
    for (int i=1; i<=n; i++) {
      if (vsz[scomp[i]] <= esz[scomp[i]]) {
        for (int j : adj[i]) {
          if (scomp[j] != scomp[i]) {
            deg[j] -= 1;
          }
        }
      }
    }
    queue<int> bfs;
    for (int i=1; i<=n; i++) {
      if (deg[i] == 0) {
        bfs.push(i);
      }
    }
    while (!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();
      for (int v : adj[u]) {
        dp[v] = (dp[v] + dp[u]) % MOD;
        deg[v]--;
        if (deg[v] == 0) {
          bfs.push(v);
        }
      }
    }

    ll ans = 0;
    memset(vis, 0, sizeof vis);
    if (solve(1,1)) {
      cout << "UNBOUNDED" << nl;
      return;
    }
    for (int i=1; i<=n; i++) {
      if (scomp[i] == scomp[1]) {
        ans += dp[i];
      }
    }
    cout << ans % MOD << nl;
    return;
  }

  return;
}

