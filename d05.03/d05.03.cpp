#include <iostream>
#include <string>

class Figure {
protected:
    std::string name;
    int sides_count;
public:
    Figure(const std::string& name, int sides_count)
        : name(name), sides_count(sides_count) {
    }

    virtual void print_info() const {
        std::cout << name << ":\n";
        std::cout << (check() ? "Правильная\n" : "Неправильная\n");
        std::cout << "Количество сторон: " << sides_count << "\n";
    }

    virtual bool check() const {
        return sides_count == 0;
    }

    virtual ~Figure() {}
};

class Triangle : public Figure {
protected:
    int a, b, c;
    int A, B, C;
public:
    Triangle(int a, int b, int c, int A, int B, int C)
        : Figure("Треугольник", 3), a(a), b(b), c(c), A(A), B(B), C(C) {
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n\n";
    }

    bool check() const override {
        return A + B + C == 180;
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c, int A, int B)
        : Triangle(a, b, c, A, B, 90) {
        name = "Прямоугольный треугольник";
    }

    bool check() const override {
        return Triangle::check() && C == 90;
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int a, int b, int A, int B)
        : Triangle(a, b, a, A, B, A) {
        name = "Равнобедренный треугольник";
    }

    bool check() const override {
        return Triangle::check() && a == c && A == C;
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int side)
        : Triangle(side, side, side, 60, 60, 60) {
        name = "Равносторонний треугольник";
    }

    bool check() const override {
        return Triangle::check() &&
            a == b && b == c &&
            A == B && B == C && A == 60;
    }
};

class Quadrangle : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
        : Figure("Четырёхугольник", 4),
        a(a), b(b), c(c), d(d),
        A(A), B(B), C(C), D(D) {
    }

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b
            << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B
            << " C=" << C << " D=" << D << "\n\n";
    }

    bool check() const override {
        return A + B + C + D == 360;
    }
};

class Rectangle : public Quadrangle {
public:
    Rectangle(int a, int b)
        : Quadrangle(a, b, a, b, 90, 90, 90, 90) {
        name = "Прямоугольник";
    }

    bool check() const override {
        return Quadrangle::check() &&
            a == c && b == d &&
            A == 90 && B == 90 && C == 90 && D == 90;
    }
};

class Square : public Quadrangle {
public:
    Square(int side)
        : Quadrangle(side, side, side, side, 90, 90, 90, 90) {
        name = "Квадрат";
    }

    bool check() const override {
        return Quadrangle::check() &&
            a == b && b == c && c == d &&
            A == 90 && B == 90 && C == 90 && D == 90;
    }
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B)
        : Quadrangle(a, b, a, b, A, B, A, B) {
        name = "Параллелограмм";
    }

    bool check() const override {
        return Quadrangle::check() &&
            a == c && b == d &&
            A == C && B == D;
    }
};

class Rhombus : public Quadrangle {
public:
    Rhombus(int side, int A, int B)
        : Quadrangle(side, side, side, side, A, B, A, B) {
        name = "Ромб";
    }

    bool check() const override {
        return Quadrangle::check() &&
            a == b && b == c && c == d &&
            A == C && B == D;
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    Figure fig("Фигура", 0);
    Triangle triangle(10, 20, 30, 50, 60, 70);
    RightTriangle wrongRight(10, 20, 30, 50, 60);
    RightTriangle correctRight(10, 20, 30, 50, 40);
    IsoscelesTriangle isos(10, 20, 50, 60);
    EquilateralTriangle equil(30);

    Quadrangle quad(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rect(10, 20);
    Square square(20);
    Parallelogram para(20, 30, 30, 40);
    Rhombus rhomb(30, 30, 40);

    Figure* figures[] = {
        &fig, &triangle, &wrongRight, &correctRight, &isos, &equil,
        &quad, &rect, &square, &para, &rhomb
    };

    for (Figure* f : figures) {
        f->print_info();
    }

    return 0;
}
