#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int K = 1e5+2;
const int N = 100+1;

struct BIT {
	ll f[K];
	BIT() { memset(f, 0, sizeof f); }
	ll query(int x) {
		ll res = 0;
		for ( ; x>0; x-=x&-x) {
			res += f[x];
		}
		return res % MOD;
	}
	ll query(int l, int r) {
		return (query(r) - query(l-1) + MOD) % MOD;
	}
	void insert(int x, ll v) {
		for ( ; x<K; x+=x&-x) {
			f[x] = (f[x]+v) % MOD;
		}
	}
};

BIT bit[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, k;
	cin >> n >> k;

	bit[0].insert(1, 1);
	FOR(i,1,n) {
		int a;
		cin >> a;
		for (int j=1; j<=k+1; j++) {
			ll cur = bit[i-1].query(max(1,j-a), j);
			bit[i].insert(j, cur);
		}
	}
	cout << bit[n].query(k+1, k+1) << nl;

	return 0;
}

