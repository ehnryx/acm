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

const ld PI = acos(-1.L);

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  complex<ld> unity = exp(complex<ld>(0, 2*PI/m));
  complex<ld> root[m];
  root[0] = 1;
  for (int k = 1; k < m; k++) {
    root[k] = root[k-1] * unity;
  }

  complex<ld> gf[n+1][m];
  for (int k = 0; k < m; k++) {
    gf[0][k] = 0;
  }

  int v;
  for (int i = 1; i <= n; i++) {
    cin >> v;
    v %= m;
    for (int k = 0; k < m; k++) {
      gf[i][k] = gf[0][k] * (1 + root[(k*v)%m]);
    }
  }

  return 0;
}
