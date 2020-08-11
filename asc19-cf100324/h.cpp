//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "pebbles"

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

ld calc(const string& s) {
  bool first = true;
  ld val = 0;
  ld frac = 1;
  for(char c : s) {
    if(first && c == s[0]) {
      val += 1;
    } else {
      first = false;
      frac /= 2;
      if(c == s[0]) {
        val += frac;
      } else {
        val -= frac;
      }
    }
  }
  return (s[0] == 'B' ? val : -val);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  int n;
  cin >> n;

  ld res = 0;
  vector<string> s(n);
  for(int i=0; i<n; i++) {
    cin >> s[i];
    res += calc(s[i]);
  }

  if(res > 0) {
    cout << "Andrew" << nl;
    for(int i=0; i<n; i++) {
      for(int j=0; j<s[i].size(); j++) {
        if(s[i][j] == 'R') continue;
        if(res - calc(s[i]) + calc(s[i].substr(0, j)) >= 0) {
          cout << i+1 << " " << j+1 << nl;
          return 0;
        }
      }
    }
    assert(false);
  } else {
    cout << "Mike" << nl;
  }

  return 0;
}
