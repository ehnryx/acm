#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
const ll MOD = 1e9+7;
const int INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}

struct LineSweep {
  struct Point {
    int time;
    int pos;
    int index;
    bool open;
    Point(int time, int pos, int index, bool open) {
      this->time = time;
      this->pos = pos;
      this->index = index;
      this->open = open;
    }
    bool operator < (const Point& other) const {
      return this->pos < other.pos;
    }
  };
  vector<Point> points;
  int heard[100001];

  void clear() {
    points.clear();
    memset(heard, 0, sizeof(heard));
  }
  void add(int time, int pos, int index, bool open) {
    points.push_back(Point(time, pos, index, open));
  }
  int sweep() {
    sort(points.begin(), points.end());
    int ans = 0; // number of monkeys on chair
    set<pair<int,int>> jokes; // -time, joke index
    pair<int,int> last; // last joke heard by interval
    int prev = 0; // previous point
    for (Point p: points) {
      // get last joke
      if (jokes.empty()) last.second = 0;
      else last = *jokes.begin();
      // check if last joke is heard ast least twice
      if (heard[last.second] >= 2) 
        ans += p.pos - prev;
      #ifdef DEBUG
      cout << "visit {time,pos,index,open}: " << p.time << " " << p.pos << " " << p.index << " " << p.open << endl;
      cout << "last joke: " << last.second << " heard " << heard[last.second] << " times" << endl;
      cout << "prev: " << prev << endl;
      cout << "CURRENT ANS: " << ans << endl;
      #endif
      // add or remove current point
      if (p.open) {
        // add
        heard[p.index]++;
        jokes.insert(pair<int,int>(-p.time, p.index));
      }
      else {
        // remove
        heard[p.index]--;
        jokes.erase(pair<int,int>(-p.time, p.index));
      }
      // update prev
      prev = p.pos;
    }
    return ans;
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  LineSweep ubc;
  int n, m;
  int x, index, vol;
  int T;
  read(T); //cin >> T;
  while (T--) {
    ubc.clear();
    read(n); read(m); //cin >> n >> m;
    for (int i = 0; i < m; i++) {
      read(x); read(index); read(vol); //cin >> x >> index >> vol;
      // add(time, pos, start)
      ubc.add(i+1, max(0, x-vol-1), index, true);
      ubc.add(i+1, min(n, x+vol), index, false);
    }
    cout << ubc.sweep() << endl;
  }

  return 0;
}
