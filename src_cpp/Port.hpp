#pragma once

#include "Dock.hpp"
#include <string>
#include <memory>

namespace seaport
{
    class BaseShip;

    class Port
    {
    private:
        static constexpr auto DEFAULT_PORT_NAME = "Standard Port";

        std::string m_portName{ DEFAULT_PORT_NAME };
        Dock m_mainDock{};

    public:
        Port();
        Port(const std::string& portName, int dockNumber, double dockDepth);
        ~Port();

        [[nodiscard]] std::string GetPortName() const
        {
            return m_portName;
        }

        void SetPortName(std::string_view newName)
        {
            m_portName = newName;
        }

        void OpenPort();
        void InspectPort() const;
        void RegisterShip(const BaseShip& ship) const;

        void DockShipInPort(std::shared_ptr<BaseShip> ship);
        void FreePortDock();
    };

}