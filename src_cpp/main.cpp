#include "port.h"
#include "ship.h"
#include <iostream>
#include <cstdlib>
#include <memory>

void DisplayShipInfo(const seaport::Ship& ship)
{
    std::cout << ship.GetName() << " | " << ship.GetCargoType() << " | " << ship.GetCargoWeight() << " т.\n";
}

int main()
{
    std::system("chcp 1251 > nul");
    std::setlocale(LC_ALL, "Russian");

    std::cout << "=== Старт демо-версии ===\n\n";

    std::cout << "--- Создание кораблей ---\n";
    std::shared_ptr<seaport::Ship> dynamicShip = std::make_shared<seaport::Ship>("Титан", "Нефть", 5000.0);

    seaport::Ship stackShip("Аврора", "Контейнеры", 1200.0);
    std::cout << "\n";

    DisplayShipInfo(*dynamicShip);
    std::cout << "\n";

    {
        std::cout << "--- Создание Порта (Композиция) ---\n";
        seaport::Port myPort("Южный Порт", 1, 15.5);
        myPort.OpenPort();
        myPort.InspectPort();
        std::cout << "\n";

        std::cout << "--- Демонстрация агрегации ---\n";
        myPort.DockShipInPort(dynamicShip);
        std::cout << "Счетчик владельцев после швартовки: " << dynamicShip.use_count() << "\n";
        myPort.InspectPort();
        std::cout << "\n";

        std::cout << "--- Проверка валидации ---\n";
        dynamicShip->UnloadCargo(6000.0);
        dynamicShip->UnloadCargo(2000.0);
        std::cout << "Текущий вес груза на \"" << dynamicShip->GetName()
            << "\": " << dynamicShip->GetCargoWeight() << " т.\n\n";

        std::cout << "--- Корабль покидает причал ---\n";
        myPort.FreePortDock();
        myPort.InspectPort();
        std::cout << "\n";

        std::cout << "--- Уничтожение Порта ---\n";
    }

    std::cout << "\n--- Проверка связи после уничтожения порта (Агрегация) ---\n";
    std::cout << "Корабль \"" << dynamicShip->GetName() << "\" всё еще существует в акватории. Владельцев: " << dynamicShip.use_count() << "\n";
    dynamicShip->Refuel();
    std::cout << "\n";

    std::cout << "--- unique_ptr ---\n";
    std::unique_ptr<seaport::Ship[]> shipArray = std::make_unique<seaport::Ship[]>(2);
    std::cout << "Массив из 2-х кораблей создан на стеке через unique_ptr.\n";
    std::cout << "\n";

    auto pointerArray = std::make_unique<std::shared_ptr<seaport::Ship>[]>(2);
    std::shared_ptr<seaport::Ship> mosoon = std::make_shared<seaport::Ship>("Муссон", "Уголь", 3000.0);
    std::cout << "Владельцев Муссона до переноса: " << mosoon.use_count() << "\n";
    pointerArray[0] = std::move(mosoon);

    if (!mosoon) {
        std::cout << "Исходный указатель mosoon теперь пуст\n";
    }
    std::cout << "Владельцев Муссона в массиве: " << pointerArray[0].use_count() << "\n";

    pointerArray[1] = std::make_shared<seaport::Ship>("Шквал", "Зерно", 2500.0);
    std::cout << "\n";

    std::cout << "--- Завершение работы main() ---\n";
    return 0;
}