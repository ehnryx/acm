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

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int N = 2e5+1;
vector<int> adj[N];
int par[N];

int pre[N], post[N], sz[N];
int pid, poid;
int build(int u) {
	pre[u] = pid++;
	sz[u] = 1;
	for(int v:adj[u]) {
		sz[u] += build(v);
	}
	post[u] = poid++;
	return sz[u];
}

inline bool anc(int a, int b) {
	return pre[a]<pre[b] && post[a]>post[b];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	//cin>>n;
	read(n);
	for(int i=1;i<=n;i++) {
		//cin>>par[i];
		read(par[i]);
		adj[par[i]].push_back(i);
	}
	build(0);

	int m;
	//cin>>m;
	read(m);
	int q[20];
	for(int i=0;i<m;i++) {
		int k;
		//cin>>k;
		read(k);
		for(int j=0;j<k;j++) {
			//cin>>q[j];
			read(q[j]);
			for(int h=0;h<j;h++) {
				if(q[h]==-1) continue;
				if(anc(q[h],q[j])) {
					q[j] = -1;
					break;
				} else if(anc(q[j],q[h])) {
					q[h] = -1;
				}
			}
		}
		int ans = 0;
		for(int j=0;j<k;j++) {
			if(q[j]!=-1) {
				ans += sz[q[j]];
			}
		}
		cout<<ans<<nl;
	}

	return 0;
}
