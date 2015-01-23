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
    /// Interaction logic for Mirror.xaml
    /// </summary>
    public partial class Mirror : Window
    {
        System.Windows.Threading.DispatcherTimer timer = new System.Windows.Threading.DispatcherTimer();
        private GUI.Interfaces.SensorController controller = new SensorController();
        private GUI.Interfaces.FeatureExtractor feature_extractor = new FeatureExtractor();
        private GUI.Interfaces.OverallAssessment overall_assessment = new OverallAssessment();
        private GUI.Interfaces.RealtimeFeedback realtime_feedback = new RealtimeFeedback();
        private string oni_file_ = "G:\\Development of SmartTutor\\11.oni";

        public Mirror()
        {
            InitializeComponent();
            timer.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer.Tick += timer_Tick;

            controller.TurnOnONIFile(oni_file_);
            timer.Start();
        }

        void timer_Tick(object sender, System.EventArgs e)
        {
            controller.QuerySensor();
            WriteableBitmap bmpMirror = realtime_feedback.GetRealtimeFeedbackFrame();
            this.imgMain.Source = bmpMirror;
        }
    }
}
