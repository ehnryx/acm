#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 4e3 + 1;
int a[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  sort(a+1, a+1+n);

  unordered_map<int,vector<pair<int,int>>> sum;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<i; j++) {
      sum[a[i]+a[j]].emplace_back(i, j);
    }
  }
  sum.erase(0);

  for(int i=n; i>=1; i--) {
    for(int j=1; j<=n; j++) {
      if(i == j) continue;
      int dif = a[i] - a[j];
      auto it = sum.find(dif);
      if(it != sum.end()) {
        for(auto [ii, jj] : it->second) {
          if(i != ii && i != jj && j != ii && j != jj) {
            cout << a[i] << nl;
            return 0;
          }
        }
      }
    }
  }

  cout << "no solution" << nl;

  return 0;
}
