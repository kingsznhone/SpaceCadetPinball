#pragma once
#include <span>
namespace scp {


class EmbeddedData
{
public:
	static const char PB_MSGFT_bin_compressed_data_base85[5380 + 1];
	static const unsigned int SDL_GameControllerDB_compressed_data[63392 / 4];
	static const unsigned int SDL_GameControllerDB_compressed_size;

	static std::span<const char> PbMsgFtBin()
	{
		return PB_MSGFT_bin_compressed_data_base85;
	}

	static std::span<const unsigned int> SdlGameControllerDb()
	{
		return SDL_GameControllerDB_compressed_data;
	}
};
} // namespace scp
