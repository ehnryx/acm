//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILE_IO
#define FILENAME "matrix"

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

const int N = 4000;

int to_num(char c) {
  if(isdigit(c)) return c - '0';
  else return c - 'A' + 10;
}

vector<bitset<N>> read_mat(int n) {
  vector<bitset<N>> a(n);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    for(int j=0; j<n; j++) {
      a[i][j] = to_num(s[j/4]) >> (3-j+j/4*4) & 1;
    }
  }
  return a;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILE_IO)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<bitset<N>> a = read_mat(n);
  vector<bitset<N>> b = read_mat(n);
  vector<bitset<N>> c = read_mat(n);

  vector<bitset<N>> prod(n);
  int k = max(1, (int)round(log2(n)));
  for(int s=0; s<n; s+=k) {
    int len = min(n, s+k) - s;
    vector<bitset<N>> res(1<<len);
    for(int i=1, bm=0; i<1<<len; i++) {
      int nbm = bm ^ 1 << __builtin_ctz(i);
      if(nbm >= 1 << len) for(;;);
      if(__builtin_popcount(bm ^ nbm) != 1) for(;;);
      int diff = __builtin_ctz(bm ^ nbm);
      res[nbm] = res[bm] ^ b[s+diff];
      bm = nbm;
    }
    for(int i=0; i<n; i++) {
      int bm = 0;
      for(int j=0; j<len; j++) {
        bm |= a[i][s+j] << j;
      }
      prod[i] ^= res[bm];
    }
  }

  if(c == prod) {
    cout << "YES" << nl;
  } else {
    cout << "NO" << nl;
  }

  return 0;
}
