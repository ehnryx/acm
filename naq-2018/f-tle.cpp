#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef __int128 lll;
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

const int N = 26;
const lll MASK = 31;

ll lcm[N][N];
ll ncr[N][N];
bool adj[N][N];
int val[N], cnt[N];
int children[N];

int value(const lll& ha, int i) {
	return ha >> (5*i) & 31;
}
void vset(lll& ha, int i, int v) {
	ha &= ~(MASK << (5*i));
	ha |= ((lll)v) << (5*i);
}

int n;
ll solve(int, lll);
ll solve_node(int, int, int, const lll&, int, lll, lll, int, int);

ostream& operator << (ostream& os, const lll& v) {
	os << nl;
	for (int i=0; i<n; i++) {
		os << i << " (" << val[i] << ") : " << value(v,i) << nl;
	}
	return os;
}

ll solve_node(int root, int left, int right, const lll& goal, int cur, lll lv, lll rv, int lp, int rp) {
	if (cur == root+1) {
		if (lp % 2 == 1) return 0;
		if (lv == 0 && rv == 0) return 1;
		else if (lv == 0) return solve(right, rv);
		else if (rv == 0) return solve(left, lv);
		ll ans = solve(left, lv);
		if (ans == 0) return 0;
		else return ans * solve(right, rv) % MOD;
	}

	int v = value(goal, cur);
	if (v == 0) return solve_node(root, left, right, goal, cur+1, lv, rv, lp, rp);

	// right only
	//if (!(children[left] & 1<<cur)) {
	if (!adj[left][cur]) {
		return solve_node(root, left, right, goal, cur+1, lv, rv | ((lll)v)<<(5*cur+1), lp, rp+v);
	}

	// left only
	//if (!(children[right] & 1<<cur)) {
	if (!adj[right][cur]) {
		return solve_node(root, left, right, goal, cur+1, lv | ((lll)v)<<(5*cur), rv, lp+v, rp);
	}

	// both
	ll res = 0;
	for (int i=0; i<=v; i++) {
		res += ncr[v][i] * solve_node(root, left, right, goal, cur+1, lv | ((lll)i)<<(5*cur), rv | ((lll)(v-i))<<(5*cur), lp+i, rp+v-i) % MOD;
	}
	return res % MOD;
}

int hashlll(const lll& v) {
	//return v ^ v>>13 ^ v>>24 ^ v>>47 ^ v>>58 ^ v>>74 ^ v>>89 ^ v>>103;
	return v ^ v>>27 ^ v>>53 ^ v>>81 ^ v>>109;
}

int arr[N];
unordered_map<int,ll> memo[N];
unordered_map<int,ll> memo_mat;
unordered_map<int,ll> memo_node[N][N];
ll solve(int root, lll ha) {
	//ll key = ha % MOD;
	int key = hashlll(ha);
	if (memo[root].count(key)) return memo[root][key];

	int bm = 0;
	int len = 0;
	for (int i=0; i<root; i++) {
		int v = value(ha, i);
		if (v) {
			bm |= 1<<i;
			arr[len++] = v<<5 | i;
		}
	}
	{
		int v = value(ha, root);
		if (v) {
			bm |= 1<<root;
		}
		arr[len++] = (v+1)<<5 | root;
	}

	// check matrix
	int mat = 0;
	for (int i=0; i<len; i++) {
		for (int j=0; j<len; j++) {
			mat *= 629;
			if (adj[arr[i]&31][arr[j]&31]) {
				mat += (arr[i]>>5) * (arr[j]>>5);
			}
		}
	}
	if (memo_mat.count(mat)) {
		return memo[root][key] = memo_mat[mat];
	}

	// calculate answer for the first time

	ll res = 0;

	for (int i=0; i<n; i++) {
		for (int j=0; j<=i; j++) {
			if ((bm & (children[i]|children[j])) == bm && lcm[i][j] == root) {
				if (i == j) {
					int base = value(ha, i);
					if (base < 2) continue;
					lll cur = ha;
					vset(cur, i, base-2);
					int curkey = hashlll(cur);
					ll ans = solve_node(root, i, j, cur, 0, 0, 0, 0, 0);
					//if (memo_node[i][j].count(curkey)) ans = memo_node[i][j][curkey];
					//else ans = memo_node[i][j][curkey] = solve_node(root, i, j, cur, 0, 0, 0, 0, 0);
					res += base*(base-1)/2 * ans;
				}
				else {
					int ibase = value(ha, i);
					int jbase = value(ha, j);
					if (ibase < 1 || jbase < 1) continue;
					lll cur = ha;
					vset(cur, i, ibase-1);
					vset(cur, j, jbase-1);
					int curkey = hashlll(cur);
					ll ans = solve_node(root, i, j, cur, 0, 0, 0, 0, 0);
					//if (memo_node[i][j].count(curkey)) ans = memo_node[i][j][curkey];
					//else ans = memo_node[i][j][curkey] = solve_node(root, i, j, cur, 0, 0, 0, 0, 0);
					res += ibase*jbase * ans;
				}
			}
		}
	}

	res %= MOD;
	memo_mat[mat] = res;
	return memo[root][key] = res;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	for (int i=0; i<N; i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for (int j=1; j<i; j++) {
			ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % MOD;
		}
	}

	cin >> n;

	int a;
	map<int,int> in;
	for (int i=0; i<n; i++) {
		cin >> a;
		in[a]++;
	}

	n = 0;
	for (const pii& it : in) {
		val[n] = it.first;
		cnt[n] = it.second;
		n++;
	}
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (val[i] % val[j] == 0) {
				children[i] |= 1<<j;
				adj[i][j] = true;
			}
			ll lcmval = (ll)val[i]*val[j] / __gcd(val[i],val[j]);
			lcm[i][j] = -1;
			for (int k=0; k<n; k++) {
				if (lcmval == val[k]) {
					lcm[i][j] = k;
				}
			}
		}
	}

	lll ha = 0;
	for (int i=0; i<n; i++) {
		ha |= ((lll)cnt[i])<<(5*i);
	}

	ll ans = 0;
	for (int i=0; i<n; i++) {
		if (__builtin_popcount(children[i]) == n) {
			lll cur = ha;
			int base = value(cur, i);
			vset(cur, i, base-1);
			ans += base * solve(i, cur);
		}
	}
	cout << ans % MOD << nl;

	return 0;
}
