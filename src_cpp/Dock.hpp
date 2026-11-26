#pragma once

#include <string>
#include <memory>

namespace seaport
{
    class BaseShip;

    class Dock
    {
    private:
        int m_dockNumber{ 0 };
        double m_maxDepth{ 0.0 };
        std::weak_ptr<BaseShip> m_currentShip{};

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

        [[nodiscard]] bool IsOccupied() const;


        [[nodiscard]] std::string GetOccupiedShipName() const;

        void MoorShip(std::shared_ptr<BaseShip> ship);
        void ReleaseShip();
    };
}