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

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
template <typename T> inline void read(T &x) {
	static char c; x = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) ;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}
inline void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int N = 5e5+1;
int p[N];
int cnt[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n; ll a,b; int c,d;
	//cin>>n>>a>>b>>c>>d;
	read(n);read(a);read(b);read(c);read(d);
	--a; --b;

	for(int i=1;i<=n;i++) {
		//cin>>p[i];
		read(p[i]);
	}

	for(int i=1;i<=n;i++) {
		if(!cnt[i]) {
			cnt[i] = 1;
			for(int j=p[i];j!=i;j=p[j]) {
				cnt[i]++;
			}
			for(int j=p[i];j!=i;j=p[j]) {
				cnt[j] = cnt[i];
			}
		}
	}

	ll lcm = 1;
	for(int i=c+1;i<=n-d;i++) {
		lcm = lcm*cnt[i] / __gcd(lcm,(ll)cnt[i]);
		if(lcm > b) {
			cout<<0<<nl;
			return 0;
		}
	}

	cout<<(b/lcm)-(a/lcm)+(a%lcm==0)<<nl;

	return 0;
}
