#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

struct Segment {
	int x, a, b, v;
	bool operator < (const Segment& o) const {
		if (x != o.x) return x < o.x;
		return v > o.v;
	}
};

const int N = 1<<18;
int segt[2*N];
void insert(int x, int v) {
	for (x+=N; x>0; x/=2) {
		segt[x] += v;
	}
}
int query(int l, int r) {
	int res = 0;
	for (l+=N,r+=N+1; l<r; l/=2,r/=2) {
		if (l&1) res += segt[l++];
		if (r&1) res += segt[--r];
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	map<int,int> remap;
	vector<Segment> segs;
	for (int i=0; i<n; i++) {
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		segs.push_back({x1,y1,y2,1});
		segs.push_back({x2,y1,y2,-1});
		remap[y1];
		remap[y2];
	}
	sort(segs.begin(), segs.end());

	int cmp=0;
	for (auto& it : remap) {
		it.second = cmp++;
		//cerr << it.first << " -> " << it.second << nl;
	}

	for (const Segment& it : segs) {
		int cur = query(remap[it.a], remap[it.b]);
		if ((it.v==1 && cur>0) || (it.v==-1 && cur>2)) {
			cout << 1 << nl;
			return 0;
		}
		insert(remap[it.a], it.v);
		insert(remap[it.b], it.v);
	}
	cout << 0 << nl;

	return 0;
}
