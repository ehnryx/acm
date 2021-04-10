#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

bool solve(vector<int> v, int res) {
	sort(v.begin(), v.end());
	return v[1]+v[2]+v[3] <= 3*res;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	ld a;
	vector<int> v;
	for(int i=0; i<4; i++) {
		cin >> a;
		v.push_back(round(a*100));
	}
	cin >> a;
	int res = round(a*100);

	int ans = 0;
	for(int i=1; i<=2001; i++) {
		v.push_back(i);
		if(solve(v, res)) {
			ans = i;
		}
		v.pop_back();
	}
	if(ans == 0) {
		cout << "impossible" << nl;
	} else if(ans > 2000) {
		cout << "infinite" << nl;
	} else {
		cout << fixed << setprecision(2) << (ld)ans/100 << nl;
	}

	return 0;
}
