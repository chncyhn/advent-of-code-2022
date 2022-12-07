#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<std::pair<int, int>> readInput() {
  std::vector<std::pair<int, int>> pairs;
  std::ifstream input("data/test_day4.txt");
  for (std::string line; getline(input, line);) {
    int a, b, c, d;
    std::sscanf(line.data(), "%d-%d,%d-%d", &a, &b, &c, &d);
    pairs.emplace_back(std::make_pair(a, b));
    pairs.emplace_back(std::make_pair(c, d));
  }
  return pairs;
}

bool covers(std::pair<int, int> const& a, std::pair<int, int> const& b) {
  return a.first <= b.first && a.second >= b.second;
}

bool overlaps(std::pair<int, int> const& a, std::pair<int, int> const& b) {
  return !(a.first > b.second || a.second < b.first);
}

int main() {
  auto ranges = readInput();
  auto part1 = 0;
  auto part2 = 0;
  for (auto i = 0; i < ranges.size(); i += 2) {
    auto a = ranges[i], b = ranges[i + 1];
    if (covers(a, b) || covers(b, a)) ++part1;
    if (overlaps(a, b)) ++part2;
  }
  std::cout << "Part 1: " << part1 << std::endl;
  std::cout << "Part 2: " << part2 << std::endl;
}