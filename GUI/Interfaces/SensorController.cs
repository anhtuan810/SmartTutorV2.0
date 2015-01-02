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
    class SensorController
    {
        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ITurnOnKinectSensor();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IQuerrySensor();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGrabFrame();

        public bool TurnOnKinectSensor()
        {
            return ITurnOnKinectSensor();
        }

        public void QuerrySensor()
        {
            IQuerrySensor();
        }

        public WriteableBitmap GrabFrameKinect()
        {
            const int kHeight = 480;
            const int kWidth = 640;

            // Grab data
            IntPtr data = IGrabFrame();
            byte[] buffer = new byte[kHeight * kWidth * 3];
            Marshal.Copy(data, buffer, 0, buffer.Length);

            // Create color image out of data

            WriteableBitmap bitmap = new WriteableBitmap(kWidth, kHeight, 96.0, 96.0, PixelFormats.Rgb24, null);
            bitmap.WritePixels(new Int32Rect(0, 0, kWidth, kHeight), buffer, kWidth * 3, 0);

            return bitmap;
        }
    }
}
