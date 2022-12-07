#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<std::pair<std::string, std::string>> readInput() {
  std::vector<std::pair<std::string, std::string>> pairs;
  std::ifstream input("data/day3.txt");
  for (std::string line; getline(input, line);) {
    std::string first = line.substr(0, line.length() / 2);
    std::string second = line.substr(line.length() / 2);
    pairs.emplace_back(first, second);
  }
  return pairs;
}

char findCommon(const std::string& a, const std::string& b) {
  for (auto ch : a) {
    if (b.find(ch) != std::string::npos) {
      return ch;
    }
  }
  return 0;
}

int prio(char ch) {
  if (ch <= 'Z')
    return ch - 'A' + 27;
  else
    return ch - 'a' + 1;
}

char findCommon(const std::string& a, const std::string& b,
                const std::string& c) {
  std::map<char, int> cnts;
  for (auto ch : a) cnts[ch] |= (1 << 0);
  for (auto ch : b) cnts[ch] |= (1 << 1);
  for (auto ch : c) cnts[ch] |= (1 << 2);
  for (auto [k, v] : cnts) {
    if (v == (1 << 3) - 1) return k;
  }
  return 0;
}

int main() {
  auto rucksacks = readInput();

  auto part1 = 0;
  for (auto r : rucksacks) {
    part1 += prio(findCommon(r.first, r.second));
  }
  auto part2 = 0;
  for (auto i = 0; i < rucksacks.size(); i += 3) {
    auto a = rucksacks[i].first + rucksacks[i].second;
    auto b = rucksacks[i + 1].first + rucksacks[i + 1].second;
    auto c = rucksacks[i + 2].first + rucksacks[i + 2].second;
    part2 += prio(findCommon(a, b, c));
  }
  std::cout << "Part 1: " << part1 << std::endl;
  std::cout << "Part 2: " << part2 << std::endl;
}