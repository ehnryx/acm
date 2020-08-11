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
	for (const T& it : v) os << it << " ";
	return os;
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
	cout << fixed << setprecision(1);
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

map<set<pii>,int> seen;

void caseinit() {
	seen.clear();
}

int jam(int red, int blue, set<pii> vis) {
	if (seen.count(vis)) return seen[vis];

	int res = 0;
	for (const pii& it : vis) {
		pii nxt;
		nxt = pii(it.first, it.second+1);
		if (nxt.first <= red && nxt.second <= blue && !vis.count(nxt)) {
			set<pii> pass = vis;
			pass.insert(nxt);
			res = max(res, 1 + jam(red - nxt.first, blue - nxt.second, pass));
		}
		nxt = pii(it.first+1, it.second);
		if (nxt.first <= red && nxt.second <= blue && !vis.count(nxt)) {
			set<pii> pass = vis;
			pass.insert(nxt);
			res = max(res, 1 + jam(red - nxt.first, blue - nxt.second, pass));
		}
	}

	return seen[vis] = res;
}

void solve() {
cerr << nl;

	int n, m;
	cin >> n >> m;
	for (int r = 0; r <= n; r++) {
		for (int b = 0; b <= m; b++) {
	caseinit();
			int red = r;
			int blue = b;

	int ans = 0;
	set<pii> vis;
	if (red > 0) {
		ans++;
		red--;
		vis.insert(pii(1,0));
	}
	if (blue > 0) {
		ans++;
		blue--;
		vis.insert(pii(0,1));
	}
	ans += jam(red,blue,vis);

	cout << (ld)ans << " ";
		}
		cout << nl;
	}

for (int r=0; r<= n; r++) {
	for (int b=0; b<=m; b++) {
		cout << sqrt(r)*sqrt(b) << " ";
	}
	cout << nl;
}

	return;
}

