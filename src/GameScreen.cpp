#include "GameScreen.h"

#include "HUD.h"
#include "Item.h"
#include "ScreenManager.h"
#include "RenderManager.h"
#include "Person.h"
#include "Enemy.h"
#include "Missile.h"
#include "utils.hpp"

#include <ctime>

std::vector<std::string> greeting_list = {
        "Hello, adventurer, i need your aid. Please kill some goblins in my garden. Good luck, adventurer!",
        "WELCOME BACK TO BROOOOOOOONZE LEEEAAAAAG.... another game of btw",
        "An easy wind is going and you feel that life is rife with new experiences to make!",
        "You sense a certain tension.",
        "You sense a certain tension. You sense a certain tension. You sense a certain tension. You sense a certain tension.",
};

GameScreen::GameScreen(const PointI& pos, const PointI& size) : Screen(pos, size, '.') {
    _person = std::make_unique<Person>(*this);
    _person->set_grid_pos(PointI(width() / 2 + left(), height() / 2 + top()));
    srand(std::time(nullptr));
    HUD::get().set_text(greeting_list[rand() % greeting_list.size()]);
}

void GameScreen::process(float elapsed) {
    delete_objects();
    if (rand() % 10 > 8) {
        generate_enemy();
    }
    auto copy_objects = _game_objects;
    for (const auto& object : copy_objects) {
        auto distance2 = dist2(player_pos(), object->grid_pos());
        auto vision_value2 = _person->vision_value() * _person->vision_value();
        object->set_visible(distance2 < vision_value2);
        object->process(elapsed);
    }

    if (_person->was_damaged()) {
        RenderManager::get().danger();
    } else {
        RenderManager::get().restore();
    }
    if (!_person->is_alive()) {
        RenderManager::get().restore();
        ScreenManager::get().game_over();
    }

    HUD::get().process(elapsed);
}

void GameScreen::render() const {
    fill_bg(_person->grid_pos(), _person->vision_value());
    Screen::render();
    HUD::get().render(*this);
}

void GameScreen::add_game_object(GameObject* object) {
    _game_objects.emplace_back(object);
}

void GameScreen::remove_game_object(GameObject* object) {
    for (auto it = _game_objects.begin(); it != _game_objects.end(); ++it) {
        if (*it == object) {
            _game_objects.erase(it);
            break;
        }
    }
}

void GameScreen::delete_later(std::unique_ptr<GameObject>&& object) {
    _to_delete.push_back(std::move(object));
}

void GameScreen::delete_objects() {
    std::vector<std::unique_ptr<GameObject>> to_delete;
    std::swap(to_delete, _to_delete);
}

PointI GameScreen::player_pos() {
    return _person->grid_pos();
}

int GameScreen::player_hp() const {
    return _person->health_points();
}

bool GameScreen::can_pass(const PointI& p, FlagType flags) const {
    for (const auto& object : _game_objects) {
        if (!object->contain_flags(flags)) {
            continue;
        }
        int distance = dist2(p, object->grid_pos());
        if (distance == 0 || p.x() < left() || p.y() < top() || p.x() >= right() || p.y() >= bottom()) {
            return false;
        }
    }

    return true;
}

void GameScreen::damage_enemy(const Missile& missile, const PointI& target) {
    for (auto e_it = _enemies.begin(); e_it != _enemies.end(); ++e_it) {
        if (e_it->get()->grid_pos() == target) {
            e_it->get()->take_damage(missile.damage());
            if (e_it->get()->health_points() <= 0) {
                if (rand() % 100 > 90) {
                    _items.push_back(std::make_unique<Item>(*this, rand() % 6 + 1));
                    _items.back()->set_grid_pos(target);
                }
                auto enemy_ptr = std::move(*e_it);
                _enemies.erase(e_it);
                delete_later(std::move(enemy_ptr));
                break;
            }
        }
    }

    for (auto m_it = _missiles.begin(); m_it != _missiles.end(); ++m_it) {
        if (m_it->get() == &missile) {
            auto missile_ptr = std::move(*m_it);
            _missiles.erase(m_it);
            delete_later(std::move(missile_ptr));
            break;
        }
    }
}

void GameScreen::damage_player(int damage) {
    _person->take_damage(damage);
}

void GameScreen::heal_player(int value) {
    _person->heal(value);
}

void GameScreen::launch_missile(const PointI& target) {
    _missiles.push_back(std::make_unique<Missile>(*this, 3));
    _missiles.back()->set_grid_pos(_person->grid_pos());
    _missiles.back()->direct_velocity(PointF(target - _person->grid_pos()));
}

void GameScreen::generate_enemy() {
    int damage = 1;
    int hp = 3;
    char type = 'g';
    if (rand() % 10 > 8) {
        damage = 6;
        hp = 6;
        type = 'G';
    }
    _enemies.push_back(std::make_unique<Enemy>(*this, damage, hp, type));
    _enemies.back()->set_grid_pos(PointI(rand() % width() + left(), rand() % height() + top()));
}

void GameScreen::remove_item(const Item& item) {
    for (auto i_it = _items.begin(); i_it != _items.end(); ++i_it) {
        if (i_it->get() == &item) {
            auto item_ptr = std::move(*i_it);
            _items.erase(i_it);
            delete_later(std::move(item_ptr));
            break;
        }
    }
}
