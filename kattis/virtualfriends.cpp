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

const int N = 2e5+1;
int dsu[N],sz[N];
int find(int i) {
	if(dsu[i]==-1) return i;
	return dsu[i]=find(dsu[i]);
}
int link(int i, int j) {
	i=find(i); j=find(j);
	if(i!=j) {
		sz[i] += sz[j];
		dsu[j] = i;
	}
	return sz[i];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin>>T;
	while(T--) {
		fill(dsu,dsu+N,-1);
		fill(sz,sz+N,1);

		int n;
		cin>>n;
		int m = 0;
		unordered_map<string,int> idx;
		for(int i=0;i<n;i++) {
			string s,t;
			cin>>s>>t;
			if(!idx.count(s)) idx[s] = m++;
			if(!idx.count(t)) idx[t] = m++;
			cout<<link(idx[s],idx[t])<<nl;
		}
	}

	return 0;
}
