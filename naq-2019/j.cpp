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

struct Frac {
	ll n, d;
	Frac(ll a, ll b): n(a), d(b) {}
	bool operator < (const Frac& o) const {
		return (ld)n/d < (ld)o.n/o.d;
	}
};

const int M = 70;
const int N = 1e6+1;
ll a[N], s[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	set<Frac> cur;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		s[i] = s[i-1] + a[i];
		cur.insert(Frac(s[i],i));
	}

	ld ans = 0;
	ll top = 0;
	ll bot = 0;
	for(int i=n;i>=0;i--) {
		auto it = cur.rbegin();
		for(int j=0;j<M&&it!=cur.rend();j++) {
			ans = max(ans, (ld)(top+it->n)/(bot+it->d));
		}
		if(bot>0) {
			ans = max(ans, (ld)(top/bot));
		}
		top += a[i];
		bot += 1;
		cur.erase(Frac(s[i],i));
	}
	cout<<ans<<nl;

	return 0;
}
