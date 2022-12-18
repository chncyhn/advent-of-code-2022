#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

using Coord = std::pair<int, int>;
using Dir = std::pair<int, int>;
using Move = std::pair<char, int>;

std::vector<Move> readInput() {
  std::ifstream input("data/day9.txt");
  std::vector<Move> moves;
  for (std::string line; getline(input, line);) {
    char dir;
    int times;
    std::sscanf(line.data(), "%c %d", &dir, &times);
    moves.emplace_back(dir, times);
  }
  return moves;
}

Dir dir(char ch) {
  switch (ch) {
    case 'R':
      return {0, 1};
    case 'L':
      return {0, -1};
    case 'U':
      return {1, 0};
    case 'D':
      return {-1, 0};
    default:
      throw std::invalid_argument("invalid");
  }
}

Coord applyMove(Coord& loc, char d) {
  auto [ox, oy] = dir(d);
  return {loc.first + ox, loc.second + oy};
}

bool touches(Coord& head, Coord& tail) {
  auto x = std::abs(head.first - tail.first) <= 1;
  auto y = std::abs(head.second - tail.second) <= 1;
  return x && y;
}

int signum(int x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }

Coord pull(Coord& head, Coord& tail) {
  if (touches(head, tail)) {
    return tail;
  }
  auto ox = signum(head.first - tail.first);
  auto oy = signum(head.second - tail.second);
  return {tail.first + ox, tail.second + oy};
}

int main() {
  auto moves = readInput();

  std::set<Coord> visited;
  visited.emplace(0, 0);
  Coord h{0, 0};
  Coord t{0, 0};
  for (auto& [dir, times] : moves) {
    for (auto i = 0; i < times; i++) {
      h = applyMove(h, dir);
      t = pull(h, t);
      visited.emplace(t.first, t.second);
    }
  }
  std::cout << visited.size() << std::endl;
}