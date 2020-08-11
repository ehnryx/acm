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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(3);

	int K, P, X;
	cin >> K >> P >> X;
	int M = sqrt(K*P/X);
	cout << min(M*X + (ld)K*P/M, (M+1)*X + (ld)K*P/(M+1)) << nl;

	return 0;
}
