#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld BS = 1e-15;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld solve(int a[], int n) {
	if(n<3) return 0;
	int sum = 0;
	int maxv = 0;
	for(int i=0;i<n;i++) {
		maxv = max(maxv, a[i]);
		sum += a[i];
	}
	if(sum-maxv <= maxv) return 0;
	ld left = (ld)maxv/2;
	ld right = 1e7;
	while(right-left > BS) {
		ld r = (left+right)/2;
		ld ang = 0;
		for(int i=0;i<n;i++) {
			ang += 2*asin((ld)a[i]/2/r);
		}
		if(ang > 2*M_PIl) {
			left = r;
		} else {
			right = r;
		}
	}
	ld r = right;
	ld area = 0;
	ld ang = 0;
	for(int i=0;i<n;i++) {
		ld cur = 2*asin((ld)a[i]/2/r);
		ang += cur;
		area += sin(cur)*r*r/2;
	}
	cerr<<"ang: "<<ang<<" -> "<<area<<nl;
	if(abs(ang-2*M_PIl)<EPS) return area;
	else return 0;
}

ld solve2(int a[], int n) {
	if(n<3) return 0;
	int sum = 0;
	int maxv = 0;
	for(int i=0;i<n;i++) {
		maxv = max(maxv, a[i]);
		sum += a[i];
	}
	if(sum-maxv <= maxv) return 0;
	ld left = (ld)maxv/2;
	ld right = 1e7;
	while(right-left > BS) {
		ld r = (left+right)/2;
		ld ang = 0;
		bool rem = true;
		for(int i=0;i<n;i++) {
			ld cur = 2*asin((ld)a[i]/2/r);
			if(a[i]==maxv && rem) {
				ang += 2*M_PIl - cur;
				rem = false;
			} else {
				ang += cur;
			}
		}
		if(ang < 2*M_PIl) {
			left = r;
		} else {
			right = r;
		}
	}
	ld r = right;
	ld area = 0;
	ld ang = 0;
	bool rem = true;
	for(int i=0;i<n;i++) {
		ld cur = 2*asin((ld)a[i]/2/r);
		if(a[i]==maxv && rem) {
			ang += 2*M_PIl - cur;
			area -= sin(cur)*r*r/2;
			rem = false;
		} else {
			ang += cur;
			area += sin(cur)*r*r/2;
		}
	}
	cerr<<"ang: "<<ang<<" -> "<<area<<" w/ r "<<r<<nl;
	if(abs(ang-2*M_PIl)<EPS) return area;
	else return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	cerr << fixed << setprecision(17);
	cerr<<"2*M_PIl: "<<2*M_PIl<<nl;

	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}
	sort(a,a+n);

	ld ans = 0;
	for(int i=0;i<n;i++) {
		ans = max(ans, solve(a,n-i));
		ans = max(ans, solve2(a,n-i));
	}
	cout<<ans<<nl;

	return 0;
}
