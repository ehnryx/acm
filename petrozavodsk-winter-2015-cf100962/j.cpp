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

struct Edge {
	int id;
	char c;
};

struct Value {
	int val;
	int child;
	int id;
};

const int N = 5e5+1;
vector<Edge> adj[N];
Value pre[N], pre2[N], suf[N], suf2[N];

string s;
int len;

pii ans = pii(-1,-1);
bool dfs(int cur, int par = -1) {
	pre[cur] = pre2[cur] = suf[cur] = suf2[cur] = {-1,cur,cur};
	for (Edge e : adj[cur]) {
		if (e.id != par) {
			if (dfs(e.id, cur)) return true;
			int pval;

			pval = pre[e.id].val;
			if (pval < len && e.c == s[pval]) pval += 1;
			if (pval > pre[cur].val) {
				pre2[cur] = pre[cur];
				pre[cur] = { pval, e.id, pre[e.id].id };
			} else if (pval > pre2[cur].val) {
				pre2[cur] = { pval, e.id, pre[e.id].id };
			}

			pval = suf[e.id].val;
			if (pval < len && e.c == s[len-1-pval]) pval++;
			if (pval > suf[cur].val) {
				suf2[cur] = suf[cur];
				suf[cur] = {pval, e.id, suf[e.id].id};
			} else if (pval > suf2[cur].val) {
				suf2[cur] = {pval, e.id, suf[e.id].id};
			}
		}
	}

	pre[cur].val = max(pre[cur].val, 0);
	pre2[cur].val = max(pre2[cur].val, 0);
	suf[cur].val = max(suf[cur].val, 0);
	suf2[cur].val = max(suf2[cur].val, 0);

	if (pre[cur].child != suf[cur].child) {
		if (pre[cur].val + suf[cur].val >= len) {
			ans = pii(pre[cur].id, suf[cur].id);
			return true;
		}
		return false;
	}
	else {
		if (pre[cur].val + suf2[cur].val >= len) {
			ans = pii(pre[cur].id, suf2[cur].id);
			return true;
		}
		if (pre2[cur].val + suf[cur].val >= len) {
			ans = pii(pre2[cur].id, suf[cur].id);
			return true;
		}
		return false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	int a, b;
	char c;
	for (int i=1; i<n; i++) {
		cin >> a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	cin >> s;
	len = s.size();

	if (dfs(1)) {
		assert(ans != pii(-1,-1));
		cout << ans.first << " " << ans.second << nl;
	}
	else {
		cout << -1 << " " << -1 << nl;
	}

	return 0;
}
