#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Move {
  int from;
  int to;
  int cnt;
};

using Stacks = std::vector<std::vector<char>>;

std::pair<Stacks, std::vector<Move>> readInput(int size) {
  std::vector<Move> moves;
  Stacks stacks;
  for (auto i = 0; i < size; i++) stacks.emplace_back();
  std::ifstream input("data/day5.txt");
  auto phase1 = true;
  for (std::string line; getline(input, line);) {
    if (phase1) {
      for (auto i = 0; 1 + 4 * i < line.size(); i += 1) {
        auto ch = line[1 + 4 * i];
        if (ch >= 'A' && ch <= 'Z') stacks[i].emplace_back(ch);
      }
      phase1 &= line != "";
    } else {
      int from, to, cnt;
      std::sscanf(line.data(), "move %d from %d to %d", &cnt, &from, &to);
      moves.push_back(Move{from - 1, to - 1, cnt});
    }
  }
  for (auto& stack : stacks) {
    std::reverse(stack.begin(), stack.end());
  }
  return std::make_pair(stacks, moves);
}

void applyMove(Stacks& stacks, Move const& move, bool part1) {
  auto& from = stacks[move.from];
  auto& to = stacks[move.to];
  if (part1) {
    for (auto i = 0; i < move.cnt; i++) {
      to.push_back(from[from.size() - 1]);
      from.pop_back();
    }
  } else {
    to.insert(to.end(), from.end() - move.cnt, from.end());
    from.resize(from.size() - move.cnt);
  }
}

std::string solve(Stacks stacks, std::vector<Move> const& moves, bool part1) {
  for (auto& move : moves) {
    applyMove(stacks, move, part1);
  }
  std::string ans = "";
  for (auto& s : stacks) {
    ans += s[s.size() - 1];
  }
  return ans;
}

int main() {
  auto [stacks, moves] = readInput(9);
  auto part1 = solve(stacks, moves, true);
  auto part2 = solve(stacks, moves, false);
  std::cout << "Part 1: " << part1 << std::endl;
  std::cout << "Part 2: " << part2 << std::endl;
}