#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {3, 1, 2, 3, 2, 1};

    // Call unique without sorting
    auto end_unique = std::unique(v.begin(), v.end());

    std::cout << "After unique (no sort): ";
    for (auto it = v.begin(); it != end_unique; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\nContainer size remains: " << v.size() << std::endl;

    // Note: elements after end_unique are unspecified

    // Now let's do it correctly: sort first
    std::vector<int> v2 = {3, 1, 2, 3, 2, 1};
    std::sort(v2.begin(), v2.end());

    auto end_unique2 = std::unique(v2.begin(), v2.end());
    v2.erase(end_unique2, v2.end()); // erase duplicates

    std::cout << "After sort + unique + erase: ";
    for (int n : v2) {
        std::cout << n << ' ';
    }
    std::cout << "\nContainer size is now: " << v2.size() << std::endl;

    return 0;
}

