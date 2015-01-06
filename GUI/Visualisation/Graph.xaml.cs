//
//  Smart Tutor v2.0
//	Interface for GUI, create dynamic library to link from C++ to C#
//  Graph to present one series of feature
//
//  Created: 2015.01.06
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

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
    /// Interaction logic for Graph.xaml
    /// </summary>
    public partial class Graph : UserControl
    {
        private SolidColorBrush BRUSH_LINE_GRAPH = Brushes.DarkGray;
        private SolidColorBrush BRUSH_BINARY_GRAPH = Brushes.DarkGray;
        private List<float> data_real_ = null;

        public object TitleReal
        {
            get { return this.lblTitle.Content; }
            set { this.lblTitle.Content = value; }
        }
        

        public Graph()
        {
            InitializeComponent();
        }


        public void SetDataReal(List<float> data)
        {
            data_real_ = data;
        }
        

        /// <summary>
        /// Actually draw graphs
        /// </summary>
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


        /// <summary>
        /// Draw line graph, if necessary
        /// </summary>
        private void drawLineGraph()
        {
            this.cvsLine.Children.Clear();

            // Draw two axes
            //
            this.drawAxis(ref this.cvsLine);

            // Draw the actual data
            //
            float dWidth = (float)this.cvsLine.ActualWidth;
            float dHeight = (float)this.cvsLine.ActualHeight;

            Path path = new Path();
            path.Stretch = Stretch.Fill;
            path.StrokeThickness = 2;
            path.Fill = BRUSH_LINE_GRAPH;

            float kx = (float)dWidth / (data_real_.Count() - 1);
            float ky = (float)dHeight / data_real_.Max();
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


        /// <summary>
        /// Draw two axes for line graph
        /// Based only on size of canvas
        /// </summary>
        /// <param name="cvs"></param>
        private void drawAxis(ref Canvas cvs)
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
            this.cvsLine.Children.Add(lineX);

            Line lineY = new Line();
            lineY.StrokeThickness = 1;
            lineY.Stroke = Brushes.Gray;
            lineY.X1 = 0;
            lineY.Y1 = iHeight;
            lineY.X2 = 0;
            lineY.Y2 = 0;
            this.cvsLine.Children.Add(lineY);
        }


        public void ChangeTitle(string title)
        {
            this.lblTitle.Content = title;
        }

    }
}
