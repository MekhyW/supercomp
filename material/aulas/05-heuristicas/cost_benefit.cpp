#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

struct Item {
    double size;
    double value;
};

void readInput(const char *filename, double &backpack_capacity, vector<Item> &items) {
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }
    int n;
    input >> n;
    input >> backpack_capacity;
    for (int i = 0; i < n; i++) {
        Item it;
        input >> it.size >> it.value;
        items.push_back(it);
    }
    input.close();
}

bool compareItems(const Item &a, const Item &b) {
    return a.value / a.size > b.value / b.size;
}

void fillBackpack(const vector<Item> &items, double backpack_capacity, vector<Item> &selected_items, double &backpack_value, double &backpack_size) {
    backpack_size = 0;
    backpack_value = 0;
    for (const auto &item : items) {
        if (backpack_size + item.size <= backpack_capacity) {
            backpack_size += item.size;
            backpack_value += item.value;
            selected_items.push_back(item);
        } else {
            break;
        }
    }
}

void printBackpack(const vector<Item> &selected_items, double backpack_value, double backpack_size, double backpack_capacity) {
    cout << "Backpack value: " << backpack_value << endl;
    cout << "Backpack used size: " << backpack_size << " out of " << backpack_capacity << endl;
    cout << "Selected items: " << endl;
    for (int i = 0; i < selected_items.size(); i++) {
        cout << "Item " << i << ": size = " << selected_items[i].size << ", value = " << selected_items[i].value << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    double backpack_capacity;
    vector<Item> items;
    vector<Item> selected_items;
    readInput(argv[1], backpack_capacity, items);
    sort(items.begin(), items.end(), compareItems);
    double backpack_size, backpack_value;
    fillBackpack(items, backpack_capacity, selected_items, backpack_value, backpack_size);
    printBackpack(selected_items, backpack_value, backpack_size, backpack_capacity);
    return 0;
}
