#include <glad/glad.h>
#include "Engine.h"

int main() {
	Engine engine;

	if (engine.Initialize(1280, 720, "BokiEngine v0.1")) {
		engine.Run();
	}

	return 0;
}