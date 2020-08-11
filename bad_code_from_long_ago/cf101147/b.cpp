#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int n, length, width;

inline double sqr(double x) {
	return x*x;
}

struct Rect {
	int top, bot, left, right;
	Rect(int h, int w, int d, int k) {
		bot = d;
		top = min(length, bot + h);
		if (k == 0) {
			left = 0;
			right = left + w;
		} else {
			right = width;
			left = right - w;
		}
	}
	double dist(const Rect& other) {
		if (top >= other.bot && bot <= other.top) {
			int res = min(abs(right - other.left), abs(left - other.right));
			if (left <= other.right && right >= other.left)
				return min(res, min(abs(top - other.bot), abs(bot - other.top)));
			else
				return res;
		}
		else if (left <= other.right && right >= other.left)
			return min(abs(top - other.bot), abs(bot - other.top));
		else if (right < other.left && top < other.bot)
			return sqrt(sqr(other.left-right) + sqr(other.bot-top));
		else if (right < other.left && bot > other.top)
			return sqrt(sqr(other.left-right) + sqr(bot-other.top));
		else if (left > other.right && top < other.bot)
			return sqrt(sqr(left-other.right) + sqr(other.bot-top));
		else if (left > other.right && bot > other.top)
			return sqrt(sqr(left-other.right) + sqr(bot-other.top));
		else 
			assert(false);
	}
};
ostream& operator << (ostream& os, const Rect& r) {
	os << "{t: " << r.top << " b: " << r.bot << " l: " << r.left << " r: " << r.right << "}";
	return os;
}

struct Edge {
	int id;
	double dist;
	Edge(int i=-1, double d=-1): id(i), dist(d) {}
	bool operator < (const Edge& other) const {
		return dist > other.dist;
	}
};

double dijkstra(const vector<vector<Edge>>& g, int s, int t) {
	static double dist[102];
	for (int i = 0; i < 102; i++) {
		dist[i] = -1;
	}

	priority_queue<Edge> next;
	next.push(Edge(s, 0));
	while (!next.empty()) {
		Edge cur = next.top();
		next.pop();
		if (cur.id == t) {
			return cur.dist;
		}

		if (dist[cur.id] == -1) {
			dist[cur.id] = cur.dist;
			for (const Edge& e : g[cur.id]) {
				if (dist[e.id] == -1) 
					next.push(Edge(e.id, cur.dist + e.dist));
			}
		}
	}
	return -1;
}

int main() {
	freopen("street.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(6);

	int h, w, d, k;
	vector<Rect> nodes;
	vector<vector<Edge>> graph;

	int T;
	cin >> T;
	while (T--) {
		nodes.clear();
		graph.clear();
		cin >> n >> length >> width;
		graph.resize(n+2);
		for (int i = 0; i < n; i++) {
			cin >> h >> w >> d >> k;
			nodes.push_back(Rect(h, w, d, k));
		}
		nodes.push_back(Rect(0, width, 0, 0));
		nodes.push_back(Rect(0, width, length, 0));

		for (int i = 0; i < n+2; i++) {
			for (int j = 0; j < i; j++) {
				double c = nodes[i].dist(nodes[j]);
				//cerr << "dist between " << i << " and " << j << " is " << c << nl;
				//cerr << "RECT: " << nodes[i] << " " << nodes[j] << nl;
				graph[i].push_back(Edge(j, c));
				graph[j].push_back(Edge(i, c));
			}
		}

		cout << dijkstra(graph, n, n+1) << nl;
	}

	return 0;
}
