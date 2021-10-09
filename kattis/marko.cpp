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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  map<char,char> mp;
  mp['a'] = '2';
  mp['b'] = '2';
  mp['c'] = '2';
  mp['d'] = '3';
  mp['e'] = '3';
  mp['f'] = '3';
  mp['g'] = '4';
  mp['h'] = '4';
  mp['i'] = '4';
  mp['j'] = '5';
  mp['k'] = '5';
  mp['l'] = '5';
  mp['m'] = '6';
  mp['n'] = '6';
  mp['o'] = '6';
  mp['p'] = '7';
  mp['q'] = '7';
  mp['r'] = '7';
  mp['s'] = '7';
  mp['t'] = '8';
  mp['u'] = '8';
  mp['v'] = '8';
  mp['w'] = '9';
  mp['x'] = '9';
  mp['y'] = '9';
  mp['z'] = '9';

  int n;
  cin >> n;
  unordered_map<string,int> cnt;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    for(char& c : s) {
      c = mp[c];
    }
    cnt[s] += 1;
  }
  string s;
  cin >> s;
  cout << cnt[s] << nl;

  return 0;
}
