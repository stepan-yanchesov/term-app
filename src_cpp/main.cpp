#include "port.h"
#include "ship.h"
#include <iostream>
#include <cstdlib>

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
    seaport::Ship* dynamicShip = new seaport::Ship("Титан", "Нефть", 5000.0);

    seaport::Ship stackShip("Аврора", "Контейнеры", 1200.0);
    std::cout << "\n";

    DisplayShipInfo(stackShip);
    std::cout << "\n";

    {
        std::cout << "--- Создание Порта (Композиция) ---\n";
        seaport::Port myPort("Южный Порт", 1, 15.5);
        myPort.OpenPort();
        myPort.InspectPort();
        std::cout << "\n";

        std::cout << "--- Демонстрация агрегации ---\n";
        myPort.DockShipInPort(dynamicShip);
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
    std::cout << "Корабль \"" << dynamicShip->GetName() << "\" всё еще существует в акватории.\n";
    dynamicShip->Refuel();
    std::cout << "\n";

    std::cout << "--- Удаление динамического корабля ---\n";
    delete dynamicShip;
    dynamicShip = nullptr;
    std::cout << "\n";

    seaport::Ship* shipArray = new seaport::Ship[2];
    delete[] shipArray;
    std::cout << "\n";

    seaport::Ship** pointerArray = new seaport::Ship * [2];
    pointerArray[0] = new seaport::Ship("Муссон", "Уголь", 3000.0);
    pointerArray[1] = new seaport::Ship("Шквал", "Зерно", 2500.0);
    std::cout << "\n";

    for (int i = 0; i < 2; ++i)
    {
        delete pointerArray[i];
    }
    delete[] pointerArray;
    std::cout << "\n";

    std::cout << "--- Завершение работы main() ---\n";
    return 0;
}