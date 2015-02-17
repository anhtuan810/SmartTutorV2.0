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
using System.IO;

namespace GUI.Practice
{
    /// <summary>
    /// Interaction logic for ucPractice1.xaml
    /// </summary>
    public partial class ucPractice1 : UserControl
    {
        private DispatcherTimer timer_ = new System.Windows.Threading.DispatcherTimer();
        private KinectController kinect_sensor_ = new KinectController();
        private WebcamController webcam_ = new WebcamController();

        private FeatureExtractor feature_extractor_ = new FeatureExtractor();
        private OverallAssessment overall_assessment_ = new OverallAssessment();
        private RealtimeFeedback realtime_feedback_ = new RealtimeFeedback();

        private string oni_to_record = @"G:\test.oni";
        private string avi_to_record = @"G:\test.avi";
        private string data_folder_ = @"G:\Development of SmartTutor\test_data\";
        ResultRecorder result_recorder_;

        bool is_recording = false;

        public ucPractice1()
        {
            InitializeComponent();            

            this.TurnOnSensors();
            this.CountDown.Finish += CountDown_Finish;
            timer_.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer_.Tick += timer__Tick;
            timer_.Start();
        }

        void CountDown_Finish(object sender, EventArgs e)
        {
            StartRecording();
        }

        void timer__Tick(object sender, EventArgs e)
        {
            kinect_sensor_.QuerySensor();
            WriteableBitmap bmpKinect = kinect_sensor_.GrabCurrentColorFrame();
            this.imgKinect.Source = bmpKinect;

            if (is_recording)
            {
                // Perform analysis in real-time
                //
                feature_extractor_.ExtractFeatureNewFrame();
                overall_assessment_.AssessOneFeatureSet();
                this.lblTest.Content = overall_assessment_.GetScore_Overall()[overall_assessment_.GetScore_Overall().Count - 1];

                // Write result data
                //
                result_recorder_.RecordMostRecentSample();
            }
        }










        private void TurnOnSensors()
        {
            this.TurnOffSensors();
            //kinect_sensor_.TurnOnKinectSensor();
            kinect_sensor_.TurnOnONIFile(@"G:\Research materials\[+++++] Database collected in QMUL\ONI\22.oni");
            webcam_ = new WebcamController();
        }

        private void TurnOffSensors()
        {
            kinect_sensor_.TurnOff();
            webcam_.TurnOff();
        }

        private void StartRecording()
        {
            string folder = this.CreateFolderData();
            oni_to_record = folder + "kinect_data.oni";
            avi_to_record = folder + "camera_data.avi";

            result_recorder_ = new ResultRecorder(folder, ref kinect_sensor_, ref feature_extractor_, ref overall_assessment_);
            result_recorder_.Initiate();


            //kinect_sensor_.StartRecording(oni_to_record);
            webcam_.StartRecordingOrDie(avi_to_record);
            is_recording = true;
        }

        private void StopRecording()
        {
            is_recording = false;
            result_recorder_.Finalise();
            kinect_sensor_.StopRecording();
            webcam_.StopRecording();
        }

        private string CreateFolderData()
        {
            //string folder_parent = data_folder_ + DateTime.Now.ToLocalTime().Ticks.ToString() + @"\";
            string folder_parent = data_folder_ + DateTime.Now.Year.ToString()
                + "-" + DateTime.Now.Month.ToString()
                + "-" + DateTime.Now.Day.ToString()
                + "-" + DateTime.Now.Hour.ToString()
                + "." + DateTime.Now.Minute.ToString()
                + "." + DateTime.Now.Second.ToString() + @"\";

            if (!Directory.Exists(folder_parent))
            {
                Directory.CreateDirectory(folder_parent);
            }

            //string folder_features = folder_parent + @"features\";
            //if (!Directory.Exists(folder_features))
            //{
            //    Directory.CreateDirectory(folder_features);
            //}

            //string folder_result = folder_parent + @"result\";
            //if (!Directory.Exists(folder_result))
            //{
            //    Directory.CreateDirectory(folder_result);
            //}
            return folder_parent;
        }

        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            this.StopRecording();
        }

        public void Closing()
        {
            this.TurnOffSensors();
        }
    }
}
