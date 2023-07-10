#include <iostream>

struct Gun {
  Gun() {
    std::cout << "Gun costructor" << std::endl;
  }
  void shoot() {
    std::cout << "bang" << std::endl;
  }
};

struct LazerBlaster : Gun {
  LazerBlaster() {
    std::cout << "LazerBlaster constructor" << std::endl;
  }
  void shoot() {
    std::cout << "bzch" << std::endl;
  }
};

struct SubmachineGun : Gun {
  SubmachineGun() {
    std::cout << "SubmachineGun constructor" << std::endl;
  }  
  void shoot() {
    std::cout << "bang bang bang" << std::endl;
  }
};

struct SubmachineLazerBlaster : SubmachineGun,
                                LazerBlaster {
  SubmachineLazerBlaster() {
    std::cout << "SubmachineLazerBlaster constructor" << std::endl;
  }
};

struct PoliceGun : SubmachineGun,
		               LazerBlaster {
  PoliceGun() {
    std::cout << "PoliceGun constructor" << std::endl;
  }
  void shoot() {
    std::cout << "u bad - BANG!!" << std::endl;
  }
};

void simple_way() {
  Gun simple_gun;
  std::cout << std::endl;
  LazerBlaster blaster;
  std::cout << std::endl;
  SubmachineGun submachine_gun;
  std::cout << std::endl;
  
  SubmachineLazerBlaster gun;
  gun.LazerBlaster::shoot(); // 1 можно обратиться к кому угодно!

  PoliceGun police_gun;
  police_gun.shoot(); // 2 а можно просто переопределить метод!
  std::cout << std::endl;
}
  // Но это будет очень неэффективно по памяти, ведь каждый объект будет
  // хранить всю цепочку базовых классов. Сейчас я проиллюстрирую это
  // через более понятный аналог этого кода на Си-шке
struct super_base_t {
  int super_base_data;
};
struct base_1_t {
  super_base_t super_base;
  int base_1_data;
};
struct base_2_t {
  super_base_t super_base;
  int base_2_data;
};
struct x {
  base_1_t base_1;
  base_2_t base_2;
  int x_data;
};
// Как это хранится в памяти при создании x:
// super_base_data
// base_1_data
// super_base_data - ДУБЛИРОВАНИЕ САМОГО БАЗОВОГО КЛАССА
// base_2_data
// x

// Решение в виртуальном наследовании!
struct Animal {
  Animal() {
    std::cout << "Animal costructor" << std::endl;
  }
};

struct Rat : virtual Animal {
  // за счёт virtual хранятся только указатели на войд и короче оно работает
  int ratData;
  Rat() {
    std::cout << "Rat constructor" << std::endl;
  }
};

struct Bird : virtual Animal {
  int birdData;
  Bird() {
    std::cout << "Bird constructor" << std::endl;
  }
};

struct Bat : Rat,
	           Bird {
  int batData;
  Bat() {
    std::cout << "Bat constructor" << std::endl;
  }
};

void virtual_way() {
  Animal Animal;
  std::cout << std::endl;
  Rat rat;
  std::cout << std::endl;
  Bird Bird;
  std::cout << std::endl;
  
  Bat bat;
  bat.ratData = 3;
}

int main() {
  simple_way();
  virtual_way();
}
