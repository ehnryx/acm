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

const int N = 106+1;
int ans[N];

int qs = 0;
void solve(int l, int r, const vector<pii>& a) {
	if(l>r || a.empty()) return;

	assert(++qs <= 1500);

	int m = (l+r)/2;
	cout<<"Q "<<m<<endl;

	int cost;
	cin>>cost;
	vector<pii> left, right;
	for(const pii& it:a) {
		if(it.first < cost) left.push_back(it);
		else if(it.first > cost) right.push_back(it);
		if(it.first >= cost) ans[it.second] = m;
	}
	solve(l, m-1, left);
	solve(m+1, r, right);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	vector<pii> a(m);
	for(int i=0;i<m;i++) {
		cin>>a[i].first;
		a[i].second = i;
	}
	solve(1,n,a);

	cout<<"A";
	for(int i=0;i<m;i++) {
		cout<<" "<<ans[i];
	}
	cout<<endl;

	return 0;
}
