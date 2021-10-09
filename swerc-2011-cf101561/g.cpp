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

const int N = 1<<21;
int st[2*N];

void insert(int x, int v) {
  st[x+=N] = v;
  for(x/=2; x>0; x/=2) {
    st[x] = min(st[2*x], st[2*x+1]);
  }
}
int query(int l, int r) {
  int res = 2*INF;
  for(l+=N, r+=N; l<r; l/=2, r/=2) {
    if(l&1) res = min(res, st[l++]);
    if(r&1) res = min(res, st[--r]);
  }
  return res;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(int n; cin >> n && n; ) {
    vector<int> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }
    int sum = 0;
    for(int i=0; i<n; i++) {
      sum += a[i];
      insert(i, sum);
    }
    for(int i=0; i<n; i++) {
      sum += a[i];
      insert(i+n, sum);
    }

    int ans = 0;
    sum = 0;
    for(int i=0; i<n; i++) {
      ans += (query(i, i+n) >= sum);
      sum += a[i];
    }
    cout << ans << nl;
  }

  return 0;
}
