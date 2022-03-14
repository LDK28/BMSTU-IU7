using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace CityWeather
{
    class LightSource
    {
        public Color color;
        public double tetax = 90, tetay = 0, tetaz = 0;
        public Vector direction;


        public LightSource(Color color, double tetay, Vector direction)
        {
            this.direction = direction;
            this.color = color;
            this.tetay = tetay;
        }

        
    }

}
