#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

int main() {
	int x, y, z;

	while (scanf("%d%d%d", &x, &y, &z) != EOF) {
		int num = x * y;
		int den = z - y;
		int g = __gcd(num, den);
		printf("%d/%d\n", num / g, den / g);
	}

	return 0;
}
