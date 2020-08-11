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

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int N = 1e5+1;
const int M = llround(sqrt(N))+1;

struct Edge {
	int id, weight;
};

struct Query {
	int i, a, b;
	bool operator < (const Query& v) const {
		if (a/M == v.a/M) return b < v.b;
		else return a < v.a;
	}
};

vector<Edge> adj[N];
int weight[N];
int linear[N];
int ans[N];

void euler_tour(int cur, int par = -1) {
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, q;
	//cin >> n >> q;
	read(n); read(q);

	int a, b, c;
	for (int i=1; i<n; i++) {
		//cin >> a >> b >> c;
		read(a); read(b); read(c);
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	euler_tour(1);

	vector<Query> queries;
	for (int i=0; i<q; i++) {
		//cin >> a >> b;
		read(a); read(b);
		queries.push_back({i,min(a,b),max(a,b)});
	}
	sort(queries.begin(), queries.end());

	int left = 0;
	int right = 0;
	set<int> outside;
	for (int i=0; i<N; i++) {
		outside.insert(i);
	}

	auto solve = [&] (int a, int b) {
		if (b jj
	};

	for (const Query& it : queries) {
		ans[it.i] = solve(it.a, it.b);
	}

	for (int i=0; i<q; i++) {
		cout << ans[i] << nl;
	}

	return 0;
}
