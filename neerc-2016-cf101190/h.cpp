//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "hard"

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

  const int LB = -32768;
  const int UB = 32767;

  vector<pair<int,int>> v;
  for(string line; getline(cin, line); ) {
    istringstream in(line);
    string _, cmp; int val;
    int left = LB;
    int right = UB;
    while(in >> _ >> cmp >> val) {
      if(cmp == "<=") {
        right = val;
      } else {
        left = val;
      }
      in >> _;
    }
    if(left <= right) {
      v.emplace_back(left, -1);
      v.emplace_back(right, 1);
    }
  }
  sort(v.begin(), v.end());

  set<int> have;
  int start = -INF;
  int cur = 0;
  for(auto [x, t] : v) {
    if(cur == 0) start = x;
    cur += t;
    if(cur == 0) {
      for(int i=start; i<=x; i++) {
        have.insert(i);
      }
    }
  }

  if(have.empty()) {
    cout << "false" << nl;
  } else if(have.size() == UB - LB + 1) {
    cout << "true" << nl;
  } else {
    bool first = true;
    for(int i=LB; i<=UB; i++) {
      if(have.count(i)) {
        if(!have.count(i-1)) {
          start = i;
        }
        if(!have.count(i+1)) {
          if(!first) {
            cout << " ||" << nl;
          }
          if(start > LB) cout << "x >= " << start;
          if(i < UB) {
            if(start > LB) cout << " && ";
            cout << "x <= " << i;
          }
          first = false;
        }
      }
    }
    cout << nl;
  }

  return 0;
}
