#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

#define int long long

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e5+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e4+1;

/*
struct BIT {
  ll f[N];
  BIT() { memset(f, 0, sizeof f); }
  void update(int x, int v) {
    for ( ; x<N; x+=x&-x) {
      f[x] += v;
    }
  }
  void update(int l, int r, int v) {
    update(l,v);
    update(r+1,-v);
  }
  ll query(int x) {
    ll res = 0;
    for ( ; x; x-=x&-x) {
      res += f[x];
    }
    return res;
  }
};
BIT segt[2];
*/

struct Dumb {
  ll a[N];
  Dumb() { memset(a, 0, sizeof a); }
  void update(int l, int r, int v) {
    assert(l<=r);
    for (int i=l; i<=r; i++) {
      a[i] += v;
    }
  }
  ll query(int x) {
    return a[x];
  }
};
Dumb segt[2];

const int M = 7;
ll mat[M][M], res[M][M], tmp[M][M];

void multiply(int n, ll r[][M], ll a[][M], ll b[][M]) {
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      r[i][j] = 0;
      for (int k=0; k<n; k++) {
        r[i][j] += a[i][k] * b[k][j] % MOD;
      }
      r[i][j] %= MOD;
    }
  }
}

int solve(ll a, ll b) {
  b %= 7;
  memset(mat, 0, sizeof mat);
  for (int i=0; i<b; i++) mat[0][i] = 1;
  for (int i=1; i<b; i++) mat[i][i-1] = 1;
  memset(res, 0, sizeof res);
  for (int i=0; i<b; i++) res[i][i] = 1;

  for (a-=b; a>0; a/=2) {
    if (a&1) {
      multiply(b, tmp, res, mat);
      swap(tmp, res);
    }
    multiply(b, tmp, mat, mat);
    swap(tmp, mat);
  }

  ll r = 0;
  for (int i=0; i<b; i++) {
    r += res[0][i];
  }
  if (b==0) assert(r==0);
  if (b==1) assert(r==1);
  return r % MOD;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  segt[0].update(1,n,1);
  segt[1].update(1,n,1);
  for (int i=0; i<m; i++) {
    char c; int l, r, h;
    cin >> c >> l >> r >> h;
    int id = c-'a';
    if (l<=r) {
      segt[id].update(l,r,h);
    } else {
      segt[id].update(1,r,h);
      segt[id].update(l,n,h);
    }
  }

  ll ans = 0;
  for (int i=1; i<=n; i++) {
    ans += solve(segt[0].query(i), segt[1].query(i));
  }
  cout << ans << nl;

  return 0;
}
