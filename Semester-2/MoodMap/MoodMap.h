#ifndef MOODMAP_MOODMAP_H
#define MOODMAP_MOODMAP_H

#endif //MOODMAP_MOODMAP_H

#include <QWidget>
#include <QPaintEvent>
#include "State.h"

class MoodMap : public QWidget {
public:
    explicit MoodMap(std::vector<State>& states, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    std::vector<State> states;
};