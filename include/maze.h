//
// Created by zoe on 6/25/26.
//

#ifndef INC_3D_MAZE_MAZE_H
#define INC_3D_MAZE_MAZE_H

#pragma once
#include <string>
#include <vector>

struct dsu {
    std::vector<int> par;
    dsu(int n);
    int f(int x);
    bool u(int x, int y);
};

struct wall {
    int c1, c2;
    int x, y;
};

class Maze {
private:
    int height, width;
    std::vector<std::vector<int>> grid;
public:
    Maze(int h, int w);
    void generate();
    bool isWall(int x, int y) const;
    std::vector<std::vector<int>>& getGrid() const;
    void minimap(double x, double y, double viewAngle) const;
};


#endif //INC_3D_MAZE_MAZE_H