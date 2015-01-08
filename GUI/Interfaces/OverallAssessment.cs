using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows;

namespace GUI.Interfaces
{
    class OverallAssessment
    {
        //////////////////////////////////////////////////////////////////////////
        #region Compute Score

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IAssessOneFeatureSet();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int IGetActualScoreBufferSize();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetScore_HandGesture();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetScore_GlobalMovement();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetScore_Energy();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetScore_Direction();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetScore_Posture();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetScore_Overall();

        public void AssessOneFeatureSet()
        {
            IAssessOneFeatureSet();
        }

        public int GetActualScoreBufferSize()
        {
            return IGetActualScoreBufferSize();
        }

        List<float> Copy_IntPtr(IntPtr input)
        {
            int size = IGetActualScoreBufferSize();
            float[] buffer = new float[size];
            Marshal.Copy(input, buffer, 0, buffer.Length);
            List<float> result = new List<float>(buffer);
            Marshal.FreeHGlobal(input);
            return result;
        }

        public List<float> GetScore_HandGesture()
        {
            return Copy_IntPtr(IGetScore_HandGesture());
        }

        public List<float> GetScore_GlobalMovement()
        {
            return Copy_IntPtr(IGetScore_GlobalMovement());
        }

        public List<float> GetScore_Energy()
        {
            return Copy_IntPtr(IGetScore_Energy());
        }

        public List<float> GetScore_Direction()
        {
            return Copy_IntPtr(IGetScore_Direction());
        }

        public List<float> GetScore_Posture()
        {
            return Copy_IntPtr(IGetScore_Posture());
        }

        public List<float> GetScore_Overall()
        {
            return Copy_IntPtr(IGetScore_Overall());
        }

        #endregion


        //////////////////////////////////////////////////////////////////////////
        #region Get binary appearance of codewords

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_VelocityLeftHand_Low();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_VelocityLeftHand_High();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_VelocityRightHand_Low();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_VelocityRightHand_High();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_VelocityGlobal_Low();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_VelocityGlobal_High();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_VelocityFoot_Low();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_VelocityFoot_High();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Energy_Low();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Energy_High();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Direction_Backward();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Direction_Forward();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Foot_Stretched();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Foot_Closed();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Balance_Backward();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Balance_Forward();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Balance_Left();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetBinary_Balance_Right();

        List<bool> Copy_IntPtr_bool(IntPtr input)
        {
            int size = IGetActualScoreBufferSize();
            byte[] buffer = new byte[size];
            Marshal.Copy(input, buffer, 0, buffer.Length);
            List<bool> result = new List<bool>(size);
            for (int i = 0; i < size; i++)
            {
                if (buffer[i] == 0)
                    result.Add(false);
                else
                    result.Add(true);
            }
            Marshal.FreeHGlobal(input);
            return result;
        }

        public List<bool> GetBinary_VelocityLeftHand_Low()
        {
            return Copy_IntPtr_bool(IGetBinary_VelocityLeftHand_Low());
        }

        public List<bool> GetBinary_VelocityLeftHand_High()
        {
            return Copy_IntPtr_bool(IGetBinary_VelocityLeftHand_High());
        }

        public List<bool> GetBinary_VelocityRightHand_Low()
        {
            return Copy_IntPtr_bool(IGetBinary_VelocityRightHand_Low());
        }

        public List<bool> GetBinary_VelocityRightHand_High()
        {
            return Copy_IntPtr_bool(IGetBinary_VelocityRightHand_High());
        }

        public List<bool> GetBinary_VelocityGlobal_Low()
        {
            return Copy_IntPtr_bool(IGetBinary_VelocityGlobal_Low());
        }

        public List<bool> GetBinary_VelocityGlobal_High()
        {
            return Copy_IntPtr_bool(IGetBinary_VelocityGlobal_High());
        }

        public List<bool> GetBinary_VelocityFoot_Low()
        {
            return Copy_IntPtr_bool(IGetBinary_VelocityFoot_Low());
        }

        public List<bool> GetBinary_VelocityFoot_High()
        {
            return Copy_IntPtr_bool(IGetBinary_VelocityFoot_High());
        }

        public List<bool> GetBinary_Energy_Low()
        {
            return Copy_IntPtr_bool(IGetBinary_Energy_Low());
        }

        public List<bool> GetBinary_Energy_High()
        {
            return Copy_IntPtr_bool(IGetBinary_Energy_High());
        }

        public List<bool> GetBinary_Direction_Backward()
        {
            return Copy_IntPtr_bool(IGetBinary_Direction_Backward());
        }

        public List<bool> GetBinary_Direction_Forward()
        {
            return Copy_IntPtr_bool(IGetBinary_Direction_Forward());
        }

        public List<bool> GetBinary_Foot_Stretched()
        {
            return Copy_IntPtr_bool(IGetBinary_Foot_Stretched());
        }

        public List<bool> GetBinary_Foot_Closed()
        {
            return Copy_IntPtr_bool(IGetBinary_Foot_Closed());
        }

        public List<bool> GetBinary_Balance_Backward()
        {
            return Copy_IntPtr_bool(IGetBinary_Balance_Backward());
        }

        public List<bool> GetBinary_Balance_Forward()
        {
            return Copy_IntPtr_bool(IGetBinary_Balance_Forward());
        }

        public List<bool> GetBinary_Balance_Left()
        {
            return Copy_IntPtr_bool(IGetBinary_Balance_Left());
        }

        public List<bool> GetBinary_Balance_Right()
        {
            return Copy_IntPtr_bool(IGetBinary_Balance_Right());
        }

        #endregion
    }
}