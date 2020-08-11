#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int MAXN = 111;

multiset<int> adj[MAXN];

list<int> ans;
void euler(int u, list<int>::iterator it) {
	for(auto it2 = adj[u].begin();it2 !=adj[u].end();) {
		int v=*it2;
		adj[u].erase(it2);
		euler(v,ans.insert(it, v)); it2= adj[u].begin();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			if (i==j) continue;
			if (i==2 && j==1) continue;
			adj[i].insert(j);
		}
	}
	int st = 1;
	euler(st, ans.insert(ans.begin(),st));
	auto it = ans.rbegin();
	auto it2 = ans.rbegin();
	it2++;
	cout << "1 1 0" <<endl;
	for(;it2!=ans.rend();it++, it2++) {
		cout << *it2 << " " << *it2 << " " << *it << endl;
	}
	cout << "0 1 2" <<endl;

	return 0;
}
