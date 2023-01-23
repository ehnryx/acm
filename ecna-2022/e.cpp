#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/square_matrix_var.h"
%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<37>;
using Matrix = square_matrix_var<Int>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  Matrix mat(n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> mat[i][j];
    }
  }
  string s;
  getline(cin, s);  // eat newline
  getline(cin, s);

  vector<Int> v;
  transform(begin(s), end(s), back_inserter(v), [](char c) {
      if(c == ' ') return 36;
      if(isdigit(c)) return c - '0' + 26;
      return c - 'A';
  });
  while(size(v) % n) {
    v.push_back(36);
  }

  //cerr << "mat:\n" << mat << nl;

  string out;
  for(int i=0; i<size(v); i+=n) {
    vector res = mat * vector(begin(v) + i, begin(v) + i + n);
    //cerr << "AT " << res << " = MAT * " << vector(begin(v) + i, begin(v) + i + n) << nl;
    for(Int it : res) {
      if(it.value() == 36) out.push_back(' ');
      else if(it.value() < 26) out.push_back('A' + it.value());
      else out.push_back('0' + it.value() - 26);
    }
  }
  cout << out << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
