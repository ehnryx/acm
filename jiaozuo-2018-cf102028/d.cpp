#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const ll INF = 0x3f3f3f3f;
const ld PI = acos(-1.L);



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(12);

	int T;
	cin >> T;

	while (T--) {
		int a, b, r, d;
		cin >> a >> b >> r >> d;
		ld ang = PI*d/180;
		pt dir = exp(pt(0,ang));
		pt x = (ld)(a+r)*dir + (ld)(b)*dir*pt(0,-1);
		if (x.imag() < 0) {
			cout << x.real()-r << nl;
		} else {
			cout << abs(x)-r << nl;
		}
	}

	return 0;
}
