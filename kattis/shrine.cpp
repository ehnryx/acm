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



//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(1);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int div[7];
  ld dist[8765];
  int pts[8765];
  const ld r = 1000;
  const int BS = 20;
  const int MAGIC = 100;

  for (int w,n,d;;) {
    cin >> w;
    if (!w) break;
    cin >> n >> d;
    for (int i=0; i<d; i++) {
      cin >> div[i];
    }

    int p = 0;
    for (int i=0; i<n; i++) {
      bool hit = false;
      for (int j=0; j<d; j++) {
        hit |= (i%div[j] == 0);
      }
      if (hit) {
        pts[p++] = i;
      }
      dist[i] = 2*r*sin(M_PIl*i/n);
    }

    ld left = 0;
    ld right = 2*M_PIl*r;
    for (int bs=0; bs<BS; bs++) {
      ld mid = (left+right)/2;
      int mincnt = INF;
      for (int k=0; k<MAGIC; k++) {
        int s = pts[rng()%p];
        int cnt = 1;
        int pre = s;
        ld cur = 0;
        for (int it=1; it<n; it++) {
          int i = it+s; if (i>=n) i -= n;
          bool hit = false;
          for (int j=0; j<d; j++) {
            hit |= (i%div[j] == 0);
          }
          if (hit) {
            int id = i-pre; if (id<0) id += n;
            if (cur + dist[id] <= mid) {
              cur += dist[id];
            } else {
              cur = 0;
              cnt++;
            }
            pre = i;
          }
        }
        mincnt = min(mincnt, cnt);
      }
      if (mincnt > w) {
        left = mid;
      } else {
        right = mid;
      }
    }
    cout << 2*r + (left+right)/2 << nl;
  }

  return 0;
}
