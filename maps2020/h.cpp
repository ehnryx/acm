//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 50 + 1;
ll ans[M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int c, n, m;
  cin >> c >> n >> m;
  vector<int> v(n);
  for(int i=0; i<n; i++) {
    cin >> v[i];
  }

  ans[0] = n;
  ll over = 0;
  for(int d=1; d<M; d++) {
    over *= 2;
    for(int j=0; j<v.size(); j++) {
      v[j] *= 2;
      if(v[j] > c) {
        v[j] = 0;
        over += 2;
      }
    }
    for(int j=0; j<v.size(); j++) {
      if(v[j] == 0) {
        swap(v[j], v[v.size()-1]);
        v.pop_back();
        --j;
      }
    }
    ans[d] = over + v.size();
  }

  for(int j=0; j<m; j++) {
    int k;
    cin >> k;
    cout << ans[k] << nl;
  }

  return 0;
}
