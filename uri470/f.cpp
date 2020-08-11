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

struct Segment {
	int x,a,b,t;
	bool operator < (const Segment& o) const {
		return x<o.x;
	}
};

const int N = 1<<17;
ll cov[2*2*N], tag[2*N];

void insert(int l, int r, int v, int i=1, int s=0, int e=N-1) {
	if(r<s||e<l) return;
	if(l<=s&&e<=r) {
		tag[i] += v;
	} else {
		int m = (s+e)/2;
		insert(l,r,v,2*i,s,m);
		insert(l,r,v,2*i+1,m+1,e);
	}
	if(tag[i]) {
		cov[i] = e-s+1;
	} else {
		cov[i] = cov[2*i] + cov[2*i+1];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	int a[n],b[n],c[n],d[n];
	for(int i=0;i<n;i++) {
		cin>>a[i]>>b[i]>>c[i]>>d[i];
	}
	int rat;
	cin>>rat;
	int A,B,C,D;
	cin>>A>>B>>C>>D;
	ll area = (ll)(C-A)*(D-B);

	int l=1;
	int r=1e5+7;
	while(l<r) {
		int m = (l+r)/2;
		vector<Segment> segs;
		for(int i=0;i<n;i++) {
			segs.push_back({max(A,a[i]-m),max(B,b[i]-m),min(D-1,d[i]+m-1),1});
			segs.push_back({min(C,c[i]+m),max(B,b[i]-m),min(D-1,d[i]+m-1),-1});
		}
		sort(segs.begin(),segs.end());
		ll cur = 0;
		ll p = -INF;
		for(Segment it:segs) {
			cur += (it.x-p)*cov[1];
			insert(it.a,it.b,it.t);
			p = it.x;
		}
		if(cur*100 >= area*rat) {
			r = m;
		} else {
			l = m+1;
		}
	}
	cout<<l<<nl;

	return 0;
}
