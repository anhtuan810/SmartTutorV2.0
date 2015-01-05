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
        System.Windows.Threading.DispatcherTimer timer = new System.Windows.Threading.DispatcherTimer();
        private GUI.Interfaces.SensorController controller;
        private GUI.Interfaces.FeatureExtractor feature_extractor;

        public MainWindow()
        {
            InitializeComponent();
            timer.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer.Tick += timer_Tick;

            controller = new SensorController();
            controller.TurnOnONIFile("F:\\Development of SmartTutor\\11.oni");

            timer.Start();

            


        }

        void timer_Tick(object sender, EventArgs e)
        {
            controller.QuerySensor();
            WriteableBitmap bmp = controller.GrabCurrentColorFrame();
            this.imgKinect.Source = bmp;

            feature_extractor = new FeatureExtractor();
            feature_extractor.ExtractFeatureNewFrame();
            int buffer_size = feature_extractor.GetActualFeatureBufferSize();
            float[] f_velocity_left_hand = feature_extractor.GetFeature_VelocityLeftHand();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            controller.TurnOff();
        }
    }
}
