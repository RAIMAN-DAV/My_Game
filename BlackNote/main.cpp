#include "Registry.h"
#include "Entity.h"

int main() {
	Registry registry;

	Entity blok_2(registry);
	blok_2.Position(100, 60);
	blok_2.Position(60, 150);
	blok_2.Dimension(10, 20);

	Entity blok_3(registry);
	blok_3.Dimension(10, 40);

	registry.Add();
	registry.AddComponent<Position>(3, 10, 20);
	registry.AddComponent<Position>(3, 50, 24);
	registry.AddComponent<Dimension>(3, 4, 30);
	registry.AddComponent<Dimension>(3, 6, 50);

	Position* comp = registry.TryGetComponent<Position>(4);


}














