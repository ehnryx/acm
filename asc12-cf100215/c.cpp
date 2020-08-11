//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "death"

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

const int N = 1<<17;
ll st[2*N];
bool z[2*N];

void push(int i) {
  if(z[i]) {
    st[2*i] = st[2*i+1] = st[i] / 2;
    z[2*i] = z[2*i+1] = true;
    z[i] = false;
  }
}

void pull(int i) {
  st[i] = st[2*i] + st[2*i+1];
}

ll query(int l, int r, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return 0;
  if(l<=s && e<=r) {
    return st[i];
  }
  push(i);
  int m = (s+e) / 2;
  return query(l, r, 2*i, s, m) + query(l, r, 2*i+1, m+1, e);
}

ll int_floor(ll, ll);
ll int_ceil(ll, ll);

void update(int l, int r, ll v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    st[i] = (ll) v * (e-s + 1);
    z[i] = true;
    return;
  }
  push(i);
  int m = (s+e) / 2;
  update(l, r, v, 2*i, s, m);
  update(l, r, v, 2*i+1, m+1 ,e);
  pull(i);
}

ll int_floor(ll n, ll d) {
  if(n >= 0) return n/d;
  return -int_ceil(-n, d);
}

ll int_ceil(ll n, ll d) {
  if(n >= 0) return (n+d-1) / d;
  return -int_floor(-n, d);
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

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    int v;
    cin >> v;
    update(i, i, v);
  }
  ll orig = query(1, n);

  for(int i=0; i<m; i++) {
    int l, r;
    cin >> l >> r;
    ll sum = query(1, n);
    ll avg = query(l, r);
    if(sum <= orig) {
      update(l, r, int_ceil(avg, r-l+1));
    } else {
      update(l, r, int_floor(avg, r-l+1));
    }
  }

  for(int i=1; i<=n; i++) {
    cout << query(i, i) << " ";
  }
  cout << nl;

  return 0;
}
