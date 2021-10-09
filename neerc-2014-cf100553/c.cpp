#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
constexpr char nl = '\n';

#define FNAME "cactus"

vector<string> tokenize(const string& s) {
  vector<string> out;
  string cur;
  for(char c : s) {
    if(isalpha(c) || isdigit(c)) {
      cur.push_back(c);
    } else {
      if(!cur.empty()) out.push_back(cur);
      out.push_back(string(1, c));
      cur.clear();
    }
  }
  if(!cur.empty()) out.push_back(cur);
  return out;
}

vector<string> clean_range(const vector<string>&, int&);

vector<string> get_graph(const vector<string>& line, int& i) {
  vector<string> out;
  int open = 0;
  while(i < line.size() && !((line[i] == ")" || line[i] == ",") && open == 0)) {
    out.push_back(line[i]);
    if(line[i] == "(") open++;
    else if(line[i] == ")") open--;
    i++;
  }
  return out;
}

vector<string> clean_range(const vector<string>& line, int& i) {
  //cerr << "clean_range: "; for(string s : line) cerr << s << " ";
  //cerr << nl;
  vector<string> out;
  int open = 0;
  while(i < line.size() && !((line[i] == ")" || line[i] == ",") && open == 0)) {
    if(line[i] == "range") {
      // range ( pat , l , r ) ?
      // range ( pat , l , r ) , graph )
      //  0    1  2  3 4 5 6 7 8   9+
      string pat = line[i + 2];
      int left = stoi(line[i + 4]);
      int right = stoi(line[i + 6]);
      if(left > right) swap(left, right);
      if(line[i+8] == ",") {
        i += 9;
        vector<string> inner = get_graph(line, i);
        for(int j=left; j<=right; j++) {
          vector<string> rep = inner;
          auto it = find(rep.begin(), rep.end(), pat);
          while(it != rep.end()) {
            *it = to_string(j);
            it = find(it + 1, rep.end(), pat);
          }
          rep = clean_range(rep, *(new int(0)));
          out.insert(out.end(), rep.begin(), rep.end());
          if(j < right) out.push_back(",");
        }
      } else {
        out.push_back(to_string(right - left + 1));
        i += 8;
      }
    } else {
      out.push_back(line[i]);
      if(line[i] == "(") open++;
      else if(line[i] == ")") open--;
      i++;
    }
  }
  //cerr << "return: "; for(string s : out) cerr << s << " ";
  //cerr << nl;
  return out;
}

vector<string> clean_repeats(const vector<string>& line, int& i) {
  vector<string> out;
  int open = 0;
  while(i < line.size() && !((line[i] == ")" || line[i] == ",") && open == 0)) {
    if(isdigit(line[i][0])) {
      int num = stoi(line[i]);
      vector<string> graph;
      if(line[i+1] == ")") {
        i += 1;
        graph.push_back("e");
      } else {
        i += 2;
        graph = clean_repeats(line, i);
      }
      for(int j=0; j<num; j++) {
        if(j > 0) out.push_back(",");
        out.insert(out.end(), graph.begin(), graph.end());
      }
    } else {
      if(line[i] == "c" && (i+1 == line.size() || line[i+1] != "(")) {
        out.push_back("e");
      } else {
        out.push_back(line[i]);
      }
      if(line[i] == "(") open++;
      else if(line[i] == ")") open--;
      i++;
    }
  }
  return out;
}

const int N = 2e5 + 1;
int dsu[N];
int find(int i) {
  if(dsu[i] == 0) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  i = find(i); j = find(j);
  if(i != j) dsu[i] = j;
}

//vector<int> adj[N], cac[N];
vector<int> cac[N];

multiset<int> adj[N];
// Watch out for stack overflow. Answer is returned in reverse order.
void euler(int u, list<int>& ret, list<int>::iterator it) {
  for (auto it2 = adj[u].begin(); it2 != adj[u].end(); ) {
    int v=*it2; adj[u].erase(it2);
    /*undirected:*/ adj[v].erase(adj[v].find(u));
    euler(v, ret, ret.insert(it, v)); it2 = adj[u].begin(); }
}

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  string eyqs;
  cin >> eyqs;

  vector<string> line = tokenize(eyqs);
