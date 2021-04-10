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

vector<int> shift_up(vector<int> a, vector<int> b) {
  int sub = *min_element(begin(a), end(a));
  vector<int> res;
  for(int it : a) {
    res.push_back(it - sub);
  }
  for(int it : b) {
    res.push_back(it + sub);
  }
  return res;
}

vector<int> get_key(vector<int> a, vector<int> b) {
  vector<int> res = min(shift_up(a, b), shift_up(b, a));
  reverse(begin(a), end(a));
  reverse(begin(b), end(b));
  res = min(res, min(shift_up(a, b), shift_up(b, a)));
  return res;
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

  int w, m, n;
  cin >> w >> m >> n;
  set<vector<int>> have;
  for(int i=0; i<n; i++) {
    vector<int> a(m), b(m);
    for(int j=0; j<m; j++) {
      cin >> a[j];
    }
    for(int j=0; j<m; j++) {
      cin >> b[j];
    }
    vector<int> key = get_key(a, b);
    have.insert(key);
  }
  cout << size(have) << nl;

  return 0;
}
