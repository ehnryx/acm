#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

struct Edge {
	int id, w;
};

const int N = 5e4+1;
vector<Edge> adj[N];
Edge first[N], second[N];
int pre[N];

int solve(int m) {
	//cerr << "SOLVE " << m << nl;
	memset(pre, 0, sizeof pre);
	queue<int> bfs;
	bfs.push(1);
	pre[1] = -1;
	while (!bfs.empty()) {
		int u = bfs.front();
		bfs.pop();
		if (u == m) {
			break;
		}
		for (const Edge& e : adj[u]) {
			if (!pre[e.id]) {
				pre[e.id] = u;
				bfs.push(e.id);
			}
		}
	}

	deque<int> path;
	for (int i=m; i!=-1; i=pre[i]) {
		path.push_front(i);
	}

	int res = 0;
	for (bool hit = false ; ; res++) {
		//cerr << res << ": "; for (int it : path) cerr << it << " ";
		//cerr << nl;
		//getchar();
		// move mouse
		if (first[path.back()].id != path.front()) {
			if (path.size() > 1 && *next(path.rbegin()) == first[path.back()].id) {
				path.pop_back();
			} else {
				path.push_back(first[path.back()].id);
			}
		} else if (second[path.back()].id != -1) {
			if (path.size() > 1 && *next(path.rbegin()) == second[path.back()].id) {
				path.pop_back();
			} else {
				path.push_back(second[path.back()].id);
			}
		} else {
			break;
		}

		// move cat
		if (path.size() == 2) {
			if (!hit) {
				path.pop_front();
				hit = true;
			}
		} else {
			path.pop_front();
		}
	}

	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;

		for (int i=1; i<=n; i++) {
			adj[i].clear();
			first[i] = second[i] = {-1,-1};
		}

		for (int i=1; i<n; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back({b,i});
			adj[b].push_back({a,i});
		}

		for (int i=1; i<=n; i++) {
			for (const Edge& e : adj[i]) {
				if (e.w > first[i].w) {
					second[i] = first[i];
					first[i] = e;
				} else if (e.w > second[i].w) {
					second[i] = e;
				}
			}
			//cerr << i << ":  first " << first[i].id << "  second " << second[i].id << nl;
		}

		int ans = solve(m);
		if (first[m].id != 1) {
			ans = min(ans, 1 + solve(first[m].id));
		} else {
			ans = min(ans, 1 + solve(second[m].id));
		}
		cout << ans << nl;
	}

	return 0;
}
