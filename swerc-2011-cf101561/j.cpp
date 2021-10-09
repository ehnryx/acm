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
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll n, ll e) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % MOD;
    n = n*n % MOD;
  }
  return r;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  const int N = 1e7 + 1;
  vector<bool> np(N);
  vector<int> ans(N, 1);
  vector<int> cur(N);
  for(int i=2; i<N; i++) {
    if(np[i]) continue;
    for(ll j=(ll)i*i; j<N; j+=i) {
      np[j] = true;
    }
    for(ll j=i; j<N; j*=i) {
      for(int k=j; k<N; k+=j) {
        cur[k]++;
      }
    }
    int sum = 0;
    int pre = 0;
    for(int k=i; k<N; k+=i) {
      sum += cur[k];
      int add = sum/2 - pre;
      pre = sum/2;
      ans[k] = ans[k] * power(i, add) % MOD;
    }
    for(ll j=i; j<N; j*=i) {
      for(int k=j; k<N; k+=j) {
        cur[k] = 0;
      }
    }
  }

  for(int i=1; i<N; i++) {
    ans[i] = (ll) ans[i-1] * ans[i] % MOD;
  }

  for(int n; cin >> n && n; ) {
    cout << (ll) ans[n] * ans[n] % MOD << nl;
  }

  return 0;
}
