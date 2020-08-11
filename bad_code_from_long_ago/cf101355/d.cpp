#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 5e5+1;
const int MAXD = 50;

namespace D {
int left[N], right[N];
int depth[N];
//unordered_map<int,int> dp[N][2];
int dp[N][2][MAXD];

int build_depth(int i) {
	if (i == 0) return 0;
	if (depth[i] != -1) return depth[i];
	return depth[i] = 1 + max(build_depth(left[i]), build_depth(right[i]));
}

int solve(int cur, int len, bool black) {
	if (len < 0) 
		return 0;
	if (cur == 0)
		return len == 0;
	if (len > depth[cur]) 
		return 0;
	if (dp[cur][black][len] != -1)
		return dp[cur][black][len];

	int res = 0;

	// black
	ll lans = solve(left[cur], len-1, false);
	ll rans = solve(right[cur], len-1, false);
	res = lans * rans % MOD;

	// red
	if (!black) {
		lans = solve(left[cur], len, true);
		rans = solve(right[cur], len, true);
		res = (res + lans * rans % MOD) % MOD;
	}

	return dp[cur][black][len] = res;
}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	memset(D::dp, -1, sizeof D::dp);
	memset(D::depth, -1, sizeof D::depth);

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> D::left[i] >> D::right[i];
	}

	D::build_depth(1);

	ll ans = 0;
	for (int i = 1; i < MAXD; i++) {
		ans = (ans + D::solve(1, i, true)) % MOD;
	}
	cout << ans << nl;

	return 0;
}
