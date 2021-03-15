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

  int n, m;
  cin >> n >> m;
  vector<ll> bar(n);
  for(int i=0; i<n; i++) {
    cin >> bar[i];
  }
  vector<ll> plate(m);
  for(int i=0; i<m; i++) {
    cin >> plate[i];
  }

  set<ll> all;
  for(int bm=0; bm<1<<m; bm++) {
    ll sum = 0;
    for(int i=0; i<m; i++) {
      if(bm & 1<<i) {
        sum += plate[i];
      }
    }
    bool ok = (bm == 0);
    for(int sm=bm; sm; sm=(sm-1)&bm) {
      ll left = 0, right = 0;
      for(int i=0; i<m; i++) {
        if(bm & 1<<i) {
          if(sm & 1<<i) {
            left += plate[i];
          } else {
            right += plate[i];
          }
        }
      }
      ok |= (left == right);
    }
    if(ok) {
      for(int i=0; i<n; i++) {
        all.insert(bar[i] + sum);
      }
    }
  }

  for(ll it : all) {
    cout << it << nl;
  }

  return 0;
}