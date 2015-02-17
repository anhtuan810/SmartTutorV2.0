using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI.Interfaces;
using System.IO;

namespace GUI.Practice
{
    /// <summary>
    /// Record real-time analysis result to HDD
    /// Only record what is needed for playing back later
    /// </summary>
    class ResultRecorder
    {
        private string data_folder_;
        private KinectController kinect_controller_;
        private FeatureExtractor feature_extractor_;
        private OverallAssessment overall_assessment_;

        private BinaryWriter writer_skeleton_;
        private BinaryWriter writer_score_overall_;
        private BinaryWriter writer_score_energy_;
        private BinaryWriter writer_score_global_movement_;
        private BinaryWriter writer_score_hand_gesture_;
        private BinaryWriter writer_score_posture_;

        private BinaryWriter writer_energy_high_;
        private BinaryWriter writer_energy_low_;
        private BinaryWriter writer_impulse_;

        private BinaryWriter writer_leaning_left_;
        private BinaryWriter writer_leaning_right_;
        private BinaryWriter writer_leaning_backward_;
        private BinaryWriter writer_leaning_forward_;
        private BinaryWriter writer_stable_;
        private BinaryWriter writer_unstable_;

        private BinaryWriter writer_disp_too_much_;
        private BinaryWriter writer_disp_too_little_;
        private BinaryWriter writer_disp_backward_;
        private BinaryWriter writer_disp_forward_;

        private BinaryWriter writer_hand_gesture_too_much_;
        private BinaryWriter writer_hand_gesture_too_little_;
            
        public ResultRecorder(string data_folder, ref KinectController kinect_controller, ref FeatureExtractor feature_extractor, ref OverallAssessment overall_assessment)
        {
            data_folder_ = data_folder;
            kinect_controller_ = kinect_controller;
            feature_extractor_ = feature_extractor;
            overall_assessment_ = overall_assessment;
        }

        public void Initiate()
        {
            writer_score_overall_ = new BinaryWriter(File.Open(data_folder_ + "score_overall.dat", FileMode.Create));
            writer_score_energy_ = new BinaryWriter(File.Open(data_folder_ + "score_energy.dat", FileMode.Create));
            writer_score_global_movement_ = new BinaryWriter(File.Open(data_folder_ + "score_global_displacement.dat", FileMode.Create));
            writer_score_hand_gesture_ = new BinaryWriter(File.Open(data_folder_ + "score_hand_gesture.dat", FileMode.Create));
            writer_score_posture_ = new BinaryWriter(File.Open(data_folder_ + "score_posture.dat", FileMode.Create));
            writer_skeleton_ = new BinaryWriter(File.Open(data_folder_ + "skeleton.dat", FileMode.Create));

            writer_energy_high_ = new BinaryWriter(File.Open(data_folder_ + "binary_energy_high.dat", FileMode.Create));
            writer_energy_low_ = new BinaryWriter(File.Open(data_folder_ + "binary_energy_low.dat", FileMode.Create));

            writer_leaning_left_ = new BinaryWriter(File.Open(data_folder_ + "leaning_left.dat", FileMode.Create));
            writer_leaning_right_ = new BinaryWriter(File.Open(data_folder_ + "leaning_right.dat", FileMode.Create));
            writer_leaning_backward_ = new BinaryWriter(File.Open(data_folder_ + "leaning_backward.dat", FileMode.Create));
            writer_leaning_forward_ = new BinaryWriter(File.Open(data_folder_ + "leaning_forward.dat", FileMode.Create));
            writer_stable_ = new BinaryWriter(File.Open(data_folder_ + "stable.dat", FileMode.Create));
            writer_unstable_ = new BinaryWriter(File.Open(data_folder_ + "unstable.dat", FileMode.Create));

            writer_disp_too_much_ = new BinaryWriter(File.Open(data_folder_ + "disp_too_much.dat", FileMode.Create));
            writer_disp_too_little_ = new BinaryWriter(File.Open(data_folder_ + "disp_too_little.dat", FileMode.Create));
            writer_disp_backward_ = new BinaryWriter(File.Open(data_folder_ + "disp_backward.dat", FileMode.Create));
            writer_disp_forward_ = new BinaryWriter(File.Open(data_folder_ + "disp_forward.dat", FileMode.Create));

            writer_hand_gesture_too_much_ = new BinaryWriter(File.Open(data_folder_ + "hand_gesture_too_much.dat", FileMode.Create));
            writer_hand_gesture_too_little_ = new BinaryWriter(File.Open(data_folder_ + "hand_gesture_too_little.dat", FileMode.Create));
        }

        public void RecordMostRecentSample()
        {
            int sample_count = overall_assessment_.GetActualScoreBufferSize();

            writer_score_overall_.Write((double)overall_assessment_.GetScore_Overall()[sample_count - 1]);
            writer_score_energy_.Write((double)overall_assessment_.GetScore_Energy()[sample_count - 1]);
            writer_score_global_movement_.Write((double)overall_assessment_.GetScore_GlobalMovement()[sample_count - 1]);
            writer_score_hand_gesture_.Write((double)overall_assessment_.GetScore_HandGesture()[sample_count - 1]);
            writer_score_posture_.Write((double)overall_assessment_.GetScore_Posture()[sample_count - 1]);

            writer_energy_high_.Write(overall_assessment_.GetBinary_Energy_High()[sample_count - 1]);
            writer_energy_low_.Write(overall_assessment_.GetBinary_Energy_Low()[sample_count - 1]);

            writer_leaning_left_.Write(overall_assessment_.GetBinary_Balance_Left_Smoothed()[sample_count - 1]);
            writer_leaning_right_.Write(overall_assessment_.GetBinary_Balance_Right_Smoothed()[sample_count - 1]);
            writer_leaning_backward_.Write(overall_assessment_.GetBinary_Balance_Backward_Smoothed()[sample_count - 1]);
            writer_leaning_forward_.Write(overall_assessment_.GetBinary_Balance_Forward_Smoothed()[sample_count - 1]);
            writer_stable_.Write(overall_assessment_.GetBinary_Stability_Stable()[sample_count - 1]);
            writer_unstable_.Write(overall_assessment_.GetBinary_Stability_Unstable()[sample_count - 1]);

            writer_disp_too_much_.Write(overall_assessment_.GetBinary_VelocityGlobal_High()[sample_count - 1]);
            writer_disp_too_little_.Write(overall_assessment_.GetBinary_VelocityGlobal_Low()[sample_count - 1]);
        }

        public void Finalise()
        {
            writer_score_overall_.Close();
            writer_score_energy_.Close();
            writer_score_global_movement_.Close();
            writer_score_hand_gesture_.Close();
            writer_score_posture_.Close();

            writer_energy_high_.Close();
            writer_energy_low_.Close();

            writer_leaning_left_.Close();
            writer_leaning_right_.Close();
            writer_leaning_backward_.Close();
            writer_leaning_forward_.Close();
            writer_stable_.Close();
            writer_unstable_.Close();

            writer_disp_too_much_.Close();
            writer_disp_too_little_.Close();
        }
    }
}
