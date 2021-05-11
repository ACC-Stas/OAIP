#include "State.h"

#include <utility>

State::State(std::string name, double negativity) {
    this->name = std::move(name);
    this->negativity = negativity;
}
