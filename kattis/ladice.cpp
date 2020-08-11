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

const int N = 3e5+1;
int dsu[N],sz[N],cnt[N];
int find(int i) {
	if(dsu[i]==-1) return i;
	return dsu[i]=find(dsu[i]);
}
bool link(int i, int j) {
	i=find(i); j=find(j);
	if(i!=j) {
		sz[i] += sz[j];
		cnt[i] += cnt[j];
		dsu[j] = i;
	}
	if(cnt[i]==sz[i]) return false;
	assert(cnt[i]<sz[i]);
	cnt[i]++;
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	fill(dsu,dsu+N,-1);
	fill(sz,sz+N,1);
	fill(cnt,cnt+N,0);

	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		int a,b;
		cin>>a>>b;
		if(link(a,b)) {
			cout<<"LADICA"<<nl;
		} else {
			cout<<"SMECE"<<nl;
		}
	}

	return 0;
}
