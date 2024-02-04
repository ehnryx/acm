#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int _d, n;
  cin >> _d >> n;
  auto d = _d * 3600ll;  // scale to treat speed as km/s

  ll last_t = 0;
  multiset<int> lefts;
  map<int, int> speed;

  auto get_speed = [&]() -> int {
    auto it = lefts.begin();
    if(it == lefts.end() or *it < 100) {
      return 100;
    } else {
      return *it;
    }
  };

  auto update_travel = [&](ll t) {
    auto cur_speed = get_speed();
    auto need = (d + cur_speed - 1) / cur_speed;
    auto dt = t - last_t;
    if (need <= dt) {
      d = 0;
      last_t += need;
    } else {
      d -= dt * cur_speed;
      last_t += dt;
    }
  };

  for (int i = 0; i < n and d > 0; i++) {
    int t, id;
    char dir;
    cin >> t >> id >> dir;
    update_travel(t);
    if (dir == 'L') {
      int s;
      cin >> s;
      speed[id] = s;
      lefts.insert(s);
    } else {
      lefts.erase(lefts.find(speed[id]));
    }
  }
  update_travel(numeric_limits<ll>::max());

  cout << last_t << nl;

  return 0;
}
