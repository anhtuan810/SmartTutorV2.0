using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using GUI.Interfaces;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private GUI.Interfaces.SensorController controller;

        public MainWindow()
        {
            InitializeComponent();
            controller = new SensorController();
            controller.TurnOnONIFile("F:\\Development of SmartTutor\\11.oni");

            controller.QuerySensor();
            WriteableBitmap bmp = controller.GrabCurrentColorFrame();
            this.imgKinect.Source = bmp;
            
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            controller.TurnOff();
        }
    }
}
