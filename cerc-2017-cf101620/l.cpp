#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2018;
int ortho[2*N][2*N], diag[2*N][2*N];
bool paint[2*N][2*N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(2);

  int n;
  cin >> n;

  char type;
  int a, b, d;
  for (int i=0; i<n; i++) {
    cin >> type >> a >> b >> d;
    a += N; b += N;
    if (type == 'A') {
      ortho[a-d/2][b-d/2] = max(ortho[a-d/2][b-d/2], d);
    } else {
      diag[a-d/2][b] = max(diag[a-d/2][b], d/2);
    }
  }

  for (int i=1; i < 2*N-1; i++) {
    for (int j=1; j < 2*N-1; j++) {
      if (ortho[i][j]) {
        paint[i][j] = true;
        ortho[i+1][j] = max(ortho[i+1][j], ortho[i][j]-1);
        ortho[i][j+1] = max(ortho[i][j+1], ortho[i][j]-1);
        ortho[i+1][j+1] = max(ortho[i+1][j+1], ortho[i][j]-1);
      }
      if (diag[i][j]) {
        paint[i][j] = paint[i][j-1] = paint[i+1][j] = paint[i+1][j-1] = true;
        diag[i+1][j-1] = max(diag[i+1][j-1], diag[i][j]-1);
        diag[i+1][j+1] = max(diag[i+1][j+1], diag[i][j]-1);
        diag[i+2][j] = max(diag[i+2][j], diag[i][j]-1);
      }
    }
  }

  ld ans = 0;
  for (int i=1; i < 2*N-1; i++) {
    for (int j=1; j < 2*N-1; j++) {
      if (paint[i][j]) {
        if (ortho[i][j]) ans += 1;
        else if (diag[i][j] && diag[i-1][j+1]) ans += 1;
        else if (diag[i-1][j] && diag[i][j+1]) ans += 1;
        else if (diag[i][j] && diag[i-1][j]) ans += 0.75;
        else if (diag[i][j] && diag[i][j+1]) ans += 0.75;
        else if (diag[i-1][j+1] && diag[i-1][j]) ans += 0.75;
        else if (diag[i-1][j+1] && diag[i][j+1]) ans += 0.75;
        else ans += 0.5;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
