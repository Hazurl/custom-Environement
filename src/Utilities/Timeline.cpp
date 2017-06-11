#include "Timeline.h"

using namespace haz;

Timeline::Timeline(long length, std::initializer_list<std::pair<long, int>> user_anchors) : length(length) {
    for(std::pair<long, int> const& p : user_anchors) {
        addAnchor(p.first, p.second);
    }
}

Timeline::~Timeline() {}

void Timeline::addAnchor(long time, int state_to_passed) {
    anchors.insert( { time, { state_to_passed } } );
}

int Timeline::update (long ticks) {
    current_tick = (current_tick + ticks) % length;
    return getState();
}

int Timeline::getState () const {
    int prev_state = anchors.rbegin()->second.state_to_passed;

    for (std::pair<const long, Anchor> const& p : anchors) {
        if (p.first > current_tick)
            return prev_state;
        prev_state = p.second.state_to_passed;
    }

    logger->ERROR("No State !");
    return 0;
}