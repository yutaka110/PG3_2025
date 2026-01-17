#include <iostream>
#include <vector>
#include <memory>

// ---------------------------------------------
// Abstract class
// ---------------------------------------------
class IShape {
public:
	virtual ~IShape() = default;

	// Return area
	virtual double Size() const = 0;

	// Print area
	virtual void Draw() const = 0;
};

// ---------------------------------------------
// Circle
// ---------------------------------------------
class Circle : public IShape {
public:
	explicit Circle(double r) : r_(r) {}

	double Size() const override {
		const double pi = 3.141592653589793;
		return pi * r_ * r_;
	}

	void Draw() const override {
		std::cout << "Circle area = " << Size() << "\n";
	}

private:
	double r_;
};

// ---------------------------------------------
// Rectangle
// ---------------------------------------------
class Rectangle : public IShape {
public:
	Rectangle(double w, double h) : w_(w), h_(h) {}

	double Size() const override {
		return w_ * h_;
	}

	void Draw() const override {
		std::cout << "Rectangle area = " << Size() << "\n";
	}

private:
	double w_;
	double h_;
};

int main() {
	std::vector<std::unique_ptr<IShape>> shapes;
	shapes.push_back(std::make_unique<Circle>(3.0));
	shapes.push_back(std::make_unique<Rectangle>(4.0, 5.0));

	for (const auto& s : shapes) {
		s->Draw();
	}

	return 0;
}
