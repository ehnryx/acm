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
    for(char c : s) {
      if(tolower(c) == 'a') {
        cout << "Hi! ";
      } else if(tolower(c) == 'e') {
        cout << "Bye! ";
      } else if(tolower(c) == 'i') {
        cout << "How are you? ";
      } else if(tolower(c) == 'o') {
        cout << "Follow me! ";
      } else if(tolower(c) == 'u') {
        cout << "Help! ";
      } else if(isdigit(c)) {
        cout << "Yes! ";
      }
    }
    cout << nl;
  }

  return 0;
}
