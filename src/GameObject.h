#pragma once

#include "utils.h"

#include <cstdint>
class GameScreen;

using FlagType = uint32_t;

extern FlagType NO_FLAGS;
extern FlagType PLAYER_FLAG;
extern FlagType ENEMY_FLAG;
extern FlagType MISSILE_FLAG;
extern FlagType ITEM_FLAG;

class GameObject {
public:
    explicit GameObject(GameScreen& game);
    GameObject(const PointI& grid_pos, GameScreen& game);

    virtual void process(float elapsed);

    virtual const PointF& pos() const;
    virtual void set_pos(const PointF& pos);

    virtual const PointI& grid_pos() const;
    virtual void set_grid_pos(const PointI& pos);

    virtual const PointF& velocity() const;
    virtual void set_velocity(const PointF& velocity);
    virtual void set_visible(bool visible);

    bool contain_flags(FlagType flags) const;
    void add_flags(FlagType flags);
    void remove_flags(FlagType flags);
    FlagType get_flags() const;

    virtual ~GameObject();

protected:
    GameScreen& _game;
    bool _visible = false;
    FlagType _flags = NO_FLAGS;

private:
    void install();

    PointF _pos;
    PointF _velocity;

    PointI _grid_pos;
};
