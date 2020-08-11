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

struct Book {
	int a,d;
	bool operator < (const Book& o) const {
		return d < o.d;
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	Book v[n];
	for(int i=0;i<n;i++) {
		cin>>v[i].a>>v[i].d;
	}
	sort(v,v+n);

	function<bool(ll)> valid = [&](ll s) {
		priority_queue<int> nxt;
		ll cur = 0;
		int late = 0;
		for(int i=0;i<n;i++) {
			cur += v[i].a;
			nxt.push(v[i].a);
			while(cur > v[i].d*s) {
				late++;
				cur -= nxt.top();
				nxt.pop();
			}
		}
		return late <= m;
	};

	ll l = 0;
	ll r = 2e14;
	while(l<r) {
		ll k = (l+r)/2;
		if(valid(k)) {
			r = k;
		} else {
			l = k+1;
		}
	}
	cout<<l<<nl;

	return 0;
}
