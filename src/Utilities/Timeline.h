#ifndef __TIMELINE_H__
#define __TIMELINE_H__

#include <logger.h>
#include <map>
#include <initializer_list>

namespace haz {

class Timeline {
public:
    Timeline (long length, std::initializer_list<std::pair<long, int>> user_anchors);
    ~Timeline ();

    int getState () const;
    int update (long ticks);

private:
    Logger* logger = &Logger::get("#.Timeline");

    void addAnchor(long time, int state_to_passed);

    struct Anchor {
        int state_to_passed;
    };

    long length, current_tick = 0;
    // time -> anchor
    std::map<long, Anchor> anchors = {};

};

} // namespace haz

#endif