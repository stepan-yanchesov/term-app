#include "Tanker.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace seaport
{
    Tanker::Tanker()
        : BaseShip(),
        m_tankCapacity(5000.0),
        m_hasDoubleHull(true)
    {
        m_cargoType = "Сырая нефть";
        std::cout << "[Tanker] Конструктор по умолчанию (ID: " << m_id << ")\n";
    }

    Tanker::Tanker(const std::string& name, double displacement, double cargoWeight,
        const std::string& liquidType, double tankCapacity, bool hasDoubleHull,
        std::shared_ptr<Port> port)
        : BaseShip(name, displacement, cargoWeight, liquidType, std::move(port)),
        m_tankCapacity(tankCapacity),
        m_hasDoubleHull(hasDoubleHull)
    {
        if (tankCapacity <= 0)
        {
            throw std::invalid_argument("Объём танков должен быть положительным!");
        }
        if (cargoWeight > tankCapacity)
        {
            throw std::invalid_argument("Объём груза превышает вместимость танков!");
        }
        std::cout << "[Tanker] Параметризованный конструктор: " << m_name
            << " (танки: " << m_tankCapacity << " т, двойной корпус: "
            << (m_hasDoubleHull ? "да" : "нет") << ")\n";
    }

    Tanker::Tanker(const Tanker& other)
        : BaseShip(other),
        m_tankCapacity(other.m_tankCapacity),
        m_hasDoubleHull(other.m_hasDoubleHull)
    {
        std::cout << "[Tanker] Конструктор копирования: " << m_name << "\n";
    }

    Tanker::Tanker(const Tanker& other, ShallowCopyTag tag)
        : BaseShip(other, tag),
        m_tankCapacity(other.m_tankCapacity),
        m_hasDoubleHull(other.m_hasDoubleHull)
    {
        std::cout << "[Tanker] Конструктор поверхностного копирования: " << m_name << "\n";
    }

    Tanker::Tanker(Tanker&& other) noexcept
        : BaseShip(std::move(other)),
        m_tankCapacity(other.m_tankCapacity),
        m_hasDoubleHull(other.m_hasDoubleHull)
    {
        other.m_tankCapacity = 0.0;
        other.m_hasDoubleHull = false;
        std::cout << "[Tanker] Конструктор перемещения\n";
    }

    Tanker::~Tanker()
    {
        std::cout << "[Tanker] Деструктор: " << m_name << " (ID: " << m_id << ")\n";
    }

    Tanker& Tanker::operator=(const Tanker& other)
    {
        if (this == &other)
        {
            std::cout << "[Tanker] Самоприсваивание (this == &other) проигнорировано.\n";
            return *this;
        }
        BaseShip::operator=(other);
        m_tankCapacity = other.m_tankCapacity;
        m_hasDoubleHull = other.m_hasDoubleHull;
        std::cout << "[Tanker] Оператор копирующего присваивания: " << m_name << "\n";
        return *this;
    }

    Tanker& Tanker::operator=(Tanker&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        BaseShip::operator=(std::move(other));
        m_tankCapacity = other.m_tankCapacity;
        m_hasDoubleHull = other.m_hasDoubleHull;

        other.m_tankCapacity = 0.0;
        other.m_hasDoubleHull = false;
        std::cout << "[Tanker] Оператор перемещающего присваивания\n";
        return *this;
    }

    void Tanker::LoadCargo(double weight, const std::string& type)
    {
        if (m_isAtSea)
        {
            throw std::logic_error("Нельзя перекачивать наливной груз в открытом море!");
        }
        if (weight <= 0)
        {
            throw std::invalid_argument("Масса наливного груза должна быть положительной!");
        }
        if (m_cargoWeight + weight > m_tankCapacity || m_cargoWeight + weight > m_displacement)
        {
            throw std::overflow_error("Превышен объём танков или водоизмещение танкера!");
        }
        if (m_cargoWeight > 0 && m_cargoType != type)
        {
            throw std::logic_error("Нельзя смешивать разные типы жидкостей в танках!");
        }

        m_cargoWeight += weight;
        m_cargoType = type;
        std::cout << m_name << ": закачано " << weight << " т (" << m_cargoType
            << "). Заполнено: " << m_cargoWeight << "/" << m_tankCapacity << " т.\n";
    }

    void Tanker::UnloadCargo(double weight)
    {
        BaseShip::UnloadCargo(weight);
        std::cout << m_name << ": откачано " << weight << " т. Остаток в танках: "
            << m_cargoWeight << " т.\n";
    }

    void Tanker::PumpOutAll()
    {
        if (m_cargoWeight > 0)
        {
            UnloadCargo(m_cargoWeight);
        }
    }

    double Tanker::CalculatePortFee() const
    {
        double baseFee = m_displacement * 2.0 + m_cargoWeight * 0.8;
        return m_hasDoubleHull ? baseFee : baseFee * 1.5;
    }

    std::unique_ptr<BaseShip> Tanker::Clone() const
    {
        return std::make_unique<Tanker>(*this);
    }

    std::unique_ptr<BaseShip> Tanker::ShallowClone() const
    {
        return std::make_unique<Tanker>(*this, ShallowCopyTag{});
    }

    std::string Tanker::Describe() const
    {
        std::ostringstream oss;
        oss << BaseShip::Describe()
            << " | [Танкер] Танки: " << m_cargoWeight << "/" << m_tankCapacity << " т"
            << " | Двойной корпус: " << (m_hasDoubleHull ? "Да" : "Нет")
            << " | Сбор: " << CalculatePortFee() << " у.е.";
        return oss.str();
    }
}