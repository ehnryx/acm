#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "math/matrix.h"
%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<37>;
using Matrix = matrix<Int>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  string s, t;
  getline(cin, s);
  getline(cin, s);
  getline(cin, t);

  auto encrypt = [](char c) {
    if(c == ' ') return 36;
    if(isdigit(c)) return c - '0' + 26;
    return c - 'A';
  };
  vector<Int> vs, vt;
  transform(begin(s), end(s), back_inserter(vs), encrypt);
  transform(begin(t), end(t), back_inserter(vt), encrypt);
  assert(size(s) == size(t));

  Matrix mat;
  for(int i=0; i<size(vs); i+=n) {
    for(int j=0; j<n; j++) {
      vector<Int> row(n*n + 1);
      row.back() = vt[i + j];
      for(int k=0; k<n; k++) {
        row[j*n + k] = vs[i + k];
      }
      mat.push_back(move(row));
    }
  }
  int rank = mat.solve();
  if(rank == -1) {
    cout << "No solution" << nl;
  } else if(rank < n*n) {
    cout << "Too many solutions" << nl;
  } else {
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        cout << mat.ans[i*n + j] << " ";
      }
      cout << nl;
    }
  }
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
