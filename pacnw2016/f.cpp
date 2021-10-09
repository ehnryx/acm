#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 4e3+7;

int low[N],vis[N],scomp[N],scompNum,I;
vector<int> adj[N]; stack<int> verts;
void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
  for (int v : adj[u]) {
    if (!vis[v]) scc(v);
    if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
  if (vis[u] <= low[u]) { int v;
    do { v=verts.top(); verts.pop(); scomp[v]=scompNum; } while (v != u);
    ++scompNum; }}
void get_scc(int n) { memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
  scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); }
bool truth[N/2]; // N must be at least 2 times the number of variables
void add_clause(int a, int b) { adj[a].push_back(b); }
bool two_sat(int n) { get_scc(n);
  for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return false;
    truth[i/2] = (scomp[i] < scomp[i^1]); } return true;
}


//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, r, m;
  cin >> n >> r >> m;

  int x, y;
  vector<pii> p;
  for (int i=0; i<m; i++) {
    cin >> x >> y;
    p.emplace_back(x,y);
  }

  for (int i=0; i<m; i++) {
    add_clause(2*i, 2*(m+i)+1);
    add_clause(2*(m+i), 2*i+1);
    add_clause(2*i+1, 2*(m+i));
    add_clause(2*(m+i)+1, 2*i);
    for (int j=0; j<i; j++) {
      if (p[i].first == p[j].first && abs(p[i].second-p[j].second) <= 2*r) {
        add_clause(2*i, 2*j+1);
        add_clause(2*j, 2*i+1);
      }
      if (p[i].second == p[j].second && abs(p[i].first-p[j].first) <= 2*r) {
        add_clause(2*(m+i), 2*(m+j)+1);
        add_clause(2*(m+j), 2*(m+i)+1);
      }
    }
  }

  if (two_sat(4*m)) {
    cout << "YES" << nl;
  } else {
    cout << "NO" << nl;
  }

  return 0;
}
