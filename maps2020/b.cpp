//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll mod_mul(ll a, ll b, ll m) {
	return (__int128)a*b % m;
}

ll power(ll n, ll e, ll m) {
	ll r = 1;
	for( ; e>0; e/=2) {
		if(e&1) r = mod_mul(r, n, m);
		n = mod_mul(n, n, m);
	}
	return r;
}

const ll wit[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool is_prime(ll n) {
	if(n<2) return 0;
	if(n%2 == 0) return n == 2;
	ll r = __builtin_ctzll(n-1), d = (n-1)>>r;
	for(ll a : wit) {
		a%=n; if(!a) return 1;
		if(a==1 || a==n-1) continue;
		ll x = power(a, d, n), y;
		for(int i=0; i<r; i++) {
			y = mod_mul(x,x,n);
			if(y==1 && x!=1 && x!=n-1) return 0;
			x = y;
		}
		if(x!=1) return 0;
	}
	return 1;
}

ll get_factor(ll n) {
	if(n%2 == 0) return 2;
	if(is_prime(n)) return n;
	while(1) {
		ll x = rng()%(n-1)+1, c=rng()%(n-1)+1, y=2, d=1;
		for(int sz=2; d==1; sz*=2) {
			for(int i=0; i<sz && d<=1; i++)
				x = (mod_mul(x,x,n)+c) % n, d = __gcd(abs(x-y),n);
			y = x;
		}
		if(d>1 && d!=n) return d;
	}
}

vector<pair<ll,int>> fac;
void prime_factor(ll n) {
	while(n>1) {
		ll k = get_factor(n);
		while(!is_prime(k)) k = get_factor(k);
		int cnt = 0;
		while(n % k == 0) {
			n /= k;
			cnt++;
		}
		fac.push_back(make_pair(k, cnt));
	}
}

bool solve(ll b, int n, ll v, ll d) {
	if(n<0) return (power(b,v,d) == d-1);
	ll curf = 1;
	for(int j=0; j<=fac[n].second; j++) {
		if(solve(b, n-1, v*curf, d)) return true;
		curf *= fac[n].first;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	ll b, d;
	cin >> b >> d;
	if(d == 2) {
		if(b % 2 == 0) {
			cout << "no" << nl;
		} else {
			cout << "yes" << nl;
		}
		return 0;
	}

	prime_factor(d-1);
	shuffle(fac.begin(), fac.end(), rng);
	assert(!fac.empty());
	if(solve(b, fac.size()-1, 1, d)) {
		cout << "yes" << nl;
	} else {
		cout << "no" << nl;
	}

	return 0;
}
