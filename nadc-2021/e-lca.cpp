#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#define USE_INT128
#define USE_RATIONAL_POINTS

#include "../../lca/numbers/fraction.h"
#include "../../lca/geometry2d/point.h"
#include "../../lca/geometry2d/general.h"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-13L;
random_device _rd; mt19937 rng(_rd());

using F = fraction<__int128, true>;
using P = point<F>;

const int N = 12;
pair<P,P> segment[N][N][N];
bool exists[N][N][N];
bool intersect[N][N][N][N][N][N];

bool valid(const vector<int>& v, int i, int j, int k) {
  if(!exists[i][j][k]) return false;
  for(int s=2; s<size(v); s++) {
    if(v[s-1] == i || v[s-1] == j || v[s-1] == k) continue;
    if(intersect[i][j][k][v[s-1]][v[s]][v[s-2]]) return false;
  }
  return true;
}

int solve(int bm, vector<int>& order) {
  int n = size(order);
  if(bm == 0) {
    return valid(order, order[n-1], order[n-2], order[0])
      && valid(order, order[0], order[1], order[n-1]);
  }
  int res = 0;
  for(int i=0; i<N; i++) {
    if(!(bm & 1<<i)) continue;
    if(n < 2 || valid(order, order[n-1], order[n-2], i)) {
      order.push_back(i);
      res += solve(bm ^ 1<<i, order);
      order.pop_back();
    }
  }
  return res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<pair<P,P>> lines;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    lines.emplace_back(P(F(a), F(b)), P(F(x), F(y)));
  }

  vector<tuple<int,int,int>> sid;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(parallel(lines[i].first, lines[i].second, lines[j].first, lines[j].second)) continue;
      for(int k=0; k<n; k++) {
        if(parallel(lines[i].first, lines[i].second, lines[k].first, lines[k].second)) continue;
        P ij = line_inter(lines[i].first, lines[i].second, lines[j].first, lines[j].second);
        P ik = line_inter(lines[i].first, lines[i].second, lines[k].first, lines[k].second);
        if(ij == ik) continue;
        segment[i][j][k] = pair(ij, ik);
        exists[i][j][k] = true;
        sid.emplace_back(i, j, k);
      }
    }
  }

  for(int s=0; s<size(sid); s++) {
    const auto& [i, j, k] = sid[s];
    const auto& [a, b] = segment[i][j][k];
    for(int t=0; t<s; t++) {
      const auto& [ii, jj, kk] = sid[t];
      const auto& [c, d] = segment[ii][jj][kk];
      bool x = seg_x_seg(a, b, c, d);
      intersect[i][j][k][ii][jj][kk] = x;
      intersect[ii][jj][kk][i][j][k] = x;
    }
  }

  vector<int> order;
  order.push_back(n-1);
  cout << solve((1<<(n-1)) - 1, order) / 2 << nl;

  return 0;
}
