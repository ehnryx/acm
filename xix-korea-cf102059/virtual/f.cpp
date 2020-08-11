#include <bits/stdc++.h>
using namespace std;

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


const int MAXN = 135;
int child[MAXN][2];
map<ll,int> vis;
int v = 0;

int solve(ll n) {
	//cerr << "@ " << n <<endl;
	if (vis.count(n)) return vis[n];
	if (n==1) {
		int id = v;
		vis[n] = v++;
		child[id][0] = child[id][1] = -1;
		return id;
	}
	int left = solve((n+1)/2);
	int right = solve(n/2);
	int id = v;
	vis[n] = v++;
	child[id][0] = left;
	child[id][1] = right;
	return id;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while(T--) {
		ll n;
		cin >> n;
		v = 0;
		vis.clear();
		solve(n);
		cout << v <<nl;
		for(int i=0;i<v;i++) {
			cout << child[i][0] << " " << child[i][1] <<nl;
		}
		cout << v-1 <<nl;
	}



	return 0;
}
