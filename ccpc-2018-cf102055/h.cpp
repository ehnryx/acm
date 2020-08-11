#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;


const int MAXN = 2e5+10;
vector<int> adj[MAXN];

int term[MAXN];
int n, m, A, B;

int dis[MAXN];
int dis2[MAXN];

vector<int> stk;
vector<int> cycle;
int vis[MAXN];
bool dfs(int u) {
	vis[u]=1;
	stk.push_back(u);
	for(int v:adj[u]) {
		if (vis[v]) {
			while(stk.back()!=v) {
				cycle.push_back(stk.back());
				stk.pop_back();
			}
			cycle.push_back(v);
			return true;
		}
		else {
			if(dfs(v)) break;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cin >> n;
		memset(vis, 0, sizeof vis);
		memset(term, 0, sizeof term);
		memset(dis, 0, sizeof dis);
		memset(dis2, 0, sizeof dis2);
		for(int i=0;i<=n;i++) {
			adj[i].clear();
		}
		for(int i=0;i<n;i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		cin >> m;
		for(int j=0;j<m;i++) {
			int v; cin >> v;
			term[v] = 1;
		}
		cin >> A >> B;
		queue<int> q;
		q.push(B);
		dis[B] = 0;
		while(!q.empty()) {
			int u = q.front();
			for(int v:adj[u]) {
				if (v!=B && dis[v]==0){
					dis[v] = dis[u]+1;
					q.push(v);
				}
			}
		}
		q.push(A);
		dis2[A] = 0;
		bool pos = false;
		while(!q.empty()) {
			int u = q.front();
			if (term[u]) pos = true;
			for(int v:adj[u]) {
				if (v!=B && dis2[v]==0 && dis2[u]+1<=dis[v]){
					dis2[v] = dis2[u]+1;
					q.push(v);
				}
			}
		}
		if (!pos) {
			dfs(1);
		}

		cout << "Case " << tt << ": ";
		cout << (pos ? "Panda" : "Sheep") <<endl;
	}

	return 0;
}
