#include "Map.h"
#include "../libs/include/rapidjson/document.h"
#include "../libs/include/rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <QPainter>
#include <unordered_map>

#include <QThread>
using namespace rapidjson;
using namespace std;


std::vector<State> decode() {
    ifstream ifs("../resources/states.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    assert(d.HasMember("WA"));
    vector<State> ans;
    int count = 0;
    for (Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
        State state;
        state.name = itr->name.GetString();
        const Value& arr = itr->value.GetArray();
        if (arr.Begin()->Begin()->Begin()->IsArray()) {
            count = -1;
            for (Value::ConstValueIterator islands = arr.Begin(); islands != arr.End(); ++islands) {
                state.coords.emplace_back();
                count++;
                for (Value::ConstValueIterator states = islands->Begin()->Begin(); states != islands->Begin()->End(); states++) {
                    const Value& coords = states->GetArray();
                    state.coords[count].push_back(Point(coords[0].GetDouble(), coords[1].GetDouble()));
                }
            }
        } else {
            state.coords.emplace_back();
            for (Value::ConstValueIterator states = arr.Begin()->Begin(); states != arr.Begin()->End(); states++) {
                const Value& coords = states->GetArray();
                state.coords[0].push_back(Point(coords[0].GetDouble(), coords[1].GetDouble()));
            }
        }
        ans.push_back(state);
    }
    return ans;
}

Map::Map(QWidget *parent) : QWidget(parent) {
    usStates = decode();
    resize(1000, 750);
    setWindowTitle(tr("Colored USA map"));
    getArea();
    getSentiments();
    coloring();
    printNegativity();
}

void Map::getSentiments() {
    QFile* dictionary = new QFile("../resources/sentiments.csv");
    dictionary->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(dictionary);
    while (!in.atEnd())
    {
        auto line = QString(in.readLine());
        auto pair = line.trimmed().split(QLatin1Char(','));
        map_.insert(pair.first(), pair.last().toDouble());
    }
    dictionary->close();
    delete dictionary;
}

void Map::getArea() {
    for (auto& state : usStates) {
        for (const auto& differentCoords : state.coords) {
            QPolygonF polygon;
            for (auto coords : differentCoords) {
                polygon << QPointF((coords.x + offsetX) * scale, (offsetY - coords.y) * scale);
            }
            state.polygons.push_back(polygon);

        }
    }
}

void Map::coloring() {
    QPointF tweetPoint;
    QFile *tweets = new QFile("../resources/tweets2011.txt");
    tweets->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(tweets);
    QRegularExpression coords(R"(.{1}(-?\d*\.?\d+).{2}(-?\d*.?\d+))");
    QRegularExpression time(R"(\d{2}:\d{2}:\d{2})");
    while (!in.atEnd()) {
        auto line = QString(in.readLine() + "\n");
        auto matchCoords = coords.match(line);
        if (matchCoords.hasMatch()) {
            tweetPoint = QPointF((offsetX + matchCoords.captured().split('[').last().split(", ").last().toDouble()) * scale,
                                 (offsetY - matchCoords.captured().split('[').last().split(", ").first().toDouble()) * scale);
            for (auto& state: usStates) {
                for (auto& polygon : state.polygons) {
                    if (polygon.containsPoint(tweetPoint, Qt::OddEvenFill)) {
                        auto matchTime = time.match(line);
                        auto tweet = line.remove(0, matchTime.capturedEnd()).trimmed().toLower().split(
                                QRegularExpression("\\s+"));
                        for (const auto& word : tweet) {
                            state.negativity += map_[word];
                        }
                    }
                }
            }
        }
    }
    tweets->close();
    delete tweets;
}

void Map::drawArea() const {
    painter_->setPen(Qt::black);
    for (const auto& state : usStates) {
        if (state.negativity >= 0) {
            painter_->setBrush(QColor(qRgb(abs(255 - state.negativity), 255, 0)));
        } else {
            painter_->setBrush(QColor(qRgb(abs(state.negativity), 0, 0)));
        }
        for (const auto& polygon : state.polygons) {
            painter_->drawPolygon(polygon);
        }
    }
}

void Map::paintEvent(QPaintEvent*) {
    painter_ = new QPainter(this);
    drawArea();
    delete painter_;
}

Map::~Map() {
    if (painter_)
        delete painter_;
}

void Map::printNegativity() {
    for (auto state : usStates) {
        std::cout << state.name << " " << state.negativity << "\n";
    }
}







