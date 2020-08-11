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

struct Pair {
	int i,j,d;
	bool operator < (const Pair& o) const {
		if(d!=o.d) return d < o.d;
		if(i!=o.i) return i < o.i;
		else return j < o.j;
	}
};

int sqr(int x) { return x*x; }

const int N = 1e3+1;
int a[3][N],b[3][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n[3];
	for(int t=0;t<3;t++) {
		cin>>n[t];
	}

	for(int t=0;t<3;t++) {
		for(int i=0;i<n[t];i++) {
			cin>>a[t][i]>>b[t][i];
		}
	}

	ld ans = 0;
	for(int t=1;t<3;t++) {
		vector<bool> done(n[0]), used(n[t]);
		vector<Pair> p;
		for(int i=0;i<n[0];i++) {
			for(int j=0;j<n[t];j++) {
				p.push_back({i, j, sqr(a[0][i]-a[t][j]) + sqr(b[0][i]-b[t][j])});
			}
		}
		sort(p.begin(),p.end());
		for(const Pair& it:p) {
			if(done[it.i]||used[it.j]) continue;
			done[it.i] = true;
			used[it.j] = true;
			ans += sqrt(it.d);
		}
	}
	cout<<ans<<nl;

	return 0;
}
