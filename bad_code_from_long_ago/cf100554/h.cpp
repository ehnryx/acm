#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ ";
  for (const T& it : v) os << it << " ";
  os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Object {
  map<string, Object> field;
  string value;

  Object() {}
  Object(const string& s) {
    field.clear();
    build(s);
  }

  void build(const string& s) {
    value = s;
    if (s.back() == '}') {
      int depth;
      string key, object;
      for (int i = 1; i < s.size()-1; i++) {
        if (s[i] != ':') {
          key.push_back(s[i]);
        } else {
          depth = 0;
          for (i++; i < s.size()-1 && (s[i] != ',' || depth > 0); i++) {
            object.push_back(s[i]);
            if (s[i] == '{') depth++;
            if (s[i] == '}') depth--;
          }
          field[key] = Object(object);
          key.clear();
          object.clear();
        }
      }
    }
  }

  /*
  string query(string s) {
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '.')
        s[i] = ' ';
    }

    vector<string> path;
    string temp;
    istringstream iss(s);
    while (iss >> temp) {
      path.push_back(temp);
    }
    return query(path, 0);
  }
  */

  string query(const string& s) {
    vector<string> path;
    string key;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '.') {
        path.push_back(key);
        key.clear();
      } else {
        key.push_back(s[i]);
      }
    }
    path.push_back(key);
    return query(path, 0);
  }

  string query(const vector<string>& path, int id) {
    if (id == path.size())
      return value;
    if (field.count(path[id]))
      return field[path[id]].query(path, id+1);
    else
      return "Error!";
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  Object json;

  int T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;
    json.build(s);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> s;
      cout << json.query(s) << nl; 
      //cerr << endl;
    }
  }

  return 0;
}
