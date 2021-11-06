#include <bits/stdc++.h>
using namespace std;

//#define FILENAME sadcactus

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct p3d {
  int x, y, z;
  p3d operator + (const p3d& o) const {
    return { x + o.x, y + o.y, z + o.z };
  }
  p3d operator - (const p3d& o) const {
    return { x - o.x, y - o.y, z - o.z };
  }
  p3d operator - () const {
    return { -x, -y, -z };
  }
  bool operator < (const p3d& o) const {
    return tie(x, y, z) < tie(o.x, o.y, o.z);
  }
  int dist() const { return abs(x) + abs(y) + abs(z); }
  int dist(const p3d& o) const {
    return abs(x - o.x) + abs(y - o.y) + abs(z - o.z);
  }
  friend ostream& operator << (ostream& os, const p3d& v) {
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  }
  int get_pos_signed(const p3d& dir) const {
    //assert(dir.dist() == 1);
    if(dir.x) {
      return x * dir.x;
    } else if(dir.y) {
      return y * dir.y;
    } else if(dir.z) {
      return z * dir.z;
    } else {
      assert(false);
    }
  }
  int get_sign() const {
    return x + y + z;
  }
};

struct segment {
  p3d a, b; // a -> b
  int s, t; // start at time s, period t
};

struct box {
  int a, b, c, x, y, z; // ehh
  pair<int, int> get_range_signed(const p3d& dir) const {
    //assert(dir.dist() == 1);
    if(dir.x) {
      int l = a * dir.x;
      int r = x * dir.x;
      return pair(min(l, r), max(l, r));
    } else if(dir.y) {
      int l = b * dir.y;
      int r = y * dir.y;
      return pair(min(l, r), max(l, r));
    } else if(dir.z) {
      int l = c * dir.z;
      int r = z * dir.z;
      return pair(min(l, r), max(l, r));
    } else {
      assert(false); // cursed
    }
  }
  bool intersects_point(const p3d& line, const p3d& dir) const {
    //assert(dir.dist() == 1);
    if(dir.x) {
      return intersects_point_2d(line.y, line.z, b, y, c, z);
    } else if(dir.y) {
      return intersects_point_2d(line.x, line.z, a, x, c, z);
    } else if(dir.z) {
      return intersects_point_2d(line.x, line.y, a, x, b, y);
    } else {
      assert(false);
    }
  }
  bool intersects_point_2d(int i, int j, int u, int v, int w, int t) const {
    return u <= i && i <= v && w <= j && j <= t;
  }
  int get_point_signed(const p3d& dir) const {
    //assert(dir.dist() == 1);
    if(dir.x) {
      return min(a*dir.x, x*dir.x);
    } else if(dir.y) {
      return min(b*dir.y, y*dir.y);
    } else if(dir.z) {
      return min(c*dir.z, z*dir.z);
    } else {
      assert(false);
    }
  }
  bool contains_point(const p3d& v) const {
    if(v.x == a || v.x == x) {
      return intersects_point_2d(v.y, v.z, b, y, c, z);
    } else if(v.y == b || v.y == y) {
      return intersects_point_2d(v.x, v.z, a, x, c, z);
    } else if(v.z == c || v.z == z) {
      return intersects_point_2d(v.x, v.y, a, x, b, y);
    } else {
      return false;
    }
  }
  bool contains_line(const p3d& s, const p3d& dir) const {
    //assert(dir.dist() == 1);
    if(dir.x) {
      return ((y == s.y || b == s.y) && c <= s.z && s.z <= z) || ((z == s.z || c == s.z) && b <= s.y && s.y <= y);
    } else if(dir.y) {
      return ((z == s.z || c == s.z) && a <= s.x && s.x <= x) || ((x == s.x || a == s.x) && c <= s.z && s.z <= z);
    } else if(dir.z) {
      return ((x == s.x || a == s.x) && b <= s.y && s.y <= y) || ((y == s.y || b == s.y) && a <= s.x && s.x <= x);
    } else {
      assert(false);
    }
  }
};

int sgn(char c) {
  return c == '+' ? +1 : -1;
}

bool in_range(int v, int a, int b) {
  return min(a, b) <= v && v <= max(a, b);
}

bool on_segment(const p3d& v, const p3d& a, const p3d& b) {
  return in_range(v.x, a.x, b.x) && in_range(v.y, a.y, b.y) && in_range(v.z, a.z, b.z);
}

struct seg2d {
  int a, b, x, y; // a,b -> x,y.
  int s, t; // start at time s, period t
};

struct seg1d {
  int a, x; // a -> x.
  int s; // start at time s, (period t is unnecessary)
};

/**
 * Description: Extended Euclidean algorithm: finds $x$ and $y$ such that $ax + by = d = \gcd(a, b)$.
 *
 * Computing $a^{-1} \bmod{m}$: \texttt{if(egcd(a,m,x,y)==1) return (x+m)\%m; else ERROR}
 * Time: O(\log(\min(a, b)))
 */

