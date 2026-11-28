#include "ContainerShip.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace seaport
{
    ContainerShip::ContainerShip()
        : BaseShip(),
        m_maxContainers(50),
        m_currentContainers(0),
        m_standardContainerWeight(DEFAULT_CONTAINER_WEIGHT)
    {
        m_cargoType = "Контейнеры (TEU)";
        std::cout << "[ContainerShip] Конструктор по умолчанию (ID: " << m_id << ")\n";
    }

    ContainerShip::ContainerShip(const std::string& name, double displacement, int maxContainers,
        int currentContainers, std::shared_ptr<Port> port,
        double standardContainerWeight)
        : BaseShip(name, displacement, currentContainers* standardContainerWeight,
            "Контейнеры (TEU)", std::move(port)),
        m_maxContainers(maxContainers),
        m_currentContainers(currentContainers),
        m_standardContainerWeight(standardContainerWeight)
    {
        if (standardContainerWeight <= 0)
        {
            throw std::invalid_argument("Стандартный вес контейнера должен быть положительным!");
        }
        if (maxContainers <= 0)
        {
            throw std::invalid_argument("Вместимость контейнеров должна быть положительной!");
        }
        if (currentContainers < 0 || currentContainers > maxContainers)
        {
            throw std::invalid_argument("Некорректное количество контейнеров!");
        }
        std::cout << "[ContainerShip] Параметризованный конструктор: " << m_name
            << " (макс. " << m_maxContainers << " конт. по "
            << m_standardContainerWeight << " т)\n";
    }

    ContainerShip::ContainerShip(const ContainerShip& other)
        : BaseShip(other),
        m_maxContainers(other.m_maxContainers),
        m_currentContainers(other.m_currentContainers),
        m_standardContainerWeight(other.m_standardContainerWeight)
    {
        std::cout << "[ContainerShip] Конструктор копирования: " << m_name << "\n";
    }

    ContainerShip::ContainerShip(const ContainerShip& other, ShallowCopyTag tag)
        : BaseShip(other, tag),
        m_maxContainers(other.m_maxContainers),
        m_currentContainers(other.m_currentContainers),
        m_standardContainerWeight(other.m_standardContainerWeight)
    {
        std::cout << "[ContainerShip] Конструктор поверхностного копирования: " << m_name << "\n";
    }

    ContainerShip::ContainerShip(ContainerShip&& other) noexcept
        : BaseShip(std::move(other)),
        m_maxContainers(other.m_maxContainers),
        m_currentContainers(other.m_currentContainers),
        m_standardContainerWeight(other.m_standardContainerWeight)
    {
        other.m_maxContainers = 0;
        other.m_currentContainers = 0;
        other.m_standardContainerWeight = 0.0;
        std::cout << "[ContainerShip] Конструктор перемещения\n";
    }

    ContainerShip::~ContainerShip()
    {
        std::cout << "[ContainerShip] Деструктор: " << m_name << " (ID: " << m_id << ")\n";
    }

    ContainerShip& ContainerShip::operator=(const ContainerShip& other)
    {
        if (this == &other)
        {
            std::cout << "[ContainerShip] Самоприсваивание (this == &other) проигнорировано.\n";
            return *this;
        }
        BaseShip::operator=(other);
        m_maxContainers = other.m_maxContainers;
        m_currentContainers = other.m_currentContainers;
        m_standardContainerWeight = other.m_standardContainerWeight;
        std::cout << "[ContainerShip] Оператор копирующего присваивания: " << m_name << "\n";
        return *this;
    }

    ContainerShip& ContainerShip::operator=(ContainerShip&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        BaseShip::operator=(std::move(other));
        m_maxContainers = other.m_maxContainers;
        m_currentContainers = other.m_currentContainers;
        m_standardContainerWeight = other.m_standardContainerWeight;

        other.m_maxContainers = 0;
        other.m_currentContainers = 0;
        other.m_standardContainerWeight = 0.0;
        std::cout << "[ContainerShip] Оператор перемещающего присваивания\n";
        return *this;
    }

    void ContainerShip::LoadCargo(double weight, const std::string& type)
    {
        if (m_isAtSea)
        {
            throw std::logic_error("Нельзя загружать контейнеровоз в открытом море!");
        }
        if (weight <= 0)
        {
            throw std::invalid_argument("Вес груза должен быть положительным!");
        }

        int containersToAdd = static_cast<int>(std::ceil(weight / m_standardContainerWeight));
        double actualWeight = containersToAdd * m_standardContainerWeight;

        if (m_currentContainers + containersToAdd > m_maxContainers || m_cargoWeight + actualWeight > m_displacement)
        {
            throw std::overflow_error("Превышена контейнеровместимость или грузоподъёмность судна!");
        }

        m_currentContainers += containersToAdd;
        m_cargoWeight = m_currentContainers * m_standardContainerWeight;
        m_cargoType = type.empty() ? "Контейнеры (TEU)" : type;

        std::cout << m_name << ": загружено " << containersToAdd << " конт. (по "
            << m_standardContainerWeight << " т, итого +" << actualWeight << " т). "
            << "На борту: " << m_currentContainers << "/" << m_maxContainers
            << " конт. (" << m_cargoWeight << " т).\n";
    }

    void ContainerShip::UnloadCargo(double weight)
    {
        int containersToRemove = static_cast<int>(std::ceil(weight / m_standardContainerWeight));
        double actualWeightToRemove = containersToRemove * m_standardContainerWeight;

        BaseShip::UnloadCargo(actualWeightToRemove);

        m_currentContainers = static_cast<int>(std::round(m_cargoWeight / m_standardContainerWeight));
        m_cargoWeight = m_currentContainers * m_standardContainerWeight;

        std::cout << m_name << ": выгружено " << containersToRemove << " конт. ("
            << actualWeightToRemove << " т). Осталось: "
            << m_currentContainers << " конт. (" << m_cargoWeight << " т).\n";
    }

    void ContainerShip::LoadContainers(int count)
    {
        if (count <= 0)
        {
            throw std::invalid_argument("Количество контейнеров должно быть положительным!");
        }
        LoadCargo(count * m_standardContainerWeight, m_cargoType);
    }

    void ContainerShip::UnloadContainers(int count)
    {
        if (count <= 0)
        {
            throw std::invalid_argument("Количество контейнеров должно быть положительным!");
        }
        if (count > m_currentContainers)
        {
            throw std::logic_error("На борту нет столько контейнеров!");
        }
        UnloadCargo(count * m_standardContainerWeight);
    }

    double ContainerShip::CalculatePortFee() const
    {
        return m_displacement * 1.5 + m_currentContainers * 25.0;
    }

    std::unique_ptr<BaseShip> ContainerShip::Clone() const
    {
        return std::make_unique<ContainerShip>(*this);
    }

    std::unique_ptr<BaseShip> ContainerShip::ShallowClone() const
    {
        return std::make_unique<ContainerShip>(*this, ShallowCopyTag{});
    }

    std::string ContainerShip::Describe() const
    {
        std::ostringstream oss;
        oss << FormatHeader() << " [Тип: Контейнеровоз]"
            << " | Контейнеры: " << m_currentContainers << "/" << m_maxContainers
            << " шт. (по " << m_standardContainerWeight << " т)"
            << " | Общий вес груза: " << m_cargoWeight << " т"
            << " | Сбор: " << CalculatePortFee() << " у.е.";
        return oss.str();
    }
}