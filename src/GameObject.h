#pragma once

class GameObject {
public:
    GameObject();

    virtual void process(float elapsed) = 0;

    virtual ~GameObject();
};
