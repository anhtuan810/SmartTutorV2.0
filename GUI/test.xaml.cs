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
using System.Windows.Shapes;
using GUI.Interfaces;

namespace GUI
{
    /// <summary>
    /// Interaction logic for test.xaml
    /// </summary>
    public partial class test : Window
    {
        System.Windows.Threading.DispatcherTimer timer_ = new System.Windows.Threading.DispatcherTimer();
        private GUI.Interfaces.KinectController kinect_sensor_ = new KinectController();
        private WebcamController webcam_ = new WebcamController();

        public test()
        {
            InitializeComponent();
            kinect_sensor_.TurnOnKinectSensor();
            timer_.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer_.Tick += timer__Tick;
            timer_.Start();
        }

        void timer__Tick(object sender, EventArgs e)
        {
            kinect_sensor_.QuerySensor();
            WriteableBitmap bmpKinect = kinect_sensor_.GrabCurrentColorFrame();
            this.imgKinect.Source = bmpKinect;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            kinect_sensor_.TurnOff();
        }
    }
}
