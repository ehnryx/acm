#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;

ll inv(ll n) {
	ll res = 1;
	for (int e=MOD-2; e>0; e/=2) {
		if (e&1) res = res*n%MOD;
		n = n*n%MOD;
	}
	return res;
}

struct F {
	ll n, d;
	F() { n=d=INF; }
	//F(ll a, ll b) { n = a%MOD; d = b%MOD; if (d==0) { n=0; d=1; } }
	F(ll a, ll b) { ll g = __gcd(a,b); n = a/g; d = b/g; if (d<0) { n=-n; d=-d; } if (d==0) { n=0; d=1; } }
	bool done() const { return n!=INF; }
	F operator + (const F& f) const { return F(n*f.d + d*f.n, d*f.d); }
	F operator - (const F& f) const { return F(n*f.d - d*f.n, d*f.d); }
	F operator * (const F& f) const { return F(n*f.n, d*f.d); }
	ll get() const { return (n*inv(d)%MOD + MOD) % MOD; }
};
ostream& operator << (ostream& os, const F& v) {
	return os << v.n << '/' << v.d;
}

const int N = 9;
vector<int> adj[N];
int val[N];

F zero = F(0,1);

F dp[1<<(2*N)][N];
F solve(int bm, int u) {
	if (dp[bm][u].done()) return dp[bm][u];
	int tot = 0;
	for (int x : adj[u]) {
		int vis = (bm>>(2*(x-1)) & 3);
		if (vis < 2) tot++;
	}
	if (!tot) return dp[bm][u] = F(val[u],1);
	F res = zero;
	for (int x : adj[u]) {
		int vis = (bm>>(2*(x-1)) & 3);
		if (vis < 2) {
			int nxt = (bm ^ vis<<(2*(x-1))) | (vis+1)<<(2*(x-1));
			res = res + F(1,tot) * solve(nxt, x);
		}
	}
	return dp[bm][u] = res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case " << tt << ": ";
		for (int i=0; i<1<<2*N; i++) for (int j=0; j<N; j++) {
			dp[i][j] = F();
		}
		int n;
		cin >> n;
		for (int i=1; i<=n; i++) {
			cin >> val[i];
			adj[i].clear();
		}
		for (int i=1; i<n; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		int s;
		cin >> s;
		F ans = solve(1<<(2*(s-1)),s);
		cerr << ans << nl;
		cout << ans.get() << nl;
	}

	return 0;
}
