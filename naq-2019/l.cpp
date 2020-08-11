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

const int N = 1e5+1;
const int S = 300;
const int M = N/S+2;
const int L = 17;
int v[N],d[N];
int A[7][N],R[7][N];
int mul[7] = { 0, 1, 2, 3, 2, 1, 0 };

struct Solver {
	int minv[N][L], maxv[N][L];
	int blk[M];

	void build(int a[], int n) {
		for(int i=0;i<n;i++) {
			minv[i][0] = maxv[i][0] = a[i];
		}
		for(int j=1;j<L;j++) {
			for(int i=0;i+(1<<(j-1))<n;i++) {
				minv[i][j] = min(minv[i][j-1], minv[i+(1<<(j-1))][j-1]);
				maxv[i][j] = max(maxv[i][j-1], maxv[i+(1<<(j-1))][j-1]);
			}
		}
		for(int s=0;s<n;s+=S) {
			int id = s/S;
			blk[id] = 0;
			int curmin = INF;
			for(int i=0;i<S;i++) {
				curmin = min(curmin, a[s+i]);
				blk[id] = max(blk[id], a[s+i]-curmin);
			}
			//cerr<<"blk "<<id<<": "<<blk[id]<<nl;
		}
		//cerr<<nl;
	}

	int getmin(int l, int r) {
		if(l>r) return INF;
		int j = 31 - __builtin_clz(r-l+1);
		return min(minv[l][j], minv[r-(1<<j)+1][j]);
	}
	int getmax(int l, int r) {
		if(l>r) return -INF;
		int j = 31 - __builtin_clz(r-l+1);
		return max(maxv[l][j], maxv[r-(1<<j)+1][j]);
	}

	int easy(int l, int r) {
		int res = 0;
		int curmin = INF;
		for(int i=l;i<=r;i++) {
			curmin = min(curmin, minv[i][0]);
			res = max(res, minv[i][0]-curmin);
		}
		return res;
	}

	int solve(int l, int r) {
		//cerr<<"solve "<<l<<" "<<r<<nl;
		int lb = (l+S-1)/S;
		int rb = r/S-1;
		if(rb<lb) {
			//cerr<<"easy "<<l<<" "<<r<<nl;
			return easy(l,r);
		} else {
			//cerr<<"easy "<<l<<" "<<lb*S-1<<" and "<<rb*S+S<<" "<<r<<nl;
			int res = max(easy(l,lb*S-1), easy(rb*S+S,r));
			//cerr<<res<<nl;
			for(int i=lb;i<=rb;i++) {
				//cerr<<"   and blk "<<i<<nl;
				res = max(res, blk[i]);
				//cerr<<res<<nl;
				int cur = getmax(i*S,r) - getmin(l,i*S-1);
				//cerr<<"   get diff "<<i*S<<" "<<r<<" - "<<l<<" "<<i*S-1<<nl;
				res = max(res, cur);
				//cerr<<res<<nl;
			}
			res = max(res, getmax(rb*S+S,r) - getmin(l,rb*S+S-1));
			//cerr<<"   get diff "<<rb*S+S<<" "<<r<<" - "<<l<<" "<<rb*S+S-1<<nl;
			//cerr<<res<<nl;
			return res;
		}
	}
};

Solver solve_right[7], solve_left[7];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>v[i]>>d[i];
	}
	for(int s=0;s<7;s++) {
		for(int i=1;i<=n;i++) {
			A[s][i] = v[i] + d[i]*mul[((i-s)%7+7)%7];
			R[s][n-i] = v[i] + d[i]*mul[((s-i)%7+7)%7];
		}
		//cerr<<"right "<<s<<": ";for(int i=0;i<=n;i++) {
		//cerr<<A[s][i]<<" "; } //cerr<<nl;
		//cerr<<"left "<<s<<": ";for(int i=0;i<=n;i++) {
		//cerr<<R[s][i]<<" "; } //cerr<<nl;
		//cerr<<nl;
		solve_right[s].build(A[s],n+1);
		solve_left[s].build(R[s],n+1);
	}

	int m;
	cin>>m;
	for(int i=0;i<m;i++) {
		int l,r;
		cin>>l>>r;
		//cerr<<"SOLVING "<<l%7<<nl;
		if(l<r) {
			int s = l%7;
			cout<<solve_right[s].solve(l,r)<<nl;
		} else {
			int s = l%7;
			cout<<solve_left[s].solve(n-l,n-r)<<nl;
		}
	}

	return 0;
}
