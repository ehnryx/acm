#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int read(string s) {
  int res = 0;
  for(char c : s) {
    res += c - 32;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  string a, c;
  cin >> a >> c;
  int offset = read(a) - (c[0] - 'a');
  getline(cin, c); // rid the newline

  for(string line; getline(cin, line); ) {
    istringstream in(line);
    for(string s; in >> s; ) {
      if(s == "0") {
        cout << " ";
      } else if(s == "<") {
        cout << ",";
      } else if(s == ">") {
        cout << ".";
      } else {
        cout << (char)(((read(s) - offset) % 26 + 26) % 26 + 'a');
      }
    }
    cout << nl;
  }

  return 0;
}
