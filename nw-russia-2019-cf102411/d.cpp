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
const ll MOD = 998244353;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll n, ll e) {
	//cerr<<"power "<<n<<" "<<e<<nl;
	ll res = 1;
	for(;e;e/=2) {
		if(e&1) res = res*n % MOD;
		n = n*n % MOD;
	}
	//cerr<<"get "<<res<<nl;
	return res;
}

const int N = 1e5+1;
ll over[N], single[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,k;
	cin>>n>>k;

	for(int i=0;i<=n;i++) {
		if(i%2 == 0) {
			over[i] = ((i/2) * power(k, i/2) + (i/2) * power(k, i/2+1)) % MOD;
		} else {
			over[i] = ((i) * power(k, (i+1)/2)) % MOD;
		}
		//cerr<<"over "<<i<<": "<<over[i]<<nl;
	}

	//cerr<<"single 1: "<<over[1]<<nl;
	for(int i=0;i<=n;i++) {
		single[i] = over[i];
		if(i<2) continue;
		for(int j=1;j*j<=i;j++) {
			if(i%j == 0) {
				single[i] -= (i/j) * single[j] % MOD;
				if(j>1 && j*j!=i) {
					single[i] -= j * single[i/j] % MOD;
				}
			}
		}
		single[i] %= MOD;
		//cerr<<"single "<<i<<": "<<single[i]<<nl;
	}

	ll ans = 0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j*j<=i;j++) {
			if(i%j == 0) {
				ans = (ans + single[j]) % MOD;
				if(j*j!=i) {
					ans = (ans + single[i/j]) % MOD;
				}
			}
		}
	}
	cout<<(ans+MOD)%MOD<<nl;

	return 0;
}
