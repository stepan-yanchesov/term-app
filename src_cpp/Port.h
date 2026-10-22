#pragma once

#include "dock.h"
#include "ship.h"
#include <string>

namespace seaport
{

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

        void OpenPort();
        void InspectPort() const;

        void DockShipInPort(Ship* ship);
        void FreePortDock();
    };

}