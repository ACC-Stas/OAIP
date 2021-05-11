#include "MoodMap.h"
#include <Qpainter>
#include <QpainterPath>

MoodMap::MoodMap(std::vector<State>& states, QWidget *parent) : QWidget(parent) {
    this->states = states;
    resize(1920,1080);
    setWindowTitle("Mood map of US");
}

void MoodMap::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    int negativity;
    for(auto& state : states) {
        if(state.negativity >= 0) {
            if (state.negativity > 255){
                negativity = 255;
            } else {
                negativity = state.negativity;
            }
            painter.setBrush(QColor(qRgb(255 - negativity, 255, 0)));
        } else {
            if (state.negativity < -255){
                negativity = 255;
            } else {
                negativity = -1*state.negativity;
            }
            painter.setBrush(QColor(qRgb(negativity, 0, 0)));
        }
        for(auto& polygon : state.polygons){
            painter.drawPolygon(polygon);
        }
    }
    //QPolygon polygon = states[0].polygons[0];
    //polygon << QPoint(100,100) << QPoint(150,150) << QPoint(150,100) << QPoint(100,150);
    //painter.drawPolygon(polygon);
}

