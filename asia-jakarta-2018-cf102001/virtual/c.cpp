#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

struct Edge {
	int id, dg;
};

vector<Edge>** adj;

int gr;
list<int> ans;
void euler(int u, list<int>::iterator it) {
	for (auto it2 = adj[gr][u].begin(); it2 != adj[gr][u].end(); ) {
		int v = it2->id;
		int d = it2->dg;
		adj[gr][u].erase(it2);
		euler(v, ans.insert(it, d));
		it2 = adj[gr][u].begin();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	int digit[m];
	for (int i=0; i<m; i++) {
		cin >> digit[i];
	}

	if (k == 1) {
		for (int i=0; i<n; i++) {
			cout << digit[0];
		}
		cout << nl;
		return 0;
	}

	vector<int> sz;
	for (int i=1; i<k; i*=m) {
		sz.push_back(i);
	}
	int s = sz.size();
	adj = new vector<Edge>*[s];
	for (int i=0; i<s; i++) {
		adj[i] = new vector<Edge>[sz[i]];
		//cerr << "add graph w/ size " << sz[i] << nl;
	}

	for (int i=0; i<m; i++) {
		adj[0][0].push_back({0,i});
	}
	for (int i=1; i<s; i++) {
		for (int u=0; u<sz[i-1]; u++) {
			for (const Edge& v : adj[i-1][u]) {
				for (const Edge& w : adj[i-1][v.id]) {
					adj[i][u*m+v.dg].push_back({v.id*m+w.dg, w.dg});
				}
			}
		}
	}

	gr = s-1;
	euler(0, ans.begin());
	int len = 0;
	while (len < n+k-1) {
		for (const auto& it : ans) {
			cout << digit[it];
			if (++len == n+k-1) break;
		}
	}
	cout << nl;

	return 0;
}
