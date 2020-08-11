#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int n, a, b; ll c;
int ww[500001];
map<int,int> graph[500001];
int done[500001];
int pref[500001][26];
ll pdist[500001][26];
int ans[500001];

void init() {
	memset(ans, -1, sizeof(ans));
	memset(pref, -1, sizeof(pref));
	memset(done, 0, sizeof(done));
	memset(pdist, -1, sizeof(pdist));
}

void build_jump(int cur, int par) {
	int c = pref[cur][0] = par;
	int i = 0;
	while (c != -1) {
		c = pref[cur][i+1] = pref[c][i];
		i++;
	}
	if (i > 0) {
		pdist[cur][0] = graph[cur][par];
		for (int j = 1; j < i; j++) {
			pdist[cur][j] = pdist[cur][j-1] + pdist[pref[cur][j-1]][j-1];
		}	
	}
	for (const pii& e : graph[cur]) {
		if (e.first != par)
			build_jump(e.first, cur);
	}
}

void build_done(int cur, int par) {
	for (int i = 0; i < n; i++) {
		ll len = ww[i];
		int c = i;
		while (len > 0) {
			int j;
			for (j = 0; pdist[c][j] != -1 && len >= pdist[c][j]; j++);
			if (j == 0) break;
			if (pref[c][j-1] == -1) break;
			len -= pdist[c][j-1];
			c = pref[c][j-1];
		}
		done[c]++;
	}
}

int dfs(int cur, int par) {
	int res = 0;
	for (pii e : graph[cur]) {
		if (e.first != par) {
			res += dfs(e.first, cur);
		}
	}
	ans[cur] = res;

	res++;
	res -= done[cur];

	return res;
}

int main() {
	freopen("car.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {

		cin >> n;
		for (int i = 0; i < n; i++) {
			graph[i].clear();
		}
		for (int i = 0; i < n; i++) {
			cin >> ww[i];
		}
		for (int i = 1; i < n; i++) {
			cin >> a >> b >> c;
			graph[a-1].insert(pii(b-1,c));
			graph[b-1].insert(pii(a-1,c));
		}

		init();
		build_jump(0, -1);
		build_done(0, -1);

		dfs(0, -1);

		for (int i = 0; i < n; i++) {
			cout << ans[i] << " ";
		}
		cout << nl;
	}

	return 0;
}
