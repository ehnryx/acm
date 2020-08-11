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
	os << "{ ";
	for (const T& it : v) os << it << " ";
	os << "}"; return os;
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

struct Edge {
	int id, cost;
	Edge() {}
	Edge(int i, int c): id(i), cost(c) {}
};
vector<Edge> graph[3001];

struct Node {
	int id, taken; 
	ll dist;
	Node() {}
	Node(int i, ll d, int t=0):
		id(i), dist(d), taken(t) {}
	bool operator < (const Node& other) const {
		return dist > other.dist;
	}
};

ll normal_dijkstra(int n, int s, int t) {
	ll dist[n+1];
	memset(dist, -1, sizeof dist);

	priority_queue<Node> next;
	next.push(Node(s, 0));
	while (!next.empty()) {
		Node cur = next.top();
		next.pop();
		if (dist[cur.id] == -1) {
			if (cur.id == t) {
				return cur.dist;
			}
			dist[cur.id] = cur.dist;
			for (const Edge& e : graph[cur.id]) {
				if (dist[e.id] == -1) 
					next.push(Node(e.id, cur.dist + e.cost));
			}
		}
	}

	return -1;
}

ll magic_dijkstra(int n, int k, int s, int t, int bound, int low, int& res) {
	ll dist[n+1][k+1];
	memset(dist, -1, sizeof dist);

	res = 0;

	priority_queue<Node> next;
	next.push(Node(s, 0, 0));
	while (!next.empty()) {
		Node cur = next.top();
		next.pop();

		if (dist[cur.id][cur.taken] == -1) {
			if (cur.id == t) {
				if (cur.taken == k) {
					res = -1;
					return cur.dist;
				}
			}
			dist[cur.id][cur.taken] = cur.dist;

			for (const Edge& e : graph[cur.id]) {
				if (e.cost > bound) {
					if (cur.taken < k)
						next.push(Node(e.id, e.cost + cur.dist, cur.taken+1));
				} else if (e.cost < bound) {
					if (e.cost <= low) 
						next.push(Node(e.id, cur.dist, cur.taken));
				} else {
					if (e.cost <= low)
						next.push(Node(e.id, cur.dist, cur.taken));
					if (cur.taken < k)
						next.push(Node(e.id, e.cost + cur.dist, cur.taken+1));
				}
			}
		}
	}

	if (!res) res = 1;
	return INFLL;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	int a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		graph[a].push_back(Edge(b,c));
		graph[b].push_back(Edge(a,c));
	}

	int res;
	ll left, right, mid;
	left = 0;
	right = INF;
	ll ans = normal_dijkstra(n, 1, n);
	while (left <= right) {
		mid = (left + right) / 2;
		ll inleft, inright, inmid;
		bool reachable = false;
		inleft = 0;
		inright = INF;
		while (inleft <= inright) {
			inmid = (inleft + inright) / 2;
			if (mid < inmid)
				res = 1;
			else 
				ans = min(ans, magic_dijkstra(n, k, 1, n, mid, inmid, res));
			if (res > 0) {
				inright = inmid-1;
			}
			else if (res < 0) {
				inleft = inmid+1;
				reachable = true;
			}
		}
		if (reachable)
			left = mid+1;
		else 
			right = mid-1;
	}

	cerr << "left: " << left << "   right: " << right << nl;
	cerr << "bound: " << mid << nl;
	cout << ans << nl;

	return 0;
}
