#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
#define pii pair<int,int>
const int INF = 0x3f3f3f3f;

struct Node {
  int next;
  int dist;
  Node (int n=0, int d=INF) {
    next = n;
    dist = d;
  }
};

Node memo[1<<22];
void bfs(int start) {
  queue<pair<int,int>> next; // prev, id
  next.push(pair<int,int>(-1, start));
  while (!next.empty()) {
    pair<int,int> curr = next.front();
    int id = curr.second;
    next.pop();
    if (memo[id].dist == INF) {
      if (id == start) {
        memo[id].next = -1;
        memo[id].dist = 0;
      }
      else {
        memo[id].next = curr.first;
        memo[id].dist = memo[curr.first].dist+1;
      }
      int empty;
      vector<int> val;
      for (int i = 0; i < 3*7; i+=3) {
        val.push_back((id & (7<<i)) >> i);
        if (val.back() == 0)
          empty = i/3;
      }
      if (empty == 0) {
        next.push(pii(id, (id + (val[1] << 3*0) - (val[1] << 3*1))));
        next.push(pii(id, (id + (val[5] << 3*0) - (val[5] << 3*5))));
      } else if (empty == 1) {
        next.push(pii(id, (id + (val[0] << 3*1) - (val[0] << 3*0))));
        next.push(pii(id, (id + (val[2] << 3*1) - (val[2] << 3*2))));
        next.push(pii(id, (id + (val[6] << 3*1) - (val[6] << 3*6))));
      } else if (empty == 2) {
        next.push(pii(id, (id + (val[1] << 3*2) - (val[1] << 3*1))));
        next.push(pii(id, (id + (val[3] << 3*2) - (val[3] << 3*3))));
      } else if (empty == 3) {
        next.push(pii(id, (id + (val[2] << 3*3) - (val[2] << 3*2))));
        next.push(pii(id, (id + (val[4] << 3*3) - (val[4] << 3*4))));
      } else if (empty == 4) {
        next.push(pii(id, (id + (val[3] << 3*4) - (val[3] << 3*3))));
        next.push(pii(id, (id + (val[5] << 3*4) - (val[5] << 3*5))));
        next.push(pii(id, (id + (val[6] << 3*4) - (val[6] << 3*6))));
      } else if (empty == 5) {
        next.push(pii(id, (id + (val[0] << 3*5) - (val[0] << 3*0))));
        next.push(pii(id, (id + (val[4] << 3*5) - (val[4] << 3*4))));
      } else if (empty == 6) {
        next.push(pii(id, (id + (val[1] << 3*6) - (val[1] << 3*1))));
        next.push(pii(id, (id + (val[4] << 3*6) - (val[4] << 3*4))));
      } else cout << "OH NO" << endl;
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0); 

  int base = 0;
  for (int i = 0; i < 6; i++) {
    base = (base << 3) + i+1;
  } bfs(base);

  int cc;
  int n;
  string s;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> cc >> s;
    int id = 0;
    for (int i = 0; i < 6; i++) {
      id = (id << 3) + s[i]-'A'+1;
    }
    int ans = memo[id].dist;
    if (ans == INF) cout << cc << " NO SOLUTION" << endl;
    else {
      cout << cc << " " << ans << " ";
      while (memo[id].next != -1) {
        int temp = id ^ memo[id].next;
        while (temp/8) {
          temp /= 8;
        }
        cout << char(temp-1+'A');
        id = memo[id].next;
      }
      cout << endl;
    }
  }

  return 0;
}
