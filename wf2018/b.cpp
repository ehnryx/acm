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

const int N = 1e6;
unordered_set<int> adj[N], rev[N];
bool vis[2][N];

void init() {
	memset(vis, 0, sizeof vis);
}

void reverse(int);
void forward(int it) {
	vis[0][it] = true;
	for (int x : adj[it]) {
		if (!vis[1][x]) {
			reverse(x);
		}
	}
}
void reverse(int it) {
	vis[1][it] = true;
	for (int x : rev[it]) {
		if (!vis[0][x]) {
			forward(x);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	string s;
	getline(cin, s);

	map<string,int> index;
	vector<string> line;
	unordered_set<int> edges;
	int id = 1;
	int pre = -1;

	istringstream ss(s);
	while (ss >> s) {
		char tail = 0;
		if (s.back() == '.') {
			line.push_back(s);
			tail = '.';
			s.pop_back();
		}
		else if (s.back() == ',') {
			tail = ',';
			s.pop_back();
			line.push_back(s);
		} else {
			line.push_back(s);
		}

		if (!index.count(s)) {
			index[s] = id++;
		}

		int cur = index[s];
		if (pre != -1) {
			adj[pre].insert(cur);
			rev[cur].insert(pre);
		}

		if (tail == '.') {
			pre = -1;
		} else {
			pre = cur;
			if (tail == ',') {
				edges.insert(pre);
			}
		}
	}

	for (int it : edges) {
		if (!vis[0][it]) {
			forward(it);
		}
	}

	for (const string& it : line) {
		cout << it;
		if (vis[0][index[it]]) cout << ',';
		cout << ' ';
	}

	return 0;
}
