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

int convert(char c) {
  if(c == 'L') return 0;
  if(c == 'U') return 1;
  if(c == 'R') return 2;
  if(c == 'D') return 3;
  return 4;
}

bool update(unsigned& a, unsigned b) {
  a = min(a, b);
  return a == b;
}

unsigned cost(int x, int to) {
  int v = x & 0b11;
  if(v == x) return 1;
  if(v == to) return 3;
  if(v % 2 == to % 2) return 7;
  return 5;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  for(string s; cin >> s && s != "#"; ) {
    int n = s.size();

    vector dp(n + 1, vector(8, vector<unsigned>(8, -1)));
    vector par(n + 1, vector(8, vector<pair<int, int>>(8)));
    dp[0][0][2] = 0;

    for(int i=0; i<n; i++) {
      int to = convert(s[i]);
      for(int l=0; l<8; l++) {
        for(int r=0; r<8; r++) {
          if(dp[i][l][r] == -1) continue;
          int L = l & 0b11;
          int R = r & 0b11;
          assert(L != R);
          if(to == 4) {
            if(update(dp[i+1][L][R], dp[i][l][r])) {
              par[i+1][L][R] = pair(l, r);
            }
            for(int nxt=0; nxt<4; nxt++) {
              if(R != 0 && R != nxt) {
                if(update(dp[i+1][nxt|0b100][R], dp[i][l][r] + cost(l, nxt))) {
                  par[i+1][nxt|0b100][R] = pair(l, r);
                }
              }
              if(L != 2 && L != nxt) {
                if(update(dp[i+1][L][nxt|0b100], dp[i][l][r] + cost(r, nxt))) {
                  par[i+1][L][nxt|0b100] = pair(l, r);
                }
              }
            }
          } else if(L == to) {
            if(update(dp[i+1][L|0b100][R], dp[i][l][r] + cost(l, to))) {
              par[i+1][L|0b100][R] = pair(l, r);
            }
          } else if(R == to) {
            if(update(dp[i+1][L][R|0b100], dp[i][l][r] + cost(r, to))) {
              par[i+1][L][R|0b100] = pair(l, r);
            }
          } else {
            if(R != 0) {
              if(update(dp[i+1][to|0b100][R], dp[i][l][r] + cost(l, to))) {
                par[i+1][to|0b100][R] = pair(l, r);
              }
            }
            if(L != 2) {
              if(update(dp[i+1][L][to|0b100], dp[i][l][r] + cost(r, to))) {
                par[i+1][L][to|0b100] = pair(l, r);
              }
            }
          }
        }
      }
    }

    tuple<unsigned, int, int> at(-1, -1, -1);
    for(int l=0; l<8; l++) {
      for(int r=0; r<8; r++) {
        at = min(at, tuple(dp[n][l][r], l, r));
      }
    }
    //cerr << "cost: " << get<0>(at) << nl;
    assert(get<0>(at) != -1);

    for(int i=n, l=get<1>(at), r=get<2>(at); i>0; i--) {
      if(l & 0b100) {
        s[i-1] = 'L';
        assert(!(r & 0b100));
      } else if(r & 0b100) {
        s[i-1] = 'R';
        assert(!(l & 0b100));
      } else {
        assert(s[i-1] == '.');
      }
      tie(l, r) = par[i][l][r];
    }
    cout << s << nl;
  }

  return 0;
}
