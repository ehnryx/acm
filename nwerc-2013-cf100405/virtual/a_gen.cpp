#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	int adj[n][n];
	memset(adj, INF, sizeof adj);
	for (int i = 0; i < n; i++) {
		adj[i][i] = 0;
	}

	for (int i = 1; i < n; i++) {
		int j = rng()%i;
		adj[j][i] = adj[i][j] = 1+rng()%5;
	}

	int a, b;
	do {
		a = rng()%n;
		b = rng()%n;
	} while (adj[a][b] != INF);
	adj[b][a] = adj[a][b] = rng()%10;

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

	cout << n << nl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << adj[i][j] << " ";
		}
		cout << nl;
	}

	return 0;
}
