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
typedef int ld;
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

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld area(const vector<pt>& v) {
	ld s = 0; int n = v.size();
	for(int i=n-1,j=0; j<n; i=j++) { s += cp(v[i],v[j]); }
	return s;
}

struct Node {
	ld a; int i,j,k;
	bool operator < (const Node& o) const {
		if(a != o.a) return a > o.a;
		else return j > o.j;
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	vector<pt> p;
	for(int i=0;i<=n;i++) {
		int x,y;
		cin>>x>>y;
		p.push_back(pt(x,y));
	}

	priority_queue<Node> nxt;
	set<int> alive;
	alive.insert(0);
	alive.insert(n);
	for(int i=1;i<n;i++) {
		nxt.push(Node{abs(area({p[i-1],p[i],p[i+1]})),i-1,i,i+1});
		alive.insert(i);
	}

	vector<int> remove;
	while(!nxt.empty()) {
		int i = nxt.top().i;
		int j = nxt.top().j;
		int k = nxt.top().k;
		nxt.pop();
		if(!alive.count(i) || !alive.count(j) || !alive.count(k)) {
			continue;
		}
		alive.erase(j);
		remove.push_back(j);
		if(i>0) {
			auto it = prev(alive.find(i));
			nxt.push(Node{abs(area({p[*it],p[i],p[k]})),*it,i,k});
		}
		if(k<n) {
			auto it=next(alive.find(k));
			nxt.push(Node{abs(area({p[i],p[k],p[*it]})),i,k,*it});
		}
	}

	for(int i=0;i<n-m;i++) {
		cout<<remove[i]<<nl;
	}

	return 0;
}
