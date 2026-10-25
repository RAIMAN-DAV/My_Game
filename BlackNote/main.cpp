#include "Registry.h"
#include "Entity.h"
#include "System.h"
#include "Pattern.h"

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
	

	Entity Georg(registry);
	Georg.Component<Position>(0, 0);
	Georg.Component<Dimension>(50, 100);
	Georg.Component<Dimension>(50, 200);
	Georg.Component<Velocity>(5);
	Georg.AddSystem<MovementSystem>();


	Pattern Wall;
	Wall.AddPatternComponent<Position>(200, 200);
	Wall.AddPatternComponent<Dimension>(80, 80);
	Wall.AddPatternComponent<Velocity>(0);
	Wall.AddPatternComponent<MovementSystem>();

	Entity Wale_1(registry);
	Entity Wale_2(registry);
	Entity Wale_3(registry);


	Wall >> Wale_1 >> Wale_2 >> Wale_3;

	Wale_1.Component<Velocity>(5);
	Wale_2.Component<Velocity>(7);
	Wale_3.Component<Velocity>(10);



	SetTraceLogLevel(LOG_WARNING);
	InitWindow(1000, 700, "My_Game");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		int move_x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int move_y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

		if (move_x != 0 || move_y != 0) {
			system.UsingSystem<MovementSystem>(obj, move_x, move_y);
		}
		Georg.UseSystem<MovementSystem>();

		Wale_1.UseSystem<MovementSystem>();
		Wale_2.UseSystem<MovementSystem>();
		Wale_3.UseSystem<MovementSystem>();

		BeginDrawing();
		ClearBackground(RAYWHITE);


		Position* pos = registry.TryGetComponent<Position>(obj);
		Dimension* dim = registry.TryGetComponent<Dimension>(obj);

		if (pos != nullptr && dim != nullptr) {
			DrawRectangle(pos->x, pos->y, dim->width, dim->height, RED);
		}
		
		Georg.Draw(SKYBLUE);

		Wale_1.Draw(BLUE);
		Wale_2.Draw(BLUE);
		Wale_3.Draw(BLUE);

		EndDrawing();
	}

	CloseWindow();
}
