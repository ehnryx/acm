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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int v[6],a,b;
	for(int i=0;i<6;i++) {
		cin>>v[i];
	}
	cin>>a>>b;
	for(int bm=0;bm<1<<6;bm++) {
		if(__builtin_popcount(bm)!=3) continue;
		vector<int> l,r;
		int left = 0;
		for(int j=0;j<6;j++) {
			if(bm&1<<j) {
				left += v[j];
				l.push_back(v[j]);
			} else {
				r.push_back(v[j]);
			}
		}
		if(left == a) {
			sort(l.begin(),l.end(),greater<int>());
			sort(r.begin(),r.end(),greater<int>());
			for(int it:l) cout<<it<<" ";
			for(int it:r) cout<<it<<" ";
			cout<<nl;
			return 0;
		}
	}
	assert(false);

	return 0;
}
