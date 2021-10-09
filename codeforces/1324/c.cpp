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



// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    s.push_back('R');
    int n = s.size();
    int l = 1;
    int r = n;
    while(l < r) {
      int m = (l+r) / 2;
      int far = m;
      bool ok = true;
      for(int i=0; i<n; i++) {
        if(s[i] == 'R') {
          if(i+1 > far) {
            ok = false;
            break;
          }
          far = i+1+m;
        }
      }
      if(ok) {
        r = m;
      } else {
        l = m+1;
      }
    }
    cout << r << nl;
  }

  return 0;
}
