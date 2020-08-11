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

const int N = 11;
const int M = 1e4+1;

vector<pii> conn;
vector<pii> edges[N];
unordered_set<int> verts[N];
int b_of[M];
int ans[M][1<<10];
int parent[M];
vector<int> child[M];

void init() {
	memset(ans, INF, sizeof ans);
	memset(parent, -1, sizeof parent);
	fill(child, child+M, vector<int>());
}

int b_id;
bool input(int cur = 0) {
	if (cur == 0) {
		init();
		b_id = 0;
	}
	int n, m, w;
	if (cin >> n >> m >> w) {
		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			edges[cur].push_back(pii(a,b));
			verts[cur].insert(a);
			verts[cur].insert(b);
			b_of[a] = b_of[b] = cur;
		}

		for (int j = 1; j <= w; j++) {
			cin >> a >> b;
			conn.push_back(a,b);
			b_of[b] = ++b_id;
			child[cur].push_back(b_id);
			parent[b_id] = cur;
			input(b_id);
		}
		return true;
	}
	else {
		return false;
	}
}

void solve(int id) {
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m, w;
	while (input()) {
		for (int i = 0; i <= b_id; i++) {
			solve(i);
		}
	}

	return 0;
}
