#pragma GCC optimize("O3")
#ifdef ONLINE_JUDGE
#pragma GCC target("sse4,avx2,tune=native")
#else
#pragma GCC target("sse4,avx2")
#endif

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 200;
const int S = 14;
const int M = 2*N/S + 1;

char g[2*N][2*N];
int dsu[2 * 2*N*N], sz[2 * 2*N*N];
int undo[2 * 2*N*N][4], uid;
void reset() {
  fill(begin(dsu), end(dsu), -1);
  fill(begin(sz), end(sz), 1);
}
int find(int i, bool compress) {
  if(dsu[i] == -1) return i;
  if(compress) return dsu[i] = find(dsu[i], compress);
  return find(dsu[i], compress);
}
bool link(int i, int j, bool compress) {
  i = find(i, compress);
  j = find(j, compress);
  if(i == j) return false;
  if(sz[i] > sz[j]) swap(i, j);
  if(!compress) {
    undo[uid][0] = i;
    undo[uid][1] = dsu[i];
    undo[uid][2] = j;
    undo[uid][3] = sz[j];
    uid++;
  }
  dsu[i] = j;
  sz[j] += sz[i];
  return true;
}
void unlink() {
  for(int k=uid-1; k>=0; k--) {
    dsu[undo[k][0]] = undo[k][1];
    sz[undo[k][2]] = undo[k][3];
  }
  uid = 0;
}

int rowcnt[2*N], blkcnt[M];
#define get(I, J) ((I)*m + (J))

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

  int n, m;
  cin >> n >> m;
  int dots = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
      g[i+n][j] = g[i][j+m] = g[i+n][j+m] = g[i][j];
      if(g[i][j] == '.') {
        dots += 1;
      }
    }
  }

  vector<pair<int,int>> ans;
  const int O = 2*n*m;
  for(int hs=0; hs<m; hs++) {
    reset();
    for(int i=0; i<2*n; i++) {
      rowcnt[i] = 0;
      for(int j=1; j<m; j++) {
        if(g[i][hs + j] == '#' || g[i][hs + j-1] == '#') continue;
        if(link(get(i, j), get(i, j-1), true)) {
          link(O + get(i, j), O + get(i, j-1), true);
          rowcnt[i] += 1;
        }
      }
    }

    for(int i=0; i<2*n; i+=S) {
      int id = i / S;
      blkcnt[id] = rowcnt[i];
      for(int k=1; k<S && i+k<2*n; k++) {
        blkcnt[id] += rowcnt[i+k];
        for(int j=0; j<m; j++) {
          if(g[i + k][hs + j] == '#' || g[i + k-1][hs + j] == '#') continue;
          blkcnt[id] += link(O + get(i + k, j), O + get(i + k-1, j), true);
        }
      }
    }

    for(int vs=0; vs<n; vs++) {
      int l = vs;
      int r = vs + n;
      int ls = (l + S-1) / S;
      int rs = r / S;
      int cnt = 0;

      if(ls >= rs) {
        cnt = rowcnt[l];
        for(int i=l+1; i<r; i++) {
          cnt += rowcnt[i];
          for(int j=0; j<m; j++) {
            if(g[i][hs + j] == '#' || g[i-1][hs + j] == '#') continue;
            cnt += link(get(i, j), get(i-1, j), false);
          }
        }
      }

      else {
        cnt = blkcnt[ls];
        // blocks
        for(int k=ls+1; k<rs; k++) {
          cnt += blkcnt[k];
          int i = k*S;
          for(int j=0; j<m; j++) {
            if(g[i][hs + j] == '#' || g[i-1][hs + j] == '#') continue;
            cnt += link(O + get(i, j), O + get(i-1, j), false);
          }
        }
        // left rows
        for(int i=l; i<ls*S; i++) {
          cnt += rowcnt[i];
          if(i == l) continue;
          for(int j=0; j<m; j++) {
            if(g[i][hs + j] == '#' || g[i-1][hs + j] == '#') continue;
            cnt += link(get(i, j), get(i-1, + j), false);
          }
        }
        // right rows
        for(int i=rs*S; i<r; i++) {
          cnt += rowcnt[i];
          if(i == rs*S) continue;
          for(int j=0; j<m; j++) {
            if(g[i][hs + j] == '#' || g[i-1][hs + j] == '#') continue;
            cnt += link(get(i, j), get(i-1, j), false);
          }
        }

        // join rows and blocks
        if(int i = ls*S; l < i) {
          for(int j=0; j<m; j++) {
            if(g[i][hs + j] == '#' || g[i-1][hs + j] == '#') continue;
            cnt += link(O + get(i, j), get(i-1, j), false);
          }
        }
        if(int i = rs*S; i < r) {
          for(int j=0; j<m; j++) {
            if(g[i][hs + j] == '#' || g[i-1][hs + j] == '#') continue;
            cnt += link(get(i, j), O + get(i-1, j), false);
          }
        }
      }

      if(cnt + 1 == dots) {
        ans.emplace_back(vs, hs);
      }
      unlink();
    }
  }

  sort(begin(ans), end(ans));
  cout << size(ans) << nl;
  for(auto [i, j] : ans) {
    cout << i << " " << j << nl;
  }

  return 0;
}
