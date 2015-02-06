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
    /// Interaction logic for ScoreGraph.xaml
    /// </summary>
    public partial class ScoreGraph : UserControl
    {
        private SolidColorBrush BRUSH_LINE_GRAPH = Brushes.DarkGreen;
        private List<float> data_real_ = null;

        public object TitleReal
        {
            get { return this.lblTitle.Content; }
            set { this.lblTitle.Content = value; }
        }

        public ScoreGraph()
        {
            InitializeComponent();
        }

        public void DrawRealData(List<float> data)
        {
            data_real_ = data;
            this.Draw_Graph_();
        }

        private void Draw_Graph_()
        {
            this.grdLine.Visibility = System.Windows.Visibility.Hidden;

            if (data_real_ != null)
            {
                this.Draw_LineGraph_();
                this.grdLine.Visibility = System.Windows.Visibility.Visible;
            }

            this.lblMaxValue.Content = data_real_.Max();
        }

        private void Draw_LineGraph_()
        {
            this.grdLine.Children.Clear();

            // Draw two axes
            //
            //this.drawAxis(ref this.cvsLine);

            // Draw the actual data
            //
            float dWidth = (float)this.grdLine.ActualWidth;
            float dHeight = (float)this.grdLine.ActualHeight;
            float kx = (float)dWidth / (data_real_.Count() - 1);
            float ky = (float)dHeight / 10;

            PathFigure path_figure = new PathFigure();
            path_figure.StartPoint = new Point(0, dHeight - data_real_[0] * ky);

            PathSegmentCollection path_segment_collection = new PathSegmentCollection();
            for (int i = 1; i < data_real_.Count; i++)
            {
                float x = i * kx;
                float y = dHeight - data_real_[i] * ky;
                path_segment_collection.Add(new LineSegment(new Point(x, y), true));
            }
            path_figure.Segments = path_segment_collection;

            Path path = new Path();
            path.Stroke = Brushes.DarkGreen;
            path.StrokeThickness = 3;
            path.Data = new PathGeometry(new PathFigure[] { path_figure });
            this.grdLine.Children.Add(path);


            //Path path = new Path();
            //path.Stretch = Stretch.Fill;
            //path.StrokeThickness = 2;
            //path.Fill = BRUSH_LINE_GRAPH;

            //float kx = (float)dWidth / (data_real_.Count() - 1);
            //float ky = (float)dHeight / 10;

            //List<LineSegment> lstLineSeg = new List<LineSegment>();
            //for (int i = 0; i < data_real_.Count(); i++)
            //{
            //    float x = i * kx;
            //    float y = dHeight - data_real_[i] * ky;
            //    LineSegment lineSeg = new LineSegment(new Point(x, y), true);
            //    lstLineSeg.Add(lineSeg);
            //}

            //PathFigure pathFig = new PathFigure(new Point(0, dHeight), lstLineSeg, true);
            //PathGeometry geometry = new PathGeometry(new PathFigure[] { pathFig });
            //path.Data = geometry;
            //this.cvsLine.Children.Add(path);
        }


        /// <summary>
        /// Draw two axes for line graph
        /// Based only on size of canvas
        /// </summary>
        /// <param name="cvs"></param>
        private void Draw_Axis_(ref Canvas cvs)
        {
            float iHeight = (float)cvs.ActualHeight;
            float iWidth = (float)cvs.ActualWidth;

            Line lineX = new Line();
            lineX.StrokeThickness = 1;
            lineX.Stroke = Brushes.Gray;
            lineX.X1 = 0;
            lineX.Y1 = iHeight;
            lineX.X2 = iWidth;
            lineX.Y2 = iHeight;
            this.grdLine.Children.Add(lineX);

            Line lineY = new Line();
            lineY.StrokeThickness = 1;
            lineY.Stroke = Brushes.Gray;
            lineY.X1 = 0;
            lineY.Y1 = iHeight;
            lineY.X2 = 0;
            lineY.Y2 = 0;
            this.grdLine.Children.Add(lineY);
        }


        public void ChangeTitle(string title)
        {
            this.lblTitle.Content = title;
        }
    }
}
