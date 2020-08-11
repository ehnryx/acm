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

const int N = 1<<17;
vector<int> idx[N];
int a[N],p[N];

ll st[2*N],z[2*N];
void build() {
	for(int i=N-1;i>0;i--) {
		st[i] = min(st[2*i],st[2*i+1]);
	}
}
void push(int i) {
	if(z[i]) {
		st[2*i] += z[i];
		st[2*i+1] += z[i];
		z[2*i] += z[i];
		z[2*i+1] += z[i];
		z[i] = 0;
	}
}
void update(int l, int r, int v, int i=1, int s=0, int e=N-1) {
	if(r<s||e<l) return;
	if(l<=s&&e<=r) {
		st[i] += v;
		z[i] += v;
		return;
	}
	push(i);
	int m = (s+e)/2;
	update(l,r,v,2*i,s,m);
	update(l,r,v,2*i+1,m+1,e);
	st[i] = min(st[2*i],st[2*i+1]);
}
int query(int l, int r, int i=1, int s=0, int e=N-1) {
	if(r<s||e<l) return -1;
	if(st[i]>0) return -1;
	if(s==e) return s;
	push(i);
	int m = (s+e)/2;
	int right = query(l,r,2*i+1,m+1,e);
	if(right!=-1) return right;
	else return query(l,r,2*i,s,m);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	const int BIG = n+7;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		idx[a[i]].push_back(i);
		if(idx[a[i]].size() == 1) {
			st[N+i] = st[N+i-1] + 1;
		} else if(idx[a[i]].size() == 2) {
			st[N+i] = st[N+i-1] - 1;
		} else {
			st[N+i] = st[N+i-1] + BIG;
		}
	}
	build();

	int ans = 0;
	for(int i=1;i<=n;i++) {
		int j = query(i-1,n);
		ans = max(ans, j-i+1);
		update(idx[a[i]][p[a[i]]],n,-1);
		if(++p[a[i]] < idx[a[i]].size()) {
			update(idx[a[i]][p[a[i]]],n,2);
		}
		if(p[a[i]]+1 < idx[a[i]].size()) {
			update(idx[a[i]][p[a[i]]+1],n,-BIG-1);
		}
	}
	cout<<ans<<nl;

	return 0;
}
