using System;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Input;

namespace Loop
{
    public partial class Viewer : Form
    {
        private Bitmap canvas;
        private Graphics g;
        private InputMaster IN;
        public Viewer(string probname)
        {
            InitializeComponent();
            canvas = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            g = Graphics.FromImage(canvas);
            Mrg = 60;
            Siz = 10;
            IN = new InputMaster();
        }

        public new void Update()
        {
            IN.Update();
            g.Dispose();
            pictureBox1.Image = canvas;   
        }

        private readonly SolidBrush[] colors = {new SolidBrush(Color.White), new SolidBrush(Color.Black), new SolidBrush(Color.RoyalBlue),new SolidBrush(Color.Salmon)};
        public int Siz { get; set; }
        public int Mrg { get; set; }

        public void DrawPanel(int x, int y, int col)
        {
            g.FillRectangle(colors[col],x*Siz,y*Siz+Mrg,Siz,Siz);
            g.DrawRectangle(new Pen(Color.Black,1),x*Siz,y*Siz+Mrg,Siz,Siz);
            
        }
        public void DrawChip(int x, int y,int col)
        {
            int sz = Siz / 4;
            g.FillRectangle(colors[col], x*Siz + sz, y*Siz + Mrg + sz, sz*2, sz*2);
        }
        public void DrawBlock(int x, int y, int qx, int qy, int col)
        {
            int sz = 10;
            g.FillRectangle(colors[col], qx * 100 + 500 + x * sz, 50 + qy * 100 + y * sz, sz, sz);
            g.DrawRectangle(new Pen(Color.Gray, 1), qx * 100 + 500 + x * sz, 50 + qy * 100 + y * sz, sz, sz);
        }
        public void DrawNum(int x, int y, int sz, int num, int dig,int col = 1)
        {
            bool flg = false;
            string str = "";
            for (int i = 0; i < dig; i++)
            {
                double k = Math.Pow(10, dig - i);
                var _num = (num % (int)k) / (int)(k / 10);
                if (!flg && _num != 0) flg = true;
                if (flg || i == dig - 1) str += _num + "";
            }
            while (str.Length < dig) str = " " + str;
            Font fnt = new Font("MS UI Gothic", sz);
            g.DrawString(str,fnt,colors[col],x,y);
        }
        public void DrawString(int x, int y, string s,int col = 1)
        {
            Font fnt = new Font("MS UI Gothic", 14);
            g.DrawString(s, fnt, colors[col], x, y);
        }
        public void DrawLine(int px, int py, int qx, int qy, int col = 1)
        {
            g.DrawLine(new Pen(colors[col],1),px,py,qx,qy);
        }
        public void Clear()
        {
            canvas = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            g = Graphics.FromImage(canvas);
        }

        public bool GetIsKeyPressed(Key key)
        {
            return IN.GetIsKeyPressed(key);
        }

        public int GetTimeKeyPressing(Key key)
        {
            return IN.GetTimeKeyPressing(key);
        }


    }
}
