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

	map<char,int> a, b;
	a['a'] = a['o'] = 2;
	a['k'] = a['n'] = a['g'] = a['r'] = 1;
	b['k'] = b['w'] = b['b'] = b['r'] = b['d'] = 1;
	b['i'] = 3;

	string s;
	cin >> s;

	int acnt, bcnt;
	acnt = bcnt = 0;
	for (char c : s) {
		acnt += a[tolower(c)];
		bcnt += b[tolower(c)];
	}

	if (acnt > bcnt) cout << "Kangaroos" << nl;
	else if (acnt < bcnt) cout << "Kiwis" << nl;
	else cout << "Feud continues" << nl;

	return 0;
}
