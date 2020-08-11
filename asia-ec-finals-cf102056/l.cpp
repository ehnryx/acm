#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 1e5+10;

int a[N];
int cnt[2][2];
int type[N];
int tcnt[2];
vector<int> adj[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		tcnt[a[i]]++;
	}

	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (int i = 0; i < n; i++) {
		bool bad = 1;
		for (int j : adj[i]) {
			if (a[i] != a[j]) {
				cnt[a[i]][a[j]]++;
				bad = 0;
				break;
			}
		}
		if (bad) cnt[a[i]][a[i]]++;
		type[i] = bad;
	}

	for (int i = 0; i < n; i++) {
		ll ans = 0;
		if (type[i]) {
			ans = 2 * cnt[!a[i]][a[i]] + 3 * cnt[!a[i]][!a[i]] + tcnt[a[i]] - 1;
		} else {
			int cadj = 0;
			for (int j : adj[i]) {
				cadj += a[j] != a[i];
			}
			ans = cadj + 2 * (tcnt[!a[i]] - cadj) + tcnt[a[i]] - 1;
		}
		cout << ans << " ";
	}
	cout << nl;

	return 0;
}
