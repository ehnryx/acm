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

bool cmp(const pii& a, const pii& b) {
	if(a.first!=b.first) return a.first>b.first;
	else return a.second<b.second;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	vector<pii> p;
	for(int i=0;i<n;i++) {
		int a,b;
		cin>>a>>b;
		p.push_back(pii(a,b));
	}
	sort(p.begin(),p.end(),cmp);

	int lis[n],pre[n],id[n];
	memset(lis,INF,sizeof lis);
	memset(pre,-1,sizeof pre);
	for(int i=0;i<n;i++) {
		int* it = upper_bound(lis,lis+n,p[i].second);
		if(it!=lis) pre[i] = id[it-lis-1];
		*it = p[i].second;
		id[it-lis] = i;
	}

	int* it = lower_bound(lis,lis+n,INF);
	cout<<it-lis<<nl;
	for(int i=id[it-lis-1];i!=-1;i=pre[i]) {
		cout<<p[i].first<<" "<<p[i].second<<nl;
	}

	return 0;
}
