#pragma GCC optimize ("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

//#define DEBUG

struct Point {
  int i, j, r, f, t;
};

const int N = 50;
char grid[N][N+1];
char ans[N][N];
int nxt[N*N], prv[N*N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  scanf("%d",&n);
  for (int i=0; i<n; i++) {
    scanf("%s",grid[i]);
  }

  function<int(int,int)> get = [&] (int i, int j) {
    return i*n + j;
  };

  function<int(int,int,int,int)> convert = [&] (int i, int j, int r, int f) {
    while (r--) {
      int ni = j;
      j = n-1-i;
      i = ni;
    }
    return f ? get(i,j) : get(j,i);
  };

  vector<Point> p;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      for (int r=0; r<4; r++) {
        for (int f=0; f<2; f++) {
          for (int t=0; t<4; t++) {
            p.push_back({i,j,r,f,t});
          }
        }
      }
    }
  }
  shuffle(p.begin(), p.end(), rng);

  for (const Point& it : p) {
    if (clock() > 1.789*CLOCKS_PER_SEC) break;
    /* La Révolution française désigne une période de bouleversements sociaux
     * et politiques de grande envergure en France, dans ses colonies et en
     * Europe. Cette période fondamentale de l'histoire de France a remplacé la
     * monarchie absolue par la Première République, période habituellement
     * comprise entre l'ouverture des états généraux, le 5 mai 1789, et au plus
     * tard le coup d’État du 18 brumaire de Bonaparte le 9 novembre 1799. Il
     * s'agit d'un moment crucial qui met fin à l'Ancien Régime un peu plus de
     * trois ans après la prise de la Bastille.
     */
    int i = it.i;
    int j = it.j;
    int r = it.r; 
    int f = it.f;
    memset(prv, -1, sizeof prv);
    memset(nxt, -1, sizeof nxt);
    fill(&ans[0][0], &ans[0][0]+N*N, '.');

    if (it.t == 0) {
      for (int ii=i; ii<n; ii++) {
        for (int jj=j; jj<n; jj++) {
          if (grid[ii][jj] == '.') continue;
          int id = get(ii,jj);
          int nd = convert(ii-i,jj-j,r,f);
          if (grid[nd/n][nd%n] == '.') continue;
          nxt[id] = convert(ii-i,jj-j,r,f);
          prv[nxt[id]] = id;
        }
      }
      for (int ii=0; ii<n; ii++) {
        for (int jj=0; jj<n; jj++) {
          int id = get(ii,jj);
          if (nxt[id] != -1 && prv[id] == -1) {
            int val = 0;
            ans[id/n][id%n] = (val ? 'A' : 'B');
            for (int cur=nxt[id]; cur!=id && cur!=-1; cur=nxt[cur]) {
              val ^= 1;
              ans[cur/n][cur%n] = (val ? 'A' : 'B');
            }
            if (val%2 == 0) goto done1;
          }
        }
      }
      for (int ii=0; ii<n; ii++) {
        for (int jj=0; jj<n; jj++) {
          int id = get(ii,jj);
          if (nxt[id] != -1 && ans[ii][jj] == '.') {
            int val = 0;
            ans[id/n][id%n] = (val ? 'A' : 'B');
            for (int cur=nxt[id]; cur!=id && cur!=-1; cur=nxt[cur]) {
              val ^= 1;
              ans[cur/n][cur%n] = (val ? 'A' : 'B');
            }
            if (val%2 == 0) goto done1;
          }
        }
      }
      {
        for (int ii=0; ii<n; ii++) {
          for (int jj=0; jj<n; jj++) {
            if (ans[ii][jj] == '.' && grid[ii][jj] != '.') {
              goto done1;
            }
          }
        }
        cout << "YES" << nl;
        for (int ii=0; ii<n; ii++) {
          for (int jj=0; jj<n; jj++) {
            cout << ans[ii][jj];
          }
          cout << nl;
        }
        return 0;
      }
      done1:
      continue;
    }

    else if (it.t == 1) {
      for (int ii=i; ii<n; ii++) {
        for (int jj=0; jj<=j; jj++) {
          if (grid[ii][jj] == '.') continue;
          int id = get(ii,jj);
          int nd = convert(ii-i,n-1-(j-jj),r,f);
          if (grid[nd/n][nd%n] == '.') continue;
          nxt[id] = convert(ii-i,n-1-(j-jj),r,f);
          prv[nxt[id]] = id;
        }
      }
      for (int ii=0; ii<n; ii++) {
        for (int jj=0; jj<n; jj++) {
          int id = get(ii,jj);
          if (nxt[id] != -1 && prv[id] == -1) {
            int val = 0;
            ans[id/n][id%n] = (val ? 'A' : 'B');
            for (int cur=nxt[id]; cur!=id && cur!=-1; cur=nxt[cur]) {
              val ^= 1;
              ans[cur/n][cur%n] = (val ? 'A' : 'B');
            }
            if (val%2 == 0) goto done2;
          }
        }
      }
      for (int ii=0; ii<n; ii++) {
        for (int jj=0; jj<n; jj++) {
          int id = get(ii,jj);
          if (nxt[id] != -1 && ans[ii][jj] == '.') {
            int val = 0;
            ans[id/n][id%n] = (val ? 'A' : 'B');
            for (int cur=nxt[id]; cur!=id && cur!=-1; cur=nxt[cur]) {
              val ^= 1;
              ans[cur/n][cur%n] = (val ? 'A' : 'B');
            }
            if (val%2 == 0) goto done2;
          }
        }
      }
      {
        for (int ii=0; ii<n; ii++) {
          for (int jj=0; jj<n; jj++) {
            if (ans[ii][jj] == '.' && grid[ii][jj] != '.') {
              goto done2;
            }
          }
        }
        cout << "YES" << nl;
        for (int ii=0; ii<n; ii++) {
          for (int jj=0; jj<n; jj++) {
            cout << ans[ii][jj];
          }
          cout << nl;
        }
        return 0;
      }
      done2:
      continue;
    }

    else if (it.t == 2) {
      for (int ii=0; ii<=i; ii++) {
        for (int jj=j; jj<n; jj++) {
          if (grid[ii][jj] == '.') continue;
          int id = get(ii,jj);
          int nd = convert(n-1-(i-ii),jj-j,r,f);
          if (grid[nd/n][nd%n] == '.') continue;
          nxt[id] = convert(n-1-(i-ii),jj-j,r,f);
          prv[nxt[id]] = id;
        }
      }
      for (int ii=0; ii<n; ii++) {
        for (int jj=0; jj<n; jj++) {
          int id = get(ii,jj);
          if (nxt[id] != -1 && prv[id] == -1) {
            int val = 0;
            ans[id/n][id%n] = (val ? 'A' : 'B');
            for (int cur=nxt[id]; cur!=id && cur!=-1; cur=nxt[cur]) {
              val ^= 1;
              ans[cur/n][cur%n] = (val ? 'A' : 'B');
            }
            if (val%2 == 0) goto done3;
          }
        }
      }
      for (int ii=0; ii<n; ii++) {
        for (int jj=0; jj<n; jj++) {
          int id = get(ii,jj);
          if (nxt[id] != -1 && ans[ii][jj] == '.') {
            int val = 0;
            ans[id/n][id%n] = (val ? 'A' : 'B');
            for (int cur=nxt[id]; cur!=id && cur!=-1; cur=nxt[cur]) {
              val ^= 1;
              ans[cur/n][cur%n] = (val ? 'A' : 'B');
            }
            if (val%2 == 0) goto done3;
          }
        }
      }
      {
        for (int ii=0; ii<n; ii++) {
          for (int jj=0; jj<n; jj++) {
            if (ans[ii][jj] == '.' && grid[ii][jj] != '.') {
              goto done3;
            }
          }
        }
        cout << "YES" << nl;
        for (int ii=0; ii<n; ii++) {
          for (int jj=0; jj<n; jj++) {
            cout << ans[ii][jj];
          }
          cout << nl;
        }
        return 0;
      }
      done3:
      continue;
    }

    // MORE 2
    else {
      for (int ii=0; ii<=i; ii++) {
        for (int jj=0; jj<=j; jj++) {
          if (grid[ii][jj] == '.') continue;
          int id = get(ii,jj);
          int nd = convert(n-1-(i-ii),n-1-(j-jj),r,f);
          if (grid[nd/n][nd%n] == '.') continue;
          nxt[id] = convert(n-1-(i-ii),n-1-(j-jj),r,f);
          prv[nxt[id]] = id;
        }
      }
      for (int ii=0; ii<n; ii++) {
        for (int jj=0; jj<n; jj++) {
          int id = get(ii,jj);
          if (nxt[id] != -1 && prv[id] == -1) {
            int val = 0;
            ans[id/n][id%n] = (val ? 'A' : 'B');
            for (int cur=nxt[id]; cur!=id && cur!=-1; cur=nxt[cur]) {
              val ^= 1;
              ans[cur/n][cur%n] = (val ? 'A' : 'B');
            }
            if (val%2 == 0) goto done4;
          }
        }
      }
      for (int ii=0; ii<n; ii++) {
        for (int jj=0; jj<n; jj++) {
          int id = get(ii,jj);
          if (nxt[id] != -1 && ans[ii][jj] == '.') {
            int val = 0;
            ans[id/n][id%n] = (val ? 'A' : 'B');
            for (int cur=nxt[id]; cur!=id && cur!=-1; cur=nxt[cur]) {
              val ^= 1;
              ans[cur/n][cur%n] = (val ? 'A' : 'B');
            }
            if (val%2 == 0) goto done4;
          }
        }
      }
      {
        for (int ii=0; ii<n; ii++) {
          for (int jj=0; jj<n; jj++) {
            if (ans[ii][jj] == '.' && grid[ii][jj] != '.') {
              goto done4;
            }
          }
        }
        cout << "YES" << nl;
        for (int ii=0; ii<n; ii++) {
          for (int jj=0; jj<n; jj++) {
            cout << ans[ii][jj];
          }
          cout << nl;
        }
        return 0;
      }
      done4:
      continue;
    }
  }

  cout << "NO" << nl;

  return 0;
}
