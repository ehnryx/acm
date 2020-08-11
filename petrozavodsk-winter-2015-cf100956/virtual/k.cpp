#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

struct suff_arr {
	typedef vector<int> vi;
	vector<int> t, sa, inv, lcp; int N;
	suff_arr(const string& s) : N(s.size()) {
		sa.resize(N); t.resize(N+3); lcp.resize(N); inv.resize(N);
		for (int i = 0; i < N; i++) t[i] = s[i];
		if (N < 3) { if (N == 2) { sa[(t[0] > t[1])] = 1; } }
		else build(t, sa, N, 128);
		genHeight();
	}
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
		return a1<b1 || (a1==b1 && a2<b2) || (a1 == b1 && a2 == b2 && a3 <= b3);
	}
	void pass(vi& a, vi& b, vi& r, int off, int n, int k) { vi c(k+1);
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

const int N = 1 << 21;
int segt[2*N];
void build() {
	for (int i = N-1; i > 0; i--) {
		segt[i] = min(segt[2*i], segt[2*i+1]);
	}
}
inline int query(int l, int r) {
	int ans = INF;
	for (l += N, r += N+1; l < r; l /= 2, r /= 2) {
		if (l%2) ans = min(ans, segt[l++]);
		if (r%2) ans = min(ans, segt[--r]);
	}
	return ans;
}

inline int f(int n, int l, int r) {
	return r - l - max(l, n - r - 1) + 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s, t; cin >> s >> t;
	int n = s.size(), m = t.size();
	suff_arr a(s + "..." + t);
	assert(a.lcp.size() == n+m+3);
	for (int i = 0; i < n+m+3; i++) {
		segt[N+i] = a.lcp[i];
	}
	build();
	int ans = -INF, ansl = -1, ansr = -1;
	set<int> tind;
	for (int i = 0; i < n+m+3; i++) {
		if (a.sa[i] >= n+3) {
			tind.insert(i);
		}
	}
	for (int i = 0; i < n+m+3; i++) {
		if (a.sa[i] >= n) continue;
		auto it = tind.lower_bound(i);
		int l = a.sa[i];
		if (it != tind.end()) {
			int len = query(i+1, *it);
			if (len > 0) {
				int r = l + len - 1;
				if (f(n, l, r) > ans) {
					ans = f(n, l, r);
					tie(ansl, ansr) = tie(l, r);
				} else if (f(n, l, r) == ans) {
					tie(ansl, ansr) = min(tie(ansl, ansr), tie(l, r));
				}
			}
		}
		if (it != tind.begin()) {
			--it;
			int len = query(*it+1, i);
			if (len > 0) {
				int r = l + len - 1;
				if (f(n, l, r) > ans) {
					ans = f(n, l, r);
					tie(ansl, ansr) = tie(l, r);
				} else if (f(n, l, r) == ans) {
					tie(ansl, ansr) = min(tie(ansl, ansr), tie(l, r));
				}
			}
		}
	}
	if (ansl == INF) {
		puts("-1 -1");
		return 0;
	}
	cout << ansl << " " << ansr << nl;

	return 0;
}
