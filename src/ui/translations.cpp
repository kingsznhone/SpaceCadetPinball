#include "pch.h"
#include "ui/translations.h"
namespace scp {


Lang translations::CurrentLanguage = Lang::English;
const LanguageInfo translations::Languages[static_cast<int>(Lang::Max)] =
{
	{Lang::Arabic, "ar", "Arabic"},
	{Lang::Czech, "cs", "Czech"},
	{Lang::Danish, "da", "Danish"},
	{Lang::German, "de", "German"},
	{Lang::Greek, "el", "Greek"},
	{Lang::English, "en", "English"},
	{Lang::Spanish, "es", "Spanish"},
	{Lang::Finnish, "fi", "Finnish"},
	{Lang::French, "fr", "French"},
	{Lang::Hebrew, "he", "Hebrew"},
	{Lang::Hungarian, "hu", "Hungarian"},
	{Lang::Italian, "it", "Italian"},
	{Lang::Japanese, "ja", "Japanese"},
	{Lang::Korean, "ko", "Korean"},
	{Lang::Norwegian, "nb", "Norwegian"},
	{Lang::Dutch, "nl", "Dutch"},
	{Lang::Polish, "pl", "Polish"},
	{Lang::BrazilianPortuguese, "pt_BR", "Brazilian Portuguese"},
	{Lang::Portuguese, "pt_PT", "Portuguese"},
	{Lang::Russian, "ru", "Russian"},
	{Lang::Swedish, "sv", "Swedish"},
	{Lang::Turkish, "tr", "Turkish"},
	{Lang::SimplifiedChinese, "zh_CN", "Simplified Chinese"},
	{Lang::TraditionalChinese, "zh_TW", "Traditional Chinese"},
};

void translations::SetCurrentLanguage(const char* short_name)
{
	for (const auto& langInfo : Languages)
	{
		if (!strcmp(short_name, langInfo.ShortName))
		{
			CurrentLanguage = langInfo.Language;
			return;
		}
	}

	assertm(false, "Unknown language");
}

const LanguageInfo* translations::GetCurrentLanguage()
{
	for (const auto& langInfo : Languages)
	{
		if (langInfo.Language == CurrentLanguage)
		{
			return &langInfo;
		}
	}

	return nullptr;
}

const char* translations::GetTranslation(Msg id)
{
	if (!TextArray::contains(id))
		return "!Missing MsgId!";

	// Current language assumed in bounds at this point
	auto text = Translations.Get(id, CurrentLanguage);

	// Fallback to English if available
	if (text == nullptr) 
	{
		text = Translations.Get(id, Lang::English);
		if (text == nullptr)
			text = "!Missing English text!";
	}

	return text;
}

void translations::GetGlyphRange(ImVector<ImWchar>* ranges)
{
	ImFontGlyphRangesBuilder builder;

	for (int i = 0; i < (int)Msg::Max; i++)
	{
		const char* translation = GetTranslation((Msg)i);
		if (translation)
		{
			builder.AddText(translation);
		}
	}

	builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesDefault());
	builder.BuildRanges(ranges);
}
} // namespace scp
