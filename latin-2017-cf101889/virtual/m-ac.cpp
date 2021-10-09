#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 420;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int& x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x*10 + c-'0';
  if (sgn) x = -x;
}

struct suff_array {
  const int L; vi s; int i, skip, lvl;
  vector<vi> P; vector<pair<pii,int>> M;
  suff_array(const vi& s) : L(s.size()), s(s), P(1, vi(L,0)), M(L) {
    for (int i=0; i<L-(L==1); i++) P[0][i] = s[i];
    for (skip=1, lvl=1; skip<L; skip*=2, lvl++) {
      P.push_back(vi(L,0));
      for (int i=0; i<L; i++)
        M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i+skip] : -1000}, i};
      sort(M.begin(), M.end());
      for (int i=0; i<L; i++)
        P[lvl][M[i].second] = (i>0 && M[i].first==M[i-1].first) ?
          P[lvl][M[i-1].second] : i; 
    }
  }
  const vi& get_sarray() { return P.back(); }
  int lcp(int i, int j) {
    int len=0; if (i==j) return L-i;
    for (int k=P.size()-1; k>=0 && i<L && j<L; k--)
      if (P[k][i] == P[k][j]) { i += 1<<k; j += 1<<k; len += 1<<k; }
    return len;
  }
};

/*
struct suff_array {
  vi t, sa, inv, lcp; int N;
  suff_array(const vi& v) : N(v.size()) {
    sa.resize(N); t.resize(N+3); lcp.resize(N); inv.resize(N);
    for (int i = 0; i < N; i++) t[i] = v[i];
    if (N < 3) { if (N == 2) { sa[(t[0] < t[1])] = 1; } } // ?????
    else build(t, sa, N, 1<<10);
    genHeight(); }
  void build(vi& T, vi& sa, int n, int K) {
    int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
    vi r(n02 + 3), sa12(n02 + 3), r0(n0), sa0(n0);
    for (int i = 0, j = 0; i < n + n0 - n1; i++) if (i % 3 != 0) r[j++] = i;
    pass(r, sa12, T, 2, n02, K);
    pass(sa12, r, T, 1, n02, K);
    pass(r, sa12, T, 0, n02, K);
    int name = 0, c0 = -1, c1 = -1, c2 = -1;
    for (int i = 0; i < n02; i++) {
      if (T[sa12[i]] != c0 || T[sa12[i] + 1] != c1 || T[sa12[i] + 2] != c2) {
        name++;
        c0 = T[sa12[i]]; c1 = T[sa12[i] + 1]; c2 = T[sa12[i] + 2]; }
      r[(sa12[i] % 3 == 1 ? 0 : n0) + sa12[i] / 3] = name; }
    if (name < n02) {
      build(r, sa12, n02, name);
      for (int i = 0; i < n02; i++) { r[sa12[i]] = i+1; }
    } else for (int i = 0; i < n02; i++) { sa12[r[i] - 1] = i; }
    for (int i = 0, j = 0; i < n02; i++)
      if (sa12[i] < n0) r0[j++] = 3 * sa12[i];
    pass(r0, sa0, T, 0, n0, K);
    for (int p = 0, t = n0 - n1, k = 0; k < n; k++) {
      int i = sa12[t] < n0 ? (sa12[t]*3+1) : ((sa12[t]-n0)*3+2), j = sa0[p];
      if (sa12[t] < n0 ? leq(T[i], r[sa12[t], + n0], 0, T[j], r[j / 3], 0)
          : leq(T[i], T[i+1], r[sa12[t]-n0+1], T[j], T[j + 1], r[j/3 + n0])) {
        sa[k] = i;
        if (++t == n02) for (k++; p < n0; sa[k++] = sa0[p++]) {}
      } else { sa[k] = j;
        if (++p == n0)
          for (k++; t < n02;
              sa[k++] = sa12[t] < n0 ? (sa12[t++]*3+1) : ((sa12[t++]-n0)*3+2)) {}
      } } }
  bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
    return a1<b1 || (a1==b1 && a2<b2) || (a1==b1 && a2==b2 && a3<=b3); }
  void pass(vi& a, vi& b, vi& r, int off, int n, int k) { vi c(k+1);
    for (int i = 0; i < n; c[r[a[i++] + off]]++);
    for (int i = 1; i <= k; i++) c[i] += c[i-1];
    for (int i = 0; i < n; c[r[a[i++] + off]]--);
    for (int i = 0; i < n; i++) { b[c[r[a[i] + off]]++] = a[i]; } }
  void genHeight() { for (int i = 0; i < N; i++) inv[sa[i]] = i;
    for (int i = 0, h = 0; i < N; i++) if (inv[i] > 0) {
      int j = sa[inv[i] - 1];
      while (i + h < N && j + h < N && t[i + h] == t[j + h]) h++;
      lcp[inv[i]] = h;
      if (h > 0) h--; } }
};
*/

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, k, a;
  //cin >> n;
  read(n);

  vector<int> s;
  vector<int> start;
  for (int i=0; i<n; i++) {
    start.push_back(s.size());
    //cin >> k;
    read(k);
    for (int j=0; j<k; j++) {
      //cin >> a;
      read(a);
      s.push_back(a);
    }
    s.push_back(INF);
  }
  n = s.size();

  //cerr << "s: "; for (int i : s) //cerr << i << " "; //cerr << nl;

  suff_array sa(s);
  const auto& id = sa.get_sarray();
  //auto id = sa.sa;

  vector<int> idx(n);
  for (int i=0; i<n; i++) {
    idx[id[i]] = i;
  }
  //cerr << "order: "; for (int i=0; i<n; i++) {
    //cerr << idx[i] << " "; }
  //cerr << nl;

  ll ans = 0;
  ll inv = 1;
  ll m = 365;
  for (int v=MOD-2; v>0; v/=2) {
    if (v&1) inv = inv*m % MOD;
    m = m*m % MOD;
  }

  ll mul = 1;
  for (int i : s) {
    if (i != INF) mul = mul*365 % MOD;
  }

  priority_queue<int,vector<int>,greater<int>> nxt;
  for (int i : start) {
    //cerr << "start " << i << ": " << id[i] << nl;
    nxt.push(id[i]);
  }

  while (!nxt.empty()) {
    int cur = nxt.top();
    nxt.pop();
    //cerr << " @ " << cur << " -> " << idx[cur] << " add " << s[idx[cur]] << nl;

    // update
    ans += s[idx[cur]]*mul;
    mul = mul*inv % MOD;

    if (s[idx[cur]+1] != INF) {
      nxt.push(id[idx[cur]+1]);
      //cerr << "push " << idx[cur]+1 << nl;
    }
  }

  cout << ans % MOD << nl;

  return 0;
}
