#include "Timeline.h"

using namespace haz;

Timeline::Timeline(long length, std::vector<std::pair<long, int>> user_anchors, float speed) : length(length), speed(speed) {
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
    current_tick = static_cast<long>(current_tick + ticks * speed) % length;
    return updateState();
}

int Timeline::reset(long tick) {
    current_tick = tick;
    return updateState();
}

int Timeline::updateState () {
    if (anchors.empty()) {
        logger->ERROR("No State !");
        return state = 0;
    } else if (anchors.size() == 1) {
        logger->WARN("Only one state");
        return anchors.begin()->second.state_to_passed;
    }

    for (auto it = anchors.rbegin(); it != anchors.rend(); ++it)
        if (it->first < current_tick)
            return state = it->second.state_to_passed;

    return state = anchors.rbegin()->second.state_to_passed;
}

int Timeline::getState () const {
    return state;
}

void Timeline::setSpeed (int sp) {
    speed = sp;
}

bool Timeline::onState (int st) const {
    return state == st;
}