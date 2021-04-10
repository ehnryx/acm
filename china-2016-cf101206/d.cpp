#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 1e5+1;
vector<int> adj[N];

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
	for (c=get(); c < '0' || c > '9'; c=get());
	for (; c >= '0' && c <= '9'; c=get()) x = x * 10 + c - '0';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; read(T);
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case #" << tt << ": ";

		int n, m, r; read(n); read(m); read(r);

		for (int i=1; i<=n; i++) {
			adj[i].clear();
		}

		vector<int> need(n+1,0);
		vector<bool> done(n+1);
		for (int i=1; i<=n; i++) {
			read(need[i]);
			if (i != r) {
				adj[min(i,r)].push_back(max(i,r));
			}
		}

		need[1]--;
		done[r] = true;

		for (int i=0; i<m; i++) {
			int a, b;
			read(a); read(b);
			adj[min(a,b)].push_back(max(a,b));
		}

		for (int i=1,j=1; i<=n; i++) {
			for (int x : adj[i]) {
				if (!done[x]) {
					done[x] = true;
					if (need[i] > 0) {
						need[i]--;
						//cerr << i << " -> " << x << endl;
					} else {
						//cerr << "S -> " << x << " (" << i << ")" << endl;
					}
				}
			}
			if (i == j && !done[j] && need[i] == 0) {
				//cerr << "S -> " << j << endl;
				done[j++] = true;
			}
			for (assert(need[i] >= 0); need[i] > 0 && j <= n; need[i]--) {
				while (j <= n && done[j]) {
					j++;
				}
				if (j <= n) {
					//cerr << i << " -> " << j << " (optional)" << endl;
					done[j++] = true;
				} else {
					break;
				}
			}
		}

		ll ans = 0;
		for (int i=1; i<=n; i++) {
			//cerr << i << ": " << need[i] << endl;
			ans += need[i];
		}
		cout << ans << nl;
	}

	return 0;
}
