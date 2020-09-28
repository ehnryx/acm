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

const int N = 400;
int val[N][N];
int best[N][N];

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

  int nr, nc, n, m;
  cin >> nr >> nc >> n >> m;

  if(n == 0) {
    cout << 0 << nl;
    return 0;
  }

  vector<pair<int,int>> rem, keep;
  vector<int> kr, kc;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    kr.push_back(x+7);
    kr.push_back(x+8);
    kc.push_back(y+4);
    kc.push_back(y+5);
    keep.emplace_back(x, y);
  }
  for(int i=0; i<m; i++) {
    int x, y;
    cin >> x >> y;
    kr.push_back(x+7);
    kr.push_back(x+8);
    kc.push_back(y+4);
    kc.push_back(y+5);
    rem.emplace_back(x, y);
  }

  int ans = n;

  kr.push_back(0);
  kc.push_back(0);
  sort(kr.begin(), kr.end());
  sort(kc.begin(), kc.end());
  kr.resize(unique(kr.begin(), kr.end()) - kr.begin());
  kc.resize(unique(kc.begin(), kc.end()) - kc.begin());
  while(kr.back() > nr) kr.pop_back();
  while(kc.back() > nc) kc.pop_back();

  for(int i=0; i<kr.size(); i++) {
    for(int j=0; j<kc.size(); j++) {
      for(auto [a, b] : keep) {
        if(a < kr[i] && b < kc[j]) {
          val[i][j]--;
        }
      }
      for(auto [a, b] : rem) {
        if(a < kr[i] && b < kc[j]) {
          val[i][j]++;
        }
      }
    }
  }

  for(int i=0; i<kr.size(); i++) {
    for(int j=0; j<kc.size(); j++) {
      for(int k=0; k<j; k++) {
        ans = min(ans, (int)keep.size() + best[j][k] + val[i][j] - val[i][k]);
        best[j][k] = min(best[j][k], val[i][k] - val[i][j]);
      }
    }
  }
  cout << ans << nl;

  return 0;
}
