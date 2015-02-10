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
using System.Windows.Threading;

namespace GUI.Practice
{
    /// <summary>
    /// Interaction logic for ucCountDown.xaml
    /// </summary>
    public partial class ucCountDown : UserControl
    {
        public event EventHandler Finish;

        private DispatcherTimer timer_count_down_ = new DispatcherTimer();
        private int count_ = 5;
        
        public ucCountDown()
        {
            InitializeComponent();
            timer_count_down_.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer_count_down_.Tick += timer_count_down__Tick;
            this.lblCount.Visibility = System.Windows.Visibility.Hidden;
            this.btnStartStop.Visibility = System.Windows.Visibility.Visible;
        }

        void timer_count_down__Tick(object sender, EventArgs e)
        {
            count_--;
            this.lblCount.Content = count_;

            if (count_ == 0)
            {
                this.lblCount.Visibility = System.Windows.Visibility.Hidden;
                this.btnStartStop.Visibility = System.Windows.Visibility.Hidden;
                timer_count_down_.Stop();
                Finish(sender, e);
            }
        }

        private void btnStartStop_Click(object sender, RoutedEventArgs e)
        {
            this.lblCount.Visibility = System.Windows.Visibility.Visible;
            this.btnStartStop.Visibility = System.Windows.Visibility.Hidden;
            this.timer_count_down_.Start();
            count_ = 5;
        }
    }
}
