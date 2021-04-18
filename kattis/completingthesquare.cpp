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

  vector<pt> v;
  for(int i=0; i<3; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(a, b);
  }
  if(abs(v[0] - v[1]) < abs(v[1] - v[2])) {
    swap(v[0], v[2]);
  }
  if(abs(v[0] - v[1]) < abs(v[0] - v[2])) {
    swap(v[1], v[2]);
  }
  pt mid = (v[0] + v[1]) / (ld)2;
  pt res = (ld)2*mid - v[2];
  cout << (int)round(real(res)) << " " << (int)round(imag(res)) << nl;


  return 0;
}
