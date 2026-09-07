#include "Registry.h"
#include "Entity.h"

int main() {
	Registry registry;

	registry.Add();
	registry.AddPosition(1, 10, 20);  //ID и координаты x,y
	registry.AddPosition(1, 150, 240);
	registry.AddPosition(2, 140, 220);  //Не срабатывает, так как существа с таким ID нет.

	Entity blok_1(registry);
	registry.AddPosition(2, 140, 220);

	Entity blok_2(registry);
	blok_2.Position(100, 60);


}














