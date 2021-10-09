#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace std {
  template<> struct hash<pii> {
    size_t operator () (const pii& v) const {
      return hash<int>()(v.first<<4) ^ hash<int>()(v.second);
    }
  };
}

bool x_inc(const pii& a, const pii& b) {
  return a.first < b.first;
}
bool x_dec(const pii& a, const pii& b) {
  return a.first > b.first;
}
bool y_inc(const pii& a, const pii& b) {
  return a.second < b.second;
}
bool y_dec(const pii& a, const pii& b) {
  return a.second > b.second;
}

// left: 0, ccw

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, w, h;
  cin >> n >> w >> h;

  unordered_map<pii,int> index;
  vector<pii> side[4];

  int a, b, x, y;
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> x >> y;
    index[pii(a,b)] = index[pii(x,y)] = i;
    if (a == 0) side[0].push_back(pii(a,b));
    if (a == w) side[2].push_back(pii(a,b));
    if (b == 0) side[1].push_back(pii(a,b));
    if (b == h) side[3].push_back(pii(a,b));
    if (x == 0) side[0].push_back(pii(x,y));
    if (x == w) side[2].push_back(pii(x,y));
    if (y == 0) side[1].push_back(pii(x,y));
    if (y == h) side[3].push_back(pii(x,y));
  }
  sort(side[0].begin(), side[0].end(), y_dec);
  sort(side[2].begin(), side[2].end(), y_inc);
  sort(side[3].begin(), side[3].end(), x_dec);
  sort(side[1].begin(), side[1].end(), x_inc);

  vector<pii> p = side[0];
  for (int i = 1; i < 4; i++) {
    for (const pii& it : side[i]) {
      p.push_back(it);
    }
  }

  unordered_set<int> cur;
  int front, back;
  front = back = 0;
  n = p.size();
  while (back < n) {
    int id = index[p[front]];
    if (!cur.count(id)) {
      cur.insert(id);
      if (cur.size() == n) {
        pair<ld,ld> l = pair<ld,ld>(p[back].first, p[back].second);
        pair<ld,ld> r = pair<ld,ld>(p[front].first, p[front].second);
        if (l.first == 0) l.second += 0.5;
        if (l.first == w) l.second -= 0.5;
        if (l.second == 0) l.first -= 0.5;
        if (l.second == h) l.first += 0.5;
        if (r.first == 0) r.second -= 0.5;
        if (r.first == w) r.second += 0.5;
        if (r.second == 0) r.first += 0.5;
        if (r.second == h) r.first -= 0.5;
        if (l.first == r.first) {
        }
        if (l.second == r.second) {
        }
      }
    }

    else {
      while (back < n && index[p[back]] != id) {
        cur.erase(index[p[back]]);
        back++;
      }
      if (back == n) break;
      ++back;
    }

    front = (front + 1) % n;
  }

  cout << 2 << nl;
  cout << 0 << " " << 0.618 << " " << w << " " << h-0.618 << nl;
  cout << 0 << " " << h-0.618 << " " << w << " " << 0.618 << nl;

  return 0;
}
