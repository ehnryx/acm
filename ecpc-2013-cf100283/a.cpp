#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "zeriba"

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
const ld PI = acos((ld)-1);
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3;
int len[N];

bool valid(ld r, int n) {
	ld ang = 0;
	for (int i=0; i<n-1; i++) {
		ang += 2 * asin((ld)len[i]/2 / r);
	}
	if (ang > 2*PI) return false;
	else return r*2*abs(sin(PI-ang/2)) > len[n-1];
}

bool obtuse(ld r, int n) {
	ld ang = 0;
	for (int i=0; i<n-1; i++) {
		ang += 2 * asin((ld)len[i]/2 / r);
	}
	return sin(2*PI-ang) < 0;
}

void solve() {
	int n;
	cin >> n;

	int maxv = 0;
	int sum = 0;
	for (int i=0; i<n; i++) {
		cin >> len[i];
		sum += len[i];
		maxv = max(maxv, len[i]);
	}
	if (maxv >= sum-maxv) {
		cout << "can't form a convex polygon" << nl;
		return;
	}

	sort(len, len+n);

	const int BS = 100;
	ld left = maxv/2;
	ld right = sum;
	for (int bs=0; bs<BS; bs++) {
		ld mid = (left+right)/2;
		(valid(mid,n) ? right : left) = mid;
	}
	if (obtuse(left,n)) cout << llround((ld)1e4*maxv/2)/(ld)1e4 << nl;
	else cout << llround((ld)1e4*left)/(ld)1e4 << nl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(4);
#ifdef ONLINE_JUDGE
	freopen(TESTFILE ".in", "r", stdin);
#endif

	int T;
	cin >> T;

	for (int tt=1; tt<=T; tt++) {
		cout << "Case " << tt << ": ";
		solve();
	}

	return 0;
}
