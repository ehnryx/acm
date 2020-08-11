#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 5e4+1;
ld x[N],y[N];

ld calc(int n, ld v) {
	ld ans = 0;
	for(int i=0;i<n;i++) {
		ans = max(ans, (x[i]-v)*(x[i]-v)+y[i]*y[i]);
	}
	return sqrt(ans);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n; cin>>n && n; ) {
		for(int i=0;i<n;i++) {
			cin>>x[i]>>y[i];
		}
		ld l = -2e5;
		ld r = 2e5;
		while(r-l>EPS) {
			ld lm = (2*l+r)/3;
			ld rm = (l+2*r)/3;
			if(calc(n,lm) < calc(n,rm)) {
				r = rm;
			} else {
				l = lm;
			}
		}
		cout<<l<<" "<<calc(n,l)<<nl;
	}

	return 0;
}
