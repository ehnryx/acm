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

struct Node {
	int id, indeg;
	Node(){}
	Node(int i, int d): id(i), indeg(d) {}
	bool operator < (const Node& other) const {
		return indeg > other.indeg;
	}
};

const int N = 1e6+1;
unordered_set<int> adj[N];
unordered_set<int> rev[N];
bitset<N> vis;
bitset<N> take;
priority_queue<Node> order;

void init() {
	take.set();
}

void solve(int s) {
	for (int x : rev[s]) {
		adj[x].erase(s);
		take[x] = false;
		//cerr << "set " << x << " to false from " << s << " in reverse" << nl;
	}
	rev[s].clear();

	queue<int> nxt;
	nxt.push(s);
	while (!nxt.empty()) {
		int cur = nxt.front();
		nxt.pop();

		if (rev[cur].empty()) {
			vis[cur] = true;
			for (int x : adj[cur]) {
				nxt.push(x);
				rev[x].erase(cur);
				if (take[cur]) {
					take[x] = false;
					//cerr << "set " << x << " to false from " << cur << nl;
				}
			}
			adj[cur].clear();
		}
		else {
			order.push(Node(cur, rev[cur].size()));
		}
	}
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

	int n, m;
	//cin >> n >> m;
	read(n); read(m);

	int a, b;
	for (int i = 0; i < m; i++) {
		//cin >> a >> b;
		read(a); read(b);
		adj[a].insert(b);
		rev[b].insert(a);
	}

	for (int i = 1; i <= n; i++) {
		order.push(Node(i, rev[i].size()));
	}

	while (!order.empty()) {
		Node cur = order.top();
		order.pop();
		if (!vis[cur.id]) {
			solve(cur.id);
		}
	}

	vector<int> ans;
	for (int i = 1; i <= n; i++) {
		if (take[i]) {
			ans.push_back(i);
		}
	}

	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
