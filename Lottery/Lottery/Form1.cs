using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Lottery
{
    public partial class Form1 : Form
    {
        c_Lottery Lottery;

        public Form1()
        {
            InitializeComponent();
            Lottery = new c_Lottery();
        }

        private void button_Pick_Click(object sender, EventArgs e)
        {
            string str = Lottery.Pick(true);
            richTextBox_Picked.Text += str + "\n";
            str = Lottery.ReadParticipant();
            richTextBox_Participant.Text = str;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Lottery.LoadParticipant();
            string str = Lottery.ReadParticipant();
            richTextBox_Participant.Text = str;
            richTextBox_Picked.Text = "";
        }

        private void timer_Lottery_Tick(object sender, EventArgs e)
        {
            textBox1.Text = Lottery.Pick(false);
        }
    }

    public class c_Lottery
    {
        double weightSum = 0.0, weight;
        Dictionary<string, double> participant_weight = new Dictionary<string, double>();

        List<string> picked;
        string line;
        string[] strs;

        object lockObj = new object();

        public void LoadParticipant(string path = "participantList_1st.txt")
        {
            picked = new List<string>();
            participant_weight = new Dictionary<string, double>();

            StreamReader sReader = new StreamReader(path);

            weightSum = 0.0;
            line = sReader.ReadLine();
            while (true)
            {
                line = sReader.ReadLine();

                if (line == null)
                    break;

                strs = line.Split('\t');
                weight = Convert.ToDouble(strs[1]);
                participant_weight.Add(strs[0], weight);
                weightSum += weight;
            }

            sReader.Close();

        }

        public string ReadParticipant()
        {
            lock (lockObj)
            {
                string str = "";
                foreach (string participant in participant_weight.Keys)
                {
                    str += participant + "\t" + participant_weight[participant] + "\n";
                }
                return str;
            }
        }

        public string Pick(bool isEliminate)
        {
            lock (lockObj)
            {
                Random rand = new Random();
                double weight = rand.NextDouble() * weightSum;
                string picked = "";

                foreach (string participant in participant_weight.Keys)
                {
                    weight -= participant_weight[participant];

                    if (weight <= 0.0)
                    {
                        picked = participant;
                        break;
                    }
                }

                if (picked != "" && isEliminate == true)
                {
                    weightSum -= participant_weight[picked];
                    participant_weight.Remove(picked);
                }

                return picked;
            }
        }
    }
}
