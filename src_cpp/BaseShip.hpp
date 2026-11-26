#pragma once

#include <memory>
#include <string>
#include "Port.hpp"

namespace seaport
{
    struct ShallowCopyTag {};

    class BaseShip
    {
    protected:
        std::string m_name;
        double m_displacement;
        double m_cargoWeight;
        std::string m_cargoType;
        bool m_isAtSea;
        int m_id;
        std::shared_ptr<Port> m_port;

        static int s_shipCounter;

        BaseShip(const BaseShip& other);
        BaseShip(const BaseShip& other, ShallowCopyTag);
        BaseShip(BaseShip&& other) noexcept;

        BaseShip& operator=(const BaseShip& other);
        BaseShip& operator=(BaseShip&& other) noexcept;

        std::string FormatHeader() const;

    public:
        BaseShip();
        BaseShip(const std::string& name, double displacement, double cargoWeight,
            const std::string& cargoType, std::shared_ptr<Port> port);

        virtual ~BaseShip();

        virtual void LoadCargo(double weight, const std::string& type) = 0;
        virtual void UnloadCargo(double weight) = 0;
        virtual double CalculatePortFee() const = 0;
        virtual std::unique_ptr<BaseShip> Clone() const = 0;
        virtual std::unique_ptr<BaseShip> ShallowClone() const = 0;

        [[nodiscard]] virtual std::string Describe() const;

        void Depart();
        void Arrive();

        void DockAtCurrentPort() const;
        void RenamePort(std::string_view newPortName);

        [[nodiscard]] std::string ParseRegistryCode(const std::string& registryCode) const;

        [[nodiscard]] std::string GetName() const { return m_name; }
        [[nodiscard]] double GetDisplacement() const { return m_displacement; }
        [[nodiscard]] double GetCargoWeight() const { return m_cargoWeight; }
        [[nodiscard]] std::string GetCargoType() const { return m_cargoType; }
        [[nodiscard]] bool IsAtSea() const { return m_isAtSea; }
        [[nodiscard]] int GetId() const { return m_id; }
        [[nodiscard]] std::string GetPortName() const;

        static int GetTotalShipsCreated();
        static void ResetCounter();
    };
}