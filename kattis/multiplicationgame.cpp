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

	unordered_map<string,string> op;
	op["Alice"] = "Bob";
	op["Bob"] = "Alice";

	int T;
	cin>>T;
	while(T--) {
		int n;
		cin>>n;
		string s;
		cin>>s;
		int tot = 0;
		int minv = INF;
		int maxv = 1;
		for(ll i=2;i*i<=n;i++) {
			if(n%i == 0) {
				int cur = 0;
				while(n%i == 0) {
					n /= i;
					tot++;
					cur++;
				}
				minv = min(minv,cur);
				maxv = max(maxv,cur);
			}
		}
		if(n>1) {
			tot++;
			minv = 1;
		}

		//cerr<<"tot: "<<tot<<nl;
		//cerr<<"minv: "<<minv<<nl;
		if(tot%2 == 0) {
			if(minv<tot/2) {
				cout<<"tie"<<nl;
			} else {
				cout<<op[s]<<nl;
			}
		} else {
			if(minv<tot/2 || maxv-1<tot/2) {
				cout<<"tie"<<nl;
			} else {
				cout<<s<<nl;
			}
		}
	}

	return 0;
}
