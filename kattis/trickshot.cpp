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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int w,l;
	cin>>w>>l;
	int r,x[4],y[4],h;
	cin>>r;
	for(int i=1;i<=3;i++) cin>>x[i]>>y[i];
	cin>>h;

	pt s[4];
	for(int i=1;i<=3;i++) {
		s[i] = pt(x[i],y[i]);
	}

	pt d[4];
	d[3] = pt(w,l);
	d[2] = pt(0,l);
	pt dir3 = (d[3]-s[3])/abs(d[3]-s[3]);
	d[1] = s[3] - (ld)2*r*dir3;
	if(eq(d[1],s[1])) {
		// TODO
	} else {
		pt dir1 = (d[1]-s[1])/abs(d[1]-s[1]);
		d[0] = s[1] - (ld)2*r*dir1;
		pt dir2 = (d[2]-s[2])/abs(d[2]-s[2]);
		s[0] = s[2] - (ld)2*r*dir2;
		if(eq(d[0],s[0])) {
			// TODO
		} else {
		}
	}

	return 0;
}
