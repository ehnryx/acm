#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

bool win(int a, int b, int c, int d) {
  if(a < b) swap(a, b);
  if(c < d) swap(c, d);
  int ab = a*10 + b;
  int cd = c*10 + d;
  if(cd == 21) return false;
  if(ab == 21) return true;
  if(c == d) {
    if(a == b) {
      return ab > cd;
    } else {
      return false;
    }
  }
  if(a == b) {
    return true;
  }
  return ab > cd;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  for(char a, b, c, d; cin >> a >> b >> c >> d && a != '0'; ) {
    int cnt = 0;
    int total = 0;
    for(char x = '1'; x <= '6'; x++) {
      if(a != '*' && a != x) continue;
      for(char y = '1'; y <= '6'; y++) {
        if(b != '*' && b != y) continue;
        for(char z = '1'; z <= '6'; z++) {
          if(c != '*' && c != z) continue;
          for(char w = '1'; w <= '6'; w++) {
            if(d != '*' && d != w) continue;
            cnt += win(x - '0', y - '0', z - '0', w - '0');
            total++;
          }
        }
      }
    }
    int g = gcd(cnt, total);
    cout << cnt/g;
    if(total > g) {
      cout << "/" << total/g;
    }
    cout << nl;
  }

  return 0;
}
