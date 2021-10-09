//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

const int N = 100;
char one[N][N], two[N][N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m, h;
  cin >> n >> m >> h;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> one[i][j];
    }
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<h; j++) {
      cin >> two[i][j];
    }
  }

  vector<tuple<int,int,int>> big, small;
  for(int i=0; i<n; i++) {
    vector<int> mvals, hvals;
    for(int j=0; j<m; j++) {
      if(one[i][j] == '0') continue;
      mvals.push_back(j);
      for(int k=0; k<h; k++) {
        if(two[i][k] == '1') {
          big.emplace_back(i, j, k);
        }
      }
    }
    for(int k=0; k<h; k++) {
      if(two[i][k] == '1') {
        hvals.push_back(k);
      }
    }

    if(mvals.empty() ^ hvals.empty()) {
      cout << -1 << nl;
      return 0;
    }

    while(mvals.size() < hvals.size()) mvals.push_back(mvals[0]);
    while(hvals.size() < mvals.size()) hvals.push_back(hvals[0]);
    sort(mvals.begin(), mvals.end());
    sort(hvals.begin(), hvals.end());
    for(int t=0; t<mvals.size(); t++) {
      small.emplace_back(i, mvals[t], hvals[t]);
    }
  }

  sort(big.begin(), big.end());
  sort(small.begin(), small.end());

  cout << big.size() << nl;
  for(auto [a, b, c] : big) {
    cout << a << " " << b << " " << c << nl;
  }

  cout << small.size() << nl;
  for(auto [a, b, c] : small) {
    cout << a << " " << b << " " << c << nl;
  }

  return 0;
}
