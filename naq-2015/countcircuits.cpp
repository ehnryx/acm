//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class U, class V>
pair<U,V> operator + (const pair<U,V>& a, const pair<U,V>& b) {
  return make_pair(a.first + b.first, a.second + b.second);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<pair<int,int>> left, right;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    if(i <= n/2) {
      left.emplace_back(x, y);
    } else {
      right.emplace_back(x, y);
    }
  }

  int lsz = left.size();
  vector<pair<int,int>> ldp(1<<lsz);
  for(int i=1; i<1<<lsz; i++) {
    int j = __builtin_ctz(i & -i);
    ldp[i] = ldp[i ^ 1<<j] + left[j];
  }

  int rsz = right.size();
  vector<pair<int,int>> rdp(1<<rsz);
  for(int i=1; i<1<<rsz; i++) {
    int j = __builtin_ctz(i & -i);
    rdp[i] = rdp[i ^ 1<<j] + right[j];
  }

  map<pair<int,int>,int> have;
  for(const auto& it : ldp) {
    have[it]++;
  }

  ll ans = 0;
  for(const auto& [a, b] : rdp) {
    pair<int,int> neg(-a, -b);
    if(have.count(neg)) {
      ans += have[neg];
    }
  }
  cout << ans - 1 << nl;

  return 0;
}
