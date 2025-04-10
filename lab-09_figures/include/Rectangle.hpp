#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);
    ~Rectangle();

    void print() const;
    bool is_inside(int x, int y) const;
    void zoom(int factor);
    
private:
    int width_;
    int height_;
};
