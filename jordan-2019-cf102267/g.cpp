#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1 << 17;

struct segtree {
  ll st[2*N];
  segtree() { memset(st, 0, sizeof st); }
  void insert(int i, ll v) {
    st[i+=N] = v;
    for(i/=2; i; i/=2) {
      st[i] = st[2*i] + st[2*i+1];
    }
  }
  ll query(int l, int r) {
    ll res = 0;
    for(l+=N, r+=N+1; l<r; l/=2, r/=2) {
      if(l&1) res += st[l++];
      if(r&1) res += st[--r];
    }
    return res;
  }
  int find(ll x, int i=1, int s=0, int e=N-1) {
    if(x >= st[i]) return -1;
    if(s == e) return s;
    int m = (s+e) / 2;
    int res = find(x, 2*i, s, m);
    if(res != -1) return res;
    return find(x - st[2*i], 2*i+1, m+1, e);
  }
};

namespace food {
  // min should be >= x
  pair<ll, int> st[2*N];
  ll lazy[2*N];
  void push(int i) {
    if(lazy[i]) {
      st[2*i].first += lazy[i];
      lazy[2*i] += lazy[i];
      st[2*i+1].first += lazy[i];
      lazy[2*i+1] += lazy[i];
      lazy[i] = 0;
    }
  }
  void pull(int i) {
    st[i] = min(st[2*i], st[2*i + 1]);
  }

  void insert(int x, ll v, int i=1, int s=0, int e=N-1) {
    if(s == e) {
      st[i] = pair(v, s);
      return;
    }
    push(i);
    int m = (s+e) / 2;
    if(x <= m) insert(x, v, 2*i, s, m);
    else insert(x, v, 2*i+1, m+1, e);
    pull(i);
  }

  void update(int l, int r, ll v, int i=1, int s=0, int e=N-1) {
    if(r<s || e<l) return;
    if(l<=s && e<=r) {
      st[i].first += v;
      lazy[i] += v;
      return;
    }
    push(i);
    int m = (s+e) / 2;
    update(l, r, v, 2*i, s, m);
    update(l, r, v, 2*i+1, m+1, e);
    pull(i);
  }

  pair<ll, int> query(int l, int r, int i=1, int s=0, int e=N-1) {
    if(r<s || e<l) return pair(INFLL, -1);
    if(l<=s && e<=r) return st[i];
    push(i);
    int m = (s+e) / 2;
    return min(query(l, r, 2*i, s, m), query(l, r, 2*i+1, m+1, e));
  }
};

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

  segtree alive, summer;

  vector<int> a(n+1);
  vector<ll> b(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i] >> b[i];
    alive.insert(i, 1);
    summer.insert(i, a[i]);
    food::insert(i, summer.query(1, i) + b[i]);
  }
  summer.insert(n+1, INFLL);

  int q;
  cin >> q;
  while(q--) {
    int t;
    cin >> t;

    if(t == 1) {
      ll x;
      cin >> x;
      int rb = summer.find(x);
      int starve = alive.query(rb, n);
      vector<int> kill;
      for(pair<ll, int> die; (die = food::query(1, rb - 1)).first < x; ) {
        int i = die.second;
        food::insert(i, INFLL); // effectively kill
        kill.push_back(i);
      }
      for(int i : kill) {
        alive.insert(i, 0);
        summer.insert(i, 0);
        food::update(i, n, -a[i]);
        a[i] = 0;
      }
      cout << size(kill) << " " << starve << nl;
    }

    else {
      int new_a;
      ll new_b;
      int i;
      cin >> new_a >> new_b >> i;
      food::update(i, n, new_a - a[i]);
      a[i] = new_a;
      b[i] = new_b;
      alive.insert(i, 1);
      summer.insert(i, a[i]);
      food::insert(i, summer.query(1, i) + b[i]);
    }
  }

  return 0;
}
