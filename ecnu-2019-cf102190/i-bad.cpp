#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
  int i, j, d;
  bool operator < (const Node& o) const {
    return d > o.d;
  }
};

const int N = 500+1;
const int M = 1e6+1;
int d[N][N];
set<pii> vals[M];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int T;
  cin >> T;

  while (T--) {
    int n;
    cin >> n;

    int m = n*1000 + 7;
    For(i,m) {
      vals[i].clear();
    }

    For(i,n) {
      For(j,n) {
        cin >> d[i][j];
      }
    }

    For(i,n) {
      if (d[i][i] == -1) d[i][i] = 0;
      For(j,i) {
        if (d[i][j] == -1) d[i][j] = d[j][i];
        if (d[j][i] == -1) d[j][i] = d[i][j];
      }
    }

    For(i,n) {
      if (d[i][i] != 0) goto bad;
      For(j,i) {
        if (d[i][j] != d[j][i]) goto bad;
        For(k,n) {
          if (d[i][k] == -1 || d[k][j] == -1) continue;
          if (d[i][j] == -1) {
            vals[d[i][k]+d[k][j]].insert(pii(i,j));
          } else if (d[i][j] > d[i][k] + d[k][j]) {
            goto bad;
          }
        }
      }
    }

    For(i,m) {
      for (const pii& it : vals[i]) {
        int a, b;
        tie(a,b) = it;
        if (d[a][b] == -1) {
          d[a][b] = d[b][a] = i;
          For(k,n) {
            if (d[a][k] == -1 && d[b][k] != -1) {
              vals[d[b][k]+i].insert(pii(a,k));
            } else if (d[a][k] != -1 && d[b][k] == -1) {
              vals[d[a][k]+i].insert(pii(b,k));
            }
          }
        }
      }
    }

    For(i,n) {
      For(j,i) {
        if (d[i][j] == -1) {
          d[i][j] = d[j][i] = INF/2;
        }
      }
    }

    For(i,n) {
      if (d[i][i] != 0) goto bad;
      For(j,i) {
        if (d[i][j] != d[j][i]) goto bad;
        For(k,n) {
          if (d[i][j] > d[i][k] + d[k][j]) goto bad;
        }
      }
    }

    cout << "YES" << nl;
    For(i,n) {
      For(j,n) {
        cout << d[i][j] << " ";
      }
      cout << nl;
    }
    continue;

    bad:
    cout << "NO" << nl;
  }

  return 0;
}
