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

typedef __int128 lll;
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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

lll gcd(lll a, lll b) {
	if(b==0) return a;
	else return gcd(b, a%b);
}

lll lcm(lll a, lll b) {
	if(a==0 || b==0) return 0;
	return a * b / gcd(a,b);
}

const int N = 1<<17;
lll st[2*N];

void build() {
	for(int i=N-1;i>0;i--) {
		st[i] = lcm(st[2*i],st[2*i+1]);
	}
}

lll query(int l, int r) {
	lll ans = 1;
	for(l+=N,r+=N;l<r;l/=2,r/=2) {
		if(l&1) ans = lcm(ans,st[l++]);
		if(r&1) ans = lcm(ans,st[--r]);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	vector<pair<ld,int>> p;
	for(int i=0;i<n;i++) {
		ld r; int o;
		cin>>r>>o;
		p.push_back(make_pair(r,o));
	}
	sort(p.begin(),p.end());

	for(int i=0;i<n;i++) {
		st[i+N] = p[i].second;
	}
	build();

	for(int i=0;i<m;i++) {
		ld l, r;
		cin>>l>>r;
		int L = lower_bound(p.begin(),p.end(),make_pair(l,0)) - p.begin();
		int R = upper_bound(p.begin(),p.end(),make_pair(r,INF)) - p.begin();
		cout<<(ll)query(L,R)<<nl;
	}

	return 0;
}
