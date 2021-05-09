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

  const int M = 1e6;
  vector<bool> isp(M + 1, true);
  isp[0] = false;
  for(int i=2; i*i<=M; i++) {
    if(!isp[i]) continue;
    for(int j=i*i; j<=M; j+=i) {
      isp[j] = false;
    }
  }
  vector<int> primes;
  for(int i=1; i<=M; i++) {
    if(isp[i]) {
      primes.push_back(i);
    }
  }

  ordered_set<int> gen;
  for(int i=1; i<=M; i++) {
    gen.insert(i);
  }
  vector<int> all;
  while(!gen.empty()) {
    vector<int> cur;
    auto it = prev(upper_bound(begin(primes), end(primes), size(gen)));
    for(int i = it - begin(primes); i >= 0; i--) {
      auto rem = gen.find_by_order(primes[i] - 1);
      cur.push_back(*rem);
      gen.erase(rem);
    }
    all.insert(end(all), rbegin(cur), rend(cur));
  }
  vector<int> inv(size(all) + 1);
  for(int i=0; i<M; i++) {
    inv[all[i]] = i;
  }

  int m;
  cin >> m;
  vector<int> ans(m);
  vector<tuple<int,int,int,int>> queries;
  for(int i=0; i<m; i++) {
    int t, n, k;
    cin >> t >> n >> k;
    queries.emplace_back(n, k, t, i);
  }
  sort(begin(queries), end(queries));

  ordered_set<pair<int,int>> have;
  int pn = 0;
  for(auto [n, k, t, i] : queries) {
    while(pn < n) {
      ++pn;
      have.insert(pair(inv[pn], pn));
    }
    if(t == 1) {
      ans[i] = have.order_of_key(pair(inv[k], 0)) + 1;
    } else {
      ans[i] = have.find_by_order(k - 1)->second;
    }
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
