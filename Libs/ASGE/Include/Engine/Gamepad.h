#pragma once
struct GamePadData
{
	GamePadData(
		int id,
		const char* n,
		int axis_count, 
		const float* axis_data,
		int button_count,
		const unsigned char* btns)
		: idx(id), name(n), no_of_axis(axis_count), axis(axis_data), no_of_buttons(button_count), buttons(btns)
	{

	}

	const int idx = -1;
	const int no_of_axis = 0;
	const int no_of_buttons = 0;
	const float* axis = nullptr;
	const unsigned char* buttons = nullptr;
	const char* name = nullptr;
	bool is_connected = false;
};
