#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 5e4;
struct DSU {
	int root[N+1];
	DSU() { memset(root, -1, sizeof root); }
	int find(int i) {
		if (root[i] == -1) return i;
		return root[i] = find(root[i]);
	}
	int link(int i, int j) {
		if (find(i) == find(j))
			return false;
		root[find(i)] = find(j);
		return true;
	}
};

struct Edge {
	int a, b, c;
	Edge() {}
	Edge(int a, int b, int c): a(a), b(b), c(c) {}
	bool operator < (const Edge& other) const {
		return c < other.c;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	vector<Edge> edges;
	int a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		edges.push_back(Edge(a, b, c));
	}
	sort(edges.begin(), edges.end());

	DSU dsu;
	int cur = n;
	int ans = 0;
	for (const Edge& e : edges) {
		if (cur <= k) {
			break;
		}
		if (dsu.link(e.a, e.b)) {
			ans += e.c;
			cur--;
		}
	}

	cout << ans << nl;

	return 0;
}
