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
ostream& operator << (ostream& os, const unordered_set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; 
	return os << '}';
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

const int N = 101;
string grid[N];

void solve() {
	caseinit();

	int n, m, h, v;
	cin >> n >> m >> h >> v;

	int total = 0;
	for (int i = 0; i < n; i++) {
		cin >> grid[i];
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '@') total++;
		}
	}
	if (total == 0) {
		cout << "POSSIBLE" << nl;
		return;
	}

	if (total % ((h+1) * (v+1)) != 0) {
		cout << "IMPOSSIBLE" << nl;
		return;
	}

	map<int,int> rows;
	int sum, hpart, cpart;
	hpart = total / (h+1);
	cpart = total / (h+1) / (v+1);

	sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '@') sum++;
		}
		if (sum > 0 && sum % hpart == 0) {
			rows[sum] = i+1;
		}
	}
	if (rows.size() != h+1) {
		cout << "IMPOSSIBLE" << nl;
		return;
	}

	unordered_set<int> cuts[101];
	for (int j = 1; j <= v+1; j++) {
		for (int i = 1; i <= m; i++) {
			cuts[j].insert(i);
		}
	}

	int pre = 0;
	for (const pii& r : rows) {
		unordered_set<int> cur[101];
		sum = 0;
		for (int j = 0; j < m; j++) {
			for (int i = pre; i < r.second; i++) {
				if (grid[i][j] == '@') sum++;
			}
			if (sum > 0 && sum % cpart == 0) {
				cur[sum / cpart].insert(j+1);
			}
		}
		for (int j = 1; j <= v+1; j++) {
			for (auto it = cuts[j].begin(); it != cuts[j].end(); ) {
				if (cur[j].count(*it)) ++it;
				else it = cuts[j].erase(it);
			}
		}
		pre = r.second;
	}

	for (int i = 1; i <= v+1; i++) {
		if (cuts[i].empty()) {
			cout << "IMPOSSIBLE" << nl;
			return;
		}
	}

	cout << "POSSIBLE" << nl;

	return;
}

