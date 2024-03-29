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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    int x;
    cin >> x;
    string s;
    cin >> s;
    ll tail = (int)s.size() - 1;
    for(int i=1; i<=x; i++) {
      tail = tail * (s[i-1]-'0') % MOD - 1;
      int curlen = s.size();
      for(int j=1; j<s[i-1]-'0' && s.size()<x; j++) {
        for(int k=i; k<curlen && s.size()<x; k++) {
          s.push_back(s[k]);
        }
      }
    }
    cout << ((1+x+tail) % MOD + MOD) % MOD << nl;
  }

  return 0;
}
