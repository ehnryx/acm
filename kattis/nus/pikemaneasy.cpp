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
constexpr ll MOD = 1e9 + 7;
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

  int n, t;
  cin >> n >> t;
  int a, b, c, t0;
  cin >> a >> b >> c >> t0;
  vector<int> all;
  for(int i=0; i<n; i++) {
    all.push_back(t0);
    t0 = ((ll)a * t0 + b) % c + 1;
  }
  sort(all.begin(), all.end());

  int num = 0;
  ll penalty = 0;
  ll cur = 0;
  for(int i=0; i<n; i++) {
    cur += all[i];
    if(cur > t) break;
    num++;
    penalty += cur;
  }
  cout << num << " " << penalty % MOD << nl;

  return 0;
}
