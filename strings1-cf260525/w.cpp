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
const int MOD = 51123987;

const int N = 1<<21;
int a[2*N], b[2*N], st[2*N];

ll length(int s, int e) {
	return e-s+1;
}

ll sum(int s, int e) {
	ll d = length(s,e);
	return (d*s + d*(d-1)/2) % MOD;
}

int mod(int x) {
	return (x<INF ? x : x%MOD);
}

void fix(int i) {
	a[i] = mod(a[i]);
	b[i] = mod(b[i]);
	st[i] = mod(st[i]);
}

void push(int i, int s, int e) {
	if(a[i] || b[i]) {
		int m = (s+e)/2;
		a[2*i] += a[i];
		b[2*i] += a[i];
		st[2*i] += (sum(s,m)*a[i] + length(s,m)*b[i]) % MOD;
		a[2*i+1] += a[i];
		b[2*i+1] += a[i];
		st[2*i+1] += (sum(m+1,e)*a[i] + length(m+1,e)*b[i]) % MOD;
		fix(2*i);
		fix(2*i+1);
		a[i] = b[i] = 0;
	}
}

void pull(int i) {
	st[i] = mod(st[2*i] + st[2*i+1]);
}

void insert(int l, int r, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l) return;
	if(l<=s && e<=r) {
		a[i] += 1;
		b[i] += -l+1;
		cerr<<"insert range " << s<<" "<<e<<" -> "<< sum(s,e) + length(s,e)*(-l+1) << nl;
		st[i] += (sum(s,e) + length(s,e)*(-l+1)) % MOD;
		fix(i);
		return;
	}
	push(i,s,e);
	int m = (s+e)/2;
	insert(l,r,2*i,s,m);
	insert(l,r,2*i+1,m+1,e);
	pull(i);
}

void insert2(int l, int r, int v, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l) return;
	if(l<=s && e<=r) {
		b[i] += v;
		st[i] += length(s,e)*v % MOD;
		fix(i);
		return;
	}
	push(i,s,e);
	int m = (s+e)/2;
	insert2(l,r,v,2*i,s,m);
	insert2(l,r,v,2*i+1,m+1,e);
	pull(i);
}

int query(int l, int r, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l) return 0;
	if(l<=s && e<=r) {
		return st[i];
	}
	push(i,s,e);
	int m = (s+e)/2;
	return mod(query(l,r,2*i,s,m) + query(l,r,2*i+1,m+1,e));
}

namespace Manacher {
	int len[2*N]; // length of odd palin centred at s[i] is len[2*i]
	void find_pals(const string& s) { // even palin btwn s[i],s[i+1]: len[2*i+1]
		len[0] = 1, len[1] = 0; int d;
		for (int i = 1; i+1 < 2*(int)s.length(); i += d) { int& p = len[i];
			int left = (i - p - 1)/2, right = (i + p + 1)/2;
			while (0 <= left && right < (int)s.length() && s[left] == s[right])
				--left, ++right, p += 2;
			for (d = 1; len[i-d] < p-d; ++d) len[i+d] = len[i-d];
			//len[i+d] = max((int)((i+d)%2==0), p-d); } }
			len[i+d] = p-d; } }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	string s;
	cin >> s;
	Manacher::find_pals(s);
	assert(Manacher::len[2*n-1] == 0);

	for(int i=0;i<2*n-1;i++) {
		cerr << "manacher " << i << " -> " << Manacher::len[i] << nl;
	}

	int ans = 0;
	for(int i=2*n-2; i>=0; i--) {
		if(Manacher::len[i] == 0) continue;
		int clen = (Manacher::len[i]+1) / 2;
		assert(clen > 0);
		cerr<<"do " << i << " w/ " << clen << nl;
		int mr = (i+1)/2;
		int ml = i/2;
		ans = mod(ans + query(mr, mr + clen - 1));
		cerr << "@ "<<ml << " "<< mr << " -> query " << mr << " " << mr + clen - 1 << " get " << ans <<nl;
		insert(ml - clen + 1, ml);
		insert2(ml+1, N-1, clen);
		cerr<<" insert " << ml-clen+1 << " " << ml << " and " << ml+1 << " " << N-1 << " w/ " << ml << nl;
		cerr << nl;
		ans = mod(ans + (ll)clen*(clen-1)/2 % MOD);
		cerr<<" add "<<clen <<" choose 2 " << ans << nl;
	}
	cout << ans % MOD << nl;

	return 0;
}
