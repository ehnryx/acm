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
// To find a^{-1} mod m, use egcd(a,m,x,y), then x = a^{-1}
// Returns gcd(a,b)
//*!
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
//*!
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

struct Edge {
	int id;
	ld dist;
	int num;
	Int val;
	Edge(){}
	Edge(int i, ld d, int n, Int v): id(i), dist(d), num(n), val(v) {}
	bool operator < (const Edge& o) const {
		if (abs(dist-o.dist) < EPS) return num > o.num;
		else return dist < o.dist;
	}
};

const int N = 5e4+1;
vector<Edge> adj[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m, a, b, c;
	cin >> n >> m;

	for (int i=0; i<m; i++) {
		cin >> a >> b >> c;
		adj[a].push_back(Edge(b,(ld)c/100,1,c));
	}

	bitset<N> vis;
	priority_queue<Edge> dk;
	dk.push(Edge(1,1,1,1));
	while (!dk.empty()) {
		Edge cur = dk.top();
		dk.pop();
		if (cur.id == n) {
			assert(cur.val != 1);
			cout << cur.val << nl;
			break;
		}
		if (!vis[cur.id]) {
			vis[cur.id] = true;
			for (const Edge& e : adj[cur.id]) {
				dk.push(Edge(e.id, cur.dist*e.dist, cur.num+e.num, cur.val*e.val));
			}
		}
	}

	return 0;
}
