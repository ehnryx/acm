//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 4;
unsigned get_hash(const vector<string>& g) {
	unsigned h = 0;
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			h = h<<2 | (g[i][j] == 'B' ? 0 : (g[i][j] == 'G' ? 1 : (g[i][j] == 'R' ? 2 : 3)));
		}
	}
	return h;
}

unsigned rm = 0b0000'0000'0000'0000'0000'0000'1111'1111;
unsigned cm = 0b0000'0011'0000'0011'0000'0011'0000'0011;

void rot_row(unsigned& h, int i) {
	unsigned row = h >> (i*8) & rm;
	unsigned shift = ((row >> 2) | (row << 6)) & rm;
	h ^= (row ^ shift) << (i*8);
}

void ref_row(unsigned& h, int i) {
	unsigned row = h >> (i*8) & rm;
	unsigned shift = ((row >> 4) | (row << 4)) & rm;
	h ^= (row ^ shift) << (i*8);
}

void rot_col(unsigned& h, int i) {
	unsigned col = h >> (i*2) & cm;
	unsigned shift = ((col >> 8) | (col << 24)) & cm;
	h ^= (col ^ shift) << (i*2);
}

void ref_col(unsigned& h, int i) {
	unsigned col = h >> (i*2) & cm;
	unsigned shift = ((col >> 16) | (col << 16)) & cm;
	h ^= (col ^ shift) << (i*2);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	queue<pair<unsigned, int>> bfs;
	unordered_map<unsigned, int> memo[2];

	vector<string> g = { "RRRR", "GGGG", "BBBB", "YYYY" };
	unsigned s = get_hash(g);
	memo[0][s] = 0;
	bfs.push(make_pair(s, 0));

	for(int i=0; i<N; i++) {
		cin >> g[i];
	}
	unsigned t = get_hash(g);
	if(memo[0].count(t)) {
		cout << 0 << nl;
		return 0;
	}
	memo[1][t] = 0;
	bfs.push(make_pair(t, 1));

	while(!bfs.empty()) {
		auto [u, j] = bfs.front();
		bfs.pop();
		int d = memo[j][u];
		for(int i=0; i<N; i++) {
			// row
			rot_row(u, i);
			if(!memo[j].count(u)) {
				if(memo[j^1].count(u)) {
					cout << d + 1 + memo[j^1][u] << nl;
					return 0;
				}
				memo[j][u] = d + 1;
				if(d < 12) bfs.push(make_pair(u, j));
			}
			ref_row(u, i);
			if(!memo[j].count(u)) {
				if(memo[j^1].count(u)) {
					cout << d + 1 + memo[j^1][u] << nl;
					return 0;
				}
				memo[j][u] = d + 1;
				if(d < 12) bfs.push(make_pair(u, j));
			}
			rot_row(u, i);
			// col
			rot_col(u, i);
			if(!memo[j].count(u)) {
				if(memo[j^1].count(u)) {
					cout << d + 1 + memo[j^1][u] << nl;
					return 0;
				}
				memo[j][u] = d + 1;
				if(d < 12) bfs.push(make_pair(u, j));
			}
			ref_col(u, i);
			if(!memo[j].count(u)) {
				if(memo[j^1].count(u)) {
					cout << d + 1 + memo[j^1][u] << nl;
					return 0;
				}
				memo[j][u] = d + 1;
				if(d < 12) bfs.push(make_pair(u, j));
			}
			rot_col(u, i);
		}
	}

	return 0;
}
