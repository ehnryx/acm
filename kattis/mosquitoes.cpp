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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin>>T;
	while(T--) {
		int n; ld d;
		cin>>n>>d;
		vector<pt> p;
		for(int i=0;i<n;i++) {
			ld x,y;
			cin>>x>>y;
			p.push_back(pt(x,y));
		}

		int ans = 0;
		for(int i=0;i<n;i++) {
			{
				pt c = p[i];
				int cnt = 0;
				for(int k=0;k<n;k++) {
					cnt += (abs(c-p[k])<d/2+EPS);
				}
				ans = max(ans,cnt);
			}
			for(int j=0;j<i;j++) {
				if(abs(p[i]-p[j])>d+EPS) continue;
				if(abs(p[i]-p[j])<EPS) continue;
				pt m = (p[i]+p[j])/(ld)2;
				ld h = sqrt(d*d - norm(p[i]-p[j])) / 2;
				pt dir = (p[i]-p[j])/abs(p[i]-p[j]) * pt(0,1);
				{
					pt c = m + dir*h;
					int cnt = 0;
					for(int k=0;k<n;k++) {
						cnt += (abs(c-p[k])<d/2+EPS);
					}
					ans = max(ans,cnt);
				}
				{
					pt c = m - dir*h;
					int cnt = 0;
					for(int k=0;k<n;k++) {
						cnt += (abs(c-p[k])<d/2+EPS);
					}
					ans = max(ans,cnt);
				}
			}
		}
		assert(ans>0);
		cout<<ans<<nl;
	}

	return 0;
}
