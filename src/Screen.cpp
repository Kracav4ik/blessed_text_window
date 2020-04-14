#include "Screen.h"

#include "ScreenManager.h"
#include "ObjectManager.hpp"
#include "Renderable.h"

#include <curses.h>

Screen::Screen(const PointI& pos, const PointI& size, char bgSing) : _bg_sing(bgSing), _pos(pos), _size(size) {
    ScreenManager::get().add_object(this);
}

void Screen::add_renderable(Renderable* object) {
    _renderables.emplace_back(object);
}

void Screen::remove_renderable(Renderable* object) {
    for (auto it = _renderables.begin(); it != _renderables.end(); ++it) {
        if (*it == object) {
            _renderables.erase(it);
            break;
        }
    }
}

void Screen::render() const {
    for (int x = left(); x < right(); ++x) {
        for (int y = top(); y < bottom(); ++y) {
            mvaddch(y, x, _bg_sing);
        }
    }
    for (const auto& renderable : _renderables) {
        renderable->render();
    }
}

Screen::~Screen() {
    ScreenManager::get().remove_object(this);
}

int Screen::top() const {
    return _pos.y();
}

int Screen::bottom() const {
    return _pos.y() + _size.y();
}

int Screen::left() const {
    return _pos.x();
}

int Screen::right() const {
    return _pos.x() + _size.x();
}

int Screen::width() const {
    return _size.x();
}

int Screen::height() const {
    return _size.y();
}
