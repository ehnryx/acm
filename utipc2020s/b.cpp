#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const int INF = 0x3f3f3f3f;

const vector<int> dx = {0, 0, 1, -1};
const vector<int> dy = {1, -1, 0, 0};

const int N = 1<<16;
vector<pair<int,int>> add[2*N];
bool down[2*N];
pair<int,int> ans[N];

const int M = 1500 + 2;
int dsu[M*M], sz[M*M], faces[M*M];
bool g[M][M];

int find(int i) {
	if(dsu[i] == 0) return i;
	return find(dsu[i]); // no path compression
}

void add_flag(int x, int i=1, int s=0, int e=N-1) {
	down[i] = true;
	if(s == e) return;
	int m = (s+e) / 2;
	if(x <= m) add_flag(x, 2*i, s, m);
	else add_flag(x, 2*i+1, m+1, e);
}

void add_range(int l, int r, pair<int,int> v, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l || !down) return;
	if(l<=s && e<=r) {
		add[i].push_back(v);
		return;
	}
	int m = (s+e) / 2;
	add_range(l, r, v, 2*i, s, m);
	add_range(l, r, v, 2*i+1, m+1, e);
}

int squares(int a, int b) {
	int res = 0;
	res += (g[a-1][b-1] && g[a-1][b] && g[a][b-1]);
	res += (g[a-1][b+1] && g[a-1][b] && g[a][b+1]);
	res += (g[a+1][b-1] && g[a+1][b] && g[a][b-1]);
	res += (g[a+1][b+1] && g[a+1][b] && g[a][b+1]);
	return res;
}

void solve(int l, int r, int islands, int lakes, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l || !down[i]) return;

	vector<pair<int,int>> memo;
	for(auto [a, b] : add[i]) {
		islands += 1;
		g[a][b] = true;
		int u = a*M + b;
		for(int d=0; d<4; d++) {
			int na = a + dx[d];
			int nb = b + dy[d];
			if(!g[na][nb]) continue;

			int v = na*M + nb;
			int ru = find(u);
			int rv = find(v);
			if(ru == rv) {
				lakes -= !!faces[ru];
				faces[ru] += 1;
				memo.emplace_back(ru, 1);
				lakes += !!faces[ru];
			} else {
				if(sz[ru] > sz[rv]) swap(ru, rv);
				lakes -= !!faces[ru];
				lakes -= !!faces[rv];
				dsu[ru] = rv;
				sz[rv] = sz[ru] + sz[rv] + 1;
				faces[rv] = faces[ru] + faces[rv];
				memo.emplace_back(ru, INF); // INF for merge
				lakes += !!faces[rv];
				islands -= 1;
			}
		}

		u = find(u);
		int sqr = squares(a, b);
		lakes -= !!faces[u];
		faces[u] -= sqr;
		memo.emplace_back(u, -sqr);
		lakes += !!faces[u];
	}

	if(s == e) {
		ans[s] = make_pair(islands, islands - lakes);
	} else {
		int m = (s+e) / 2;
		solve(l, r, islands, lakes, 2*i, s, m);
		solve(l, r, islands, lakes, 2*i+1, m+1, e);
	}

	reverse(memo.begin(), memo.end());
	for(auto [u, val] : memo) {
		if(val != INF) {
			faces[u] -= val;
		} else {
			int par = dsu[u];
			dsu[u] = 0;
			sz[par] = sz[par] - sz[u] - 1;
			faces[par] = faces[par] - faces[u];
		}
	}
	for(auto [a, b] : add[i]) {
		g[a][b] = false;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector<char> t(m);
	map<pair<int,int>,vector<int>> ev;
	for(int i=0; i<m; i++) {
		cin >> t[i];
		if(t[i] == '?') {
			add_flag(i);
		} else {
			int a, b;
			cin >> a >> b;
			ev[make_pair(a, b)].push_back(i);
		}
	}

	for(const auto& [e, v] : ev) {
		bool in = false;
		int pre = -1;
		for(int i : v) {
			if(in) {
				add_range(pre, i, e);
			}
			in ^= 1;
			pre = i;
		}
		if(in) {
			add_range(pre, m-1, e);
		}
	}

	solve(0, m-1, 0, 0);
	for(int i=0; i<m; i++) {
		if(t[i] == '?') {
			cout << ans[i].first << " " << ans[i].second << nl;
		}
	}

	return 0;
}
