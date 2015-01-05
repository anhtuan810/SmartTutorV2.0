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


        public void ExtractFeatureNewFrame()
        {
            IExtractFeatureNewFrame();
        }

        public int GetActualFeatureBufferSize()
        {
            return IGetActualFeatureBufferSize();
        }

        public float[] GetFeature_VelocityLeftHand()
        {
            IntPtr data = IGetFeature_VelocityLeftHand();
            int size = IGetActualFeatureBufferSize();
            float[] buffer = new float[size];
            Marshal.Copy(data, buffer, 0, buffer.Length);
            return buffer;
        }
    }
}
