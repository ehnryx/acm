#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "jenga"

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
const ld EPS = 1e-13;
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

  int n, w;
  cin >> n >> w;
  w = 2; // ???
  int h, m;
  cin >> h >> m;

  vector<ll> cnt(h + 1), x(h + 1), y(h + 1);
  vector<int> num(h + 1), lb(h + 1), rb(h + 1);
  vector<vector<bool>> rem(h + 1);
  for(int i=1; i<=h; i++) {
    num[i] = n;
    rem[i].resize(n + 1);
    lb[i] = 1;
    rb[i] = n;
    for(int j=1; j<=i; j++) {
      cnt[j] += n;
      if(i % 2) {
        x[j] += n * n*w/2;
        y[j] += n*w/2 + (n-1)*n/2 * w;
      } else {
        y[j] += n * n*w/2;
        x[j] += n*w/2 + (n-1)*n/2 * w;
      }
    }
  }
  assert(n * n*w/2 == n*w/2 + (n-1)*n/2 * w); // ???

  for(int i=1; i<=m; i++) {
    int l, k;
    cin >> l >> k;
    //cerr << "@ " << i << " -> " << l << " " << k << nl;
    rem[l][k] = true;
    if(--num[l] == 0) {
      cout << "yes" << nl;
      cout << i << nl;
      return 0;
    }
    // remove block
    for(int j=1; j<=l; j++) {
      cnt[j] -= 1;
      if(l % 2) {
        x[j] -= n*w/2;
        y[j] -= k*w - w/2;
      } else {
        y[j] -= n*w/2;
        x[j] -= k*w - w/2;
      }
    }
    while(rem[l][lb[l]]) lb[l]++;
    while(rem[l][rb[l]]) rb[l]--;
    // check for bot collapse
    for(int j=1; j<=l; j++) {
      if(j == h) continue;
      ll check = (j % 2 ? y[j + 1] : x[j + 1]);
      ll left = (lb[j] - 1) * w * cnt[j + 1];
      ll right = rb[j] * w * cnt[j + 1];
      //cerr << "check " << left << " " << right << " and " << check << nl;
      if(check <= left || check >= right) {
        cout << "yes" << nl;
        cout << i << nl;
        return 0;
      }
    }
  }

  cout << "no" << nl;

  return 0;
}

