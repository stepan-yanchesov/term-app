using System;
using System.Xml.Linq;

namespace Seaport
{
    public class Dock
    {
        private int _dockNumber = 0;
        private double _maxdepth = 0.0;
        private Ship? _currentShip = null;
        public Dock() { }
        public Dock(int  dockNumber, double maxdepth)
        {
            _dockNumber = dockNumber;
            _maxdepth = maxdepth;
        }
        public int DockNubmer => _dockNumber;
        public double Maxdepth => _maxdepth;
        public bool IsOccupied => _currentShip != null;
        public string OccupiedShipName()
        {
            if (_currentShip == null)
            {
                return "Свободно.\n";
            }
            else
            {
                return _currentShip.NAME;
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
            Console.WriteLine($"[Успех] Корабль {_currentShip.NAME} пришвартован к порту №{_dockNumber}\n");
        }
        public void ReleaseShip()
        {
            if ( _currentShip == null )
            {
                Console.WriteLine($"[Предупреждение] Причал №{_dockNumber} не содержит корабля.\n");
                return;
            }
            Console.WriteLine($"Корабль {_currentShip.NAME} отошёл от причала №{_dockNumber}\n");
        }
        public override string ToString()
        {
            return $"Причал №{_dockNumber}, максимальная глубина - {_maxdepth}\n";
        }
    }
}