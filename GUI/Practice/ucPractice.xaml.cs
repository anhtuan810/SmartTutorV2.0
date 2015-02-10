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
using System.Windows.Threading;
using GUI.Interfaces;

namespace GUI.Pratice
{
    /// <summary>
    /// Interaction logic for ucPractice.xaml
    /// </summary>
    public partial class ucPractice : UserControl
    {
        private DispatcherTimer timer_ = new System.Windows.Threading.DispatcherTimer();
        private KinectController kinect_sensor_ = new KinectController();
        private WebcamController webcam_ = new WebcamController();
        private FeatureExtractor feature_extractor_ = new FeatureExtractor();
        private OverallAssessment overall_assessment_ = new OverallAssessment();
        private RealtimeFeedback realtime_feedback_ = new RealtimeFeedback();

        private string oni_to_record = "G:\\test.oni";
        private string avi_to_record = "G:\\test.avi";

        public ucPractice()
        {
            InitializeComponent();
            this.TurnOnSensors();

            timer_.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer_.Tick += timer__Tick;
            timer_.Start();

            this.count_down.Finish += count_down_Finish;
        }

        void count_down_Finish(object sender, EventArgs e)
        {
            this.StartRecording();
        }

        void timer__Tick(object sender, EventArgs e)
        {
            kinect_sensor_.QuerySensor();
            WriteableBitmap bmpKinect = kinect_sensor_.GrabCurrentColorFrame();
            this.imgMirror.Source = bmpKinect;
        }

        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            this.StopRecording();
        }



        private void TurnOnSensors()
        {
            kinect_sensor_.TurnOnKinectSensor();
            webcam_ = new WebcamController();
        }

        private void TurnOffSensors()
        {
            kinect_sensor_.TurnOff();
            webcam_.TurnOff();
        }

        private void StartRecording()
        {
            kinect_sensor_.StartRecording(oni_to_record);
            webcam_.StartRecordingOrDie(avi_to_record);
        }

        private void StopRecording()
        {
            kinect_sensor_.StopRecording();
            webcam_.StopRecording();
        }
    }
}
