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

const int N = 3e5 + 1;
vector<pair<int,int>> adj[N];
int have[N];

pair<list<int>, ll> solve(int x, int u, int p) {
  vector<list<int>> child;
  vector<pair<ll,int>> order;
  ll sum = have[u];
  for(auto [v, e] : adj[u]) {
    if(v == p) continue;
    auto [sub, val] = solve(x, v, u);
    if (val > 0) {
      sub.insert(end(sub), e);
    } else {
      sub.insert(begin(sub), e);
    }
    order.emplace_back(val, (int)child.size());
    child.push_back(move(sub));
    sum += val - x;
  }
  sort(begin(order), end(order), greater<pair<ll,int>>());
  list<int> ans;
  for(auto [_, i] : order) {
    ans.splice(ans.end(), child[i]);
  }
  return pair(move(ans), sum);
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

  int n, m, x;
  cin >> n >> m >> x;
  for(int i=1; i<=n; i++) {
    cin >> have[i];
  }
  if(accumulate(begin(have), end(have), (ll)0) < (ll)x * (n-1)) {
    cout << "NO" << nl;
    return 0;
  }

  vector<int> dsu(n + 1, -1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int,int)> link = [&](int i, int j) {
    i = find(i);
    j = find(j);
    if(i == j) return;
    dsu[j] = i;
    return;
  };

  vector<int> a(m+1), b(m+1);
  for(int i=1; i<=m; i++) {
    cin >> a[i] >> b[i];
    if(find(a[i]) == find(b[i])) continue;
    link(a[i], b[i]);
    adj[a[i]].emplace_back(b[i], i);
    adj[b[i]].emplace_back(a[i], i);
  }

  auto [ans, _] = solve(x, 1, 0);
  cout << "YES" << nl;
  for(int it : ans) {
    cout << it << nl;
  }

  return 0;
}
