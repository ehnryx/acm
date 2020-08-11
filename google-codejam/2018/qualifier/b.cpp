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

void solve() {
	caseinit();

	int n;
	cin >> n;

	vector<int> odd, even;
	int a;
	for (int i = 0; i < n; i++) {
		cin >> a;
		(i % 2 ? odd : even).push_back(a);
	}
	sort(odd.begin(), odd.end());
	sort(even.begin(), even.end());

	vector<int> arr;
	for (int i = 0; i < n; i++) {
		if (i < even.size()) arr.push_back(even[i]);
		if (i < odd.size()) arr.push_back(odd[i]);
	}

	for (int i = 1; i < n; i++) {
		if (arr[i] < arr[i-1]) {
			cout << i-1 << nl;
			return;
		}
	}
	cout << "OK" << nl;

	return;
}

