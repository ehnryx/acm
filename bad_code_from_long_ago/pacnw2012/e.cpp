#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

bool validate(const vector<vector<int>> &r, int rings) {
  for (auto &v : r)
    for (int i : v)
      if (i == 0) {
        puts("INVALID: NULL RING");
        return 0;
      }
  for (auto &v : r)
    for (int i : v)
      if (i > rings || i < -rings) {
        puts("INVALID: RING MISSING");
        return 0;
      }
  for (auto &v : r) {
    vector<bool> vis(rings);
    for (int i : v) {
      if ((i > 0 && vis[i-1]) || (i < 0 && vis[-i-1])) {
        puts("INVALID: RUNE CONTAINS A REPEATED RING");
        return 0;
      }
      if (i > 0)
        vis[i-1] = 1;
      else vis[-i-1] = 1;
    }
  }
  return 1;
}


int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int g; cin >> g;
  while (g--) {
    int rings, runes; cin >> rings >> runes;
    vector<vector<int>> r(runes, vector<int>(3));
    for (int i = 0; i < runes; i++) {
      for (int j = 0; j < 3; j++)
        cin >> r[i][j];
      int dumb; cin >> dumb;
    }
    if (!validate(r, rings)) continue;
    bool good = 0;
    for (int i = 0; i < (1 << rings); i++) {
      bitset<32> b(i);
      for (auto &v : r) {
        bool g = 0;
        for (int j : v) {
          if (j < 0 && !b[-j-1]) {
            g = 1;
          } else if (j > 0 && b[j-1]) {
            g = 1;
          }
        }
        if (!g) goto bd;
      }
      puts("RUNES SATISFIED!");
      good = 1;
      break;
bd:
      ;
    }
    if (!good)
      puts("RUNES UNSATISFIABLE! TRY ANOTHER GATE!");
  }

  return 0;
}
