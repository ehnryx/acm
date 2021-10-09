//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const vector<int> di = { 1, -1, 0, 0 };
const vector<int> dj = { 0, 0, 1, -1 };

const int N = 1e5 + 1;
int dsu[N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
bool link(int i, int j) {
  i = find(i); j = find(j);
  if (i == j) return false;
  dsu[i] = j;
  return true;
}

const int M = 2e3 + 1;
int dist[M][M];
int val[M][M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  memset(dsu, -1, sizeof dsu);
  memset(dist, -1, sizeof dist);
  queue<tuple<int,int,int>> bfs;

  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    x *= 2; y *= 2;
    if (dist[x][y] == -1) {
      dist[x][y] = 0;
      val[x][y] = i;
      bfs.push(make_tuple(x, y, i));
    } else {
    }
  }

  int ans = 0;
  while (!bfs.empty()) {
    auto [i, j, t] = bfs.front();
    bfs.pop();
    for (int d=0; d<4; d++) {
      int ni = i + di[d];
      int nj = j + dj[d];
      if (ni<0 || nj<0 || ni>=M || nj>=M) continue;
      if (dist[ni][nj] == -1) {
        dist[ni][nj] = dist[i][j] + 1;
        val[ni][nj] = t;
        bfs.push(make_tuple(ni, nj, t));
      } else {
        if(link(t, val[ni][nj])) {
          ans += dist[ni][nj] + dist[i][j] + 1;
        }
      }
    }
  }
  cout << ans / 2 << nl;

  return 0;
}
