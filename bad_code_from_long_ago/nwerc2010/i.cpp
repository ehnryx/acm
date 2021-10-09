#include <bits/stdc++.h>
using namespace std;

map<int,int> answer;
void solve(int n, int index, const vector<int>& start, const vector<int>& end) {
  cerr << "solving layer " << n << ", index " << index << endl;
  cerr << "matches: " << endl; for (int i = 0; i < 1<<n; i++)
    cerr << index+i << ": " << start[i] << "    " << end[i] << endl;
  cerr << endl;

  if (n == 0) {
    if (start[0]) {
      cerr << "insert pair " << start[0] << " with index " << index << endl;
      assert(start[0] == end[0]);
      answer.insert(pair<int,int>(start[0], index));
    }
    return;
  }
  else {
    int half = 1<<(n-1);
    set<int> intop, inbot;
    map<int,int> conflict[2];
    vector<int> top[2];
    vector<int> bottom[2];
    for (int i = 0; i < 2; i++) {
      top[i].resize(half);
      bottom[i].resize(half);
      memset(&top[i][0], 0, half*sizeof(top[i][0]));
      memset(&bottom[i][0], 0, half*sizeof(bottom[i][0]));
    }

    // find conflicts
    for (int i = 0; i < half; i++) {
      if (start[i] && start[i+half]) {
        conflict[0].insert(pair<int,int>(start[i], i+half));
        conflict[0].insert(pair<int,int>(start[i+half], i));
      }
      if (end[i] && end[i+half]) {
        conflict[1].insert(pair<int,int>(end[i], i+half));
        conflict[1].insert(pair<int,int>(end[i+half], i));
      }
    }
    // resolve conflicts
    for (int i = 0; i < half; i++) {
      if (conflict[0].count(start[i])) {
        int j = 0;
        intop.insert(start[i]);
        top[0][i] = start[i];
        int curr = start[i];
        int next;
        for(;;) {
          ++j;
          if (j%2) {
            next = conflict[1][curr];
            if (next == 0) break;
            bottom
          }
          else {
            next = conflict[0][curr];
          }
        }
      }
      if (conflict[1].count(end[i])) {
      }
    }
    // resolve others
    for (int i = 0; i < half; i++) {
      if (start[i] && !start[i+half]) {
        assert(!top[0][i]);
        assert(!bottom[0][i]);
        if (intop.count(start[i])) 
          top[0][i] = start[i];
        else
          bottom[0][i] = start[i];
      }
      else if (start[i+half] && !start[i]) {
        assert(!top[0][i]);
        assert(!bottom[0][i]);
        if (intop.count(start[i+half]))
          top[0][i] = start[i+half];
        else
          bottom[0][i] = start[i+half];
      }
    }
    for (int i = 0; i < half; i++) {
      if (end[i] && !end[i+half]) {
        assert(!top[1][i]);
        assert(!bottom[1][i]);
        if (intop.count(end[i]))
          top[1][i] = end[i];
        else
          bottom[1][i] = end[i];
      }
      else if (end[i+half] && !end[i]) {
        assert(!top[1][i]);
        assert(!bottom[1][i]);
        if (intop.count(end[i+half]))
          top[1][i] = end[i+half];
        else 
          bottom[1][i] = end[i+half];
      }
    }
    if (!intop.empty())
      solve(n-1, index, top[0], top[1]);
    solve(n-1, index+half, bottom[0], bottom[1]);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int layers, m; // 65536
  int a, b;
  vector<int> start, end;

  int T;
  cin >> T;
  while (T--) {
    answer.clear();
    start.clear();
    end.clear();

    cin >> layers >> m;
    start.resize(1<<layers);
    end.resize(1<<layers);
    memset(&start[0], 0, (1<<layers)*sizeof(start[0]));
    memset(&end[0], 0, (1<<layers)*sizeof(end[0]));
    for (int i = 1; i <= m; i++) {
      cin >> a >> b;
      start[a] = i;
      end[b] = i;
    }
    cerr << "start solve" << endl;
    solve(layers, 0, start, end);
    for (int i = 1; i <= m; i++) {
      cout << answer[i] << " ";
    } cout << endl;
  }
  
  return 0;
}
