#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

const int N = 1<<18;
unsigned int segt[2*N][20];
unsigned int cur[20];
unsigned int res[20];

int m;
void combine(int i) {
  //cerr << "combine @ " << i << endl;
  //cerr << "cur: "; for (int j = 0; j < m; j++) //cerr << cur[j] << " "; //cerr << endl;
  //cerr << "seg: "; for (int j = 0; j < m; j++) //cerr << segt[i][j] << " "; //cerr << endl;
  memset(res, 0, sizeof res);
  for (int j = 0; j < m; j++) {
    res[j] = (res[j] + cur[j] + segt[i][j]) % MOD;
    for (int k = 0; k < m; k++) {
      res[(j+k)%m] = (res[(j+k)%m] + (ll) cur[j] * segt[i][k] % MOD) % MOD;
    }
  }
  //cerr << "get: ";
  for (int j = 0; j < m; j++) {
    cur[j] = res[j];
    //cerr << cur[j] << " ";
  }
  //cerr << endl;
}

int query(int l, int r) {
  memset(cur, 0, sizeof cur);
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l & 1) combine(l++);
    if (r & 1) combine(--r);
  }
  return (cur[0] + 1) % MOD;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n >> m;

  int a;
  for (int i = 0; i < n; i++) {
    cin >> a;
    a %= m;
    segt[N+i][a] = 1;
  }

  for (int i = N-1; i > 0; i--) {
    for (int j = 0; j < m; j++) {
      segt[i][j] = (segt[i][j] + segt[i<<1][j] + segt[i<<1|1][j]) % MOD;
      for (int k = 0; k < m; k++) {
        segt[i][(j+k)%m] = (segt[i][(j+k)%m] + (ll) segt[i<<1][j] * segt[i<<1|1][k] % MOD) % MOD;
      }
    }
  }

  int queries;
  cin >> queries;

  int left, right;
  for (int i = 0; i < queries; i++) {
    cin >> left >> right;
    cout << query(left-1, right) << nl;
  }

  return 0;
}
