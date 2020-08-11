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

struct Int {
	int x;
	Int(int v): x(v) {}
	Int(char c = 0) {
		switch (c) {
			case '0': x = 0; break;
			case '1': x = 1; break;
			case 'x': x = 2; break;
			case 'X': x = 3; break;
			default: x = -1; break;
		}
	}
	Int operator & (const Int& o) const {
		if (x == 0 || o.x == 0) return Int(0);
		if (x == 1) return o;
		if (o.x == 1) return *this;
		if (x == o.x) return *this;
		else return Int(0);
	}
	Int operator | (const Int& o) const {
		if (x == 1 || o.x == 1) return Int(1);
		if (x == 0) return o;
		if (o.x == 0) return *this;
		if (x == o.x) return *this;
		else return Int(1);
	}
	Int operator ^ (const Int& o) const {
		if (x == 0) return o;
		if (o.x == 0) return *this;
		if (x == 1) return Int(o.x^1);
		if (o.x == 1) return Int(x^1);
		if (x == o.x) return Int(0);
		else return Int(1);
	}
};

const int N = 418;
vector<int> adj[N];
int par[N];
char op[N];
Int val[N];

Int calc(int u) {
	if (adj[u].empty()) {
		assert(val[u].x != -1);
		return val[u];
	} else {
		assert(adj[u].size() == 2);
		Int left = calc(adj[u].front());
		Int right = calc(adj[u].back());
		assert(op[u] != 0);
		if (op[u] == '&') return left & right;
		if (op[u] == '|') return left | right;
		if (op[u] == '^') return left ^ right;
		assert(false);
	}
}

void caseinit() {
	memset(par, 0, sizeof par);
	memset(op, 0, sizeof op);
	memset(val, -1, sizeof val);
	for (int i=0; i<N; i++) {
		adj[i].clear();
	}
}

void solve() {
	caseinit();

	string s;
	cin >> s;

	int id = 1;
	int cur = 1;
	for (char c : s) {
		if (c == '(') {
			adj[cur].push_back(++id);
			par[id] = cur;
			cur = id;
		} else if (c == ')') {
			cur = par[cur];
		} else if (isdigit(c) || isalpha(c)) {
			val[cur] = Int(c);
		} else {
			cur = par[cur];
			op[cur] = c;
			adj[cur].push_back(++id);
			par[id] = cur;
			cur = id;
		}
	}

	if (calc(1).x < 2) {
		cout << 0 << nl;
	} else {
		cout << 1 << nl;
	}

	return;
}

