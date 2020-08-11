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

const int M = 5;

typedef vector<vector<ll>> vvi;
vvi mul(const vvi& a, const vvi& b) {
	int n = a.size();
	vvi r(n, vector<ll>(n,0));
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			for(int k=0;k<n;k++) {
				r[i][j] += a[i][k] * b[k][j] % MOD;
			}
			r[i][j] %= MOD;
		}
	}
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	vvi base = {
		{ 2, 0, 0, 0, 0},
		{ 4, 2, 2, 0, 0 },
		{ 4, 2, 0, 0, 0 },
		{ 4, 2, 0, 0, 0 },
		{ 0, 0, 0, 2, 2 }
	};
	vvi res = {
		{ 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 1 }
	};
	vvi mat = base;
	vector<ll> init = { 1, 0, 2, 0, 1 };

	int n;
	cin>>n;
	if(n==1) {
		cout<<2<<nl;
		return 0;
	}

	for(n-=1;n;n/=2) {
		if(n&1) res = mul(res,mat);
		mat = mul(mat,mat);
	}

	vector<ll> last;
	//cerr<<"["<<nl;
	for(int i=0;i<M;i++) {
		last.push_back(0);
		for(int j=0;j<M;j++) {
			last[i] += res[i][j] * init[j] % MOD;
		}
		//cerr<<"  "<<last[i]<<","<<nl;
	}
	//cerr<<"]"<<nl;

	//cerr<<"ANSWER:"<<nl;
	cout<<2*(last[0]+last[1]+last[M-1])%MOD<<nl;

	return 0;
}
