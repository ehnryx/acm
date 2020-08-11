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
	int size;
	int g[300][300];
	Graph(int n) {
		size = n;
	}

	void add_edge(int a, int b, int w) {
		g[a][b] = w;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
				cout << g[i][j] << " ";
			cout << nl;
		}
	}

	bool valid() {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				for (int k = 0; k < size; k++)
					if (g[i][k] + g[k][j] < g[i][j])
						return false;
		return true;
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n, weight;
	cin >> n;
	Graph graph(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> weight;
			graph.add_edge(i,j,weight);
		}
	}
	// check
	if (graph.valid())
		graph.print();
	else 
		cout << -1 << nl;

	return 0;
}
