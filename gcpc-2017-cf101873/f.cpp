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

const int N = 1500+1;
const int M = 1500+1;

vector<int> adjmat[M+2];

//To get vertex cover from matching:
//  - from all unmatched vertices, find all odd distance vertices on alternating
//    paths (dfs/bfs) and put all of those vertices in the cover
//  - for each matched edge that is not in the set above, assign one endpoint
//    arbitrarily to the cover.
//To get max indep. set from matching: Take the complement of the vertex cover.
struct Matching {
  bitset<N> seen; int matchL[M], matchR[N], m, n;
  Matching(int m = 0, int n = 0): m(m), n(n) {
    seen.reset();
    memset(matchL, -1, sizeof matchL);
    memset(matchR, -1, sizeof matchR);
  }

  bool bpm(int u) { // Can we find augmenting path starting from u
    for(int v : adjmat[u]) if(!seen[v]) { seen[v] = true;
    if(matchR[v] == -1 || bpm(matchR[v]) ) { matchL[u] = v, matchR[v] = u;
      return true; } }
    return false; 
  }
  int solve(int s = 1) {
    int cnt = 0;
    for (int i = s; i <= m; i++) {
      seen.reset();
      if (bpm(i)) cnt++;
    }
    return cnt;
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m, k, a, b;
  cin >> m >> n >> k;

  Matching orig(m,n);
  for (int i = 0; i < k; i++) {
    cin >> a >> b;
    adjmat[a].push_back(b);
  }

  int matches = orig.solve();
  int ans = matches;
  for (int i = 1; i <= m; i++) {
    Matching cur = orig;
    cur.m += 2;
    for (int j : adjmat[i]) {
      adjmat[m+1].push_back(j);
      adjmat[m+2].push_back(j);
    }
    ans = max(ans, matches + cur.solve(m+1));

    adjmat[m+1].clear();
    adjmat[m+2].clear();
  }

  cout << ans << nl;

  return 0;
}
