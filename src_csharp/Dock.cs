using System;
using System.Xml.Linq;

namespace Seaport
{
    public class Dock
    {
        private int _dockNumber = 0;
        private double _maxDepth = 0.0;
        private Ship? _currentShip = null;
        public Dock() { }
        public Dock(int  dockNumber, double maxDepth)
        {
            _dockNumber = dockNumber;
            _maxDepth = maxDepth;
        }
        public int DockNumber => _dockNumber;
        public double Maxdepth => _maxDepth;
        public bool IsOccupied => _currentShip != null;
        public string OccupiedShipName
        {
            get
            {
                if (_currentShip == null)
                {
                    return "Свободно.";
                }
                else
                {
                    return _currentShip.Name;
                }
            }
        }
        public void MoorShip(Ship ship)
        {
            if (_currentShip != null)
            {
                Console.WriteLine($"[Отказ] Причал №{_dockNumber} уже занят другим судном.\n");
                return;
            }
            _currentShip = ship;
            Console.WriteLine($"[Успех] Корабль {_currentShip.Name} пришвартован к порту №{_dockNumber}\n");
        }
        public void ReleaseShip()
        {
            if ( _currentShip == null )
            {
                Console.WriteLine($"[Предупреждение] Причал №{_dockNumber} не содержит корабля.\n");
                return;
            }
            Console.WriteLine($"Корабль {_currentShip.Name} отошёл от причала №{_dockNumber}\n");
            _currentShip = null;
        }
        public override string ToString()
        {
            return $"Причал №{_dockNumber}, максимальная глубина - {_maxDepth}\n";
        }
    }
}