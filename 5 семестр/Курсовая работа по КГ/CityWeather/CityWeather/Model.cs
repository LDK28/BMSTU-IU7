using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using System.IO;

namespace CityWeather
{
    class Model
    {
        List<Point3D> vertices;
        public List<Polygon> polygons;
        private List<int[]> indexes;
        private Color basicColor = Color.Black;
        
        public Model(Color color)
        {
            basicColor = color;
            vertices = new List<Point3D>();
            polygons = new List<Polygon>();
            indexes = new List<int[]>();
        }
        
        public void AddVertex(Point3D vertex)
        {
            vertices.Add(vertex);
        }

        public void AddVertex(int x, int y, int z)
        {
            vertices.Add(new Point3D(x, y, z));
        }

        /// <summary>
        /// Создание многоугольника используя индексы вершин модели
        /// </summary>
        /// <param name="indexes">Индексы вершин многоугольника из списка всех вершин модели</param>
        public void CreatePolygon(params int[] indexes)
        {
            this.indexes.Add(indexes);

            List<Point3D> verticesPolygon = new List<Point3D>();
            foreach (int i in indexes)
            {
                verticesPolygon.Add(vertices[i]);
            }
            polygons.Add(new Polygon(verticesPolygon, basicColor));
        }
        public void CreatePolygonSpecial(params int[] indexes)
        {
            this.indexes.Add(indexes);

            List<Point3D> verticesPolygon = new List<Point3D>();
            foreach (int i in indexes)
            {
                verticesPolygon.Add(vertices[i]);
            }
            polygons.Add(new Polygon(verticesPolygon, basicColor, true));
        }

        /// <summary>
        /// Повернуть модель вокруг осей x, y, z
        /// </summary>
        /// <param name="tetax">Угол поворота вокруг x</param>
        /// <param name="tetay">Угол поворота вокруг y</param>
        /// <param name="tetaz">Угол поворота вокруг z</param>
        public void TransformModel(double tetax, double tetay, double tetaz)
        {
            tetax = tetax * Math.PI / 180;
            tetay = tetay * Math.PI / 180;
            tetaz = tetaz * Math.PI / 180;
            double cosTetX = Math.Cos(tetax), sinTetX = Math.Sin(tetax);
            double cosTetY = Math.Cos(tetay), sinTetY = Math.Sin(tetay);
            double cosTetZ = Math.Cos(tetaz), sinTetZ = Math.Sin(tetaz);
            foreach (Point3D v in vertices)
            {
                Transformation.Transform(ref v.x, ref v.y, ref v.z, cosTetX, sinTetX, cosTetY, sinTetY, cosTetZ, sinTetZ);
            }
        }
        
        /// <summary>
        /// Получить модель, повернутую на углы teta
        /// </summary>
        public Model GetTurnedModel(double tetax, double tetay, double tetaz)
        {
            Model m = new Model(basicColor);
            
            foreach (Point3D p in vertices)
            {
                m.AddVertex(p.x, p.y, p.z);
            }

            m.TransformModel(tetax, tetay, tetaz);

            for(int i = 0; i < indexes.Count; i++)
            {
                if (polygons[i].ignore)
                    m.CreatePolygonSpecial(indexes[i]);
                else
                    m.CreatePolygon(indexes[i]);
            }

            return m;
        }

        public static Model LoadModel(string path)
        {
            if (!File.Exists(path))
                return null;

            Model m = new Model(Color.Red);
            foreach (string line in File.ReadLines(path))
            {
                if (line == "")
                    continue;
                if (line[0] == 'v' && line[1] == ' ')
                {
                    var el = line.Split(' ');
                    
                    if (el.Length == 5)
                        m.AddVertex(new Point3D((int)Convert.ToDouble(el[2].Replace('.', ',')), (int)Convert.ToDouble(el[3].Replace('.', ',')), (int)Convert.ToDouble(el[4].Replace('.', ','))));
                    else
                        m.AddVertex(new Point3D((int)Convert.ToDouble(el[1].Replace('.', ',')), (int)Convert.ToDouble(el[2].Replace('.', ',')), (int)Convert.ToDouble(el[3].Replace('.', ','))));
                }
                else if (line[0] == 'f')
                {
                    var el = line.Split(' ');

                    List<int> ind = new List<int>();
                    for(int i = 1; i < el.Length - 1; i++)
                    {
                        if (el[i] != "")
                            ind.Add(Convert.ToInt32((el[i].Split('/'))[0].Replace('.', ',')));
                    }
                    m.CreatePolygon(ind.ToArray());
                }
            }
            return m;
        }
    }
        

