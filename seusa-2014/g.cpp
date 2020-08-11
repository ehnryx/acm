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
	int id, taken, dist;
	pii t;
	bool operator < (const Edge& e) const {
		if (dist == e.dist) return taken > e.taken;
		else return dist > e.dist;
	}
};

const int N = 1e3+1;
vector<Edge> adj[N];
bool vis[N][2];

int dist(const string& s, const string& t) {
	int res = 0;
	for (int i=0; i<s.size(); i++) {
		res += (s[i] != t[i]);
	}
	return res;
}

string answer(const string& s, const string& t) {
	set<string> res;
	for (int i=0; i<s.size(); i++) {
		if (s[i] != t[i]) {
			string cur = s;
			cur[i] = t[i];
			res.insert(cur);
		}
	}
	return *res.begin();
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

	int n;
	cin >> n;

	string s;
	vector<string> nodes;
	for (int i=0; i<n; i++) {
		cin >> s;
		nodes.push_back(s);
	}

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int d = dist(nodes[i],nodes[j]);
			if (0<d && d<=2) {
				adj[i].push_back({j,0,d});
			}
		}
	}

	priority_queue<Edge> nxt;
	nxt.push({0,0,0});
	while (!nxt.empty()) {
		Edge cur = nxt.top();
		nxt.pop();
		if (!vis[cur.id][cur.taken]) {
			vis[cur.id][cur.taken] = true;
			if (cur.id == 1) {
				if (cur.taken == 0) {
					cout << 0 << nl;
					cout << cur.dist << nl;
				} else {
					cout << answer(nodes[cur.t.first], nodes[cur.t.second]) << nl;
					cout << cur.dist << nl;
				}
				return 0;
			}
			for (const Edge& e : adj[cur.id]) {
				if (e.dist == 1) {
					nxt.push({e.id, cur.taken, cur.dist+e.dist, cur.t});
				} else if (!cur.taken) {
					nxt.push({e.id, 1, cur.dist+e.dist, pii(cur.id,e.id)});
				}
			}
		}
	}

	cout << 0 << nl;
	cout << -1 << nl;

	return 0;
}
