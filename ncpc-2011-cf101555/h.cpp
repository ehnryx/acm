// attempt 2
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

const int N = 12+1;
int val[N];
int taken[N];

int solve(int bm, const vector<int>& v) {
  memset(taken, 0, sizeof taken);
  for (int i = 1; i < N; i++) {
    if (bm & 1<<i) {
      taken[i] = i;
    }
  }

  for (int len : v) {
    bool bad = true;
    for (int i = 1; i < N; i++) {
      if (len <= i - taken[i]) {
        taken[i] += len+1;
        bm |= 1<<i;
        bad = false;
        break;
      }
    }

    if (bad) return INF;
  }

  return 31 - __builtin_clz(bm);
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

  int n;
  cin >> n;

  int bm = 0;
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> val[i];
    sum += (i+1)*val[i];
    if (val[i]) {
      bm |= 1<<i;
      val[i] -= 1;
    }
  }

  if (sum-12 > 78) {
    cout << "impossible" << nl;
    return 0;
  }

  int ans = INF;

  vector<int> perm;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < val[i]; j++) {
      perm.push_back(i);
    }
  }

  while (clock() < 0.984*CLOCKS_PER_SEC) {
    shuffle(perm.begin(), perm.end(), rng);
    ans = min(ans, solve(bm, perm));
  }

  if (ans <= 12) cout << ans << nl;
  else cout << "impossible" << nl;

  return 0;
}
