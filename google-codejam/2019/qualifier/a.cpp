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

const int N = 1e2+1;
int dp[N][2];
pii memo[N][2];

bool inrange(int x) {
	return 0<=x && x!=4 && x<10;
}

bool solve(const string& n, int p, int c) {
	if (dp[p][c] != -1) return dp[p][c];
	if (p == n.size()) return dp[p][c] = (c == 0);

	int val = n[p]-'0' + 10*c;
	// with carry
	for (int i=1; i<=val-1; i++) {
		if (inrange(i) && inrange(val-1-i)) {
			if (solve(n, p+1, 1)) {
				memo[p][c] = pii(i, val-1-i);
				return dp[p][c] = true;
			}
		}
	}
	if (val == 1 && solve(n, p+1, 1)) {
		memo[p][c] = pii(0,0);
		return dp[p][c] = true;
	}
	// no carry
	for (int i=1; i<=val; i++) {
		if (inrange(i) && inrange(val-i)) {
			if (solve(n, p+1, 0)) {
				memo[p][c] = pii(i, val-i);
				return dp[p][c] = true;
			}
		}
	}
	if (val == 0 && solve(n, p+1, 0)) {
		memo[p][c] = pii(0,0);
		return dp[p][c] = true;
	}
	// sad
	return dp[p][c] = false;
}

void caseinit() {
	memset(dp, -1, sizeof dp);
}

void solve() {
	caseinit();

	string n;
	cin >> n;
	assert(solve(n,0,0));
	string a, b;
	for (int p=0,c=0; p != n.size(); p++) {
		int x, y;
		tie(x,y) = memo[p][c];
		if (!a.empty() || x != 0) a.push_back(x+'0');
		if (!b.empty() || y != 0) b.push_back(y+'0');
		int val = n[p]-'0' + 10*c;
		if (x+y == val) {
			c = 0;
		} else {
			c = 1;
		}
	}
	cout << a << " " << b << nl;

	return;
}

