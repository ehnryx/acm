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

	int n;
	cin>>n;
	int a[n],b[n];
	for(int i=0;i<n;i++) {
		cin>>a[i]>>b[i];
	}

	int ans = 0;
	int x[n/2],y[n/2];
	for(int bm=0;bm<1<<n;bm++) {
		if(__builtin_popcount(bm) != n/2 || !(bm&1)) continue;
		vector<int> p,o;
		for(int i=0;i<n;i++) {
			if(bm&1<<i) p.push_back(i);
			else o.push_back(i);
		}
		do {
			bool ok = true;
			for(int i=0;i<n/2;i++) {
				if(p[i]>o[i]) {
					ok = false;
					break;
				} else {
					x[i] = a[p[i]]-a[o[i]];
					y[i] = b[p[i]]-b[o[i]];
				}
			}
			if(ok) {
				int cnt = 0;
				for(int i=0;i<n/2;i++) {
					for(int j=0;j<i;j++) {
						cnt += (x[i]*y[j] == x[j]*y[i]);
					}
				}
				ans = max(ans,cnt);
			}
		} while(next_permutation(o.begin(),o.end()));
	}
	cout<<ans<<nl;

	return 0;
}
