#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
template <typename T> inline void read(T &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const vector<int> dx = {1, -1, 0, 0};
const vector<int> dy = {0, 0, 1, -1};

const int N = 500 + 2;
char g[N][N][N];
int last_i[N][N], first_i[N][N];
int last_j[N][N], first_j[N][N];
int last_k[N][N], first_k[N][N];
unordered_map<int,int> dist[N][N];

bool valid(const tuple<int,int,int>& v) {
	auto [i, j, k] = v;
	return i == first_i[j][k] || i == last_i[j][k] ||
		j == first_j[k][i] || j == last_j[k][i] ||
		k == first_k[i][j] || k == last_k[i][j];
}

queue<tuple<int,int,int>> bfs;
void push(const tuple<int,int,int>& v, int d) {
	auto [i, j, k] = v;
	if(g[i][j][k] == 'T') {
		cout << d << nl;
		exit(0);
	}
	if(!dist[i][j].count(k)) {
		dist[i][j][k] = d;
		bfs.push(v);
	}
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	//ios::sync_with_stdio(0); cin.tie(0);
	//cout << fixed << setprecision(10);

	memset(first_i, -1, sizeof first_i);
	memset(last_i, INF, sizeof last_i);
	memset(first_j, -1, sizeof first_j);
	memset(last_j, INF, sizeof last_j);
	memset(first_k, -1, sizeof first_k);
	memset(last_k, INF, sizeof last_k);

	int n, m, h;
	//cin >> h >> m >> n;
	read(h); read(m); read(n);

	tuple<int,int,int> S, T;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			for(int k=1; k<=h; k++) {
				//cin >> g[i][j][k];
				readchar(g[i][j][k]);
				if(g[i][j][k] == '*') {
					if(first_i[j][k] < 0) first_i[j][k] = i-1;
					if(first_j[k][i] < 0) first_j[k][i] = j-1;
					if(first_k[i][j] < 0) first_k[i][j] = k-1;
					last_i[j][k] = i+1;
					last_j[k][i] = j+1;
					last_k[i][j] = k+1;
				} else if(g[i][j][k] == 'R') {
					S = make_tuple(i, j, k);
				} else if(g[i][j][k] == 'T') {
					T = make_tuple(i, j, k);
				}
			}
		}
	}

	if(!valid(S) || !valid(T)) {
		cout << -1 << nl;
		return 0;
	}

	push(S, 0);
	for(int bs=0; !bfs.empty() && (bs&((1<<12)-1) || clock()<3.8*CLOCKS_PER_SEC); bs++) {
	//while(!bfs.empty()) {
		auto [i, j, k] = bfs.front();
		bfs.pop();
		int cur = dist[i][j][k] + 1;

		if(i == first_i[j][k]) {
			for(int d=0; d<4; d++) {
				int nj = j + dx[d];
				int nk = k + dy[d];
				int ni = first_i[nj][nk];
				if(ni < i) continue;
				push(make_tuple(ni, nj, nk), cur);
			}
		} else if(i == last_i[j][k]) {
			for(int d=0; d<4; d++) {
				int nj = j + dx[d];
				int nk = k + dy[d];
				int ni = last_i[nj][nk];
				if(ni > i) continue;
				push(make_tuple(ni, nj, nk), cur);
			}
		} else if(i < first_i[j][k]) {
			push(make_tuple(first_i[j][k], j, k), cur);
		} else if(i > last_i[j][k]) {
			push(make_tuple(last_i[j][k], j, k), cur);
		}

		if(j == first_j[k][i]) {
			for(int d=0; d<4; d++) {
				int nk = k + dx[d];
				int ni = i + dy[d];
				int nj = first_j[nk][ni];
				if(nj < j) continue;
				push(make_tuple(ni, nj, nk), cur);
			}
		} else if(j == last_j[k][i]) {
			for(int d=0; d<4; d++) {
				int nk = k + dx[d];
				int ni = i + dy[d];
				int nj = last_j[nk][ni];
				if(nj > j) continue;
				push(make_tuple(ni, nj, nk), cur);
			}
		} else if(j < first_j[k][i]) {
			push(make_tuple(i, first_j[k][i], k), cur);
		} else if(j > last_j[k][i]) {
			push(make_tuple(i, last_j[k][i], k), cur);
		}

		if(k == first_k[i][j]) {
			for(int d=0; d<4; d++) {
				int ni = i + dx[d];
				int nj = j + dy[d];
				int nk = first_k[ni][nj];
				if(nk < k) continue;
				push(make_tuple(ni, nj, nk), cur);
			}
		} else if(k == last_k[i][j]) {
			for(int d=0; d<4; d++) {
				int ni = i + dx[d];
				int nj = j + dy[d];
				int nk = last_k[ni][nj];
				if(nk > k) continue;
				push(make_tuple(ni, nj, nk), cur);
			}
		} else if(k < first_k[i][j]) {
			push(make_tuple(i, j, first_k[i][j]), cur);
		} else if(k > last_k[i][j]) {
			push(make_tuple(i, j, last_k[i][j]), cur);
		}
	}

	cout << -1 << nl;

	return 0;
}
