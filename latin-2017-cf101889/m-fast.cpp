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

////////////////////////////////////////////////////////////////////////////////
// Suffix Array - O(N) construction, TESTED (SWERC09J)
////////////////////////////////////////////////////////////////////////////////
//sa[i] is the starting index of the ith suffix in the sorted suffix array
//inv[i] is the ranking of s[i..L-1] in the sorted suffix array, inverse of sa
//lcp[i] is the lcp of suffix i-1 and i in the sorted suffix array, lcp[0] = 0
struct suff_arr { // integer rep, suffix array, inverse array, adjacent lcp
	vi t, sa, inv, lcp; int N;
	suff_arr(const vi& s) : N(s.size()) {
		sa.resize(N); t.resize(N + 3); lcp.resize(N); inv.resize(N);
		for (int i = 0; i < N; i++) t[i] = s[i];
		if (N < 3) { if (N == 2) { sa[(t[0] < t[1])] = 1; } }
		else build(t, sa, N, 302);
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
	cin >> n;

	vi s;
	for (int i=0; i<n; i++) {
		cin >> k;
		for (int j=0; j<k; j++) {
			cin >> a;
			s.push_back(a);
		}
		s.push_back(301);
	}
	n = s.size();

	suff_arr sa(s);
	const auto& id = sa.sa;
	vi idx(n);
	for (int i=0; i<n; i++) {
		idx[id[i]] = i;
	}

	priority_queue<int,vi,greater<int>> front;
	for (int i=0; i<n; i++) {
		if (i==0 || s[i-1]==301) {
			front.push(idx[i]);
		}
	}

	ll ans = 0;
	while (!front.empty()) {
		int cur = front.top();
		front.pop();

		ans = (ans*365 + s[id[cur]]) % MOD;
		if (s[id[cur]+1] != 301) {
			front.push(idx[id[cur]+1]);
		}
	}

	cout << (ans*365) % MOD << nl;

	return 0;
}
