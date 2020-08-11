#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <random>
#include <chrono>
#include <utility>
using namespace std;

typedef long long ll;

const char nl = '\n';

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	os<<"[ ";
	for(T it:v) { os<<it<<", "; }
	return os<<"]";
}

template<class T, class U>
pair<T,U> operator - (const pair<T,U>& a, const pair<T,U>& b) {
	return make_pair(a.first-b.first, a.second-b.second);
}

const int N = 1e5+1;
const int S = 300;
const int M = N/S+1;
int a[N],A[N];
ll pre[S+1], suf[S+1];
ll sval[M][N];

ll ans[N];
struct Query {
	int l, r, s, e, i;
	bool operator < (const Query& o) const {
		if(l/S != o.l/S) return l/S < o.l/S;
		return ((l/S)%2==0 ? r < o.r : r > o.r);
	}
};

ll bit[N];
int cnt[N];
void update(int x, int v, int c) {
	for(;x<N;x+=x&-x) {
		bit[x] += v;
		cnt[x] += c;
	}
}
pair<int,ll> pquery(int x) {
	int tot = 0;
	ll res = 0;
	for(;x>0;x-=x&-x) {
		res += bit[x];
		tot += cnt[x];
	}
	return make_pair(tot,res);
}
pair<int,ll> query(int l, int r) {
	return pquery(r) - pquery(l-1);
}

int insert(int i) {
	update(A[i], a[i], 1);
	return a[i];
};

int remove(int i) {
	update(A[i], -a[i], -1);
	return a[i];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout<<fixed<<setprecision(13);

	int n,m;
	cin>>n>>m;
	map<int,int> rmp;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		rmp[a[i]];
	}
	int rid=0;
	for(auto& it:rmp) {
		it.second = ++rid;
	}
	for(int i=1;i<=n;i++) {
		A[i] = rmp[a[i]];
	}

	for(int i=1;i<=n;i+=S) {
		int id = i/S;
		assert(id<M);
		vector<int> b;
		for(int j=0;j<S&&i+j<=n;j++) {
			b.push_back(a[i+j]);
		}
		sort(b.begin(),b.end());
		int sz = b.size();
		for(int j=0;j<sz;j++) {
			pre[j+1] = b[j]+pre[j];
			suf[j+1] = b[sz-1-j]+suf[j];
		}
		for(int j=1;j<=n;j++) {
			int left = lower_bound(b.begin(),b.end(),a[j]) - b.begin();
			int right = sz - left;
			ll cur = (ll)(left-right)*a[j] - pre[left] + suf[right];
			sval[id][j] = sval[id][j-1] + cur;
		}
	}

	vector<Query> q;
	for(int i=0;i<m;i++) {
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		int l = (a-2)/S+1;
		int r = (b)/S-1;
		if(l>r) {
			q.push_back({c,d,a,b,i});
		} else {
			int left = l*S+1;
			int right = r*S+S;
			if(a<left) q.push_back({c,d,a,left-1,i});
			if(b>right) q.push_back({c,d,right+1,b,i});
			for(int j=l;j<=r;j++) {
				ans[i] += sval[j][d] - sval[j][c-1];
			}
		}
	}
	sort(q.begin(),q.end());

	int left = 1;
	int right = 0;
	ll sum = 0;
	for(const Query& it:q) {
		while(left>it.l) sum += insert(--left);
		while(right<it.r) sum += insert(++right);
		while(left<it.l) sum -= remove(left++);
		while(right>it.r) sum -= remove(right--);
		for(int i=it.s;i<=it.e;i++) {
			int v = A[i];
			int left;
			ll sumleft;
			tie(left,sumleft) = query(1, v);
			int right = it.r-it.l+1 - left;
			ll sumright = sum - sumleft;
			ll cur = (ll)(left-right)*a[i] - sumleft + sumright;
			ans[it.i] += cur;
		}
	}

	for(int i=0;i<m;i++) {
		cout<<ans[i]<<nl;
	}

	return 0;
}
