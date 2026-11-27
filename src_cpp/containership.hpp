#pragma once

#include "BaseShip.hpp"

namespace seaport
{
    class ContainerShip final : public BaseShip
    {
    private:
        static constexpr double DEFAULT_CONTAINER_WEIGHT = 24.0;

        int m_maxContainers;
        int m_currentContainers;
        double m_standardContainerWeight;

    protected:
        ContainerShip(const ContainerShip& other);
        ContainerShip(const ContainerShip& other, ShallowCopyTag);

    public:
        ContainerShip();
        ContainerShip(const std::string& name, double displacement, int maxContainers,
            int currentContainers, std::shared_ptr<Port> port,
            double standardContainerWeight = DEFAULT_CONTAINER_WEIGHT);
        ContainerShip(ContainerShip&& other) noexcept;

        ~ContainerShip() override;

        ContainerShip& operator=(const ContainerShip& other);
        ContainerShip& operator=(ContainerShip&& other) noexcept;

        void LoadCargo(double weight, const std::string& type) override;
        void UnloadCargo(double weight) override;
        [[nodiscard]] double CalculatePortFee() const override;
        [[nodiscard]] std::unique_ptr<BaseShip> Clone() const override;
        [[nodiscard]] std::unique_ptr<BaseShip> ShallowClone() const override;

        [[nodiscard]] std::string Describe() const override;

        void LoadContainers(int count);
        void UnloadContainers(int count);

        [[nodiscard]] int GetMaxContainers() const { return m_maxContainers; }
        [[nodiscard]] int GetCurrentContainers() const { return m_currentContainers; }
        [[nodiscard]] double GetStandardContainerWeight() const { return m_standardContainerWeight; }
    };
}