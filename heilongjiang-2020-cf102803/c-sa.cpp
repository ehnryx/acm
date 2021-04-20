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

namespace SuffixArray {
  const int L = 20; const int N = 1<<L; const int A = 1e9+7;
  int p[L+1][N]; pair<ll,int> m[N]; int last, n;
  /// replace pair<ll,int> ^here with pair<pair<int,int>,int> for 32-bit
  void build(const string& s) { n = s.size();
    if(n <= 1) { p[0][0] = last = 0; return; }
    for (int i = 0; i < n; i++) p[0][i] = s[i];
    for (int j = 1, v = 1; j < n; j *= 2, v++) {
      for (int i = 0; i < n; i++) {
        m[i] = { (ll)p[v-1][i] * A + (i+j<n ? p[v-1][i+j] : -1), i };
      } sort(m, m+n);
      for (int i = 0; i < n; i++) {
        p[v][m[i].second] = (i > 0 && m[i].first == m[i-1].first) ?
          p[v][m[i-1].second] : i; } last = v; } }
  int* idx() { return p[last]; }
  int lcp(int i, int j) {
    int len = 0; if (i == j) return n - i;
    for (int k = last; k >= 0 && i < n && j < n; k--) {
      if (p[k][i] == p[k][j]) { i += 1<<k; j += 1<<k; len += 1<<k; }
    } return len; }
}

struct suff_arr { // integer rep, suffix array, inverse, adjacent lcp
  using vi = vector<int>;
  vi t, sa, inv, lcp; int N;
  suff_arr(const string& s) : N(s.size()) { // begin-hash
    sa.resize(N); t.resize(N + 3); lcp.resize(N); inv.resize(N);
    for (int i = 0; i < N; i++) t[i] = s[i];
    if (N < 3) { if (N == 2) { sa[(t[0] < t[1])] = 1; } }
    else build(t, sa, N, 128);
    genHeight(); }
  void build(vi& T, vi& sa, int n, int K) {
    int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
    vi r(n02 + 3), sa12(n02 + 3), r0(n0), sa0(n0);
    for (int i = 0, j = 0; i < n + n0 - n1; i++)
      if (i % 3 != 0) r[j++] = i;
    pass(r, sa12, T, 2, n02, K);
    pass(sa12, r, T, 1, n02, K);
    pass(r, sa12, T, 0, n02, K);
    int name = 0, c0 = -1, c1 = -1, c2 = -1;
    for (int i = 0; i < n02; i++) {
      if (T[sa12[i]] != c0 || T[sa12[i]+1] != c1 || T[sa12[i]+2] != c2){
        name++;
        c0 = T[sa12[i]]; c1 = T[sa12[i] + 1]; c2 = T[sa12[i] + 2]; }
      r[(sa12[i] % 3 == 1 ? 0 : n0) + sa12[i] / 3] = name; }
    if (name < n02) {
      build(r, sa12, n02, name);
      for (int i = 0; i < n02; i++) { r[sa12[i]] = i+1; }
    } else for (int i = 0; i < n02; i++) { sa12[r[i] - 1] = i; }
    for (int i = 0, j = 0; i < n02; i++)
      if (sa12[i] < n0) r0[j++] = 3 * sa12[i];
    pass(r0, sa0, T, 0, n0, K); // end-hash: 6320ed
    for (int p = 0, t = n0 - n1, k = 0; k < n; k++) { // begin-hash
      int i = sa12[t]<n0 ? (sa12[t]*3+1) : ((sa12[t]-n0)*3+2), j=sa0[p];
      if (sa12[t]<n0 ? leq(T[i], r[sa12[t] + n0], 0, T[j], r[j / 3], 0)
        : leq(T[i], T[i+1], r[sa12[t]-n0+1], T[j], T[j+1], r[j/3+n0])) {
        sa[k] = i;
        if (++t == n02) for (k++; p < n0; sa[k++] = sa0[p++]) {}
      } else { sa[k] = j;
        if (++p == n0)
          for (k++; t < n02; sa[k++] = sa12[t] < n0
            ? (sa12[t++]*3+1) : ((sa12[t++]-n0)*3+2)) {}
      } } } // end-hash: 20a5a8
  bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
    return a1<b1 || (a1==b1 && a2<b2) || (a1==b1 && a2==b2 && a3<=b3); }
  void pass(vi& a, vi& b, vi& r, int off, int n, int k) { vi c(k + 1);
    for (int i = 0; i < n; c[r[a[i++] + off]]++);
    for (int i = 1; i <= k; i++) c[i] += c[i - 1];
    for (int i = 0; i < n; c[r[a[i++] + off]]--);
    for (int i = 0; i < n; i++) { b[c[r[a[i] + off]]++] = a[i]; } }
  void genHeight() { for (int i = 0; i < N; i++) inv[sa[i]] = i;
    for (int i = 0, h = 0; i < N; i++) if (inv[i] > 0) {
      int j = sa[inv[i] - 1];
      while (i + h < N && j + h < N && t[i + h] == t[j + h]) h++;
      lcp[inv[i]] = h;
      if (h > 0) h--; } }
};

const int L = 20;
const int N = 8e5 + 1;
int rmq[L][N];

template <class T>
int query(const T& sa, int a, int b) {
  int l = min(sa.inv[a], sa.inv[b]) + 1;
  int r = max(sa.inv[a], sa.inv[b]);
  int j = 31 - __builtin_clz(r - l + 1);
  return min(rmq[j][l], rmq[j][r-(1<<j)+1]);
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

  string s;
  cin >> s;
  int n = size(s);
  suff_arr sa(s);

  for(int i=0; i<n; i++) {
    rmq[0][sa.inv[i]] = sa.lcp[sa.inv[i]];
  }
  for(int j=1; j<L; j++) {
    for(int i=0; i+(1<<j)<=n; i++) {
      rmq[j][i] = min(rmq[j-1][i], rmq[j-1][i+(1<<(j-1))]);
    }
  }

  for(int d=1; d<=n/3; d++) {
    int len1 = query(sa, 0, d) / d * d;
    int b = d + len1;
    int len2 = query(sa, b, b+d) / d * d;
    int c = b+d + len2;
    int len3 = query(sa, c, c+d);
    if(len3 == n - (c+d)) {
      cout << s.substr(0, d) << " " << s.substr(b, d) << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
