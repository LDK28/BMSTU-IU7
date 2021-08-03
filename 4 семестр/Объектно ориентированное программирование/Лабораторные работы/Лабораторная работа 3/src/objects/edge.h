#ifndef EDGE_H
#define EDGE_H


class Edge
{
private:
    int first, second;
public:
    Edge() = default;
    Edge(int fst, int scd) {first = fst; second = scd; };

    int get_first() const {return first; };
    int get_second() const {return second; };
};

#endif // EDGE_H
