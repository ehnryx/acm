#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Item {
  ll length;
  char type; 
  Item(ll len, char c=0): length(len), type(c) {}
  bool operator == (const Item& other) const {
    return length == other.length && type == other.type;
  }
  bool operator != (const Item& other) const {
    return !(*this == other);
  }
};

void insert(list<Item>& str, ll id, char c) {
  for (auto it = str.begin(); it != str.end(); ++it) {
    if (it->type == '-') {
      continue;
    } else if (id > it->length) {
      id -= it->length;
    } else {
      if (id == 1) {
        str.insert(it, Item(1, c));
      } else {
        it->length -= id-1;
        it = str.insert(it, Item(1, c));
        str.insert(it, Item(id-1, 0));
      }
      break;
    }
  }
}

void erase(list<Item>& str, ll id) {
  for (auto it = str.begin(); it != str.end(); ++it) {
    if (it->type == '-') {
      continue;
    } else if (id > it->length) {
      id -= it->length;
    } else {
      if (it->length == 1) {
        if (it->type == 0)
          it->type = '-';
        else
          str.erase(it);
      } else {
        if (id == 1) {
          it->length--;
          str.insert(it, Item(1, '-'));
        } else if (id == it->length) {
          it->length--;
          str.insert(++it, Item(1, '-'));
        } else {
          it->length -= id;
          it = str.insert(it, Item(1, '-'));
          str.insert(it, Item(id-1, 0));
        }
      }
      break;
    }
  }
}

bool neq(const list<Item>& first, const list<Item>& second) {
  auto i = first.begin();
  auto j = second.begin();
  while (i != first.end() && j != second.end()) {
    deque<Item> firstSeg;
    deque<Item> secondSeg;
    while (i != first.end() && i->type != 0 && j != second.end() && j->type != 0) {
      if (i->type == '-') firstSeg.push_front(*i);
      else firstSeg.push_back(*i);
      if (j->type == '-') secondSeg.push_front(*j);
      else secondSeg.push_back(*j);
      ++i; ++j;
    }
    if (firstSeg != secondSeg)
      return true;
    if (i == first.end() || j == second.end())
      break;
    if (*i != *j)
      return true;
    ++i; ++j;
  }
  return i != first.end() || j != second.end();
}

void build(list<Item>& dna) {
  char command, add;
  ll index;
  dna.insert(dna.begin(), Item(INFLL, 0));
  for(;;) {
    cin >> command;
    if (command == 'E') 
      break;
    if (command == 'D') {
      cin >> index;
      erase(dna, index);
    } else {
      cin >> index >> add;
      insert(dna, index, add);
    }
  }
  for (auto it = dna.begin(); it != dna.end(); ) {
    if (it != dna.begin() && it->type == 0 && prev(it)->type == 0) {
      prev(it)->length += it->length;
      it = dna.erase(it);
    } else {
      ++it;
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  list<Item> first, second;
  build(first);
  build(second);
  cout << neq(first, second) << nl;

  return 0;
}
