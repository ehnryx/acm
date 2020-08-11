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

struct Node {
	int pre,i,rev,d;
	bool operator < (const Node& o) const {
		return d > o.d;
	}
};

const int N = 1e3+1;
int dist[N][N],ang[N][N];
vector<int> adj[N];
int D[N][N][2];

bool in_range(int in, int out, int l, int r) {
	int op = (in+180)%360;
	int turn = (out-op+360)%360;
	if(turn==180) return l==180 || r==180;
	if(turn<180) return turn<=l;
	else return 360-turn<=r;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,d,l,r;
	cin>>n>>d>>l>>r;
	for(int i=1;i<=n;i++) {
		int m;
		cin>>m;
		for(int j=0;j<m;j++) {
			int o,t,a;
			cin>>o>>t>>a;
			adj[i].push_back(o);
			dist[i][o] = t;
			ang[i][o] = a;
		}
	}
	if(d==1) {
		cout<<0<<nl;
		return 0;
	}

	memset(D,INF,sizeof D);
	priority_queue<Node> dijk;
	for(int v:adj[1]) {
		dijk.push({1,v,0,dist[1][v]});
		D[1][v][0] = dist[1][v];
	}

	while(!dijk.empty()) {
		Node cur = dijk.top();
		dijk.pop();
		if(cur.d > D[cur.pre][cur.i][cur.rev]) continue;
		if(cur.i==1 && cur.rev) {
			cout<<cur.d<<nl;
			return 0;
		}
		int in = ang[cur.i][cur.pre];
		for(int j:adj[cur.i]) {
			int out = ang[cur.i][j];
			int nd = cur.d+dist[cur.i][j];
			if(in_range(in,out,l,r) && nd < D[cur.i][j][cur.rev|(cur.i==d)]) {
				D[cur.i][j][cur.rev|(cur.i==d)] = nd;
				dijk.push({cur.i,j,cur.rev|(cur.i==d),nd});
			}
		}
	}
	cout<<"impossible"<<nl;

	return 0;
}
