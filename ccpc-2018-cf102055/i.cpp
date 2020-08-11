#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

const int N = 1e5+2;
const int N2 = 5010;


inline char get() {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int& x) {
	static char c; x = 0;
	for (c=get(); c < '0' || c > '9'; c = get());
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}

int x[N], y[N];
template<int X>
void solve(int n) {
	map<int, int> mx, my;
	for (int i = 0; i < n; i++) {
		read(x[i]); read(y[i]);
		mx[x[i]]; my[y[i]];
	}
	if (n == 1) {
		cout << "1 1\n";
		return;
	}
	if (n == 2) {
		cout << "2 1\n";
		return;
	}
	int idx = 0;
	for (auto& p : mx) {
		p.second = idx++;
	}
	int idy = 0;
	for (auto& p : my) {
		p.second = idy++;
	}
	vector<int> cntx(idx), cnty(idy);
	//cerr << "compressed: \n";
	for (int i = 0; i < n; i++) {
		x[i] = mx.at(x[i]);
		y[i] = my.at(y[i]);
		//cerr << x[i] << " " << y[i] << nl;
		cntx[x[i]]++;
		cnty[y[i]]++;
	}
	int bestx = *max_element(cntx.begin(), cntx.end()),
		besty = *max_element(cnty.begin(), cnty.end());
	//cerr << "bestx " << bestx << " besty " << besty << nl;
	bitset<X> mxy, mxy1;
	vector<vector<int>> xs(idx);
	for (int i = 0; i < n; i++) {
		xs[x[i]].push_back(y[i]);
	}
	for (int i = 0; i < idy; i++) {
		if (cnty[i] == besty) {
			//cerr << "mxy: " << i << nl;
			mxy[i] = 1;
		} else if (cnty[i] == besty-1) {
			//cerr << "mxy-1: " << i << nl;
			mxy1[i] = 1;
		}
	}
	int mxy_cnt = mxy.count(), mxy1_cnt = mxy1.count();
	ll ans1 = 0, ans2 = 0;
	for (int i = 0; i < idx; i++) {
		if (cntx[i] < bestx-1) continue;
		if (cntx[i] == bestx) {
			int acnt = 0;
			for (int j : xs[i]) acnt += mxy[j];
			ans1 += mxy_cnt - acnt;
			ans2 += acnt;

			acnt = 0;
			for (int j : xs[i]) acnt += mxy1[j];
			ans2 += mxy1_cnt - acnt;
		} else if (cntx[i] == bestx-1) {
			int acnt = 0;
			for (int j : xs[i]) acnt += mxy[j];
			ans2 += mxy_cnt - acnt;
		}
	}
	//cerr << "ans: " << ans1 << " " << ans2 << nl;
	if (ans1) {
		cout << bestx + besty << " " << ans1 / (bestx + besty == 2 ? 2 : 1) << nl;
	} else {
		cout << bestx + besty - 1 << " " << ans2 / (bestx + besty - 1 == 2 ? 2 : 1) << nl;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; read(T);
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case " << tt << ": ";
		int n; read(n);
		if (n < N2) {
			solve<N2>(n);
		} else solve<N>(n);
	}

	return 0;
}
