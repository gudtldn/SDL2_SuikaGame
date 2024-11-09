#include "EventManager.h"
#include "Interfaces/IEventObserver.h"

void EventManager::AddObserver(std::shared_ptr<IEventObserver> observer)
{
    observers.push_back(observer);
}

void EventManager::RemoveObserver(std::shared_ptr<IEventObserver> observer)
{
    observers.erase(
        std::remove(
            observers.begin(),
            observers.end(),
            observer
        ),
        observers.end()
    );
}

void EventManager::NotifyObservers(const SDL_Event& event)
{
    for (const auto& observer : observers)
    {
        observer->OnEvent(event);
    }
}
