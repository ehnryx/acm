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

vector<int> p;
unordered_map<ll,int> cnt;
void get_factors(ll v) {
	for (int it : p) {
		while (v%it == 0) {
			cnt[it]++;
			v /= it;
		}
	}
	if (v>1) {
		cnt[v]++;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	const int N = 1e6+1;
	const int S = 1e3+1;
	bitset<N> np;
	for (int i=2; i<S; i++) {
		if (!np[i]) {
			for (int j=i*i; j<N; j+=i) {
				np[j] = true;
			}
		}
	}
	for (int i=2; i<N; i++) {
		if (!np[i]) {
			p.push_back(i);
		}
	}

	int b, n;
	cin >> b >> n;

	for (int i=0; i<n; i++) {
		ll v;
		cin >> v;
		get_factors(v);
	}

	ll dp[cnt.size()+1][b+1];
	memset(dp, 0, sizeof dp);
	dp[0][1] = 1;
	int id = 0;
	for (const auto& it : cnt) {
		id++;
		for (int i=1; i<=b; i++) {
			for (int j=0; j<=it.second && i*(j+1)<=b; j++) {
				dp[id][i*(j+1)] = (dp[id][i*(j+1)] + dp[id-1][i]) % MOD;
			}
		}
	}
	cerr << "primes: " << id << nl;
	cout << dp[id][b] << nl;

	return 0;
}
