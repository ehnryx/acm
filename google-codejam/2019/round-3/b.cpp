#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

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

const int N = 1e6+1;
int a[N];

void caseinit() {
}

void solve() {
	caseinit();

	int n;
	cin >> n;

	set<int> big;
	vector<pii> order;
	FOR(i,1,n) {
		cin >> a[i];
		big.insert(i);
		order.push_back(pii(a[i],i));
	}
	sort(order.begin(), order.end());

	ll ans = 0;
	for (const pii& it : order) {
		int i = it.second;
		big.erase(i);
		auto jt = big.upper_bound(i);
		if (jt == big.begin() || jt == big.end()) {
			continue;
		} else {
			int l = *prev(jt);
			int r = *jt;
			int h = min(a[l],a[r]) - a[i];
			ans += (ll)(r-l-1)*h % MOD * ((ll)l*(n-r+1) % MOD) % MOD;
		}
	}
	cout << ans % MOD << nl;

	return;
}

