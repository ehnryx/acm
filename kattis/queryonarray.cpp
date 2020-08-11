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

ll modpow(ll n, ll e) {
	ll res = 1;
	for(;e;e/=2) {
		if(e&1) res = res*n % MOD;
		n = n*n % MOD;
	}
	return res;
}

const ll half = modpow(2, MOD-2);
const ll third = modpow(3, MOD-2);
const ll fourth = modpow(4, MOD-2);
const ll sixth = modpow(6, MOD-2);

struct Node {
	vector<ll> v;
	Node() { v.resize(5,0); }
	Node(ll a, int s) {
		vector<ll> c = {
			s * (3*a*a - a*a*a - 2*a) % MOD,
			s * (2 + 3*a*a - 6*a) % MOD,
			s * (3 - 3*a) % MOD,
			s * (1) % MOD,
		};
		v = {
			0,
			(c[0] + half*c[1] + sixth*c[2]) % MOD,
			(half*c[1] + half*c[2] + fourth*c[3]) % MOD,
			(third*c[2] + half*c[3]) % MOD,
			(fourth*c[3]) % MOD,
		};
	}
	Node(ll a) {
		v.resize(5,0);
		v[0] = a;
	}

	ll operator () (int x) const {
		ll xn = 1;
		ll res = 0;
		for(int i=0;i<5;i++) {
			res += xn*v[i] % MOD;
			xn = xn*x % MOD;
		}
		return res % MOD;
	}
	void operator += (const Node& o) {
		for(int i=0;i<5;i++) {
			v[i] = (v[i] + o.v[i]) % MOD;
		}
	}
};

const int N = 1<<17;
Node st[2*N];

ll query(int x) {
	int i = x;
	Node res = st[x+=N];
	for(x/=2;x;x/=2) {
		res += st[x];
	}
	return res(i);
}

void insert(int l, int r, const Node& v) {
	for(l+=N,r+=N+1; l<r; l/=2,r/=2) {
		if(l&1) st[l++] += v;
		if(r&1) st[--r] += v;
	}
}

ll query_range(int l, int r) {
	return (query(r) - query(l-1) + 2*MOD) % MOD;
}

void insert_range(int l, int r, int s) {
	Node val(l-1,s);
	insert(l, r, val);
	insert(l, N-1, Node(-val(l-1)));
	insert(r+1, N-1, Node(val(r)));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int t,x,y;
		cin>>t>>x>>y;
		if(t==0) {
			cout<<query_range(x,y)<<nl;
		} else if(t==1) {
			insert_range(x,y,1);
		} else {
			insert_range(x,y,-1);
		}
	}

	return 0;
}
