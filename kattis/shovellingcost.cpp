//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int di[] = { 1, -1, 0, 0 };
int dj[] = { 0, 0, 1, -1 };

const int N = 20 + 1;
char g[N][N];
int dist[4][N][N];
int apsp[N*N][N*N];
pair<int,int> start[4];

void go(int n, int m, int s, int t, int d[N][N]) {
  deque<pair<int,int>> bfs;
  d[s][t] = 0;
  bfs.push_back(make_pair(s, t));
  while(!bfs.empty()) {
    auto [i, j] = bfs.front();
    bfs.pop_front();
    for(int k=0; k<4; k++) {
      int ni = i + di[k];
      int nj = j + dj[k];
      if(ni<0 || nj<0 || ni>=n || nj>=m || d[ni][nj]<INF) continue;
      if(g[ni][nj] == '.') {
        d[ni][nj] = d[i][j];
        bfs.push_front(make_pair(ni, nj));
      } else if(g[ni][nj] == 'o') {
        d[ni][nj] = d[i][j] + 1;
        bfs.push_back(make_pair(ni, nj));
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(int n, m; cin >> n >> m && n; ) {
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        cin >> g[i][j];
        if('A' <= g[i][j] && g[i][j] <= 'D') {
          start[g[i][j]-'A'] = make_pair(i,j);
          g[i][j] = '.';
        }
      }
    }

    function<int(int,int)> get = [&](int i, int j) {
      return i*m + j;
    };

    memset(apsp, INF, sizeof apsp);
    for(int i=0; i<n*m; i++) {
      apsp[i][i] = 0;
    }
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        if(g[i][j] != 'o' && g[i][j] != '.') continue;
        for(int k=0; k<4; k++) {
          int ni = i + di[k];
          int nj = j + dj[k];
          if(ni<0 || nj<0 || ni>=n || nj>=m) continue;
          if(g[ni][nj] == 'o') {
            apsp[get(i,j)][get(ni,nj)] = 1;
          } else if(g[ni][nj] == '.') {
            apsp[get(i,j)][get(ni,nj)] = 0;
          }
        }
      }
    }

    for(int k=0; k<n*m; k++) {
      for(int i=0; i<n*m; i++) {
        for(int j=0; j<n*m; j++) {
          apsp[i][j] = min(apsp[i][j], apsp[i][k]+apsp[k][j]);
        }
      }
    }

    memset(dist, INF, sizeof dist);
    for(int i=0; i<4; i++) {
      go(n, m, start[i].first, start[i].second, dist[i]);
    }

    int ans = INF;
    for(int o=1; o<4; o++) {
      for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
          if(g[i][j] != 'o' && g[i][j] != '.') continue;
          for(int ii=0; ii<n; ii++) {
            for(int jj=0; jj<m; jj++) {
              if(g[ii][jj] != 'o' && g[ii][jj] != '.') continue;
              int left = dist[0][i][j] + dist[o][i][j];
              if(g[i][j] == 'o') left--;
              int right = 0;
              for(int c=1; c<4; c++) {
                if(c == o) continue;
                right += dist[c][ii][jj];
              }
              if(g[ii][jj] == 'o') right -= 2;
              ans = min(ans, left + right + apsp[get(i,j)][get(ii,jj)]);
            }
          }
        }
      }
    }

    assert(ans < INF);
    cout << ans << nl;
    cerr<<endl;
  }

  return 0;
}
