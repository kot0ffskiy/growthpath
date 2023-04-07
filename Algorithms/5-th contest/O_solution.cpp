#include <iostream>
#include <list>
#include <vector>

class HashTable {
 private:
  std::vector<std::list<int>> table_;

  int size_;

  [[nodiscard]] int Hash(int key) const { return key % size_; }
  void Resize() {
    std::vector<std::list<int>> new_table(size_ * 2);
    for (int i = 0; i < size_; i++) {
      for (int& element : table_[i]) {
        int index = Hash(element);
        new_table[index].push_back(element);
      }
    }
    table_ = new_table;
    size_ *= 2;
  }

 public:
  HashTable(int size) {
    this->size_ = size;
    table_.resize(size);
  }

  void Insert(int key) {
    int index = Hash(key);
    for (int& elem : table_[index]) {
      if (elem == key) {
        return;
      }
    }
    table_[index].push_back(key);
    const int kMax = 5;
    if (table_[index].size() > kMax) {
      Resize();
    }
  }

  void Search(int key) {
    int index = Hash(key);
    for (int& element : table_[index]) {
      if (element == key) {
        std::cout << "YES" << std::endl;
        return;
      }
    }
    std::cout << "NO" << std::endl;
  }

  void Remove(int key) {
    int index = Hash(key);
    for (auto iterator = table_[index].begin(); iterator != table_[index].end();
         iterator++) {
      if (*iterator == key) {
        table_[index].erase(iterator);
        return;
      }
    }
  }
};

int main() {
  int query_count = 0;
  std::cin >> query_count;
  HashTable table(query_count);
  for (int i = 0; i < query_count; i++) {
    std::string query;
    int key = 0;
    std::cin >> query >> key;
    if (query == "+") {
      table.Insert(key);
    } else if (query == "-") {
      table.Remove(key);
    } else if (query == "?") {
      table.Search(key);
    }
  }
}