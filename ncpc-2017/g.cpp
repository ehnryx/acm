#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr char nl = '\n';

struct Team {
  int score, penalty, id;
  Team(int s, int p, int i): score(s), penalty(p), id(i) {}
  bool operator < (const Team& o) const {
    if(score != o.score) return score > o.score;
    if(penalty != o.penalty) return penalty < o.penalty;
    return id < o.id;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<int> score(n+1), penalty(n+1);
  ordered_set<Team> order;
  for(int i=1; i<=n; i++) {
    order.insert(Team(score[i], penalty[i], i));
  }

  vector<int> ans;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    order.erase(Team(score[a], penalty[a], a));
    score[a] += 1;
    penalty[a] += b;
    order.insert(Team(score[a], penalty[a], a));
    ans.push_back(order.order_of_key(Team(score[1], penalty[1], 1)) + 1);
  }

  for(int it : ans) {
    cout << it << nl;
  }

  return 0;
}
