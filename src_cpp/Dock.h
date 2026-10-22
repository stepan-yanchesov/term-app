#pragma once

#include "Ship.h"
#include <string>

namespace seaport
{

    class Dock
    {
    private:
        int m_dockNumber{ 0 };
        double m_maxDepth{ 0.0 };
        Ship* m_currentShip{ nullptr };

    public:
        Dock();
        Dock(int dockNumber, double maxDepth);
        ~Dock();

        [[nodiscard]] int GetDockNumber() const
        {
            return m_dockNumber;
        }

        [[nodiscard]] double GetMaxDepth() const
        {
            return m_maxDepth;
        }

        [[nodiscard]] bool IsOccupied() const
        {
            return m_currentShip != nullptr;
        }

        [[nodiscard]] std::string GetOccupiedShipName() const;

        void MoorShip(Ship* ship);
        void ReleaseShip();
    };
}