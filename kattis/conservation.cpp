#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int N = 1e5+1;
int val[N];
vector<int> adj[N];
int deg[N], cnt[N];

int solve(int n, int t) {
	memset(cnt+1, 0, n*sizeof(int));
	stack<int> bfs[3];
	for (int i=1; i<=n; i++) {
		if (deg[i]==0) {
			bfs[val[i]].push(i);
		}
	}

	int res = 0;
	int cur = t;
	while (!bfs[1].empty()||!bfs[2].empty()) {
		if (bfs[cur].empty()) {
			res++;
			cur = (cur==1?2:1);
		}
		int id = bfs[cur].top();
		bfs[cur].pop();
		for (int x : adj[id]) {
			cnt[x]++;
			if (cnt[x]==deg[x]) {
				bfs[val[x]].push(x);
			}
		}
	}
	return res;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int T;
	//cin >> T;
	read(T);
	while (T--) {
		int n, m;
		//cin >> n >> m;
		read(n); read(m);

		for (int i=1; i<=n; i++) {
			//cin >> val[i];
			read(val[i]);
			adj[i].clear();
			deg[i] = 0;
		}

		int a, b;
		for (int i=0; i<m; i++) {
			//cin >> a >> b;
			read(a); read(b);
			adj[a].push_back(b);
			deg[b]++;
		}

		int ans = INF;
		for (int t=1; t<=2; t++) {
			ans = min(ans, solve(n,t));
		}
		cout << ans << nl;
	}

	return 0;
}
