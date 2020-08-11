#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef unsigned long long ull;
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

typedef vector<int> vi;
struct SuffixArray {
	vi t, sa, inv, lcp; int N;
	SuffixArray(const string& s) : N(s.size()) {
		sa.resize(N); t.resize(N+3); lcp.resize(N); inv.resize(N);
		for(int i=0;i<N;i++) t[i]=s[i];
		if(N<3) { if(N==2) { sa[(t[0]>t[1])] = 1; } }
		else build(t,sa,N,128);
		genHeight();
	}
	void build(vi& T, vi& sa, int n, int K) {
		int n0 = (n+2)/3, n1 = (n+1)/3, n2 = n/3, n02 = n0+n2;
		vi r(n02+3), sa12(n02+3), r0(n0), sa0(n0);
		for(int i=0,j=0; i<n+n0-n1; i++) if(i%3) r[j++] = i;
		pass(r, sa12, T, 2, n02, K);
		pass(sa12, r, T, 1, n02, K);
		pass(r, sa12, T, 0, n02, K);
		int name=0, c0=-1, c1=-1, c2=-1;
		for(int i=0;i<n02;i++) {
			if(T[sa12[i]] != c0 || T[sa12[i] + 1] != c1 || T[sa12[i] + 2] != c2) {
				name++;
				c0 = T[sa12[i]]; c1 = T[sa12[i] + 1]; c2 = T[sa12[i] + 2];
			}
			r[(sa12[i]%3 == 1 ? 0 : n0) + sa12[i]/3] = name;
		}
		if(name<n02) {
			build(r, sa12, n02, name);
			for(int i=0; i<n02; i++) { r[sa12[i]] = i+1; }
		} else for(int i=0;i<n02;i++) { sa12[r[i]-1] = i; }
		for(int i=0,j=0; i<n02; i++) {
			if(sa12[i] < n0) r0[j++] = 3*sa12[i];
		}
		pass(r0, sa0, T, 0, n0, K);
		for(int p=0, t=n0-n1, k=0; k<n; k++) {
			int i=sa12[t] < n0 ? (sa12[t]*3 + 1) : ((sa12[t]-n0)*3+2), j=sa0[p];
			if(sa12[t] < n0 ? leq(T[i], r[sa12[t] + n0], 0, T[j], r[j/3], 0)
				: leq(T[i], T[i+1], r[sa12[t]-n0+1], T[j], T[j+1], r[j/3 + n0])) {
				sa[k] = i;
				if(++t == n02) for(k++; p<n0; sa[k++] = sa0[p++]) {}
			} else { sa[k] = j;
				if(++p == n0) {
					for(k++; t<n02; sa[k++] = sa12[t]<n0 ?
						(sa12[t++]*3+1) : ((sa12[t++]-n0)*3+2)) {}
				}
			}
		}
	}
	bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
		return a1<b1 || (a1==b1 && a2<b2) || (a1==b1 && a2==b2 && a3<=b3);
	}
	void pass(vi& a, vi& b, vi& r, int off, int n, int k) { vi c(k+1);
		for(int i=0;i<n;c[r[a[i++] + off]]++);
		for(int i=1;i<=k;i++) c[i]+=c[i-1];
		for(int i=0;i<n;c[r[a[i++] + off]]--);
		for(int i=0;i<n;i++) { b[c[r[a[i]+off]]++] = a[i]; }
	}
	void genHeight() { for(int i=0;i<N;i++) inv[sa[i]] = i;
		for(int i=0,h=0; i<N; i++) if(inv[i]>0) {
			int j=sa[inv[i]-1];
			while(i+h<N && j+h<N && t[i+h]==t[j+h]) h++;
			lcp[inv[i]] = h;
			if(h>0) h--;
		}
	}
};

const int L = 18;
const int N = 1<<L;
string s[N];
int a[N];

int st[2*N];
void build(int len) {
	for(int i=len-1;i>0;i--) {
		st[i] = max(st[2*i], st[2*i+1]);
	}
}
int query(int len, int l, int r) {
	int res = 0;
	for(l+=len,r+=len+1;l<r;l/=2,r/=2) {
		if(l&1) res = max(res, st[l++]);
		if(r&1) res = max(res, st[--r]);
	}
	return res;
}

int rmq[N][L];
void build_rmq(int n, int l) {
	for(int j=1;j<l;j++) {
		for(int i=0;i+(1<<j)<=n;i++) {
			rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
		}
	}
}

int lcp(int i, int j) {
	if(i>j) return lcp(j,i);
	if(i==j) return INF;
	++i;
	int k = 31 - __builtin_clz(j-i+1);
	return min(rmq[i][k], rmq[j-(1<<k)+1][k]);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	freopen("exciting.in", "r", stdin);

	int T;
	cin>>T;
	while(T--) {
		int n;
		cin>>n;
		string all;
		int cid = 0;
		for(int i=0;i<n;i++) {
			cin>>s[i];
			for(int j=s[i].size()-1;j>=0;j--) {
				all.push_back(s[i][j]);
			}
			all.push_back(' ');
		}
		for(int i=0;i<n;i++) {
			for(int j=s[i].size()-1;j>=0;j--) {
				cin>>a[cid+j];
			}
			cid += s[i].size()+1;
			a[cid-1] = 0;
		}
		////cerr<<"got string "<<all<<endl;

		SuffixArray sa(all);
		int m = all.size();
		int lg = (32 - __builtin_clz(m-1));
		int LEN = 1 << lg;
		const vector<int>& idx = sa.inv;
		//const vector<int>& id = sa.sa;
		for(int i=0;i<m;i++) {
			st[LEN+idx[i]] = a[i];
			//cerr<<"put "<<a[i]<<" @ "<<idx[i]<<nl;
			rmq[i][0] = sa.lcp[i];
		}
		build(LEN);
		build_rmq(m,lg);
		//cerr<<nl;

		function<pii(int,int)> find = [&](int M, int len) {
			//cerr<<"find "<<M<<" "<<len<<" -> "<<idx[M]<<nl;
			M = idx[M];
			int left, right;
			{
				int l = 0;
				int r = M;
				while(l<r) {
					int mid = (l+r)/2;
					if(lcp(mid,M) < len) l = mid+1;
					else r = mid;
				}
				left = l;
			}
			{
				int l = M;
				int r = m-1;
				while(l<r) {
					int mid = (l+r+1)/2;
					if(lcp(mid,M) < len) r = mid-1;
					else l = mid;
				}
				right = r;
			}
			//cerr<<"get "<<left<<" "<<right<<nl;
			return pii(left,right);
		};

		ull ans = 0;
		cid = 0;
		for(int i=0;i<n;i++) {
			int sz = s[i].size();
			for(int j=0;j<sz;j++) {
				////cerr<<"solving "<<i<<" "<<j<<nl;
				// solve
				pii pop = find(cid+j, sz-j+1);
				pii mat = find(cid+j, sz-j);
				ans = max(ans, (ull)(pop.second-pop.first+1)
						* query(LEN,mat.first,mat.second) * (sz-j));
				//cerr<<"mat range "<<mat.first<<" "<<mat.second<<nl;
				//cerr<<" -> "<<pop.second-pop.first+1<<" * "<<query(LEN,mat.first,mat.second)<<" * "<<sz-j<<nl;
			}
			cid += sz+1;
			//cerr<<nl;
		}
		cout<<ans<<nl;
		////cerr<<endl;
	}

	return 0;
}
