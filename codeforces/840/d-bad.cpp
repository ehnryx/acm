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

const int N = 3e5+1;
const int K = 17;
int a[N], l[N], r[N], k[N];
int ans[N];
vector<pii> best[N];

void solve(int left, int right, const vector<int>& q) {
	if(left==right) {
		for(int i:q) {
			ans[i]=a[left];
		}
		return ;
	}
	int mid = (left+right)/2;

	unordered_map<int,int> f;
	for(int i=mid;i>=left;i--) {
		int cnt = ++f[a[i]];
		if(i==mid) {
			best[i] = { pii(a[i],1) };
		} else {
			best[i] = best[i+1];
			bool found = false;
			for(pii& j:best[i]) {
				if(j.first == a[i]) {
					found = true;
					j.second = cnt;
				}
			}
			if(!found) {
				if(best[i].size()<K) {
					best[i].push_back(pii(a[i],cnt));
				} else if(best[i][K-1].second<cnt) {
					best[i][K-1]=pii(a[i],cnt);
				}
			}
		}
	}

	f.clear();
	for(int i=mid+1;i<=right;i++) {
		int cnt = ++f[a[i]];
		if(i==mid+1) {
			best[i] = { pii(a[i],1) };
		} else {
			best[i] = best[i-1];
			bool found = false;
			for(pii& j:best[i]) {
				if(j.first == a[i]) {
					found = true;
					j.second = cnt;
				}
			}
			if(!found) {
				if(best[i].size()<K) {
					best[i].push_back(pii(a[i],cnt));
				} else if(best[i][K-1].second<cnt) {
					best[i][K-1]=pii(a[i],cnt);
				}
			}
		}
	}

	vector<int> lq,rq;
	for(int i:q) {
		if(r[i]<=mid) {
			lq.push_back(i);
		} else if(l[i]>mid) {
			rq.push_back(i);
		} else {
			ans[i]=INF;
			int lb = (r[i]-l[i]+1)/k[i];
			for(pii it:best[l[i]]) {
				for(pii jt:best[r[i]]) {
					if(it.first==jt.first) {
						if(it.second+jt.second>lb) ans[i] = min(ans[i],it.first);
					} else {
						if(it.second>lb) ans[i] = min(ans[i],it.first);
						if(jt.second>lb) ans[i] = min(ans[i],jt.first);
					}
				}
			}
			if(ans[i]==INF) ans[i]=-1;
		}
	}

	solve(left,mid,lq);
	solve(mid+1,right,rq);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
	}
	vector<int> q;
	for(int i=0;i<m;i++) {
		cin>>l[i]>>r[i]>>k[i];
		q.push_back(i);
	}
	solve(1,n,q);

	for(int i=0;i<m;i++) {
		cout<<ans[i]<<nl;
	}

	return 0;
}
