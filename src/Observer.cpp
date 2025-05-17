/*
** EPITECH PROJECT, 2024
** Semestre 4
** File description:
** Observer.cpp
*/

#include "Observer.hpp"
#include <algorithm>

void Subject::attach(std::shared_ptr<IObserver> observer) {
    _observers.push_back(observer);
}

void Subject::detach(std::shared_ptr<IObserver> observer) {
    _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
}

void Subject::notify() {
    for (const auto& observer : _observers) {
        if (observer) observer->update();
    }
}