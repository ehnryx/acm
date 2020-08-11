#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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

const int N = 1e5+1;
const int M = 3e5+1;
const int T = 240;
int cnt[M+N];
vector<int> vals[T];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;

	for(int i=0;i<n;i++) {
		int a;
		cin>>a;
		cnt[a]++;
		for(int j=2;j<T;j++) {
			if(a%j == 0) {
				vals[j].push_back(a);
			}
		}
	}

	ll ans = 0;
	for(int i=0;i<m;i++) {
		int v;
		cin>>v;
		if(v<T) {
			for(int j:vals[v]) {
				int cur = cnt[j];
				ans += cur;
				cnt[j+1] += cur;
				cnt[j] = 0;
				if(cur>0 && cnt[j+1] == cur) {
					for(int k=2;k<T;k++) {
						if((j+1)%k == 0) {
							vals[k].push_back(j+1);
						}
					}
				}
			}
			vals[v].clear();
		} else {
			for(int j=v;j<M+N;j+=v) {
				int cur = cnt[j];
				ans += cur;
				cnt[j+1] += cur;
				cnt[j] = 0;
				if(cur>0 && cnt[j+1] == cur) {
					for(int k=2;k<T;k++) {
						if((j+1)%k == 0) {
							vals[k].push_back(j+1);
						}
					}
				}
			}
		}
	}
	cout<<ans<<nl;

	return 0;
}
