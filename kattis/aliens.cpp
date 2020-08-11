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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

////////////////////////////////////////////////////////////////////////
// Range Minimum Query -- O(nlogn) to build, O(1) to query
// Maximum query is also possible
// The code is 0-indexed, change the loops in build to make it 1-indexed
// Query range is inclusive
// USAGE:
//  1. RMQ rmq(n);
//  2. rmq.build(vector containing the values);
//  3. rmq.query(l,r);  // range inclusive [l,r]
//*!
template <class T> struct RMQ {
    int lg;
    vector<vector<T>> rmq;
    RMQ(int n) {
        lg = 32 - __builtin_clz(n);
        rmq.resize(n, vector<T>(lg));
    }
    void set(int i, const T& v) {
        rmq[i][0] = v;
    }
    void build() {
        for (int j = 1; j < lg; j++)
            for (int i = 0; i+(1<<j)-1 < rmq.size(); i++)
                rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
    }
    T query(int l, int r) {
        if (l > r) swap(l, r);
        int j = 31 - __builtin_clz(r-l+1);
        return min(rmq[l][j], rmq[r-(1<<j)+1][j]);
    }
};
//*/

// get_sarray()[i] = idx of suffix s[i..L-1] in list of sorted suffixes
struct suff_array {
  const int L; string s; int i, skip, lvl;
  vector<vi> P; vector<pair<pii,int>> M;
  suff_array(const string &s) : L(s.size()), s(s), P(1, vi(L, 0)), M(L) {
    for (i = 0; i < L-(L==1); i++) P[0][i] = int(s[i]);
    for (skip = 1, lvl = 1; skip < L; skip *= 2, lvl++) {
      P.push_back(vi(L, 0));
      for (int i = 0; i < L; i++)
        M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i + skip] : -1000}, i};
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++)
        P[lvl][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
            P[lvl][M[i-1].second] : i; } }
  const vi& get_sarray() { return P.back(); }
  //returns len of longest common prefix of s[i...L-1] and s[j...L-1], O(lg L)
  int lcp(int i, int j) {
    int len = 0; if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
      if (P[k][i] == P[k][j]) { i += 1 << k; j += 1 << k; len += 1 << k; }
    return len; }
}; //! code adapted from the Stanford Team Notebook

//sa[i] is the starting index of the ith suffix in the sorted suffix array
//inv[i] is the ranking of s[i..L-1] in the sorted suffix array, inverse of sa
//lcp[i] is the lcp of suffix i-1 and i in the sorted suffix array, lcp[0] = 0
struct suff_arr { // integer rep, suffix array, inverse array, adjacent lcp
  vi t, sa, inv, lcp; int N;
  suff_arr(const string& s) : N(s.size()) {
    sa.resize(N); t.resize(N + 3); lcp.resize(N); inv.resize(N);
    for (int i = 0; i < N; i++) t[i] = s[i];
    if (N < 3) { if (N == 2) { sa[(t[0] > t[1])] = 1; } }
    else build(t, sa, N, 128);
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
      if (sa12[t] < n0 ? leq(T[i], r[sa12[t] + n0], 0, T[j], r[j / 3], 0)
          : leq(T[i], T[i+1], r[sa12[t]-n0+1], T[j], T[j + 1], r[j/3 + n0])) {
        sa[k] = i;
        if (++t == n02) for (k++; p < n0; sa[k++] = sa0[p++]) {}
      } else { sa[k] = j;
        if (++p == n0)
          for (k++; t < n02;
            sa[k++] = sa12[t] < n0 ? (sa12[t++]*3+1) : ((sa12[t++]-n0)*3+2)) {}
      } } }
  bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
    return a1<b1 || (a1==b1 && a2<b2) || (a1 == b1 && a2 == b2 && a3<=b3); }
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
}; //! from Antony at UCF

//const int N = 4e4+1;
//int id[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	for (int n;;) {
		cin >> n;
		if (!n) break;

		string s;
		cin >> s;
		int m = s.size();

		if (n==1) {
			cout << m << " " << 0 << nl;
			continue;
		}

		/* O(nlog^2)
		suff_array sa(s);
		const auto& idx = sa.get_sarray();
		for (int i=0; i<m; i++) {
			id[idx[i]] = i;
		}
		*/
		/* O(n) */
		suff_arr sa(s);
		const auto& id = sa.sa;
		const auto& lcp = sa.lcp;

		RMQ<int> window(m), index(m);
		for (int i=0; i<m; i++) {
			window.set(i,lcp[i]);
			index.set(i,-id[i]);
		}
		window.build();
		index.build();

		int len = 0;
		int last = -1;
		for (int i=n-1; i<m; i++) {
			int cur = window.query(i-n+2, i);
			int val = -index.query(i-n+1, i);
			if (cur == len) {
				last = max(last, val);
			}
			if (cur > len) {
				len = cur;
				last = val;
			}
		}

		if (len == 0) {
			cout << "none" << nl;
		} else {
			assert(last != -1);
			cout << len << " " << last << nl;
		}
	}

	return 0;
}
