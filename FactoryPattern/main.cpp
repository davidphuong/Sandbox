#include <iostream>
#include <string>
#include <map>
#include <memory>

class AnimalInterface {
public:
	virtual int GetNumberOfLegs() const = 0;
	virtual void Speak() = 0;
};

class Cat : public AnimalInterface {
public:
	int GetNumberOfLegs() const override {
		return 4;
	}

	void Speak() override {
		std::cout << "Meow" << std::endl;
	}

	static std::shared_ptr<AnimalInterface> Create() { return std::make_shared<Cat>(); }
};

class Dog : public AnimalInterface {
public:
	int GetNumberOfLegs() const override {
		return 4;
	}

	void Speak() override {
		std::cout << "Woof" << std::endl;
	}

	static std::shared_ptr<AnimalInterface> Create() { return std::make_shared<Dog>(); }
};

class Spider : public AnimalInterface {
public:
	int GetNumberOfLegs() const override {
		return 8;
	}

	void Speak() override {
		std::cout << std::endl;
	}

	static std::shared_ptr<AnimalInterface> Create() { return std::make_shared<Spider>(); }
};

class Horse : public AnimalInterface {
public:
	int GetNumberOfLegs() const override {
		return 4;
	}

	void Speak() override {
		std::cout << "A horse is a horse, of course, of course." << std::endl;
	}

	static std::shared_ptr<AnimalInterface> Create() { return std::make_shared<Horse>(); }
};

class AnimalFactory {
public:
	AnimalFactory() {
		Register("Horse", &Horse::Create);
		Register("Cat", &Cat::Create);
		Register("Dog", &Dog::Create);
		Register("Spider", &Spider::Create);
	}

	void Register(const std::string& animal_name, std::shared_ptr<AnimalInterface>(*CreateAnimalFn)(void)) {
		factory_map_[animal_name] = CreateAnimalFn;
	}

	std::shared_ptr<AnimalInterface> CreateAnimal(const std::string &animal_name) {
		auto it = factory_map_.find(animal_name);
		if (it == factory_map_.end()) {
			return nullptr;
		}
		return it->second();
	}

private:
	std::map<std::string, std::shared_ptr<AnimalInterface>(*)(void)> factory_map_;
};

int main(int argc, char* argv[]) {
	AnimalFactory factory;
	auto dog = factory.CreateAnimal("Dog");
	dog->Speak();

	auto horse = factory.CreateAnimal("Horse");
	horse->Speak();


	system("pause");
	return EXIT_SUCCESS;
}