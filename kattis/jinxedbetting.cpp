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
	ll a[n];
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}

	map<ll,int> cnt;
	for(int i=1;i<n;i++) {
		cnt[a[i]]++;
	}
	cnt[-INFLL/330] = 0;

	ll ans = 0;
	for(;;) {
		auto it = prev(cnt.end());
		auto jt = prev(it);
		int d = 31 - __builtin_clz(it->second);
		ll diff = it->first - jt->first;
		if(it->first + diff*d > a[0]) {
			ll need = a[0] - it->first + 1;
			ans += ((need-1)/d) * (d+1);
			need -= ((need-1)/d) * d;
			ans += need;
			assert(need <= d);
			break;
		} else {
			ans += diff*(d+1);
			a[0] -= diff*(d+1);
			jt->second += it->second;
			cnt.erase(it);
		}
	}
	cout<<ans-1<<nl;

	return 0;
}
