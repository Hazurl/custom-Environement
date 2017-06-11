#include "Timeline.h"

using namespace haz;

Timeline::Timeline(long length, std::vector<std::pair<long, int>> user_anchors) : length(length) {
    for(std::pair<long, int> const& p : user_anchors) {
        addAnchor(p.first, p.second);
    }

    updateState();
}

Timeline::~Timeline() {}

void Timeline::addAnchor(long time, int state_to_passed) {
    anchors.insert( { time, { state_to_passed } } );
}

int Timeline::update (long ticks) {
    current_tick = (current_tick + ticks) % length;
    return updateState();
}

int Timeline::reset(long tick) {
    current_tick = tick;
    return updateState();
}

int Timeline::updateState () {
    int prev_state = anchors.rbegin()->second.state_to_passed;

    for (std::pair<const long, Anchor> const& p : anchors) {
        if (p.first > current_tick)
            return state = prev_state;
        prev_state = p.second.state_to_passed;
    }

    logger->ERROR("No State !");
    return state = 0;
}

int Timeline::getState () const {
    return state;
}

bool Timeline::onState (int st) const {
    return state == st;
}