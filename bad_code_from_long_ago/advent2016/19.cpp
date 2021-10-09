#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

////////////////////////////////////////////////////////////////////////////////
// Josephus ring survivor (n: # of people, starting at 0, killing every m'th)
////////////////////////////////////////////////////////////////////////////////
const int MAXN = 6e6;
int survive[MAXN]; void josephus(int n, int m) {
  survive[1] = 0; for(int i = 2; i <= n; ++i) survive[i] = (m+survive[i-1])%i; }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n; cin >> n;
  josephus(n, 2);
  cout << survive[n]+1 << nl;

  return 0;
}
