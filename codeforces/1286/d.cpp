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

int add(int a, int b) {
	return (a+b<MOD ? a+b : a+b-MOD);
}

int mul(int a, int b) {
	return (ll)a*b % MOD;
}

int power(int n, int e) {
	int res = 1;
	for(;e;e/=2) {
		if(e&1) res = mul(res, n);
		n = mul(n, n);
	}
	return res;
}

int inverse(int n) {
	return power(n, MOD-2);
}

enum {
	MIDDLE, LEFT, RIGHT;
};
struct Event {
	int i, tn, td, dir;
	bool operator < (const Event& o) const {
		return (ll)tn*o.td < (ll)td*o.tn;
	}
};

const int N = 1e5+1;
int x[N], s[N], p[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	int inv100 = inverse(100);
	for(int i=0; i<n; i++) {
		cin >> x[i] >> s[i] >> p[i];
		p[i] = mul(p[i], inv100);
		lval[i] = add(1, MOD-p[i]);
		rval[i] = p[i];
	}

	vector<Event> events;
	for(int i=1; i<n; i++) {
		events.push_back({i, x[i]-x[i-1], s[i]+s[i-1], MIDDLE});
		if(s[i] < s[i-1]) {
			events.push_back({i, x[i]-x[i-1], s[i-1]-s[i], RIGHT});
		} else if(s[i] > s[i-1]) {
			events.push_back({i, x[i]-x[i-1], s[i]-s[i-1], LEFT});
		}
	}
	sort(events.begin(), events.end());

	int cur = 1;
	int ans = 0;
	for(auto [i, tn, td, dir] : events) {

	}
	cout << ans << nl;

	return 0;
}
