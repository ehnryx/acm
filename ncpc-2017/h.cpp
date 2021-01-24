#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ld = long double;

const ld EPS = 1e-13;
const ld PI = acos((ld) -1);

ld sub(ld a, ld b) {
  ld s = a - b;
  if(s < 0) s += 2 * PI;
  return s;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<ld> ppl;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    ppl.push_back(atan2l(y, x));
  }

  map<ld,int> lines;
  vector<int> cap(m);
  for(int i=0; i<m; i++) {
    int x, y;
    cin >> x >> y >> cap[i];
    lines[atan2l(y, x)] = i;
  }

  vector<pair<int,int>> ans;
  vector<tuple<ld,ld,int>> v;
  for(int i=0; i<n; i++) {
    auto upper = lines.lower_bound(ppl[i]);
    if(upper == lines.end()) upper = lines.begin();
    auto lower = upper;
    if(lower == lines.begin()) lower = prev(lines.end());
    else lower = prev(lower);

    if(sub(upper->first, ppl[i]) < sub(ppl[i], lower->first) - EPS) {
      if(cap[upper->second] > 0) {
        cap[upper->second]--;
        ans.emplace_back(i, upper->second);
      }
    } else if(sub(ppl[i], lower->first) < sub(upper->first, ppl[i]) - EPS) {
      if(cap[lower->second] > 0) {
        cap[lower->second]--;
        ans.emplace_back(i, lower->second);
      }
    } else {
      auto [l, r] = make_pair(lower->first, upper->first);
      if(l < r) {
        v.emplace_back(lower->first, upper->first, i);
      } else {
        v.emplace_back(lower->first, upper->first, i);
      }
    }
  }

  if(!v.empty()) {
    sort(v.begin(), v.end());

    map<ld,int> used;
    int save = 0;
    ld s = get<0>(v[0]);
    for(auto [l, r, _] : v) {
      s = min(s, min(l, r));
      if(used[l] < cap[lines[l]]) {
        used[l]++;
      } else if(l > r) {
        save++;
      } else if (used[r] < cap[lines[r]]) {
        used[r]++;
      }
    }
    save = min(save, cap[lines[s]]);

    used.clear();
    used[s] = save;
    for(auto [l, r, i] : v) {
      if(used[l] < cap[lines[l]]) {
        used[l]++;
        ans.emplace_back(i, lines[l]);
      } else if(l > r) {
        if(save > 0) {
          save--;
          ans.emplace_back(i, lines[r]);
        }
      } else if (used[r] < cap[lines[r]]) {
        used[r]++;
        ans.emplace_back(i, lines[r]);
      }
    }
  }

  cout << ans.size() << nl;
  for(auto [a, b] : ans) {
    cout << a << " " << b << nl;
  }

  return 0;
}
