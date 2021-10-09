#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 5;

int dp[N][N][N][N][N][N];

int solve(int a, int b, int c, int d, int e, int f) {
  if (!(a+b) || !(c+d) || !(e+f)) return 0;
  if (dp[a][b][c][d][e][f] != -1) return dp[a][b][c][d][e][f];
  int ans = 0;
  for (int i = 0; i < a; i++) {
    ans |= !solve(i, b, c, d, e, f);
  }
  for (int i = 0; i < b; i++) {
    ans |= !solve(a, i, c, d, e, f);
  }
  for (int i = 0; i < c; i++) {
    ans |= !solve(a, b, i, d, e, f);
  }
  for (int i = 0; i < d; i++) {
    ans |= !solve(a, b, c, i, e, f);
  }
  for (int i = 0; i < e; i++) {
    ans |= !solve(a, b, c, d, i, f);
  }
  for (int i = 0; i < f; i++) {
    ans |= !solve(a, b, c, d, e, i);
  }
  for (int u = 1; u <= min(a, b); u++) {
    ans |= !solve(a-u, b-u, c, d, e, f);
  }
  for (int u = 1; u <= min(c, d); u++) {
    ans |= !solve(a, b, c-u, d-u, e, f);
  }
  for (int u = 1; u <= min(e, f); u++) {
    ans |= !solve(a, b, c, d, e-u, f-u);
  }
  return dp[a][b][c][d][e][f] = ans;
}
const int B = 105;
int dp2[B][B];

int solve(int x, int y) {
  if (dp2[x][y] != -1) return dp2[x][y];
  bitset<3*B> a; int mex = 0;
  for (int i = 0; i < x; i++) {
    a[solve(i, y)] = 1;
  }
  for (int i = 0; i < y; i++) {
    a[solve(x, i)] = 1;
  }
  for (int u = 1; u <= min(x, y); u++) {
    a[solve(x-u, y-u)] = 1;
  }
  while (a[mex]) mex++;
  return dp2[x][y] = mex;
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  memset(dp, -1, sizeof dp);
  memset(dp2, -1, sizeof dp2);
  set<vector<int>> win, lose;
  set<int> a, b;
  for (int a = 0; a < N; a++) {
    for (int b = 0; b < N; b++) {
      for (int c = a; c < N; c++) {
        for (int d = 0; d < N; d++) {
          for (int e = c; e < N; e++) {
            for (int f = 0; f < N; f++) {
              if (!(a + b) || !(c + d) || !(e + f)) continue;
              if (tie(a, b) > tie(c, d) || tie(c, d) > tie(e, f)) continue;
              if (solve(a, b, c, d, e, f)) {
                cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " ("
                  << solve(a, b) << " " << solve(c, d) << " " << solve(e, f) << ") "
                  << (solve(a, b) ^ solve(c, d) ^ solve(e, f)) << nl;
                vector<int> k = {min(2, solve(a, b)), min(2, solve(c, d)), min(2, solve(e, f))};
                sort(k.begin(), k.end());
                win.insert(k);
                if (lose.count(k)) {
                  //cerr << "BAD LOSE " << k[0] << " " << k[1] << " " << k[2] << nl;
                  //assert(0);
                }
              } else {
                vector<int> k = {min(2, solve(a, b)), min(2, solve(c, d)), min(2, solve(e, f))};
                sort(k.begin(), k.end());
                lose.insert(k);
                if (win.count(k)) {
                  //cerr << "BAD WIN " << k[0] << " " << k[1] << " " << k[2] << nl;
                  //assert(0);
                }
              }
            }
          }
        }
      }
    }
  }

  return 0;
}
