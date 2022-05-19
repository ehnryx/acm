#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

bool solve(string s, int base) {
  for(char c : s) {
    if(isdigit(c) && c - '0' >= base) throw 0;
    if(isalpha(c) && c - 'A' + 10 >= base) throw 0;
  }
  ll n = stoll(s, 0, base);
  if(n <= 1) return false; // what is a prime
  for(int i=2; (ll)i*i <= n; i++) {
    if(n % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    int cnt = 0;
    int all = 0;
    try {
      cnt += solve(s, 2);
      all++;
    } catch(...) {}
    try {
      cnt += solve(s, 8);
      all++;
    } catch(...) {}
    try {
      cnt += solve(s, 10);
      all++;
    } catch(...) {}
    try {
      cnt += solve(s, 16);
      all++;
    } catch(...) {}
    int g = gcd(cnt, all);
    cout << cnt/g << "/" << all/g << nl;
  }

  return 0;
}
