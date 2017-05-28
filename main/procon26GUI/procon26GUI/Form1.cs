using System;
using System.Windows.Forms;

namespace Loop
{
    public partial class Form1 : Form
    {
        Main main;
        int mode = 1;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        void StartGame()
        {
            main = new Main(textBox_probrem.Text,mode,textBox_program.Text,checkBox_no_Putting.Checked);
            timer1.Enabled = true;
            main.Init();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            StartGame();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            main.Update();
        }
        private void button4_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.FileName = "";
            ofd.Filter = "exe files (*.exe)|*.exe|All files (*.*)|*.*";
            if (radioButton3.Checked) ofd.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            ofd.Title = "保存先のファイルを選択してください";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                if (ofd.FileName != "")
                {
                    textBox_program.Text = ofd.FileName;
                }
            }
            
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked)
            {
                textBox_program.Enabled = false;
                button_browser.Enabled = false;
            }
            else
            {
                textBox_program.Enabled = true;
                button_browser.Enabled = true;
            }
            mode = 1;
        }


        private void button_quest_browser_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.FileName = "";
            ofd.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            ofd.Title = "開くファイルを選択してください";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                if (ofd.FileName != "")
                {
                    textBox_probrem.Text = ofd.FileName;
                }
            }
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            mode = 2;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            mode = 3;
        }

    }
}
