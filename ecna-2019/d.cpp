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
const int INF = 0x3f3f3f3f;
const ld BIG = 1e5;
const ld EPS = 1e-11;
const ld TPS = 1e-7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
int sgn(const ld& x) { return abs(x)<EPS ? 0 : (x<0 ? -1 : 1); }
bool seg_x_seg(pt a, pt b, pt c, pt d) {
	ld za = abs(b-a); ld zb = abs(c-d); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
	int s1=sgn(cp(a-b,c-b)*za); int s2=sgn(cp(a-b,d-b)*za);
	int s3=sgn(cp(c-d,a-d)*zb); int s4=sgn(cp(c-d,b-d)*zb);
	if(!s1 && !s2 && !s3) return false;
	else return s1*s2 <= 0 && s3*s4 <= 0;
}
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a,d-c) / cp(b-a,d-c) * (b-a);
}

pt reflect(const pt& a, const pt& b, const pt& d) {
	pt ab = a-b;
	ab /= abs(ab);
	return ab*ab/d;
}

struct Ball {
	pt v, dir; ld t; int pid, eid;
	bool operator < (const Ball& o) const {
		return t > o.t;
	}
};

const int N = 20+4;
vector<pt> p[N];
int val[N],sz[N];
vector<Ball> batch[N];

void find(priority_queue<Ball>& nxt, int n, pt v, pt dir, ld t) {
	//cerr<<"find nxt for "<<v<<" "<<dir<<nl;
	pt hit = v+dir*BIG;
	int id = -1;
	int eid = -1;
	for(int i=0;i<n;i++) {
		if(val[i]==0) continue;
		for(int j=sz[i]-1,k=0; k<sz[i]; j=k++) {
			////cerr<<"try intersecting "<<v<<" "<<hit<<" w/ "<<p[i][j]<<" "<<p[i][k]<<nl;
			if(seg_x_seg(v,hit,p[i][j],p[i][k])) {
				pt it = line_inter(v,v+dir,p[i][j],p[i][k]);
				if(abs(it-v) > EPS) {
					hit = it;
					id = i;
					eid = j;
				}
			}
		}
	}
	if(id!=-1) {
		nxt.push({hit,dir,abs(hit-v)+t,id,eid});
		//cerr<<"hit "<<hit<<" @ "<<id<<" "<<eid << "pre: "<< v<<nl;
	}
}

void solve(priority_queue<Ball>& nxt, int n, pt v, pt dir) {
	while(!nxt.empty()) {
		Ball topBall = nxt.top();
		batch[topBall.pid].push_back(topBall);
		nxt.pop();
		//cerr<<"@ time "<<topBall.t<<nl;
		while(!nxt.empty() && nxt.top().t < topBall.t+TPS) {
			batch[nxt.top().pid].push_back(nxt.top());
			nxt.pop();
		}
		//getchar();
		for(int pid=0;pid<n;pid++) {
			val[pid] -= min(val[pid], (int)batch[pid].size());
			for(Ball& it:batch[pid]) {
				if(val[pid] > 0) {
					it.dir = reflect(p[pid][it.eid],p[pid][(it.eid+1)%sz[pid]],it.dir);
				}
				find(nxt, n, it.v, it.dir, it.t);
			}
			batch[pid].clear();
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(16);

	int w,h,n,m; ld l; int r,s;
	cin>>w>>h>>n>>m>>l>>r>>s;
	for(int i=0;i<m;i++) {
		cin>>sz[i];
		for(int j=0;j<sz[i];j++) {
			ld x,y;
			cin>>x>>y;
			p[i].push_back(pt(x,y));
		}
		cin>>val[i];
	}
	val[m] = val[m+1] = val[m+2] = INF;
	sz[m] = sz[m+1] = sz[m+2] = 2;
	p[m] = { pt(0,0), pt(0,h) };
	p[m+1] = { pt(0,h), pt(w,h) };
	p[m+2] = { pt(w,h), pt(w,0) };

	pt dir(r,s);
	dir /= abs(dir);
	pt start(l,0);
	priority_queue<Ball> nxt;
	for(int i=0;i<n;i++) {
		nxt.push({start,dir,(ld)i,m+3});
	}
	solve(nxt,m+4,start,dir);

	for(int i=0;i<m;i++) {
		cout<<val[i]<<" ";
	}
	cout<<nl;

	return 0;
}
