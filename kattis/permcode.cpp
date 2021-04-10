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

int pos(const string& s, char c) {
  return find(begin(s), end(s), c) - begin(s);
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

  for(int x; cin >> x && x; ) {
    string s, p, c;
    cin >> s >> p >> c;
    int n = size(c);
    int d = (int)floor(powl(n, 1.5) + x) % n;
    string m(n, p[pos(s, c[d])]);
    for(int i=1; i<n; i++) {
      int j = (d + n - i) % n;
      int nj = (j + 1) % n;
      m[j] = p[pos(s, m[nj]) ^ pos(s, c[j])];
    }
    cout << m << nl;
  }

  return 0;
}
