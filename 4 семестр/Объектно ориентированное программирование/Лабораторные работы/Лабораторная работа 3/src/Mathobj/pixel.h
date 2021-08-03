#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
public:
    Pixel() = default;
    Pixel(int _x, int _y) { x = _x; y = _y;};

    int get_x() const {return x;};
    int get_y() const {return y;};

    void set_x(int _x) {x = _x; };
    void set_y(int _y) {y = _y; };
private:
    int x, y;
};

#endif // PIXEL_H
