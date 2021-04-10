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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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

  int T;
  cin >> T;
  for(int testnum=1; testnum<=T; testnum++) {
    cout << "Case " << testnum << ": ";
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }

    if(*max_element(a.begin(), a.end()) == *min_element(a.begin(), a.end())) {
      if(a[0] > 1) cout << 0 << nl;
      else cout << 1 << nl;
      continue;
    }

    int g = 0;
    for(int i=1; i<n; i++) {
      g = gcd(g, abs(a[i] - a[i-1]));
    }

    vector<int> primes;
    for(int d=2; d*d<=g; d++) {
      if(g % d == 0) {
        primes.push_back(d);
        while(g % d == 0) {
          g /= d;
        }
      }
    }
    if(g > 1) primes.push_back(g);

    unsigned int ans = -1;
    for(int d : primes) {
      int rem = -1;
      bool ok = true;
      for(int i=0; i<n; i++) {
        if(rem == -1) {
          rem = a[i] % d;
        } else if(rem != a[i] % d) {
          ok = false;
          break;
        }
      }
      if(ok) {
        int add = d - a[0] % d;
        if(add >= d) add -= d;
        ans = min(ans, (unsigned int)add);
      }
    }
    cout << (int)ans << nl;
  }

  return 0;
}
