#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; 
	return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
	return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cout << "Case #" << cc << ": ";
		solve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y), then x = a^{-1}
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

struct Point {
	int x, y;
	Point(){}
	Point(int x, int y): x(x), y(y);
};

void caseinit() {
}

void solve() {
	caseinit();

	int n, s, e;
	cin >> n >> s >> e;

	vector<Point> p;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		p.push_back(Point(x,y));
	}

	Int left, right, mid;
	left = right = mid = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (p[i].y > s && p[j].y > s) {
				if (p[i].y > p[j].y && p[i].x < p[j].x 
						|| p[i].y < p[j].y && p[i].x > p[j].x) {
					left += Int(1);
				}
			}
			else if (p[i].y < s && p[j].y < s) {
				if (p[i].y < p[j].y && p[i].x < p[j].x 
						|| p[i].y > p[j].y && p[i].x > p[j].x) {
					left += Int(1);
				}
			}

			if (p[i].y > e && p[j].y > e) {
				if (p[i].y < p[j].y && p[i].x < p[j].x 
						|| p[i].y > p[j].y && p[i].x > p[j].x) {
					right += Int(1);
				}
			}
			else if (p[i].y < e && p[j].y < e) {
				if (p[i].y > p[j].y && p[i].x < p[j].x 
						|| p[i].y < p[j].y && p[i].x > p[j].x) {
					right += Int(1);
				}
			}
		}
	}

	return;
}

