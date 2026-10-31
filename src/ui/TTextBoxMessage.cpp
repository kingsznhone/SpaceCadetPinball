#include "pch.h"
#include "ui/TTextBoxMessage.h"
#include "core/pb.h"
namespace scp {

TTextBoxMessage::TTextBoxMessage(const char* text, float time, bool lowPriority)
{
	NextMessage = nullptr;
	Time = time;
	EndTicks = pb::time_ticks + static_cast<int>(time * 1000.0f);
	LowPriority = lowPriority;
	if (text)
	{
		const auto textLen = strlen(text) + 1;
		Text = new char[textLen];
		if (Text)
				std::copy_n(text, textLen, Text);
	}
	else
		Text = nullptr;
}

TTextBoxMessage::~TTextBoxMessage()
{
	delete[] Text;
}

float TTextBoxMessage::TimeLeft() const
{
	return static_cast<float>(EndTicks - pb::time_ticks) * 0.001f;
}

void TTextBoxMessage::Refresh(float time)
{
	this->Time = time;
	this->EndTicks = pb::time_ticks + static_cast<int>(time * 1000.0f);
}
} // namespace scp
