#include "dock.h"
#include <iostream>

namespace seaport
{

    Dock::Dock() = default;

    Dock::Dock(int dockNumber, double maxDepth)
        : m_dockNumber{ dockNumber }
        , m_maxDepth{ maxDepth }
    {
    }

    Dock::~Dock()
    {
        std::cout << "[Деструктор] Причал №" << m_dockNumber << " уничтожен.\n";
    }

    bool Dock::IsOccupied() const
    {
        return !m_currentShip.expired();
    }

    std::string Dock::GetOccupiedShipName() const
    {
        if (auto shipSp = m_currentShip.lock())
        {
            return shipSp->GetName();
        }
        return "Свободно";
    }

    void Dock::MoorShip(std::shared_ptr<Ship> ship)
    {
        if (IsOccupied())
        {
            std::cout << "[Отказ] Причал №" << m_dockNumber << " уже занят другим судном!\n";
            return;
        }

        if (!ship) return;

        m_currentShip = ship;
        std::cout << "[Успех] Корабль \"" << ship->GetName() << "\" пришвартован к причалу №" << m_dockNumber << ".\n";
    }

    void Dock::ReleaseShip()
    {
        if (!IsOccupied())
        {
            std::cout << "[Предупреждение] Причал №" << m_dockNumber << " и так пуст.\n";
            return;
        }

        if (auto shipSp = m_currentShip.lock())
        {
            std::cout << "[Действие] Корабль \"" << shipSp->GetName() << "\" отошел от причала №" << m_dockNumber << ".\n";
        }
        m_currentShip.reset();
    }

}