ll egcd(ll a, ll b, ll& x, ll &y) { if (!b) {x=1; y=0; return a;}
  // to ensure d>=0: x=sgn(a);y=0;return abs(a);       ^^^^^^^^
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d; }

// Assuming a != 0, find smallest y >= 0 such that ax+by=c (if possible)
bool canon_egcd(ll a, ll b, ll c, ll& x, ll& y) {
  ll d = egcd(a, b, x, y), z = abs(a/d); if (c%d) return false;
  y = (y*(c/d)%z + z)%z, x = (c - b*y)/a; return true; }

ll solve(int a, int b, int c, int s, int t, int du) {
  //cerr << "solving for " << a << " " << b << " " << c << nl;
  //assert(a > 0 && b < 0);
  if(c >= 0) {
    ll x, y;
    if(canon_egcd(a, b, c, x, y)) {
      //cerr << "get " << x << " " << y << nl;
      //assert(x >= 0 && y >= 0);
      return s + x * t + du;
    }
  } else {
    ll x, y;
    if(canon_egcd(-b, -a, -c, x, y)) {
      //cerr << "get " << x << " " << y << nl;
      //assert(x >= 0 && y >= 0);
      return s + y * t + du; // uhhh
    }
  }
  return INFLL;
}

ll get_intersect(seg1d u, seg1d v) {
  //cerr << "1d intersect" << nl;
  if((u.a < u.x) == (v.a < v.x)) {
    return INFLL;
  }

  if(u.a > u.x) {
    swap(u, v);
  }

  u.x -= 1;
  v.x += 1;

  int l = max(u.a, v.x);
  int r = min(u.x, v.a);
  if(l > r) {
    return INFLL;
  }

  int tu = u.s + l - u.a;
  int tv = v.s + v.a - r;
  int len = r - l;
  if(abs(tu - tv) > r - l) {
    return INFLL;
  }

  // intersection found!
  len -= abs(tu - tv);
  return max(tu, tv) + len / 2;
}

ll get_intersect(seg2d u, seg2d v) {
  if(u.a == u.x && v.a == v.x) {
    if(u.a == v.a) {
      return get_intersect(seg1d{u.b, u.y, u.s}, seg1d{v.b, v.y, v.s});
    } else {
      return INFLL;
    }
  } else if(u.b == u.y && v.b == v.y) {
    if(u.b == v.b) {
      return get_intersect(seg1d{u.a, u.x, u.s}, seg1d{v.a, v.x, v.s});
    } else {
      return INFLL;
    }
  }
  //cerr << "2d intersect" << nl;
  if(u.b == u.y) {
    swap(u.a, u.b);
    swap(u.x, u.y);
    swap(v.a, v.b);
    swap(v.x, v.y);
  }
  // u.a == u.x, v.b == v.y
  if(min(v.a, v.x) <= u.x && u.x <= max(v.a, v.x) && min(u.b, u.y) <= v.y && v.y <= max(u.b, u.y)) {
    int du = abs(v.y - u.b);
    int dv = abs(u.x - v.a);
    return solve(u.t, -v.t, v.s - u.s + dv - du, u.s, u.t, du);
  } else {
    return INFLL;
  }
}

