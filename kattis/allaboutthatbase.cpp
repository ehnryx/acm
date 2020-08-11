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

ll solve(const string& s, int b) {
	if (b == 1) return s.size();
	ll cur = 0;
	for (char c : s) {
		if (isdigit(c)) cur = cur*b + c-'0';
		else cur = cur*b + c-'a'+10;
	}
	return cur;
}
ld solve(const string& s, const string& op, const string& t, int b) {
	ll x = solve(s, b);
	ll y = solve(t, b);
	if (op == "+") return x+y;
	if (op == "-") return x-y;
	if (op == "*") return x*y;
	if (op == "/") return (ld)x/y;
	assert(false);
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int T;
	cin >> T;
	while (T--) {
		string x, op, y, _, z;
		cin >> x >> op >> y >> _ >> z;
		int minbase = 2;
		bool ones = true;
		for (char c : x+y+z) {
			if (c != '1') ones = false;
			if (isdigit(c)) minbase = max(minbase, c-'0'+1);
			else minbase = max(minbase, c-'a'+11);
		}
		string ans;
		if (ones && abs(solve(x,op,y,1) - solve(z,1)) < EPS) {
			ans.push_back('1');
		}
		for (int i=minbase; i<=36; i++) {
			if (abs(solve(x,op,y,i) - solve(z,i)) < EPS) {
				ans.push_back(i==36?'0':i<10?i+'0':i-10+'a');
			}
		}
		if (ans.empty()) {
			cout << "invalid" << nl;
		} else {
			cout << ans << nl;
		}
	}

	return 0;
}
