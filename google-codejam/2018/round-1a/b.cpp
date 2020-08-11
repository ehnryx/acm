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

void caseinit() {
}

const int N = 1000 + 1;
int robots, bits, cashiers;
pair<ll,ll> line[N]; // (slope, intercept)
ll maxv[N];

bool valid(ll t) {
	vector<ll> res;
	for (int i = 0; i < cashiers; i++) {
		res.push_back(min(maxv[i], (t - line[i].second) / line[i].first));
	}
	sort(res.begin(), res.end(), greater<ll>());

	ll ans = 0;
	for (int i = 0; i < robots; i++) {
		ans += res[i];
		if (ans >= bits) return true;
	}
	return false;
}

void solve() {
	caseinit();

	cin >> robots >> bits >> cashiers;
	for (int i = 0; i < cashiers; i++) {
		cin >> maxv[i] >> line[i].first >> line[i].second;
	}

	ll left, right, mid;
	left = 0;
	right = INFLL;
	while (left <= right) {
		mid = (left + right) / 2;
		if (!valid(mid)) {
			left = mid+1;
		} else {
			right = mid-1;
		}
	}
	if (!valid(mid)) {
		mid++;
	}
	cout << mid << nl;

	return;
}

