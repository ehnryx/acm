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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Rect {
	int a,b,c,d;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m,k;
	cin>>n>>m>>k;
	map<int,vector<int>> v;
	for(int i=0;i<k;i++) {
		int a,b;
		cin>>a>>b;
		v[a].push_back(b);
	}
	v[n+1].push_back(m+1);

	for(auto it=v.begin();next(it)!=v.end();it++) {
		auto jt = next(it);
		int lb = (it==v.begin() ? 1 : it->first);
		int ub = jt->first-1;
		auto& h = it->second;
		sort(h.begin(),h.end());
		h.push_back(m+1);
		for(int j=0;j+1<h.size();j++) {
			int l = (j==0 ? 1 : h[j]);
			int r = h[j+1]-1;
			cout<<lb<<" "<<l<<" "<<ub<<" "<<r<<nl;
		}
	}
	cout<<0<<nl;

	return 0;
}
