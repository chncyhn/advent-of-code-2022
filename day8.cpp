#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using Grid = std::vector<std::vector<int>>;
using Direction = std::pair<int, int>;
using Coord = std::pair<int, int>;

Grid readInput() {
  std::ifstream input("data/day8.txt");
  Grid grid;
  for (std::string line; getline(input, line);) {
    std::vector<int> row;
    for (auto i = 0; i < line.size(); i++) row.emplace_back(line[i] - '0');
    grid.emplace_back(row);
  }
  return grid;
}

bool inGrid(Grid const& grid, Coord const& loc) {
  auto rows = grid.size(), cols = grid[0].size();
  return loc.first >= 0 && loc.second >= 0 && loc.first < rows &&
         loc.second < cols;
}

bool onEdge(Grid const& grid, Coord const& loc) {
  auto rows = grid.size(), cols = grid[0].size();
  return loc.first == 0 || loc.second == 0 || loc.first == rows - 1 ||
         loc.second == cols - 1;
}

Coord move(Coord const& loc, Direction const& dir) {
  return std::make_pair(loc.first + dir.first, loc.second + dir.second);
}

Coord blocker(Grid const& grid, Coord const& loc, Direction const& dir) {
  auto cur = move(loc, dir);
  while (inGrid(grid, cur) &&
         grid[loc.first][loc.second] > grid[cur.first][cur.second]) {
    cur = move(cur, dir);
  }
  return cur;
}

int dist(Grid const& grid, Coord const& a, Coord const& b) {
  auto dist = std::abs(a.first - b.first) + std::abs(a.second - b.second);
  return inGrid(grid, b) ? dist : dist - 1;
}

int main() {
  auto grid = readInput();
  std::vector<Direction> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  auto part1 = 0, part2 = 0;
  for (auto i = 0; i < grid.size(); i++) {
    for (auto j = 0; j < grid[0].size(); j++) {
      Coord loc{i, j};
      auto score = 1;
      bool visible = false;
      for (auto& dir : dirs) {
        auto blk = blocker(grid, loc, dir);
        score *= dist(grid, loc, blk);
        if (!inGrid(grid, blk)) visible = true;
      }
      if (!onEdge(grid, loc)) part2 = std::max(part2, score);
      if (visible) part1++;
    }
  }
  std::cout << "Part 1: " << part1 << std::endl;
  std::cout << "Part 2: " << part2 << std::endl;
}