    class Polygon
    {
        List<Point3D> v;

        Color basicColor = Color.Gray;
        public List<Point3D> pointsInside;
        Vector normal;
        public bool ignore = false; // игнорируем ли от лица солнца

        #region Создание Polygon
        
        public Polygon(List<Point3D> vertex, bool special = false)
        {
            pointsInside = new List<Point3D>();
            v = vertex;
            normal = GetNormal();
            this.ignore = special;
        }

        public Polygon(Color color, bool special = false)
        {
            basicColor = color;
            pointsInside = new List<Point3D>();
            v = new List<Point3D>();
            normal = GetNormal();
            this.ignore = special;
        }

        public Polygon(List<Point3D> vertex, Color color, bool special = false)
        {
            pointsInside = new List<Point3D>();
            v = vertex;
            basicColor = color;
            normal = GetNormal();
            this.ignore = special;
        }
        #endregion

        #region Нахождение внутренних точек

        /// <summary>
        /// Поиск точек, лежащих внутри многоугольника
        /// </summary>
        /// <param name="maxX">Максимальная х координата</param>
        /// <param name="maxY">Максимальная y координата</param>
        public void CalculatePointsInside(int maxX, int maxY)
        {
            pointsInside = new List<Point3D>();

            if (v.Count() > 4)
            {
                ; // TODO: найти треугольники
                //CalculatePointsInsideTriangle(width, height);
            }
            else if (v.Count() == 4)
            {
                List<Point3D> triangle = new List<Point3D>();
                triangle.Add(v[0]);
                triangle.Add(v[2]);
                triangle.Add(v[1]);
                CalculatePointsInsideTriangle(triangle, maxX, maxY);
                triangle = new List<Point3D>();
                triangle.Add(v[0]);
                triangle.Add(v[2]);
                triangle.Add(v[3]);
                CalculatePointsInsideTriangle(triangle, maxX, maxY);
            }
            else if (v.Count() == 3)
            {
                CalculatePointsInsideTriangle(v, maxX, maxY);
            }
        }

        /// <summary>
        /// Поиск точек, лежащих внутри треугольника
        /// </summary>
        /// <param name="firstXPossible">Минимальная x координата</param>
        /// <param name="firstYPossible">Минимальная y координата</param>
        /// <param name="lastXPossible">Максимальная x координата</param>
        /// <param name="lastYPossible">Максимальная y координата</param>
        /// <param name="v">Вершины треугольника</param>
        private void CalculatePointsInsideTriangle(List<Point3D> v, int lastXPossible, int lastYPossible, int firstXPossible = 0, int firstYPossible = 0)
        {
            int yMax, yMin;
            int[] x = new int[3], y = new int[3];
            
            for (int i = 0; i < 3; ++i)
            {
                x[i] = v[i].x;
                y[i] = v[i].y;
            }
            
            yMax = y.Max();
            yMin = y.Min();

            yMin = (yMin < firstYPossible) ? firstYPossible : yMin;
            yMax = (yMax < lastYPossible) ? yMax : lastYPossible;

            int x1 = 0, x2 = 0;
            double z1 = 0, z2 = 0;
            
            for (int yDot = yMin; yDot <= yMax; yDot++)
            {
                int fFirst = 1;
                for (int n = 0; n < 3; ++n)
                {
                    int n1 = (n == 2) ? 0 : n + 1;
                    
                    if (yDot >= Math.Max(y[n], y[n1]) || yDot < Math.Min(y[n], y[n1])) // || y[n] == y[n1]  
                        continue; // точка вне
                    
                    double m = (double)(y[n] - yDot) / (y[n] - y[n1]);
                    if (fFirst == 0)
                    {
                        x2 = x[n] + (int)(m * (x[n1] - x[n]));
                        z2 = v[n].z + m * (v[n1].z - v[n].z);
                    }
                    else
                    {
                        x1 = x[n] + (int)(m * (x[n1] - x[n]));
                        z1 = v[n].z + m * (v[n1].z - v[n].z);
                    }
                    fFirst = 0;
                }

                if (x2 < x1)
                {
                    Swap(ref x1, ref x2);
                    Swap(ref z1, ref z2);
                }

                int xStart = (x1 < firstXPossible) ? firstXPossible : x1;
                int xEnd = (x2 < lastXPossible)? x2 : lastXPossible;
                for (int xDot = xStart; xDot < xEnd; xDot++)
                {
                    double m = (double)(x1 - xDot) / (x1 - x2);
                    double zDot = z1 + m * (z2 - z1);

                    pointsInside.Add(new Point3D(xDot, yDot, (int)zDot));
                }
            }
        }
        #endregion

