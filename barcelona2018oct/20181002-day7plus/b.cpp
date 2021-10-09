#include <bits/stdc++.h>
using namespace std;

typedef __int128 Int;
typedef long long ll;
typedef pair<int,int> pii;

#define nl '\n'

struct pt { Int x, y, z; };
Int dot(const pt& a, const pt& b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}
pt cross(const pt& a, const pt& b) {
  return { a.y*b.z-b.y*a.z, a.z*b.x-b.z*a.x, a.x*b.y-b.x*a.y };
}
Int vol(const pt& a, const pt& b, const pt& c) {
  return dot(cross(a,b),c);
}

struct tri {
  int x, y, z;
  bool operator < (const tri& o) const {
    if (x!=o.x) return x<o.x;
    if (y!=o.y) return y<o.y;
    return z<o.z;
  }
  Int volume(const vector<pt>& p) const {
    return vol(p[x], p[y], p[z]);
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  int x, y, z;
  vector<pt> p;
  p.push_back({0,0,0});
  for (int i=0; i<n; i++) {
    cin >> x >> y >> z;
    p.push_back({x,y,z});
  }

  int m;
  cin >> m;

  map<pii,vector<tri>> adj;
  tri s;
  for (int i=0; i<m; i++) {
    cin >> x >> y >> z;
    if (!i) s = {x,y,z};
    adj[{x,y}].push_back({x,y,z});
    adj[{y,z}].push_back({x,y,z});
    adj[{z,x}].push_back({x,y,z});
    adj[{x,z}].push_back({x,y,z});
    adj[{y,x}].push_back({x,y,z});
    adj[{z,y}].push_back({x,y,z});
  }

  queue<pii> todo;
  set<tri> vis;
  Int v = 0;

  vis.insert(s);
  v += s.volume(p);
  todo.push({s.x,s.y});
  todo.push({s.y,s.z});
  todo.push({s.z,s.x});
  while (!todo.empty()) {
    pii e = todo.front();
    todo.pop();
    for (tri t : adj[e]) {
      if (vis.count(t)) continue;
      if (e == pii(t.x,t.y) || e == pii(t.y,t.z) || e == pii(t.z,t.x)) {
        v -= t.volume(p);
        vis.insert(t);
        todo.push({t.x,t.z});
        todo.push({t.y,t.x});
        todo.push({t.z,t.y});
      } else {
        v += t.volume(p);
        vis.insert(t);
        todo.push({t.x,t.y});
        todo.push({t.y,t.z});
        todo.push({t.z,t.x});
      }
    }
  }

  if (v < 0) v = -v;
  int k = v % 6;
  v /= 6;
  switch (k) {
    case 0: cout << (ll)v << nl;
        break;
    case 1: cout << (ll)v;
        cout << ".1";
        for (int i=0; i<7; i++) cout << 6;
        cout << nl;
        break;
    case 2: cout << (ll)v;
        cout << '.';
        for (int i=0; i<7; i++) cout << 3;
        cout << nl;
        break;
    case 3: cout << (ll)v;
        cout << ".5" << nl;
        break;
    case 4: cout << (ll)v;
        cout << '.';
        for (int i=0; i<7; i++) cout << 6;
        cout << nl;
        break;
    case 5: cout << (ll)v;
        cout << ".8";
        for (int i=0; i<7; i++) cout << 3;
        cout << nl;
        break;
    default: cout << "???" << nl;
  }

  return 0;
}
