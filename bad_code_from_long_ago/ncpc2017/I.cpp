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
const int N = 505;

vector<int> adj[N];

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n; cin >> n;
	map<string, int> dumb;
	map<int, string> undumb;
	int id = 0;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		dumb[s] = id;
		undumb[id++] = s;
	}

	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		int k; cin >> k;
		getline(cin, s);
		while (k--) {
			getline(cin, s);
			istringstream in(s);
			string a; in >> a;
			while (in >> a) {
				if (a.back() == ',')
					a.pop_back();
				adj[i].push_back(dumb[a]);
			}
		}
	}

	vector<vector<int>> dist(n, vector<int>(n, INF));
	for (int i = 0; i < n; i++) {
		for (int j : adj[i])
			dist[i][j] = 1;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (dist[i][j] + dist[j][k] < dist[i][k])
					dist[i][k] = dist[i][j] + dist[j][k];
	int b1 = INF, b2;
	for (int i = 0; i < n; i++)
		if (dist[i][i] < b1)
			b1 = dist[i][i], b2 = i;
	if (b1 == INF) {
		cout << "SHIP IT" << endl;
		return 0;
	}

	vector<int> par(n, -1);
	queue<int> todo;
	todo.push(b2);
	vector<bool> visited(n);
	visited[b2] = 1;
	int last;
	while (1) {
		int cur = todo.front(); todo.pop();
		visited[cur] = 1;
		for (int i : adj[cur]) {
			if (i == b2) {
				last = cur;
				goto out;
			}
			if (!visited[i]) {
				visited[i] = 1;
				par[i] = cur;
				todo.push(i);
			}
		}
	}
out:
	vector<string> ans;
	int cur = last;
	while (cur != -1) {
		ans.push_back(undumb[cur]);
		cur = par[cur];
	}

	for (int i  = ans.size()-1; i >= 0; i--)
		cout << ans[i] << " ";
	cout << endl;

	return 0;
}
