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
            controller.TurnOnKinectSensor();
            //controller.TurnOnONIFile("F:\\Development of SmartTutor\\11.oni");

            timer.Start();

            this.grpVelocity_LeftHand.TitleReal = "Velocity Left Hand";
            this.grpVelocity_RightHand.TitleReal = "Velocity Right Hand";
            this.grpVelocity_Global.TitleReal = "Velocity Global";
            this.grpVelocity_Foot.TitleReal = "Velocity Foot";
            this.grpEnergy.TitleReal = "Energy";
            this.grpDirection_BackForth.TitleReal = "Direction";
            this.grpFootStretch.TitleReal = "Foot Stretch";
            this.grpBalanceBackForth.TitleReal = "Balance Back Forth";
            this.grpBalanceLeftRight.TitleReal = "Balance Left Right";
        }

        void timer_Tick(object sender, EventArgs e)
        {
            controller.QuerySensor();
            WriteableBitmap bmp = controller.GrabCurrentColorFrame();
            this.imgKinect.Source = bmp;

            feature_extractor = new FeatureExtractor();
            feature_extractor.ExtractFeatureNewFrame();
            int buffer_size = feature_extractor.GetActualFeatureBufferSize();
            if (buffer_size >= 5)   
            {
                this.grpVelocity_LeftHand.SetDataReal(feature_extractor.GetFeature_VelocityLeftHand());
                this.grpVelocity_LeftHand.DrawGraph();

                this.grpVelocity_RightHand.SetDataReal(feature_extractor.GetFeature_VelocityRightHand());
                this.grpVelocity_RightHand.DrawGraph();

                this.grpVelocity_Global.SetDataReal(feature_extractor.GetFeature_VelocityGlobal());
                this.grpVelocity_Global.DrawGraph();

                this.grpVelocity_Foot.SetDataReal(feature_extractor.GetFeature_VelocityFoot());
                this.grpVelocity_Foot.DrawGraph();

                this.grpEnergy.SetDataReal(feature_extractor.GetFeature_Energy());
                this.grpEnergy.DrawGraph();

                this.grpDirection_BackForth.SetDataReal(feature_extractor.GetDirection_BackForth());
                this.grpDirection_BackForth.DrawGraph();

                this.grpFootStretch.SetDataReal(feature_extractor.GetFeature_FootStretch());
                this.grpFootStretch.DrawGraph();

                this.grpBalanceBackForth.SetDataReal(feature_extractor.GetFeature_BalanceBackForth());
                this.grpBalanceBackForth.DrawGraph();

                this.grpBalanceLeftRight.SetDataReal(feature_extractor.GetFeature_BalanceLeftRight());
                this.grpBalanceLeftRight.DrawGraph();
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            controller.TurnOff();
        }
    }
}
