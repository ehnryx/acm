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
constexpr ll INF = 1e12;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1 << 20;
ll st[2*N], ust[2*N];

ll find(ll x, int r, int i=1, int s=0, int e=N-1) {
  if(r < s || !ust[i] || st[e + N] < x) return INF;
  if(s == e) return ust[i];
  int m = (s+e) / 2;
  ll res = find(x, r, 2*i, s, m);
  if(res == INF) res = find(x, r, 2*i+1, m+1, e);
  return res;
}

bool pay(ll x, int r, int i=1, int s=0, int e=N-1) {
  if(r < s || !ust[i] || st[e + N] < x) return false;
  if(s == e) {
    ust[i] = 0; // no more unpaid
    return true;
  }
  int m = (s+e) / 2;
  bool res = pay(x, r, 2*i, s, m);
  if(!res) res = pay(x, r, 2*i+1, m+1, e);
  ust[i] = ust[2*i] + ust[2*i+1];
  return res;
}

ll query(ll x, int r, int i=1, int s=0, int e=N-1) {
  if(r < s || x < st[s + N]) return 0;
  if(e <= r && st[e + N] <= x) return ust[i];
  assert(s != e);
  int m = (s+e) / 2;
  return query(x, r, 2*i, s, m) + query(x, r, 2*i+1, m+1, e);
}

void undo(ll x, int r, int i=1, int s=0, int e=N-1) {
  if(r < s || x < st[s + N] || ust[i] == st[i]) return;
  if(s == e) {
    ust[i] = st[i];
    return;
  }
  int m = (s+e) / 2;
  undo(x, r, 2*i, s, m);
  undo(x, r, 2*i+1, m+1, e);
  ust[i] = ust[2*i] + ust[2*i+1];
}


unsigned long long k1, k2;

unsigned long long xorShift128Plus() {
  unsigned long long k3 = k1, k4 = k2;
  k1 = k4;
  k3 ^= k3 << 23;
  k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
  return k2 + k4;
}

void gen(int n) {
  cin >> k1 >> k2;
  for (int i = 0; i < n; i++) {
    st[i + N] = xorShift128Plus() % 999999999999 + 1;
  }
  sort(st + N, st + N + n);
  for(int i=N-1; i>0; i--) {
    st[i] = st[2*i] + st[2*i+1];
  }
  copy(begin(st), end(st), begin(ust));
  for(int i=n; i<N; i++) {
    st[i + N] = INF;
  }
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

  int n;
  cin >> n;
  gen(n);
  int T;
  cin >> T;
  while(T--) {
    char t; ll x;
    cin >> t >> x;
    if(t == 'F') {
      cout << find(x, n-1) << nl;
    } else if(t == 'D') {
      pay(x, n-1);
    } else if(t == 'C') {
      cout << query(x, n-1) << nl;
    } else { // t == 'R'
      undo(x, n-1);
    }
  }

  return 0;
}
