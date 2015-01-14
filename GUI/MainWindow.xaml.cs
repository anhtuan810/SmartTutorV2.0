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
        private GUI.Interfaces.SensorController controller = new SensorController();
        private GUI.Interfaces.FeatureExtractor feature_extractor = new FeatureExtractor();
        private GUI.Interfaces.OverallAssessment overall_assessment = new OverallAssessment();
        private string oni_file_ = "G:\\Development of SmartTutor\\11.oni";

        public MainWindow()
        {
            InitializeComponent();
            SetGraphTitles();

            ResetONIFile(oni_file_);
            //ResetKinectSensor();

            timer.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer.Tick += timer_Tick;
            timer.Start();
        }

        void SetGraphTitles()
        {
            this.grpVelocity_LeftHand.TitleReal = "Velocity Left Hand";
            this.grpVelocity_RightHand.TitleReal = "Velocity Right Hand";
            this.grpVelocity_Global.TitleReal = "Velocity Global";
            this.grpVelocity_Foot.TitleReal = "Velocity Foot";
            this.grpEnergy.TitleReal = "Energy";
            this.grpDirection_BackForth.TitleReal = "Direction";
            this.grpFootStretch.TitleReal = "Foot Stretch";
            this.grpBalanceBackForth.TitleReal = "Balance Back Forth";
            this.grpBalanceLeftRight.TitleReal = "Balance Left Right";

            this.grpScore_HandGesture.TitleReal = "Score Hand Gesture";
            this.grpScore_GlobalMovement.TitleReal = "Score Global Movement";
            this.grpScore_Energy.TitleReal = "Score Energy";
            this.grpScore_Direction.TitleReal = "Score Direction";
            this.grpScore_Posture.TitleReal = "Score Posture";
            this.grpScore_Overall.TitleReal = "Score Overall";

            this.grpBin_VelocityLeftHand_Low.Title = "Low Velocity";
            this.grpBin_VelocityLeftHand_High.Title = "High Velocity";
            this.grpBin_VelocityRightHand_Low.Title = "Low Velocity";
            this.grpBin_VelocityRightHand_High.Title = "High Velocity";
            this.grpBin_VelocityGlobal_Low.Title = "Low Velocity";
            this.grpBin_VelocityGlobal_High.Title = "High Velocity";
            this.grpBin_VelocityFoot_Low.Title = "Low Velocity";
            this.grpBin_VelocityFoot_High.Title = "High Velocity";
            this.grpBin_Energy_Low.Title = "Low Energy";
            this.grpBin_Energy_High.Title = "High Energy";
            this.grpBin_Direction_Forward.Title = "Direction Forward";
            this.grpBin_Direction_Backward.Title = "Direction Backward";
            this.grpBin_Foot_Stretched.Title = "Foot Stretched";
            this.grpBin_Foot_Closed.Title = "Foot Closed";
            this.grpBin_Balance_Forward.Title = "Balance Forward";
            this.grpBin_Balance_Backward.Title = "Balance Backward";
            this.grpBin_Balance_LeaningLeft.Title = "Leaning Left";
            this.grpBin_Balance_LeaningRight.Title = "Leaning Right";
        }

        void ResetGraphData()
        {
            
        }

        void ResetONIFile(string file_name)
        {
            oni_file_ = file_name;
            timer.Stop();
            controller.TurnOff();
            controller.TurnOnONIFile(oni_file_);
            timer.Start();
        }

        void ResetKinectSensor()
        {
            oni_file_ = "";
            timer.Stop();
            controller.TurnOff();
            controller.TurnOnKinectSensor();
            timer.Start();
        }

        void timer_Tick(object sender, EventArgs e)
        {
            controller.QuerySensor();

            WriteableBitmap bmp = controller.GrabCurrentColorFrame();
            this.imgKinect.Source = bmp;

            feature_extractor.ExtractFeatureNewFrame();
            int buffer_feature_size = feature_extractor.GetActualFeatureBufferSize();
            if (buffer_feature_size >= 5)
            {
                this.grpVelocity_LeftHand.SetDataReal(feature_extractor.GetFeature_VelocityLeftHand());
                this.grpVelocity_RightHand.SetDataReal(feature_extractor.GetFeature_VelocityRightHand());
                this.grpVelocity_Global.SetDataReal(feature_extractor.GetFeature_VelocityGlobal());
                this.grpVelocity_Foot.SetDataReal(feature_extractor.GetFeature_VelocityFoot());
                this.grpEnergy.SetDataReal(feature_extractor.GetFeature_Energy());
                this.grpDirection_BackForth.SetDataReal(feature_extractor.GetDirection_BackForth());
                this.grpFootStretch.SetDataReal(feature_extractor.GetFeature_FootStretch());
                this.grpBalanceBackForth.SetDataReal(feature_extractor.GetFeature_BalanceBackForth());
                this.grpBalanceLeftRight.SetDataReal(feature_extractor.GetFeature_BalanceLeftRight());

                this.grpVelocity_LeftHand.DrawGraph();
                this.grpVelocity_RightHand.DrawGraph();
                this.grpVelocity_Global.DrawGraph();
                this.grpVelocity_Foot.DrawGraph();
                this.grpEnergy.DrawGraph();
                this.grpDirection_BackForth.DrawGraph();
                this.grpFootStretch.DrawGraph();
                this.grpBalanceBackForth.DrawGraph();
                this.grpBalanceLeftRight.DrawGraph();

                this.grpBin_VelocityLeftHand_Low.DataBinary = overall_assessment.GetBinary_VelocityLeftHand_Low();
                this.grpBin_VelocityLeftHand_High.DataBinary = overall_assessment.GetBinary_VelocityLeftHand_High();
                this.grpBin_VelocityRightHand_Low.DataBinary = overall_assessment.GetBinary_VelocityRightHand_Low();
                this.grpBin_VelocityRightHand_High.DataBinary = overall_assessment.GetBinary_VelocityRightHand_High();
                this.grpBin_VelocityGlobal_Low.DataBinary = overall_assessment.GetBinary_VelocityGlobal_Low();
                this.grpBin_VelocityGlobal_High.DataBinary = overall_assessment.GetBinary_VelocityGlobal_High();
                this.grpBin_VelocityFoot_Low.DataBinary = overall_assessment.GetBinary_VelocityFoot_Low();
                this.grpBin_VelocityFoot_High.DataBinary = overall_assessment.GetBinary_VelocityFoot_High();
                this.grpBin_Energy_Low.DataBinary = overall_assessment.GetBinary_Energy_Low();
                this.grpBin_Energy_High.DataBinary = overall_assessment.GetBinary_Energy_High();
                this.grpBin_Direction_Forward.DataBinary = overall_assessment.GetBinary_Direction_Forward();
                this.grpBin_Direction_Backward.DataBinary = overall_assessment.GetBinary_Direction_Backward();
                this.grpBin_Foot_Stretched.DataBinary = overall_assessment.GetBinary_Foot_Stretched();
                this.grpBin_Foot_Closed.DataBinary = overall_assessment.GetBinary_Foot_Closed();
                this.grpBin_Balance_Forward.DataBinary = overall_assessment.GetBinary_Balance_Forward();
                this.grpBin_Balance_Backward.DataBinary = overall_assessment.GetBinary_Balance_Backward();
                this.grpBin_Balance_LeaningLeft.DataBinary = overall_assessment.GetBinary_Balance_Left();
                this.grpBin_Balance_LeaningRight.DataBinary = overall_assessment.GetBinary_Balance_Right();

                this.grpBin_VelocityLeftHand_Low.DrawGraph();
                this.grpBin_VelocityLeftHand_High.DrawGraph();
                this.grpBin_VelocityRightHand_Low.DrawGraph();
                this.grpBin_VelocityRightHand_High.DrawGraph();
                this.grpBin_VelocityGlobal_Low.DrawGraph();
                this.grpBin_VelocityGlobal_High.DrawGraph();
                this.grpBin_VelocityFoot_Low.DrawGraph();
                this.grpBin_VelocityFoot_High.DrawGraph();
                this.grpBin_Energy_Low.DrawGraph();
                this.grpBin_Energy_High.DrawGraph();
                this.grpBin_Direction_Forward.DrawGraph();
                this.grpBin_Direction_Backward.DrawGraph();
                this.grpBin_Foot_Stretched.DrawGraph();
                this.grpBin_Foot_Closed.DrawGraph();
                this.grpBin_Balance_Forward.DrawGraph();
                this.grpBin_Balance_Backward.DrawGraph();
                this.grpBin_Balance_LeaningLeft.DrawGraph();
                this.grpBin_Balance_LeaningRight.DrawGraph();
            }

            overall_assessment.AssessOneFeatureSet();
            int buffer_score_size = overall_assessment.GetActualScoreBufferSize();
            if (buffer_score_size >= 5)
            {
                this.grpScore_HandGesture.SetDataReal(overall_assessment.GetScore_HandGesture());
                this.grpScore_GlobalMovement.SetDataReal(overall_assessment.GetScore_GlobalMovement());
                this.grpScore_Energy.SetDataReal(overall_assessment.GetScore_Energy());
                this.grpScore_Direction.SetDataReal(overall_assessment.GetScore_Direction());
                this.grpScore_Posture.SetDataReal(overall_assessment.GetScore_Posture());
                this.grpScore_Overall.SetDataReal(overall_assessment.GetScore_Overall());

                this.grpScore_HandGesture.DrawGraph();
                this.grpScore_GlobalMovement.DrawGraph();
                this.grpScore_Energy.DrawGraph();
                this.grpScore_Direction.DrawGraph();
                this.grpScore_Posture.DrawGraph();
                this.grpScore_Overall.DrawGraph();

            }
        }

        List<float> Fill_The_Buffer(List<float> data, int buffer_size)
        {
            List<float> result = new List<float>(data);
            if (result.Count < buffer_size)
            {
                for (int i = 0; i < buffer_size - result.Count; i++)
                {
                    result.Insert(0, 0);
                }
            }
            return result;
        }

        List<bool> Fill_The_Buffer(List<bool> data, int buffer_size)
        {
            List<bool> result = new List<bool>(data);
            if (result.Count < buffer_size)
            {
                for (int i = 0; i < buffer_size - result.Count; i++)
                {
                    result.Insert(0, false);
                }
            }
            return result;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            controller.TurnOff();
        }

        private void btnOpenFile_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dialog = new Microsoft.Win32.OpenFileDialog();
            dialog.DefaultExt = ".oni";
            if (dialog.ShowDialog() == true)
            {
                ResetONIFile(dialog.FileName);
            }
        }

        private void btnTurnOnSensor_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
