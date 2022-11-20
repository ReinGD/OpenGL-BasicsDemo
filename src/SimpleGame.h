#include <vector>
#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

class GLFWwindow;

class SimpleGame
{
public:
	struct vertex 
	{
		float x;
		float y;
		float z;

		vertex(float in_x, float in_y, float in_z)
		{
			x = in_x;
			y = in_y;
			z = in_z;
		};
	};


public:
	//big 6
	SimpleGame();
	~SimpleGame() = default;
	SimpleGame(const SimpleGame&) = delete;
	SimpleGame(SimpleGame&&) = delete;
	SimpleGame& operator= (const SimpleGame&) = delete;
	SimpleGame& operator= (SimpleGame&&) = delete;


	void InitializeOpenGL();
	void TerminateOpenGL();
	void run();

	void resizeBufferCallback(GLFWwindow* window, int width, int height);

	std::vector<vertex> allVertex;

private:

};

#endif // !SIMPLE_GAME_H
