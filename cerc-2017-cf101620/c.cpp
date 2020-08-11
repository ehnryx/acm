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

const int N = 15;
ll dps[N+1][1<<N], dp1[N+1][1<<N], dph[N+1][1<<N];

int a,d,k;
ll solve(int n, int s, int id) {
	if(n == 0 || id > a+d*(k-1)) return 0;
	//cerr<<"@ "<<n<<" "<<s<<" "<<id<<nl;

	bool right = (__builtin_popcount(s)+__builtin_clz(s) == 32);
	if(right) {
		//cerr<<"is right"<<nl;
		ll sum = solve(n-1, 2*s, id) + solve(n-1, 2*s+1, id + (1<<(n-1)));
		int sid = id + (1<<(n-1)) - 1;
		if(a <= sid && sid < a+d*k && (sid-a)%d == 0) {
			sum += 2*s+1;
			//cerr<<"add 2*"<<s<<"+1 at "<<s<<nl;
		}
		//cerr<<"GOT "<<sum<<" @ "<<s<<nl;
		//cerr<<nl;
		return sum;
	}

	else {
		int len = (1<<n) - 1;
		int sid = id + len-1;
		int nxt = a + (max(0,id-a)+d-1)/d * d;
		//cerr<<"is left w/ len "<<len<<nl;
		//cerr<<"nxt is "<<nxt<<nl;
		if(nxt > sid) return 0;
		int shift = nxt - id;
		//cerr<<"shift is "<<shift<<nl;
		if(n <= N && a <= id && id+len <= a+d*k && dps[n][shift] != -1) {
			//cerr<<"memoized! "<<dps[n][shift]<<"*"<<s<<" + "<<dp1[n][shift]<<" + "<<dph[n][shift]<<"*"<<s<<"/2"<<nl;
			//cerr<<nl;
			//if(n<1 || n>=N || shift<0 || shift>=1<<N) for(;;);
			return dps[n][shift]*s + dp1[n][shift] + dph[n][shift]*(s/2);
		}

		int rid = id + len/2;
		ll sum = solve(n-1, 2*s, id) + solve(n-1, 2*s+1, rid);
		if(a <= sid && sid < a+d*k && (sid-a)%d == 0) {
			sum += s/2;
			//cerr<<"add "<<s<<"/2 at "<<s<<nl;
		}
		//cerr<<"GOT "<<sum<<" @ "<<s<<nl;

		if(n <= N && a <= id && id+len <= a+d*k) {
			//if(n<1 || n>=N || shift<0 || shift>=1<<N) for(;;);
			dps[n][shift] = dp1[n][shift] = dph[n][shift] = 0;
			//cerr<<"add "<<n-1<<" "<<shift<<nl;
			if(dps[n-1][shift] != -1) {
				dps[n][shift] += 2*dps[n-1][shift] + dph[n-1][shift];
				dp1[n][shift] += dp1[n-1][shift];
			}
			int nxtr = a + (max(0,rid-a)+d-1)/d * d;
			int shiftr = nxtr - rid;
			//if(shiftr>=1<<N) for(;;);
			//cerr<<"add "<<n-1<<" "<<shiftr<<nl;
			if(shiftr < 1<<N && dps[n-1][shiftr] != -1) {
				dps[n][shift] += 2*dps[n-1][shiftr] + dph[n-1][shiftr];
				dp1[n][shift] += dps[n-1][shiftr] + dp1[n-1][shiftr];
			}
			if((sid-a)%d == 0) {
				dph[n][shift] += 1;
			}
			//cerr<<"mem "<<n<<" "<<shift<<" -> "<<dps[n][shift]<<" "<<dp1[n][shift]<<" "<<dph[n][shift]<<nl;
			//assert(dps[n][shift]*s + dp1[n][shift] + dph[n][shift]*(s/2) == sum);
		}
		//cerr<<nl;

		return sum;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;

	for(int i=0;i<m;i++) {
		cin>>a>>d>>k;
		memset(dps,-1,sizeof dps);
		cout<<solve(n,1,1)<<nl;
		//cerr<<nl;
	}

	return 0;
}
