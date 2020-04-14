#include "GameScreen.h"

#include "ScreenManager.h"
#include "RenderManager.h"
#include "Person.h"
#include "Enemy.h"
#include "Missile.h"
#include "utils.hpp"

GameScreen::GameScreen(const PointI& pos, const PointI& size) : Screen(pos, size, '.') {
    _person = std::make_unique<Person>(*this);
    _person->set_grid_pos(PointI(width() / 2 + left(), height() / 2 + top()));
}

void GameScreen::process(float elapsed) {
    delete_objects();
    if (rand() % 10 > 8) {
        generate_enemy();
    }
    auto copy_objects = _game_objects;
    for (const auto& object : copy_objects) {
        object->process(elapsed);
    }

    bool damaged = false;

    for (const auto& enemy : _enemies) {
        int distance = dist2(_person->grid_pos(), enemy->grid_pos());
        if (distance < 3) {
            damaged = true;
            _person->take_damage(enemy->damage());
        }
    }

    if (damaged) {
        RenderManager::get().danger();
    } else {
        RenderManager::get().restore();
    }
    if (!_person->is_alive()) {
        RenderManager::get().restore();
        ScreenManager::get().game_over();
    }
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

bool GameScreen::can_pass(const PointI& p, std::unordered_set<GameObject*> ignore) const {
    for (const auto& object : _game_objects) {
        if (ignore.count(object) != 0) {
            continue;
        }
        int distance = dist2(p, object->grid_pos());
        if (distance == 0 || p.x() < left() || p.y() < top() || p.x() >= right() || p.y() >= bottom()) {
            return false;
        }
    }

    return true;
}

void GameScreen::kill(const Missile& missile, const PointI& target) {
    for (auto e_it = _enemies.begin(); e_it != _enemies.end(); ++e_it) {
        if (e_it->get()->grid_pos() == target) {
            auto enemy_ptr = std::move(*e_it);
            _enemies.erase(e_it);
            delete_later(std::move(enemy_ptr));
            break;
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

void GameScreen::launch_missile(const PointI& target) {
    _missiles.push_back(std::make_unique<Missile>(*this));
    _missiles.back()->set_grid_pos(_person->grid_pos());
    _missiles.back()->direct_velocity(PointF(target - _person->grid_pos()));
}

void GameScreen::generate_enemy() {
    float damage = 1;
    char type = 'g';
    if (rand() % 10 > 8) {
        damage = 6;
        type = 'G';
    }
    _enemies.push_back(std::make_unique<Enemy>(*this, damage, type));
    _enemies.back()->set_grid_pos(PointI(rand() % width() + left(), rand() % height() + top()));
}
