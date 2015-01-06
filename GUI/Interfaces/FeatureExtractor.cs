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

        float[] Copy_IntPtr(IntPtr input)
        {
            int size = IGetActualFeatureBufferSize();
            float[] buffer = new float[size];
            Marshal.Copy(input, buffer, 0, buffer.Length);
            return buffer;
        }

        public float[] GetFeature_VelocityLeftHand()
        {
            IntPtr data = IGetFeature_VelocityLeftHand();
            return Copy_IntPtr(data);
        }

        public float[] GetFeature_VelocityRightHand()
        {
            IntPtr data = IGetFeature_VelocityRightHand();
            return Copy_IntPtr(data);
        }

        public float[] GetFeature_VelocityGlobal()
        {
            IntPtr data = IGetFeature_VelocityGlobal();
            return Copy_IntPtr(data);
        }

        public float[] GetFeature_VelocityFoot()
        {
            IntPtr data = IGetFeature_VelocityFoot();
            return Copy_IntPtr(data);
        }

        public float[] GetFeature_Energy()
        {
            IntPtr data = IGetFeature_Energy();
            return Copy_IntPtr(data);
        }

        public float[] GetFeature_FootStretch()
        {
            IntPtr data = IGetFeature_FootStretch();
            return Copy_IntPtr(data);
        }

        public float[] GetFeature_BalanceBackForth()
        {
            IntPtr data = IGetFeature_BalanceBackForth();
            return Copy_IntPtr(data);
        }

        public float[] GetFeature_BalanceLeftRight()
        {
            IntPtr data = IGetFeature_BalanceLeftRight();
            return Copy_IntPtr(data);
        }
    }
}
