#include "Registry.h"
#include "Entity.h"
#include "System.h"

int main() {
	Registry registry;
	System system(registry);

	registry.Add();
	registry.AddComponent<Position>(1, 0, 0);
	registry.AddComponent<Dimension>(1, 50, 50);
	registry.AddComponent<Velocity>(1, 10);
	system.SystemAdd<MovementSystem>(1);

	system.UsingSystem<MovementSystem>(1, 1, 1);
	system.UsingSystem<MovementSystem>(1, 1, 0);
	system.UsingSystem<MovementSystem>(1, 0, 1);
	system.UsingSystem<MovementSystem>(1, -1, 1);
	system.UsingSystem<MovementSystem>(1, 1, -1);
	


	Entity Stive(registry);
	Stive.Component<Position>(50, 50);
	Stive.Component<Dimension>(50, 50);
	Stive.Component<Velocity>(10);
	Stive.AddSystem<MovementSystem>();





	SetTraceLogLevel(LOG_WARNING);
	InitWindow(1000, 700, "My_Game");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		int move_x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int move_y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

		if (move_x != 0 || move_y != 0) {
			system.UsingSystem<MovementSystem>(1, move_x, move_y);
		}
		Stive.UseSystem<MovementSystem>();



		BeginDrawing();
		ClearBackground(RAYWHITE);


		Position* pos = registry.TryGetComponent<Position>(1);
		Dimension* dim = registry.TryGetComponent<Dimension>(1);

		if (pos != nullptr && dim != nullptr) {
			DrawRectangle(pos->x, pos->y, dim->width, dim->height, RED);
		}

		Stive.Draw(BLUE);


		EndDrawing();
	}

	CloseWindow();
}
