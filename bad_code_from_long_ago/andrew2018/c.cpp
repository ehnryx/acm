#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ ";
	for (const T& it : v) os << it << " ";
	os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

// Find x,y such that ax + by = d = gcd(a,b)
// * a^-1 (mod m): if (egcd(a,m,x,y) == 1) return (x+m)%m; else ERROR;
ll egcd(ll a, ll b, ll& x, ll &y) {
  if (!b) {x = 1; y = 0; return a;}//to ensure d>=0: x=sgn(a);y=0;return abs(a);
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d; }

const ll MOD = 1e6+3;
const ld EPS = 1e-9;

const int N = 2e6+1;
ll fact[N], inv[N];

void init() {
	fact[0] = inv[0] = 1;
	ll x, y;
	for (int i = 1; i <= 2e6; i++) {
		fact[i] = i * fact[i-1] % MOD;
		egcd(fact[i], MOD, x, y);
		inv[i] = (x+MOD) % MOD;
	}
}

inline ll choose(ll n, ll r) {
	return inv[r] * inv[n-r] % MOD * fact[n] % MOD;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	init();

	int T;
	cin >> T;
	while (T--) {
		ll n, m, x, y;
		cin >> n >> m;
		cin >> x >> y;
		ll ans = choose(n+m, n) - choose(n-x + m-y, n-x) * choose(x+y, x) % MOD;
		cout << (ans % MOD + MOD) % MOD << nl;
	}

	return 0;
}
