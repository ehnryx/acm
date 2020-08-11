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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	ll x, y;
	cin >> x >> y;

	ll a, b, c, d;
	cin >> a >> b >> c >> d;

	function<bool(ll,ll)> inrect = [=] (ll xx, ll yy) {
		return a<=xx && xx<=c && b<=yy && yy<=d;
	};

	ll g = __gcd(x,y);
	if (g == 1) {
		cout << "Yes" << nl;
	} else {
		ll x0 = x/g;
		ll y0 = y/g;
		if (!inrect(x0,y0)) {
			cout << "No" << nl;
			cout << x0 << " " << y0 << nl;
		}
		else if (!inrect(x-x0,y-y0)) {
			// binary search
			ll left = 1;
			ll right = g-1;
			while (left < right) {
				ll mid = (left+right)/2;
				if (inrect(mid*x0, mid*y0)) {
					left = mid+1;
				} else {
					right = mid;
				}
			}
			cout << "No" << nl;
			cout << left*x0 << " " << right*y0 << nl;
		} else {
			cout << "Yes" << nl;
		}
	}

	return 0;
}
