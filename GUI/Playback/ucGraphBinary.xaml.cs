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
	/// Interaction logic for ucGraphBinary.xaml
	/// </summary>
	public partial class ucGraphBinary : UserControl
	{
		public ucGraphBinary()
		{
			this.InitializeComponent();
		}

        public void DrawBinaryGraph(List<bool> data)
        {
            cvsBar.Children.Clear();
            double dHeight = this.cvsBar.ActualHeight;
            double dWidth = this.cvsBar.ActualWidth;

            // Draw the bounding rectangle
            //
            Rectangle recBound = new Rectangle();
            recBound.Stroke = Brushes.LightGray;
            recBound.Height = dHeight;
            recBound.Width = dWidth;
            Canvas.SetTop(recBound, 0);
            Canvas.SetLeft(recBound, 0);
            cvsBar.Children.Add(recBound);

            // Draw actual data
            //
            double kx = (double)dWidth / (data.Count() - 1);
            int i = 0;
            int iStart = 0;
            int iStop = 0;
            while (i < data.Count)
            {
                if (data[i] == true)
                {
                    // Find start and stop of the blocks
                    //
                    iStart = i;
                    while (data[i] == true)
                    {
                        i++;
                        if (i >= data.Count)
                            break;
                    }
                    iStop = i;

                    // Draw rectangle of data
                    //
                    Rectangle rec = new Rectangle();
                    rec.Fill = Brushes.DarkGray;
                    rec.Height = dHeight;
                    rec.Width = (int)(iStop - iStart) * kx;
                    Canvas.SetTop(rec, 0);
                    Canvas.SetLeft(rec, (int)iStart * kx);
                    cvsBar.Children.Add(rec);
                }
                i++;
            }
        }
	}
}