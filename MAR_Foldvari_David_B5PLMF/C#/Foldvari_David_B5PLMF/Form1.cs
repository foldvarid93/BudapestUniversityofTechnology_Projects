using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Threading;
using System.Timers;
using System.IO;

namespace Foldvari_David_B5PLMF
{
    public partial class B5PLMF : Form
    {
        List<Bitmap> BitmapList = new List<Bitmap>();
        int ActualPictureIndex;
        System.Timers.Timer Timer = new System.Timers.Timer();
        byte[] DataArray = new byte[1024];
        bool TransmitStatus;
        bool InvertingState = false;
        public B5PLMF()
        {
            InitializeComponent();
            GetPortNames();
            Timer.Elapsed += TimerEvent;
        }
        void GetPortNames()
        {
            String[] ports = SerialPort.GetPortNames();
            comboBox1.Items.AddRange(ports);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                button1.Text = "Open Port";
                try
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                    serialPort1.DataBits=8;
                    serialPort1.Parity = Parity.None;
                    serialPort1.StopBits = StopBits.One;
                    serialPort1.Handshake = Handshake.None;
                    serialPort1.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
                    serialPort1.Open();
                    textBox1.Text = "Port opened:\r\nName: " + comboBox1.Text + "\r\nBaudrate: " + comboBox2.Text;
                    button1.Text = "Close Port";
                    if (BitmapList.Count != 0) {
                        Send.Enabled = true;
                    }
                }
                catch (UnauthorizedAccessException)
                {
                    textBox1.Text = "Cannot open port!";
                }
            }
            else {
                serialPort1.Close();
                textBox1.Text = "Port closed.";
                button1.Text = "Open Port";
                Send.Enabled = false;
            }
        }
        private void comboBox1_OnChange(object sender, EventArgs e)
        {
            if (comboBox1.Text == "" || comboBox2.Text == "") {
                button1.Enabled = false;
                textBox1.Text = "Select port settings!";
            }
            else
            {
                button1.Enabled = true;
            }
        }
        private void comboBox2_OnChange(object sender, EventArgs e)
        {
            if (comboBox1.Text == "" || comboBox2.Text == "")
            {
                button1.Enabled = false;
                textBox1.Text = "Select port settings!";
            }
            else {
                button1.Enabled = true;
            }
        }
        private void Add_Click(object sender, EventArgs e)//kép megnyitása
        {
            OpenPicture();
        }
        private void Remove_Click(object sender, EventArgs e)//kép törlése
        {
            DeletePicture();
        }
        private void Prev_Click(object sender, EventArgs e)//előző kép mutatása
        {
            if (ActualPictureIndex > 0)
            {
                ActualPictureIndex--;
                ShowActualPicture();
            }
        }
        private void Next_Click(object sender, EventArgs e)//következő kép mutatása
        {
            if (ActualPictureIndex < BitmapList.Count - 1) {
                ActualPictureIndex++;
                ShowActualPicture();
            }
        }
        private void Send_Click(object sender, EventArgs e)//képek küldése
        {
            if (BitmapList.Count ==1) {
                ConvertPictureToDisplay();
                SendToDevice();
                ShowActualPicture();
                return;
            }
            if (!Timer.Enabled) {
                Timer.Interval = Convert.ToInt32(TimerInterval.Text) * 1000;
                Timer.AutoReset = true;
                Remove.Enabled = false;
                Open.Enabled = false;
                Next.Enabled = false;
                Prev.Enabled = false;
                Inverting.Enabled = false;
                TimerInterval.Enabled = false;
                label5.Enabled = false;
                Export.Enabled = false;
                Send.Text = "Stop sending";
                Timer.Enabled = true;
                return;
            }
            else if (Timer.Enabled) {
                Timer.Enabled = false;
                label5.Enabled = true;
                Remove.Enabled = true;
                Open.Enabled = true;
                Next.Enabled = true;
                Prev.Enabled = true;
                Inverting.Enabled = true;
                TimerInterval.Enabled = true;
                Export.Enabled = true;
                Send.Text = "Start sending";
                return;
            }
        }
        private void Export_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "c files (*.c)|*.c|h files(*.h|*.h)";
            saveFileDialog1.RestoreDirectory = true;
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string filenameC = saveFileDialog1.FileName;
                string filenameH = filenameC.TrimEnd('c').TrimEnd('.')+".h";
                string Name = Path.GetFileName(filenameH);
                string DataArrayName = Name.TrimEnd('h').TrimEnd('.') + "DataArray";
                String CString = "#include\t"+'"'+ Name +'"'+"\r\nconst uint8_t "+ DataArrayName+"[1024]={";
                String HString = "#include\t" + '"' + "stdint.h"+'"'+ "\r\nextern const uint8_t " + DataArrayName + "[1024];";
                ConvertPictureToDisplay();
                for (int i = 0; i < 1024; i++)
                {
                    if (i % 8 == 0) { CString += "\r\n\t";}
                    CString += ByteArrayToString(DataArray[i]) + ',';
                }
                CString = CString.TrimEnd(',');
                CString += "\r\n};";
                StreamWriter writer = new StreamWriter(saveFileDialog1.OpenFile());
                writer.WriteLine(CString);
                writer.Dispose();
                saveFileDialog1.FileName = filenameH;
                writer = new StreamWriter(saveFileDialog1.OpenFile());
                writer.WriteLine(HString);
                writer.Dispose();
            }
        }
        private void Inverting_CheckedChanged(object sender, EventArgs e)
        {
            InvertingState = (!InvertingState);
            ShowActualPicture();
        }
        private void TimerEvent(Object source, ElapsedEventArgs e)
        {
            ActualPictureIndex++;
            if (ActualPictureIndex >= BitmapList.Count)
            {
                ActualPictureIndex = 0;
            }
            ConvertPictureToDisplay();
            SendToDevice();
            ShowActualPicture();
        }
        public void SendToDevice()
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write(DataArray, 0, 1024);//serialPort1.Write("a");//
            }
            else {
                textBox1.Text = "No serial port available";
            }
        }
        public void ConvertPictureToDisplay()
        {
            for (int i = 0; i < 1024; i++)
            {
                DataArray[i] = 0x00;
            }
            Color PixelColor = new Color();            
            for (int i = 0; i < 64; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    PixelColor= BitmapList[ActualPictureIndex].GetPixel(j, i);
                    if (PixelColor.R == 0 &&PixelColor.G == 0 &&PixelColor.B == 0)
                    {
                        byte mask = 1;
                        mask <<= i % 8;
                        DataArray[((i/8)*128) +  j] |= mask;
                    }
                }
            }
            if (!InvertingState) {
                for (int i = 0; i < 1024; i++)
                {
                    DataArray[i] = (byte)~DataArray[i]; ;
                }
            }
        }
        public static string ByteArrayToString(byte b)
        {
            StringBuilder hex = new StringBuilder(4);
            hex.AppendFormat("{0:x2}", b);
            string str="0x"+hex.ToString();
            return str;
        }
        public void ShowActualPicture() {
            Color PixelColor = new Color();
            Bitmap tmp = new Bitmap(128, 64,PixelFormat.Format16bppRgb555);
            for (int i = 0; i < 64; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    PixelColor = BitmapList[ActualPictureIndex].GetPixel(j, i);
                    if (PixelColor.R == 0 && PixelColor.G == 0 && PixelColor.B == 0)
                    {
                        if (!InvertingState){tmp.SetPixel(j, i, Color.Blue);}
                        else {tmp.SetPixel(j, i, Color.White);}
                        
                    }
                    else {
                        if (!InvertingState){tmp.SetPixel(j, i, Color.White);}
                        else{tmp.SetPixel(j, i, Color.Blue);}
                    }
                }
            }
            tmp= new Bitmap(tmp, new Size(512, 256));
            pictureBox1.Image = tmp;
            tmp=null;
            label4.Invoke(new Action(()=>label4.Text= (ActualPictureIndex + 1).ToString() + "/" + BitmapList.Count.ToString()));       
        }
        public void OpenPicture()
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = "Image Files(*.bmp)|*.bmp";
            if (open.ShowDialog() == DialogResult.OK)
            {
                Bitmap tmp = new Bitmap(open.FileName);
                if (tmp.Height == 64 && tmp.Width == 128&& tmp.PixelFormat== PixelFormat.Format1bppIndexed)
                {
                    BitmapList.Add(tmp);
                    ActualPictureIndex = BitmapList.Count - 1;
                    ShowActualPicture();
                    if (serialPort1.IsOpen) {
                        Send.Enabled = true;
                    }
                    Remove.Enabled = true;
                    Inverting.Enabled = true;
                    Export.Enabled = true;
                    if (BitmapList.Count > 1) {
                        TimerInterval.SelectedIndex = 0;
                        Send.Text = "Start sending";
                        TimerInterval.Enabled = true;
                        label5.Enabled = true;
                    }
                }
                else
                {
                    MessageBox.Show("Wrong picture format or size");
                }
            }
        }
        public void DeletePicture() {
            if (BitmapList.Count != 0)
            {
                BitmapList.RemoveAt(ActualPictureIndex);
                if (BitmapList.Count != 0)
                {
                    if (ActualPictureIndex != 0) {
                        ActualPictureIndex--;
                    }
                    ShowActualPicture();
                }
                else
                {
                    pictureBox1.Image = null;
                    label4.Text = "No Image";
                    Send.Enabled = false;
                    Remove.Enabled = false;
                    Inverting.Enabled = false;
                    Export.Enabled = false;
                }
            }
            if (BitmapList.Count < 2) {
                TimerInterval.Enabled = false;
                label5.Enabled = false;
                Send.Text = "Send";
            }
        }
        public void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string indata = sp.ReadExisting();
            if (indata == "OK")
            {
                TransmitStatus = true;
                textBox1.Invoke(new Action(() => textBox1.Text = "Transmit status: OK."));
            }
            else
            {
                TransmitStatus = false;
                textBox1.Invoke(new Action(() => textBox1.Text = "Transmit status: ERROR!"));
            }         
        }
    }
}
