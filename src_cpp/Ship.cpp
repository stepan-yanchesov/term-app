#include "Ship.h"
#include <iostream>

namespace seaport
{
	Ship::Ship() = default;

	Ship::Ship(std::string_view name, std::string_view cargoType, double cargoWeight)
        : m_name{ name }
        , m_cargoType{ cargoType }
        , m_cargoWeight{ cargoWeight }
    {
        if (m_cargoWeight < 0.0)
        {
            std::cout << "[Ошибка] Вес груза не может быть отрицательным! Установлено значение 0.0.\n";
            m_cargoWeight = 0.0;
        }
    }

    Ship::~Ship()
    {
        std::cout << "[Деструктор] Корабль \"" << m_name << "\" уничтожен.\n";
    }

    void Ship::UnloadCargo(double amount)
    {
        if (amount > m_cargoWeight)
        {
            std::cout << "[Отказ] Нельзя выгрузить " << amount << " т. На корабле \""
                << m_name << "\" всего " << m_cargoWeight << " т.!\n";
            return;
        }

        m_cargoWeight -= amount;
        std::cout << "[Успех] С корабля \"" << m_name << "\" выгружено " << amount << " т. груза.\n";
    }

    void Ship::Refuel()
    {
        std::cout << "[Действие] Корабль \"" << m_name << "\" успешно заправлен топливом.\n";
    }

}