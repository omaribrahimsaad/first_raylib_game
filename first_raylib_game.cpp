// first_raylib_game.cpp : Defines the entry point for the application.
//

#include "first_raylib_game.h"
#include "raylib.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

#if 0
int main()
{
	// initialize stuff
	InitWindow(500, 500, "hello world");

	const std::map<std::string, Color> colors = {
		{"red",{ 0xff, 0, 0, 0xff }},
		{"green",{ 0, 0xff, 0, 0xff }},
		{"blue",{ 0, 0, 0xff, 0xff }},
		{"white",{ 0xff, 0xff, 0xff, 0xff }},

	};


	enum Mode
	{
		Hovering,
		Drawing,

	};

	Mode mode = Hovering;
	// main game loop
	while (!WindowShouldClose())
	{

		BeginDrawing();

		switch (mode)
		{
		case Mode::Drawing:
			DrawCircle(GetMouseX(), GetMouseY(), 5, colors.at("red"));
			break;
		case Mode::Hovering:

			ClearBackground(colors.at("white"));
			DrawCircle(GetMouseX(), GetMouseY(), 5, colors.at("red"));

			break;
		}

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			mode = Drawing;
		}
		else
		{
			mode = Hovering;
		}

		EndDrawing();
	}

}
#endif

const struct{
	Color red_ = { 0xff, 0, 0, 0xff };
	Color green_ = { 0, 0xff, 0, 0xff };
	Color blue_ = { 0, 0, 0xff, 0xff };
	Color white_ = { 0xff, 0xff, 0xff, 0xff };
	Color black_ = { 0, 0, 0, 0xff };
}kColor;

// colorful grid exercise
void DrawGrid(int rows,int cols)
{
	int screen_height = GetScreenHeight(), screen_width = GetScreenWidth();

	float row_height = screen_height / rows;
	float col_width = screen_width / cols;


	for (int row = 0; row < rows; row++)
	{
		DrawLine(0, row_height * row, screen_width, row_height * row, kColor.black_);
	}

	for (int col = 0; col < cols; col++)
	{
		DrawLine(col_width * col, 0, col_width * col, screen_height, kColor.black_);

	}


}

class GridRect
{
public:
	GridRect(int x, int y, int width, int height)
		:x_(x),y_(y),width_(width),height_(height)
	{}
	
	bool ContainsCoordinate(int x, int y)
	{
		bool contained_horizontal = x > x_ && x < (x_ + width_);
		bool contained_vertical = y > y_ && y < (y_ + height_);
		if (contained_horizontal && contained_vertical)
			return true;

		return false;
	}

	void DrawGridRect(Color color)
	{
		DrawRectangle(x_,y_,width_,height_,color);
	}


private:
	int x_, y_, width_, height_;

};


int main()
{
	//---------- window initialization ----------
	
	// width height ratio of 16:9
	const struct { const int width_ = 16, height_ = 9; }ratio;
	const int kWidth = 1000;
	const int kHeight = kWidth * ratio.height_ / ratio.width_;

	InitWindow(kWidth, kHeight, "colorful grid");

	SetTargetFPS(60);

	// initialize grid
	const int kGridRow = 18, kGridCol = 32;
	std::vector<GridRect> squares;
	int screen_height = GetScreenHeight(), screen_width = GetScreenWidth();
	float row_height = screen_height / kGridRow;
	float col_width = screen_width / kGridCol;

	for (int row = 0; row < kGridRow; row++)
	{
		for (int col = 0; col < kGridCol; col++)
		{
			squares.emplace_back(GridRect(col*col_width,row*row_height, col_width, row_height));
		}
	}

	//---------- main loop ----------
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(kColor.white_);
		DrawGrid(kGridRow, kGridCol);

		auto mouse_position = GetMousePosition();
		
		for (auto& square : squares)
		{
			if (square.ContainsCoordinate(mouse_position.x, mouse_position.y))
				square.DrawGridRect(kColor.green_);
		}

		EndDrawing();
	}
}