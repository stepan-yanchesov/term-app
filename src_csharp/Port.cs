namespace Seaport
{
    public class Port
    {
        private string _portName = "Standard Port";
        private Dock _mainDock;
        public Port()
        {
            _mainDock = new Dock();
        }
        public Port(string portName)
        {
            _portName = portName;
            _mainDock = new Dock();
        }
        public string PortName => _portName;
        public void OpenPort()
        {
            Console.WriteLine($"[Действие] Порт '{_portName}' открыл навигацию.\n");
        }
        public void DockShipInPort(Ship ship)
        {
            Console.WriteLine($"Порт '{_portName}' перенаправляет корабль на причал.\n");
            _mainDock.MoorShip(ship);
        }
        public void FreePortDock()
        {
            _mainDock.ReleaseShip();
        }
        public override string ToString()
        {
            return $"Порт - '{_portName}', причал №{_mainDock.DockNumber}, статус: {_mainDock.OccupiedShipName}\n";
        }
    }
}