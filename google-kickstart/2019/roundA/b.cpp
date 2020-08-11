#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Point {
	int x, y;
};

vector<int> dx = {0,0,-1,1};
vector<int> dy = {1,-1,0,0};

const int N = 250;
string grid[N];
int dist[N][N];

bool valid(int d, int r, int c) {
	int minx, maxx, miny, maxy;
	minx = miny = INF;
	maxx = maxy = -INF;
	for (int i=0; i<r; i++) {
		for (int j=0; j<c; j++) {
			if (dist[i][j] > d) {
				minx = min(minx, i+j);
				maxx = max(maxx, i+j);
				miny = min(miny, i-j);
				maxy = max(maxy, i-j);
			}
		}
	}
	if (minx == INF) return true;
	int sx = (maxx-minx);
	int sy = (maxy-miny);
	int side = max(sx,sy);
	if ((side+1)/2 > d) return false;
	if ((side+1)/2 < d) return true;
	if (sx != sy) return true;
	if (sx%2 == 1) return true;
	int mx = (minx+maxx)/2;
	int my = (miny+maxy)/2;
	return (mx+my)%2 == 0;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int T;
	cin >> T;
	for (int tt=1; tt<=T; tt++) {
		cout << "Case #" << tt << ": ";

		int r, c;
		cin >> r >> c;
		for (int i=0; i<r; i++) {
			cin >> grid[i];
		}

		memset(dist, INF, sizeof dist);
		queue<Point> bfs;
		for (int i=0; i<r; i++) {
			for (int j=0; j<c; j++) {
				if (grid[i][j] == '1') {
					bfs.push({i,j});
					dist[i][j] = 0;
				}
			}
		}

		while (!bfs.empty()) {
			Point cur = bfs.front();
			bfs.pop();
			for (int i=0; i<4; i++) {
				int nx = cur.x+dx[i];
				int ny = cur.y+dy[i];
				if (0<=nx && nx<r && 0<=ny && ny<c && dist[nx][ny]==INF) {
					dist[nx][ny] = dist[cur.x][cur.y]+1;
					bfs.push({nx,ny});
				}
			}
		}

		int left = 0;
		int right = r+c+1;
		while (left < right) {
			int mid = (left+right)/2;
			if (valid(mid,r,c)) {
				right = mid;
			} else {
				left = mid+1;
			}
		}
		cout << left << nl;

	}

	return 0;
}
