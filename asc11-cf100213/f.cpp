//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "money"

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

const int N = 40;
int n[2], m[2];
char g[2][N][N];
bool mat[N][N];
int nxt[N][N];
pair<int,int> front[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  for(int t=0; t<2; t++) {
    cin >> n[t] >> m[t];
    for(int i=0; i<n[t]; i++) {
      for(int j=0; j<m[t]; j++) {
        cin >> g[t][i][j];
      }
    }
  }

  int best = 0;
  int height, width;
  int s1, s2, t1, t2;
  //for(int s=-N; s<N; s++) {
    //for(int t=-N; t<N; t++) {
  for(int s=-n[0]; s<n[1]; s++) {
    for(int t=-m[0]; t<m[1]; t++) {
      memset(mat, 0, sizeof mat);
      for(int i=0; i<n[0]; i++) {
        for(int j=0; j<m[0]; j++) {
          if(0 <= s+i && s+i < n[1] && 0 <= t+j && t+j < m[1]) {
            mat[i][j] = (g[0][i][j] == g[1][s+i][t+j]);
          }
        }
      }

      for(int i=0; i<N; i++) {
        for(int j=N-1; j>=0; j--) {
          nxt[i][j] = j;
          if(j+1<N && mat[i][j+1]) nxt[i][j] = nxt[i][j+1];
        }
      }

      for(int j=0; j<N; j++) {
        int rid = 0;
        for(int i=0; i<N; i++) {
          if(!mat[i][j]) {
            rid = 0;
            continue;
          }
          int top = i;
          while(rid > 0 && front[rid-1].second >= nxt[i][j]) {
            top = front[--rid].first;
          }
          front[rid++] = make_pair(top, nxt[i][j]);
          for(int k=0; k<rid; k++) {
            auto [x, y] = front[k];
            int h = i-x+1;
            int w = y-j+1;
            int area = h * w;
            if(area > best) {
              best = area;
              height = h;
              width = w;
              s1 = x + 1;
              t1 = j + 1;
              s2 = s + x + 1;
              t2 = t + j + 1;
            }
          }
        }
      }
    }
  }


  if(best == 0) {
    cout << 0 << " " << 0 << nl;
  } else {
    cout << height << " " << width << nl;
    cout << s1 << " " << t1 << nl;
    cout << s2 << " " << t2 << nl;
  }

  return 0;
}
