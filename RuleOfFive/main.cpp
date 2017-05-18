#include <iostream>

class Resource {
private:
	int x{ 0 };
};

class Foo
{
public:
	Resource* p{ nullptr }; // Raw pointer used as a handle to a dynamically-allocated memory block
	Foo()
		: p(new Resource) // Allocate
	{
		std::cout << "Constructor called" << std::endl;
	}

	~Foo()
	{
		std::cout << "Destructor called" << std::endl;
		delete p; // Deallocate
		p = nullptr;
	}

	Foo(const Foo& other) // Copy constructor
	{
		std::cout << "Copy constructor called" << std::endl;
		if (p)
		{
			delete p;
		}

		p = new Resource{ *(other.p) };
	}

	Foo(Foo&& other) // Move constructor
	{
		std::cout << "Move constructor called" << std::endl;
		if (p) {
			delete p;
		}

		p = other.p;
		other.p = nullptr;
	}

	Foo& operator=(const Foo& other) // Copy assignment
	{
		std::cout << "Copy assignment called" << std::endl;
		if (&other != this)
		{
			if (p)
			{
				delete p;
			}

			p = new Resource{ *(other.p) };
		}
		return *this;
	}

	Foo& operator=(Foo&& other) // Move assignment
	{
		std::cout << "Move assignment called" << std::endl;
		if (&other != this)
		{
			if (p)
			{
				delete p;
			}
			p = other.p;
			other.p = nullptr;
		}
		return *this;
	}
};

void Function(const Foo foo) {
	return;
}

int main()
{
	Foo foo;
	Function(foo);

	system("pause");
	return 0;
}