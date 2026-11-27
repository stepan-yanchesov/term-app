#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "BaseShip.hpp"
#include "ContainerShip.hpp"
#include "Dock.hpp"
#include "Port.hpp"
#include "Tanker.hpp"

using namespace seaport;

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Демонстрация конструктора, перемещения и виртуального деструктора.\n";
    {
        std::cout << "-> Создаём временный ContainerShip по умолчанию:\n";
        ContainerShip tempDefault;

        std::cout << "-> Создаём временный Tanker через unique_ptr<BaseShip>:\n";
        std::unique_ptr<BaseShip> polyTemp = std::make_unique<Tanker>();

        std::cout << "-> Демонстрация конструктора перемещения:\n";
        ContainerShip movedShip(std::move(tempDefault));

        std::cout << "-> Выход из блока (уничтожение через базовый указатель и по значению):\n";
    }
    std::cout << "Всего создано судов (static счётчик): " << BaseShip::GetTotalShipsCreated() << "\n\n";

    std::cout << "Демонстрация полиморфизма.\n";
    auto spbPort = std::make_shared<Port>("Большой порт Санкт-Петербург", 1, 14.5);
    auto novorosPort = std::make_shared<Port>("Порт Новороссийск", 3, 18.0);

    spbPort->OpenPort();
    novorosPort->OpenPort();

    std::vector<std::unique_ptr<BaseShip>> fleet;

    fleet.push_back(std::make_unique<ContainerShip>(
        "Балтийский Экспресс", 25000.0, 500, 120, spbPort, 24.0));

    fleet.push_back(std::make_unique<Tanker>(
        "Северный Поток", 60000.0, 35000.0, "Сырая нефть", 45000.0, true, novorosPort));

    fleet.push_back(std::make_unique<Tanker>(
        "Каспий-1", 18000.0, 10000.0, "Мазут", 12000.0, false, novorosPort));

    std::cout << "\n--- Вызов Describe() ---\n";
    for (const auto& ship : fleet)
    {
        std::cout << ship->Describe() << "\n";
    }

    std::cout << "\n--- Погрузка и выгрузка (LoadCargo / UnloadCargo) ---\n";
    fleet[0]->LoadCargo(480.0, "Электроника");
    fleet[0]->UnloadCargo(240.0);

    fleet[1]->LoadCargo(5000.0, "Сырая нефть");
    fleet[1]->UnloadCargo(10000.0);

    std::cout << "Демонстрация this.\n";
    std::cout << "--- Передача *this в Port::RegisterShip ---\n";
    for (const auto& ship : fleet)
    {
        ship->DockAtCurrentPort();
    }

    std::cout << "\n--- Проверка самоприсваивания (this == &other) и возврата *this ---\n";
    ContainerShip shipA("Тест-А", 10000.0, 200, 10, spbPort, 20.0);
    ContainerShip shipB("Тест-Б", 12000.0, 250, 20, novorosPort, 24.0);

    ContainerShip& refA = shipA;
    shipA = refA;
    shipA = shipB;
    std::cout << "После присваивания shipA = shipB: " << shipA.Describe() << "\n";

    std::cout << "Поверхностное и глубокое копирование\n";
    auto original = std::make_unique<ContainerShip>(
        "Оригинал-1", 15000.0, 300, 50, spbPort, 20.0);

    std::unique_ptr<BaseShip> shallowCopy = original->ShallowClone();
    std::unique_ptr<BaseShip> deepCopy = original->Clone();

    std::cout << "До переименования порта:\n";
    std::cout << "  Оригинал (ID " << original->GetId() << "):       " << original->GetPortName() << "\n";
    std::cout << "  Поверхн. копия (ID " << shallowCopy->GetId() << "): " << shallowCopy->GetPortName() << "\n";
    std::cout << "  Глубокая копия (ID " << deepCopy->GetId() << "): " << deepCopy->GetPortName() << "\n";

    shallowCopy->RenamePort("Порт Усть-Луга (общий с оригиналом)");
    deepCopy->RenamePort("Порт Владивосток (независимый порт)");

    std::cout << "\nПосле переименования порта:\n";
    std::cout << "  Оригинал (ID " << original->GetId() << "):       " << original->GetPortName() << "\n";
    std::cout << "  Поверхн. копия (ID " << shallowCopy->GetId() << "): " << shallowCopy->GetPortName() << "\n";
    std::cout << "  Глубокая копия (ID " << deepCopy->GetId() << "): " << deepCopy->GetPortName() << "\n";

    std::cout << "5. std::string\n";
    std::cout << fleet[0]->ParseRegistryCode("RU-LED-042") << "\n";
    std::cout << fleet[1]->ParseRegistryCode("PA-BAL-109") << "\n";
    std::cout << fleet[2]->ParseRegistryCode("INVALID_CODE") << "\n";

    std::cout << "Обработка исключений и швартовка.\n";
    try
    {
        fleet[0]->Depart();
        fleet[0]->LoadCargo(100.0, "Контейнеры");
    }
    catch (const std::exception& ex)
    {
        std::cout << "[Перехвачено исключение]: " << ex.what() << "\n";
    }

    auto sharedTanker = std::make_shared<Tanker>(
        "Арктика", 40000.0, 20000.0, "СПГ", 30000.0, true, novorosPort);
    novorosPort->DockShipInPort(sharedTanker);
    novorosPort->InspectPort();
    novorosPort->FreePortDock();

    std::cout << "Завершение программы\n";
    return 0;
}