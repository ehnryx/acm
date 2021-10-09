#include <bits/stdc++.h>
using namespace std;
#define problem_name "digital"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 205;

const int b[10][3] = {
  {bitset<5>("11").to_ulong(), bitset<5>("101").to_ulong(), bitset<5>("11").to_ulong()}, // 0
  {bitset<5>("00").to_ulong(), bitset<5>("000").to_ulong(), bitset<5>("11").to_ulong()}, // 1
  {bitset<5>("10").to_ulong(), bitset<5>("111").to_ulong(), bitset<5>("01").to_ulong()}, // 2
  {bitset<5>("00").to_ulong(), bitset<5>("111").to_ulong(), bitset<5>("11").to_ulong()}, // 3
  {bitset<5>("01").to_ulong(), bitset<5>("010").to_ulong(), bitset<5>("11").to_ulong()}, // 4
  {bitset<5>("01").to_ulong(), bitset<5>("111").to_ulong(), bitset<5>("10").to_ulong()}, // 5
  {bitset<5>("11").to_ulong(), bitset<5>("111").to_ulong(), bitset<5>("10").to_ulong()}, // 6
  {bitset<5>("00").to_ulong(), bitset<5>("001").to_ulong(), bitset<5>("11").to_ulong()}, // 7
  {bitset<5>("11").to_ulong(), bitset<5>("111").to_ulong(), bitset<5>("11").to_ulong()}, // 8
  {bitset<5>("01").to_ulong(), bitset<5>("111").to_ulong(), bitset<5>("11").to_ulong()}, // 9
};

int w;
int grid[N];
int dp[N][2][1 << 4];
vector<int> poss[N][3];
int ans[N][3];

bool solve(int pos, bool carry, int bm) {
  if (pos < 0) return !carry && !bm;
  if (dp[pos][carry][bm] != -1) return dp[pos][carry][bm];
  for (int i : poss[pos][0]) {
    for (int j : poss[pos][1]) {
      for (int k : poss[pos][2]) {
        if ((i + j + carry) % 10 != k) continue;
        int cover = b[i][2] | (b[j][2] << 1) | (b[k][2] << 2);
        if ((cover | bm) != cover) continue;
        int vcover = b[i][1] | (b[j][1] << 1) | (b[k][1] << 2);
        if ((grid[pos*2+1] ^ vcover)) continue;

        int ncover = b[i][0] | (b[j][0] << 1) | (b[k][0] << 2);
        int nbm = grid[pos*2] ^ ncover;
        bool ncarry = (i + j + carry >= 10);
        if (solve(pos-1, ncarry, nbm)) {
          ans[pos][0] = i;
          ans[pos][1] = j;
          ans[pos][2] = k;
          return 1;
        }
      }
    }
  }
  return dp[pos][carry][bm] = 0;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(problem_name ".in", "r", stdin);
  freopen(problem_name ".out", "w", stdout);
#endif

  cin >> w;
  for (int i = 0; i < 9; i++) {
    if (i%2) {
      for (int j = 0; j < w+1; j++) {
        int k; cin >> k;
        grid[j*2] += (k << (i/2));
      }
    } else {
      for (int j = 0; j < w; j++) {
        int k; cin >> k;
        grid[j*2+1] += (k << (i/2));
      }
    }
  }
  // 2*i, 2*i+1, 2*i+2
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k <= 9; k++) {
        bool good = 1;
        for (int l = 0; l < 3; l++) {
          if ((grid[2*i+l] | (b[k][l] << j)) != grid[2*i+l]) {
            good = 0;
            break;
          }
        }
        if (good) {
          poss[i][j].push_back(k);
        }
      }
    }
  }
  memset(dp, -1, sizeof dp);
  if (!solve(w-1, 0, grid[2*w])) puts("NO");
  else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < w; i++) {
        cout << ans[i][j];
      }
      cout << nl;
    }
  }

  return 0;
}
