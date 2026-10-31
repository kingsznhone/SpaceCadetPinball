#include "pch.h"
#include "ui/font_selection.h"

#include "app/options.h"
#include "core/pb.h"
#include "ui/score.h"
#include "app/winmain.h"
#include "ui/translations.h"
namespace scp {

static const char* popupName = "Font Selection";
bool font_selection::ShowDialogFlag = false;
char font_selection::DialogInputBuffer[512];

void font_selection::ShowDialog()
{
	ShowDialogFlag = true;
}

void font_selection::RenderDialog()
{
	if (ShowDialogFlag == true)
	{
		auto inputEnd = std::format_to_n(DialogInputBuffer, sizeof DialogInputBuffer - 1, "{}",
		                                 options::Options.FontFileName.V);
		*inputEnd.out = '\0';
		ShowDialogFlag = false;
		if (!ImGui::IsPopupOpen(popupName))
		{
			ImGui::OpenPopup(popupName);
		}
	}

	bool unused_open = true;
	if (ImGui::BeginPopupModal(popupName, &unused_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Font file to use: ");
		ImGui::SameLine();
		ImGui::InputText("##Font", DialogInputBuffer, IM_ARRAYSIZE(DialogInputBuffer));

		if (ImGui::Button(pb::get_rc_string(Msg::GenericOk)))
		{
			options::Options.FontFileName.V = DialogInputBuffer;
			ImGui::CloseCurrentPopup();
			winmain::Restart();
		}

		ImGui::SameLine();
		if (ImGui::Button(pb::get_rc_string(Msg::GenericCancel)))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}
}
} // namespace scp
