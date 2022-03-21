#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int getnum() {
  string line;
  getline(cin, line);
  int res = 0;
  for(char c : line) {
    if(isdigit(c)) {
      res = 10*res + c - '0';
    }
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  string line;
  getline(cin, line);
  int n = stoi(line);
  for(int i=0; i<n; i++) {
    for(char c : to_string(getnum() + getnum())) {
      cout << c << " ";
    }
    cout << nl;
  }

  return 0;
}
