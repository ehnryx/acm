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

ll damage(const vector<char>& s) {
	ll res = 0;
	ll cur = 1;
	for (char c : s) {
		if (c == 'C') cur *= 2;
		else res += cur;
	}
	return res;
}

void solve() {
	caseinit();

	ll d;
	cin >> d;
	string S;
	cin >> S;
	ll n = S.size();
	vector<char> s;
	for (char c : S) s.push_back(c);

	ll ans = 0;
	ll dmg = damage(s);
	while (dmg > d) {
		ans++;
		bool change = false;
		for (int i = n-2; i >= 0; i--) {
			if (s[i] == 'C' && s[i+1] == 'S') {
				swap(s[i], s[i+1]);
				dmg = damage(s);
				change = true;
				break;
			}
		}
		if (!change) {
			cout << "IMPOSSIBLE" << nl;
			return;
		}
	}
	cout << ans << nl;

	return;
}

