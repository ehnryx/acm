#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ ";
  for (const T& it : v) os << it << " ";
  os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ll ncr[31][31];
ll dp[31][901];
void init() {
  memset(dp, -1, sizeof dp);
  memset(ncr, 0, sizeof ncr);
  for (int n = 0; n <= 30; n++) {
    ncr[n][n] = ncr[n][0] = 1;
    for (int r = 1; r < n; r++) {
      ncr[n][r] = (ncr[n-1][r] + ncr[n-1][r-1]) % MOD;
    }
  }
}

ll solve(int n, int k) {
  if (n == 0)
    return k == 0;
  if (k < n) 
    return 0;
  if (dp[n][k] != -1)
    return dp[n][k];

  k -= n;
  ll res = 0;
  for (int left = 0; left < n; left++) {
    ll temp = 0;
    for (int lk = left; lk <= k - (n-1-left); lk++) {
      if (dp[left][lk] == 0) continue;
      if (dp[n-1-left][k-lk] == 0) continue;
      temp += solve(left, lk) * solve(n-1-left, k-lk) % MOD;
    }
    res = (res + ncr[n-1][left] * temp % MOD) % MOD;
  }
  return dp[n][k+n] = res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  init();

  int n, k;
  cin >> n >> k;
  if (k > 500) cout << 0 << nl;
  else cout << solve(n, k) << nl;

  return 0;
}
