#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/mod_int.h"
%:include "number/square_matrix.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  ll n;
  int goal;
  cin >> n >> goal;
  if(n == 1) {
    return void(cout << (goal < 10) << nl);
  }

  vector<int> residues = { 0 };
  for(int v = 100; v != 0; v = (v + 100) % 225) {
    residues.push_back(v);
  }
  assert(size(residues) == 9);

  auto get = [](int r, int d) {
    return r * 10 + d;
  };

  static constexpr int M = 90;
  square_matrix<Int, M> mat;
  for(int r=0; r<9; r++) {
    for(int d=0; d<10; d++) {
      for(int nd=0; nd<10; nd++) {
        if(d == nd) continue;
        int nr = (r + nd) % 9;
        int cur = get(r, d);
        int nxt = get(nr, nd);
        mat[nxt][cur] = 1;
      }
    }
  }
  auto res = mat.pow(n - 2);
  vector<Int> have(M);
  for(int i=0; i<M; i++) {
    have[i] = res[i][get(0, 0)];
  }

  Int ans = 0;
  for(int tail=0; tail<100; tail++) {
    if(tail / 10 == tail % 10) continue;
    int want = (goal + 225 - tail) % 225;
    auto it = find(begin(residues), end(residues), want);
    if(it == end(residues)) continue;
    int r = it - begin(residues);
    int avoid = tail / 10;
    for(int d=0; d<10; d++) {
      if(d == avoid) continue;
      ans += have[get(r, d)];
    }
  }
  cout << ans << nl;
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
