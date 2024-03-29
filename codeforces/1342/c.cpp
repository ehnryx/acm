//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    int a, b, q;
    cin >> a >> b >> q;
    int m = a*b;
    vector<int> sum(m+1);
    for(int i=0; i<m; i++) {
      sum[i+1] = (i % a % b != i % b % a);
    }
    partial_sum(sum.begin(), sum.end(), sum.begin());

    function<ll(ll)> query = [=](ll r) {
      ll cnt = r / m;
      return cnt * sum[m] + sum[r%m + 1];
    };

    for(int i=0; i<q; i++) {
      ll l, r;
      cin >> l >> r;
      cout << query(r) - query(l-1) << " ";
    }
    cout << nl;
  }

  return 0;
}
