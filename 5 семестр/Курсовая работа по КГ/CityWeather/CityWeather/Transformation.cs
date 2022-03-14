using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CityWeather
{
    static class Transformation
    {
        static int centerX = 0;
        static int centerY = 0;
        
        public static void SetSize(int w, int h)
        {
            centerX = (int)(w/2);
            centerY = (int)(h/2);
        }
                
        static void RotateX(ref double y, ref double z, double tetax)
        {
            tetax = tetax * Math.PI / 180;
            double buf = y;
            y = centerY + Math.Cos(tetax) * (y - centerY) - Math.Sin(tetax) * z;
            z = Math.Cos(tetax) * z + Math.Sin(tetax) * (buf - centerY);
        }

        static void RotateX(ref double y, ref double z, double cosTetX, double sinTetX)
        {
            double buf = y;
            y = centerY + cosTetX * (y - centerY) - sinTetX * z;
            z = cosTetX * z + sinTetX * (buf - centerY);
        }

        static void RotateY(ref double x, ref double z, double tetay)
        {
            tetay = tetay * Math.PI / 180;
            double buf = x;
            x = centerX + Math.Cos(tetay) * (x - centerX) - Math.Sin(tetay) * z;
            z = Math.Cos(tetay) * z + Math.Sin(tetay) * (buf - centerX);
        }

        static void RotateY(ref double x, ref double z, double cosTetY, double sinTetY)
        {
            double buf = x;
            x = centerX + cosTetY * (x - centerX) - sinTetY * z;
            z = cosTetY * z + sinTetY * (buf - centerX);
        }

        static void RotateZ(ref double x, ref double y, double tetaz)
        {
            tetaz = tetaz * Math.PI / 180;
            double buf = x;
            x = centerX + Math.Cos(tetaz) * (x - centerX) - Math.Sin(tetaz) * (y - centerY);
            y = centerY + Math.Cos(tetaz) * (y - centerY) + Math.Sin(tetaz) * (buf - centerX);
        }

        static void RotateZ(ref double x, ref double y, double cosTetZ, double sinTetZ)
        {
            double buf = x;
            x = centerX + cosTetZ * (x - centerX) - sinTetZ * (y - centerY);
            y = centerY + cosTetZ * (y - centerY) + sinTetZ * (buf - centerX);
        }

        /// <summary>
        /// Поворачивает точку относительно осей x, y, z
        /// </summary>
        /// <param name="x">Координата x точки</param>
        /// <param name="y">Координата y точки</param>
        /// <param name="z">Координата z точки</param>
        /// <param name="tetax">Угол поворота вокруг оси x</param>
        /// <param name="tetay">Угол поворота вокруг оси y</param>
        /// <param name="tetaz">Угол поворота вокруг оси z</param>
        public static void Transform(ref int x, ref int y, ref int z, double tetax, double tetay, double tetaz)
        {
            double x_tmp = x;
            double y_tmp = y;
            double z_tmp = z;
            RotateX(ref y_tmp, ref z_tmp, tetax);
            RotateY(ref x_tmp, ref z_tmp, tetay);
            RotateZ(ref x_tmp, ref y_tmp, tetaz);

            x = (int)x_tmp;
            y = (int)y_tmp;
            z = (int)z_tmp;
        }

        public static void Transform(ref int x, ref int y, ref int z, double cosTetX, double sinTetX, double cosTetY, double sinTetY, double cosTetZ, double sinTetZ)
        {
            double x_tmp = x;
            double y_tmp = y;
            double z_tmp = z;
            RotateX(ref y_tmp, ref z_tmp, cosTetX, sinTetX);
            RotateY(ref x_tmp, ref z_tmp, cosTetY, sinTetY);
            RotateZ(ref x_tmp, ref y_tmp, cosTetZ, sinTetZ);

            x = (int)x_tmp;
            y = (int)y_tmp;
            z = (int)z_tmp;
        }

        public static Point3D Transform(int x, int y, int z, double tetax, double tetay, double tetaz)
        {
            double x_tmp = x;
            double y_tmp = y;
            double z_tmp = z;
            RotateX(ref y_tmp, ref z_tmp, tetax);
            RotateY(ref x_tmp, ref z_tmp, tetay);
            RotateZ(ref x_tmp, ref y_tmp, tetaz);

            return new Point3D((int)x_tmp, (int)y_tmp, (int)z_tmp);
        }
        
        public static Point3D Transform(Point3D p, double tetax, double tetay, double tetaz)
        {
            double x_tmp = p.x;
            double y_tmp = p.y;
            double z_tmp = p.z;
            RotateX(ref y_tmp, ref z_tmp, tetax);
            RotateY(ref x_tmp, ref z_tmp, tetay);
            RotateZ(ref x_tmp, ref y_tmp, tetaz);

            return new Point3D((int)x_tmp, (int)y_tmp, (int)z_tmp);
        }
        
    }
}
