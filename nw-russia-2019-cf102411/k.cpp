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

const int N = 1<<10;
char g[N][N];

struct RMQ {
	int st[2*N];
	RMQ(int v) { fill(st,st+2*N,v); }
	void insert(int i, int v) {
		i += N;
		st[i] = min(st[i], v);
		for(i/=2;i;i/=2) {
			st[i] = min(st[2*i], st[2*i+1]);
		}
	}
	int query(int l, int r) {
		int res = INF;
		for(l+=N,r+=N+1; l<r; l/=2,r/=2) {
			if(l&1) res = min(res, st[l++]);
			if(r&1) res = min(res, st[--r]);
		}
		return res;
	}
};

void solve(int li, int ri, int lj, int rj) {
	if(li>ri || lj>rj) return;
	//cerr<<"solve "<<li<<" "<<ri<<" "<<lj<<" "<<rj<<nl;
	for(int i=li;i<=ri;i++) {
		for(int j=lj;j<=rj;j++) {
			if(j > lj && g[i][j] == '.') {
				g[i][j] = tolower(g[i][j-1]);
			}
		}
		for(int j=rj;j>=lj;j--) {
			if(j < rj && g[i][j] == '.') {
				g[i][j] = tolower(g[i][j+1]);
			}
		}
		if(i > li && g[i][lj] == '.') {
			for(int j=lj;j<=rj;j++) {
				assert(g[i][j] == '.');
				g[i][j] = tolower(g[i-1][j]);
			}
		}
	}
	for(int i=ri;i>=li;i--) {
		if(i < ri && g[i][lj] == '.') {
			for(int j=lj;j<=rj;j++) {
				assert(g[i][j] == '.');
				g[i][j] = tolower(g[i+1][j]);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	int si = -1;
	int sj = -1;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			cin>>g[i][j];
			if(g[i][j] == 'A') {
				si = i;
				sj = j;
			}
		}
	}

	RMQ top(si+1), bot(n-si);
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			if(g[i][j] != 'A' && g[i][j] != '.') {
				if(i <= si) {
					top.insert(j, si-i);
				} else {
					bot.insert(j, i-si);
				}
			}
		}
	}

	int best = 0;
	int i1, j1, i2, j2;
	i1 = j1 = i2 = j2 = -1;
	for(int l=0; l<=sj; l++) {
		for(int r=sj; r<m; r++) {
			int tlr = top.query(l,r);
			if(tlr == 0) continue;
			int blr = bot.query(l,r);
			assert(tlr<INF && blr<INF);
			int cur = (r-l+1) * (tlr + blr - 1);
			if(cur > best) {
				best = cur;
				i1 = si-tlr+1;
				i2 = si+blr-1;
				j1 = l;
				j2 = r;
			}
		}
	}

	//cerr<<"fill rect iijj "<<i1<<" "<<i2<<" "<<j1<<" "<<j2<<nl;
	assert(i1<=i2 && j1<=j2);
	for(int i=i1;i<=i2;i++) {
		for(int j=j1;j<=j2;j++) {
			if(g[i][j] == '.') {
				g[i][j] = 'a';
			} else {
				assert(g[i][j] == 'A');
			}
		}
	}

	solve(0, i1-1, 0, m-1);
	solve(i1, n-1, 0, j1-1);
	solve(i1, n-1, j2+1, m-1);
	solve(i2+1, n-1, j1, j2);

	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			assert(g[i][j] != '.');
			cout<<g[i][j];
		}
		cout<<nl;
	}

	return 0;
}
