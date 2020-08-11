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
	int id, time;
};

const int N = 2e5+1;
vector<Edge> adj[N];
bool vis[N];

vector<int> arr;
void generate(int cur, int t) {
	if (arr.size() > 1e6) return;

	arr.push_back(cur);
	for (int i = adj[cur].size()-1; i >= 0 && adj[cur][i].time > t; i--) {
		generate(adj[cur][i].id, adj[cur][i].time);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, l, r;
	cin >> n >> l >> r;

	int a, b;
	vis[0] = true;
	for (int i=0; i<n; i++) {
		cin >> a >> b;
		if (vis[a]) {
			adj[a].push_back({b,i});
			vis[b] = true;
		}
	}
	generate(0, -1);

	int len = arr.size();
	for (int i = l; i < r; i++) {
		cout << arr[i%len] << " ";
	}
	cout << nl;

	return 0;
}
