#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

vector<int> di = { 0, 0, 1, -1 };
vector<int> dj = { 1, -1, 0, 0 };

const int N = 500 + 2;
char g[N][N];
int mat[N][N], adj[N][N];

int get(int i, int j) {
  return i*501 + j;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    fill(&g[0][0], &g[0][0]+N*N, ' ');
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=m; j++) {
        cin >> g[i][j];
        adj[i][j] = 0;
        mat[i][j] = 0;
      }
    }

    bool ok = true;
    queue<pair<int,int>> white;
    int wcnt = 0;
    int bcnt = 0;
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=m; j++) {
        if(g[i][j] == 'B') {
          bcnt++;
          for(int d=0; d<4; d++) {
            if(g[i+di[d]][j+dj[d]] == 'W') {
              adj[i][j] |= 1<<d;
            }
          }
        } else if(g[i][j] == 'W') {
          wcnt++;
          for(int d=0; d<4; d++) {
            if(g[i+di[d]][j+dj[d]] == 'B') {
              adj[i][j] |= 1<<d;
            }
          }
          if(adj[i][j] == 0) {
            ok = false;
          } else if(__builtin_popcount(adj[i][j]) == 1) {
            white.push(make_pair(i, j));
            //cerr<<"init push "<<i<<" "<<j<<nl;
          }
        }
      }
    }

    if(!ok || wcnt != bcnt*2) {
      //cerr<<"pre bad"<<nl;
      cout << "NO" << nl;
      continue;
    }

loop:
    while(!white.empty()) {
      auto [i, j] = white.front();
      white.pop();
      assert(g[i][j] == 'W');
      //cerr<<"visit "<<i<<" "<<j<<" w/ "<<bitset<4>(adj[i][j])<<nl;

      int d = 0;
      for(; d<4; d++) {
        if(adj[i][j] & 1<<d) {
          break;
        }
      }
      if(d == 4) {
        ok = false;
        break;
      }
      assert(adj[i][j] == (1<<d));
      int bi = i + di[d];
      int bj = j + dj[d];
      assert(g[bi][bj] == 'B');

      mat[bi][bj]++;
      int op = ((1<<d & 0b11) ? (1<<d ^ 0b11) : (1<<d ^ 0b1100));
      adj[bi][bj] ^= op;
      adj[i][j] ^= 1<<d;

      int wi = bi + di[d];
      int wj = bj + dj[d];
      if(adj[bi][bj] & 1<<d) {
        assert(g[wi][wj] == 'W');
        adj[bi][bj] ^= 1<<d;
        adj[wi][wj] ^= op;
        if(__builtin_popcount(adj[wi][wj]) == 1) {
          //cerr<<"opp push "<<wi<<" "<<wj<<nl;
          white.push(make_pair(wi, wj));
        }
      }

      if(mat[bi][bj] == 2) {
        for(int e=0; e<4; e++) {
          if(adj[bi][bj] & 1<<e) {
            int ep = ((1<<e & 0b11) ? (1<<e ^ 0b11) : (1<<e ^ 0b1100));
            int ni = i + di[e];
            int nj = j + dj[e];
            assert(g[ni][nj] == 'W');
            adj[bi][bj] ^= 1<<e;
            adj[ni][nj] ^= ep;
            if(__builtin_popcount(adj[ni][nj]) == 1) {
              //cerr<<"done "<<wi<<" "<<wj<<nl;
              white.push(make_pair(ni, nj));
            }
          }
        }
        assert(adj[bi][bj] == 0);
      }
      assert(adj[i][j] == 0);
    }

    if(!ok) {
      cout << "NO" << nl;
      continue;
    } else {
      for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
          if(g[i][j] == 'W' && __builtin_popcount(adj[i][j]) > 0) {
            if(__builtin_popcount(adj[i][j]) == 2) {
              adj[i][j] ^= (adj[i][j] & -adj[i][j]);
              white.push(make_pair(i, j));
              ok = true;
              goto loop;
            } else {
              ok = false;
            }
          }
        }
      }
      if(!ok) {
        cout << "NO" << nl;
        continue;
      }
    }

    assert(ok);
    cout << "YES" << nl;
  }

}
