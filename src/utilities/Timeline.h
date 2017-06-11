#ifndef __TIMELINE_H__
#define __TIMELINE_H__

#include <logger.h>
#include <map>
#include <vector>

namespace haz {

class Timeline {
public:
    Timeline (long length, std::vector<std::pair<long, int>> user_anchors);
    ~Timeline ();

    int getState () const;
    int update (long ticks);
    int reset(long tick = 0);
    bool onState (int st) const;

private:
    Logger* logger = &Logger::get("#.Timeline");

    void addAnchor(long time, int state_to_passed);
    int updateState ();

    struct Anchor {
        int state_to_passed;
    };

    long length, current_tick = 0;
    int state = 0;
    // time -> anchor
    std::map<long, Anchor> anchors = {};

};

} // namespace haz

#endif