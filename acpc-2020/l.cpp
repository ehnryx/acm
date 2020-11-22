#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag() < b.imag() - EPS ||
    (a.imag() < b.imag() + EPS && a.real() < b.real() - EPS);
}

vector<pt> chull(vector<pt> p) {
  sort(p.begin(), p.end(), cmp_lex_i);
  int top=0, bot=1, n=p.size();
  vector<pt> ch(2*n);
  for(int i=0, d=1; i<n && i>=0; i+=d) {
    while(top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if(i==n-1) d = -1, bot = top;
  }
  ch.resize(max(1, top-1));
  return ch;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<string> g(n);
  for(int i=0; i<n; i++) {
    cin >> g[i];
  }

  if(n == 1) {
    if(g[0][0] == '1') {
      cout << 4 << nl;
    } else {
      cout << 0 << nl;
    }
    return 0;
  }

  vector<pt> v;
  ld mid = (ld)(n-1)/2;
  pt center(mid, mid);
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(g[i][j] == '1') {
        pt pos(i, j);
        pos = center + (pos - center) / (1 - (ld)1/n);
        v.push_back(pos);
      }
    }
  }

  vector<pt> hull = chull(v);
  int m = hull.size();
  ld ans = 0;
  for(int i=m-1, j=0; j<m; i=j++) {
    ans += abs(hull[i] - hull[j]);
  }
  cout << ans << nl;

  return 0;
}
