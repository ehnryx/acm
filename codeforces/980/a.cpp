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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;

  int link, pearl;
  link = pearl = 0;
  for (char c : s) {
    if (c == '-') link++;
    else pearl++;
  }

  if (pearl == 0 || link % pearl == 0) cout << "YES" << nl;
  else cout << "NO" << nl;

  return 0;
}
