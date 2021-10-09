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



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  sort(s.begin(), s.end());

  int n = s.size();
  int h = n/2;
  if(n <= 8) {
    do {
      unordered_set<string> seen;
      string cur = s + s;
      bool ok = true;
      for(int i=0; i<n; i++) {
        ok &= seen.insert(cur.substr(i, h)).second;
      }
      if(ok) {
        cout << "YES" << nl;
        cout << s << nl;
        return 0;
      }
    } while(next_permutation(s.begin(), s.end()));
    cout << "NO" << nl;
    return 0;
  }

  map<char,int> cnt;
  char sad = 0;
  for(char c : s) {
    cnt[c]++;
    if(cnt[c] > h) {
      sad = c;
    }
  }

  if(sad) {
    rotate(s.begin(), lower_bound(s.begin(), s.end(), sad), s.end());
  }

  if(s[n-2] == s[0]) {
    cout << "NO" << nl;
    return 0;
  }

  if(s[n-3] == s[0]) {
    if(s[n-2] == s[n-1]) {
      cout << "NO" << nl;
      return 0;
    }

    cout << "YES" << nl;
    for(int i=0; i<h-1; i++) {
      cout << s[i];
    }
    cout << s[n-2];
    for(int i=h-1; i<n-2; i++) {
      cout << s[i];
    }
    cout << s[n-1];
    cout << nl;
    return 0;
  }

  cout << "YES" << nl;
  for(int i=0; i<h-1; i++) {
    cout << s[i];
  }
  cout << s[n-3];
  for(int i=h-1; i<n-3; i++) {
    cout << s[i];
  }
  cout << s[n-2];
  cout << s[n-1];
  cout << nl;

  return 0;
}
