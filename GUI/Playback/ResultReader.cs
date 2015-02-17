using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace GUI.Playback
{
    /// <summary>
    /// Read recorded results
    /// </summary>
    class ResultReader
    {
        private string data_folder_;
        private List<double> scores_overall_ = new List<double>();
        private List<double> scores_posture_ = new List<double>();
        private List<double> scores_gesture_ = new List<double>();
        private List<double> scores_movement_ = new List<double>();
        private List<double> scores_energy_ = new List<double>();

        private List<bool> binary_energy_high_ = new List<bool>();
        private List<bool> binary_energy_low_ = new List<bool>();

        private List<bool> binary_lean_left_ = new List<bool>();
        private List<bool> binary_lean_right_ = new List<bool>();
        private List<bool> binary_lean_forward_ = new List<bool>();
        private List<bool> binary_lean_backward_ = new List<bool>();
        private List<bool> binary_stable_ = new List<bool>();
        private List<bool> binary_unstable_ = new List<bool>();

        private List<bool> binary_disp_too_much_ = new List<bool>();
        private List<bool> binary_disp_too_little_ = new List<bool>();
        private List<bool> binary_disp_backward_ = new List<bool>();
        private List<bool> binary_disp_forward_ = new List<bool>();

        private List<bool> binary_hand_too_much_ = new List<bool>();
        private List<bool> binary_hand_too_little_ = new List<bool>();

        public List<double> ScoresOverall { get { return scores_overall_; } }
        public List<double> ScoresPosture { get { return scores_posture_; } }
        public List<double> ScoresGesture { get { return scores_gesture_; } }
        public List<double> ScoresMovement { get { return scores_movement_; } }
        public List<double> ScoresEnergy { get { return scores_energy_; } }

        public List<bool> Binary_Energy_High { get { return binary_energy_high_; } }
        public List<bool> Binary_Energy_Low { get { return binary_energy_low_; } }

        public List<bool> Binary_Lean_Left { get { return binary_lean_left_; } }
        public List<bool> Binary_Lean_Right { get { return binary_lean_right_; } }
        public List<bool> Binary_Lean_Forward { get { return binary_lean_forward_; } }
        public List<bool> Binary_Lean_Backward { get { return binary_lean_backward_; } }
        public List<bool> Binary_Stable { get { return binary_stable_; } }
        public List<bool> Binary_Unstable { get { return binary_unstable_; } }

        public List<bool> Binary_Disp_Too_Much { get { return binary_disp_too_much_; } }
        public List<bool> Binary_Disp_Too_Little { get { return binary_disp_too_little_; } }
        public List<bool> Binary_Disp_Forward { get { return binary_disp_forward_; } }
        public List<bool> Binary_Disp_Backward { get { return binary_disp_backward_; } }

        public List<bool> Binary_Hand_Too_Much { get { return binary_hand_too_much_; } }
        public List<bool> Binary_Hand_Too_Little { get { return binary_hand_too_little_; } }

        public ResultReader(string data_folder)
        {
            data_folder_ = data_folder;
        }

        public void ReadData()
        {
            scores_overall_ = Read_One_Data_File_(data_folder_ + "score_overall.dat");
            scores_posture_ = Read_One_Data_File_(data_folder_ + "score_posture.dat");
            scores_gesture_ = Read_One_Data_File_(data_folder_ + "score_hand_gesture.dat");
            scores_movement_ = Read_One_Data_File_(data_folder_ + "score_global_displacement.dat");
            scores_energy_ = Read_One_Data_File_(data_folder_ + "score_energy.dat");

            binary_energy_high_ = Read_One_Binary_File(data_folder_ + "binary_energy_high.dat");
            binary_energy_low_ = Read_One_Binary_File(data_folder_ + "binary_energy_low.dat");

            binary_lean_left_ = Read_One_Binary_File(data_folder_ + "leaning_left.dat");
            binary_lean_right_ = Read_One_Binary_File(data_folder_ + "leaning_right.dat");
            binary_lean_forward_ = Read_One_Binary_File(data_folder_ + "leaning_forward.dat");
            binary_lean_backward_ = Read_One_Binary_File(data_folder_ + "leaning_backward.dat");
            binary_stable_ = Read_One_Binary_File(data_folder_ + "stable.dat");
            binary_unstable_ = Read_One_Binary_File(data_folder_ + "unstable.dat");

            binary_disp_too_much_ = Read_One_Binary_File(data_folder_ + "disp_too_much.dat");
            binary_disp_too_little_ = Read_One_Binary_File(data_folder_ + "disp_too_little.dat");
            binary_disp_forward_ = Read_One_Binary_File(data_folder_ + "disp_forward.dat");
            binary_disp_backward_ = Read_One_Binary_File(data_folder_ + "disp_backward.dat");

            binary_hand_too_much_ = Read_One_Binary_File(data_folder_ + "hand_gesture_too_much.dat");
            binary_hand_too_little_ = Read_One_Binary_File(data_folder_ + "hand_gesture_too_little.dat");
        }

        private List<double> Read_One_Data_File_(string file_name)
        {
            List<double> data = new List<double>();
            if (File.Exists(file_name))
            {                
                using (BinaryReader reader = new BinaryReader(File.Open(file_name, FileMode.Open)))
                {
                    while (reader.BaseStream.Position != reader.BaseStream.Length)
                    {
                        double sample = reader.ReadDouble();
                        data.Add(sample);
                    }
                    reader.Close();
                }
            }
            return data;
        }

        private List<bool> Read_One_Binary_File(string file_name)
        {
            List<bool> data = new List<bool>();
            if (File.Exists(file_name))
            {
                using (BinaryReader reader = new BinaryReader(File.Open(file_name, FileMode.Open)))
                {
                    while (reader.BaseStream.Position != reader.BaseStream.Length)
                    {
                        bool sample = reader.ReadBoolean();
                        data.Add(sample);
                    }
                    reader.Close();
                }
            }
            return data;
        }
    }
}
