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
    class FeatureExtractor
    {
        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IExtractFeatureNewFrame();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int IGetActualFeatureBufferSize();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_VelocityLeftHand();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_VelocityRightHand();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_VelocityGlobal();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_VelocityFoot();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_Energy();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_DirectionBackForth();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_FootStretch();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_BalanceBackForth();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeature_BalanceLeftRight();



        public void ExtractFeatureNewFrame()
        {
            IExtractFeatureNewFrame();
        }

        public int GetActualFeatureBufferSize()
        {
            return IGetActualFeatureBufferSize();
        }

        List<float> Copy_IntPtr(IntPtr input)
        {
            int size = IGetActualFeatureBufferSize();
            float[] buffer = new float[size];
            Marshal.Copy(input, buffer, 0, buffer.Length);
            List<float> result = new List<float>(buffer);
            Marshal.FreeHGlobal(input);
            return result;
        }

        public List<float> GetFeature_VelocityLeftHand()
        {
            return Copy_IntPtr(IGetFeature_VelocityLeftHand());
        }

        public List<float> GetFeature_VelocityRightHand()
        {
            return Copy_IntPtr(IGetFeature_VelocityRightHand());
        }

        public List<float> GetFeature_VelocityGlobal()
        {
            return Copy_IntPtr(IGetFeature_VelocityGlobal());
        }

        public List<float> GetFeature_VelocityFoot()
        {
            return Copy_IntPtr(IGetFeature_VelocityFoot());
        }

        public List<float> GetFeature_Energy()
        {
            return Copy_IntPtr(IGetFeature_Energy());
        }

        public List<float> GetDirection_BackForth()
        {
            return Copy_IntPtr(IGetFeature_DirectionBackForth());
        }

        public List<float> GetFeature_FootStretch()
        {
            return Copy_IntPtr(IGetFeature_FootStretch());
        }

        public List<float> GetFeature_BalanceBackForth()
        {
            return Copy_IntPtr(IGetFeature_BalanceBackForth());
        }

        public List<float> GetFeature_BalanceLeftRight()
        {
            return Copy_IntPtr(IGetFeature_BalanceLeftRight());
        }
    }
}
