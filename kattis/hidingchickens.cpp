#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef pair<ld,ld> pdd;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void next_combination(int& v) {
  int t = v|(v-1);
  v = (t+1)|((~t&-~t)-1)>>(__builtin_ctz(v)+1);
}

ld dist(const pdd& a, const pdd& b) {
  return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  ld x, y;
  cin >> x >> y;
  pdd base(x,y);

  int n;
  cin >> n;
  vector<pdd> p;
  for (int i=0; i<n; i++) {
    cin >> x >> y;
    p.emplace_back(x,y);
  }

  ld dp[1<<n];
  fill(dp, dp+(1<<n), 1e42);
  dp[0] = 0;
  for (int b=1; b<=n; b++) {
    for (int it=(1<<b)-1; it<1<<n; next_combination(it)) {
      for (int i=0; i<n; i++) {
        if (!(1<<i&it)) continue;
        for (int j=0; j<=i; j++) {
          if (!(1<<j&it)) continue;
          int bm = 1<<i|1<<j;
          if (bm==it) {
            ld d = dist(p[i],p[j])+min(dist(p[i],base),dist(p[j],base));
            dp[it] = min(dp[it], dp[it^bm]+d);
          } else {
            ld d = dist(p[i],p[j])+dist(p[i],base)+dist(p[j],base);
            dp[it] = min(dp[it], dp[it^bm]+d);
          }
        }
      }
    }
  }
  cout << dp[(1<<n)-1] << nl;

  return 0;
}
