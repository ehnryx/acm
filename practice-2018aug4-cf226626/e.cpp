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

const int N = 3e3+1;
int dist[N*N];
bool vis[N*N];
int p[N], suff[N];

void init() {
	memset(dist, INF, sizeof dist);
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	init();

	int n, k;
	cin >> n >> k;

	p[n] = 0;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}

	suff[n] = 0;
	for (int i = n-1; i >= 0; i--) {
		suff[i] = max(suff[i+1], p[i]);
	}

	auto get = [&] (int i, int j) {
		return i*(n+1) + j;
	};

	int ans = 0;
	queue<int> bfs;
	bfs.push(get(0, 1));
	dist[get(0,1)] = 0;
	while (!bfs.empty()) {
		int cur = bfs.front();
		bfs.pop();

		if (!vis[cur]) {
			vis[cur] = true;
			if (dist[cur] <= k) {
				ans++;
			}

			int i = cur / (n+1);
			int j = cur % (n+1);
			if (p[i] > 0 && suff[j] > 0) {
				int nxt = get(min(n, j+1), min(n, j+2));
				dist[nxt] = dist[cur]+1;
				bfs.push(nxt);
			}
			if (p[i] > 0 && suff[j] < 100) {
				int nxt = get(min(n, i), min(n, j+1));
				dist[nxt] = dist[cur]+1;
				bfs.push(nxt);
			}
			if (p[i] < 100 && suff[j] > 0) {
				int nxt = get(min(n, j), min(n, j+1));
				dist[nxt] = dist[cur]+1;
				bfs.push(nxt);
			}
			if (p[i] < 100 && suff[j] < 100) {
				int nxt = get(min(n, i), min(n, j));
				dist[nxt] = dist[cur]+1;
				bfs.push(nxt);
			}
		}
	}

	cout << ans << nl;

	return 0;
}
