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

////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y) and x = a^{-1}
// Returns gcd(a,b)
ll egcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	} else {
		ll d = egcd(b, a%b, y, x);
		y -= x * (a/b);
		return d;
	}
}
//*/

////////////////////////////////////////////////////////////////////////
// Int struct for operations on a prime field (TESTED)
// WARNING: slow
struct Int {
	ll x;
	Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
	operator ll() { return x; }
	Int operator + (const Int& n) const { return Int(x + n.x); }
	Int operator - (const Int& n) const { return Int(x - n.x); }
	Int operator * (const Int& n) const { return Int(x * n.x); }
	Int operator / (const Int& n) const { return Int(x * n.inv()); }
	void operator += (const Int& n) { x = (x + n.x) % MOD; }
	void operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; }
	void operator *= (const Int& n) { x = (x * n.x) % MOD; }
	void operator /= (const Int& n) { x = (x * n.inv()) % MOD; }
	ll inv() const {
		if (x == 0) throw runtime_error("divide by zero");
		ll c, d;
		egcd(x, MOD, c, d);
		return (c < 0) ? c+MOD : c;
	}
};
//*/

namespace std {
	template<> struct hash<vector<int>> {
		size_t operator () (const vector<int>& v) const {
			int res = 0;
			for (int i = 0; i < 5; i++) {
				res = 10*res + v[i];
			}
			return res;
		}
	};
}

const int N = 1e4+1;
const int M = 52;
Int dp[N][52];
unordered_map<vector<int>,int> id;
int sz[M];

Int ncr(int n, int r) {
	if (n < r) return 0;
	Int res = 1;
	for (int i = 0; i < r; i++) {
		res *= Int(n-i);
		res /= Int(i+1);
	}
	return res;
}

vector<int> convert(vector<int> v) {
	unordered_map<int,int> m;
	int id = 1;
	for (int i = 0; i < 5; i++) {
		if (!m.count(v[i])) {
			m[v[i]] = id++;
		}
		v[i] = m[v[i]];
	}
	return v;
}

void init() {
	int cnt = 0;
	for (int a=0; a<5; a++) {
		for (int b=0; b<5; b++) {
			if (a == b) continue;
			for (int c=0; c<5; c++) {
				if (b == c) continue;
				for (int d=0; d<5; d++) {
					if (c == d) continue;
					for (int e=0; e<5; e++) {
						if (d == e) continue;
						vector<int> v = convert({a,b,c,d,e});
						if (!id.count(v)) {
							id[v] = cnt;
							set<int> s;
							for (int i : v) {
								s.insert(i);
							}
							sz[cnt++] = s.size();
						}
					}
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T;
	cin >> T;
	while (T--) {
		int n, m, k;
		cin >> n >> m >> k;

		memset(dp, -1, sizeof dp);
		for (int i = 0; i < M; i++) {
			dp[1][i] = ncr(k, sz[i]);
		}

		Int ans = 0;
		for (int i = 0; i < M; i++) {
			if (dp[m][i] > 0) {
				ans += dp[m][i];
			}
		}
		cout << ans << nl;
	}

	return 0;
}
