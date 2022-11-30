#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/fraction.h"
%:include "math/matrix.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Fraction = fraction<long long>;
using Matrix = matrix<Fraction>;

bool solve1(const vector<int>& a) {
  vector<vector<Fraction>> es;
  for(int i=1; i<size(a); i++) {
    es.push_back({ a[i-1], a[i] });
  }
  Matrix mat(es);
  if(mat.solve() == -1) {
    return false;
  }
  auto ans = mat.ans[0] * a[a.size()-1];
  assert(ans.denominator() == 1);
  cout << ans.numerator() << nl;
  return true;
}

bool solve2(const vector<int>& a) {
  vector<vector<Fraction>> es;
  for(int i=2; i<size(a); i++) {
    es.push_back({ a[i-2], a[i-1], a[i] });
  }
  Matrix mat(es);
  if(mat.solve() == -1) {
    return false;
  }
  auto ans = mat.ans[0] * a[a.size()-2] + mat.ans[1] * a[a.size()-1];
  assert(ans.denominator() == 1);
  cout << ans.numerator() << nl;
  return true;
}

bool solve3(const vector<int>& a) {
  vector<vector<Fraction>> es;
  for(int i=3; i<size(a); i++) {
    es.push_back({ a[i-3], a[i-2], a[i-1], a[i] });
  }
  Matrix mat(es);
  if(mat.solve() == -1) {
    return false;
  }
  auto ans = mat.ans[0] * a[a.size()-3] + mat.ans[1] * a[a.size()-2] + mat.ans[2] * a[a.size()-1];
  assert(ans.denominator() == 1);
  cout << ans.numerator() << nl;
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
    int n;
    cin >> n;
    auto a = cin.read<int>(n);
    if(solve1(a)) {
    } else if(solve2(a)) {
    } else if(solve3(a)) {
    } else {
      assert(false);
    }
  }

  return 0;
}
