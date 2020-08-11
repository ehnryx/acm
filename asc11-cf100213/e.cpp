//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "islands"

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

vector<int> dx = {0, 0, 1, 1, -1, -1};
vector<vector<int>> dy = {
  {1, -1, 0, -1, 0, -1},
  {1, -1, 0, 1, 0, 1},
};

const int O = 502;
const int N = 2*O + 1;
bool land[N][N];
int dsu[N*N], sz[N*N];
int find(int i) {
  if(!dsu[i]) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  i = find(i);
  j = find(j);
  if(i == j) return;
  sz[i] += sz[j];
  dsu[j] = i;
}


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

  int n, s;
  cin >> n >> s;

  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    x += O; y += O;
    if(land[x][y]) continue;

    vector<int> nbs;
    for(int d=0; d<6; d++) {
      int nx = x + dx[d];
      int ny = y + dy[x%2][d];
      if(land[nx][ny]) {
        nbs.push_back(find(nx*N + ny));
      }
    }
    sort(nbs.begin(), nbs.end());
    nbs.resize(unique(nbs.begin(), nbs.end()) - nbs.begin());
    int tot = 1;
    for(int j : nbs) {
      tot += sz[j];
    }
    if(tot > s) continue;

    land[x][y] = true;
    int u = x*N + y;
    sz[u] = 1;
    for(int j : nbs) {
      link(u, j);
    }
  }

  vector<int> ans;
  for(int i=1; i<N; i++) {
    for(int j=1; j<N; j++) {
      if(find(i*N + j) == i*N + j && sz[i*N + j]) {
        ans.push_back(sz[i*N + j]);
      }
    }
  }
  sort(ans.begin(), ans.end());

  cout << ans.size() << nl;
  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