ll get_intersect(const segment& u, const segment& v) {
  if(u.a.x == u.b.x && v.a.x == v.b.x && u.a.x == v.a.x) {
    return get_intersect(
        seg2d{u.a.y, u.a.z, u.b.y, u.b.z, u.s, u.t},
        seg2d{v.a.y, v.a.z, v.b.y, v.b.z, v.s, v.t});
  } else if(u.a.y == u.b.y && v.a.y == v.b.y && u.a.y == v.a.y) {
    return get_intersect(
        seg2d{u.a.z, u.a.x, u.b.z, u.b.x, u.s, u.t},
        seg2d{v.a.z, v.a.x, v.b.z, v.b.x, v.s, v.t});
  } else if(u.a.z == u.b.z && v.a.z == v.b.z && u.a.z == v.a.z) {
    return get_intersect(
        seg2d{u.a.x, u.a.y, u.b.x, u.b.y, u.s, u.t},
        seg2d{v.a.x, v.a.y, v.b.x, v.b.y, v.s, v.t});
  } else {
    return INFLL;
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, k;
  cin >> n >> k;

  vector<box> boxes;
  for(int i=0; i<n; i++) {
    int a, b, c, x, y, z;
    cin >> a >> b >> c >> x >> y >> z;
    boxes.push_back(box{2*a, 2*b, 2*c, 2*x, 2*y, 2*z});
  }

  auto find_the_end = [&](p3d pos, const p3d& dir, const p3d& up) {
    //assert(((pos.x ^ pos.y ^ pos.z) & 1) == 0);
    //assert(dir.dist() == 1);
    //assert(up.dist() == 1);
    p3d wall_line = pos + up; // intersect with boxes
    int v_signed = pos.get_pos_signed(dir);
    int wall = INF;
    vector<pair<int, int>> ext;
    //cerr << "contains line " << pos << " " << dir << " ??? " << nl;
    for(const box& bx : boxes) {
      if(bx.contains_line(pos, dir)) {
        ext.push_back(bx.get_range_signed(dir));
      }
      if(bx.intersects_point(wall_line, dir)) {
        int wall_hit = bx.get_point_signed(dir);
        //assert(((wall_hit ^ v_signed) & 1)== 1);
        if(wall_hit > v_signed) {
          wall = min(wall, wall_hit);
        }
      }
    }
    sort(begin(ext), end(ext));
    for(auto [l, r] : ext) {
      //cerr << "l, r: " << l << " " << r << nl;
      if(l <= v_signed + 1) {
        v_signed = max(v_signed, r);
      }
    }

    v_signed = min(v_signed, wall); // uhhhhh

    int v = v_signed * dir.get_sign();
    if(dir.x) {
      pos.x = v;
    } else if(dir.y) {
      pos.y = v;
    } else if(dir.z) {
      pos.z = v;
    } else {
      assert(false);
    }
    //cerr << "RETURNING " << pos << nl;
    return pos;
  };

  auto do_the_turn = [&](const p3d& pos, const p3d& dir, const p3d& up) {
    //cerr << "TURN " << pos << nl;
    //assert(((pos.x ^ pos.y ^ pos.z) & 1) == 1);
    //assert(dir.dist() == 1);
    //assert(up.dist() == 1);
    p3d turn = pos + up;
    for(const box& bx : boxes) {
      if(bx.contains_point(turn)) {
        // go up
        return tuple(turn, up, -dir);
      }
    }
    // go down
    turn = pos - up;
    return tuple(turn, -up, dir);
  };

  vector<vector<segment>> paths;

  set<tuple<int, int, int>> init_have;
  for(int i=0; i<k; i++) {
    int a, b, c; string d1, d2;
    cin >> a >> b >> c >> d1 >> d2;
    p3d center{2*a + 1, 2*b + 1, 2*c + 1};
    p3d normal;
    if (d1[0] == 'x') {
      normal = p3d{sgn(d1[1]), 0, 0};
    } else if(d1[0] == 'y') {
      normal = p3d{0, sgn(d1[1]), 0};
    } else if(d1[0] == 'z') {
      normal = p3d{0, 0, sgn(d1[1])};
    } else {
      assert(false);
    }
    p3d pos = center + normal;
    if (init_have.insert(tuple(pos.x, pos.y, pos.z)).second == false) {
      cout << 0 << nl;
      return 0; // oops
    }

    //cerr << "DO ROBOT " << pos << endl;

    p3d dir;
    if(d2[0] == 'x') {
      dir = p3d{sgn(d2[1]), 0, 0};
    } else if(d2[0] == 'y') {
      dir = p3d{0, sgn(d2[1]), 0};
    } else if(d2[0] == 'z') {
      dir = p3d{0, 0, sgn(d2[1])};
    } else {
      assert(false);
    }

    vector<segment> segments;

    p3d start = pos; // save the start
    p3d last = find_the_end(pos, dir, normal);

    int start_ts = pos.dist(last);
    segments.push_back(segment{pos, last, 0, 0});

    tie(pos, dir, normal) = do_the_turn(last, dir, normal);
    int ts = start_ts;
    while(true) {
      //cerr << "AT " << pos << " " << dir << " " << normal << endl;
      ts += 1;
      last = find_the_end(pos, dir, normal);
      // pos -> last is a line segment

      segments.push_back(segment{pos, last, ts, 0}); // period = ???

      ts += pos.dist(last);
      if (on_segment(start, pos, last)) {
        break; // uh oh
      }

      tie(pos, dir, normal) = do_the_turn(last, dir, normal);
    }

    int period = ts - start_ts;
    for(auto& seg : segments) {
      seg.t = period;
      //cerr << " -> " << seg.a << " " << seg.b << " " << seg.s << " " << seg.t << nl;
    }
    paths.emplace_back(move(segments)); // help
  }

  ll ans = INFLL;
  for(int i=0; i<k; i++) {
    for(int j=0; j<i; j++) {
      for(const segment& ii : paths[i]) {
        for(const segment& jj : paths[j]) {
          ans = min(ans, get_intersect(ii, jj));
        }
      }
    }
  }

  if(ans == INFLL) {
    cout << "ok" << nl;
  } else {
    cout << ans / 2 << nl;
    //cerr << "2ans: " << ans << nl;
  }

  return 0;
}
