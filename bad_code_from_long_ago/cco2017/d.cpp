#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ll nc2[10001];
void init() {
	for (ll i = 0; i <= 10000; i++) {
		nc2[i] = i*(i-1)/2;
	}
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	init();

	ll k;
	cin >> k;

	int sum = 0;
	vector<int> cycles;
	while (k > 0) {
		auto it = prev(upper_bound(nc2, nc2+10001, k));
		int v = it - nc2;
		cycles.push_back(v);
		k -= *it;
		sum += v;
	}

	cout << sum << " " << sum + cycles.size() - 1 << nl;
	int prev = -1;
	int cur = 1;
	for (int cs : cycles) {
		for (int i = 0; i < cs; i++) 
			cout << cur + i << " " << cur + (i+1)%cs << nl;
		if (prev != -1)
			cout << cur << " " << prev << nl;
		prev = cur;
		cur += cs;
	}

	return 0;
}
