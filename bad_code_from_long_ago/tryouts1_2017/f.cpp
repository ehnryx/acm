#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Point {
  int x, y;
  Point(){}
  Point(int r, int c) {
    x = r;
    y = c;
  }
  bool operator < (const Point& other) const {
    if (x == other.x) return y < other.y;
    else return x < other.x;
  }
};

bool notin(Point p, int r[], int c[]) {
  if (r[1] <= p.x && p.x <= r[2] && c[1] <= p.y && p.y <= c[2])
    return false;
  if (r[3] <= p.x && p.x <= r[4] && c[3] <= p.y && p.y <= c[4])
    return false;
  return true;
}

void bfs(map<Point,int>& sad, int n, int m, int r[], int c[]) {
  struct Node {
    Point pt;
    int dist;
    Node(){}
    Node(Point p, int d) {
      pt = p;
      dist = d;
    }
  };

  queue<Node> next;
  next.push(Node(Point(r[0], c[0]), 0));
  while (!next.empty()) {
    Node curr = next.front();
    next.pop();
    if (!sad.count(curr.pt)) {
      sad[curr.pt] = curr.dist;
      if (curr.pt.x + 1 <= n && notin(Point(curr.pt.x+1, curr.pt.y), r, c))
        next.push(Node(Point(curr.pt.x+1, curr.pt.y), curr.dist+1));
      if (curr.pt.x - 1 > 0 && notin(Point(curr.pt.x-1, curr.pt.y), r, c))
        next.push(Node(Point(curr.pt.x-1, curr.pt.y), curr.dist+1));
      if (curr.pt.y + 1 <= m && notin(Point(curr.pt.x, curr.pt.y+1), r, c))
        next.push(Node(Point(curr.pt.x, curr.pt.y+1), curr.dist+1));
      if (curr.pt.y - 1 > 0 && notin(Point(curr.pt.x, curr.pt.y-1), r, c))
        next.push(Node(Point(curr.pt.x, curr.pt.y-1), curr.dist+1));
    }
  }
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  map<Point,int> sad;

  int ans = 0;
  int n, m;
  int r[5], c[5];
  int D, N, x, y;
  cin >> n >> m >> r[0] >> c[0] >> D >> N;
  cin >> r[1] >> c[1] >> r[2] >> c[2];
  cin >> r[3] >> c[3] >> r[4] >> c[4];
  bfs(sad, n, m, r, c);
  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    if (sad.count(Point(x,y)))
      if (sad[Point(x,y)] <= D)
        ans++;
  }
  cout << ans << nl;

  return 0;
}
