using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DirectX.Capture;

namespace GUI.Interfaces
{
    class WebcamController
    {
        private Filters filters_;
        private Capture capture_;

        public WebcamController()
        {
            filters_ = new Filters();
            capture_ = new Capture(filters_.VideoInputDevices[0], filters_.AudioInputDevices[0]);
        }

        public WebcamController(int video_id, int audio_id)
        {
            filters_ = new Filters();
            capture_ = new Capture(filters_.VideoInputDevices[video_id], filters_.AudioInputDevices[audio_id]);
        }

        public string[] GetVideoDevices()
        {
            string[] devices = new string[filters_.VideoInputDevices.Count];
            for (int i = 0; i < filters_.VideoInputDevices.Count; i++)
            {
                devices[i] = filters_.VideoInputDevices[i].Name;
            }
            return devices;
        }

        public string[] GetAudioDevices()
        {
            string[] devices = new string[filters_.AudioInputDevices.Count];
            for (int i = 0; i < filters_.AudioInputDevices.Count; i++)
            {
                devices[i] = filters_.AudioInputDevices[i].Name;
            }
            return devices;
        }

        public void TurnOff()
        {
            capture_.Dispose();
        }

        public bool StartRecordingOrDie(string file_name)
        {
            capture_.VideoCompressor = filters_.VideoCompressors[0];
            capture_.AudioCompressor = filters_.AudioCompressors[0];
            capture_.Filename = file_name;
            capture_.Start();
            return true;
        }

        public void StopRecording()
        {
            capture_.Stop();
        }
    }
}
