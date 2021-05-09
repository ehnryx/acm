#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int modpow(int n, int e, int m) {
  if(n == 0) return 0;
  int r = 1;
  for(; e; e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  }
  return r;
}

const int N = 1 << 17;
const int K = 30;
vector<int> st[2*N];
vector<int> lazy[2*N], identity;

int add(int a, int b, int m) {
  return a+b < m ? a+b : a+b-m;
}

int calc_sum(int mod, int i, int k) {
  int res = 0;
  for(int j=0; j<mod; j++) {
    if(st[i][j] == 0) continue;
    res = (res + st[i][j] * modpow(j, k, mod)) % mod;
  }
  return res;
}

int calc_prod(int mod, int i) {
  int res = 1;
  for(int j=0; j<mod; j++) {
    if(st[i][j] == 0) continue;
    res = res * modpow(j, st[i][j], mod) % mod;
  }
  return res;
}

void put(int i, int v) {
  i += N;
  st[i][v] = 1;
  for(i/=2; i; i/=2) {
    st[i][v] += 1;
  }
}

void apply(int mod, int i, const vector<int>& f) {
  vector<int> nst(mod);
  for(int j=0; j<mod; j++) {
    nst[f[j]] += st[i][j];
    lazy[i][j] = f[lazy[i][j]];
  }
  st[i] = move(nst);
}

void push(int mod, int i) {
  if(lazy[i] == identity) return;
  apply(mod, 2*i, lazy[i]);
  apply(mod, 2*i+1, lazy[i]);
  lazy[i] = identity;
}

void pull(int mod, int i) {
  for(int j=0; j<mod; j++) {
    st[i][j] = st[2*i][j] + st[2*i+1][j];
  }
}

void update(int mod, int l, int r, const vector<int>& f, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    apply(mod, i, f);
    return;
  }
  push(mod, i);
  int m = (s+e) / 2;
  update(mod, l, r, f, 2*i, s, m);
  update(mod, l, r, f, 2*i+1, m+1, e);
  pull(mod, i);
}

int query_sum(int mod, int l, int r, int k, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return 0;
  if(l<=s && e<=r) {
    return calc_sum(mod, i, k);
  }
  push(mod, i);
  int m = (s+e) / 2;
  return add(query_sum(mod, l, r, k, 2*i, s, m), query_sum(mod, l, r, k, 2*i+1, m+1, e), mod);
}

int query_prod(int mod, int l, int r, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return 1;
  if(l<=s && e<=r) {
    return calc_prod(mod, i);
  }
  push(mod, i);
  int m = (s+e) / 2;
  return query_prod(mod, l, r, 2*i, s, m) * query_prod(mod, l, r, 2*i+1, m+1, e) % mod;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, p;
  cin >> n >> p;

  identity.resize(p);
  iota(begin(identity), end(identity), 0);
  fill(begin(lazy), end(lazy), identity);
  fill(begin(st), end(st), vector<int>(p));

  for(int i=1; i<=n; i++) {
    int a;
    cin >> a;
    put(i, a % p);
  }

  //cerr << "init: "; for(int i=1; i<=n; i++) {
  //cerr << query_sum(p, i, i, 1) << " "; } cerr << nl;

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int t, l, r, k;
    cin >> t >> l >> r >> k;
    if(t == 1) {
      k %= p;
      vector<int> f(p);
      for(int j=0; j<p; j++) {
        f[j] = add(j, k, p);
      }
      update(p, l, r, f);
    } else if(t == 2) {
      k %= p;
      vector<int> f(p);
      for(int j=0; j<p; j++) {
        f[j] = j * k % p;
      }
      update(p, l, r, f);
    } else if(t == 3) {
      vector<int> f(p, 1);
      if(k > 0) {
        for(int j=0; j<p; j++) {
          f[j] = modpow(j, k, p);
        }
      }
      update(p, l, r, f);
    } else if(t == 4) {
      if(k == 0) {
        cout << (r - l + 1) % p << nl;
      } else {
        cout << query_sum(p, l, r, k) << nl;
      }
    } else { // t == 5
      cout << query_prod(p, l, r) << nl;
    }
    //cerr << "after " << i << ": "; for(int j=1; j<=n; j++) {
    //cerr << query_sum(p, j, j, 1) << " "; } cerr << nl;
  }

  return 0;
}
