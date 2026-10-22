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

    std::string Dock::GetOccupiedShipName() const
    {
        if (m_currentShip == nullptr)
        {
            return "Свободно";
        }
        return std::string(m_currentShip->GetName());
    }

    void Dock::MoorShip(Ship* ship)
    {
        if (m_currentShip != nullptr)
        {
            std::cout << "[Отказ] Причал №" << m_dockNumber << " уже занят другим судном!\n";
            return;
        }

        m_currentShip = ship;
        std::cout << "[Успех] Корабль \"" << ship->GetName() << "\" пришвартован к причалу №" << m_dockNumber << ".\n";
    }

    void Dock::ReleaseShip()
    {
        if (m_currentShip == nullptr)
        {
            std::cout << "[Предупреждение] Причал №" << m_dockNumber << " и так пуст.\n";
            return;
        }

        std::cout << "[Действие] Корабль \"" << m_currentShip->GetName() << "\" отошел от причала №" << m_dockNumber << ".\n";
        m_currentShip = nullptr;
    }

}