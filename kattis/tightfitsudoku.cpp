#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

#define CHECK \
  char a = s[0]; \
  if(a != '-') { \
    if(bm & 1 << (a - '0')) return false; \
    bm |= 1 << (a - '0'); \
  } \
  if(s.size() > 1) { \
    char b = s[2]; \
    if (b != '-') { \
      if(bm & 1 << (b - '0')) return false; \
      bm |= 1 << (b - '0'); \
      if (a != '-' && b < a) return false; \
    } \
  }

bool check_row(const vector<vector<string>>& g, [[maybe_unused]] int i, int j) {
  int bm = 0;
  for(int k=0; k<6; k++) {
    const string& s = g[k][j];
    CHECK
  }
  return true;
}

bool check_col(const vector<vector<string>>& g, int i, [[maybe_unused]] int j) {
  int bm = 0;
  for(int k=0; k<6; k++) {
    const string& s = g[i][k];
    CHECK
  }
  return true;
}

bool check_sqr(const vector<vector<string>>& g, int i, int j) {
  int si = i / 2 * 2;
  int sj = j / 3 * 3;
  int bm = 0;
  for(int ki=0; ki<2; ki++) {
    for(int kj=0; kj<3; kj++) {
      const string& s = g[si+ki][sj+kj];
      CHECK
    }
  }
  return true;
}

bool solve(vector<vector<string>>& g, int i, int j, int t) {
  if(i == 6) return true;
  if(j == 6) return solve(g, i+1, 0, 0);
  if(2*t >= g[i][j].size()) return solve(g, i, j+1, 0);
  if(g[i][j][2*t] != '-') return solve(g, i, j, t+1);

  for(int v=1; v<=9; v++) {
    g[i][j][2*t] = v + '0';
    if(check_row(g, i, j)
        && check_col(g, i, j)
        && check_sqr(g, i, j)
        && solve(g, i, j, t+1)) {
      return true;
    }
  }
  g[i][j][2*t] = '-';
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  auto g = cin.read<string>(6, 6);
  assert(solve(g, 0, 0, 0));
  for(int i=0; i<6; i++) {
    for(int j=0; j<6; j++) {
      cout << g[i][j] << " ";
    }
    cout << nl;
  }

  return 0;
}
