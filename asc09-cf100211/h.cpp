//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "tickets"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 36 + 1;
int m[N], name[N][4];

const int M = 10;
int dp[N][5][M][M][M][M]; // i, j, 1, 2, 3, 4
pair<int,int> pre[N][5][M][M][M][M]; // room, put
int ans[N][N], idx[N];

bool update(int& x, int v) {
  x = max(x, v);
  return x == v;
}

void recover(int n, int a, int b, int c, int d) {
  cout << dp[n][m[n]][a][b][c][d] << nl;
  vector<unordered_set<int>> groups(5);
  for(int i=0; i<9; i++) {
    if(i<a) groups[1].insert(i);
    else if(i<a+b) groups[2].insert(i);
    else if(i<a+b+c) groups[3].insert(i);
    else if(i<a+b+c+d) groups[4].insert(i);
  }

  while(n > 0) {
    assert(m[n] >= 0);
    if(!m[n]) {
      n--;
    }

    else {
      auto [room, put] = pre[n][m[n]][a][b][c][d];
      if(room == 1) {
        a--;
      } else if(room == 2) {
        b--;
        if(put == 1) a++;
      } else if(room == 3) {
        c--;
        if(put == 1) b++;
        if(put == 2) a++;
      } else if(room == 4) {
        d--;
        if(put == 1) c++;
        if(put == 2) b++;
        if(put == 3) a++;
      }

      int use = *groups[room].begin();
      groups[room].erase(use);
      for(int i=0; i<put; i++) {
        ans[use][idx[use]++] = name[n][--m[n]];
      }
      groups[room-put].insert(use);
    }
  }

  for(int i=0; i<9; i++) {
    for(int j=0; j<4; j++) {
      cout << ans[i][j] << " ";
    }
    cout << nl;
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  memset(dp, 0xff^0x3f, sizeof dp);
  dp[0][0][0][0][0][0] = 0;

  int n;
  cin >> n;
  for(int i=1; i<=n; i++) {
    int value;
    cin >> m[i];
    cin >> value;
    for(int j=0; j<m[i]; j++) {
      cin >> name[i][j];
    }

    for(int a=0; a<M; a++) {
      for(int b=0; a+b<M; b++) {
        for(int c=0; a+b+c<M; c++) {
          for(int d=0; a+b+c+d<M; d++) {
            dp[i][0][a][b][c][d] = dp[i-1][m[i-1]][a][b][c][d];
          }
        }
      }
    }

    for(int j=1; j<=m[i]; j++) {
      for(int a=0; a<M; a++) {
        for(int b=0; a+b<M; b++) {
          for(int c=0; a+b+c<M; c++) {
            for(int d=0; a+b+c+d<M; d++) {
              if(a) {
                if(1<=j && update(dp[i][j][a][b][c][d], dp[i][j-1][a-1][b][c][d])) {
                  pre[i][j][a][b][c][d] = make_pair(1, 1);
                }
              }
              if(b) {
                if(1 <= j && update(dp[i][j][a][b][c][d], dp[i][j-1][a+1][b-1][c][d])) {
                  pre[i][j][a][b][c][d] = make_pair(2, 1);
                }
                if(2 <= j && update(dp[i][j][a][b][c][d], dp[i][j-2][a][b-1][c][d] + 2*1*value)) {
                  pre[i][j][a][b][c][d] = make_pair(2, 2);
                }
              }
              if(c) {
                if(1 <= j && update(dp[i][j][a][b][c][d], dp[i][j-1][a][b+1][c-1][d])) {
                  pre[i][j][a][b][c][d] = make_pair(3, 1);
                }
                if(2 <= j && update(dp[i][j][a][b][c][d], dp[i][j-2][a+1][b][c-1][d] + 2*1*value)) {
                  pre[i][j][a][b][c][d] = make_pair(3, 2);
                }
                if(3 <= j && update(dp[i][j][a][b][c][d], dp[i][j-3][a][b][c-1][d] + 3*2*value)) {
                  pre[i][j][a][b][c][d] = make_pair(3, 3);
                }
              }
              if(d) {
                if(1 <= j && update(dp[i][j][a][b][c][d], dp[i][j-1][a][b][c+1][d-1])) {
                  pre[i][j][a][b][c][d] = make_pair(4, 1);
                }
                if(2 <= j && update(dp[i][j][a][b][c][d], dp[i][j-2][a][b+1][c][d-1] + 2*1*value)) {
                  pre[i][j][a][b][c][d] = make_pair(4, 2);
                }
                if(3 <= j && update(dp[i][j][a][b][c][d], dp[i][j-3][a+1][b][c][d-1] + 3*2*value)) {
                  pre[i][j][a][b][c][d] = make_pair(4, 3);
                }
                if(4 <= j && update(dp[i][j][a][b][c][d], dp[i][j-4][a][b][c][d-1] + 4*3*value)) {
                  pre[i][j][a][b][c][d] = make_pair(4, 4);
                }
              }
            }
          }
        }
      }
    }
  }

  int best = 0;
  for(int a=0; a<M; a++) {
    for(int b=0; a+b<M; b++) {
      for(int c=0; a+b+c<M; c++) {
        for(int d=0; a+b+c+d<M; d++) {
          best = max(best, dp[n][m[n]][a][b][c][d]);
        }
      }
    }
  }

  for(int a=0; a<M; a++) {
    for(int b=0; a+b<M; b++) {
      for(int c=0; a+b+c<M; c++) {
        for(int d=0; a+b+c+d<M; d++) {
          if(best == dp[n][m[n]][a][b][c][d]) {
            recover(n, a, b, c, d);
            return 0;
          }
        }
      }
    }
  }

  assert(false);

  return 0;
}
