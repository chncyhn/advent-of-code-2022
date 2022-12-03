#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> readCalories() {
  std::vector<int> cals;
  std::ifstream input("data/day1.txt");
  int cal = 0;
  for (std::string line; getline(input, line);) {
    if (line == "") {
      cals.push_back(cal);
      cal = 0;
    } else {
      cal += std::stoi(line);
    }
  }
  cals.push_back(cal);
  return cals;
}

int main() {
  auto cals = readCalories();
  std::partial_sort(cals.begin(), cals.begin() + 3, cals.end(),
                    std::greater<int>{});
  auto ans1 = cals[0];
  auto ans2 = cals[0] + cals[1] + cals[2];
  std::cout << "Part 2: " << ans1 << std::endl;
  std::cout << "Part 1: " << ans2 << std::endl;
}