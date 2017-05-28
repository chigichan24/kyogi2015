using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace Loop
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.button_start = new System.Windows.Forms.Button();
            this.textBox_probrem = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.button_browser = new System.Windows.Forms.Button();
            this.textBox_program = new System.Windows.Forms.TextBox();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.button_quest_browser = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBox_no_Putting = new System.Windows.Forms.CheckBox();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_start
            // 
            this.button_start.Location = new System.Drawing.Point(173, 119);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(114, 23);
            this.button_start.TabIndex = 2;
            this.button_start.Text = "問題読み込み";
            this.button_start.UseVisualStyleBackColor = true;
            this.button_start.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox_probrem
            // 
            this.textBox_probrem.Location = new System.Drawing.Point(173, 84);
            this.textBox_probrem.Name = "textBox_probrem";
            this.textBox_probrem.Size = new System.Drawing.Size(114, 22);
            this.textBox_probrem.TabIndex = 3;
            // 
            // timer1
            // 
            this.timer1.Interval = 5;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.radioButton3);
            this.groupBox2.Controls.Add(this.button_browser);
            this.groupBox2.Controls.Add(this.textBox_program);
            this.groupBox2.Controls.Add(this.radioButton2);
            this.groupBox2.Controls.Add(this.radioButton1);
            this.groupBox2.Location = new System.Drawing.Point(15, 63);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox2.Size = new System.Drawing.Size(150, 120);
            this.groupBox2.TabIndex = 10;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "解答方法";
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(9, 58);
            this.radioButton3.Margin = new System.Windows.Forms.Padding(2);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(73, 19);
            this.radioButton3.TabIndex = 12;
            this.radioButton3.Text = "テキスト";
            this.radioButton3.UseVisualStyleBackColor = true;
            this.radioButton3.CheckedChanged += new System.EventHandler(this.radioButton3_CheckedChanged);
            // 
            // button_browser
            // 
            this.button_browser.Enabled = false;
            this.button_browser.Location = new System.Drawing.Point(116, 82);
            this.button_browser.Name = "button_browser";
            this.button_browser.Size = new System.Drawing.Size(19, 23);
            this.button_browser.TabIndex = 11;
            this.button_browser.Text = "...";
            this.button_browser.UseVisualStyleBackColor = true;
            this.button_browser.Click += new System.EventHandler(this.button4_Click);
            // 
            // textBox_program
            // 
            this.textBox_program.Enabled = false;
            this.textBox_program.Location = new System.Drawing.Point(8, 85);
            this.textBox_program.Margin = new System.Windows.Forms.Padding(2);
            this.textBox_program.Name = "textBox_program";
            this.textBox_program.Size = new System.Drawing.Size(104, 22);
            this.textBox_program.TabIndex = 2;
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(9, 38);
            this.radioButton2.Margin = new System.Windows.Forms.Padding(2);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(84, 19);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.Text = "プログラム";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.ForeColor = System.Drawing.Color.Black;
            this.radioButton1.Location = new System.Drawing.Point(9, 18);
            this.radioButton1.Margin = new System.Windows.Forms.Padding(2);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(58, 19);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "手動";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // button_quest_browser
            // 
            this.button_quest_browser.Location = new System.Drawing.Point(293, 83);
            this.button_quest_browser.Name = "button_quest_browser";
            this.button_quest_browser.Size = new System.Drawing.Size(19, 23);
            this.button_quest_browser.TabIndex = 12;
            this.button_quest_browser.Text = "...";
            this.button_quest_browser.UseVisualStyleBackColor = true;
            this.button_quest_browser.Click += new System.EventHandler(this.button_quest_browser_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(170, 63);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 15);
            this.label1.TabIndex = 13;
            this.label1.Text = "Quest";
            // 
            // checkBox_no_Putting
            // 
            this.checkBox_no_Putting.AutoSize = true;
            this.checkBox_no_Putting.Location = new System.Drawing.Point(16, 236);
            this.checkBox_no_Putting.Name = "checkBox_no_Putting";
            this.checkBox_no_Putting.Size = new System.Drawing.Size(136, 19);
            this.checkBox_no_Putting.TabIndex = 14;
            this.checkBox_no_Putting.Text = "盤面を更新しない";
            this.checkBox_no_Putting.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(336, 297);
            this.Controls.Add(this.checkBox_no_Putting);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_quest_browser);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.textBox_probrem);
            this.Controls.Add(this.button_start);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Button button_start;
        private TextBox textBox_probrem;
        private Timer timer1;
        private GroupBox groupBox2;
        private Button button_browser;
        private TextBox textBox_program;
        private RadioButton radioButton2;
        private RadioButton radioButton1;
        private Button button_quest_browser;
        private Label label1;
        private CheckBox checkBox_no_Putting;
        private RadioButton radioButton3;
    }
}