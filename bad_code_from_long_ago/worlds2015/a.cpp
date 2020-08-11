#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	double p, a, b, c, d;
	cin >> p >> a >> b >> c >> d >> n;
	double pmax, cmax, tv;
	cmax = 0;
	pmax = 0;
	for (int i = 1; i <= n; i++) {
		tv = p*(sin(a*i + b) + cos(c*i + d) + 2);
		if (tv > pmax) {
			pmax = tv;
		}
		else {
			cmax = max(cmax, pmax - tv);
		}
	}
	cout << fixed << setprecision(10) << cmax << endl;
	return 0;
}
