#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
const char nl = '\n';

const int N = 250000 + 1;
const int M = 2e4 + 1;
int sx[N], sy[N], px[N], py[N];
int wa[N], wb[N], wx[N], wy[N];
unordered_map<int,unordered_map<int,int>> grid;
vector<int> prods[N];
vector<pair<int,int>> ans[N];

ll sqr(int x) {
	return (ll)x*x;
}

ll dist(int a, int b, int x, int y) {
	return sqr(a-x) + sqr(b-y);
}

ll cp(int a, int b, int x, int y) {
	return (ll)a*y - (ll)b*x;
}

int sgn(ll x) {
	return x<0 ? -1 : (x>0 ? 1 : 0);
}

bool seg_x_seg(int i, int j, int k) {
	int s1 = sgn(cp(sx[i]-px[j],sy[i]-py[j], sx[i]-wx[k],sy[i]-wy[k]));
	int s2 = sgn(cp(sx[i]-px[j],sy[i]-py[j], sx[i]-wa[k],sy[i]-wb[k]));
	int s3 = sgn(cp(wa[k]-wx[k],wb[k]-wy[k], wa[k]-sx[i],wb[k]-sy[i]));
	int s4 = sgn(cp(wa[k]-wx[k],wb[k]-wy[k], wa[k]-px[j],wb[k]-py[j]));
	if(!s1 && !s2 && !s3) {
		pair<int,int> a(sx[i],sy[i]);
		pair<int,int> b(px[j],py[j]);
		pair<int,int> c(wa[k],wb[k]);
		pair<int,int> d(wx[k],wy[k]);
		if(b<a) swap(a,b);
		if(d<c) swap(c,d);
		return !(b<c || d<a);
	} else {
		return s1*s2 <= 0 && s3*s4 <= 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int T;
	cin >> T;
	while(T--) {
		int s, r, w, p;
		cin >> s >> r >> w >> p;
		grid.clear();
		for(int i=0; i<s; i++) {
			cin >> sx[i] >> sy[i];
			grid[sx[i]][sy[i]] = i;
			prods[i].clear();
		}
		for(int i=0; i<w; i++) {
			cin >> wa[i] >> wb[i] >> wx[i] >> wy[i];
		}
		for(int i=0; i<p; i++) {
			cin >> px[i] >> py[i];
			ans[i].clear();
		}

		for(int i=0; i<p; i++) {
			for(int x=-r; x<=r; x++) {
				for(int y=-r; y<=r; y++) {
					if(grid[px[i]+x].count(py[i]+y)) {
						prods[grid[px[i]+x][py[i]+y]].push_back(i);
					}
				}
			}
		}

		for(int i=0; i<s; i++) {
			for(int j : prods[i]) {
				int cnt = 0;
				for(int k=0; k<w; k++) {
					if(seg_x_seg(i,j,k)) {
						cnt++;
					}
				}
				if(dist(sx[i],sy[i], px[j],py[j]) <= sqr(r-cnt)) {
					ans[j].push_back(make_pair(sx[i], sy[i]));
				}
			}
		}

		for(int i=0; i<p; i++) {
			sort(ans[i].begin(), ans[i].end());
			cout << ans[i].size();
			for(auto [x,y] : ans[i]) {
				cout << " (" << x << "," << y << ")";
			}
			cout << nl;
		}
	}
}
