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

vector<vector<int>> op_init = {
	{ 0, 0, 0, 0, 1, 1, 0, 1, 2 },
	{ 0, 1, 2, 1, 1, 2, 2, 2, 2 },
	{ 2, 2, 2, 1, 2, 2, 0, 1, 2 },
	{ 2, 0, 0, 0, 2, 0, 0, 0, 2 }
};

vector<vector<int>> initial = {
	{ 0, 0, 0, 1, 1, 1, 2, 2, 2 },
	{ 0, 1, 2, 0, 1, 2, 0, 1, 2 }
};

ll compose(const ll& a, const ll& b, const ll& op) {
	ll res = 0;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			int i = 3*x + y;
			int left = 3 & (a >> (2*i));
			int right = 3 & (b >> (2*i));
			int j = left*3 + right;
			res |= (3 & (op >> (2*j))) << (2*i);
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	unordered_set<ll> bfs;
	vector<ll> operation;
	for (const auto& v : initial) {
		ll a = 0;
		for (int j=0; j<9; j++) {
			a |= v[j] << (2*j);
		}
		bfs.insert(a);
	}
	for (const auto& v : op_init) {
		ll a = 0;
		for (int j=0; j<9; j++) {
			a |= v[j] << (2*j);
		}
		operation.push_back(a);
	}

	//while (clock() < 8.420*CLOCKS_PER_SEC) {
	for (int i = 0; i <= 4; i++) {
		vector<ll> add;
		for (const ll& one : bfs) {
			for (const ll& two : bfs) {
				for (const ll& op : operation) {
					add.push_back(compose(one, two, op));
				}
			}
		}
		for (const ll& v : add) {
			bfs.insert(v);
		}
	}
	cerr << "found " << bfs.size() << " grids" << nl;

	int n;
	cin >> n;

	for (int i=0; i<n; i++) {
		ll a = 0;
		for (int j=0; j<9; j++) {
			char c;
			cin >> c;
			if (c == 'F') a |= 0 << (2*j);
			else if (c == 'T') a |= 2 << (2*j);
			else a |= 1 << (2*j);
		}
		cout << (bfs.count(a) ? "definable" : "undefinable") << nl;
	}

	return 0;
}
