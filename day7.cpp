#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Dir {
  std::string path;
  std::uint32_t filesize;
  Dir* parent;
  std::map<std::string, Dir*> children;

  Dir(std::string path)
      : path(path), filesize(0), parent(nullptr), children({}) {}
};

std::vector<std::string> readInput() {
  std::ifstream input("data/day7.txt");
  std::vector<std::string> lines;
  for (std::string line; getline(input, line);) {
    lines.emplace_back(line);
  }
  return lines;
}

std::uint32_t dfs(Dir* dir, std::vector<std::uint32_t>& sizes) {
  auto size = dir->filesize;
  for (auto [_, child] : dir->children) {
    size += dfs(child, sizes);
  }
  sizes.emplace_back(size);
  return size;
}

void runCommands(Dir* root, std::vector<std::string> const& commands) {
  Dir* cur = root;
  for (auto i = 1; i < commands.size(); i++) {
    auto cmd = commands[i];
    if (cmd.find("$ cd") != std::string::npos) {
      auto target = cmd.substr(5);
      if (target == "..") {
        cur = cur->parent;
      } else if (target == "/") {
        cur = root;
      } else {
        cur = cur->children[target];
      }
    } else if (cmd.find("dir ") != std::string::npos) {
      auto childName = cmd.substr(4);
      Dir* child = new Dir(cur->path + childName + "/");
      child->parent = cur;
      cur->children[childName] = child;
    } else if (cmd.find("$ ls") == std::string::npos) {
      std::uint32_t size = std::stol(cmd.substr(0, cmd.find(" ")));
      cur->filesize += size;
    }
  }
}

int main() {
  auto commands = readInput();
  Dir* root = new Dir("/");
  runCommands(root, commands);

  std::vector<std::uint32_t> sizes;
  dfs(root, sizes);

  std::sort(sizes.begin(), sizes.end());
  auto free = 70000000 - sizes[sizes.size() - 1];
  auto part1 = 0;
  auto part2 = 0;
  for (auto size : sizes) {
    if (size <= 100000) part1 += size;
    if (free + size >= 30000000 && !part2) {
      part2 = size;
    }
  }
  std::cout << "Part: 1 " << part1 << std::endl;
  std::cout << "Part: 2 " << part2 << std::endl;
}
