#include "Port.hpp"
#include "BaseShip.hpp"
#include <iostream>

namespace seaport
{

    Port::Port() = default;

    Port::Port(const std::string& portName, int dockNumber, double dockDepth)
        : m_portName{ portName }
        , m_mainDock{ dockNumber, dockDepth }
    {
        if (m_portName.empty())
        {
            m_portName = DEFAULT_PORT_NAME;
        }
    }

    Port::~Port()
    {
        std::cout << "[Деструктор] Порт \"" << m_portName << "\" прекратил работу.\n";
    }

    void Port::OpenPort()
    {
        std::cout << "[Действие] Морской порт \"" << m_portName << "\" официально открыл навигацию.\n";
    }

    void Port::InspectPort() const
    {
        std::cout << "[Статус Порта] Порт: " << m_portName
            << " | Причал №" << m_mainDock.GetDockNumber()
            << " | Статус: " << m_mainDock.GetOccupiedShipName() << "\n";
    }

    void Port::RegisterShip(const BaseShip& ship) const
    {
        std::cout << "[Регистрация] Порт \"" << m_portName << "\" принял уведомление от судна: "
            << ship.Describe() << "\n";
    }

    void Port::DockShipInPort(std::shared_ptr<BaseShip> ship)
    {
        std::cout << "[Запрос] Порт \"" << m_portName << "\" перенаправляет корабль на причал...\n";
        m_mainDock.MoorShip(std::move(ship));
    }

    void Port::FreePortDock()
    {
        m_mainDock.ReleaseShip();
    }

}