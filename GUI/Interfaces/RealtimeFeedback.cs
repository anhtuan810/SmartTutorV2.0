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
    class RealtimeFeedback
    {
        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetRealtimeFeedbackFrame();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int IGetNumberOfErrorPoints();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetErrorPoints(int index);

        public WriteableBitmap GetRealtimeFeedbackFrame()
        {
            const int kHeight = 480;
            const int kWidth = 640;

            // Grab data
            IntPtr data = IGetRealtimeFeedbackFrame();
            byte[] buffer = new byte[kHeight * kWidth * 3];
            Marshal.Copy(data, buffer, 0, buffer.Length);

            // Adjust buffer to swap order of RGB before writing image
            for (int i = 0; i < buffer.Length - 2; i++)
            {
                byte tmp = buffer[i];
                buffer[i] = buffer[i + 2];
                buffer[i + 2] = tmp;
            }

            // Create color image out of data
            WriteableBitmap bitmap = new WriteableBitmap(kWidth, kHeight, 96.0, 96.0, PixelFormats.Rgb24, null);
            bitmap.WritePixels(new Int32Rect(0, 0, kWidth, kHeight), buffer, kWidth * 3, 0);

            Marshal.FreeHGlobal(data);
            return bitmap;
        }

        public List<Point> GetErrorPoints()
        {
            int no_of_points = IGetNumberOfErrorPoints();
            List<Point> point_list = new List<Point>();
            for (int i = 0; i < no_of_points; i++)
            {
                IntPtr data = IGetErrorPoints(i);
                float[] buffer = new float[3];
                Marshal.Copy(data, buffer, 0, 3);

                Point point = new Point(buffer[0], buffer[1]);
                point_list.Add(point);
            }
            return point_list;
        }
    }
}
