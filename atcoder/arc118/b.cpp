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

  int k, n, m;
  cin >> k >> n >> m;
  vector<int> a(k), b(k);
  vector<pair<ld,int>> order;
  ll sum = 0;
  for(int i=0; i<k; i++) {
    cin >> a[i];
    b[i] = (ll)m*a[i]/n;
    sum += b[i];
    ld x = (ld)m*a[i]/n;
    order.emplace_back(x - floor(x), i);
  }

  if(sum < m) {
    sort(begin(order), end(order), greater<>());
    int base = (m - sum) / k;
    int extra = (m - sum) % k;
    for(int i=0; i<k; i++) {
      b[order[i].second] += base + (i < extra);
    }
  } else {
    sort(begin(order), end(order));
    int base = (sum - m) / k;
    int extra = (sum - m) % k;
    for(int i=0; i<k; i++) {
      b[order[i].second] -= base + (i < extra);
    }
  }

  for(int it : b) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
