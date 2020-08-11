#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const int N = 1010;
const string s = "?BRW";

vector<int> uf(N);
vector<vector<int>> rel;
int n;
int find(int cur) {
	return (cur == uf[cur] ? cur : uf[cur] = find(uf[cur]));
}
void merge(int a, int b) {
	uf[find(a)] = find(b);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	iota(uf.begin(), uf.end(), 0);
	int m; cin >> n >> m;
	rel = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < m; i++) {
		int u, v; char c; cin >> u >> c >> v;
		u--; v--;
		if (c == '=')
			merge(u, v);
		else if (c == '<')
			rel[u][v] = 1, rel[v][u] = -1;
		else rel[v][u] = 1, rel[u][v] = -1;
	}

	for (int i = 0; i < n; i++) {
		int k = find(i);
		for (int j = 0; j < n; j++)
			if (rel[k][j] == 0) rel[k][j] = rel[i][j];
	}

	vector<int> ans(n);
	vector<bool> vis(n);
	for (int i = 0; i < n; i++) {
		int cur = find(i);
		if (vis[cur] || ans[cur] != 0) continue;
		vis[cur] = 1;
		vector<int> big, small;
		for (int j = 0; j < n; j++) {
			if (rel[cur][j] == -1) small.push_back(j);
			if (rel[cur][j] == 1) big.push_back(j);
		}
		if (!big.empty() && !small.empty()) {
			ans[cur] = 2;
			for (int j : small)
				ans[find(j)] = 1;
			for (int j : big)
				ans[find(j)] = 3;
		}
	}

	for (int i = 0; i < n; i++)
		cout << s[ans[find(i)]];
	cout << endl;

	return 0;
}
