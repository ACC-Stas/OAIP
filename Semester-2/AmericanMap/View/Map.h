#ifndef MAP_H
#define MAP_H
#include <vector>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QMap>
#include <QRegularExpression>
using namespace std;

struct Point {
    double x;
    double y;
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }
};

struct State {
    std::vector<std::vector<Point>> coords;
    double negativity;
    QList<QPolygonF> polygons;
    std::string name;
    State() {
        name = "";
        coords = vector<std::vector<Point>>(1);
    }
};


class Map : public QWidget {
    Q_OBJECT

public:
    Map(QWidget *parent = nullptr);
    ~Map();
private:
    std::vector<State> usStates;
    double offsetX = 170;
    double offsetY = 100;
    double scale = 7;
    void printNegativity();
    QPainter *painter_;
    QFile file_;
    QMap<QString, double> map_;
    void coloring();
    void getSentiments();
    void drawArea() const;
    void getArea();
    void paintEvent(QPaintEvent*);
};

#endif MAP_H
