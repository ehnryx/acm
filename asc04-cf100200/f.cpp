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

const int N = 1<<19;
int st[2*N];
int query(int l, int r) {
  int res = INF;
  for(l+=N, r+=N+1; l<r; l/=2, r/=2) {
    if(l&1) res = min(res, st[l++]);
    if(r&1) res = min(res, st[--r]);
  }
  return res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
  freopen("positive.in", "r", stdin);
  freopen("positive.out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<int> a(2*n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
    a[n+i] = a[i];
  }
  partial_sum(a.begin(), a.end(), a.begin());
  for(int i=0; i<2*n; i++) {
    st[N+i+1] = a[i];
  }
  for(int i=N-1; i>0; i--) {
    st[i] = min(st[2*i], st[2*i+1]);
  }

  int ans = 0;
  for(int i=0; i<n; i++) {
    int s = query(i, i);
    ans += (query(i+1, i+n) > s);
  }
  cout << ans << nl;

  return 0;
}
