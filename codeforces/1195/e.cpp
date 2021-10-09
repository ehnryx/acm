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

const int M = 1<<12;
struct SegmentTree {
  int t[2*M];
  int query(int l, int r) {
    int res = INF;
    for (l+=M,r+=M; l<r; l/=2,r/=2) {
      if (l&1) res = min(res, t[l++]);
      if (r&1) res = min(res, t[--r]);
    }
    return res;
  }
};

void build(int n, SegmentTree& s, int a[]) {
  For(i,n) {
    s.t[i+M] = a[i];
  }
  DOWN(i,1,M-1) {
    s.t[i] = min(s.t[2*i], s.t[2*i+1]);
  }
}

const int N = 3000+1;
int g[N][N], h[N][N];
SegmentTree segt[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m, a, b;
  cin >> n >> m >> a >> b;

  int x, y, z;
  cin >> g[0][0] >> x >> y >> z;
  For(i,n) {
    For(j,m) {
      if (j>0) {
        g[i][j] = ((ll)g[i][j-1]*x + y) % z;
      } else if (i>0) {
        g[i][j] = ((ll)g[i-1][m-1]*x + y) % z;
      }
    }
  }

  For(i,n) {
    build(m, segt[i], g[i]);
  }

  For(i,n) {
    For(j,m-b+1) {
      h[j][i] = segt[i].query(j,j+b);
    }
  }

  For(j,m-b+1) {
    build(n, segt[j], h[j]);
  }

  ll ans = 0;
  For(j,m-b+1) {
    For(i,n-a+1) {
      ans += segt[j].query(i,i+a);
    }
  }
  cout << ans << nl;

  return 0;
}
