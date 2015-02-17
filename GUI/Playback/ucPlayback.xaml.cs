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

namespace GUI.Playback
{
    /// <summary>
    /// Interaction logic for ucPlayback.xaml
    /// </summary>
    public partial class ucPlayback : UserControl
    {
        private const string data_folder_ = @"G:\Development of SmartTutor\test_data\2015-2-17-14.35.52\";
        private ResultReader result_reader_;

        public ucPlayback()
        {
            InitializeComponent();
            this.media_player.LoadVideo(data_folder_ + "camera_data.avi");
            result_reader_ = new ResultReader(data_folder_);
            result_reader_.ReadData();
            

            //this.grpEnergyScore.DrawGraph(result_reader_.ScoresEnergy);
            //this.grpBin_EnergyHigh.DrawBinaryGraph(result_reader_.Binary_Energy_High);
            //this.grpBin_EnergyLow.DrawBinaryGraph(result_reader_.Binary_Energy_Low);
        }

        private void DrawGraphs_()
        {
            this.grpScore_Overall.DrawGraph(result_reader_.ScoresOverall);
            this.grpScore_Energy.DrawGraph(result_reader_.ScoresEnergy);
            this.grpScore_Posture.DrawGraph(result_reader_.ScoresPosture);
            this.grpScore_GlobalDisplacement.DrawGraph(result_reader_.ScoresMovement);
            this.grpScore_HandGestures.DrawGraph(result_reader_.ScoresGesture);

            this.grpBin_Energy_High.DrawBinaryGraph(result_reader_.Binary_Energy_High);
            this.grpBin_Energy_Low.DrawBinaryGraph(result_reader_.Binary_Energy_Low);

            this.grpBin_Lean_Left.DrawBinaryGraph(result_reader_.Binary_Lean_Left);
            this.grpBin_Lean_Right.DrawBinaryGraph(result_reader_.Binary_Lean_Right);
            this.grpBin_Lean_Backward.DrawBinaryGraph(result_reader_.Binary_Lean_Backward);
            this.grpBin_Lean_Forward.DrawBinaryGraph(result_reader_.Binary_Lean_Forward);
            this.grpBin_Stable.DrawBinaryGraph(result_reader_.Binary_Stable);
            this.grpBin_Unstable.DrawBinaryGraph(result_reader_.Binary_Unstable);

            this.grpBin_Disp_Too_Much.DrawBinaryGraph(result_reader_.Binary_Disp_Too_Much);
            this.grpBin_Disp_Too_Little.DrawBinaryGraph(result_reader_.Binary_Disp_Too_Little);
            this.grpBin_Disp_Forward.DrawBinaryGraph(result_reader_.Binary_Disp_Forward);
            this.grpBin_Disp_Backward.DrawBinaryGraph(result_reader_.Binary_Disp_Backward);

            this.grpBin_Hand_TooMuch.DrawBinaryGraph(result_reader_.Binary_Hand_Too_Much);
            this.grpBin_Hand_TooLittle.DrawBinaryGraph(result_reader_.Binary_Hand_Too_Little);
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            DrawGraphs_();
        }
    }
}
