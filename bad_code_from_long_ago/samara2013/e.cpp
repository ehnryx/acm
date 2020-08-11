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

// MODINT
template<int MOD> struct ModInt {
	ll x;
	ModInt(ll n=0) { n %= MOD; if (n < 0) n += MOD; x = n; }
	int get() const { return (int) x; }
	ModInt operator + (const ModInt& other) { return ModInt(x + other.x); }
	ModInt operator - (const ModInt& other) { return ModInt(x + MOD - other.x); }
	ModInt operator * (const ModInt& other) { return ModInt(x * other.x); } 
	ModInt& operator += (const ModInt& other) { x = (x + other.x) % MOD; return *this; }
	ModInt& operator -= (const ModInt& other) { x = (x + MOD - other.x) % MOD; return *this; }
	ModInt& operator *= (const ModInt& other) { x = (x * other.x) % MOD; return *this; }
};

struct Node {
	pair<int,int> pos;
	int dist;
	Node(pair<int,int> pos, int dist) {
		this->pos = pos;
		this->dist = dist;
	}
	bool operator < (const Node& other) const {
		return other.dist < this->dist;
	}
};
int dijkstra(int n, int m, const pair<int,int>& start, const pair<int,int>& end, const vector<vector<char>>& grid) {
	int dist[n][m];
	memset(dist, -1, sizeof(dist));
	priority_queue<Node> next;
	next.push(Node(start, 0));
	Node curr(start, 0);
	while (!next.empty()) {
		curr = next.top();
		next.pop();
		if (curr.pos == end)
			return curr.dist;
		if (dist[curr.pos.first][curr.pos.second] == -1) {
			int i = curr.pos.first;
			int j = curr.pos.second;
			dist[i][j] = curr.dist;
			if (i > 0 && dist[i-1][j] == -1 && grid[i-1][j] == '.')
				next.push(Node(pair<int,int>(i-1,j), curr.dist+1));
			if (i < n-1 && dist[i+1][j] == -1 && grid[i+1][j] == '.')
				next.push(Node(pair<int,int>(i+1,j), curr.dist+1));
			if (j > 0 && dist[i][j-1] == -1 && grid[i][j-1] == '.')
				next.push(Node(pair<int,int>(i,j-1), curr.dist+1));
			if (j < m-1 && dist[i][j+1] == -1 && grid[i][j+1] == '.')
				next.push(Node(pair<int,int>(i,j+1), curr.dist+1));
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n, m;
	string line;
	vector<vector<char>> first, second;
	vector<vector<char>> both;
	cin >> n >> m;
	first.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> line;
		for (int j = 0; j < m; j++)
			first[i].push_back(line[j]);
	}
	second.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> line;
		for (int j = 0; j < m; j++) 
			second[i].push_back(line[j]);
	}
	both.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (first[i][j] == '#' || second[i][j] == '#')
				both[i].push_back('#');
			else
				both[i].push_back('.');
		}
	}
	int i = dijkstra(n, m, pair<int,int>(0,0), pair<int,int>(n-1,m-1), first);
	int j = dijkstra(n, m, pair<int,int>(0,0), pair<int,int>(n-1,m-1), second);
	int k = dijkstra(n, m, pair<int,int>(0,0), pair<int,int>(n-1,m-1), both);
	if (i == k && j == k && k != -1) cout << "YES" << nl;
	else cout << "NO" << nl;

	return 0;
}
