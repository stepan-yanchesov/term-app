namespace Seaport
{
    public class PortLog : IDisposable
    {
        public PortLog() => Console.WriteLine("[Log] Ресурс PortLog выделен (файл журнала открыт).");
        public void Write(string message) => Console.WriteLine($"[Log] Запись: {message}");

        public void Dispose()
        {
            Console.WriteLine("[Log] Метод Dispose вызван: PortLog освобожден без деструктора.");
        }
    }
    class Program
    {
        static void CreateTemporaryGarbage()
        {
            Ship tempShip = new Ship("Фрегат", "Пушечные ядра", 100.0);
            Console.WriteLine($"Создан временный объект: {tempShip.Name}");
        }
        static void Main(string[] args)
        {
            Console.WriteLine("=== Работа порта ===");
            Port myPort = new Port("Морской Северный");
            myPort.OpenPort();

            Ship ship1 = new Ship("Виктория", "Уголь", 500.0);
            Ship ship2 = new Ship("Надежда", "Зерно", -50.0);

            myPort.DockShipInPort(ship1);
            Console.WriteLine(myPort.ToString());

            myPort.DockShipInPort(ship2);

            myPort.FreePortDock();
            Console.WriteLine(myPort.ToString());

            Console.WriteLine("--- Ссылки ---");
            Ship originalShip = new Ship("Старый Корабль", "Рыба", 10.0);
            Console.WriteLine(originalShip.ToString());
            Ship linkedShip = originalShip;

            linkedShip.UnloadCargo(5.0);

            Console.WriteLine($"Оригинальный корабль вес груза: {originalShip.CargoWeight} т.");

            Console.WriteLine("Входим в блок using...");
            using (PortLog log = new())
            {
                log.Write("Корабль зашел в порт.");
                log.Write("Началась выгрузка.");
                Console.WriteLine("Выходим из блока using...");
            }

            Console.WriteLine("\n=== Демонстрация работы Garbage Collector ===");

            CreateTemporaryGarbage();

            Console.WriteLine("Временный корабль потерял ссылку, но GC еще не запускался.");

            Console.WriteLine("Вызов GC.Collect()");
            GC.Collect();

            GC.WaitForPendingFinalizers();

            Console.WriteLine("=== Программа завершена ===");

        }
    }
}