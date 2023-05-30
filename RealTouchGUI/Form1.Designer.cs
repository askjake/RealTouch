using System.Windows.Forms;

namespace RealTouchGUI
{
    public void updateRichTextBox(string text)
    {
        if (InvokeRequired)
        {
            this.Invoke(new Action<string>(updateRichTextBox), new object[] { text });
            return;
        }
        richTextBox1.Text += text + "\n";
    }

    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            pictureBox1 = new PictureBox();
            imageList1 = new ImageList(components);
            button2 = new Button();
            button3 = new Button();
            button1 = new Button();
            button4 = new Button();
            button5 = new Button();
            button6 = new Button();
            button7 = new Button();
            button8 = new Button();
            button9 = new Button();
            button10 = new Button();
            button11 = new Button();
            button12 = new Button();
            button13 = new Button();
            button14 = new Button();
            button15 = new Button();
            button16 = new Button();
            button17 = new Button();
            button18 = new Button();
            button19 = new Button();
            button20 = new Button();
            button21 = new Button();
            button22 = new Button();
            button23 = new Button();
            button24 = new Button();
            button25 = new Button();
            button26 = new Button();
            button27 = new Button();
            button28 = new Button();
            button29 = new Button();
            button30 = new Button();
            button31 = new Button();
            button32 = new Button();
            button33 = new Button();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            label1 = new Label();
            label2 = new Label();
            label4 = new Label();
            textBox4 = new TextBox();
            checkBox1 = new CheckBox();
            checkBox2 = new CheckBox();
            checkBox3 = new CheckBox();
            checkBox4 = new CheckBox();
            checkBox5 = new CheckBox();
            checkBox6 = new CheckBox();
            checkBox7 = new CheckBox();
            checkBox8 = new CheckBox();
            checkBox9 = new CheckBox();
            checkBox10 = new CheckBox();
            checkBox11 = new CheckBox();
            checkBox12 = new CheckBox();
            checkBox13 = new CheckBox();
            checkBox14 = new CheckBox();
            checkBox15 = new CheckBox();
            checkBox16 = new CheckBox();
            textBox3 = new TextBox();
            textBox5 = new TextBox();
            textBox6 = new TextBox();
            textBox7 = new TextBox();
            textBox8 = new TextBox();
            textBox9 = new TextBox();
            textBox10 = new TextBox();
            textBox11 = new TextBox();
            textBox12 = new TextBox();
            textBox13 = new TextBox();
            textBox14 = new TextBox();
            textBox15 = new TextBox();
            textBox16 = new TextBox();
            textBox17 = new TextBox();
            textBox18 = new TextBox();
            textBox19 = new TextBox();
            textBox20 = new TextBox();
            textBox21 = new TextBox();
            label3 = new Label();
            textBox22 = new TextBox();
            label5 = new Label();
            label6 = new Label();
            textBox23 = new TextBox();
            textBox24 = new TextBox();
            textBox25 = new TextBox();
            textBox26 = new TextBox();
            textBox27 = new TextBox();
            textBox28 = new TextBox();
            textBox29 = new TextBox();
            textBox30 = new TextBox();
            textBox31 = new TextBox();
            textBox32 = new TextBox();
            textBox33 = new TextBox();
            label7 = new Label();
            textBox34 = new TextBox();
            label8 = new Label();
            label9 = new Label();
            textBox35 = new TextBox();
            textBox36 = new TextBox();
            textBox37 = new TextBox();
            textBox38 = new TextBox();
            textBox39 = new TextBox();
            textBox40 = new TextBox();
            textBox41 = new TextBox();
            textBox42 = new TextBox();
            textBox43 = new TextBox();
            textBox44 = new TextBox();
            textBox45 = new TextBox();
            label10 = new Label();
            textBox46 = new TextBox();
            label11 = new Label();
            label12 = new Label();
            textBox47 = new TextBox();
            textBox48 = new TextBox();
            richTextBox1 = new RichTextBox();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            SuspendLayout();
            // 
            // pictureBox1
            // 
            pictureBox1.Image = (Image)resources.GetObject("pictureBox1.Image");
            pictureBox1.Location = new Point(31, 25);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(277, 815);
            pictureBox1.TabIndex = 0;
            pictureBox1.TabStop = false;
            // 
            // imageList1
            // 
            imageList1.ColorDepth = ColorDepth.Depth8Bit;
            imageList1.ImageSize = new Size(16, 16);
            imageList1.TransparentColor = Color.Transparent;
            // 
            // button2
            // 
            button2.Location = new Point(138, 526);
            button2.Name = "button2";
            button2.Size = new Size(54, 36);
            button2.TabIndex = 2;
            button2.Text = "2";
            button2.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            button3.Location = new Point(198, 526);
            button3.Name = "button3";
            button3.Size = new Size(52, 36);
            button3.TabIndex = 3;
            button3.Text = "3";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click_1;
            // 
            // button1
            // 
            button1.BackColor = SystemColors.Control;
            button1.FlatStyle = FlatStyle.Flat;
            button1.ForeColor = SystemColors.ActiveBorder;
            button1.Location = new Point(75, 526);
            button1.Name = "button1";
            button1.Size = new Size(57, 36);
            button1.TabIndex = 1;
            button1.Text = "1";
            button1.UseVisualStyleBackColor = false;
            button1.Click += button1_Click;
            // 
            // button4
            // 
            button4.Location = new Point(75, 579);
            button4.Name = "button4";
            button4.Size = new Size(57, 31);
            button4.TabIndex = 4;
            button4.Text = "4";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click_1;
            // 
            // button5
            // 
            button5.Location = new Point(138, 577);
            button5.Name = "button5";
            button5.Size = new Size(54, 31);
            button5.TabIndex = 5;
            button5.Text = "5";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click_1;
            // 
            // button6
            // 
            button6.Location = new Point(198, 577);
            button6.Name = "button6";
            button6.Size = new Size(52, 31);
            button6.TabIndex = 6;
            button6.Text = "6";
            button6.UseVisualStyleBackColor = true;
            button6.Click += button6_Click_1;
            // 
            // button7
            // 
            button7.Location = new Point(198, 665);
            button7.Name = "button7";
            button7.Size = new Size(52, 31);
            button7.TabIndex = 12;
            button7.Text = "ddiamaond";
            button7.UseVisualStyleBackColor = true;
            button7.Click += button7_Click_1;
            // 
            // button8
            // 
            button8.Location = new Point(138, 665);
            button8.Name = "button8";
            button8.Size = new Size(54, 31);
            button8.TabIndex = 11;
            button8.Text = "0";
            button8.UseVisualStyleBackColor = true;
            button8.Click += button8_Click_1;
            // 
            // button9
            // 
            button9.BackColor = Color.Transparent;
            button9.Location = new Point(75, 665);
            button9.Name = "button9";
            button9.Size = new Size(57, 31);
            button9.TabIndex = 10;
            button9.Text = "diamond";
            button9.UseVisualStyleBackColor = false;
            button9.Click += button9_Click_1;
            // 
            // button10
            // 
            button10.Location = new Point(198, 614);
            button10.Name = "button10";
            button10.Size = new Size(52, 36);
            button10.TabIndex = 9;
            button10.Text = "9";
            button10.UseVisualStyleBackColor = true;
            button10.Click += button10_Click_1;
            // 
            // button11
            // 
            button11.Location = new Point(138, 614);
            button11.Name = "button11";
            button11.Size = new Size(54, 36);
            button11.TabIndex = 8;
            button11.Text = "8";
            button11.UseVisualStyleBackColor = true;
            button11.Click += button11_Click_1;
            // 
            // button12
            // 
            button12.BackColor = SystemColors.Control;
            button12.FlatStyle = FlatStyle.Flat;
            button12.ForeColor = SystemColors.ActiveBorder;
            button12.Location = new Point(75, 614);
            button12.Name = "button12";
            button12.Size = new Size(57, 36);
            button12.TabIndex = 7;
            button12.Text = "7";
            button12.UseVisualStyleBackColor = false;
            button12.Click += button12_Click_1;
            // 
            // button13
            // 
            button13.Location = new Point(198, 351);
            button13.Name = "button13";
            button13.Size = new Size(68, 36);
            button13.TabIndex = 15;
            button13.Text = "ffw";
            button13.UseVisualStyleBackColor = true;
            // 
            // button14
            // 
            button14.Location = new Point(138, 351);
            button14.Name = "button14";
            button14.Size = new Size(54, 36);
            button14.TabIndex = 14;
            button14.Text = "play";
            button14.UseVisualStyleBackColor = true;
            // 
            // button15
            // 
            button15.BackColor = SystemColors.Control;
            button15.FlatStyle = FlatStyle.Flat;
            button15.ForeColor = SystemColors.ActiveBorder;
            button15.Location = new Point(63, 351);
            button15.Name = "button15";
            button15.Size = new Size(69, 36);
            button15.TabIndex = 13;
            button15.Text = "rwd";
            button15.UseVisualStyleBackColor = false;
            // 
            // button16
            // 
            button16.Location = new Point(198, 465);
            button16.Name = "button16";
            button16.Size = new Size(68, 45);
            button16.TabIndex = 18;
            button16.Text = "button16";
            button16.UseVisualStyleBackColor = true;
            // 
            // button17
            // 
            button17.Location = new Point(138, 474);
            button17.Name = "button17";
            button17.Size = new Size(54, 36);
            button17.TabIndex = 17;
            button17.Text = "button17";
            button17.UseVisualStyleBackColor = true;
            // 
            // button18
            // 
            button18.BackColor = SystemColors.Control;
            button18.FlatStyle = FlatStyle.Flat;
            button18.ForeColor = SystemColors.ActiveBorder;
            button18.Location = new Point(75, 474);
            button18.Name = "button18";
            button18.Size = new Size(57, 36);
            button18.TabIndex = 16;
            button18.Text = "vol_down";
            button18.UseVisualStyleBackColor = false;
            // 
            // button19
            // 
            button19.Location = new Point(198, 409);
            button19.Name = "button19";
            button19.Size = new Size(68, 50);
            button19.TabIndex = 21;
            button19.Text = "ch_up";
            button19.UseVisualStyleBackColor = true;
            // 
            // button20
            // 
            button20.Location = new Point(138, 423);
            button20.Name = "button20";
            button20.Size = new Size(54, 36);
            button20.TabIndex = 20;
            button20.Text = "recall";
            button20.UseVisualStyleBackColor = true;
            // 
            // button21
            // 
            button21.BackColor = SystemColors.Control;
            button21.FlatStyle = FlatStyle.Flat;
            button21.ForeColor = SystemColors.ActiveBorder;
            button21.Location = new Point(75, 409);
            button21.Name = "button21";
            button21.Size = new Size(57, 50);
            button21.TabIndex = 19;
            button21.Text = "vol_up";
            button21.UseVisualStyleBackColor = false;
            // 
            // button22
            // 
            button22.Location = new Point(213, 92);
            button22.Name = "button22";
            button22.Size = new Size(68, 36);
            button22.TabIndex = 24;
            button22.Text = "guide";
            button22.UseVisualStyleBackColor = true;
            button22.Click += button22_Click_1;
            // 
            // button23
            // 
            button23.BackColor = Color.Transparent;
            button23.BackgroundImageLayout = ImageLayout.None;
            button23.FlatAppearance.MouseDownBackColor = Color.Transparent;
            button23.FlatAppearance.MouseOverBackColor = Color.Transparent;
            button23.FlatStyle = FlatStyle.Flat;
            button23.Location = new Point(122, 92);
            button23.Name = "button23";
            button23.Size = new Size(85, 36);
            button23.TabIndex = 23;
            button23.Text = "home";
            button23.UseVisualStyleBackColor = false;
            button23.Click += button23_Click;
            // 
            // button24
            // 
            button24.BackColor = SystemColors.Control;
            button24.FlatStyle = FlatStyle.Flat;
            button24.ForeColor = SystemColors.ActiveBorder;
            button24.Location = new Point(47, 92);
            button24.Name = "button24";
            button24.Size = new Size(69, 36);
            button24.TabIndex = 22;
            button24.Text = "dvr";
            button24.UseVisualStyleBackColor = false;
            button24.Click += button24_Click;
            // 
            // button25
            // 
            button25.BackColor = Color.Transparent;
            button25.Location = new Point(138, 288);
            button25.Name = "button25";
            button25.Size = new Size(59, 47);
            button25.TabIndex = 31;
            button25.UseVisualStyleBackColor = false;
            button25.Click += button25_Click;
            // 
            // button26
            // 
            button26.Location = new Point(122, 143);
            button26.Name = "button26";
            button26.Size = new Size(85, 49);
            button26.TabIndex = 26;
            button26.Text = "up";
            button26.UseVisualStyleBackColor = true;
            button26.Click += button26_Click;
            // 
            // button27
            // 
            button27.BackColor = SystemColors.Control;
            button27.FlatStyle = FlatStyle.Flat;
            button27.ForeColor = SystemColors.ActiveBorder;
            button27.Location = new Point(47, 143);
            button27.Name = "button27";
            button27.Size = new Size(69, 49);
            button27.TabIndex = 25;
            button27.Text = "options";
            button27.UseVisualStyleBackColor = false;
            button27.Click += button27_Click;
            // 
            // button28
            // 
            button28.Location = new Point(220, 222);
            button28.Name = "button28";
            button28.Size = new Size(68, 36);
            button28.TabIndex = 30;
            button28.Text = "right";
            button28.UseVisualStyleBackColor = true;
            button28.Click += button28_Click;
            // 
            // button29
            // 
            button29.BackColor = Color.Transparent;
            button29.Location = new Point(129, 198);
            button29.Name = "button29";
            button29.Size = new Size(85, 84);
            button29.TabIndex = 29;
            button29.UseVisualStyleBackColor = false;
            button29.Click += button29_Click;
            // 
            // button30
            // 
            button30.BackColor = SystemColors.Control;
            button30.FlatStyle = FlatStyle.Flat;
            button30.ForeColor = SystemColors.ActiveBorder;
            button30.Location = new Point(47, 222);
            button30.Name = "button30";
            button30.Size = new Size(69, 36);
            button30.TabIndex = 28;
            button30.Text = "left";
            button30.UseVisualStyleBackColor = false;
            button30.Click += button30_Click;
            // 
            // button31
            // 
            button31.BackColor = Color.Transparent;
            button31.BackgroundImageLayout = ImageLayout.None;
            button31.ForeColor = Color.Transparent;
            button31.Location = new Point(63, 288);
            button31.Name = "button31";
            button31.Size = new Size(53, 47);
            button31.TabIndex = 0;
            button31.UseVisualStyleBackColor = false;
            // 
            // button32
            // 
            button32.Location = new Point(213, 288);
            button32.Name = "button32";
            button32.Size = new Size(68, 47);
            button32.TabIndex = 1;
            button32.Click += button32_Click;
            // 
            // button33
            // 
            button33.AllowDrop = true;
            button33.AutoEllipsis = true;
            button33.Location = new Point(232, 143);
            button33.Name = "button33";
            button33.Size = new Size(56, 49);
            button33.TabIndex = 6;
            button33.UseCompatibleTextRendering = true;
            button33.Click += button33_Click;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(544, 50);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(100, 23);
            textBox1.TabIndex = 32;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(650, 50);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(100, 23);
            textBox2.TabIndex = 33;
            textBox2.KeyDown += textBox2_KeyDown;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(559, 25);
            label1.Name = "label1";
            label1.Size = new Size(39, 15);
            label1.TabIndex = 34;
            label1.Text = "Name";
            label1.Click += label1_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(679, 25);
            label2.Name = "label2";
            label2.Size = new Size(17, 15);
            label2.TabIndex = 35;
            label2.Text = "IP";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(773, 25);
            label4.Name = "label4";
            label4.Size = new Size(65, 15);
            label4.TabIndex = 38;
            label4.Text = "Receiver ID";
            label4.Click += label4_Click;
            // 
            // textBox4
            // 
            textBox4.Location = new Point(758, 50);
            textBox4.Name = "textBox4";
            textBox4.Size = new Size(100, 23);
            textBox4.TabIndex = 36;
            textBox4.KeyDown += textBox2_KeyDown;
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Location = new Point(337, 50);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(76, 19);
            checkBox1.TabIndex = 39;
            checkBox1.Text = "Remote 1";
            checkBox1.UseVisualStyleBackColor = true;
            // 
            // checkBox2
            // 
            checkBox2.AutoSize = true;
            checkBox2.Location = new Point(337, 75);
            checkBox2.Name = "checkBox2";
            checkBox2.Size = new Size(76, 19);
            checkBox2.TabIndex = 40;
            checkBox2.Text = "Remote 2";
            checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox3
            // 
            checkBox3.AutoSize = true;
            checkBox3.Location = new Point(337, 125);
            checkBox3.Name = "checkBox3";
            checkBox3.Size = new Size(76, 19);
            checkBox3.TabIndex = 42;
            checkBox3.Text = "Remote 4";
            checkBox3.UseVisualStyleBackColor = true;
            // 
            // checkBox4
            // 
            checkBox4.AutoSize = true;
            checkBox4.Location = new Point(337, 100);
            checkBox4.Name = "checkBox4";
            checkBox4.Size = new Size(76, 19);
            checkBox4.TabIndex = 41;
            checkBox4.Text = "Remote 3";
            checkBox4.UseVisualStyleBackColor = true;
            // 
            // checkBox5
            // 
            checkBox5.AutoSize = true;
            checkBox5.Location = new Point(337, 271);
            checkBox5.Name = "checkBox5";
            checkBox5.Size = new Size(76, 19);
            checkBox5.TabIndex = 46;
            checkBox5.Text = "Remote 8";
            checkBox5.UseVisualStyleBackColor = true;
            // 
            // checkBox6
            // 
            checkBox6.AutoSize = true;
            checkBox6.Location = new Point(337, 246);
            checkBox6.Name = "checkBox6";
            checkBox6.Size = new Size(76, 19);
            checkBox6.TabIndex = 45;
            checkBox6.Text = "Remote 7";
            checkBox6.UseVisualStyleBackColor = true;
            // 
            // checkBox7
            // 
            checkBox7.AutoSize = true;
            checkBox7.Location = new Point(337, 221);
            checkBox7.Name = "checkBox7";
            checkBox7.Size = new Size(76, 19);
            checkBox7.TabIndex = 44;
            checkBox7.Text = "Remote 6";
            checkBox7.UseVisualStyleBackColor = true;
            // 
            // checkBox8
            // 
            checkBox8.AutoSize = true;
            checkBox8.Location = new Point(337, 196);
            checkBox8.Name = "checkBox8";
            checkBox8.Size = new Size(76, 19);
            checkBox8.TabIndex = 43;
            checkBox8.Text = "Remote 5";
            checkBox8.UseVisualStyleBackColor = true;
            // 
            // checkBox9
            // 
            checkBox9.AutoSize = true;
            checkBox9.Location = new Point(337, 412);
            checkBox9.Name = "checkBox9";
            checkBox9.Size = new Size(82, 19);
            checkBox9.TabIndex = 50;
            checkBox9.Text = "Remote 12";
            checkBox9.UseVisualStyleBackColor = true;
            // 
            // checkBox10
            // 
            checkBox10.AutoSize = true;
            checkBox10.Location = new Point(337, 387);
            checkBox10.Name = "checkBox10";
            checkBox10.Size = new Size(82, 19);
            checkBox10.TabIndex = 49;
            checkBox10.Text = "Remote 11";
            checkBox10.UseVisualStyleBackColor = true;
            // 
            // checkBox11
            // 
            checkBox11.AutoSize = true;
            checkBox11.Location = new Point(337, 362);
            checkBox11.Name = "checkBox11";
            checkBox11.Size = new Size(82, 19);
            checkBox11.TabIndex = 48;
            checkBox11.Text = "Remote 10";
            checkBox11.UseVisualStyleBackColor = true;
            // 
            // checkBox12
            // 
            checkBox12.AutoSize = true;
            checkBox12.Location = new Point(337, 337);
            checkBox12.Name = "checkBox12";
            checkBox12.Size = new Size(76, 19);
            checkBox12.TabIndex = 47;
            checkBox12.Text = "Remote 9";
            checkBox12.UseVisualStyleBackColor = true;
            // 
            // checkBox13
            // 
            checkBox13.AutoSize = true;
            checkBox13.Location = new Point(337, 557);
            checkBox13.Name = "checkBox13";
            checkBox13.Size = new Size(82, 19);
            checkBox13.TabIndex = 54;
            checkBox13.Text = "Remote 16";
            checkBox13.UseVisualStyleBackColor = true;
            // 
            // checkBox14
            // 
            checkBox14.AutoSize = true;
            checkBox14.Location = new Point(337, 532);
            checkBox14.Name = "checkBox14";
            checkBox14.Size = new Size(82, 19);
            checkBox14.TabIndex = 53;
            checkBox14.Text = "Remote 15";
            checkBox14.UseVisualStyleBackColor = true;
            // 
            // checkBox15
            // 
            checkBox15.AutoSize = true;
            checkBox15.Location = new Point(337, 507);
            checkBox15.Name = "checkBox15";
            checkBox15.Size = new Size(82, 19);
            checkBox15.TabIndex = 52;
            checkBox15.Text = "Remote 14";
            checkBox15.UseVisualStyleBackColor = true;
            // 
            // checkBox16
            // 
            checkBox16.AutoSize = true;
            checkBox16.Location = new Point(337, 482);
            checkBox16.Name = "checkBox16";
            checkBox16.Size = new Size(82, 19);
            checkBox16.TabIndex = 51;
            checkBox16.Text = "Remote 13";
            checkBox16.UseVisualStyleBackColor = true;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(758, 79);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(100, 23);
            textBox3.TabIndex = 57;
            // 
            // textBox5
            // 
            textBox5.Location = new Point(650, 79);
            textBox5.Name = "textBox5";
            textBox5.Size = new Size(100, 23);
            textBox5.TabIndex = 56;
            // 
            // textBox6
            // 
            textBox6.Location = new Point(544, 79);
            textBox6.Name = "textBox6";
            textBox6.Size = new Size(100, 23);
            textBox6.TabIndex = 55;
            // 
            // textBox7
            // 
            textBox7.Location = new Point(758, 108);
            textBox7.Name = "textBox7";
            textBox7.Size = new Size(100, 23);
            textBox7.TabIndex = 60;
            // 
            // textBox8
            // 
            textBox8.Location = new Point(650, 108);
            textBox8.Name = "textBox8";
            textBox8.Size = new Size(100, 23);
            textBox8.TabIndex = 59;
            // 
            // textBox9
            // 
            textBox9.Location = new Point(544, 108);
            textBox9.Name = "textBox9";
            textBox9.Size = new Size(100, 23);
            textBox9.TabIndex = 58;
            // 
            // textBox10
            // 
            textBox10.Location = new Point(758, 137);
            textBox10.Name = "textBox10";
            textBox10.Size = new Size(100, 23);
            textBox10.TabIndex = 63;
            // 
            // textBox11
            // 
            textBox11.Location = new Point(650, 137);
            textBox11.Name = "textBox11";
            textBox11.Size = new Size(100, 23);
            textBox11.TabIndex = 62;
            // 
            // textBox12
            // 
            textBox12.Location = new Point(544, 137);
            textBox12.Name = "textBox12";
            textBox12.Size = new Size(100, 23);
            textBox12.TabIndex = 61;
            // 
            // textBox13
            // 
            textBox13.Location = new Point(758, 283);
            textBox13.Name = "textBox13";
            textBox13.Size = new Size(100, 23);
            textBox13.TabIndex = 78;
            // 
            // textBox14
            // 
            textBox14.Location = new Point(650, 283);
            textBox14.Name = "textBox14";
            textBox14.Size = new Size(100, 23);
            textBox14.TabIndex = 77;
            // 
            // textBox15
            // 
            textBox15.Location = new Point(544, 283);
            textBox15.Name = "textBox15";
            textBox15.Size = new Size(100, 23);
            textBox15.TabIndex = 76;
            // 
            // textBox16
            // 
            textBox16.Location = new Point(758, 254);
            textBox16.Name = "textBox16";
            textBox16.Size = new Size(100, 23);
            textBox16.TabIndex = 75;
            // 
            // textBox17
            // 
            textBox17.Location = new Point(650, 254);
            textBox17.Name = "textBox17";
            textBox17.Size = new Size(100, 23);
            textBox17.TabIndex = 74;
            // 
            // textBox18
            // 
            textBox18.Location = new Point(544, 254);
            textBox18.Name = "textBox18";
            textBox18.Size = new Size(100, 23);
            textBox18.TabIndex = 73;
            // 
            // textBox19
            // 
            textBox19.Location = new Point(758, 225);
            textBox19.Name = "textBox19";
            textBox19.Size = new Size(100, 23);
            textBox19.TabIndex = 72;
            // 
            // textBox20
            // 
            textBox20.Location = new Point(650, 225);
            textBox20.Name = "textBox20";
            textBox20.Size = new Size(100, 23);
            textBox20.TabIndex = 71;
            // 
            // textBox21
            // 
            textBox21.Location = new Point(544, 225);
            textBox21.Name = "textBox21";
            textBox21.Size = new Size(100, 23);
            textBox21.TabIndex = 70;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(773, 171);
            label3.Name = "label3";
            label3.Size = new Size(65, 15);
            label3.TabIndex = 69;
            label3.Text = "Receiver ID";
            // 
            // textBox22
            // 
            textBox22.Location = new Point(758, 196);
            textBox22.Name = "textBox22";
            textBox22.Size = new Size(100, 23);
            textBox22.TabIndex = 68;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(679, 171);
            label5.Name = "label5";
            label5.Size = new Size(17, 15);
            label5.TabIndex = 67;
            label5.Text = "IP";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(559, 171);
            label6.Name = "label6";
            label6.Size = new Size(39, 15);
            label6.TabIndex = 66;
            label6.Text = "Name";
            // 
            // textBox23
            // 
            textBox23.Location = new Point(650, 196);
            textBox23.Name = "textBox23";
            textBox23.Size = new Size(100, 23);
            textBox23.TabIndex = 65;
            // 
            // textBox24
            // 
            textBox24.Location = new Point(544, 196);
            textBox24.Name = "textBox24";
            textBox24.Size = new Size(100, 23);
            textBox24.TabIndex = 64;
            // 
            // textBox25
            // 
            textBox25.Location = new Point(758, 424);
            textBox25.Name = "textBox25";
            textBox25.Size = new Size(100, 23);
            textBox25.TabIndex = 93;
            // 
            // textBox26
            // 
            textBox26.Location = new Point(650, 424);
            textBox26.Name = "textBox26";
            textBox26.Size = new Size(100, 23);
            textBox26.TabIndex = 92;
            // 
            // textBox27
            // 
            textBox27.Location = new Point(544, 424);
            textBox27.Name = "textBox27";
            textBox27.Size = new Size(100, 23);
            textBox27.TabIndex = 91;
            // 
            // textBox28
            // 
            textBox28.Location = new Point(758, 395);
            textBox28.Name = "textBox28";
            textBox28.Size = new Size(100, 23);
            textBox28.TabIndex = 90;
            // 
            // textBox29
            // 
            textBox29.Location = new Point(650, 395);
            textBox29.Name = "textBox29";
            textBox29.Size = new Size(100, 23);
            textBox29.TabIndex = 89;
            // 
            // textBox30
            // 
            textBox30.Location = new Point(544, 395);
            textBox30.Name = "textBox30";
            textBox30.Size = new Size(100, 23);
            textBox30.TabIndex = 88;
            // 
            // textBox31
            // 
            textBox31.Location = new Point(758, 366);
            textBox31.Name = "textBox31";
            textBox31.Size = new Size(100, 23);
            textBox31.TabIndex = 87;
            // 
            // textBox32
            // 
            textBox32.Location = new Point(650, 366);
            textBox32.Name = "textBox32";
            textBox32.Size = new Size(100, 23);
            textBox32.TabIndex = 86;
            // 
            // textBox33
            // 
            textBox33.Location = new Point(544, 366);
            textBox33.Name = "textBox33";
            textBox33.Size = new Size(100, 23);
            textBox33.TabIndex = 85;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(773, 312);
            label7.Name = "label7";
            label7.Size = new Size(65, 15);
            label7.TabIndex = 84;
            label7.Text = "Receiver ID";
            // 
            // textBox34
            // 
            textBox34.Location = new Point(758, 337);
            textBox34.Name = "textBox34";
            textBox34.Size = new Size(100, 23);
            textBox34.TabIndex = 83;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(679, 312);
            label8.Name = "label8";
            label8.Size = new Size(17, 15);
            label8.TabIndex = 82;
            label8.Text = "IP";
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new Point(559, 312);
            label9.Name = "label9";
            label9.Size = new Size(39, 15);
            label9.TabIndex = 81;
            label9.Text = "Name";
            // 
            // textBox35
            // 
            textBox35.Location = new Point(650, 337);
            textBox35.Name = "textBox35";
            textBox35.Size = new Size(100, 23);
            textBox35.TabIndex = 80;
            // 
            // textBox36
            // 
            textBox36.Location = new Point(544, 337);
            textBox36.Name = "textBox36";
            textBox36.Size = new Size(100, 23);
            textBox36.TabIndex = 79;
            // 
            // textBox37
            // 
            textBox37.Location = new Point(758, 569);
            textBox37.Name = "textBox37";
            textBox37.Size = new Size(100, 23);
            textBox37.TabIndex = 108;
            // 
            // textBox38
            // 
            textBox38.Location = new Point(650, 569);
            textBox38.Name = "textBox38";
            textBox38.Size = new Size(100, 23);
            textBox38.TabIndex = 107;
            // 
            // textBox39
            // 
            textBox39.Location = new Point(544, 569);
            textBox39.Name = "textBox39";
            textBox39.Size = new Size(100, 23);
            textBox39.TabIndex = 106;
            // 
            // textBox40
            // 
            textBox40.Location = new Point(758, 540);
            textBox40.Name = "textBox40";
            textBox40.Size = new Size(100, 23);
            textBox40.TabIndex = 105;
            // 
            // textBox41
            // 
            textBox41.Location = new Point(650, 540);
            textBox41.Name = "textBox41";
            textBox41.Size = new Size(100, 23);
            textBox41.TabIndex = 104;
            // 
            // textBox42
            // 
            textBox42.Location = new Point(544, 540);
            textBox42.Name = "textBox42";
            textBox42.Size = new Size(100, 23);
            textBox42.TabIndex = 103;
            // 
            // textBox43
            // 
            textBox43.Location = new Point(758, 511);
            textBox43.Name = "textBox43";
            textBox43.Size = new Size(100, 23);
            textBox43.TabIndex = 102;
            // 
            // textBox44
            // 
            textBox44.Location = new Point(650, 511);
            textBox44.Name = "textBox44";
            textBox44.Size = new Size(100, 23);
            textBox44.TabIndex = 101;
            // 
            // textBox45
            // 
            textBox45.Location = new Point(544, 511);
            textBox45.Name = "textBox45";
            textBox45.Size = new Size(100, 23);
            textBox45.TabIndex = 100;
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new Point(773, 457);
            label10.Name = "label10";
            label10.Size = new Size(65, 15);
            label10.TabIndex = 99;
            label10.Text = "Receiver ID";
            // 
            // textBox46
            // 
            textBox46.Location = new Point(758, 482);
            textBox46.Name = "textBox46";
            textBox46.Size = new Size(100, 23);
            textBox46.TabIndex = 98;
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Location = new Point(679, 457);
            label11.Name = "label11";
            label11.Size = new Size(17, 15);
            label11.TabIndex = 97;
            label11.Text = "IP";
            // 
            // label12
            // 
            label12.AutoSize = true;
            label12.Location = new Point(559, 457);
            label12.Name = "label12";
            label12.Size = new Size(39, 15);
            label12.TabIndex = 96;
            label12.Text = "Name";
            // 
            // textBox47
            // 
            textBox47.Location = new Point(650, 482);
            textBox47.Name = "textBox47";
            textBox47.Size = new Size(100, 23);
            textBox47.TabIndex = 95;
            // 
            // textBox48
            // 
            textBox48.Location = new Point(544, 482);
            textBox48.Name = "textBox48";
            textBox48.Size = new Size(100, 23);
            textBox48.TabIndex = 94;
            // 
            // richTextBox1
            // 
            richTextBox1.Location = new Point(326, 628);
            richTextBox1.Name = "richTextBox1";
            richTextBox1.Size = new Size(532, 212);
            richTextBox1.TabIndex = 109;
            richTextBox1.Text = "";
            richTextBox1.KeyDown += textBox2_KeyDown;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.ControlDark;
            ClientSize = new Size(1148, 974);
            Controls.Add(richTextBox1);
            Controls.Add(textBox37);
            Controls.Add(textBox38);
            Controls.Add(textBox39);
            Controls.Add(textBox40);
            Controls.Add(textBox41);
            Controls.Add(textBox42);
            Controls.Add(textBox43);
            Controls.Add(textBox44);
            Controls.Add(textBox45);
            Controls.Add(label10);
            Controls.Add(textBox46);
            Controls.Add(label11);
            Controls.Add(label12);
            Controls.Add(textBox47);
            Controls.Add(textBox48);
            Controls.Add(textBox25);
            Controls.Add(textBox26);
            Controls.Add(textBox27);
            Controls.Add(textBox28);
            Controls.Add(textBox29);
            Controls.Add(textBox30);
            Controls.Add(textBox31);
            Controls.Add(textBox32);
            Controls.Add(textBox33);
            Controls.Add(label7);
            Controls.Add(textBox34);
            Controls.Add(label8);
            Controls.Add(label9);
            Controls.Add(textBox35);
            Controls.Add(textBox36);
            Controls.Add(textBox13);
            Controls.Add(textBox14);
            Controls.Add(textBox15);
            Controls.Add(textBox16);
            Controls.Add(textBox17);
            Controls.Add(textBox18);
            Controls.Add(textBox19);
            Controls.Add(textBox20);
            Controls.Add(textBox21);
            Controls.Add(label3);
            Controls.Add(textBox22);
            Controls.Add(label5);
            Controls.Add(label6);
            Controls.Add(textBox23);
            Controls.Add(textBox24);
            Controls.Add(textBox10);
            Controls.Add(textBox11);
            Controls.Add(textBox12);
            Controls.Add(textBox7);
            Controls.Add(textBox8);
            Controls.Add(textBox9);
            Controls.Add(textBox3);
            Controls.Add(textBox5);
            Controls.Add(textBox6);
            Controls.Add(checkBox13);
            Controls.Add(checkBox14);
            Controls.Add(checkBox15);
            Controls.Add(checkBox16);
            Controls.Add(checkBox9);
            Controls.Add(checkBox10);
            Controls.Add(checkBox11);
            Controls.Add(checkBox12);
            Controls.Add(checkBox5);
            Controls.Add(checkBox6);
            Controls.Add(checkBox7);
            Controls.Add(checkBox8);
            Controls.Add(checkBox3);
            Controls.Add(checkBox4);
            Controls.Add(checkBox2);
            Controls.Add(checkBox1);
            Controls.Add(label4);
            Controls.Add(textBox4);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(textBox2);
            Controls.Add(textBox1);
            Controls.Add(button29);
            Controls.Add(button30);
            Controls.Add(button27);
            Controls.Add(button24);
            Controls.Add(button19);
            Controls.Add(button20);
            Controls.Add(button21);
            Controls.Add(button16);
            Controls.Add(button17);
            Controls.Add(button18);
            Controls.Add(button7);
            Controls.Add(button8);
            Controls.Add(button9);
            Controls.Add(button10);
            Controls.Add(button11);
            Controls.Add(button12);
            Controls.Add(button6);
            Controls.Add(button5);
            Controls.Add(button4);
            Controls.Add(button3);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(button31);
            Controls.Add(button32);
            Controls.Add(button33);
            Controls.Add(button28);
            Controls.Add(button25);
            Controls.Add(button26);
            Controls.Add(button22);
            Controls.Add(button23);
            Controls.Add(button13);
            Controls.Add(button14);
            Controls.Add(button15);
            Controls.Add(pictureBox1);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pictureBox1;
        private ImageList imageList1;
        private Button button2;
        private Button button3;
        private Button button1;
        private Button button4;
        private Button button5;
        private Button button6;
        private Button button7;
        private Button button8;
        private Button button9;
        private Button button10;
        private Button button11;
        private Button button12;
        private Button button13;
        private Button button14;
        private Button button15;
        private Button button16;
        private Button button17;
        private Button button18;
        private Button button19;
        private Button button20;
        private Button button21;
        private Button button22;
        private Button button23;
        private Button button24;
        private Button button25;
        private Button button26;
        private Button button27;
        private Button button28;
        private Button button29;
        private Button button30;
        private Button button31;
        private Button button32;
        private Button button33;
        private TextBox textBox1;
        private TextBox textBox2;
        private Label label1;
        private Label label2;
        private Label label4;
        private TextBox textBox4;
        private CheckBox checkBox1;
        private CheckBox checkBox2;
        private CheckBox checkBox3;
        private CheckBox checkBox4;
        private CheckBox checkBox5;
        private CheckBox checkBox6;
        private CheckBox checkBox7;
        private CheckBox checkBox8;
        private CheckBox checkBox9;
        private CheckBox checkBox10;
        private CheckBox checkBox11;
        private CheckBox checkBox12;
        private CheckBox checkBox13;
        private CheckBox checkBox14;
        private CheckBox checkBox15;
        private CheckBox checkBox16;
        private TextBox textBox3;
        private TextBox textBox5;
        private TextBox textBox6;
        private TextBox textBox7;
        private TextBox textBox8;
        private TextBox textBox9;
        private TextBox textBox10;
        private TextBox textBox11;
        private TextBox textBox12;
        private TextBox textBox13;
        private TextBox textBox14;
        private TextBox textBox15;
        private TextBox textBox16;
        private TextBox textBox17;
        private TextBox textBox18;
        private TextBox textBox19;
        private TextBox textBox20;
        private TextBox textBox21;
        private Label label3;
        private TextBox textBox22;
        private Label label5;
        private Label label6;
        private TextBox textBox23;
        private TextBox textBox24;
        private TextBox textBox25;
        private TextBox textBox26;
        private TextBox textBox27;
        private TextBox textBox28;
        private TextBox textBox29;
        private TextBox textBox30;
        private TextBox textBox31;
        private TextBox textBox32;
        private TextBox textBox33;
        private Label label7;
        private TextBox textBox34;
        private Label label8;
        private Label label9;
        private TextBox textBox35;
        private TextBox textBox36;
        private TextBox textBox37;
        private TextBox textBox38;
        private TextBox textBox39;
        private TextBox textBox40;
        private TextBox textBox41;
        private TextBox textBox42;
        private TextBox textBox43;
        private TextBox textBox44;
        private TextBox textBox45;
        private Label label10;
        private TextBox textBox46;
        private Label label11;
        private Label label12;
        private TextBox textBox47;
        private TextBox textBox48;
        private RichTextBox richTextBox1;
        private readonly EventHandler richTextBox1_TextAppendText;
    }
}
