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

const int N = 3e2 + 7;
const int M = 3e4 + 1;
const int K = 17;
const int T = 4;

int dsu[N];
int find(int i) {
	if(dsu[i] == -1) return i;
	return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
	if(find(i) != find(j)) {
		dsu[find(i)] = find(j);
	}
}

int pre[N][2*N];
int op[N][2*N];
vector<int> ans[M];
vector<pair<int,int>> query[K][K];
vector<int> roots;

int all[K];
int val[N];
int init[N][K];
int trans[N][T][K];

vector<int> recover(int n, int v) {
	vector<int> out(n, -1);
	int m = roots.size();
	for(int i=0; i<m; i++) {
		out[roots[i] - 1] = op[i][v];
		v = pre[i][v];
	}
	for(int i=1; i<=n; i++) {
		out[i-1] = out[find(i)-1];
		assert(out[i-1] != -1);
	}
	return out;
}

void solve(int n, int a, int b) {
	if(a == b) {
		for(auto [c, i] : query[a][b]) {
			if(c != 0) continue;
			ans[i] = vector<int>(n, 0);
		}
		return;
	}

	assert(query[b][a].empty());
	if(query[a][b].empty()) return;
	//cerr<<"DP "<<a<<" "<<b<<nl;

	memset(op, -1, sizeof op);
	int m = roots.size();
	op[m][all[a]-all[b] + N] = 0;
	op[m][all[b]-all[a] + N] = 0;
	//cerr<<"init @ "<<all[a]-all[b]<<nl;
	for(int i=m-1; i>=0; i--) {
		int v = roots[i];
		for(int k=0; k<2*N; k++) {
			for(int j=0; j<T; j++) {
				int da = trans[v][j][a] - init[v][a];
				int db = trans[v][j][b] - init[v][b];
				int diff = da - db;
				if(k-diff < 0 || k-diff >= 2*N || op[i+1][k-diff] == -1) continue;
				//cerr<<"transition: "<<k-diff-N<<" -> "<<k-N<<" by move "<<j<<" @ "<<v<<nl;
				pre[i][k] = k-diff;
				op[i][k] = j;
				break;
			}
		}
	}
	//cerr<<endl;

	for(auto [c, i] : query[a][b]) {
		if(op[0][c+N] != -1) {
			ans[i] = recover(n, c+N);
		}
		if(op[0][-c+N] != -1) {
			if(ans[i].empty()) {
				ans[i] = recover(n, -c+N);
			} else {
				ans[i] = min(ans[i], recover(n, -c+N));
			}
		}
	}
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	memset(dsu, -1, sizeof dsu);

	int n, m, k, q;
	cin >> n >> m >> k >> q;
	for(int i=1; i<=n; i++) {
		cin >> val[i];
	}
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		if(a < b) swap(a, b);
		link(a, b); // b is smaller
	}

	for(int i=1; i<=n; i++) {
		if(i == find(i)) {
			roots.push_back(i);
		}
		init[find(i)][val[i]]++;
	}
	assert(!roots.empty());

	for(int v : roots) {
		for(int i=1; i<=k; i++) {
			all[i] += init[v][i];
		}
		// do nothing
		for(int i=1; i<=k; i++) {
			trans[v][0][i] = init[v][i];
		}
		// + 1
		for(int i=1; i<=k; i++) {
			trans[v][1][i] = init[v][i-1];
		}
		// * 2
		for(int i=1; i<=k; i++) {
			if(i%2 == 1) {
				trans[v][2][i] = 0;
			} else {
				trans[v][2][i] = init[v][i/2];
			}
		}
		// ^ 15
		for(int i=1; i<=k; i++) {
			trans[v][3][i] = init[v][i^15];
		}
	}

	for(int i=0; i<q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if(a < b) swap(a, b); // b is smaller
		query[a][b].push_back(make_pair(c, i));
	}

	for(int i=1; i<=k; i++) {
		for(int j=1; j<=i; j++) {
			solve(n, i, j);
		}
	}

	for(int i=0; i<q; i++) {
		if(ans[i].empty()) {
			cout << "NO" << nl;
		} else {
			cout << "YES" << nl;
			for(int it : ans[i]) {
				cout << it << " ";
			}
			cout << nl;
		}
	}

	return 0;
}

// this is wrong
