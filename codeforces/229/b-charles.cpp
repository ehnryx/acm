#include <queue>
#include <iostream>
#include <unordered_map>

using namespace std;

int main(void) {
  cin.tie(0)->sync_with_stdio(0); // incantation for faster cin

  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> adj_list(n + 1); // unordered_map -> vector
  vector<unordered_map<int, bool>> collisions(n + 1); // unordered_map -> vector
  for (int i = 0; i < m; i++) {
    int a, b, weight;
    cin >> a >> b >> weight;
    adj_list[a].push_back(pair<int, int>(b, weight));
    adj_list[b].push_back(pair<int, int>(a, weight));
  }
  for (int i = 0; i < n; i++) {
    int count;
    cin >> count;
    if (count == 0) continue;
    unordered_map<int, bool> current_collisions;
    for (int i = 0; i < count; i++) {
      int time;
      cin >> time;
      current_collisions[time] = true;
    }
    collisions[i+1] = current_collisions;
  }
  auto cmp = [](pair<int, int> v1, pair<int, int> v2) {return v1.second > v2.second; };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> vertex_queue(cmp);
  vertex_queue.push(pair<int, int>(1, 0));
  vector<int> path_lengths(n+1, -1);
  while (vertex_queue.size() > 0) {
    pair<int, int> cur_v = vertex_queue.top();
    vertex_queue.pop();
    if (path_lengths[cur_v.first] != -1 && path_lengths[cur_v.first] < cur_v.second) continue;
    if (cur_v.first == n) {
      cout << cur_v.second << '\n';
      return 0;
    }
    const vector<pair<int, int>>& children = adj_list[cur_v.first];
    int wait_time = 0;
    int cur_time = cur_v.second;
    while (collisions[cur_v.first][cur_time] == true) {
      wait_time++;
      cur_time++;
    }
    for (pair<int, int> child : children) {
      int new_path_length = cur_v.second + wait_time + child.second;
      if (path_lengths[child.first] != -1 && path_lengths[child.first] <= new_path_length) continue;
      path_lengths[child.first] = new_path_length;
      vertex_queue.push(pair<int, int>(child.first, new_path_length));
    }
  }
  cout << -1 << '\n';
  return 0;
}

