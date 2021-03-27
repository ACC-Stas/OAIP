#include <iostream>

struct parts {
    int modelNumber;
    int partNumber;
    double cost;
};

int main()
{
    parts part1, part2, part3;
    part1.modelNumber = 84;
    part1.partNumber = 176;
    part1.cost = 44.15;
    part2 = { 65,5,32.16 };
    part3 = part2;
    std::cout << part1.modelNumber << " " << part1.partNumber << " " << part1.cost << std::endl;
    std::cout << part2.modelNumber << " " << part2.partNumber << " " << part2.cost << std::endl;
    std::cout << part3.modelNumber << " " << part3.partNumber << " " << part3.cost << std::endl;
}
