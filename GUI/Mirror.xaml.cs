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
using GUI.Interfaces;

namespace GUI
{
    /// <summary>
    /// Interaction logic for Mirror.xaml
    /// </summary>
    public partial class Mirror : Window
    {
        System.Windows.Threading.DispatcherTimer timer = new System.Windows.Threading.DispatcherTimer();
        private GUI.Interfaces.SensorController controller = new SensorController();
        private GUI.Interfaces.FeatureExtractor feature_extractor = new FeatureExtractor();
        private GUI.Interfaces.OverallAssessment overall_assessment = new OverallAssessment();
        private GUI.Interfaces.RealtimeFeedback realtime_feedback = new RealtimeFeedback();
        private string oni_file_ = "G:\\Development of SmartTutor\\11.oni";

        //private Ellipse ellipse_ = new Ellipse();
        private WriteableBitmap mirror_image_;

        public Mirror()
        {
            InitializeComponent();
            timer.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer.Tick += timer_Tick;

            controller.TurnOnONIFile(oni_file_);
            timer.Start();
        }

        void timer_Tick(object sender, System.EventArgs e)
        {
            controller.QuerySensor();
            mirror_image_ = realtime_feedback.GetRealtimeFeedbackFrame();
            this.imgMain.Source = mirror_image_;

            // Annotate error points
            List<Point> error_points = realtime_feedback.GetErrorPoints();
            if (error_points.Count > 0)
                lblTest.Content = error_points[0].X + " - " + error_points[0].Y;

            for (int i = 0; i < error_points.Count; i++)
            {
                DrawEllipse((float)error_points[i].X, (float)error_points[i].Y);
            }
        }

        void DrawEllipse(float X, float Y)
        {
            //// Remove all existing ellipses in grdDrawing
            //for (int i = 0; i < this.grdDrawing.Children.Count; i++)
            //{
            //    if (this.grdDrawing.Children[i].GetType() == typeof(Ellipse))
            //    {
            //        this.grdDrawing.Children.RemoveAt(i);
            //    }
            //}

            //Ellipse ell = new Ellipse();
            //ell.Height = 50;
            //ell.Width = 50;
            //ell.Stroke = Brushes.Red;
            //ell.Visibility = System.Windows.Visibility.Visible;
            //ell.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;
            //ell.VerticalAlignment = System.Windows.VerticalAlignment.Top;            
            //ell.Tag = "OK";
            //this.grdDrawing.Children.Add(ell);
            
            Point WPF_point = ConvertDepthToWPF((int)X, (int)Y);
            Thickness margin = new Thickness();
            margin.Left = WPF_point.X;
            margin.Top = WPF_point.Y;
            //ell.Margin = margin;
            ellMain.Margin = margin;
        }

        Point ConvertDepthToWPF(int X, int Y)
        {
            // Adjust because of the alignment that was made on the original depth image
            double ratioX = 0.91;
            double ratioY = 0.91;

            double dX = (X - 320) * ratioX;
            double dY = (Y - 240) * ratioY;

            double ratioW = 1 / ratioX;
            double ratioH = 1 / ratioY;
            double dW = dX * ratioW;
            double dH = dY * ratioH;

            double X_new = 640 - X / ratioX;
            double Y_new = Y * ratioY;
            return new Point(X_new, Y_new);
        }
    }
}
