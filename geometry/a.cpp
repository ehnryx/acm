#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long double ld;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	// output exactly 12 digits after the decimal point
	cout << fixed << setprecision(12);

	int R, x, y;
	cin >> R >> x >> y;

	// get distance from point to the straight edge (ie. the line y = 0)
	ld distToEdge = y;

	// get distance from point to the circular arc
	ld distToCircle = R - hypot(x, y);

	cout << min(distToEdge, distToCircle) << nl;

	return 0;
}
