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

int solve(int s, const vector<int>& vals) {
  if (s == 0) return 0;
  ll v = 1;
  for (int it : vals) {
    if (v*it > s) break;
    v *= it;
  }
  int cnt = s/v;
  return cnt + solve(s-cnt*v, vals);
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

  int n, s, a;
  cin >> n >> s;

  vector<int> vals;
  for (int i = 0; i < n; i++) {
    cin >> a;
    vals.push_back(a);
  }
  cout << solve(s, vals) << nl;

  return 0;
}
