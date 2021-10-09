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
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
  return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



void init() {
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

const int N = 17;
char g[N][N];
int dp[N][N][N][N];

int solve(int a, int b, int n, int m) {
  if(a>n || b>m) return 0;
  if(dp[a][b][n][m] != -1) return dp[a][b][n][m];

  vector<int> vis;
  for(int i=a; i<=n; i++) {
    for(int j=b; j<=m; j++) {
      if(g[i][j] != '.') continue;
      bool ok = true;
      for(int k=a; k<=n && ok; k++) {
        ok &= (g[k][j] == '.');
      }
      if(ok) {
        vis.push_back(solve(a,b,n,j-1) ^ solve(a,j+1,n,m));
      }
      ok = true;
      for(int k=b; k<=m && ok; k++) {
        ok &= (g[i][k] == '.');
      }
      if(ok) {
        vis.push_back(solve(a,b,i-1,m) ^ solve(i+1,b,n,m));
      }
    }
  }

  sort(vis.begin(), vis.end());
  vis.resize(distance(vis.begin(), unique(vis.begin(), vis.end())));
  for(int i=0; i<vis.size(); i++) {
    if(vis[i] != i) {
      return dp[a][b][n][m] = i;
    }
  }
  return dp[a][b][n][m] = vis.size();
}

void caseinit() {
  memset(dp, -1, sizeof dp);
}

void casesolve() {
  caseinit();

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
    }
  }

  int ans = 0;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] != '.') continue;
      bool ok = true;
      for(int k=1; k<=n && ok; k++) {
        ok &= (g[k][j] == '.');
      }
      if(ok && (solve(1,1,n,j-1) ^ solve(1,j+1,n,m)) == 0) {
        ans++;
      }
      ok = true;
      for(int k=1; k<=m && ok; k++) {
        ok &= (g[i][k] == '.');
      }
      if(ok && (solve(1,1,i-1,m) ^ solve(i+1,1,n,m)) == 0) {
        ans++;
      }
    }
  }

  cout << ans << nl;

  return;
}

