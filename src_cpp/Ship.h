#pragma once

#include <string>

namespace seaport
{

    class Ship
    {
    private:
        static constexpr auto BASE_NAME = "Unknown Ship";
        static constexpr auto BASE_CARGO = "None";

        std::string m_name{ BASE_NAME };
        std::string m_cargoType{ BASE_CARGO };
        double m_cargoWeight{ 0.0 };

    public:
        Ship();
        Ship(const std::string& name, const std::string& cargoType, double cargoWeight);
        ~Ship();

        [[nodiscard]] std::string GetName() const
        {
            return m_name;
        }

        [[nodiscard]] std::string GetCargoType() const
        {
            return m_cargoType;
        }

        [[nodiscard]] double GetCargoWeight() const
        {
            return m_cargoWeight;
        }

        void UnloadCargo(double amount);
        void Refuel();
    };

}