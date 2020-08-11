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

struct Frac {
	ll n,d;
	Frac(ll a, ll b) {
		ll g = __gcd(a,b);
		n = a/g; d = b/g;
	}
	Frac operator + (const Frac& o) const {
		return Frac(n*o.d + d*o.n, d*o.d);
	}
	bool operator < (const Frac& o) const {
		return d < o.d;
	}
	friend ostream& operator << (ostream& os, const Frac& v) {
		return os << v.n << "/" << v.d;
	}
};

Frac calc(const string& s, int d) {
	int len = s.size();
	int head = (len==d ? 0 : stoi(s.substr(0, len-d)));
	int tail = stoi(s.substr(len-d));
	int denom = llround(pow(10,len-d));
	int nines = llround(pow(10,d))-1;
	return Frac(head,denom) + Frac(tail,denom*nines);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(string s; cin>>s && s!="0"; ) {
		s.pop_back();
		s.pop_back();
		s.pop_back();
		s = s.substr(2);
		Frac ans(INFLL-1,INFLL);
		for(int i=1;i<=s.size();i++) {
			ans = min(ans, calc(s,i));
		}
		cout<<ans<<nl;
	}

	return 0;
}
