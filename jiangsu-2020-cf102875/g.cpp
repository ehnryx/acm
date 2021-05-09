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
constexpr ll MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

bool valid(int n, vector<int> g) {
  for(int i=2; i<size(g); i++) {
    for(int j=0; j<n; j++) {
      int x = g[i-0] >> j & 1;
      int y = g[i-1] >> j & 1;
      int z = g[i-2] >> j & 1;
      if(x == y && y == z) return false;
      if(j >= 2) {
        x = g[i-0] >> (j-2) & 1;
        y = g[i-1] >> (j-1) & 1;
        z = g[i-2] >> (j-0) & 1;
        if(x == y && y == z) return false;
        x = g[i-0] >> (j-0) & 1;
        y = g[i-1] >> (j-1) & 1;
        z = g[i-2] >> (j-2) & 1;
        if(x == y && y == z) return false;
      }
    }
  }
  return true;
}

bool row_valid(int n, int bm) {
  for(int i=2; i<n; i++) {
    int x = bm >> (i-2) & 1;
    int y = bm >> (i-1) & 1;
    int z = bm >> (i-0) & 1;
    if(x == y && y == z) return false;
  }
  return true;
}

int solve_4(int n) {
  vector<vector<int>> good;
  for(int bm=0; bm<1<<4; bm++) {
    if(row_valid(4, bm)) {
      good.emplace_back(1, bm);
    }
  }
  for(int i=1; i<n; i++) {
    vector<vector<int>> cur;
    for(int bm=0; bm<1<<4; bm++) {
      if(!row_valid(4, bm)) continue;
      for(vector<int> g : good) {
        g.push_back(bm);
        if(valid(4, g)) {
          cur.push_back(g);
        }
      }
    }
    good = move(cur);
  }
  return size(good);
}

vector<vector<int>> mul(const vector<vector<int>>& a, const vector<vector<int>>& b) {
  int n = size(a);
  vector res(n, vector<int>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      for(int k=0; k<n; k++) {
        res[i][j] = (res[i][j] + (ll)a[i][k] * b[k][j]) % MOD;
      }
    }
  }
  return res;
}

int solve(int n, int m) {
  int len = 1 << (2 * m);
  vector mat(len, vector<int>(len));
  for(int a=0; a<1<<m; a++) {
    if(!row_valid(m, a)) continue;
    for(int b=0; b<1<<m; b++) {
      if(!row_valid(m, b)) continue;
      for(int c=0; c<1<<m; c++) {
        if(!row_valid(m, c)) continue;
        if(!valid(m, {a, b, c})) continue;
        // (ab -> bc) on row bc
        mat[b << m | c][a << m | b] = 1;
      }
    }
  }

  vector res(len, vector<int>(len));
  for(int i=0; i<len; i++) {
    res[i][i] = 1;
  }
  for(int e=n-2; e>0; e/=2, mat = mul(mat, mat)) {
    if(e&1) res = mul(res, mat);
  }

  vector<int> init(len);
  for(int a=0; a<1<<m; a++) {
    if(!row_valid(m, a)) continue;
    for(int b=0; b<1<<m; b++) {
      if(!row_valid(m, b)) continue;
      int key = a << m | b;
      init[key] = 1;
    }
  }

  int ans = 0;
  for(int i=0; i<len; i++) {
    for(int j=0; j<len; j++) {
      ans = (ans + (ll)res[i][j] * init[j]) % MOD;
    }
  }
  return ans;
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

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    if(n < m) swap(n, m);
    if(n == 1) {
      cout << 2 << nl;
    } else if(m > 4) {
      cout << 8 << nl;
    } else if(m == 4) {
      if(n > 8) {
        cout << 14 << nl;
      } else {
        cout << solve_4(n) << nl;
      }
    } else {
      cout << solve(n, m) << nl;
    }
  }

  return 0;
}
