#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
template <typename T> inline void read(T &x) {
	static char c; x = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') ;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}
// END MAGIC IO

const int N = 2e5 + 1;
int x[N];
pair<int,int> g[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, p, q, s;
	read(n); read(p); read(q); read(s);
	multiset<int> y;
	for(int i=0; i<p; i++) {
		read(x[i]);
	}
	for(int i=0; i<q; i++) {
		int v;
		read(v);
		y.insert(v);
	}

	int l = 0;
	int r = 1e9+1;
	while(l<r) {
		int m = (l+r)/2;
		for(int i=0; i<p; i++) {
			g[i].first = min(x[i]+m, s-x[i]);
			g[i].second = x[i]-m;
		}
		sort(g, g+p);

		multiset<int> cur = y;
		int cnt = 0;
		for(int i=0; i<p; i++) {
			auto it = cur.lower_bound(g[i].second);
			if(it != cur.end() && *it <= g[i].first) {
				assert(g[i].first >= *it && *it >= g[i].second);
				cur.erase(it);
				cnt++;
			}
		}

		if(cnt >= n) {
			r = m;
		} else {
			l = m+1;
		}
	}

	cout << (r == 1e9+1 ? -1 : r) << nl;

	return 0;
}
