#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 600;
vector<int> adj[N], graph[N];
pair<int,int> edges[N];
int pre[N];
bool used[N];

vector<int> get_path(int n, int s, int t) {
	fill(pre, pre+n, -2);
	queue<int> bfs;
	bfs.push(s);
	pre[s] = -1;
	while(!bfs.empty()) {
		int u = bfs.front();
		bfs.pop();
		if(u == t) {
			break;
		}
		for(int e : graph[u]) {
			int v = u ^ edges[e].first ^ edges[e].second;
			if(pre[v] == -2) {
				bfs.push(v);
				pre[v] = e;
			}
		}
	}

	vector<int> path;
	while(pre[t] >= 0) {
		path.push_back(pre[t]);
		t ^= edges[pre[t]].first ^ edges[pre[t]].second;
	}
	return path;
}

void update(int u) {
	for(bool add=true; u>=0; u=pre[u], add^=1) {
		auto [a, b] = edges[u];
		if(add) {
			used[u] = true;
			graph[a].push_back(u);
			graph[b].push_back(u);
		} else {
			used[u] = false;
			graph[a].erase(find(graph[a].begin(), graph[a].end(), u));
			graph[b].erase(find(graph[b].begin(), graph[b].end(), u));
		}
	}
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n; cin >> n && n; ) {
		n *= 2;

		unordered_map<int,int> remap;
		int rid = 0;
		for(int i=0; i<n; i++) {
			int a, b;
			cin >> a >> b;
			if(!remap.count(a)) remap[a] = rid++;
			if(!remap.count(b)) remap[b] = rid++;
			edges[i] = make_pair(remap[a], remap[b]);
		}
		for(int i=0; i<rid; i++) {
			graph[i].clear();
		}

		int ans = 0;
		int maxn = 0;
		for(int i=0; i<n; i+=2) {
			for(int j=0; j<i; j++) {
				if(used[j]) {
					adj[j].clear();
					adj[j].push_back(j^1);
				} else if(used[j^1]) {
					adj[j] = get_path(maxn+1, edges[j].first, edges[j].second);
				}
			}
			maxn = max(maxn, max(edges[i].first, edges[i].second));
			adj[i] = get_path(maxn+1, edges[i].first, edges[i].second);
			maxn = max(maxn, max(edges[i^1].first, edges[i^1].second));
			adj[i^1] = get_path(maxn+1, edges[i^1].first, edges[i^1].second);
			used[i] = used[i^1] = false;

			fill(pre, pre+i+2, -2);
			queue<int> bfs;
			bfs.push(i);
			bfs.push(i^1);
			pre[i] = pre[i^1] = -1;
			while(!bfs.empty()) {
				int u = bfs.front();
				bfs.pop();
				if(adj[u].empty()) {
					update(u);
					ans++;
					break;
				}
				for(int v : adj[u]) {
					if(pre[v] == -2) {
						bfs.push(v);
						pre[v] = u;
					}
				}
			}
		}

		cout << ans*2 << nl;
	}

	return 0;
}
