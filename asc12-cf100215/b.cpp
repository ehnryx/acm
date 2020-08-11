//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "choco"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 5e5;
const ld phi = (1 + sqrt((ld)5)) / 2;

bool check_gcd(int a, int b) {
  if(a == b) return true;
  if(a < b) swap(a, b);
  if(a - b > b) return false;
  return check_gcd(a-b, b);
}

int solve(int n) {
  int a = round(n / (1+phi));
  int l = max(1, a - M);
  int r = min(n-1, a + M);
  int best = 0;
  for(int i=l; i<=r; i++) {
    if(check_gcd(i, n-i)) {
      best = max(best, n - __gcd(i, n-i));
    }
  }
  return best;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  int m, n;
  cin >> m >> n;
  cout << max((ll) solve(m) * n, (ll)solve(n) * m) << nl;

  return 0;
}
