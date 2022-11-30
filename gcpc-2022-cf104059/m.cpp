#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

//#undef assert
//#define assert(X) do { if(not(X)) for(;;); } while(false)

enum {
  VERTICAL = 0,
  HORIZONTAL = 1,
};

struct State {
  int x, l, r, d;
  State(int _x, int _l, int _r, int _d): x(_x), l(_l), r(_r), d(_d) {
    assert(l < r);
  }
  bool operator<(const State& o) const {
    return tie(d, x, l, r) < tie(o.d, o.x, o.l, o.r);
  }
  friend ostream& operator<<(ostream& os, const State& v) {
    return os << "(" << v.x << ":" << v.l << "," << v.r << ":" << v.d << ")";
  }
};

int base_x;
struct Line {
  int m, b;
  mutable int s;
  Line(int _m, int _b, int _s): m(_m), b(_b), s(_s) {}
  bool operator<(const Line& o) const {
    return eval(base_x) < o.eval(base_x);
  }
  int eval(int x) const {
    return m*x + b;
  }
};

Line get_line(pair<int, int> u, pair<int, int> v) {
  int m = (u.second - v.second) / (u.first - v.first);
  return Line(m, u.second - m*u.first, min(u.first, v.first));
}

State get_state(pair<int, int> u, pair<int, int> v) {
  if(u.first == v.first) {
    return State(u.first, min(u.second, v.second), max(u.second, v.second), VERTICAL);
  } else {
    return State(u.second, min(u.first, v.first), max(u.first, v.first), HORIZONTAL);
  }
}

