#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Graph {
	int vertices;
	vector<vector<pair<int,int>>> g;
	Graph(int n) {
		vertices = n;
		g.resize(n);
	}
	void add_edge(int a, int b, int c) {
		g[a].push_back(pii(b,c));
		g[b].push_back(pii(a,c));
	}
	int dijkstra(int s, int t) {
		struct Node {
			int id;
			int safe;
			Node (int i = -1, int val = INF) {
				id = i;
				safe = val;
			}
			bool operator < (const Node& other) const {
				return other.safe > safe;
			}
		};
		Node curr;
		priority_queue<Node> next;
		int dist[vertices];
		memset(dist, -1, sizeof(dist));
		next.push(Node(s, INF));
		while (!next.empty()) {
			curr = next.top();
			next.pop();
			if (curr.id == t)
				return curr.safe;
			if (dist[curr.id] == -1) {
				//cerr << "visit " << curr.id << " set to " << curr.safe << nl;
				dist[curr.id] = curr.safe;
				for (const pii& e : g[curr.id]) {
					if (dist[e.first] == -1)
						next.push(Node(e.first, min(curr.safe, e.second)));
				}
			}
		}
		return -1;
	}
};

struct Node {
	int id;
	int start, end;
	Node(int i=0, int a=0, int b=0) {
		id = i;
		start = a;
		end = b;
	}
	int distance(const Node& other, const Node& acm) const {
		int res;
		if (start <= other.start && other.end <= end) {
			return (other.end - other.start - (acm.end - acm.start));
		} else if (other.start <= start && end <= other.end) {
			return (end - start - (acm.end - acm.start));
		} else if (other.start < end && end <= other.end) {
			return (end - other.start - (acm.end - acm.start));
		} else if (other.start <= start && start < other.end) {
			return (other.end - start - (acm.end - acm.start));
		} else {
			exit(-1);
		}
	}
	bool connected(int a, int b) const {
		return (start <= a && a < end) || (start < b && b <= end)
			|| (a <= start && start < b) || (a < end && end <= b);
	}
	bool operator < (const Node& other) const {
		return start < other.start;
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	Node acm;
	int lanes, cars, range;
	int lane, length, dist;
	cin >> lanes >> cars >> range;
	vector<Node> nodes[lanes];
	int id = 0;
	for (int i = 0; i < lanes; i++) {
		nodes[i].push_back(Node(id++, 0, range));
	}
	for (int i = 0; i < cars; i++) {
		cin >> lane >> length >> dist;
		if (i > 0) for (int j = 0; j < nodes[lane].size(); j++) {
			if (nodes[lane][j].connected(dist, dist+length)) {
				nodes[lane].push_back(Node(id++, dist+length, nodes[lane][j].end));
				nodes[lane][j].end = dist;
				break;
			}
		} else {
			acm.start = dist;
			acm.end = dist+length;
		}
	}

#ifdef DEBUG
	for (int i = 0; i < lanes; i++)
	for (Node it: nodes[i])
		cout << it.id << ": " << it.start << " " << it.end << nl;
#endif

	Graph graph(cars + lanes + 7);
	int source, sink, firstdist;
	sink = cars + lanes + 6;
	for (int l = 0; l < lanes-1; l++) {
		for (const Node& nd : nodes[l]) {
			if (l == 0) if (nd.connected(acm.start, acm.end)) {
				source = nd.id;
				firstdist = min(acm.start - nd.start, nd.end - acm.end);
			}
			for (const Node& next : nodes[l+1]) {
				if (nd.connected(next.start, next.end)) {
					int d = nd.distance(next, acm);
					if (d >= 0) graph.add_edge(nd.id, next.id, d);
				}
			}
		}
	}
	for (const Node& nd : nodes[lanes-1]) {
		graph.add_edge(nd.id, sink, INF);
	}
	int ans = graph.dijkstra(source, sink);
	if (ans == -1) cout << "Impossible" << nl;
	else cout << fixed << setprecision(10) << min(ans/2.0, 1.0*firstdist) << nl;

	return 0;
}
