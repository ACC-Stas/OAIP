#pragma once
#ifndef MOODMAP_STATES_H
#define MOODMAP_STATES_H

#endif //MOODMAP_STATES_H

#include <QPolygon>
#include <string>
#include <vector>

struct State {
public:
    explicit State(std::string name = "Unnamed", double negativity = 0);
    std::string name;
    std::vector<QPolygon> polygons;
    double negativity;
};
