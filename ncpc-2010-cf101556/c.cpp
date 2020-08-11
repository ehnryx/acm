#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace std {
	template<> struct hash<pii> {
		size_t operator () (const pii& v) const {
			return v.first<<10 ^ v.second;
		}
	};
}

const int N = 500+1;
vector<int> adj[N];
ld prob[2][N*N];
ld nodep[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m, k, a;
	cin >> n;
	cin >> m;

	auto get = [&] (int i, int j) {
		return i*(n+1) + j;
	};

	vector<int> walk = {n};
	for (int i = 0; i < m; i++) {
		cin >> a;
		walk.push_back(a);
	}

	int degree = 0;
	for (int i = 0; i < n; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> a;
			adj[i].push_back(a);
			degree++;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j : adj[i]) {
			prob[0][get(i,j)] = (ld)1/degree;
		}
	}

	ld ans = 1;
	for (int t = 1; t <= m; t++) {
		// captain lives
		ld cur = 1 - prob[(t-1)%2][get(walk[t],walk[t-1])];
		prob[(t-1)%2][get(walk[t],walk[t-1])] = 0;
		for (int i : adj[walk[t]]) {
			cur -= prob[(t-1)%2][get(i,walk[t])];
			prob[(t-1)%2][get(i,walk[t])] = 0;
		}
		ans *= cur;

		// update probabilities
		fill(nodep, nodep+N, 0);
		for (int i = 0; i < n; i++) {
			for (int j : adj[i]) {
				nodep[i] += prob[(t-1)%2][get(j,i)] / cur;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j : adj[i]) {
				prob[t%2][get(i,j)] = nodep[i] / adj[i].size();
			}
		}
	}

	cout << ans << nl;

	return 0;
}
