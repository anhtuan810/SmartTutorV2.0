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

namespace GUI.Visualisation
{
    /// <summary>
    /// Interaction logic for Graph_2sides.xaml
    /// </summary>
    public partial class Graph_2sides : UserControl
    {
        private SolidColorBrush BRUSH_LINE_GRAPH = Brushes.DarkCyan;
        private List<float> data_real_ = null;

        public object TitleReal
        {
            get { return this.lblTitle.Content; }
            set { this.lblTitle.Content = value; }
        }

        public Graph_2sides()
        {
            InitializeComponent();
        }

        public void DrawRealData(List<float> data)
        {
            data_real_ = data;
            DrawGraph();
        }

        public void DrawGraph()
        {
            this.cvsLine.Visibility = System.Windows.Visibility.Hidden;
            this.cvsBar1.Visibility = System.Windows.Visibility.Hidden;
            this.cvsBar2.Visibility = System.Windows.Visibility.Hidden;

            if (data_real_ != null)
            {
                this.drawLineGraph();
                this.cvsLine.Visibility = System.Windows.Visibility.Visible;
            }

            this.lblMaxValue.Content = data_real_.Max();
        }

        private void drawLineGraph()
        {
            this.cvsLine.Children.Clear();

            // Draw two axes
            //
            //this.drawAxis(ref this.cvsLine);

            // Draw the actual data
            //
            float dWidth = (float)this.cvsLine.ActualWidth;
            float dHeight = (float)this.cvsLine.ActualHeight;

            Path path = new Path();
            path.Stretch = Stretch.Fill;
            path.StrokeThickness = 2;
            path.Fill = BRUSH_LINE_GRAPH;

            float larger = Math.Abs(data_real_.Max());
            if (Math.Abs(data_real_.Min()) > larger)
                larger = Math.Abs(data_real_.Min());

            float kx = (float)dWidth / (data_real_.Count() - 1);
            float ky = (float)dHeight / (larger * 2);
            Point ptStart = new Point(0, dHeight);
            Point ptEnd = new Point((data_real_.Count - 1) * kx, dHeight);

            List<LineSegment> lstLineSeg = new List<LineSegment>();
            for (int i = 0; i < data_real_.Count(); i++)
            {
                float x = i * kx;
                float y = dHeight - data_real_[i] * ky;
                LineSegment lineSeg = new LineSegment(new Point(x, y), true);
                lstLineSeg.Add(lineSeg);
            }

            lstLineSeg.Add(new LineSegment(ptEnd, true));

            PathFigure pathFig = new PathFigure(new Point(0, dHeight), lstLineSeg, true);
            PathGeometry geometry = new PathGeometry(new PathFigure[] { pathFig });
            path.Data = geometry;
            this.cvsLine.Children.Add(path);
        }

        private void drawAxis(ref Canvas cvs)
        {
            float iHeight = (float)cvs.ActualHeight;
            float iWidth = (float)cvs.ActualWidth;

            Line lineX = new Line();
            lineX.StrokeThickness = 1;
            lineX.Stroke = Brushes.DarkGray;
            lineX.X1 = 0;
            lineX.Y1 = iHeight / 2;
            lineX.X2 = iWidth;
            lineX.Y2 = iHeight / 2;
            this.cvsLine.Children.Add(lineX);
        }
    }
}
