using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using System.Diagnostics;

namespace CityWeather
{

    public partial class Form1 : Form
    {
        Bitmap img;
        Graphics g;
        Scene scene, sceneTurned;
        double tetax, tetay, tetaz;

        LightSource sun1, sun2, sun3, sun4, sun5, currentSun;
        Zbuffer zbuf;
        ParticleSystem rain;
        
                
        public Form1()
        {
            InitializeComponent();
            Transformation.SetSize(canvas.Width, canvas.Height);

            img = new Bitmap(canvas.Width, canvas.Height);
            g = canvas.CreateGraphics();
            scene = new Scene(canvas.Size);
            scene.CreateScene();
            
            //Model building = Model.LoadModel(@"D:\GitHub\bmstu_CG_CP\CityWeather\CityWeather\res\power.obj");
            //scene.Add(building);
            SetSun();
            HandleSceneChange();
        }

        private void canvas_MouseMove(object sender, MouseEventArgs e)
        {
            label12.Text = zbuf.GetZ(e.X, e.Y).ToString();
        }
        
        /// <summary>
        /// Функция сравнения времени двух реализаций (Эксперементальная часть)
        /// </summary>
        public void CompareTime()
        {
            double res = AnalyseTime(zbuf.AddShadowsParallel);
            double res2 = AnalyseTime(zbuf.AddShadows);
            ;
        }

        public long AnalyseTime(Func<Bitmap> act)
        {
            int n = 20;
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();

            for (int i = 0; i < n; i++)
                act();

            stopWatch.Stop();
            return (long)(stopWatch.Elapsed.Ticks)/(long)n;
        }

        #region Установка освещения
        private void button1_Click(object sender, EventArgs e)
        {
            currentSun = sun1;
            HandleSceneChange();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            currentSun = sun2;
            HandleSceneChange();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            currentSun = sun3;
            HandleSceneChange();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            currentSun = sun4;
            HandleSceneChange();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            currentSun = sun5;
            HandleSceneChange();
        }

        private void SetSun()
        {
            sun1 = new LightSource(Color.White, -90, new Vector(1, 0, 0));
            sun2 = new LightSource(Color.White, -110, new Vector(0.4, -0.5, 0));
            sun3 = new LightSource(Color.White, 180, new Vector(0, -1, 0));
            sun4 = new LightSource(Color.White, 110, new Vector(-0.4, -0.5, 0));
            sun5 = new LightSource(Color.White, 90, new Vector(-1, 0, 0));
            currentSun = sun3;
        }
        #endregion

        #region Сцена
        
        private void buttonView_Click(object sender, EventArgs e)
        {
            canvas.Image = zbuf.GetImage();
        }

        private void buttonViewShadows_Click(object sender, EventArgs e)
        {
            canvas.Image = zbuf.AddShadows();
        }

        private void buttonViewSun_Click(object sender, EventArgs e)
        {
            canvas.Image = zbuf.GetSunImage();
        }

        private void buttonAddBuilding_Click(object sender, EventArgs e)
        {
            int x = Convert.ToInt32(textBoxSX.Text);
            int z = Convert.ToInt32(textBoxSZ.Text);
            int dx = Convert.ToInt32(textBoxSDx.Text);
            int dz = Convert.ToInt32(textBoxSDz.Text);
            int h = Convert.ToInt32(textBoxSH.Text);
            scene.CreateCube(Color.DarkKhaki, x, dx, z, dz, h);
            HandleSceneChange();
        }

        private void HandleSceneChange()
        {
            sceneTurned = scene.GetTurnedScene(tetax, tetay, tetaz);
            zbuf = new Zbuffer(sceneTurned, canvas.Size, currentSun);
            canvas.Image = zbuf.AddShadows();
        }
        #endregion

        #region Дождь
        private void buttonRain_Click(object sender, EventArgs e)
        {
            int intensity = Convert.ToInt32(textBoxIntensiveness.Text);
            int dx = Convert.ToInt32(textBoxDx.Text);
            int dy = Convert.ToInt32(textBoxDy.Text);
            int dz = Convert.ToInt32(textBoxDz.Text);
            Vector wind = new Vector(dx, dy, dz);

            StartRain(intensity, wind);

            int delay = Convert.ToInt32(textBoxDelay.Text);
            for (int i = 0; i < 100; i++)
            {
                UpdRain();
                rain.InitParticles(intensity);
                System.Threading.Thread.Sleep(delay);
            }

            while (!rain.IsEmpty())
            {
                UpdRain();
                System.Threading.Thread.Sleep(delay);
            }
            /*
            for (int i = 0; i < 50; i++) // while not empty?
            {
                UpdRain();
                System.Threading.Thread.Sleep(delay);
            }*/
        }
        

        private void StartRain(int intensity, Vector direction)
        {
            rain = new ParticleSystem(canvas.Width, canvas.Height, direction, intensity);
        }

        private void UpdRain()
        {
            canvas.Refresh();
            rain.ProcessSystem(g, new Pen(Color.LightBlue, 2));
            canvas.Update();
        }
        
        #endregion

        #region Туман
        private void buttonFog_Click(object sender, EventArgs e)
        {
            int far = Convert.ToInt32(textBoxfar.Text);
            int close = Convert.ToInt32(textBoxClose.Text);
            canvas.Image = Fog.AddFog(zbuf, far, close);
        }
        #endregion
        
        #region Повороты
        private void buttonLeft_Click(object sender, EventArgs e)
        {
            tetay -= 45;
            HandleSceneChange();
        }

        private void buttonRight_Click(object sender, EventArgs e)
        {
            tetay += 45;
            HandleSceneChange();
        }
        
        private void buttonUp_Click(object sender, EventArgs e)
        {
            tetax += 20;
            HandleSceneChange();
        }

        private void buttonDown_Click(object sender, EventArgs e)
        {
            tetax -= 20;
            HandleSceneChange();
        }

        #endregion

    }
}
