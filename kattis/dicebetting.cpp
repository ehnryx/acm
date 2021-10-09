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

ld logncr(int n, int r) {
  ld res = 0;
  for (int j=0; j<r; j++) {
    res += log(n-j) - log(j+1);
  }
  return res;
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

  int n, s, k;
  cin >> n >> s >> k;

  vector<ld> ans(s+1, 0);
  for (int i=1; i<=s; i++) {
    ans[i] = exp(logncr(s,i) + n*(log(i)-log(s)));
  }

  ld res = 1;
  for (int j=1; j<k; j++) {
    if (j%2==(k-1)%2) {
      res -= ans[j];
    } else {
      res += ans[j];
    }
  }
  cerr << res << nl;

  if (abs(res) > 1+EPS || res < -EPS) {
    cout << 1 << nl;
  } else {
    cout << res << nl;
  }

  return 0;
}
