#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-11L;
random_device _rd; mt19937 rng(_rd());

constexpr ld PI = acos(-1.l);

struct pt {
  ld x, y, z;
  pt operator+(const pt& o) const {
    return { x + o.x, y + o.y, z + o.z, };
  }
  pt operator/(auto c) const {
    return { x / c, y / c, z / c, };
  }
};

pt dot(const pt& a, const pt& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

ld abs(const pt& v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

ld read_angle(string s) {
  istringstream in(s);
  int h, m; char d;
  in >> h >> m >> d;
  ld angle = (h * 60 + m) / 60.l / 180.l * PI;
  return d == 'N' or d == 'W' ? angle : -angle;
}

pt read_point() {
  string a, b;
  cin >> a >> b;
  ld latitude = read_angle(a);
  ld longitude = read_angle(b);
  return {
    cos(latitude) * cos(longitude),
    cos(latitude) * sin(longitude),
    sin(latitude),
  };
}

void print_point(pt v) {
  int latitude = round(asin(v.z) * 60.l / PI * 180.l);
  char lat_dir = latitude < 0 ? 'S' : 'N';
  latitude = abs(latitude);
  cout << latitude / 60 << ',' << latitude % 60 << lat_dir << nl;
}

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  pt S = read_point();
  pt T = read_point();
  if(abs(S + T) < EPS) {
    return void(cout << "undefined" << nl);
  }
  pt mid = (S + T) / 2;
  if(dot(mid, {0, 0, 1}) < EPS) {
    return print_point(S.z > T.z ? S : T);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
