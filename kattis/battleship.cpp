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

void solve(fast_input<>& cin) {
  int m, n, k;
  cin >> m >> n >> k;
  auto g = cin.read<char>(2, n, m);
  auto moves = cin.read<pair<int, int>>(k);

  vector<int> cnt(2);
  for(int t=0; t<2; t++) {
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        cnt[t] += g[t][i][j] == '#';
      }
    }
  }

  int turn = 1;
  for(auto [b, a] : moves) {
    a = n-1 - a; // reversed
    if(g[turn][a][b] == '#') {
      g[turn][a][b] = '_';
      cnt[turn]--;
      if(cnt[turn]) {
        continue; // hit
      }
    }
    turn ^= 1;
    if(turn && (cnt[0] == 0 || cnt[1] == 0)) {
      break;
    }
  }

  if((cnt[0] && cnt[1]) || (cnt[0] == cnt[1])) {
    cout << "draw" << nl;
  } else {
    cout << "player " << (cnt[0] ? "one" : "two") << " wins" << nl;
  }
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
    solve(cin);
  }

  return 0;
}
