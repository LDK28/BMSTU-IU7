using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace CityWeather
{
    static class Colors
    {
        /// <summary>
        /// Смешивание цветов в разных пропорциях
        /// </summary>
        /// <param name="aPers">Коэффициент влияния цвета a</param>
        /// <returns></returns>
        public static Color Mix(Color a, Color b, float aPers)
        {
            aPers = Math.Min(aPers, 1);
            float bPers = 1 - aPers;
            int red = (int)(a.R * aPers + b.R * bPers);
            int green = (int)(a.G * aPers + b.G * bPers);
            int blue = (int)(a.B * aPers + b.B * bPers);

            return Color.FromArgb(red, green, blue);
        }
        
    }
}
