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

vector<int> join(int a, int b) {
	vector<int> res = {a,b};
	if (__builtin_clz(a) > __builtin_clz(b)) swap(a,b);
	while (__builtin_clz(a) != __builtin_clz(b)) {
		res.push_back(a^1);
		a >>= 1;
	}
	if (a == b) {
		return {-1};
	}

	while ((a^1) != b) {
		res.push_back(a^1);
		res.push_back(b^1);
		a >>= 1;
		b >>= 1;
	}

	a >>= 1;
	while (a > 1) {
		res.push_back(a^1);
		a >>= 1;
	}

	sort(res.begin(), res.end());
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int a, b;
	cin >> a >> b;

	for (int it : join(a,b)) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
