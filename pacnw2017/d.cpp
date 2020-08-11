#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Edge {
	int other;
	int colo;
	Edge(int o, int c): other(o), colo(c) {}
};

set<int> ans;
vector<Edge> graph[500001];

bool dfs(int cur, int par, int colo, bool good) {
	int bad = 0;
	bool horrible = false;
	unordered_map<int,int> match;
	unordered_map<int,bool> dup;
	for (const Edge& e : graph[cur]) {
		if (e.other == par) continue;
		if (e.colo == colo) bad = e.other;
		if (match[e.colo] == 0) match[e.colo] = e.other;
		else if (match[e.colo] == -1) dup[e.other] = true;
		else {
			dup[e.other] = true;
			dup[match[e.colo]] = true;
			match[e.colo] = -1;
		}
	}
	if (bad) {
		ans.clear();
	}
	for (const Edge& e : graph[cur]) {
		if (e.other == par) continue;
		horrible |= dfs(e.other, cur, e.colo, good && !dup[e.other] && e.other != bad && !horrible);
	}
	if (good && !horrible) {
		ans.insert(cur);
	}
	return bad || horrible;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int a, b, c;
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> a >> b >> c;
		graph[a].push_back(Edge(b,c));
		graph[b].push_back(Edge(a,c));
	}
	dfs(1, -1, -1, true);

	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << nl;
	}

	return 0;
}
