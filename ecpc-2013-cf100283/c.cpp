#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "treasures"

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

// MAGIC IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
// END MAGIC IO

const ll LB = 1e16;

const int N = 100+1;
int grid[N][N];
ll diag[2][4*N][4*N];

void fill(int s) {
  for (int i=1; i<4*N; i++) {
    for (int j=1; j<4*N; j++) {
      diag[s][i][j] += diag[s][i-1][j] + diag[s][i][j-1] - diag[s][i-1][j-1];
      if (abs(diag[s][i][j]) > LB) diag[s][i][j] %= MOD;
    }
  }
}

ll query(int s, int i, int j, int len) {
  ll res = diag[s][i+len][j+len] + diag[s][i-len-1][j-len-1]
      - diag[s][i+len][j-len-1] - diag[s][i-len-1][j+len];
  if (abs(res) > LB) res %= MOD;
  return res;
}

void print(int s) {
  cerr << "GRID: " << nl;
  for (int i=0; i<4*N; i++) {
    for (int j=0; j<4*N; j++) {
      cerr << diag[s][i][j] << " ";
    }
    cerr << nl;
  }
  cerr << nl;
}

void solve() {
  int n, m, s, x, y;
  //cin >> n >> m >> s >> x >> y;
  read(n); read(m); read(s); read(x); read(y);
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      //cin >> grid[i][j];
      read(grid[i][j]);
    }
  }

  memset(diag[s&1], 0, sizeof diag[s&1]);
  diag[s&1][x+y+N][x-y+N+N] = 1;
  fill(s&1);
  //print(s&1);
  while (--s) {
    memset(diag[s&1], 0, sizeof diag[s&1]);
    for (int i=1; i<=n; i++) {
      for (int j=1; j<=m; j++) {
        ll cur = query((s&1)^1, i+j+N, i-j+N+N, s);
        diag[s&1][i+j+N][i-j+N+N] = cur;
      }
    }
    fill(s&1);
    //print(s&1);
  }

  ll ans = 0;
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      ll cur = query(1, i+j+N, i-j+N+N, 0) % MOD;
      ans += cur*grid[i][j] % MOD;
      //cerr << i << " " << j << " -> " << (cur+MOD)%MOD << nl;
    }
  }
  cout << (ans%MOD + MOD) % MOD << nl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(TESTFILE ".in", "r", stdin);
#endif

  int T;
  //cin >> T;
  read(T);

  for (int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ": ";
    solve();
  }

  return 0;
}
