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

const int UB = 12;
const int N = 40;
int adj[N][N];
ll nbr[N];
ll lmemo[1<<20];
ll rmemo[1<<20];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;

	unordered_set<int> graph[m];

	int sid = 0;
	unordered_map<string,int> idx;
	unordered_set<int> cur;
	for (int i=0; i<n; i++) {
		int t;
		cin >> t;
		if (t == 1) {
			for (int a : cur) {
				for (int b : cur) {
					if (a==b) continue;
					graph[a].insert(b);
				}
			}
			cur.clear();
		} else {
			string s;
			cin >> s;
			if (!idx.count(s)) idx[s] = sid++;
			cur.insert(idx[s]);
		}
	}
	for (int a : cur) {
		for (int b : cur) {
			if (a==b) continue;
			graph[a].insert(b);
		}
	}

	for (int i=0; i<m; i++) {
		for (int j=0; j<m; j++) {
			if (i==j || graph[i].count(j)) continue;
			adj[i][j] = true;
			nbr[i] |= 1LL<<j;
		}
	}

	// TODO

	return 0;
}
