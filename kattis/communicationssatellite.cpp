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

struct Edge {
	int a,b; ld c;
	bool operator < (const Edge& o) const {
		return c < o.c;
	}
};

int sqr(int x) { return x*x; }

const int N = 2e3+1;
int root[N];
int find(int i) {
	if(root[i]==-1) return i;
	return root[i] = find(root[i]);
}
int link(int i, int j) {
	i=find(i); j=find(j);
	if(i==j) return false;
	root[i] = j;
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	memset(root,-1,sizeof root);

	int n;
	cin>>n;
	int x[n],y[n],r[n];
	vector<Edge> edges;
	for(int i=0;i<n;i++) {
		cin>>x[i]>>y[i]>>r[i];
		for(int j=0;j<i;j++) {
			ld d = sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
			edges.push_back({i,j,d-r[i]-r[j]});
		}
	}
	sort(edges.begin(),edges.end());

	ld ans = 0;
	for(const Edge& e:edges) {
		if(link(e.a,e.b)) {
			ans += e.c;
		}
	}
	cout<<ans<<nl;

	return 0;
}
