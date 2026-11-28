#include "BaseShip.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace seaport
{
    int BaseShip::s_shipCounter = 0;

    BaseShip::BaseShip()
        : m_name("Неизвестное судно"),
        m_displacement(1000.0),
        m_cargoWeight(0.0),
        m_cargoType("Пусто"),
        m_isAtSea(false),
        m_id(++s_shipCounter),
        m_port(std::make_shared<Port>())
    {
        std::cout << "[BaseShip] Конструктор по умолчанию (ID: " << m_id << ")\n";
    }

    BaseShip::BaseShip(const std::string& name, double displacement, double cargoWeight,
        const std::string& cargoType, std::shared_ptr<Port> port)
        : m_name(name),
        m_displacement(displacement),
        m_cargoWeight(cargoWeight),
        m_cargoType(cargoType),
        m_isAtSea(false),
        m_id(++s_shipCounter),
        m_port(std::move(port))
    {
        if (displacement <= 0)
        {
            throw std::invalid_argument("Водоизмещение должно быть положительным!");
        }
        if (cargoWeight < 0 || cargoWeight > displacement)
        {
            throw std::invalid_argument("Некорректный вес груза!");
        }
        if (!m_port)
        {
            m_port = std::make_shared<Port>();
        }
        std::cout << "[BaseShip] Параметризованный конструктор: " << m_name << " (ID: " << m_id << ")\n";
    }

    BaseShip::BaseShip(const BaseShip& other)
        : m_name(other.m_name + " (Копия)"),
        m_displacement(other.m_displacement),
        m_cargoWeight(other.m_cargoWeight),
        m_cargoType(other.m_cargoType),
        m_isAtSea(other.m_isAtSea),
        m_id(++s_shipCounter),
        m_port(other.m_port ? std::make_shared<Port>(*other.m_port) : nullptr)
    {
        std::cout << "[BaseShip] Конструктор глубокого копирования: " << m_name << " (ID: " << m_id << ")\n";
    }

    BaseShip::BaseShip(const BaseShip& other, ShallowCopyTag)
        : m_name(other.m_name + " (Поверхн. копия)"),
        m_displacement(other.m_displacement),
        m_cargoWeight(other.m_cargoWeight),
        m_cargoType(other.m_cargoType),
        m_isAtSea(other.m_isAtSea),
        m_id(++s_shipCounter),
        m_port(other.m_port)
    {
        std::cout << "[BaseShip] Конструктор поверхностного копирования: " << m_name << " (ID: " << m_id << ")\n";
    }

    BaseShip::BaseShip(BaseShip&& other) noexcept
        : m_name(std::move(other.m_name)),
        m_displacement(other.m_displacement),
        m_cargoWeight(other.m_cargoWeight),
        m_cargoType(std::move(other.m_cargoType)),
        m_isAtSea(other.m_isAtSea),
        m_id(other.m_id),
        m_port(std::move(other.m_port))
    {
        other.m_displacement = 0.0;
        other.m_cargoWeight = 0.0;
        other.m_id = -1;
        std::cout << "[BaseShip] Конструктор перемещения (ID: " << m_id << ")\n";
    }

    BaseShip& BaseShip::operator=(const BaseShip& other)
    {
        if (this == &other)
        {
            return *this;
        }
        m_name = other.m_name;
        m_displacement = other.m_displacement;
        m_cargoWeight = other.m_cargoWeight;
        m_cargoType = other.m_cargoType;
        m_isAtSea = other.m_isAtSea;
        m_port = other.m_port ? std::make_shared<Port>(*other.m_port) : nullptr;
        return *this;
    }

    BaseShip& BaseShip::operator=(BaseShip&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        m_name = std::move(other.m_name);
        m_displacement = other.m_displacement;
        m_cargoWeight = other.m_cargoWeight;
        m_cargoType = std::move(other.m_cargoType);
        m_isAtSea = other.m_isAtSea;
        m_id = other.m_id;
        m_port = std::move(other.m_port);

        other.m_displacement = 0.0;
        other.m_cargoWeight = 0.0;
        other.m_id = -1;
        return *this;
    }

    BaseShip::~BaseShip()
    {
        std::cout << "[BaseShip] Виртуальный деструктор: " << m_name << " (ID: " << m_id << ")\n";
    }

    std::string BaseShip::FormatHeader() const
    {
        std::ostringstream oss;
        oss << "[ID #" << m_id << "] Судно \"" << m_name << "\" | Порт: " << GetPortName()
            << " | Статус: " << (m_isAtSea ? "В море" : "В порту");
        return oss.str();
    }

    std::string BaseShip::Describe() const
    {
        std::ostringstream oss;
        oss << FormatHeader() << " | Водоизмещение: " << m_displacement << " т | Груз: "
            << m_cargoWeight << " т (" << m_cargoType << ")";
        return oss.str();
    }

    void BaseShip::UnloadCargo(double weight)
    {
        if (m_isAtSea)
        {
            throw std::logic_error("Нельзя разгружать судно в открытом море!");
        }
        if (weight <= 0)
        {
            throw std::invalid_argument("Вес выгрузки должен быть положительным!");
        }
        if (weight > m_cargoWeight)
        {
            m_cargoWeight = 0;
            m_cargoType = "Пусто";
        }
        else
        {
            m_cargoWeight -= weight;
            if (m_cargoWeight == 0)
            {
                m_cargoType = "Пусто";
            }
        }
    }

    void BaseShip::Depart()
    {
        if (m_isAtSea)
        {
            std::cout << m_name << " уже находится в море.\n";
        }
        else
        {
            m_isAtSea = true;
            std::cout << m_name << " вышло в рейс из порта " << GetPortName() << ".\n";
        }
    }

    void BaseShip::Arrive()
    {
        if (!m_isAtSea)
        {
            std::cout << m_name << " уже стоит в порту.\n";
        }
        else
        {
            m_isAtSea = false;
            std::cout << m_name << " прибыло в порт " << GetPortName() << ".\n";
        }
    }

    void BaseShip::DockAtCurrentPort() const
    {
        if (!m_port)
        {
            throw std::logic_error("У судна не назначен порт!");
        }
        if (m_isAtSea)
        {
            throw std::logic_error("Нельзя зарегистрировать в порту судно, находящееся в море!");
        }
        m_port->RegisterShip(*this);
    }

    void BaseShip::RenamePort(std::string_view newPortName)
    {
        if (m_port)
        {
            m_port->SetPortName(newPortName);
        }
    }

    std::string BaseShip::ParseRegistryCode(const std::string& registryCode) const
    {
        std::size_t firstDash = registryCode.find('-');
        if (firstDash == std::string::npos)
        {
            return "Неверный формат кода: " + registryCode;
        }

        std::size_t secondDash = registryCode.find('-', firstDash + 1);
        if (secondDash == std::string::npos)
        {
            return "Неверный формат кода: " + registryCode;
        }

        std::string country = registryCode.substr(0, firstDash);
        std::string portCode = registryCode.substr(firstDash + 1, secondDash - firstDash - 1);
        std::string serialNumber = registryCode.substr(secondDash + 1);

        std::string result = "Судно " + m_name + " -> Реестр: ";
        if (country == "RU")
        {
            result += "РФ (порт " + portCode + ", №" + serialNumber + ")";
        }
        else
        {
            result += "Иностранный [" + country + "] (порт " + portCode + ", №" + serialNumber + ")";
        }
        return result;
    }

    std::string BaseShip::GetPortName() const
    {
        return m_port ? m_port->GetPortName() : "Не назначен";
    }

    int BaseShip::GetTotalShipsCreated()
    {
        return s_shipCounter;
    }

    void BaseShip::ResetCounter()
    {
        s_shipCounter = 0;
    }
}