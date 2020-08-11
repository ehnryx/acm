#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const int N = 1e4+10;

int n;
vector<pair<int, int>> a, ap;
inline ld sq(ld x) { return x*x; }
ld calc(const vector<pair<int, int>>& vs) {
	ld ans = 0, v = 0;
	for (const auto& p : vs) {
		ans += v * p.second + (ld) p.first * sq(p.second) / 2;
		v += (ld) p.second * p.first;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n; a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
	}
	ap = a;
	sort(ap.rbegin(), ap.rend());
	cout << fixed << setprecision(1) << calc(ap) - calc(a) << nl;

	return 0;
}
