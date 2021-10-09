//#pragma GCC optimize("O3")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef float ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Merge {
  int s, l, r;
};

const int N = 301;
const int M = 501;
vector<Merge> adj;
ld dp[M][M][N];

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
  cin >> n;

  unordered_map<string,int> id;
  vector<string> value;
  string x, y, z;
  for (int i=0; i<n; i++) {
    cin >> x >> y >> z;
    for (const string& s : {x,y,z}) {
      if (!id.count(s)) {
        id[s] = value.size();
        value.push_back(s);
      }
    }
    adj.push_back({id[z],id[x],id[y]});
  }
  int colours = value.size();

  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
        for (int c=0; c<colours; c++) {
          dp[i][j][c] = -1e42;
        }
      }
    }
    for (int i=0; i<n; i++) {
      cin >> x;
      while (x != "END") {
        ld v;
        cin >> v;
        if (id.count(x)) {
          dp[i][i][id[x]] = log(v);
        }
        cin >> x;
      }
    }

    for (int l=1; l<n; l++) {
      for (int i=0; i+l<n; i++) {
        for (int k=i; k<i+l; k++) {
          for (const Merge& it : adj) {
            dp[i][i+l][it.s] = max(dp[i][i+l][it.s], dp[i][k][it.l]+dp[k+1][i+l][it.r]);
            dp[i][i+l][it.s] = max(dp[i][i+l][it.s], dp[i][k][it.r]+dp[k+1][i+l][it.l]);
          }
        }
      }
    }

    dp[0][n-1][colours] = -1e42;
    int ans = colours;
    for (int c=0; c<colours; c++) {
      if (dp[0][n-1][c] > dp[0][n-1][ans]) {
        ans = c;
      }
    }
    if (ans == colours) {
      cout << "GAMEOVER" << nl;
    } else {
      cout << value[ans] << nl;
    }
  }

  return 0;
}
