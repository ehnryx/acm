#include <bits/stdc++.h>
using namespace std;

#define FILENAME "equal"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int M = 1e6+1;
int cnt[M];
bool remable[M];

struct Item {
  int sz, todo;
  bool operator < (const Item& o) const {
    if(sz != o.sz) return sz > o.sz;
    else return todo < o.todo;
  }
};

int ans1[M], ans2[M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  if(fopen(FILENAME ".in", "r")) {
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
  }

  int n;
  cin >> n;
  int a[n];
  for(int i=0; i<n; i++) {
    cin >> a[i];
    cnt[a[i]] += 1;
  }

  priority_queue<Item> dijk;
  int remcnt = 0;
  vector<int> todo;
  int tot = 0;
  for(int i=1; i<M; i++) {
    if(cnt[i]) {
      tot++;
      for(int j=i+i; j<M; j+=i) {
        if(cnt[j]) {
          remable[i] = true;
          break;
        }
      }
      if(remable[i]) {
        dijk.push({cnt[i],0});
        remcnt++;
      } else {
        todo.push_back(cnt[i]);
      }
    }
  }
  sort(todo.begin(), todo.end());
  assert(!todo.empty());

  int tid = 1;
  if(todo.size() > 1) {
    dijk.push({todo[0] + todo[1], 1});
  }

  int cur = remcnt + todo.size();
  int aid = 0;
  ans1[aid++] = cur;
  while(!dijk.empty()) {
    Item rem = dijk.top();
    dijk.pop();
    for(int j=1; j<rem.sz; j++) {
      ans1[aid++] = cur;
    }
    ans1[aid++] = --cur;
    if(rem.todo && ++tid < todo.size()) {
      dijk.push({todo[tid], 1});
    }
  }
  if(todo.size() == 1) {
    for(int j=1; j<=todo.back(); j++) {
      ans1[aid++] = cur;
    }
  }

  if(todo.size() > 1) {
    tid = 1;
    dijk.push({todo[0] + todo[1], 1});
    cur = remcnt + todo.size();
    aid = 0;
    ans2[aid++] = cur;
    while(!dijk.empty()) {
      Item rem = dijk.top();
      dijk.pop();
      for(int j=1; j<rem.sz; j++) {
        ans2[aid
      }
    }
  }

  return 0;
}
