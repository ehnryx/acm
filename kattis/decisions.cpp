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



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	int a[1<<n];
	for(int i=0;i<1<<n;i++) {
		cin>>a[i];
	}

	int ans = 0;
	vector<int> cnt(n);
	for(int j=0;j<=n;j++) {
		//cerr<<"start layer "<<j<<nl;
		for(int i=0;i<1<<j;i++) {
			//cerr<<"enter block "<<bitset<3>(i)<<nl;
			int sum = 0;
			for(int k=0;k<1<<(n-j);k++) {
				//cerr<<"look at "<<bitset<3>(k<<j|i)<<nl;
				sum += a[k<<j|i];
			}
			if(sum == 0 || sum == (1<<(n-j))) {
				//cerr<<"good block"<<nl;
				if(j==0 || cnt[j-1]==0) {
					ans++;
				} else {
					cnt[j-1] -= 1<<(n-j);
				}
				cnt[j] += 1<<(n-j);
			}
		}
	}
	cout<<2*ans-1<<nl;

	return 0;
}
