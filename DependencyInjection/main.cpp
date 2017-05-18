#include <iostream>
#include <boost/make_unique.hpp>

enum class ShapeType { circle, triangle };

class Shape {
public:
	virtual void draw() = 0;
};

class Circle : public Shape {
public:
	void draw() override {
		std::cout << "Circle" << std::endl;
	}
};

class Triangle : public Shape {
public:
	void draw() override {
		std::cout << "Triangle" << std::endl;
	}
};

class Drawing {
public:
	void draw_shape(std::unique_ptr<Shape> shape) {
		m_shape = std::move(shape);
		m_shape->draw();
	}

private:
	std::unique_ptr<Shape> m_shape;
};

class IDrawing {
public:
	IDrawing() :
		m_drawing(boost::make_unique<Drawing>())
	{}

	void draw(ShapeType type) {
		switch (type) {
		case ShapeType::circle:
			m_drawing->draw_shape(boost::make_unique<Circle>());
			break;
		case ShapeType::triangle:
			m_drawing->draw_shape(std::make_unique<Triangle>());
			break;
		}
	}

private:
	std::unique_ptr<Drawing> m_drawing;
};

int main(int argc, char* argv[]) {
	IDrawing drawing;
	drawing.draw(ShapeType::circle);
	drawing.draw(ShapeType::triangle);

	system("pause");
	return EXIT_SUCCESS;
}