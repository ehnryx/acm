#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
	for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) { os << it << " "; }
	return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
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

const int N = 1e3 + 1;
char ans[N];

struct Segment {
	int l, r, i;
	bool operator < (const Segment& o) const {
		return l < o.l;
	}
};

void caseinit() {
}

void solve() {
	caseinit();

	int n;
	cin >> n;
	vector<Segment> segs;
	for(int i=0; i<n; i++) {
		int a, b;
		cin >> a >> b;
		segs.push_back(Segment{a, b, i});
	}
	sort(segs.begin(), segs.end());

	int lc = 0;
	int lj = 0;
	for(const auto& s : segs) {
		if(lc <= s.l) {
			lc = s.r;
			ans[s.i] = 'C';
		} else if(lj <= s.l) {
			lj = s.r;
			ans[s.i] = 'J';
		} else {
			cout << "IMPOSSIBLE" << nl;
			return;
		}
	}
	for(int i=0; i<n; i++) {
		cout << ans[i];
	}
	cout << nl;

	return;
}

