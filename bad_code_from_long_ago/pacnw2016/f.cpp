#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;
const int N = 2005;

int low[N], vis[N], scomp[N], scompNum, I;
vector<int> adj[N]; stack<int> verts;
void scc(int u) {low[u] = vis[u] = ++I; verts.push(u);
	for (int v : adj[u]) {
		if (!vis[v]) scc(v);
		if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
	if (vis[u] <= low[u]) {
		int v;
		do { v = verts.top(); verts.pop(); scomp[v] = scompNum; } while (v != u);
		++scompNum; }}
void get_scc(int n) { memset(vis, 0, sizeof vis); memset(scomp, -1, sizeof scomp); scompNum=I=0;
	for (int i = 0; i < n; i++) if (!vis[i]) scc(i);
}

bool truth[N/2];
void add_clause(int a, int b) {adj[a^1].push_back(b); adj[b^1].push_back(a);}
bool two_sat(int n) { get_scc(n);
	for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return 0;
		truth[i/2] = (scomp[i] < scomp[i^1]); } return true; }

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n, r, l; cin >> n >> r >> l;
	vector<vector<int>> grid(n, vector<int>(n));
	vector<pair<int, int>> ls(l);
	for (int i = 0; i < l; i++) {
		int r, c; cin >> r >> c;
		grid[r-1][c-1] = i;
		ls[i] = {r-1, c-1};
	}
	// vertical = true
	for (int i = 0; i < l; i++) {
		for (int j = i+1; j < l; j++) {
			const auto& p = ls[i], q = ls[j];
//			cout << p.first << " " << p.second << " " << q.first << " " << q.second << endl;
			// v v
			if (p.first == q.first && abs(p.second - q.second) <= 2*r) {
//				cout << "vv" << endl;
				adj[2*i].push_back(2*j^1);
				adj[2*j].push_back(2*i^1);
			}
			// h h
			if (p.second == q.second && abs(p.first - q.first) <= 2*r) {
//				cout << "hh" << endl;
				adj[2*i^1].push_back(2*j);
				adj[2*j^1].push_back(2*i);
			}
			/*
			// v h
			if (p.first != q.first && p.second != q.second
					&& abs(p.first - q.first) <= r && abs(p.second - q.second) <= r) {
				cout << "vh" << endl;
				adj[2*i].push_back(2*j);
				adj[2*j].push_back(2*i);
				adj[2*i^1].push_back(2*j^1);
				adj[2*j^1].push_back(2*i^1);
			}
			*/
		}
	}
	if (two_sat(2*l))
		cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}
