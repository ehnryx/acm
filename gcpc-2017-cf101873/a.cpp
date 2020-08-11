#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

bool cmp(const pt& a, const pt& b) {
	if (a.imag() == b.imag()) return a.real() < b.real();
	return a.imag() < b.imag();
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;

	int a, b, c;
	map<int,vector<int>> p[3];
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c;
		p[c-1][b].push_back(a);
	}

	vector<pt> ans;

	// left side
	ans = { pt(-2000,2000), pt(-2001,2000), pt(-2001,-2000), pt(-2000,-2000) };

	for (pair<const int,vector<int>>& it : p[0]) {
		int y = it.first;
		vector<int>& row = it.second;
		sort(row.begin(), row.end());

		ans.push_back(pt(-2000, y+0.2));
		for (int x : row) {
			ans.push_back(pt(x-0.1, y+0.2));
			ans.push_back(pt(x-0.1, y-0.1));
			ans.push_back(pt(x+0.1, y-0.1));
			ans.push_back(pt(x+0.1, y+0.2));
		}
		ans.push_back(pt(-2000, y+0.3));
	}

	cout << ans.size() << nl;
	for (const pt& it : ans) {
		cout << it.real() << " " << it.imag() << nl;
	}

	// right side
	ans = { pt(2000,-2000), pt(2001,-2000), pt(2001,2000), pt(2000,2000) };

	for (auto it = p[1].rbegin(); it != p[1].rend(); it++) {
		int y = it->first;
		vector<int>& row = it->second;
		sort(row.begin(), row.end(), greater<int>());

		ans.push_back(pt(2000, y-0.2));
		for (int x : row) {
			ans.push_back(pt(x+0.1, y-0.2));
			ans.push_back(pt(x+0.1, y+0.1));
			ans.push_back(pt(x-0.1, y+0.1));
			ans.push_back(pt(x-0.1, y-0.2));
		}
		ans.push_back(pt(2000, y-0.3));
	}

	cout << ans.size() << nl;
	for (const pt& it : ans) {
		cout << it.real() << " " << it.imag() << nl;
	}

	return 0;
}
