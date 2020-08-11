#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Plan {
	int p, c;
	Plan(int p, int c): p(p), c(c) {}
	bool operator < (const Plan& o) const {
		return c/p < o.c/o.p;
	}
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;

	vector<Plan> o;
	For(i,n) {
		int p, c;
		cin >> p >> c;
		o.push_back(Plan(p,c));
	}
	sort(o.begin(), o.end());

	ll ans = INFLL;
	ll cost = 0;
	ll profit = 0;
	for (const Plan& x : o) {
		cost += x.c;
		profit += x.p;
		ll d = (m+cost+profit-1)/profit;
		ans = min(ans, d);
	}
	cout << ans << nl;

	return 0;
}
