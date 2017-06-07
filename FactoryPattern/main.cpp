#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <functional>

class AnimalInterface {
public:
	virtual int GetNumberOfLegs() const = 0;
	virtual void Speak() = 0;
	virtual void GetAge() = 0; // Not the best example
};

class Cat : public AnimalInterface {
public:
	Cat(size_t age) :
		age_{ age }
	{
	}

	int GetNumberOfLegs() const override {
		return 4;
	}

	void Speak() override {
		std::cout << "Meow" << std::endl;
	}

	void GetAge() override {
		std::cout << age_ << std::endl;
	}

	static std::shared_ptr<AnimalInterface> Create(size_t age) { return std::make_shared<Cat>(age); }

private:
	size_t age_;
};

class Dog : public AnimalInterface {
public:
	Dog(size_t age) :
		age_{ age }
	{
	}

	int GetNumberOfLegs() const override {
		return 4;
	}

	void Speak() override {
		std::cout << "Woof" << std::endl;
	}

	void GetAge() override {
		std::cout << age_ << std::endl;
	}

	static std::shared_ptr<AnimalInterface> Create(size_t age) { return std::make_shared<Dog>(age); }

private:
	size_t age_;
};

class Spider : public AnimalInterface {
public:
	Spider(size_t age) :
		age_{ age }
	{
	}

	int GetNumberOfLegs() const override {
		return 8;
	}

	void Speak() override {
		std::cout << std::endl;
	}

	void GetAge() override {
		std::cout << age_ << std::endl;
	}

	static std::shared_ptr<AnimalInterface> Create(size_t age) { return std::make_shared<Spider>(age); }

private:
	size_t age_;
};

class Horse : public AnimalInterface {
public:
	Horse(size_t age) :
		age_{ age }
	{
	}

	int GetNumberOfLegs() const override {
		return 4;
	}

	void Speak() override {
		std::cout << "A horse is a horse, of course, of course." << std::endl;
	}

	void GetAge() override {
		std::cout << age_ << std::endl;
	}

	static std::shared_ptr<AnimalInterface> Create(size_t age) { return std::make_shared<Horse>(age); }

private:
	size_t age_;
};

class AnimalFactory {
public:
	AnimalFactory() {
		Register("Horse", std::bind(&Horse::Create, 1));
		Register("Cat", std::bind(&Cat::Create, 2));
		Register("Dog", std::bind(&Dog::Create, 3));
		Register("Spider", std::bind(&Spider::Create, 4));
	}

	void Register(const std::string& animal_name, const std::function<std::shared_ptr<AnimalInterface>()>& CreateAnimalFn) {
		factory_map_[animal_name] = CreateAnimalFn;
	}

	std::shared_ptr<AnimalInterface> CreateAnimal(const std::string &animal_name) {
		auto it = factory_map_.find(animal_name);
		if (it == factory_map_.end()) {
			return nullptr;
		}
		return (it->second)();
	}

private:
	std::map<std::string, std::function<std::shared_ptr<AnimalInterface>()>> factory_map_;
};

int main(int argc, char* argv[]) {
	AnimalFactory factory;
	auto dog = factory.CreateAnimal("Dog");
	dog->Speak();
	dog->GetAge();

	auto horse = factory.CreateAnimal("Horse");
	horse->Speak();
	horse->GetAge();

	system("pause");
	return EXIT_SUCCESS;
}