#pragma once
namespace scp {

class font_selection
{
public:
	static void ShowDialog();
	static void RenderDialog();
private:
	static bool ShowDialogFlag;
	static char DialogInputBuffer[512];
};
} // namespace scp
