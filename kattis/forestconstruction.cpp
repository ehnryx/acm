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

const int N = 100;
int dsu[N];
int find(int i) {
	if(dsu[i]==-1) return i;
	return dsu[i]=find(dsu[i]);
}
void link(int i, int j) {
	if(find(i)!=find(j)) {
		dsu[find(i)]=find(j);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	memset(dsu,-1,sizeof dsu);

	int n;
	cin>>n;
	if(n==0) {
		cout<<"POSSIBLE"<<nl;
		return 0;
	}

	int d[n];
	for(int i=0;i<n;i++) {
		cin>>d[i];
	}

	vector<pii> ans;
	for(;;) {
		vector<pii> vals;
		for(int i=0;i<n;i++) {
			vals.push_back(pii(d[i],i));
		}
		sort(vals.begin(),vals.end(),greater<pii>());
		int deg, id;
		tie(deg,id) = vals[0];
		if(deg==0) break;
		for(int i=1;i<n;i++) {
			int j = vals[i].second;
			if(d[id]>0 && d[j]>0 && find(id)!=find(j)) {
				d[id]--;
				d[j]--;
				link(id,j);
				ans.push_back(pii(id,j));
			}
		}
		if(d[id]!=0) {
			cout<<"IMPOSSIBLE"<<nl;
			return 0;
		}
	}

	cout<<"POSSIBLE"<<nl;
	for(const pii& it:ans) {
		cout<<it.first+1<<" "<<it.second+1<<nl;
	}

	return 0;
}
