using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace RealTouchGUI

{
    public partial class Form1 : Form
    {
        // Use a Timer to detect the long press
        private System.Windows.Forms.Timer buttonTimer = new System.Windows.Forms.Timer();

        public Form1()
        {
            InitializeComponent();

            // Set the Timer Interval to the length of time you want for the "long press"
            buttonTimer.Interval = 1000; // 1 second
            buttonTimer.Tick += ButtonTimer_Tick;

            // Assign the MouseDown and MouseUp events
            button31.MouseDown += Button31_MouseDown;
            button31.MouseUp += Button31_MouseUp;
        }
        private void Button31_MouseDown(object? sender, MouseEventArgs e)
        {
            buttonTimer.Start();
        }
        private void Button31_MouseUp(object? sender, MouseEventArgs e)
        {
            if (buttonTimer.Enabled)
            {
                buttonTimer.Stop();
            }
            else
            {
                RunPythonScript("Back");
            }
        }

        private void ButtonTimer_Tick(object? sender, EventArgs e)
        {
            buttonTimer.Stop();
            RunPythonScript("Live");
        }

        private void RunPythonScript(string buttonValue)
        {
            string stbIP = textBox2.Text; // Replace txtBoxIP with the name of your TextBox for IP
            string stbRID = textBox3.Text; // Replace txtBoxRID with the name of your TextBox for RID
            var psi = new ProcessStartInfo
            {
                FileName = "python", // Change this to the full path of your Python interpreter if necessary
                Arguments = $"{Path.Combine("c:\\Real_Touch\\RealTouch_GUI\\", "scripts", "sgs_remote.py")} -i {stbIP} -s {stbRID} {buttonValue}",
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                UseShellExecute = false,
                CreateNoWindow = true // This prevents the command window from appearing
            };

            var process = new Process { StartInfo = psi };
            process.Start();

            string output = process.StandardOutput.ReadToEnd();
            string error = process.StandardError.ReadToEnd();

            process.WaitForExit();
            // Print the output and error to the richTextBox
    updateRichTextBox($"Output: {output}");
    updateRichTextBox($"Error: {error}");

    // If you want to see the command being run, you can print it like this:
    updateRichTextBox($"Command: python {Path.Combine("c:\\Real_Touch\\RealTouch_GUI\\", "scripts", "sgs_remote.py")} {stb} {buttonValue}");


        }

        private void button1_Click(object sender, EventArgs e)
        {
            RunPythonScript("1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            RunPythonScript("2");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            RunPythonScript("3");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            RunPythonScript("4");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            RunPythonScript("5");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            RunPythonScript("6");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            RunPythonScript("7");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            RunPythonScript("8");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            RunPythonScript("9");
        }
        private void button10_Click(object sender, EventArgs e)
        {
            RunPythonScript("0");
        }
        private void button11_Click(object sender, EventArgs e)
        {
            RunPythonScript("11");
        }
        private void button12_Click(object sender, EventArgs e)
        {
            RunPythonScript("12");
        }
        private void button13_Click(object sender, EventArgs e)
        {
            RunPythonScript("ffd");
        }
        private void button14_Click(object sender, EventArgs e)
        {
            RunPythonScript("play");
        }
        private void button15_Click(object sender, EventArgs e)
        {
            RunPythonScript("rewind");
        }
        private void button16_Click(object sender, EventArgs e)
        {
            RunPythonScript("ch_down");
        }
        private void button17_Click(object sender, EventArgs e)
        {
            RunPythonScript("mute");
        }
        private void button18_Click(object sender, EventArgs e)
        {
            RunPythonScript("vol_down");
        }
        private void button19_Click(object sender, EventArgs e)
        {
            RunPythonScript("channel_up");
        }
        private void button20_Click(object sender, EventArgs e)
        {
            RunPythonScript("recall");
        }
        private void button21_Click(object sender, EventArgs e)
        {
            RunPythonScript("volume_up");
        }
        private void button22_Click(object sender, EventArgs e)
        {
            RunPythonScript("Guide");
        }
        private void button23_Click(object sender, EventArgs e)
        {
            RunPythonScript("Home");
        }
        private void button24_Click(object sender, EventArgs e)
        {
            RunPythonScript("DVR");
        }
        private void button29_Click(object sender, EventArgs e)
        {
            RunPythonScript("Enter");
        }
        private void button30_Click(object sender, EventArgs e)
        {
            RunPythonScript("Left");
        }
        private void button28_Click(object sender, EventArgs e)
        {
            RunPythonScript("Right");
        }
        private void button26_Click(object sender, EventArgs e)
        {
            RunPythonScript("Up");
        }
        private void button27_Click(object sender, EventArgs e)
        {
            RunPythonScript("Options");
        }
        /*private void Button31_MouseDown(object sender, MouseEventArgs e)
        {
            // Start the timer when the mouse button is pressed
            buttonTimer.Start();
        }
        private void Button31_MouseUp(object sender, MouseEventArgs e)
        {
            // Stop the timer when the mouse button is released
            buttonTimer.Stop();

            // If the timer is not running, then it's a short press. Perform your short press action here.
            if (!buttonTimer.Enabled)
            {
                RunPythonScript("-i 172.20.110.241 -s R1886471350-71 ", "Back");
            }
        }
        
        private void ButtonTimer_Tick(object sender, EventArgs e)
        {
            // The timer has ticked past the interval, so a long press has been detected.
            // Stop the timer so it doesn't continue to tick.
            buttonTimer.Stop();

            // Perform your long press action here.
            RunPythonScript("-i 172.20.110.241 -s R1886471350-71 ", "Live");
        }
        /*private void button31_Click(object sender, EventArgs e)
        {
            RunPythonScript("-i 172.20.110.241 -s R1886471350-71 ", "Back");
        }
        */
        private void button32_Click(object sender, EventArgs e)
        {
            RunPythonScript("Info");
        }

        private void button33_Click(object sender, EventArgs e)
        {
            RunPythonScript("Voice");
        }

        private void button25_Click(object sender, EventArgs e)
        {
            RunPythonScript("Down");
        }

        private void button5_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("5");
        }

        private void button6_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("6");
        }

        private void button12_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("7");
        }

        private void button11_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("8");
        }

        private void button10_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("9");
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("3");
        }

        private void button4_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("4");
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("2");
        }

        private void button9_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("diamond");
        }

        private void button8_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("0");
        }

        private void button7_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("ddiamond");
        }

        private void button22_Click_1(object sender, EventArgs e)
        {
            RunPythonScript("Guide");
        }



        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void textBox4_KeyDown(object sender, KeyEventArgs e)
        {
            Console.WriteLine("Committing changes: " + textBox4.Text);

            // If you don't want a newline in the TextBox when Enter is pressed
            e.SuppressKeyPress = true;
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                // Commit your changes
                // Replace the following line with your code
                Console.WriteLine("Committing changes: " + textBox2.Text);

                // If you don't want a newline in the TextBox when Enter is pressed
                e.SuppressKeyPress = true;
            }
        }

         // richTextBox1.AppendText("This is a debug message\n");

    }
}
