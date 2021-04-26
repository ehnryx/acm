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

struct Frac {
  int a, b;
  Frac(ll _a=0, ll _b=0): a(_a), b(_b) {}
  bool operator > (const Frac& o) const {
    return (ll)a*o.b > (ll)b*o.a;
  }
  bool operator <= (const Frac& o) const {
    return (ll)a*o.b <= (ll)b*o.a;
  }
  void operator += (const Frac& o) {
    a += o.a;
    b += o.b;
  }
};

const int N = 1e5 + 1;
vector<int> adj[N];
int a[N], b[N];

using order_t = priority_queue<Frac, vector<Frac>, greater<Frac>>;
order_t solve(int u, ll& ans) {
  order_t subtree;
  for(int v : adj[u]) {
    order_t child = solve(v, ans);
    if(size(subtree) < size(child)) {
      swap(subtree, child);
    }
    while(!child.empty()) {
      subtree.push(child.top());
      child.pop();
    }
  }
  Frac cur(a[u], b[u]);
  while(!subtree.empty() && subtree.top() <= cur) {
    ans += (ll)cur.b * subtree.top().a;
    cur += subtree.top();
    subtree.pop();
  }
  subtree.push(cur);
  return subtree;
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
  for(int i=2; i<=n; i++) {
    int parent;
    cin >> parent;
    adj[parent].push_back(i);
  }
  for(int i=1; i<=n; i++) {
    cin >> a[i] >> b[i];
  }

  ll ans = 0;
  order_t order = solve(1, ans);
  Frac cur(0, 0);
  while(!order.empty()) {
    ans += (ll)cur.b * order.top().a;
    cur += order.top();
    order.pop();
  }
  cout << ans << nl;

  return 0;
}
