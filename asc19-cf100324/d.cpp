//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "dna"

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

vector<string> calc(const string& s) {
  int n = s.size();
  vector<string> out = {s};
  for(int t=0; t<2; t++) {
    int len = out.size();
    for(int i=0; i<len; i++) {
      string cur = out[i];
      for(int l=0; l<n; l++) {
        for(int r=l; r<n; r++) {
          reverse(cur.begin()+l, cur.begin()+r+1);
          out.push_back(cur);
          reverse(cur.begin()+l, cur.begin()+r+1);
        }
      }
    }
  }
  return out;
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

  string s, t;
  cin >> s >> t;
  vector<string> first = calc(s);
  vector<string> second = calc(t);
  set<string> seen(first.begin(), first.end());
  for(const string& it : second) {
    if(seen.count(it)) {
      cout << "Similar" << nl;
      return 0;
    }
  }
  cout << "Different" << nl;

  return 0;
}
