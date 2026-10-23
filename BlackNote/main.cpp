#include "Registry.h"
#include "Entity.h"
#include "System.h"

int main() {
	Registry registry;
	System system(registry);

	EntityID& obj = registry.Add();
	registry.AddComponent<Position>(obj, 0, 0);
	registry.AddComponent<Dimension>(obj, 50, 50);
	registry.AddComponent<Velocity>(obj, 10);
	system.SystemAdd<MovementSystem>(obj);

	system.UsingSystem<MovementSystem>(obj, 1, 1);
	system.UsingSystem<MovementSystem>(obj, 1, 0);
	system.UsingSystem<MovementSystem>(obj, 0, 1);
	system.UsingSystem<MovementSystem>(obj, -1, 1);
	system.UsingSystem<MovementSystem>(obj, 1, -1);
	


	Entity Stive(registry);
	Stive.Component<Position>(50, 50);
	Stive.Component<Dimension>(50, 50);
	Stive.Component<Velocity>(10);
	Stive.AddSystem<MovementSystem>();


	Stive.Destroy();

	Entity Bob(registry);
	Stive.Component<Position>(100, 100);
	Stive.Component<Dimension>(50, 50);
	Stive.Component<Velocity>(10);
	Bob.AddSystem<MovementSystem>();







	SetTraceLogLevel(LOG_WARNING);
	InitWindow(1000, 700, "My_Game");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		int move_x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int move_y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

		if (move_x != 0 || move_y != 0) {
			system.UsingSystem<MovementSystem>(obj, move_x, move_y);
		}
		Stive.UseSystem<MovementSystem>();
		Bob.UseSystem<MovementSystem>();



		BeginDrawing();
		ClearBackground(RAYWHITE);


		Position* pos = registry.TryGetComponent<Position>(obj);
		Dimension* dim = registry.TryGetComponent<Dimension>(obj);

		if (pos != nullptr && dim != nullptr) {
			DrawRectangle(pos->x, pos->y, dim->width, dim->height, RED);
		}

		Stive.Draw(BLUE);


		EndDrawing();
	}

	CloseWindow();
}
