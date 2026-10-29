#include "World.h"


int main() {
	Registry registry;
	World world(registry);


	Entity Georg(registry);
	Georg.Component<Position>(0, 0);
	Georg.Component<Dimension>(50, 100);
	Georg.Component<Dimension>(50, 200);
	Georg.Component<Velocity>(5);
	Georg.AddSystem<MovementSystem>();



	Pattern Wall;
	Wall.AddPatternComponent<Position>(200, 200);
	Wall.AddPatternComponent<Dimension>(80, 80);
	Wall.AddPatternComponent<Velocity>(3);
	Wall.AddPatternComponent<MovementSystem>();

	Entity& Wale_1 = world.Add();
	Entity& Wale_2 = world.Add();
	Entity& Wale_3 = world.Add();
	Wall >> Wale_1 >> Wale_2 >> Wale_3;

	Wale_1.Component<Velocity>(5);
	Wale_2.Component<Velocity>(7);
	Wale_3.Component<Velocity>(10);



	SetTraceLogLevel(LOG_WARNING);
	InitWindow(1000, 700, "My_Game");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {


		if (IsKeyPressed(KEY_X)) {
			Wale_1.Destroy();
		}

		if (IsKeyPressed(KEY_R)) {
			Wall >> Wale_1;
		}


		Georg.UseSystem<MovementSystem>();

		Wale_1.UseSystem<MovementSystem>();
		Wale_2.UseSystem<MovementSystem>();
		Wale_3.UseSystem<MovementSystem>();

		BeginDrawing();
		ClearBackground(RAYWHITE);


		Georg.Draw(SKYBLUE);

		//world.ForEach([](Entity& entity) {
		//	entity.Draw(BLUE);
		//});

		world.ForEach<Position, Dimension>(DrawRectangle, BLUE);


		EndDrawing();
	}

	CloseWindow();
}
