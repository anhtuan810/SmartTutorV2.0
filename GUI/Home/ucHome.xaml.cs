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

namespace GUI.Home
{
    /// <summary>
    /// Interaction logic for ucHome.xaml
    /// </summary>
    public partial class ucHome : UserControl
    {
        public ucHome()
        {
            InitializeComponent();
        }

        private void btnPractice_Click(object sender, RoutedEventArgs e)
        {
            frmMain main_form = (frmMain)((Grid)this.Parent).Parent;
            main_form.SwitchWindow(frmMain.ContentInMainForm.Practice);
        }

        private void btnProgress_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
