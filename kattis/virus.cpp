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
typedef pair<int,int> pii;
typedef vector<int> vi;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s, t;
  cin >> s >> t;
  int a = s.size();
  int b = t.size();
  int ok = 0;
  for(int i=0; i<min(a,b); i++) {
    if(s[i] == t[i]) {
      ok++;
    } else {
      break;
    }
  }
  reverse(s.begin(), s.end());
  reverse(t.begin(), t.end());
  for(int i=0; i<min(a,b); i++) {
    if(s[i] == t[i]) {
      ok++;
    } else {
      break;
    }
  }
  cout << max(0, b-min(a,ok)) << nl;

  return 0;
}
