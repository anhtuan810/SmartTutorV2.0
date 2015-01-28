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
    /// Interaction logic for BinaryGraph.xaml
    /// </summary>
    public partial class BinaryGraph : UserControl
    {
        private SolidColorBrush BRUSH_BINARY_GRAPH = Brushes.DarkGreen;

        public object Title
        {
            get { return this.lblBinary.Content; }
            set { this.lblBinary.Content = value; }
        }

        private List<bool> binary_data_ = null;

        public BinaryGraph()
        {
            InitializeComponent();
        }

        public void DrawBinaryData(List<bool> binary_data)
        {
            binary_data_ = binary_data;
            this.cvsBar.Visibility = System.Windows.Visibility.Hidden;
            this.lblBinary.Visibility = System.Windows.Visibility.Hidden;
            if (binary_data_ != null)
            {
                this.drawBinaryGraph(ref cvsBar, binary_data_);
                this.lblBinary.Visibility = System.Windows.Visibility.Visible;
                this.cvsBar.Visibility = System.Windows.Visibility.Visible;
            }
        }

        private void drawBinaryGraph(ref Canvas cvs, List<bool> data)
        {
            cvs.Children.Clear();
            double dHeight = cvs.ActualHeight;
            double dWidth = cvs.ActualWidth;

            // Draw the bounding rectangle
            //
            Rectangle recBound = new Rectangle();
            recBound.Stroke = Brushes.LightGray;
            recBound.Height = dHeight;
            recBound.Width = dWidth;
            Canvas.SetTop(recBound, 0);
            Canvas.SetLeft(recBound, 0);
            cvs.Children.Add(recBound);

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
                    rec.Fill = BRUSH_BINARY_GRAPH;
                    rec.Height = dHeight;
                    rec.Width = (int)(iStop - iStart) * kx;
                    Canvas.SetTop(rec, 0);
                    Canvas.SetLeft(rec, (int)iStart * kx);
                    cvs.Children.Add(rec);
                }
                i++;
            }
        }
    }
}