State get_state(const Line& line, int r, const auto& func) {
  return get_state(
      func(line.s, line.eval(line.s)),
      func(r, line.eval(r)));
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
  }

  ll perimeter = 0;
  for(int i=n-1, j=0; j<n; i=j++) {
    perimeter += abs(p[i].first - p[j].first) + abs(p[i].second - p[j].second);
  }

  auto build = [&](const auto& func, const auto& invf) {
    //cerr << "BUILD" << nl;
    vector<pair<int, int>> rp;
    map<int, vector<int>> ev;
    for(auto [x, y] : p) {
      rp.emplace_back(func(x, y));
      ev[rp.back().first].push_back(size(rp) - 1);
      //cerr << x << " " << y << " --> " << rp.back().first << " " << rp.back().second << nl;
    }

    map<State, State> adj;
    int perim = 0;

    set<Line> segs;
    for(const auto& [cur, v] : ev) {
      //cerr << "AT " << cur << nl;
      base_x = cur - 1;
      for(int i : v) {
        int a = (i+1 < size(rp) ? i+1 : 0);
        int b = (i-1 >= 0 ? i-1 : size(rp) - 1);
        Line to = get_line(rp[b], rp[i]);
        Line from = get_line(rp[i], rp[a]);
        auto it_to = segs.find(to);
        auto it_from = segs.find(from);

        if(it_to != end(segs) and it_from != end(segs) and to.m == 1) {
          //assert(from.m == -1); // ok
          State sto = get_state(*it_to, cur, invf);
          State sfrom = get_state(*it_from, cur, invf);
          //cerr << "ADD " << sto << " -- " << sfrom << nl;
          adj.emplace(sto, sfrom);
          adj.emplace(sfrom, sto);
          assert(sto.r - sto.l == sfrom.r - sfrom.l);
          perim += sto.r - sto.l;
        } else {
          if(it_to != end(segs) and it_to->s != cur and next(it_to) != end(segs)) {
            //assert(next(it_to) != end(segs)); // ok
            auto jt = next(it_to);
            State sto = get_state(*it_to, cur, invf);
            State sjt = get_state(*jt, cur, invf);
            //cerr << "ADD " << sto << " -- " << sjt << nl;
            adj.emplace(sto, sjt);
            adj.emplace(sjt, sto);
            assert(sto.r - sto.l == sjt.r - sjt.l);
            perim += sto.r - sto.l;
            jt->s = cur;
          }
          if(it_from != end(segs) and it_from->s != cur and it_from != begin(segs)) {
            //assert(it_from != begin(segs)); // ok
            auto jt = prev(it_from);
            State sfrom = get_state(*it_from, cur, invf);
            State sjt = get_state(*jt, cur, invf);
            //cerr << "ADD " << sfrom << " -- " << sjt << nl;
            adj.emplace(sfrom, sjt);
            adj.emplace(sjt, sfrom);
            assert(sfrom.r - sfrom.l == sjt.r - sjt.l);
            perim += sfrom.r - sfrom.l;
            jt->s = cur;
          }
        }

        if(it_to != end(segs)) {
          segs.erase(it_to);
        }
        if(it_from != end(segs)) {
          segs.erase(it_from);
        }
      }

      base_x = cur + 1;
      for(int i : v) {
        int a = (i+1 < size(rp) ? i+1 : 0);
        int b = (i-1 >= 0 ? i-1 : size(rp) - 1);
        Line to = get_line(rp[b], rp[i]);
        Line from = get_line(rp[i], rp[a]);
        auto it_to = (rp[b].first > rp[i].first ? segs.insert(to).first : end(segs));
        auto it_from = (rp[a].first > rp[i].first ? segs.insert(from).first : end(segs));

        if(it_to != end(segs) and it_from != end(segs) and to.m == -1 and
            next(it_from) != end(segs) and it_to != begin(segs)) {
          auto upper = next(it_from);
          auto lower = prev(it_to);
          //cerr << "upper, lower s " << upper->s << " " << lower->s << nl;
          assert((upper->s == cur) == (lower->s == cur));
          if(upper->s != cur) {
            State supper = get_state(*upper, cur, invf);
            State slower = get_state(*lower, cur, invf);
            //cerr << "ADD2 " << supper << " -- " << slower << nl;
            adj.emplace(supper, slower);
            adj.emplace(slower, supper);
            assert(supper.r - supper.l == slower.r - slower.l);
            perim += supper.r - supper.l;
            upper->s = cur;
            lower->s = cur;
          }
        }
      }
    }

    //cerr << perim << " " << perimeter << nl;
    assert(perim*2 == perimeter);

    return adj;
  };

  vector adj = {
    build(
        [](int x, int y) { return pair(x-y, x+y); },
        [](int x, int y) { return pair((x+y)/2, (y-x)/2); }),
    build(
        [](int x, int y) { return pair(x+y, y-x); },
        [](int x, int y) { return pair((x-y)/2, (x+y)/2); }),
  };

  auto run_step = [&adj](int x, int y, State cur, int dir) {
    //cerr << "RUN STEP " << x << " " << y << " @ " << cur << nl;
    cur = adj[dir].at(cur);
    int slope = (dir ? -1 : 1);
    int b = y - slope*x;
    if(cur.d == VERTICAL) {
      x = cur.x;
      y = slope*x + b;
      //cerr << "GET " << x << " " << y << " @ " << cur << nl;
      //assert(cur.l < y and y < cur.r);
    } else {
      y = cur.x;
      x = slope*y - b*slope;
      //cerr << "GET " << x << " " << y << " @ " << cur << nl;
      //assert(cur.l < x and x < cur.r);
    }
    cur.l = cur.r = (cur.d == VERTICAL ? y : x);
    auto it = adj[dir^1].lower_bound(cur);
    assert(it != begin(adj[dir^1]));
    auto nxt = prev(it)->first;
    //assert(cur.d == nxt.d);
    //assert(cur.x == nxt.x);
    //if(cur.d == VERTICAL) assert(cur.l < y and y < cur.r);
    //else assert(cur.l < x and x < cur.r);
    return tuple(x, y, nxt);
  };

  int sx, sy;
  cin >> sx >> sy;

  auto start = [&] {
    for(int i=n-1, j=0; j<n; i=j++) {
      if(min(p[i].first, p[j].first) <= sx and sx <= max(p[i].first, p[j].first) and
          min(p[i].second, p[j].second) <= sy and sy <= max(p[i].second, p[j].second)) {
        State res = get_state(p[i], p[j]);
        res.l = res.r = (res.d == VERTICAL ? sy : sx);
        //assert(res.x == (res.d == VERTICAL ? sx : sy));
        return res;
      }
    }
    while(clock() < 2*CLOCKS_PER_SEC);
    assert(false);
  }();

  auto it = adj[0].lower_bound(start);
  assert(it != begin(adj[0]));
  auto cur = prev(it)->first;
  assert(cur.d == start.d);
  assert(cur.x == start.x);
  if(start.d == VERTICAL) assert(cur.l < sy and sy < cur.r);
  else assert(cur.l < sx and sx < cur.r);

  for(int dir=0; m--; dir^=1) {
    tie(sx, sy, cur) = run_step(sx, sy, cur, dir);
    cout << sx << " " << sy << nl;
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
