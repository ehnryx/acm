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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n,m;cin>>n>>m;) {
		int M = m;
		bool ok = (m>0);
		for(ll i=2;i*i<=m;i++) {
			int cnt = 0;
			while(m%i==0) {
				m /= i;
				cnt++;
			}
			if(cnt) {
				int has = 0;
				for(int j=n;j>0;j/=i) {
					has += j/i;
				}
				cerr<<n<<" has "<<has<<" factors of "<<i<<", while "<<M<<" has "<<cnt<<nl;
				ok &= (cnt<=has);
			}
		}
		if(m>1) {
			ok &= (m<=n);
		}
		if(ok) {
			cout<<M<<" divides "<<n<<"!"<<nl;
		} else {
			cout<<M<<" does not divide "<<n<<"!"<<nl;
		}
	}

	return 0;
}
