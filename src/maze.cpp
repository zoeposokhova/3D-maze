//
// Created by zoe on 6/25/26.
//

#include "maze.h"
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>

dsu::dsu(int n) {
    for (int i = 0; i < n; ++i) {
        par.push_back(i);
    }
}

int dsu::f(int x) {
    if (par[x] == x) return x;
    return par[x] = f(par[x]);
}

bool dsu::u(int x, int y) {
    x = f(x);
    y = f(y);
    if (x != y) {
        par[x] = y;
        return 1;
    }
    return 0;
}

Maze::Maze(int h, int w) {
    height = h;
    width = w;
    grid.resize(2*h+1, std::vector<int>(2*w+1, 1));
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            grid[2*x+1][2*y+1] = 0;
        }
    }
}

bool Maze::isWall(int x, int y) const {
    if (x < 0 || x >= grid.size() ||
        y < 0 || y >= grid[0].size()) return 1;
    return grid[x][y] == 1;
}

void Maze::generate() {
    std::vector<wall> allWalls;
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            int cell = x * width + y;
            //v
            if (x + 1 < height) {
                int nextCell = (x+1) * width + y;
                allWalls.push_back({cell, nextCell, 2*x+2, 2*y+1});
            }
            //>
            if (y + 1 < width) {
                int nextCell = x * width + y+1;
                allWalls.push_back({cell, nextCell, 2*x+1, 2*y+2});
            }
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allWalls.begin(), allWalls.end(), g);

    dsu dsu(height * width);

    while (!allWalls.empty()) {
        wall curr = allWalls.back();
        allWalls.pop_back();

        if (dsu.u(curr.c1, curr.c2)) {
            grid[curr.x][curr.y] = 0;
        }
    }

    grid[1][0] = 0;
    grid[2 * height - 1][2 * width] = 0;
}

void Maze::minimap(double x, double y, double viewAngle) const {
    int px = std::floor(x);
    int py = std::floor(y);

    std::string player;
    const double pi = 3.14159265358979323846;
    double angle = fmod(viewAngle, 2*pi);
    if (angle >= 7*pi/4 || angle < pi/4) player = "▶ ";
    else if (angle >= pi/4 && angle < 3*pi/4) player = "▼ ";
    else if (angle >= 3*pi/4 && angle < 5*pi/4) player = "◀ ";
    else if (angle >= 5*pi/4 && angle < 7*pi/4) player = "▲";

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (i == py && j == px) {
                std::cout << player;
            }
            else {
                if (grid[i][j] == 1) {
                    std::cout << "██";
                }
                else {
                    std::cout << "  ";
                }
            }
        }
        std::cout << "\n";
    }
}
