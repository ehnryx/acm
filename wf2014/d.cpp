#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const int MAXN = 25;
int n;

vector<int> adj[MAXN];

int ans[MAXN][MAXN];

void bfs(int v) {
	int prebm = 0;
	int bm = 1<<v;
	ans[v][v] = 0;
	//cerr << "SOLVING " << v <<endl;
	for(int it=1;it<25;it++) {
		if (prebm==bm) break;
		prebm = bm;
		vector<int> nex;
		for(int i=0;i<n;i++) {
			if (bm>>i&1) continue;
			for(int pos : adj[i]) {
				if ((pos | bm)==bm) {
					//cerr << i << " has dis " << it << " from "  << v <<endl;
					ans[v][i] = it;
					nex.push_back(i);
					break;
				}
			}
		}
		for(int i : nex) {
			bm |= (1<<i);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(ans, -1,sizeof ans);
	cin >> n;
	for(int i=0;i<n;i++) {
		int k;
		cin >> k;
		for(int j=0;j<k;j++) {
			string s;
			cin >> s;
			int bm = 0;
			for(char c: s) {
				bm |=(1<< (c-'a'));
			}
			//cerr << i << " " << bitset<10>(bm) <<endl;
			adj[i].push_back(bm);
		}
	}

	for(int i=0;i<n;i++) {
		bfs(i);
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout << ans[j][i] << " ";
		}
		cout <<endl;
	}


	return 0;
}
