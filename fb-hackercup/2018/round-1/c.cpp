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

const int N = 2e5+1;

int height[N];
int lv[N], rv[N];
ld dist[N];

void caseinit() {
	memset(lv, INF, sizeof lv);
	memset(rv, INF, sizeof rv);
}

void solve() {
	caseinit();

	int n, m;
	cin >> n >> m;

	ll w, x, y, z;
	cin >> height[1] >> height[2] >> w >> x >> y >> z;
	for (int i = 3; i <= n; i++) {
		height[i] = (w*height[i-2] + x*height[i-1] + y) % z;
	}

	while (m--) {
		int a, b, u, d;
		cin >> a >> b >> u >> d;
		for (int i = a; i < b; i++) {
			rv[i] = min(rv[i], u);
			lv[i+1] = min(lv[i+1], d);
		}
		for (int i = b; i < a; i++) {
			rv[i] = min(rv[i], d);
			lv[i+1] = min(lv[i+1], u);
		}
	}

	auto valid = [&] (const ld& t) {
		fill(dist, dist+N, INFLL);

		for (int i = 1; i <= n; i++) {
			dist[i] = t + height[i];
		}
		for (int i = 1; i < n; i++) {
			dist[i+1] = min(dist[i+1], dist[i] + rv[i]);
		}
		for (int i = n; i > 1; i--) {
			dist[i-1] = min(dist[i-1], dist[i] + lv[i]);
		}

		ld res = INFLL;
		for (int i = 1; i <= n; i++) {
			res = min(res, dist[i] + t - height[i]);
		}
		return res >= 0;
	};

	ld left, right, mid;
	left = 0;
	right = z;
	while (right - left > EPS) {
		mid = (left+right)/2;
		if (valid(mid)) right = mid;
		else left = mid;
	}

	assert(mid < z-0.1);
	cout << mid << nl;

	return;
}

