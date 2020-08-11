#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const ll INF = 0x3f3f3f3f;

const int MAXN = 3e5+10;

ll ans=0;

int offsetx, offsety;
int minx, maxx, miny, maxy;

struct dsu {
	vector<map<int,int>> sets;
	vector<int> par;
	dsu() = default;
	dsu(int n) {
		par.resize(n, -1);
		sets.resize(n);
	}
	void insert(int a, int b, int i) {
		sets[a][b]=i;
	}
	int parent(int a) { return par[a] < 0 ? a : (par[a] = parent(par[a])); }
} d[2], rooks;

int x[MAXN], y[MAXN];

void rookmerge(int a, int b) {
	int x = rooks.parent(a), y = rooks.parent(b);
	if (x==y) return;
	ans+=(ll)rooks.par[x]*rooks.par[y];
	rooks.par[x] += rooks.par[y];
	rooks.par[y] = x;
}

void update(map<int,int> &seta, int id) {
	if (!seta.empty()) {
		pair<int,int> p = *seta.begin();
		seta.erase(seta.begin());
		p.first = max(p.first, !id? minx:miny);
		seta.insert(p);
		auto it = prev(seta.end());
		p = *it;
		seta.erase(it);
		p.first = min(p.first, !id? maxx:maxy);
		seta.insert(p);
	}
}

// id = 0 is x
void merge(int a, int b, int id) {
	//cerr << "merging coord " << a << " " << b << " " << (id? "y":"x") <<endl;
	// merge seta into setb
	auto &seta = d[id].sets[a];
	auto &setb = d[id].sets[b];
	if (seta.size() > setb.size()) seta.swap(setb);
	// update endpoints of seta and setb
	update(seta, !id);
	update(setb, !id);
	for(auto &p: seta) {
		int col = p.first;
		int rep = p.second;
		if (setb.count(col)) {
			// merge reps!!!!!!!!!!!!
			rookmerge(rep, setb[col]);
			auto &column = d[!id].sets[col];
			update(column, id);
			column.erase(column.find(a));
		}
		else {
			setb[col] = rep;
		}
	}
	seta.clear();
	d[id].par[a] = b;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) {
		int n, m; cin >> n >> m;
		offsetx = offsety = 0;
		minx=1, maxx= n;
		miny=1, maxy= n;
		ans = 0;
		d[0] = d[1] = rooks = dsu(n+2);
		for (int i = 1; i <= n; i++) {
			cin >> x[i] >> y[i];
			d[0].insert(x[i], y[i], i);
			d[1].insert(y[i], x[i], i);
		}


		for(int iii=0;iii<m;iii++) {
			char c; cin >> c;
			if (c == '!') {
				cout << ans << nl;
			} else if (c == '?') {
				int k; cin >> k;
				int xx = d[0].parent(x[k]), yy = d[1].parent(y[k]);
				cout << xx - offsetx << " " << yy - offsety << nl;
			} else if (c == 'L') { // y offset increases 
				int val;
				cin >> val;
				int target = offsety+val;
				while(miny < target+1 && miny<maxy) {
					merge(miny, miny+1, 1);
					miny++;
				}
				offsety = min(maxy-1, target);
			} else if (c == 'R') {
				int val;
				cin >> val;
				int target = offsety-val;
				while (maxy > target+n && maxy>miny) { // move and merge bounding box
					merge(maxy, maxy-1, 1);
					maxy--;
				}
				offsety = max(-n+miny, target);
			} else if (c == 'U') {
				int val;
				cin >> val;
				int target = offsetx+val;
				while (minx < target+1 && minx<maxx) { // move and merge bounding box
					merge(minx, minx+1, 0);
					minx++;
				}
				offsetx = min(maxx-1, target);
			} else if (c == 'D') {
				int val;
				cin >> val;
				int target = offsetx-val;
				while (maxx > target+n && maxx>minx) { // move and merge bounding box
					merge(maxx, maxx-1, 0);
					maxx--;
				}
				offsetx = max(-n+minx, target);
			}
//			if (c!='?' && c!='!') cerr << iii << " query " << offsetx << " "<< offsety << " "<< maxx << " " << minx << " " << maxy << " " << miny << endl;
			/*
			cerr << " coordinates " <<endl;
			for(int k=1;k<=n;k++) {
				int xx = d[0].parent(x[k]), yy = d[1].parent(y[k]);
				cerr << xx - offsetx << " " << yy - offsety << nl;
			}
			cerr << " end coordinates " <<endl;
			*/
		}
	}
	return 0;
}
