#include <bits/stdc++.h>
using namespace std;

#define PRINT_NEGATIVES
#include "../../lca/math/matrix.h"
#include "../../lca/number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  string line;
  getline(cin, line);
  unordered_map<string, int> remap;
  int rid = 0;
  vector<vector<int>> rows;
  for(int i=0; i<n; i++) {
    getline(cin, line);
    istringstream in(line);
    vector<int> row;
    int sgn = 1;
    int left = 1;
    for(string s; in >> s; ) {
      if(s == "*") {
        sgn = 1;
      } else if(s == "/") {
        sgn = -1;
      } else if(s == "=") {
        sgn = 1;
        left = -1;
      } else if(s != "1") {
        if(!remap.count(s)) remap[s] = ++rid;
        row.push_back(sgn * left * remap[s]);
      }
    }
    rows.emplace_back(move(row));
  }

  matrix<Int> mat(n, rid);
  for(int i=0; i<n; i++) {
    for(int v : rows[i]) {
      mat[i][abs(v) - 1] += v / abs(v);
    }
  }
  cerr << "Matrix\n" << mat << nl;

  mat.rref();
  cerr << "RREF\n" << mat << nl;

  for (const auto& row : mat) {
    int nonzero = 0;
    for (const auto& v : row) {
      nonzero += (v != 0);
    }
    if (nonzero == 1) {
      cout << "invalid" << nl;
      return 0;
    }
  }
  cout << "valid" << nl;

  return 0;
}
