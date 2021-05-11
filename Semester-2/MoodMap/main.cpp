#include <QApplication>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <unordered_map>
#include <regex>
#include <cstdio>
#include "MoodMap.h"
#include "State.h"

#define ENLARGMENT 14 //used to convert coordinates from json to widget coordinates
#define XINDENT 2600  //y coordinates need -1*
#define YINDENT 1100  //tweets coordinates - swap x and y

void loadStates(std::vector<State>& states);
void loadWordsValues(std::unordered_map<std::string, double>& wordsValues);
void loadSentiments(std::vector<State>& states, std::unordered_map<std::string, double>& wordsValues);

int main(int argc, char *argv[]) {
    std::vector<State> states;
    loadStates(states);
    std::unordered_map<std::string,double> wordsValues;
    loadWordsValues(wordsValues);
    loadSentiments(states,wordsValues);
    QApplication app(argc, argv);
    MoodMap window(states);
    window.show();
    return QApplication::exec();
}

void loadStates(std::vector<State>& states) {
    std::ifstream ifs("../resources/states.json");
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document d;
    d.ParseStream(isw);
    ifs.close();
    for(auto it = d.MemberBegin(); it != d.MemberEnd(); it++) { //first - name, second - groupOfPolygons
        State st(it->name.GetString());                   //third - polygon/polygonDots, forth - polygonDots/no
        if(it->value.Begin()->Begin()->Begin()->IsArray()){
            for (auto polygons = it->value.Begin(); polygons != it->value.End(); polygons++) {
                QPolygon polygon;
                for(auto polygonDots = polygons->Begin(); polygonDots != polygons->End(); polygonDots++){
                    for(auto dot = polygonDots->Begin(); dot != polygonDots->End(); dot++){
                        polygon << QPoint((dot[0][0].GetDouble()*ENLARGMENT + XINDENT),(dot[0][1].GetDouble()) * (-ENLARGMENT) + YINDENT);
                    }
                }
                st.polygons.push_back(polygon);
            }
        } else { //only on polygon
            QPolygon polygon;
            for(auto polygonDots = it->value.Begin(); polygonDots != it->value.End(); polygonDots++){
                for(auto dot = polygonDots->Begin(); dot != polygonDots->End(); dot++) {
                    polygon << QPoint((dot[0][0].GetDouble()*ENLARGMENT + XINDENT),(dot[0][1].GetDouble()) * (-ENLARGMENT) + YINDENT);
                }
            }
            st.polygons.push_back(polygon);
        }
        states.push_back(st);
    }
}

void loadWordsValues(std::unordered_map<std::string, double>& wordsValues) {
    std::ifstream fin("../resources/sentiments.csv");
    std::string line;
    std::regex rx(R"(^([\d\w\s]+),\s*(-?[.\d]+))");
    std::cmatch result;
    while(std::getline(fin,line)) {
        if(std::regex_search(line.c_str(),result,rx)) {
            wordsValues[result[1].str()] = std::stod(result[2].str());
        }
    }
    fin.close();
}

void loadSentiments(std::vector<State>& states, std::unordered_map<std::string, double>& wordsValues) {
    FILE* fp;
    fp = fopen("../resources/tweets.txt","rb");
    if(fp == NULL) {
        return;
    }
    std::string line;
    line.resize(1024);
    std::cmatch result;
    std::regex rx(R"(\[(-?\d+.?\d*)[,\s]+(-?\d+.?\d*)\][_\s]+\d{4}-\d{2}-\d{2}\s+\d{2}:\d{2}:\d{2}\s+([\d\w\W\s]+))");
    std::regex oneWord(R"((\w+))");
    std::regex twoWords(R"((\w+)[\W]+(\w+))");
    std::regex threeWords(R"((\w+)[\W]+(\w+)[\W]+(\w+))");
    double x;
    double y;
    std::string words;
    QPoint point(0,0);
    while(fgets(line.data(),line.size(),fp)) {
        if(std::regex_search(line.c_str(),result,rx)) {
            y = std::stod(result[1].str()) * (-ENLARGMENT) + YINDENT;
            x = std::stod(result[2].str()) * ENLARGMENT + XINDENT;
            words = result[3].str();
            for(auto& state : states) {
                for(auto& polygon : state.polygons) {
                    point.setX(x);
                    point.setY(y);
                    if(polygon.containsPoint(point, Qt::OddEvenFill)) {
                        for (auto it = std::sregex_iterator(words.cbegin(), words.cend(), oneWord); it != std::sregex_iterator(); ++it) {
                            auto wordValue = wordsValues.find(it->str());
                            if(wordValue != wordsValues.end()){
                                state.negativity += wordValue->second;
                            }
                        }
                        for (auto it = std::sregex_iterator(words.cbegin(), words.cend(), twoWords); it != std::sregex_iterator(); ++it) {
                            auto wordValue = wordsValues.find(it->str());
                            if(wordValue != wordsValues.end()){
                                state.negativity += wordValue->second;
                            }
                        }
                        for (auto it = std::sregex_iterator(words.cbegin(), words.cend(), threeWords); it != std::sregex_iterator(); ++it) {
                            auto wordValue = wordsValues.find(it->str());
                            if(wordValue != wordsValues.end()){
                                state.negativity += wordValue->second;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}
