//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5 + 1;
int wz[N], pre[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, p, d;
  cin >> n >> p >> d;
  string s;
  cin >> s;
  s += s;
  transform(s.begin(), s.end(), wz, [] (char c) {
    return (c == 'Z' ? 1 : 0);
  });
  partial_sum(wz, wz+2*n, pre+1);
  int ans = 0;
  for(int i=n+1; i<=2*n; i++) {
    ans += (pre[i] - pre[i-p] < d);
  }
  cout << ans << nl;

  return 0;
}
