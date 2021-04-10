//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "expect"

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



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  vector<int> v(n+1), t(n+1);
  for(int i=1; i<=n; i++) {
    char c;
    cin >> c >> t[i] >> v[i];
    if(c == '+') {
      v[i] = -v[i];
    }
  }
  partial_sum(v.begin(), v.end(), v.begin());
  adjacent_difference(t.begin(), t.end(), t.begin());
  rotate(t.begin(), t.begin() + 1, t.end());

  int need = v.back();
  ll ans = 0;
  ll sum = 0;
  vector<pair<int,int>> rem;
  for(int i=1; i<n; i++) {
    v[i] = max(0, v[i] - need);
    ans += (ll) v[i] * t[i];
    if(v[i] > 0) {
      rem.emplace_back(v[i], t[i]);
      sum += t[i];
    }
  }
  sort(rem.begin(), rem.end(), greater<pair<int,int>>());

  vector<pair<int,int>> query;
  vector<ll> out(m);
  for(int i=0; i<m; i++) {
    int j;
    cin >> j;
    query.emplace_back(j - need, i);
  }
  sort(query.begin(), query.end());

  int have = 0;
  for(auto [j, i] : query) {
    if(j < have) {
      out[i] = -1;
    } else {
      while(!rem.empty() && rem.back().first < j) {
        sum -= rem.back().second;
        ans -= (ll) (rem.back().first - have) * rem.back().second;
        //cerr << "rem " << rem.back().first << " " << rem.back().second << nl;
        rem.pop_back();
      }
      ans -= (j - have) * sum;
      //cerr << "sub " << (j - have) << " * " << sum << nl;
      out[i] = ans;
      have = j;
    }
  }

  for(int i=0; i<m; i++) {
    if(out[i] == -1) cout << "INFINITY" << nl;
    else cout << out[i] << nl;
  }

  return 0;
}
