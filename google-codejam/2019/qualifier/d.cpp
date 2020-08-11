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
		//cout << "Case #" << cc << ": ";
		solve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

void check(const string& s) {
	if (s == "-1") {
		exit(0);
	}
}

vector<int> start(int n) {
	int v = 0;
	for (int i=0; i<n; i+=16) {
		for (int j=0; j<16 && i+j<n; j++) {
			cout << v;
		}
		v ^= 1;
	}
	cout << endl;

	string s;
	cin >> s;
	check(s);
	int pre = -1;
	int cur = 0;
	vector<int> out;
	for (char c : s) {
		if (c != pre) {
			if (cur > 0) out.push_back(cur);
			cur = 0;
		}
		cur++;
		pre = c;
	}
	if (cur > 0) out.push_back(cur);
	return out;
}

vector<int> query(int n, int b, const vector<int>& g) {
	int v = 0;
	for (int i=0; i<n; i+=b) {
		for (int j=0; j<b && i+j<n; j++) {
			cout << v;
		}
		v ^= 1;
	}
	cout << endl;

	string s;
	cin >> s;
	check(s);
	vector<int> out;
	int idx = 0;
	for (int len : g) {
		int zero = 0;
		int one = 0;
		for (int j=0; j<len; j++) {
			if (s[idx++] == '0') zero++;
			else one++;
		}
		out.push_back(zero);
		out.push_back(one);
	}
	return out;
}

void caseinit() {
}

void solve() {
	caseinit();

	int n, b, f;
	cin >> n >> b >> f;

	vector<int> good = start(n);
	for (int i=8; i>0; i/=2) {
		good = query(n, i, good);
	}

	for (int i=0; i<n; i++) {
		if (!good[i]) {
			cout << i << " ";
		}
	}
	cout << endl;

	return;
}

