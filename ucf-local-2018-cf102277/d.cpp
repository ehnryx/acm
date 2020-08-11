#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

int sqr(int x) {
	return x*x;
}

int d2(int a, int b, int x, int y) {
	return sqr(a-x) + sqr(b-y);
}

int dist(int s, int t, int a, int b, int x, int y) {
	int minv=min(d2(s,t,x,y),d2(s,t,a,b));
	if(a==x) {
		if(min(b,y)<t&&t<max(b,y)) {
			minv=min(minv,sqr(a-s));
		}
	} else { assert(b==y);
		if(min(a,x)<s&&s<max(a,x)) {
			minv=min(minv,sqr(b-t));
		}
	}
	return minv;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int x,y,r;
	cin>>x>>y>>r;
	int a,b,s;
	cin>>a>>b>>s;

	int minv = (a<x&&x<a+s&&b<y&&y<b+s ? 0 : INF);
	minv=min(minv,dist(x,y,a,b,a,b+s));
	minv=min(minv,dist(x,y,a,b+s,a+s,b+s));
	minv=min(minv,dist(x,y,a+s,b+s,a+s,b));
	minv=min(minv,dist(x,y,a+s,b,a,b));
	if(minv==r*r) {
		cout<<1<<nl;
	} else if(minv<r*r) {
		cout<<2<<nl;
	} else {
		cout<<0<<nl;
	}

	return 0;
}
