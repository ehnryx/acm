#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
#pragma GCC optimize("fast-math")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

mt19937 rng(7);

const char nl = '\n';
typedef float ld;
typedef complex<ld> pt;

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	os << "[ ";
	for(const T& it : v) {
		os << " " << it << ", ";
	}
	return os << "]";
}

const ld EPS = 1e-7;

const int N = 1000;
ld x[N], y[N];

int distance(int i, int j) {
	return round(sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j])));
}

ld cp(const pt& a, const pt& b) {
	return imag(conj(a) * b);
}

int sgn(ld v) {
	return v < -EPS ? -1 : v <= EPS ? 0 : 1;
}

bool seg_x_seg(int i, int j, int ii, int jj) {
	pt a(x[i], y[i]), b(x[j], y[j]);
	pt c(x[ii], y[ii]), d(x[jj], y[jj]);
	int r1 = sgn(cp(a-b, c-b)), r2 = sgn(cp(a-b, d-b));
	int r3 = sgn(cp(c-d, a-d)), r4 = sgn(cp(c-d, b-d));
	if(!r1 && !r2 && !r3) return false;
	return r1*r2 < 0 && r3*r4 < 0;
}

int adj[N][N];

void remove_crossings(int n, vector<int>& tour) {
	for(int i=n-1, j=0; j<n; i=j++) {
		for(int ii=i, jj=j; jj<n; ii=jj++) {
			if(i == ii || i == jj || ii == j) continue;
			if(seg_x_seg(tour[i], tour[j], tour[ii], tour[jj])) {
				reverse(tour.begin() + j, tour.begin() + ii + 1);
				//break;
			}
		}
	}
}

int naive_tsp(int n, vector<int>& tour) {
	vector<bool> used(n);
	tour[0] = rng()%n;
	used[tour[0]] = true;
	int M = rng()%21;
	for(int i=1; i<n; i++) {
		int best = M ? rng()%(M*n) : n;
		if(best >= n || used[best]) {
			best = -1;
			for(int j=0; j<n; j++) {
				if(!used[j] && (best == -1 || adj[tour[i-1]][j] < adj[tour[i-1]][best])) {
					best = j;
				}
			}
		}
		tour[i] = best;
		used[best] = true;
	}
	remove_crossings(n, tour);
	int sum = 0;
	for(int i=n-1, j=0; j<n; i=j++) {
		sum += adj[tour[i]][tour[j]];
	}
	return sum;
}

void dfs_shortcut(int u, vector<vector<int>>& tree, vector<int>& tour) {
	shuffle(tree[u].begin(), tree[u].end(), rng);
	tour.push_back(u);
	for(int v : tree[u]) {
		dfs_shortcut(v, tree, tour);
	}
}

int mst_tsp(int n, vector<int>& tour) {
	vector<int> dist(n, -1), par(n, -1);
	vector<bool> vis(n);
	vector<vector<int>> tree(n);
	priority_queue<pair<int,int>> prims;
	prims.emplace(0, 0);
	dist[0] = 0;
	while(!prims.empty()) {
		auto [d, u] = prims.top();
		prims.pop();
		if(vis[u]) continue;
		vis[u] = true;
		if(par[u] != -1) {
			tree[par[u]].push_back(u);
		}
		d = -d;
		for(int v=0; v<n; v++) {
			if(vis[v]) continue;
			if(dist[v] == -1 || max(d, adj[u][v]) < dist[v]) {
				dist[v] = max(d, adj[u][v]);
				par[v] = u;
				prims.emplace(-dist[v], v);
			}
		}
	}

	tour.clear();
	dfs_shortcut(0, tree, tour);
	int sum = 0;
	for(int i=n-1, j=0; j<n; i=j++) {
		sum += adj[tour[i]][tour[j]];
	}
	return sum;
}

void solve_opt(int);

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> x[i] >> y[i];
		for(int j=0; j<i; j++) {
			adj[i][j] = adj[j][i] = distance(i, j);
		}
	}

	if(n <= 20) {
		solve_opt(n);
		return 0;
	}

	int ans = -1;
	vector<int> res(n), tour(n);

	const int mstcnt = 7;
	for(int mst=0; mst<mstcnt; mst++) {
		int cur = mst_tsp(n, tour);
		if(ans == -1 || cur < ans) {
			ans = cur;
			swap(res, tour);
		}
	}

	int naivecnt = 0;
	while(clock()<1.90*CLOCKS_PER_SEC) {
		naivecnt++;
		int cur = naive_tsp(n, tour);
		if(ans == -1 || cur < ans) {
			ans = cur;
			swap(res, tour);
		}
	}

	for(int i=0; i<n; i++) {
		cout << res[i] << nl;
	}
	cerr << "length: " << ans << nl;
	cerr << "mst iterations: " << mstcnt << nl;
	cerr << "naive iterations: " << naivecnt << nl;

	return 0;
}

/*
GreedyTour
   tour[0] = 0
   used[0] = true
   for i = 1 to n-1
      best = -1
      for j = 0 to n-1
         if not used[j] and (best = -1 or dist(tour[i-1],j) < dist(tour[i-1],best))
            best = j
      tour[i] = best
      used[best] = true
   return tour
*/

int solve_opt_tsp(int dp[], int n, int i, int bm) {
	if(dp[bm*n+i] != -1) return dp[bm*n+i];
	if(bm == 0) return dp[bm*n+i] = adj[i][n-1];
	int best = -1;
	for(int j=0; j<n; j++) {
		if(!(bm & 1<<j)) continue;
		int len = solve_opt_tsp(dp, n, j, bm ^ 1<<j) + adj[i][j];
		if(best == -1 || len < best) {
			best = len;
		}
	}
	return dp[bm*n+i] = best;
}

void recover_opt_tsp(int dp[], int n, int i, int bm, int* res) {
	int id = __builtin_popcount(bm);
	res[id] = i;
	if(bm == 0) return;
	for(int j=0; j<n; j++) {
		if(!(bm & 1<<j)) continue;
		int len = dp[(bm^1<<j)*n+j] + adj[i][j];
		if(len == dp[bm*n+i]) {
			recover_opt_tsp(dp, n, j, bm ^ 1<<j, res);
			return;
		}
	}
}

void solve_opt(int n) {
	int dp[n<<n];
	memset(dp, -1, sizeof dp);
	int length = solve_opt_tsp(dp, n, n-1, (1<<(n-1))-1);

	int tour[n];
	memset(tour, -1, sizeof tour);
	recover_opt_tsp(dp, n, n-1, (1<<(n-1))-1, tour);
	for(int i=0; i<n; i++) {
		cout << tour[i] << nl;
	}
	cerr << "opt length: " << length << nl;
}

