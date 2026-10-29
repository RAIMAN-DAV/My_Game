#include "World.h"


int main() {
	Registry registry;
	World world(registry);


	Entity Georg(registry);
	Georg.Component<Position>(0, 0);
	Georg.Component<Dimension>(50, 100);
	Georg.Component<Dimension>(50, 50);
	Georg.Component<Velocity>(5);
	Georg.AddSystem<MovementSystem>();



	Pattern Wall;
	Wall.AddPatternComponent<Position>(200, 200);
	Wall.AddPatternComponent<Dimension>(50, 50);
	Wall.AddPatternComponent<MovementSystem>();


	Entity& Wale_1 = world.Add();
	Entity& Wale_2 = world.Add();
	Entity& Wale_3 = world.Add();
	Entity& Wale_4 = world.Add();

	Wall >> Wale_1 >> Wale_2 >> Wale_3 >> Wale_4;

	
	Wale_2.Component<Position>(250, 200);
	Wale_3.Component<Position>(300, 200);
	Wale_4.Component<Position>(350, 200);


	Entity& Wale_5 = world.Add();




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


		world.UseSystem<MovementSystem>();

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
