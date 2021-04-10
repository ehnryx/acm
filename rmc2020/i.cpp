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

  int n;
  cin >> n;
  vector<int> control(4), vaccine(4);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    if(s[0] == 'Y') {
      vaccine[0]++;
      for(int j=1; j<=3; j++) {
        vaccine[j] += (s[j] == 'Y');
      }
    } else {
      control[0]++;
      for(int j=1; j<=3; j++) {
        control[j] += (s[j] == 'Y');
      }
    }
  }

  for(int j=1; j<=3; j++) {
    if(vaccine[j] * control[0] >= control[j] * vaccine[0]) {
      cout << "Not Effective" << nl;
    } else {
      cout << 100 * (1 - (ld)vaccine[j]*control[0]/control[j]/vaccine[0]) << nl;
    }
  }

  return 0;
}
