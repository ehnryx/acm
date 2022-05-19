#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "number/fraction.h"
%:include "number/int_base10.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = int_base10;
using Fraction = fraction<Int>;

Fraction read_fraction(fast_input<>& cin, int n) {
  auto a = cin.read<int>(n);
  Fraction res(a.back(), 1);
  for(int i=(int)a.size()-2; i>=0; i--) {
    res = res.inverse() + Fraction(a[i], 1);
  }
  return res;
}

void print_fraction(Fraction v) {
  for(;;) {
    cout << v.integer_part();
    v = v.fractional_part();
    if(v == Int(0)) break;
    v = v.inverse();
    cout << " ";
  }
  cout << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  auto a = read_fraction(cin, n);
  auto b = read_fraction(cin, m);
  print_fraction(a + b);
  print_fraction(a - b);
  print_fraction(a * b);
  print_fraction(a / b);

  return 0;
}
