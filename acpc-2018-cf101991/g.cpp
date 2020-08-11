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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

struct Range {
	int x,l,r,i;
	bool operator < (const Range& o) const {
		if(x!=o.x) return x > o.x;
		else return r > o.r;
	}
};
ostream& operator << (ostream& os, const Range& v) {
	return os<<"{ "<<v.x<<", "<<v.l<<", "<<v.r<<" }";
}

const int M = 1e6+1;
const int N = 1<<17;
int seen[M];
vector<Range> vals[M];
ll ans[N];
int d[N];

int gst[2*N];
void build_g(int L) {
	for(int i=L-1;i>0;i--) {
		gst[i] = __gcd(gst[2*i],gst[2*i+1]);
	}
}
int query_gcd(int l, int r, int v, int g, int i, int s, int e, int& x) {
	if(r<s||e<l) return v;
	int ng = __gcd(v,gst[i]);
	if(l <= s && (!ng || ng>=g)) return ng;
	if(s==e) {
		x = s;
		return ng;
	}
	int m = (s+e)/2;
	int left = query_gcd(l,r,v,g,2*i,s,m,x);
	if(left && left < g) return left;
	return query_gcd(l,r,left,g,2*i+1,m+1,e,x);
}

ll sum[N<<3], z[N<<3], len[N<<3];

void build(int L) {
	for(int i=1;i<2*L;i++) {
		sum[i] = 0;
		z[i] = 0;
	}
	for(int i=L-1;i>0;i--) {
		len[i] = len[2*i] + len[2*i+1];
	}
}

void push(int i) {
	if(z[i]) {
		sum[2*i] += z[i]*len[2*i];
		sum[2*i+1] += z[i]*len[2*i+1];
		z[2*i] += z[i];
		z[2*i+1] += z[i];
		z[i] = 0;
	}
}

ll query(int l, int r, int i, int s, int e) {
	if(r<s||e<l) return 0;
	if(l<=s&&e<=r) return sum[i];
	push(i);
	int m = (s+e)/2;
	return query(l,r,2*i,s,m) + query(l,r,2*i+1,m+1,e);
}

void update(int l, int r, int i, int s, int e) {
	if(r<s||e<l) return;
	if(l<=s&&e<=r) {
		sum[i] += len[i];
		z[i] += 1;
		return;
	}
	push(i);
	int m = (s+e)/2;
	update(l,r,2*i,s,m);
	update(l,r,2*i+1,m+1,e);
	sum[i] = sum[2*i] + sum[2*i+1];
}

void solve(vector<Range>& v) {
	////cerr<<"solve with ranges "<<nl;
	sort(v.begin(),v.end());
	map<int,int> cmp;
	for(const Range& it:v) {
		cmp[it.x]; cmp[it.l]; cmp[it.r];
		cmp[it.l+1]; cmp[it.r+1];
		////cerr<<it<<nl;
	}
	int cid = 0;
	for(auto& it:cmp) {
		it.second = cid++;
	}
	assert(cid);
	int L = 1 << (32 - __builtin_clz(cid));
	assert(L<=4*N);
	for(auto it=cmp.begin();next(it)!=cmp.end();it++) {
		len[L+it->second] = next(it)->first - it->first;
	}
	build(L);
	for(Range& it:v) {
		if(it.r!=-1) {
			update(cmp[it.l], cmp[it.r], 1, 0, L-1);
		} else {
			ans[it.i] = query(cmp[it.x], cmp[it.l], 1, 0, L-1);
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	freopen("gcdrng.in", "r", stdin);

	int T;
	//cin>>T;
	read(T);
	while(T--) {
		int n,m;
		//cin>>n>>m;
		read(n);read(m);
		int L = 1 << (32 - __builtin_clz(n));
		assert(L<=N);
		for(int i=0;i<n;i++) {
			//cin>>gst[L+i];
			read(gst[L+i]);
		}
		gst[L+n] = 1;
		build_g(L);

		for(int i=0;i<m;i++) {
			int l,r;
			//cin>>l>>r>>d[i];
			read(l);read(r);read(d[i]);
			vals[d[i]].push_back({l-1,r-1,-1,i});
			seen[d[i]] = true;
		}

		for(int i=0;i<n;i++) {
			int g = gst[L+i];
			int j = i;
			//cerr<<"start @ "<<i<<" w/ "<<g<<nl;
			while(g>1) {
				int r = 0;
				int ng = query_gcd(i,n,0,g,1,0,L-1,r);
				assert(ng && ng<g);
				//cerr<<r<<" -> "<<ng<<nl;
				//cerr<<"got range "<<j<<" "<<r-1<<" w/ "<<g<<nl;
				if(seen[g]) vals[g].push_back({i,j,r-1});
				g = ng;
				j = r;
			}
			//cerr<<"got range "<<j<<" "<<n<<" w/ "<<1<<nl;
			if(seen[1]) vals[1].push_back({i,j,n});
			//cerr<<nl;
		}

		for(int i=0;i<m;i++) {
			if(seen[d[i]]) {
				////cerr<<"@ "<<d[i]<<nl;
				solve(vals[d[i]]);
				vals[d[i]].clear();
				seen[d[i]] = false;
			}
			cout<<ans[i]<<nl;
		}
	}

	return 0;
}
