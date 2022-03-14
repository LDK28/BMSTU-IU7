using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace CityWeather
{
    class Drop
    {
        int x, y, z;
        
        public Drop(int x, int y, int z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public void Update(int dx, int dy, int dz)
        {
            x += dx;
            y += dy;
            z += dz;
        }

        public void Draw(Graphics g, Pen pen, int dx, int dy)
        {
            g.DrawLine(pen, x, y, x + dx, y + dy);
        }

        public int GetDepth()
        {
            return z;
        }

        public bool IsVisible(int maxZ)
        {
            if (z > maxZ)
                return true;
            return false;
        }

        public bool IsNextVisible(int maxZ, int dz)
        {
            if ((z + dz) > maxZ)
                return true;
            return false;
        }

        public Point GetPoint()
        {
            return new Point(x, y);
        }

        public Point GetNextPoint(int dx, int dy)
        {
            return new Point(x + dx, y + dy);
        }

        public static bool IsBelow(Drop d)
        {
            if (d.y > 1000)
                return true;
            return false;
        }

    }

    class ParticleSystem
    {
        List<Drop> system;
        Vector direction;
        int xMax, yMax;

        static Random rnd = new Random();

        public ParticleSystem(int width, int height, Vector dir, int intensity)
        {
            system = new List<Drop>();
            direction = dir;
            xMax = width;
            yMax = height;
            InitParticles(intensity);
        }

        public void InitParticles(int intensity)
        {
            for (int i = 0; i < intensity; i++)
                system.Add(new Drop(rnd.Next(-400, xMax + 400), 0, 700)); // не 700!
        }

        private void UpdateParticles()
        {
            foreach (Drop drop in system)
            {
                drop.Update((int)direction.x, (int)direction.y, (int)direction.z);
            }
            system.RemoveAll(Drop.IsBelow);
        }

        public void DrawParticles(Graphics g, Pen pen)
        {
            foreach (Drop drop in system)
            {
                drop.Draw(g, pen, (int)direction.x, (int)direction.y);
            }
        }
        
        public void ProcessSystem(Graphics g, Pen pen)
        {
            DrawParticles(g, pen);
            UpdateParticles();
        }
        
        public bool IsEmpty() // Эффективно ли?
        {
            return (system.Count == 0);
        }
    }

}
