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
const int P = sqrt(4e7)+1;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<int> ps;
void init() {
  vector<bool> isp(P, 1);
  for (int i = 2; i*i < P; i++) {
    if (isp[i]) {
      for (int j = i*i; j < P; j += i) {
        isp[j] = 0;
      }
    }
  }
  for (int i = 2; i < P; i++) {
    if (isp[i]) ps.push_back(i);
  }
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
  init();

  int sum = 0;
  for (int i:ps) {
    if (i>100) break;
    sum++;
  }
  cout << sum << nl;

  return 0;
}
