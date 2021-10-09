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
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 50;
ll adj[N][N], mat[N][N], res[N][N];

void multiply(int n, ll r[N][N], ll a[N][N], ll b[N][N]) {
  For(i,n) {
    For(j,n) {
      r[i][j] = 0;
      For(k,n) {
        r[i][j] += a[i][k] * b[k][j] % MOD;
      }
      r[i][j] %= MOD;
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n; ll k;
  cin >> n >> k;

  For(i,n) {
    For(j,n) {
      cin >> adj[i][j];
      res[i][j] = (i==j);
    }
  }

  for ( ; k>0; k/=2) {
    if (k&1) {
      multiply(n, mat, res, adj);
      swap(res, mat);
    }
    multiply(n, mat, adj, adj);
    swap(adj, mat);
  }

  ll ans = 0;
  For(i,n) {
    For(j,n) {
      ans += res[i][j];
    }
  }
  cout << ans % MOD << nl;

  return 0;
}

