#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int SCORES[3] = {1, 2, 3};
int winnerTo(int act) { return (act + 1) % 3; }
int loserTo(int act) { return (act - 1 + 3) % 3; }
bool beats(int a, int b) { return winnerTo(a) == b; }

std::vector<std::pair<int, int>> readInput() {
  std::vector<std::pair<int, int>> pairs;
  std::ifstream input("data/day2.txt");
  int cal = 0;
  for (std::string line; getline(input, line);) {
    pairs.push_back(std::make_pair(line[0] - 'A', line[2] - 'X'));
  }
  return pairs;
}

int part1Score(int me, int them) {
  if (beats(me, them))
    return 6 + SCORES[me];
  else if (beats(them, me))
    return SCORES[me];
  else
    return 3 + SCORES[me];
}

int part2Score(int me, int them) {
  if (me == 0)
    return SCORES[loserTo(them)];
  else if (me == 1)
    return 3 + SCORES[them];
  else
    return 6 + SCORES[winnerTo(them)];
}

int main() {
  auto rounds = readInput();
  auto part1 = 0;
  auto part2 = 0;
  for (auto x : rounds) {
    part1 += part1Score(x.second, x.first);
    part2 += part2Score(x.second, x.first);
  }
  std::cout << "Part 1: " << part1 << std::endl;
  std::cout << "Part 2: " << part2 << std::endl;
}