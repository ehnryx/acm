#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
mt19937 rng;

#define nl '\n'

const int MAXN = 111;
int n;

set<int> adj[MAXN], unadj[MAXN];

int col[MAXN];
bool vis[MAXN];
vector<int> order;

void dfs(int u) {
	order.push_back(u);
	vis[u] = 1;
	for (int i : adj[u]) {
		if (!vis[i]) dfs(i);
	}
}

bool rec(int x) {
	if (x>=n) return true;
	int u = order[x];
	if (col[u]) return rec(x+1);
	bitset<5> bm;
	for(int v:adj[u]) {
		bm[col[v]] = 1;
	}
	for(int c = 1; c <= 4; c++) {
		if (bm[c]) continue;
		col[u] = c;
		if (rec(x+1)) return true;
		col[u] = 0;
	}
	return false;
}

vector<int> interleave(vector<int> a) {
	vector<int> ans(a.size());
	int k = 0;
	for (int i = 0; i < (n+1)/2; i++) {
		for (int j = i; j < n; j += (n+1)/2) {
			ans[k++] = a[j];
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int a, b; char c;
	while(cin >> a >> c >> b) {
		adj[a].insert(b);
		adj[b].insert(a);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i != j && !adj[i].count(j)) {
				unadj[i].insert(j);
			}
		}
	}
	/*
	vector<int> clique;
	vector<int> aa(n);
	iota(aa.begin(), aa.end(), 1);
	for(int i=1;i<=n;i++) {
		vector<int> cur = {i};
		shuffle(aa.begin(), aa.end(), rng);
		for (int j : aa) {
			bool shit = 0;
			for (int k : cur) {
				if (!unadj[j].count(k)) {
					shit = 1;
					break;
				}
			}
			if (!shit) cur.push_back(j);
		}
		if (cur.size() > clique.size()) clique = cur;
	}
	cerr << "CLIQUE: " << clique.size() << nl;
	for (int i : clique) col[i] = 1;
	*/
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) dfs(i);
	}
	order = interleave(interleave(interleave(order)));
	bool good = rec(0);
	assert(good);
	for(int i=1;i<=n;i++) {
		cout << i << " " << col[i] <<endl;
	}
	return 0;
}
