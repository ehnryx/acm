//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

pt vec(const pair<int,int>& a, const pair<int,int>& b) {
	return pt(b.second - a.second, b.first - a.first);
}

const int N = 800;
int dist[N][N];
pair<int,int> pre[N][N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
	freopen("straight.in", "r", stdin);
	freopen("straight.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;
	string line;
	getline(cin, line);
	vector<string> g;
	for(int i=0; i<2*n-1; i++) {
		getline(cin, line);
		g.push_back(line);
	}
	reverse(g.begin(), g.end());

	memset(dist, INF, sizeof dist);
	queue<pair<int,int>> bfs;
	bfs.emplace(2*n-2, 2*m-2);
	dist[2*n-2][2*m-2] = 0;
	while(!bfs.empty()) {
		auto [i, j] = bfs.front();
		bfs.pop();
		if(i > 0 && g[i-1][j] != ' ' && dist[i-2][j] == INF) {
			bfs.emplace(i-2, j);
			dist[i-2][j] = dist[i][j] + 1;
			pre[i-2][j] = make_pair(i, j);
		}
		if(j > 0 && g[i][j-1] != ' ' && dist[i][j-2] == INF) {
			bfs.emplace(i, j-2);
			dist[i][j-2] = dist[i][j] + 1;
			pre[i][j-2] = make_pair(i, j);
		}
		if(i+2 < 2*n && g[i+1][j] != ' ' && dist[i+2][j] == INF) {
			bfs.emplace(i+2, j);
			dist[i+2][j] = dist[i][j] + 1;
			pre[i+2][j] = make_pair(i, j);
		}
		if(j+2 < 2*m && g[i][j+1] != ' ' && dist[i][j+2] == INF) {
			bfs.emplace(i, j+2);
			dist[i][j+2] = dist[i][j] + 1;
			pre[i][j+2] = make_pair(i, j);
		}
	}

	vector<pair<int,int>> path = { make_pair(0, 0) };
	for(int i=0, j=0, dx=0, dy=0; i<2*n-2 || j<2*m-2; ) {
		int ni = i + 2*dx;
		int nj = j + 2*dy;
		//cerr<<i<<" "<<j<<" -> "<<ni<<" "<<nj<<" w/ dxdy= "<<dx<<" "<<dy<<nl;
		if(0 <= ni && 0 <= nj && ni < 2*n && nj < 2*m && g[i+dx][j+dy] != ' ' && dist[ni][nj] == dist[i][j] - 1) {
			i = ni;
			j = nj;
		} else {
			tie(ni, nj) = pre[i][j];
			dx = (ni - i) / 2;
			dy = (nj - j) / 2;
			tie(i, j) = pre[i][j];
		}
		path.emplace_back(i, j);
	}

	cout << (path[1].first > 0 ? 'N' : 'E') << nl;
	for(int t=1; t+1<path.size(); t++) {
		pt turn = vec(path[t], path[t+1]) / vec(path[t-1], path[t]);
		if(turn.imag() > 0.5) {
			cout << 'L';
		} else if(turn.imag() < -0.5) {
			cout << 'R';
		} else {
			cout << 'F';
		}
	}
	cout << nl;

	return 0;
}
