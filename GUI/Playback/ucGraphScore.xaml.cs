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

namespace GUI
{
	/// <summary>
	/// Interaction logic for ucGraphScore.xaml
	/// </summary>
	public partial class ucGraphScore : UserControl
	{
		public ucGraphScore()
		{
			this.InitializeComponent();
		}

        public void DrawGraph(List<double> data)
        {
            this.cvsLine.Children.Clear();
            double dWidth = this.cvsLine.ActualWidth;
            double dHeight = this.cvsLine.ActualHeight;

            Path path = new Path();
            path.Stretch = Stretch.Fill;
            path.StrokeThickness = 2;
            path.Fill = Brushes.DarkCyan;

            double kx = dWidth / (data.Count() - 1);
            double ky = dHeight / data.Max();
            Point ptStart = new Point(0, dHeight);
            Point ptEnd = new Point((data.Count() - 1) * kx, dHeight);

            List<LineSegment> lstLineSeg = new List<LineSegment>();
            for (int i = 0; i < data.Count(); i++)
            {
                double x = i * kx;
                double y = dHeight - data[i] * ky;
                LineSegment lineSeg = new LineSegment(new Point(x, y), true);
                lstLineSeg.Add(lineSeg);
            }

            lstLineSeg.Add(new LineSegment(ptEnd, true));

            PathFigure pathFig = new PathFigure(new Point(0, dHeight), lstLineSeg, true);
            PathGeometry geometry = new PathGeometry(new PathFigure[] { pathFig });
            path.Data = geometry;
            this.cvsLine.Children.Add(path);
        }
	}
}