        /// <summary>
        /// Получение вектора нормали к многоугольнику
        /// </summary>
        /// <returns></returns>
        public Vector GetNormal()
        {
            int len = v.Count();
            int a = 0, b = 0, c = 0;
            for (int i = 0; i < len - 1; i++)
            {
                a += (v[i].y - v[i + 1].y) * (v[i].z + v[i + 1].z);
                b += (v[i].x - v[i + 1].x) * (v[i].z + v[i + 1].z);
                c += (v[i].x - v[i + 1].x) * (v[i].y + v[i + 1].y);
            }
            a += (v[len - 1].y - v[0].y) * (v[len - 1].z + v[0].z);
            b += (v[len - 1].x - v[0].x) * (v[len - 1].z + v[0].z);
            c += (v[len - 1].x - v[0].x) * (v[len - 1].y + v[0].y);
            
            return new Vector(a, b, c);
        }
        
        /// <summary>
        /// Нахождение цвета многоугольника с наложением затемнения в зависимости от его расположения к источнику света
        /// </summary>
        /// <param name="light">Источник света</param>
        /// <returns></returns>
        public Color GetColor(LightSource light)
        {
            double cos = Vector.ScalarMultiplication(light.direction, normal) / 
                (light.direction.length * normal.length);
            
            if (cos <= 0)
                return Colors.Mix(basicColor, Color.Black, 0.2f);

            return Colors.Mix(basicColor, Color.Black, (float)cos);
            
        }

        static void Swap<T>(ref T a, ref T b)
        {
            T temp = a;
            a = b;
            b = temp;
        }
    }

    class Point3D
    {
        public int x, y, z;
        public Point3D(int x, int y, int z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    class Vector
    {
        public double x, y, z;
        public double length;

        public Vector(int x, int y, int z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            FindLength();
        }
        public Vector(double x, double y, double z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            FindLength();
        }

        public Vector(Point3D a, Point3D b)
        {
            x = b.x - a.x;
            y = b.y - a.y;
            z = b.z - b.z;
            FindLength();
        }
        
        /// <summary>
        /// Нахождение длины вектора
        /// </summary>
        private void FindLength()
        {
            length = Math.Sqrt(x * x + y * y + z * z);
        }

        /// <summary>
        /// Получение длины вектора
        /// </summary>
        /// <returns></returns>
        public double GetLength()
        {
            return length;
        }

        public void RotateVectorX(double tetax)
        {
            tetax = tetax * Math.PI / 180;
            double buf = y;
            y = Math.Cos(tetax) * (y) - Math.Sin(tetax) * z;
            z = Math.Cos(tetax) * z + Math.Sin(tetax) * (buf);
        }

        /// <summary>
        /// Вращение вектора относительно оси y
        /// </summary>
        /// <param name="tetay">Угол поворота</param>
        public void RotateVectorY(double tetay)
        {
            tetay = tetay * Math.PI / 180;
            double buf = x;
            x = Math.Cos(tetay) * (x) - Math.Sin(tetay) * z;
            z = Math.Cos(tetay) * z + Math.Sin(tetay) * (buf);
        }
        
        /// <summary>
        /// Векторное умножение двух векторов
        /// </summary>
        /// <returns></returns>
        public static Vector VectorMultiplication(Vector a, Vector b)
        {
            Vector res = new Vector(0, 0, 0);
            res.x = a.y * b.z - a.z * b.y;
            res.y = a.z * b.x - a.x * b.z;
            res.z = a.x * b.y - a.y * b.x;
            res.FindLength();
            return res;
        }

        /// <summary>
        /// Скалярное умножение двух векторов
        /// </summary>
        public static double ScalarMultiplication(Vector a, Vector b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }
        
    }
    
}
