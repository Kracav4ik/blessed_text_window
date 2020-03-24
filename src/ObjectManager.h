#pragma once

#include <vector>

template <typename T>
class ObjectManager {
friend T;
protected:
    std::vector<T*> _objects;

private:
    void add_object(T* object);
    void remove_object(T* object);
};
