#include "Item.h"

#include "GameScreen.h"

#include <curses.h>

Item::Item(GameScreen& game_screen, int healing_value)
    : GameObject(game_screen), Renderable(game_screen), _healing_value(healing_value)
{
    add_flags(ITEM_FLAG);
}

void Item::render() const {
    if (!_visible) {
        return;
    }
    auto theme = COLOR_PAIR(104);
    if (is_danger_theme()) {
        theme = COLOR_PAIR(204);
    }
    mvaddch(grid_pos().y(), grid_pos().x(), '+' | theme);
}

void Item::process(float elapsed) {
    int distance = dist2(_game.player_pos(), grid_pos());
    if (distance < 1) {
        _game.heal_player(_healing_value);
        _game.remove_item(*this);
    }
}

void Item::set_visible(bool visible) {
    _visible |= visible;
}
