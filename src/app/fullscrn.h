#pragma once
#include <array>
namespace scp {

struct resolution_info
{
	int ScreenWidth;
	int ScreenHeight;
	int TableWidth;
	int TableHeight;
	int ResolutionMenuId;
};

class fullscrn
{
public:
	static int screen_mode;
	static int display_changed;
	static const std::array<resolution_info, 3> resolution_array;
	static float ScaleX;
	static float ScaleY;
	static int OffsetX;
	static int OffsetY;

	static void init();
	static void shutdown();
	static int set_screen_mode(int isFullscreen);
	static void activate(int flag);
	static int GetResolution();
	static void SetResolution(int value);
	static int GetMaxResolution();
	static void window_size_changed();
	static SDL_Rect GetScreenRectFromPinballRect(SDL_Rect rect);
	static float GetScreenToPinballRatio();
private :
	static int resolution;

	static int enableFullscreen();
	static int disableFullscreen();
};
} // namespace scp
