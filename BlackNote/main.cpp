#include "Registry.h"
#include "Entity.h"
#include "System.h"

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

	registry.AddComponent<Velocity>(3, 10);


	cout << endl;

	System system(registry);

	registry.Add();
	registry.AddComponent<Position>(4, 0, 0);
	registry.AddComponent<Dimension>(4, 100, 100);
	registry.AddComponent<Velocity>(4, 10);

	system.SystemAdd<MovementSystem>(4);

	system.UsingSystem<MovementSystem>(4, 1, 1);
	system.UsingSystem<MovementSystem>(4, 1, 0);
	system.UsingSystem<MovementSystem>(4, 0, 1);
	system.UsingSystem<MovementSystem>(4, -1, 1);
	system.UsingSystem<MovementSystem>(4, 1, -1);



	
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(1000, 700, "My_Game");
	SetTargetFPS(60);


	while (!WindowShouldClose()) {
		int x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

		if (x != 0 || y != 0) {
			system.UsingSystem<MovementSystem>(4, x, y);
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("ECS window is ready", 20, 20, 24, DARKGRAY);

		Position* pos = registry.TryGetComponent<Position>(4);
		Dimension* dim = registry.TryGetComponent<Dimension>(4);

		DrawRectangle(pos->x, pos->y, dim->width, dim->height, RED);


		EndDrawing();
	}

	CloseWindow();

	
}














