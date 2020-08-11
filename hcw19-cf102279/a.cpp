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

ll lcm(ll a, ll b) {
	return a*b / __gcd(a,b);
}

ll calc(ll a, ll b, ll ab) {
	return max(ab/a, ab/b);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	ll n,a,b,c;
	cin>>n>>a>>b>>c;
	n++;

	ll ab = lcm(a,b);
	ll bc = lcm(b,c);
	ll ca = lcm(c,a);
	if(ab==n&&bc==n&&ca==n) {
		cout<<(ll)3e9<<nl;
		return 0;
	}

	int ans = 0;
	int pa=0, pb=0, pc=0;
	char vis[n];
	memset(vis,0,sizeof vis);
	for(;;) {
		ans++;
		pa = (pa+a)%n;
		if(vis[pa] && vis[pa]!='a') break;
		else if(pa) vis[pa]='a';
		ans++;
		pb = (pb+b)%n;
		if(vis[pb] && vis[pb]!='b') break;
		else if(pb) vis[pb]='b';
		ans++;
		pc = (pc+c)%n;
		if(vis[pc] && vis[pc]!='c') break;
		else if(pc) vis[pc]='c';
	}

	cout << ans << nl;

	return 0;
}
