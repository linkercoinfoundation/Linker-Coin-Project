namespace Lottery
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.button1 = new System.Windows.Forms.Button();
            this.timer_Lottery = new System.Windows.Forms.Timer(this.components);
            this.richTextBox_Participant = new System.Windows.Forms.RichTextBox();
            this.button_Pick = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.richTextBox_Picked = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(112, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "Load Participant";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // timer_Lottery
            // 
            this.timer_Lottery.Enabled = true;
            this.timer_Lottery.Tick += new System.EventHandler(this.timer_Lottery_Tick);
            // 
            // richTextBox_Participant
            // 
            this.richTextBox_Participant.Location = new System.Drawing.Point(12, 41);
            this.richTextBox_Participant.Name = "richTextBox_Participant";
            this.richTextBox_Participant.Size = new System.Drawing.Size(422, 201);
            this.richTextBox_Participant.TabIndex = 1;
            this.richTextBox_Participant.Text = "";
            // 
            // button_Pick
            // 
            this.button_Pick.Location = new System.Drawing.Point(356, 263);
            this.button_Pick.Name = "button_Pick";
            this.button_Pick.Size = new System.Drawing.Size(78, 23);
            this.button_Pick.TabIndex = 2;
            this.button_Pick.Text = "Pick";
            this.button_Pick.UseVisualStyleBackColor = true;
            this.button_Pick.Click += new System.EventHandler(this.button_Pick_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 264);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(338, 21);
            this.textBox1.TabIndex = 3;
            // 
            // richTextBox_Picked
            // 
            this.richTextBox_Picked.Location = new System.Drawing.Point(12, 292);
            this.richTextBox_Picked.Name = "richTextBox_Picked";
            this.richTextBox_Picked.Size = new System.Drawing.Size(422, 150);
            this.richTextBox_Picked.TabIndex = 4;
            this.richTextBox_Picked.Text = "";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(446, 454);
            this.Controls.Add(this.richTextBox_Picked);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button_Pick);
            this.Controls.Add(this.richTextBox_Participant);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Lottery Program";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Timer timer_Lottery;
        private System.Windows.Forms.RichTextBox richTextBox_Participant;
        private System.Windows.Forms.Button button_Pick;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.RichTextBox richTextBox_Picked;
    }
}

