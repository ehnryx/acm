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
		//cout << "Case #" << cc << ": ";
		solve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

void caseinit() {
}

void solve() {
	caseinit();
	RNG rng(chrono::high_resolution_clock::now().time_since_epoch().count());
	auto dice = bind(uniform_int_distribution<int>(2, 14), rng);

	int $why_does_this_even_exist_WHY_WHYYY_WHYYYYYYYY;
	cin >> $why_does_this_even_exist_WHY_WHYYY_WHYYYYYYYY;

	int grid[16][16]; memset(grid, 0, sizeof grid);
	int res = 0;
	while (res < 225) {
		int a = dice();
		int b = dice();
		bool good = false;
		for (int i = a-1; i <= a+1; i++) {
			for (int j = b-1; j <= b+1; j++) {
				if (grid[i][j] == 0) {
					good = true;
				}
			}
		}
		if (good) {
			cout << a << " " << b << endl;
			cin >> a >> b;
			if (a == 0 && b == 0) return;
			if (grid[a][b] == 0) {
				grid[a][b] = 1;
				res++;
			}
		}
	}

	return;
}

