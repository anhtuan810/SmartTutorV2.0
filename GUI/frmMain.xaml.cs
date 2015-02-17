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
using System.Windows.Shapes;

namespace GUI
{
    /// <summary>
    /// Interaction logic for frmMain.xaml
    /// </summary>
    public partial class frmMain : Window
    {
        public enum ContentInMainForm
        {
            Home,
            Practice,
            Practice_FullScreen,
            Playback,
            Result
        }

        private ContentInMainForm content_;

        public frmMain()
        {
            InitializeComponent();
            SwitchWindow(ContentInMainForm.Playback);
        }

        public void SwitchWindow(ContentInMainForm content)
        {
            content_ = content;

            this.LayoutRoot.Children.Clear();
            if (content == ContentInMainForm.Home)
            {
                GUI.Home.ucHome home = new GUI.Home.ucHome();
                this.LayoutRoot.Children.Add(home);
            }
            if (content == ContentInMainForm.Practice)
            {
                GUI.Practice.ucPractice1 practice = new GUI.Practice.ucPractice1();
                this.LayoutRoot.Children.Add(practice);
            }
            if (content == ContentInMainForm.Playback)
            {
                GUI.Playback.ucPlayback playback = new Playback.ucPlayback();
                this.LayoutRoot.Children.Add(playback);
            }

        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (content_ == ContentInMainForm.Practice)
            {
                GUI.Practice.ucPractice1 practice = (GUI.Practice.ucPractice1 )this.LayoutRoot.Children[0];
                practice.Closing();
            }
        }
    }
}
