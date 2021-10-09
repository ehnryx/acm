#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

const int N = 1e4+1;
int lcis[2][N];
int a[N], b[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  FOR(i,1,n) {
    cin >> a[i];
  }
  FOR(j,1,m) {
    cin >> b[j];
  }

  FOR(i,1,n) {
    int maxv = 0;
    FOR(j,1,m) {
      lcis[i&1][j] = lcis[(i&1)^1][j];
      if (a[i] == b[j]) lcis[i&1][j] = maxv+1;
      else if (a[i] > b[j]) maxv = max(maxv, lcis[(i&1)^1][j]);
    }
  }

  int ans = 0;
  FOR(j,1,m) {
    ans = max(ans, lcis[n&1][j]);
  }
  cout << 2*ans << nl;

  return 0;
}
