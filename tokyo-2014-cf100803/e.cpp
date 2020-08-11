#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

const int N = 55;
const int MAXT = 101;

char d[]={'N', 'E', 'S', 'W'};
map<char,int> md{ {'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}}; 
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

bool g[N][N][4];

int n, x00, y00, t;

int ttt[MAXT];
int dir[MAXT];

int mem[N][N][4][11][MAXT];

bool dp(int xt, int yt, int dt, int tl, int it) {
	if (mem[xt][yt][dt][tl][it]!=-1) return mem[xt][yt][dt][tl][it];
	if (tl==0) {
		//cerr << xt << " " << yt << " " << dt << " " << tl << " " << it <<" " << t << endl;
		if (it==t-1) {
			return mem[xt][yt][dt][tl][it] = (dt==dir[it] || (dir[it]!=((2+dt)%4)&& g[xt][yt][dir[it]]));
		}
		else {
			//cerr << "@ "<< xt << " " << yt << " " << dt << " " << tl << " " << it << " " << t <<endl;
			if (dt!=dir[it]) {
				// oh no can't go that way
				if (!g[xt][yt][dir[it]] || (dir[it]==((dt+2)%4))) return mem[xt][yt][dt][tl][it] = 0;
				// go a step in the direction!
				int i = dir[it];
				//cerr << ttt[it+1] << " " << it+1 <<endl;
				return mem[xt][yt][dt][tl][it] = dp(xt+dx[i], yt+dy[i], i, ttt[it+1]-1, it+1);
			}
		  else return mem[xt][yt][dt][tl][it] = dp(xt,yt,dt,ttt[it+1],it+1);
		}
	}
	assert(tl>0);

	bool ans = 0;
	for(int i=0;i<4;i++) {
		if ((i+2)%4==dt) continue;
		// try all cardinal directions
		if (g[xt][yt][i]) {
			// we go in this direction!
			ans|=dp(xt+dx[i], yt+dy[i], i, tl-1, it);
		}
	}

	return mem[xt][yt][dt][tl][it] = ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> x00 >> y00 >> t;
	memset(mem, -1, sizeof mem);
	for(int i=0;i<n;i++) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 == x2) {
			for(int i=min(y1,y2);i<=max(y1,y2);i++) {
				// down (S)
				if (i!=min(y1,y2)) g[x1][i][2]=1;
				// up (N)
				if (i!=max(y1,y2)) g[x1][i][0]=1;
			}
		}
		if (y1 == y2) {
			for(int i=min(x1,x2);i<=max(x1,x2);i++) {
				// left (W)
				if (i!=min(x1,x2)) g[i][y1][3]=1;
				// right (E)
				if (i!=max(x1,x2)) g[i][y1][1]=1;
			}
		}
	}
//	for(int k=0;k<4;k++) { for(int i=0;i<N;i++) { for(int j=0;j<N;j++) { cerr << g[i][j][k]; } cerr <<endl; } cerr <<endl; }
	for(int i=0;i<t;i++) {
		string direction;
		cin >> ttt[i] >> direction;
		dir[i] = md[direction[0]];
	}
	for(int i=0;i<4;i++) {
		dp(x00,y00,i, ttt[0], 0);
	}
	set<pair<int,int>> ans;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			for(int k=0;k<4;k++) {
				if (mem[i][j][k][0][t-1]==1) ans.insert({i, j});
			}
		}
	}
	for(auto &p : ans) {
		cout << p.first << " " << p.second <<endl;
	}

	return 0;
}
