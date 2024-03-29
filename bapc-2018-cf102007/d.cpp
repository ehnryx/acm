#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Pair {
  int i, j;
};

const int N = 1e5;
int l[N], r[N], p[N], cnt[N];
unordered_map<int,int> vis[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, a, b;
  cin >> n >> a >> b;

  For(i,n) {
    cin >> l[i] >> r[i] >> p[i];
  }

  if (p[a]^p[b]) {
    cout << 0 << nl;
    return 0;
  }

  const int CAP = 17;
  int ans = INF;

  queue<Pair> bfs;
  bfs.push({a,b});
  vis[a][b] = 1;
  cnt[a]++;
  while (!bfs.empty()) {
    Pair c = bfs.front();
    bfs.pop();
    { // left
      int ni = l[c.i];
      int nj = l[c.j];
      if (ni != nj && !vis[ni].count(nj) && cnt[ni]<CAP) {
        if (p[ni]^p[nj]) {
          ans = min(ans, vis[c.i][c.j]);
          break;
        }
        vis[ni][nj] = vis[c.i][c.j]+1;
        bfs.push({ni,nj});
        cnt[ni]++;
      }
    }
    { // right
      int ni = r[c.i];
      int nj = r[c.j];
      if (ni != nj && !vis[ni].count(nj) && cnt[ni]<CAP) {
        if (p[ni]^p[nj]) {
          ans = min(ans, vis[c.i][c.j]);
          break;
        }
        vis[ni][nj] = vis[c.i][c.j]+1;
        bfs.push({ni,nj});
        cnt[ni]++;
      }
    }
  }

  memset(cnt, 0, sizeof cnt);
  while (!bfs.empty()) {
    bfs.pop();
  }
  For(i,n) {
    vis[i].clear();
  }
  swap(a,b);

  bfs.push({a,b});
  vis[a][b] = 1;
  cnt[a]++;
  while (!bfs.empty()) {
    Pair c = bfs.front();
    bfs.pop();
    { // left
      int ni = l[c.i];
      int nj = l[c.j];
      if (ni != nj && !vis[ni].count(nj) && cnt[ni]<CAP) {
        if (p[ni]^p[nj]) {
          ans = min(ans, vis[c.i][c.j]);
          break;
        }
        vis[ni][nj] = vis[c.i][c.j]+1;
        bfs.push({ni,nj});
        cnt[ni]++;
      }
    }
    { // right
      int ni = r[c.i];
      int nj = r[c.j];
      if (ni != nj && !vis[ni].count(nj) && cnt[ni]<CAP) {
        if (p[ni]^p[nj]) {
          ans = min(ans, vis[c.i][c.j]);
          break;
        }
        vis[ni][nj] = vis[c.i][c.j]+1;
        bfs.push({ni,nj});
        cnt[ni]++;
      }
    }
  }

  if (ans != INF) cout << ans << nl;
  else cout << "indistinguishable" << nl;

  return 0;
}
