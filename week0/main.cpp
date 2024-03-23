#include <iostream>
#include <vector>

class Integers {
private:
    std::vector<int> data;

public:
    void insert(int number) {
        if (!contains(number)) {
            data.push_back(number);
        }
    }

    bool contains(int number) {
        for (int elem : data) {
            if (elem == number) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Integers numbers;
    bool queryMode = false; 
    int num;
    int count = 0; 

    std::cout << "Enter non-negative integers to insert, negative to switch mode, CTRL+C or EOF to quit.\n";

    while (true) {
        if (std::cin >> num) {
            if (num < 0) {
                queryMode = !queryMode;
                std::cout << "Switched to " << (queryMode ? "query" : "insert") << " mode.\n";
            } else if (queryMode) {
                if (numbers.contains(num)) {
                    std::cout << num << " is in the set.\n";
                } else {
                    std::cout << num << " is not in the set.\n";
                }
            } else {
                numbers.insert(num);
                std::cout << "#" << count << " inserted.\n";
                count++;
            }
        } else {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');\
            std::cout << "Invalid input. Please enter an integer.\n";
        }
    }

    return 0;
}
