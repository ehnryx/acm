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

void solve() {
	caseinit();

	int n;
	cin >> n;
	string s;
	cin >> s;

	set<int> h, v;
	for (int i=0; i<n; i++) {
	    h.insert(i);
			v.insert(i);
	}

	int x, y;
	x = y = 0;
	for (char c : s) {
		if (c == 'E') {
			h.erase(x);
			y++;
		} else {
			v.erase(y);
			x++;
		}
	}

	string ans;
	if (s[0] == 'E') {
		int l = 0;
		for (int i=0; i!=*h.rbegin(); l=++i) {
			ans.push_back('S');
		}
		for (int i=0; i<n-1; i++) {
			ans.push_back('E');
		}
		for (int i=l; i<n-1; i++) {
			ans.push_back('S');
		}
	} else {
		int l = 0;
		for (int i=0; i!=*v.rbegin(); l=++i) {
			ans.push_back('E');
		}
		for (int i=0; i<n-1; i++) {
			ans.push_back('S');
		}
		for (int i=l; i<n-1; i++) {
			ans.push_back('E');
		}
	}
	cout << ans << nl;

	return;
}


