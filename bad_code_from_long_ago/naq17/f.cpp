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
  Point(int a, int b) {
    x = a;
    y = b;
  }
  void operator += (const Point& other) {
    x += other.x;
    y += other.y;
  }
  void rotate(int d) {
    if (x != 0) {
      y = x*d;
      x = 0;
    } else {
      x = -y*d;
      y = 0;
    }
  }
};

bool go(int x, int y, vector<string> s) {
  Point dir = Point(0,1);
  Point pos = Point(0,0);
  for (string c : s) {
    if (c == "Forward")
      pos += dir;
    else if (c == "Left") {
      dir.rotate(1);
    } else if (c == "Right") {
      dir.rotate(-1);
    }
  }
  return (pos.x == x && pos.y == y);
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int x, y, n;
  cin >> x >> y;
  cin >> n;
  vector<string> com(n);
  for (int i = 0; i < n; i++) {
    cin >> com[i];
  }
  for (int i = 0; i < n; i++) {
    string memo = com[i];
    com[i] = "Forward";
    if (go(x, y, com)) {
      cout << i+1 << " " << com[i] << nl;
      break;
    }
    com[i] = "Left";
    if (go(x, y, com)) {
      cout << i+1 << " " << com[i] << nl;
      break;
    }
    com[i] = "Right";
    if (go(x, y, com)) {
      cout << i+1 << " " << com[i] << nl;
      break;
    }
    com[i] = memo;
  }

  return 0;
}
