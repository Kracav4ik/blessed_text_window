#include "ObjectManager.h"

template<typename T>
void ObjectManager<T>::add_object(T* object) {
    _objects.emplace_back(object);
}

template<typename T>
void ObjectManager<T>::remove_object(T* object) {
    for (auto it = _objects.begin(); it != _objects.end(); ++it) {
        if (*it == object) {
            _objects.erase(it);
            break;
        }
    }
}
