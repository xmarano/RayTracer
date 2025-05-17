/*
** EPITECH PROJECT, 2024
** Semestre 4
** File description:
** Observer.hpp
*/

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include <memory>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update() = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify() = 0;
};

class Subject : public ISubject {
public:
    void attach(std::shared_ptr<IObserver> observer) override;
    void detach(std::shared_ptr<IObserver> observer) override;
    void notify() override;

private:
    std::vector<std::shared_ptr<IObserver>> _observers;
};

#endif