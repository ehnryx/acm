// 15 minutes

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const char nl = '\n';

const int N = 1<<20;
ll sum[2*N], z[2*N], za[2*N];

ll arith(int a, int b) {
	int d = b-a;
	return (ll)a*(d+1) + (ll)d*(d+1)/2;
}

void push(int i, int s, int m, int e) {
	if(z[i]) {
		sum[2*i] += z[i]/2;
		sum[2*i+1] += z[i]/2;
		z[2*i] += z[i]/2;
		z[2*i+1] += z[i]/2;
		z[i] = 0;
	}
	if(za[i]) {
		sum[2*i] += za[i] * arith(s, m);
		sum[2*i+1] += za[i] * arith(m+1, e);
		za[2*i] += za[i];
		za[2*i+1] += za[i];
		za[i] = 0;
	}
}

void pull(int i) {
	sum[i] = sum[2*i] + sum[2*i+1];
}

void insert(int l, int r, ll a, ll v, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l) return;
	if(l<=s && e<=r) {
		za[i] += a;
		sum[i] += a * arith(s, e);
		z[i] += v * (e-s+1);
		sum[i] += v * (e-s+1);
		return;
	}
	int m = (s+e)/2;
	push(i, s, m, e);
	insert(l, r, a, v, 2*i, s, m);
	insert(l, r, a, v, 2*i+1, m+1, e);
	pull(i);
}

ll query(int l, int r, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l) return 0;
	if(l<=s && e<=r) {
		return sum[i];
	}
	int m = (s+e)/2;
	push(i, s, m, e);
	return query(l, r, 2*i, s, m) + query(l, r, 2*i+1, m+1, e);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int t;
		cin >> t;
		if(t == 1) {
			int l, r, v;
			cin >> l >> r >> v;
			insert(l, r, v, v*(-l+1));
		} else {
			int l, r;
			cin >> l >> r;
			cout << query(l, r) << nl;
		}
	}

	return 0;
}
