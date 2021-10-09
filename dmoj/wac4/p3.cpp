//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Geo {
  ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
  ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
  pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
    return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }
  pt lsp_closest(const pt &a, const pt &b, const pt &p) {
    if (dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0)
      return abs(cp(b-a,p-a))<EPS ? p : line_inter(a,b,p,p+(a-b)*pt(0,1));
    return abs(a - p) < abs(b - p) ? a : b; }
}

const int N = 15;
ld dp[1<<N][N];
pt S[N], V[N];
int n, spd;

ld get_time(pt o, pt s, pt v) {
  if(abs(v) < EPS) {
    return abs(o-s) / spd;
  }

  s -= o;
  ld A = spd*spd - norm(v);
  ld B = -2 * Geo::dp(s, v);
  ld C = -norm(s);
  ld first = (-B - sqrt(B*B-4*A*C)) / (2*A);
  ld second = (-B + sqrt(B*B-4*A*C)) / (2*A);
  if(first > -EPS) return first;
  else return second;
}

ld solve(int bm, int s) {
  if(dp[bm][s] > -1) return dp[bm][s];
  if(__builtin_popcount(bm) == 1) {
    return dp[bm][s] = get_time(pt(0, 0), S[s], V[s]);
  }

  ld res = INFLL;
  for(int i=0; i<n; i++) {
    if(i == s || !(bm & 1<<i)) continue;
    ld t = solve(bm ^ 1<<s, i);
    pt cur = S[i] + V[i] * t;
    pt other = S[s] + V[s] * t;
    ld add = get_time(cur, other, V[s]);
    res = min(res, add + t);
  }
  assert(res > -1);
  return dp[bm][s] = res;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  cin >> n >> spd;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    S[i] = pt(a, b);
    V[i] = pt(x, y);
  }

  fill(&dp[0][0], &dp[0][0] + (1<<N)*N, -7);
  ld ans = INFLL;
  for(int i=0; i<n; i++) {
    ans = min(ans, solve((1<<n)-1, i));
  }
  cout << ans << nl;

  return 0;
}
