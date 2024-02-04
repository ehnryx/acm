%:include "geometry/point.h"
%:include "geometry/lines.h"
using pt = point<int>;

%:include "ds/fenwick_tree.h"

//%:include "utility/output.h"

struct Segment {
  pt u, v;
  pt vec() const { return v - u; }
};

enum {
  QUERY = 0,
  ADD = 1,
  REMOVE = -1,
};
struct Event {
  int type;  // 0: query, 1: add, -1: remove
  int idx;
  pt vec;
};

#define MULTI_TEST
%:include "main.h"
#include <cassert>
SOLVE() {
  pt P, Q;
  cin >> P >> Q;

  int n;
  cin >> n;

  vector<Segment> segs(n);
  vector<int> qsegs;
  vector<Event> ev;

  auto add_point_event = [&](int i, pt v) {
    if (cross(P - Q, v - P) < 0) {
      ev.push_back(Event{
          .type = ADD,
          .idx = i,
          .vec = v - P,
      });
    } else {
      ev.push_back(Event{
          .type = REMOVE,
          .idx = i,
          .vec = v - P,
      });
    }
  };

  for (int i = 0; i < n; i++) {
    cin >> segs[i].u >> segs[i].v;
    if (collinear(P, Q, segs[i].u) or collinear(P, Q, segs[i].v)) continue;
    if (on_segment(segs[i].u, segs[i].v, P)) {
      ev.push_back(Event{
          .type = QUERY,
          .idx = i,
          .vec = segs[i].vec(),
      });
    }
    if (on_segment(segs[i].u, segs[i].v, Q)) {
      qsegs.push_back(i);
      add_point_event(i, segs[i].u);
      add_point_event(i, segs[i].v);
    }
  }

  if (empty(qsegs)) {
    return void(cout << 0 << nl);
  }

  auto by_ref_v = pt::by_ref_v(Q - P);
  auto by_ref = pt::by_ref(Q - P);

  sort(begin(qsegs), end(qsegs), [&](int i, int j) {
    return by_ref(segs[i].vec(), segs[j].vec());
  });
  //cerr << "Q " << qsegs << nl;
  vector<int> remap(n);
  for (int i = 0; i < size(qsegs); i++) {
    remap[qsegs[i]] = i;
    //cerr << segs[qsegs[i]].vec() << nl;
  }

  sort(begin(ev), end(ev), [&](auto const& i, auto const& j) {
    ll res = by_ref_v(i.vec, j.vec);
    if (res == 0) return i.type < j.type;
    return res > 0;
  });

  fenwick_tree<int> have(n);

  ll ans = 0;
  for (auto const& e : ev) {
    //cerr << "Event " << e.vec << nl;
    if (e.type == ADD) {
      int i = remap[e.idx];
      have.update_point(i, 1);
      //cerr << "ADD " << i << nl;
    } else if (e.type == REMOVE) {
      int i = remap[e.idx];
      have.update_point(i, -1);
      //cerr << "REM " << i << nl;
    } else {
      int i = e.idx;
      auto U = segs[i].u - Q;
      auto V = segs[i].v - Q;
      if (cross(P - Q, U) < 0) swap(U, V);
      int l = upper_bound(
                  begin(qsegs), end(qsegs), U,
                  [&](pt v, int j) { return by_ref(v, segs[j].vec()); }) -
              begin(qsegs);
      int r = lower_bound(
                  begin(qsegs), end(qsegs), V,
                  [&](int j, pt v) { return by_ref(segs[j].vec(), v); }) -
              begin(qsegs);
      //cerr << "GET " << l << " " << r << " @ " << segs[i].u << " " << segs[i].v << endl;
      assert(l <= r);
      ans += r - l;
      if (r < size(qsegs)) {
        ans += have.query_range(r, size(qsegs) - 1);
        //cerr << "R " << have.query_range(r, size(qsegs) - 1) << nl;
      }
      if (l > 0) {
        ans += have.query_range(0, l - 1);
        //cerr << "L " << have.query_range(0, l - 1) << nl;
      }
    }
  }
  cout << ans << nl;
}
