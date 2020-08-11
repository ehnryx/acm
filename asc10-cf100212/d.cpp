//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "divisors"

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

vector<int> p = {
  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 49, 51, 53, 57,
};

pair<ll,int> solve(ll n, ll cur, int last, int i) {
  ll res = 1;
  int best = 1;
  for(int j=1; j<=last; j++) {
    ll f = llround(powl(p[i], j));
    ll nxt = cur * f;
    if(nxt > n) break;
    auto [val, cnt] = solve(n, nxt, j, i+1);
    if(cnt * (j+1) > best) {
      best = cnt * (j+1);
      res = val * f;
    } else if(cnt * (j+1) == best && val * f < res) {
      res = val * f;
    }
  }
  return make_pair(res, best);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  ll n;
  cin >> n;
  auto [ans, cnt] = solve(n, 1, INF, 0);
  cout << ans << nl;

	return 0;
}
