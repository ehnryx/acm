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

namespace std {
	template<> struct hash<pii> {
		size_t operator () (const pii& v) const {
			return v.first<<15^v.second;
		}
	};
}

const int N = 4200;
int val[N];
unordered_map<pii,ld> memo[N];

ld solve(int left, int right, int id, int largebot) {
	if (right-left == 1) return left == id;
	pii range(left,right);
	if (memo[id].count(range)) return memo[id][range];

	int diff = right-left;
	int small = max(largebot/2, diff-largebot);
	if (id < left+small) {
		ld win = solve(left, left+small, id, largebot/2);
		ld res = 0;
		for (int i=left+small; i<right; i++) {
			res += solve(left+small, right, i, largebot/2) * val[id] / (val[id]+val[i]);
		}
		return memo[id][range] = res * win;
	}
	else {
		ld win = solve(left+small, right, id, largebot/2);
		ld res = 0;
		for (int i=left; i<left+small; i++) {
			res += solve(left, left+small, i, largebot/2) * val[id] / (val[id]+val[i]);
		}
		return memo[id][range] = res * win;
	}
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

	int n;
	cin >> n;

	for (int i=0; i<n; i++) {
		cin >> val[i];
	}
	sort(val+1, val+n);

	int largebot = 1 << (31 - __builtin_clz(n-1));
	cout << solve(0, n, 0, largebot) << nl;

	return 0;
}
