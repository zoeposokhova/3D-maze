#include "../include/maze.h"
#include <iostream>

int main() {

    for (int i = 0; i < 5; ++i) {
        Maze test(5, 5);
        test.generate();
        test.minimap(1.5, 1.5, 0.0);
        std::cout << "\n";
    }
    return 0;
}