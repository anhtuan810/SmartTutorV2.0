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

namespace GUI.Playback
{
    /// <summary>
    /// Interaction logic for ucMediaPlayer.xaml
    /// </summary>
    public partial class ucMediaPlayer : UserControl
    {
        enum MediaStatus
        {
            Stopped,
            Playing,
            Paused,
            Loop_One_Segment
        }

        public DispatcherTimer TimerTrackbar = new DispatcherTimer();
        public double MediaPosition;
        public double MediaDuration;

        private MediaStatus media_status_;
        private double media_start_pos_ = 0;
        private double media_end_pos_;


        public ucMediaPlayer()
        {
            this.InitializeComponent();
            TimerTrackbar.Interval = new TimeSpan(0, 0, 0, 0, 30);
            TimerTrackbar.Tick += timer_trackbar_Tick;
        }



        public void LoopOneSegment(int length, int start, int end)
        {
            if (this.mediaElement.NaturalDuration.HasTimeSpan)
            {
                media_start_pos_ = this.mediaElement.NaturalDuration.TimeSpan.TotalMilliseconds / length * start;
                media_end_pos_ = this.mediaElement.NaturalDuration.TimeSpan.TotalMilliseconds / length * end;
                media_status_ = MediaStatus.Loop_One_Segment;
            }
        }

        void timer_trackbar_Tick(object sender, EventArgs e)
        {
            if (this.mediaElement.NaturalDuration.HasTimeSpan)
            {
                this.MediaDuration = this.mediaElement.NaturalDuration.TimeSpan.TotalMilliseconds;
                this.MediaPosition = this.mediaElement.Position.TotalMilliseconds;

                this.trackBar.Maximum = this.mediaElement.NaturalDuration.TimeSpan.TotalMilliseconds;
                media_end_pos_ = this.mediaElement.NaturalDuration.TimeSpan.TotalMilliseconds;

                this.trackBar.Value = this.mediaElement.Position.TotalMilliseconds;
                if (this.trackBar.Value == this.trackBar.Maximum)
                {
                    this.mediaElement.Position = new TimeSpan(0, 0, 0, 0, 1);
                }
                this.lblCurrentPosition.Content = this.mediaElement.Position.ToString(@"mm\:ss");
                this.lblTotalDuration.Content = this.mediaElement.NaturalDuration.TimeSpan.ToString(@"mm\:ss");
            }
        }


        public void LoadVideo(string avi_file)
        {
            this.mediaElement.Source = new Uri(avi_file);
            //this.trackBar.Maximum = this.mediaElement.NaturalDuration.TimeSpan.TotalMilliseconds;
            Play();
        }

        private void Play()
        {
            this.mediaElement.Play();
            this.media_status_ = MediaStatus.Playing;
            TimerTrackbar.Start();
        }

        private void Pause()
        {
            this.mediaElement.Pause();
            this.media_status_ = MediaStatus.Paused;
            TimerTrackbar.Stop();
        }

        private void UserControl_MouseEnter(object sender, MouseEventArgs e)
        {
            this.control_panel.Opacity = 0.7;
        }

        private void UserControl_MouseLeave(object sender, MouseEventArgs e)
        {
            this.control_panel.Opacity = 0.3;
        }

        private void mediaElement_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (media_status_ == MediaStatus.Playing)
            {
                Pause();
            }
            else if (media_status_ == MediaStatus.Paused)
            {
                Play();
            }
        }

        private void trackBar_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            this.mediaElement.Position = TimeSpan.FromMilliseconds(this.trackBar.Value);
        }
    }
}
