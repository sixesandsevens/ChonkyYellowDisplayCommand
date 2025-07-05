#ifndef ESP323248S035_HPP
#define ESP323248S035_HPP

#include <lvgl.h>
#include <cronos.hpp>
#include <string>

namespace bsp {
using msecu32_t = ::msecu32_t;

class View {
public:
    virtual ~View() = default;
    virtual bool init(lv_obj_t* root) = 0;
    virtual void update(msecu32_t now) = 0;
    virtual std::string title() = 0;
};

template <class Root>
class ESP323248S035C {
public:
    explicit ESP323248S035C(Root& root) : view_(root) {}
    void init() {
        lv_init();
        view_.init(lv_scr_act());
    }
    void update() {
        lv_timer_handler();
        view_.update(msecu32());
    }
private:
    Root& view_;
};

} // namespace bsp

#endif // ESP323248S035_HPP
