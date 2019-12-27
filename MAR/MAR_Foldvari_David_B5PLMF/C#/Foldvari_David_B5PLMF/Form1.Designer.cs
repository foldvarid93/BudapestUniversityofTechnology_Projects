namespace Foldvari_David_B5PLMF
{
    partial class B5PLMF
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.label3 = new System.Windows.Forms.Label();
            this.Send = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.Remove = new System.Windows.Forms.Button();
            this.Next = new System.Windows.Forms.Button();
            this.Open = new System.Windows.Forms.Button();
            this.Prev = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.TimerInterval = new System.Windows.Forms.ComboBox();
            this.Inverting = new System.Windows.Forms.CheckBox();
            this.Export = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(82, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(31, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Ports";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(119, 22);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 21);
            this.comboBox1.TabIndex = 1;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_OnChange);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(63, 62);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(50, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Baudrate";
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "9600",
            "115200"});
            this.comboBox2.Location = new System.Drawing.Point(119, 59);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(121, 21);
            this.comboBox2.TabIndex = 3;
            this.comboBox2.SelectedIndexChanged += new System.EventHandler(this.comboBox2_OnChange);
            // 
            // button1
            // 
            this.button1.Enabled = false;
            this.button1.Location = new System.Drawing.Point(246, 22);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(89, 58);
            this.button1.TabIndex = 4;
            this.button1.Text = "Open Port";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(341, 22);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(186, 58);
            this.textBox1.TabIndex = 6;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(404, 6);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Messages";
            // 
            // Send
            // 
            this.Send.Enabled = false;
            this.Send.Location = new System.Drawing.Point(554, 306);
            this.Send.Name = "Send";
            this.Send.Size = new System.Drawing.Size(200, 36);
            this.Send.TabIndex = 9;
            this.Send.Text = "Send";
            this.Send.UseVisualStyleBackColor = true;
            this.Send.Click += new System.EventHandler(this.Send_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(15, 86);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(512, 256);
            this.pictureBox1.TabIndex = 10;
            this.pictureBox1.TabStop = false;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(45, 3);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(131, 20);
            this.textBox2.TabIndex = 0;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(229, 359);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "No Image";
            // 
            // Remove
            // 
            this.Remove.Enabled = false;
            this.Remove.Location = new System.Drawing.Point(554, 214);
            this.Remove.Name = "Remove";
            this.Remove.Size = new System.Drawing.Size(200, 36);
            this.Remove.TabIndex = 15;
            this.Remove.Text = "Delete Image";
            this.Remove.UseVisualStyleBackColor = true;
            this.Remove.Click += new System.EventHandler(this.Remove_Click);
            // 
            // Next
            // 
            this.Next.Location = new System.Drawing.Point(341, 354);
            this.Next.Name = "Next";
            this.Next.Size = new System.Drawing.Size(186, 23);
            this.Next.TabIndex = 17;
            this.Next.Text = ">";
            this.Next.UseVisualStyleBackColor = true;
            this.Next.Click += new System.EventHandler(this.Next_Click);
            // 
            // Open
            // 
            this.Open.Location = new System.Drawing.Point(554, 86);
            this.Open.Name = "Open";
            this.Open.Size = new System.Drawing.Size(200, 36);
            this.Open.TabIndex = 18;
            this.Open.Text = "Open Image";
            this.Open.UseVisualStyleBackColor = true;
            this.Open.Click += new System.EventHandler(this.Add_Click);
            // 
            // Prev
            // 
            this.Prev.Location = new System.Drawing.Point(15, 354);
            this.Prev.Name = "Prev";
            this.Prev.Size = new System.Drawing.Size(165, 23);
            this.Prev.TabIndex = 19;
            this.Prev.Text = "<";
            this.Prev.UseVisualStyleBackColor = true;
            this.Prev.Click += new System.EventHandler(this.Prev_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Enabled = false;
            this.label5.Location = new System.Drawing.Point(551, 259);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(87, 13);
            this.label5.TabIndex = 20;
            this.label5.Text = "Timer Intelval [s]:";
            // 
            // TimerInterval
            // 
            this.TimerInterval.Enabled = false;
            this.TimerInterval.FormattingEnabled = true;
            this.TimerInterval.ImeMode = System.Windows.Forms.ImeMode.On;
            this.TimerInterval.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.TimerInterval.Location = new System.Drawing.Point(675, 256);
            this.TimerInterval.Name = "TimerInterval";
            this.TimerInterval.Size = new System.Drawing.Size(79, 21);
            this.TimerInterval.TabIndex = 21;
            // 
            // Inverting
            // 
            this.Inverting.AutoSize = true;
            this.Inverting.CheckAlign = System.Drawing.ContentAlignment.TopRight;
            this.Inverting.Enabled = false;
            this.Inverting.Location = new System.Drawing.Point(554, 283);
            this.Inverting.Name = "Inverting";
            this.Inverting.Size = new System.Drawing.Size(53, 17);
            this.Inverting.TabIndex = 22;
            this.Inverting.Text = "Invert";
            this.Inverting.UseVisualStyleBackColor = true;
            this.Inverting.CheckedChanged += new System.EventHandler(this.Inverting_CheckedChanged);
            // 
            // Export
            // 
            this.Export.Enabled = false;
            this.Export.Location = new System.Drawing.Point(554, 150);
            this.Export.Name = "Export";
            this.Export.Size = new System.Drawing.Size(200, 36);
            this.Export.TabIndex = 23;
            this.Export.Text = "Export...";
            this.Export.UseVisualStyleBackColor = true;
            this.Export.Click += new System.EventHandler(this.Export_Click);
            // 
            // B5PLMF
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 400);
            this.Controls.Add(this.Export);
            this.Controls.Add(this.Inverting);
            this.Controls.Add(this.TimerInterval);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.Prev);
            this.Controls.Add(this.Open);
            this.Controls.Add(this.Next);
            this.Controls.Add(this.Remove);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.Send);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label1);
            this.MaximumSize = this.Size;
            this.MinimumSize = this.Size;
            this.Name = "B5PLMF";
            this.Text = "Billboard";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button Send;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button Remove;
        private System.Windows.Forms.Button Next;
        private System.Windows.Forms.Button Open;
        private System.Windows.Forms.Button Prev;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox TimerInterval;
        private System.Windows.Forms.CheckBox Inverting;
        private System.Windows.Forms.Button Export;
    }
}

