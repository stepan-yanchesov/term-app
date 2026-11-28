#pragma once

#include "BaseShip.hpp"

namespace seaport
{
    class Tanker : public BaseShip
    {
    private:
        double m_tankCapacity;
        bool m_hasDoubleHull;

    public:
        Tanker();
        Tanker(const std::string& name, double displacement, double cargoWeight,
            const std::string& liquidType, double tankCapacity, bool hasDoubleHull,
            std::shared_ptr<Port> port);
        Tanker(const Tanker& other);
        Tanker(const Tanker& other, ShallowCopyTag);
        Tanker(Tanker&& other) noexcept;

        ~Tanker() override;

        Tanker& operator=(const Tanker& other);
        Tanker& operator=(Tanker&& other) noexcept;

        void LoadCargo(double weight, const std::string& type) override;
        void UnloadCargo(double weight) override;
        [[nodiscard]] double CalculatePortFee() const override;
        [[nodiscard]] std::unique_ptr<BaseShip> Clone() const override;
        [[nodiscard]] std::unique_ptr<BaseShip> ShallowClone() const override;

        [[nodiscard]] std::string Describe() const override;

        void PumpOutAll();

        [[nodiscard]] double GetTankCapacity() const { return m_tankCapacity; }
        [[nodiscard]] bool HasDoubleHull() const { return m_hasDoubleHull; }
    };
}