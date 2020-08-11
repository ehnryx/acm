#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;




int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ll l, r, w; cin >> l >> r >> w;
	ll g = __gcd(r, w);
	ll mn = l - w + 1, mx = r - 1;

	ll a = (mn + g - 1) / g * g;
	puts(a <= mx ? "DEADLOCK" : "OK");

	return 0;
}
