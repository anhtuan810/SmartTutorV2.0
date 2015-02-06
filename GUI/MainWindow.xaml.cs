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
        System.Windows.Threading.DispatcherTimer timer_ = new System.Windows.Threading.DispatcherTimer();
        private GUI.Interfaces.SensorController controller_ = new SensorController();
        private GUI.Interfaces.FeatureExtractor feature_extractor_ = new FeatureExtractor();
        private GUI.Interfaces.OverallAssessment overall_assessment_ = new OverallAssessment();
        private GUI.Interfaces.RealtimeFeedback realtime_feedback_ = new RealtimeFeedback();
        private string oni_file_ = @"G:\Research materials\[+++++] Database collected in QMUL\ONI\11.oni";

        public MainWindow()
        {
            InitializeComponent();
            SetGraphTitles();

            ResetONIReader();
            //ResetKinectSensor();

            timer_.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer_.Tick += timer_Tick;
            timer_.Start();
        }


        


        /////////////////////////////////////////////////////////////////////////////////////////////////
        #region Internal Processings

        List<float> Fill_The_Buffer_(List<float> data, int buffer_size)
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

        List<bool> Fill_The_Buffer_(List<bool> data, int buffer_size)
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

        void SetGraphTitles()
        {
            this.grpVelocity_LeftHand.TitleReal = "Velocity Left Hand";
            this.grpVelocity_RightHand.TitleReal = "Velocity Right Hand";
            this.grpVelocity_Global.TitleReal = "Velocity Global";
            this.grpVelocity_Hands.TitleReal = "Velocity Hands";
            this.grpImpulsiveness.TitleReal = "Impulsiveness";
            this.grpEnergy.TitleReal = "Energy";
            this.grpDirection_BackForth.TitleReal = "Direction";
            this.grpFootStretch.TitleReal = "Foot Stretch";
            this.grpBalanceBackForth.TitleReal = "Balance Back Forth";
            this.grpBalanceLeftRight.TitleReal = "Balance Left Right";
            this.grpOpenness.TitleReal = "Openness";
            this.grpStability.TitleReal = "Stability";

            this.grpScore_HandGesture.TitleReal = "Score Hand Gesture";
            this.grpScore_GlobalMovement.TitleReal = "Score Global Movement";
            this.grpScore_Energy.TitleReal = "Score Energy";
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
            this.grpBin_Stability_Stable.Title = "Stable";
            this.grpBin_Stability_Unstable.Title = "Unstable";
            this.grpBin_Openness_High.Title = "Opened";
            this.grpBin_Openness_Low.Title = "Closed";
        }

        void SetGraphData()
        {
            this.grpVelocity_LeftHand.DrawRealData(feature_extractor_.GetFeature_VelocityLeftHand());
            this.grpVelocity_RightHand.DrawRealData(feature_extractor_.GetFeature_VelocityRightHand());
            this.grpVelocity_Global.DrawRealData(feature_extractor_.GetFeature_VelocityGlobal());
            this.grpVelocity_Hands.DrawRealData(feature_extractor_.GetFeature_VelocityHands());
            this.grpEnergy.DrawRealData(feature_extractor_.GetFeature_Energy());
            this.grpDirection_BackForth.DrawRealData(feature_extractor_.GetDirection_BackForth());
            this.grpFootStretch.DrawRealData(feature_extractor_.GetFeature_FootStretch());
            this.grpBalanceBackForth.DrawRealData(feature_extractor_.GetFeature_BalanceBackForth());
            this.grpBalanceLeftRight.DrawRealData(feature_extractor_.GetFeature_BalanceLeftRight());
            this.grpOpenness.DrawRealData(feature_extractor_.GetFeature_Openness());
            this.grpImpulsiveness.DrawRealData(feature_extractor_.GetFeature_Impulsiveness());
            this.grpStability.DrawRealData(feature_extractor_.GetFeature_Stability());
        }

        void ResetONIReader()
        {
            this.txtONIfile.Text = oni_file_;
            this.radONI.IsChecked = true;
            this.radSensor.IsChecked = false;

            timer_.Stop();
            controller_.TurnOff();
            controller_.TurnOnONIFile(oni_file_);
            timer_.Start();
        }

        void ResetKinectSensor()
        {
            oni_file_ = "";
            this.radONI.IsChecked = false;
            this.radSensor.IsChecked = true;

            this.txtONIfile.Text = oni_file_;
            timer_.Stop();
            controller_.TurnOff();
            controller_.TurnOnKinectSensor();
            timer_.Start();
        }

        #endregion
        /////////////////////////////////////////////////////////////////////////////////////////////////


        /////////////////////////////////////////////////////////////////////////////////////////////////
        #region User intraction with form
        
        void timer_Tick(object sender, EventArgs e)
        {
            //
            // Display image from sensor
            //
            controller_.QuerySensor();
            WriteableBitmap bmp = controller_.GrabCurrentColorFrame();
            this.imgKinect.Source = bmp;

            //
            //  Perform feature extraction and then display on the form as graphs
            //
            feature_extractor_.ExtractFeatureNewFrame();
            int buffer_feature_size = feature_extractor_.GetActualFeatureBufferSize();
            if (buffer_feature_size >= 5)
            {
                SetGraphData();
            }

            //
            //  Perform overall assessment and then display on the form as graphs  
            //
            overall_assessment_.AssessOneFeatureSet();
            int buffer_score_size = overall_assessment_.GetActualScoreBufferSize();
            if (buffer_score_size >= 10)
            {
                this.grpBin_VelocityLeftHand_Low.DrawBinaryData(overall_assessment_.GetBinary_VelocityLeftHand_Low());
                this.grpBin_VelocityLeftHand_High.DrawBinaryData(overall_assessment_.GetBinary_VelocityLeftHand_High());
                this.grpBin_VelocityRightHand_Low.DrawBinaryData(overall_assessment_.GetBinary_VelocityRightHand_Low());
                this.grpBin_VelocityRightHand_High.DrawBinaryData(overall_assessment_.GetBinary_VelocityRightHand_High());
                this.grpBin_VelocityGlobal_Low.DrawBinaryData(overall_assessment_.GetBinary_VelocityGlobal_Low());
                this.grpBin_VelocityGlobal_High.DrawBinaryData(overall_assessment_.GetBinary_VelocityGlobal_High());
                this.grpBin_VelocityFoot_Low.DrawBinaryData(overall_assessment_.GetBinary_VelocityFoot_Low());
                this.grpBin_VelocityFoot_High.DrawBinaryData(overall_assessment_.GetBinary_VelocityFoot_High());
                this.grpBin_Energy_Low.DrawBinaryData(overall_assessment_.GetBinary_Energy_Low());
                this.grpBin_Energy_High.DrawBinaryData(overall_assessment_.GetBinary_Energy_High());
                this.grpBin_Direction_Forward.DrawBinaryData(overall_assessment_.GetBinary_Direction_Forward());
                this.grpBin_Direction_Backward.DrawBinaryData(overall_assessment_.GetBinary_Direction_Backward());
                this.grpBin_Foot_Stretched.DrawBinaryData(overall_assessment_.GetBinary_Foot_Stretched_Smoothed());
                this.grpBin_Foot_Closed.DrawBinaryData(overall_assessment_.GetBinary_Foot_Closed_Smoothed());
                this.grpBin_Balance_Forward.DrawBinaryData(overall_assessment_.GetBinary_Balance_Forward_Smoothed());
                this.grpBin_Balance_Backward.DrawBinaryData(overall_assessment_.GetBinary_Balance_Backward_Smoothed());
                this.grpBin_Balance_LeaningLeft.DrawBinaryData(overall_assessment_.GetBinary_Balance_Left_Smoothed());
                this.grpBin_Balance_LeaningRight.DrawBinaryData(overall_assessment_.GetBinary_Balance_Right_Smoothed());
                this.grpBin_Stability_Stable.DrawBinaryData(overall_assessment_.GetBinary_Stability_Stable());
                this.grpBin_Stability_Unstable.DrawBinaryData(overall_assessment_.GetBinary_Stability_Unstable());
                this.grpBin_Openness_High.DrawBinaryData(overall_assessment_.GetBinary_Openness_High_Smoothed());
                this.grpBin_Openness_Low.DrawBinaryData(overall_assessment_.GetBinary_Openness_Low_Smoothed());

                this.grpScore_HandGesture.DrawRealData(overall_assessment_.GetScore_HandGesture());
                this.grpScore_GlobalMovement.DrawRealData(overall_assessment_.GetScore_GlobalMovement());
                this.grpScore_Energy.DrawRealData(overall_assessment_.GetScore_Energy());
                this.grpScore_Posture.DrawRealData(overall_assessment_.GetScore_Posture());
                this.grpScore_Overall.DrawRealData(overall_assessment_.GetScore_Overall());
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            controller_.TurnOff();
        }

        #endregion

        private void btnOpenONI_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dialog = new Microsoft.Win32.OpenFileDialog();
            dialog.DefaultExt = ".oni";
            if (dialog.ShowDialog() == true)
            {
                oni_file_ = dialog.FileName;
                ResetONIReader();
            }
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
