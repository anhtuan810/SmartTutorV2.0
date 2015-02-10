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
    class KinectController
    {
        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ITurnOnKinectSensor();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ITurnOnONIFile(string file_name);

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ITurnOff();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IStartRecording(string file_name);

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IStopRecording();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IQuerySensor();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGrabCurrentColorFrame();


        public bool TurnOnKinectSensor()
        {
            return ITurnOnKinectSensor();
        }

        public bool TurnOnONIFile(string file_name)
        {
            return ITurnOnONIFile(file_name);
        }

        public void TurnOff()
        {
            ITurnOff();
        }

        public void StartRecording(string file_name)
        {
            IStartRecording(file_name);
        }

        public void StopRecording()
        {
            IStopRecording();
        }

        public void QuerySensor()
        {
            IQuerySensor();
        }

        public WriteableBitmap GrabCurrentColorFrame()
        {
            const int kHeight = 480;
            const int kWidth = 640;

            // Grab data
            IntPtr data = IGrabCurrentColorFrame();
            byte[] buffer = new byte[kHeight * kWidth * 3];
            Marshal.Copy(data, buffer, 0, buffer.Length);

            // Create color image out of data

            WriteableBitmap bitmap = new WriteableBitmap(kWidth, kHeight, 96.0, 96.0, PixelFormats.Rgb24, null);
            bitmap.WritePixels(new Int32Rect(0, 0, kWidth, kHeight), buffer, kWidth * 3, 0);

            Marshal.FreeHGlobal(data);
            return bitmap;
        }

        public void testMemoryLeak()
        {
            IntPtr data = IGrabCurrentColorFrame();
            Marshal.FreeHGlobal(data);
        }
    }
}
