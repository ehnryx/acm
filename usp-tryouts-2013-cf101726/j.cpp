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
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Point {
	int x, t;
	bool operator < (const Point& o) const {
		if(x!=o.x) return x<o.x;
		else return t>o.t;
	}
};

ll sqr(ll x) { return x*x; }

const int N = 1e3+1;
int x[N],y[N],r[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin>>T;
	while(T--) {
		int n,m;
		cin>>n>>m;
		int c,k;
		cin>>c>>k;
		for(int i=0;i<c;i++) {
			cin>>x[i]>>y[i]>>r[i];
		}

		int ans = 0;
		for(int i=1;i<=n;i++) {
			vector<Point> p;
			for(int j=0;j<c;j++) {
				if(abs(x[j]-i)>r[j]) continue;
				int d = sqrt(sqr(r[j])-sqr(x[j]-i));
				p.push_back({max(1,y[j]-d),1});
				p.push_back({min(m,y[j]+d),-1});
			}
			sort(p.begin(),p.end());

			int pre = 0;
			int cur = 0;
			for(const Point& it:p) {
				if(it.t > 0) {
					cur += it.t;
					if(cur==k) {
						pre = it.x;
					}
				} else {
					if(cur==k) {
						ans += it.x-pre + 1;
					}
					cur += it.t;
				}
			}
		}
		cout<<ans<<nl;
	}

	return 0;
}
