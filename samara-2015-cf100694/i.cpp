#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int x, y;
	cin >> x >> y;

	string dir;
	cin >> dir;

	int best = INF;
	string ans;

	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		string s;
		int a, b;
		cin >> s >> a >> b;
		a -= x;
		b -= y;

		int cur;
		if (dir == "LEFT") {
			a += (abs(b)+1)/2;
			if (a<0) cur = (abs(b)+1)/2 + (abs(a)+2)/3;
			else cur = (abs(b)+1)/2 + abs(a);
		} else if (dir == "RIGHT") {
			a -= (abs(b)+1)/2;
			if (a>0) cur = (abs(b)+1)/2 + (abs(a)+2)/3;
			else cur = (abs(b)+1)/2 + abs(a);
		} else if (dir == "UP") {
			b -= (abs(a)+1)/2;
			if (b>0) cur = (abs(a)+1)/2 + (abs(b)+2)/3;
			else cur = (abs(a)+1)/2 + abs(b);
		} else {
			b += (abs(a)+1)/2;
			if (b<0) cur = (abs(a)+1)/2 + (abs(b)+2)/3;
			else cur = (abs(a)+1)/2 + abs(b);
		}

		if (cur < best) {
			best = cur;
			ans = s;
		}
	}

	cout << ans << nl;

	return 0;
}
