
namespace Seaport
{
    public class Ship
    {
        private const string BASE_NAME = "Unknown ship";
        private const string BASE_CARGO = "None";
        private double _cargoWeight;
        private string _name;
        private string _cargoType;
        public Ship()
        {
            _name = BASE_NAME;
            _cargoType = BASE_CARGO;
            _cargoWeight = 0.0;
        }
        public Ship(string name, string base_cargo, double cargoWeight)
        {
            _name = name;
            _cargoType = base_cargo;
            if (cargoWeight < 0.0)
            {
                Console.WriteLine("[Ошибка] Вес груза не может быть отрицательным. Установлено значение 0.0.");
                _cargoWeight = 0.0;
            }
            else
            {
                _cargoWeight = cargoWeight;
            }
        }
        public string NAME => _name;
        public string CARGO_TYPE => _cargoType;
        public double CargoWeight => _cargoWeight;
        public void UnloadCargo(double amount)
        {
            if (amount < 0.0 || amount > CargoWeight) {
                Console.WriteLine("[Отказ] С корабля невозможно выгрузить отрицательный или больший груз, который на нём находится.\n");
                return;
            }
            _cargoWeight -= amount;
            Console.WriteLine($"[Успех] С корабля {_name} выгружено {amount} т.\n");
        }
        public void Refuel()
        {
            Console.WriteLine($"[Успех] Корабль {_name} успешно заправлен топливом.\n");
        }
        public override string ToString()
        {
            return $"Корабль \"{_name}\" (Груз: {_cargoType}, Вес: {_cargoWeight} т.)";
        }
    }
}