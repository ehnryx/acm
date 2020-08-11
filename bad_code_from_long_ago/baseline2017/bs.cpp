#include <bits/stdc++.h>
using namespace std;

double a, b, c, d, m, t;

double bs(double left, double right) {
	if (right - left < 1e-6)
		return left;
	double mid = (left + right) / 2;
	if (a*mid*mid*mid + b*mid*mid + c*mid + d > t/m)
		return bs(left, mid);
	else 
		return bs(mid, right);
}

int main() {
	ios::sync_with_stdio(0);

	while (cin >> a >> b >> c >> d >> m >> t) {
		double ans = bs(0, t/(c*m));
		cout << fixed << setprecision(2) << ((int)(ans * 100)) / 100.0 << '\n';
	}

	return 0;
}
