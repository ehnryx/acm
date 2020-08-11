#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(chrono::high_resolution_clock::now().time_since_epoch().count()); }

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
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
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

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 1e6 + 1;

// Find x,y such that ax + by = d = gcd(a,b)
// * a^-1 (mod m): if (egcd(a,m,x,y) == 1) return (x+m)%m; else ERROR;
ll egcd(ll a, ll b, ll& x, ll &y) {
  if (!b) {x = 1; y = 0; return a;}//to ensure d>=0: x=sgn(a);y=0;return abs(a);
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d; }

ll ncr(ll n, ll r, ll m) {
	if (n % 2 == 1) return 0;
	ll first, second;
	first = second = -1;
	int fcount, scount, mcount;
	fcount = scount = mcount = 0;
	ll fact = 1;
	for (int i = 1; i <= n; i++) {
		int j = i;
		for ( ; j % m == 0; j /= m) {
			mcount++;
		}
		fact = fact * j % m;

		if (i == r) {
			first = fact;
			fcount = mcount;
		}
		if (i == n-r) {
			second = fact;
			scount = mcount;
		}
	}

	mcount -= fcount + scount;
	if (mcount > 0) {
		return 0;
	} else {
		ll inv, y;
		egcd(first, m, inv, y);
		inv = (inv + m) % m;
		fact = fact * inv % m;
		egcd(second, m, inv, y);
		inv = (inv + m) % m;
		fact = fact * inv % m;
		return fact;
	}
}

ll dp[N][2];
ll no_consec(int n, int m, bool red = false) {
	memset(dp, -1, 2*(n+1)*sizeof(ll));
	dp[0][0] = dp[0][1] = 1;
	for (int i = 1; i <= n; i++) {
		dp[i][1] = dp[i-1][0];
		dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % m;
	}
	return dp[n][0];
}

ll both(int n, int m) {
	if (n % 2 == 0) {
		return n/2 + 1;
	} else {
		return 0;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	srand();

	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		ll ans = ncr(n, n/2, m) + no_consec(n, m) - both(n, m);
		cout << (ans % m + m) % m << nl;
	}

	return 0;
}
