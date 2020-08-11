#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 1 << 17;

int segt[2*N], lazy[2*N];
void push(int i) {
	if (lazy[i] != 0) { 
		segt[2*i] += lazy[i];
		segt[2*i+1] += lazy[i];
		lazy[2*i] += lazy[i];
		lazy[2*i+1] += lazy[i];
		lazy[i] = 0;
	}
}
void pull(int i) {
	segt[i] = min(segt[2*i], segt[2*i+1]);
}
void dec(int x, int y, int i=1, int l=0, int r=N-1) {
	if (y<l || r<x) return;
	if (x<=l && r<=y) {
		segt[i]--;
		lazy[i]--;
		return;
	}
	int m = (l+r)/2;
	push(i);
	dec(x, y, 2*i, l, m);
	dec(x, y, 2*i+1, m+1, r);
	pull(i);
}
int query(int x, int y, int i=1, int l=0, int r=N-1) {
	if (y<l || r<x) return INF;
	if (x <= l && r <= y) return segt[i];
	int m = (l+r)/2;
	push(i);
	return min(query(x, y, 2*i, l, m), query(x, y, 2*i+1, m+1, r));
}

struct val {
	int a, b, i;
	bool operator<(const val& o) const {
		return tie(a, b, i) < tie(o.a, o.b, o.i);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n; cin >> n;
	vector<val> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i].a;
	}
	for (int i = 0; i < n; i++) {
		cin >> v[i].b;
	}
	sort(v.rbegin(), v.rend());
	for (int i = 0; i < n; i++) {
		v[i].i = i;
	}
	sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
		return tie(a.b, a.i) > tie(b.b, b.i);
	});
	for (int i = 0; i < N; i++) {
		segt[N+i] = (i+1)/2;
	}
	for (int i = N-1; i >= 1; i--) {
		pull(i);
	}
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		if (query(v[i].i, n) >= 1) {
			//cerr << v[i].b << nl;
			ans += v[i].b;
			dec(v[i].i, n);
		}
	}
	cout << ans << nl;

	return 0;
}
