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
  ll x, y;
};

ll area(const vector<Point>& c, int i, int j, int k) {
  return abs((c[i].x*c[j].y + c[j].x*c[k].y + c[k].x*c[i].y) - (c[i].y*c[j].x + c[j].y*c[k].x + c[k].y*c[i].x));
}

struct Answer {
  ll area;
  int a, b;
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;
  vector<Point> cake(n);
  for (int i = 0; i < n; i++) {
    cin >> cake[i].x >> cake[i].y;
  }

  ll total = 0;
  for (int i = 2; i < n; i++) {
    total += 2*area(cake, 0, i, i-1);
  }
  ll half = total/2;

  Answer ans;
  ll current;
  int first, second;
  first = 0;
  second = 1;
  current = 0;
  for (;;) {
    if (current == half) {
      cout << first+1 << " " << second+1 << nl;
      return 0;
    }
    else if (current < half) {
      second = (second+1)%n;
      current += 2*area(cake, first, second, second-1);
    }
    else {
      first++;
      if (first == n) {
        break;
      }
      current -= 2*area(cake, first, first-1, second);
    }
    if (abs(half-current) < abs(half-ans.area)) {
      ans.a = first;
      ans.b = second;
      ans.area = current;
    }
  }


  cout << ans.a+1 << " " << ans.b+1 << nl;

  return 0;
}
