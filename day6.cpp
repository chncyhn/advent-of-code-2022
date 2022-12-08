#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string readInput() {
  std::ifstream input("data/day6.txt");
  for (std::string line; getline(input, line);) {
    return line;
  }
  return "";
}

int solve(std::string const& buffer, int size) {
  std::map<char, int> cnts;
  for (auto i = 0; i < size - 1; i++) cnts[buffer[i]]++;
  for (auto i = size - 1; i < buffer.size(); i++) {
    cnts[buffer[i]]++;

    if (cnts.size() == size) return i + 1;

    auto j = i - size + 1;
    if (--cnts[buffer[j]] == 0) cnts.erase(buffer[j]);
  }
  return -1;
}

int main() {
  auto buffer = readInput();
  std::cout << "Part 1: " << solve(buffer, 4) << std::endl;
  std::cout << "Part 2: " << solve(buffer, 14) << std::endl;
}
