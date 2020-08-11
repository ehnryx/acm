//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n; ll m;
	cin >> n >> m;
	vector<pair<int,int>> a(n);
	for(int i=0; i<n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a.begin(), a.end());

	vector<int> b(n);
	ll sum = 0;
	for(int i=0; i<n; i++) {
		b[i] = sqrt((ld)a[i].first/3);
		sum += b[i];
	}

	if(sum < m) {
		//cerr<<"sum < m"<<nl;
		int l = 0;
		int r = INF;
		while(l<r) {
			int v = (l+r+1) / 2;
			ll cnt = 0;
			for(int i=0; i<n; i++) {
				cnt += min(a[i].first, max(b[i], v));
			}
			if(cnt <= m) {
				l = v;
			} else {
				r = v-1;
			}
		}
		//cerr<<"got r = "<<r<<nl;
		ll cnt = 0;
		for(int i=0; i<n; i++) {
			b[i] = min(a[i].first, max(b[i], r));
			cnt += b[i];
		}
		assert(cnt <= m);
		cnt = abs(cnt - m);
		for(int i=n-1; cnt>0 && i>=0; i--) {
			if(b[i] == r && b[i] < a[i].first) {
				b[i]++;
				cnt--;
			}
		}
		assert(cnt == 0);
	}

	else if(sum > m) {
		//cerr<<"sum > m"<<nl;
		int l = 0;
		int r = INF;
		while(l<r) {
			int v = (l+r) / 2;
			ll cnt = 0;
			for(int i=0; i<n; i++) {
				if(b[i] >= v) {
					cnt += b[i];
				}
			}
			if(cnt <= m) {
				r = v;
			} else {
				l = v+1;
			}
		}
		ll cnt = 0;
		for(int i=0; i<n; i++) {
			if(b[i] < r) {
				b[i] = 0;
			}
			cnt += b[i];
		}
		assert(cnt <= m);
		cnt = abs(cnt - m);
		for(int i=n-1; cnt>0 && i>=0; i--) {
			if(b[i] <= sqrt((ld)a[i].first/3)) {
				b[i]++;
				cnt--;
			}
		}
		assert(cnt == 0);
	}

	ll f = 0;
	vector<int> ans(n);
	for(int i=0; i<n; i++) {
		ans[a[i].second] = b[i];
		f += (ll)b[i]*(a[i].first-b[i]*b[i]);
	}

	//cerr<<"f: "<<f<<nl;
	for(int i=0; i<n; i++) {
		cout << ans[i] << " ";
	}
	cout << nl;

	return 0;
}