#ifndef ONLINE_JUDGE
  cout << "LINE" << nl;
  for(string s : line) {
    cout << s << " ";
  }
  cout << nl << nl;
#endif

  vector<string> clean = clean_range(line, *(new int(0)));
#ifndef ONLINE_JUDGE
  cout << "CLEAN" << nl;
  for(string s : clean) {
    cout << s << " ";
  }
  cout << nl << nl;
#endif

  vector<string> graph = clean_repeats(clean, *(new int(0)));
#ifndef ONLINE_JUDGE
  cout << "EXPANDED" << nl;
  for(string s : graph) {
    cout << s << " ";
  }
  cout << nl << nl;
#endif

  stack<char> op;
  stack<vector<pair<int,int>>> lims;
  lims.push({});

  int uid = 0;
  int len = graph.size();
  for(int i=0; i<len; i++) {
    if(isalpha(graph[i][0]) && graph[i][0] != 'e') {
      op.push(graph[i][0]);
      lims.push({});
    } else if(graph[i] == "e") {
      int a = ++uid;
      int b = ++uid;
      cac[a].push_back(b);
      cac[b].push_back(a);
      lims.top().emplace_back(a, b);
    } else if(graph[i] == "(") {
      // do nothing because we pushed already
    } else if(graph[i] == ")") {
      // pop and join
      for(int j=0; j<lims.top().size(); j++) {
        if(op.top() == 'l') {
          int k = (j + 1) % lims.top().size();
          link(lims.top()[j].second, lims.top()[k].first);
        } else if(op.top() == 'c') {
          if(j > 0) {
            link(lims.top()[j].first, lims.top()[j-1].second);
          }
        } else { // op.top() == 't'
          if(j > 0) {
            link(lims.top()[j].first, lims.top()[j-1].first);
          }
        }
      }
      int newfirst = lims.top().front().first;
      int newsecond = (op.top() == 'c' ? lims.top().back().second : lims.top().front().second);
      lims.pop();
      op.pop();
      lims.top().emplace_back(newfirst, newsecond);
    } else { // graph[i] == ","
      // do nothing ???
    }
  }

  vector<int> remap(uid+1);
  set<int> seen;
  int n = 0;
  for(int i=1; i<=uid; i++) {
    if(seen.insert(find(i)).second) {
      remap[find(i)] = ++n;
    }
  }
  int first = find(remap.begin(), remap.end(), 1) - remap.begin();
  int last = find(remap.begin(), remap.end(), n) - remap.begin();
  swap(remap[first], remap[find(lims.top()[0].first)]);
  swap(remap[last], remap[find(lims.top()[0].second)]);

#ifndef ONLINE_JUDGE
  cerr << n << nl;
#endif
  for(int i=1; i<=uid; i++) {
    int u = remap[find(i)];
    for(int j : cac[i]) {
      int v = remap[find(j)];
      adj[u].insert(v);
#ifndef ONLINE_JUDGE
      if(u < v) cerr << u << " " << v << nl;
#endif
    }
  }

  set<int> roots;
  for(int i=1; i<=n; i++) {
    if(adj[i].size() % 2) {
      adj[i].insert(0);
      adj[0].insert(i);
    }
  }

  list<int> ans;
  euler(0, ans, ans.begin());
  if(ans.size() <= 1) ans.clear();
  euler(1, ans, ans.begin());
  if(*ans.begin() != 0) {
    ans.insert(ans.end(), *ans.begin());
    ans.insert(ans.begin(), 0);
  }

  vector<vector<int>> out = {};
  for(int it : ans) {
    if(it == 0) {
      out.push_back({});
    } else {
      out.back().push_back(it);
    }
  }

  cerr << nl;
  cout << n << " " << out.size() << nl;
  for(const auto& p : out) {
    cout << p.size();
    for(int it : p) {
      cout << " " << it;
    }
    cout << nl;
  }

  return 0;
}
