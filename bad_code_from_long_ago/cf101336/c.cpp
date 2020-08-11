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

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Item {
	ll a, b, x, d;
	Item() {}
	Item(ll a, ll b, ll x): a(a), b(b), x(x) { d = a-b; }
	bool operator < (const Item& other) const {
		if (d == 0 && x == 0) return false;
		else if (other.d == 0 && other.x == 0) return true;
		else return d * other.x < other.d * x;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;

		ll a, b, x;
		vector<Item> items;
		for (int i = 0; i < n; i++) {
			cin >> a >> b >> x;
			items.push_back(Item(a, b, x));
		}
		sort(items.begin(), items.end());

		ld ans = 0;
		ld curp = 0;
		for (const Item& it : items) {
			ans += curp * it.b + (1-curp) * it.a;
			curp += (ld) it.x / 1e7;
		}
		cout << ans << nl;
	}

	return 0;
}
