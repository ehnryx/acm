#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	pt A, B, C;
	int x, y;

	cin >> x >> y;
	A = pt(x,y);
	cin >> x >> y;
	B = pt(x,y);
	cin >> x >> y;
	C = pt(x,y);

	pt AB = B-A;
	pt BC = C-B;
	pt CA = A-C;

	vector<pt> ab, bc, ca;
	int n, t;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t;
		ab.push_back(A + AB*(t/abs(AB)));
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t;
		bc.push_back(B + BC*(t/abs(BC)));
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t;
		ca.push_back(C + CA*(t/abs(CA)));
	}

	ld ans = 0;
	ans = max(ans, abs(cp(ab[0]-bc[0], ab[0]-ca[0]))/2);
	ans = max(ans, abs(cp(ab[0]-bc.back(), ab[0]-ca[0]))/2);
	ans = max(ans, abs(cp(ab[0]-bc[0], ab[0]-ca.back()))/2);
	ans = max(ans, abs(cp(ab[0]-bc.back(), ab[0]-ca.back()))/2);
	ans = max(ans, abs(cp(ab.back()-bc[0], ab.back()-ca[0]))/2);
	ans = max(ans, abs(cp(ab.back()-bc.back(), ab.back()-ca[0]))/2);
	ans = max(ans, abs(cp(ab.back()-bc[0], ab.back()-ca.back()))/2);
	ans = max(ans, abs(cp(ab.back()-bc.back(), ab.back()-ca.back()))/2);
	ans = max(ans, abs(cp(ab[0]-ab.back(), ab[0]-ca[0]))/2);
	ans = max(ans, abs(cp(ab[0]-ab.back(), ab[0]-ca.back()))/2);
	ans = max(ans, abs(cp(ab[0]-ab.back(), ab[0]-bc[0]))/2);
	ans = max(ans, abs(cp(ab[0]-ab.back(), ab[0]-bc.back()))/2);
	ans = max(ans, abs(cp(bc[0]-bc.back(), bc[0]-ab[0]))/2);
	ans = max(ans, abs(cp(bc[0]-bc.back(), bc[0]-ab.back()))/2);
	ans = max(ans, abs(cp(bc[0]-bc.back(), bc[0]-ca[0]))/2);
	ans = max(ans, abs(cp(bc[0]-bc.back(), bc[0]-ca.back()))/2);
	ans = max(ans, abs(cp(ca[0]-ca.back(), ca[0]-ab[0]))/2);
	ans = max(ans, abs(cp(ca[0]-ca.back(), ca[0]-ab.back()))/2);
	ans = max(ans, abs(cp(ca[0]-ca.back(), ca[0]-bc[0]))/2);
	ans = max(ans, abs(cp(ca[0]-ca.back(), ca[0]-bc.back()))/2);
	cout << ans << nl;

	return 0;
}
