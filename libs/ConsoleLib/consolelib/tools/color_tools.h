//============================================================================
// Name        : ColorUtils
// Author      : Riyufuchi
// Created on  : Nov 20, 2021
// Last Edit   : Jan 13, 2026
//============================================================================

#ifndef SRC_INC_COLOR_UTILS_H_
#define SRC_INC_COLOR_UTILS_H_

namespace consolelib
{
struct Color // This way, there is no need to cast, because uint8_t would be treated as char not numerical value
{
	short int red;
	short int green;
	short int blue;
};
enum ColorPallete
{
	HAUNTED,
	UNIQUE,
	STRANGE,
	UNUSUAL,
	COLLECTORS,
	VALVE_VIOLET,
	COMMUNITY,
	PINK_AS_HELL,
	AUSTRALIUM_GOLD,
	No_216_190_216,
	SMARAGDINE,
	CONSOLE_ART_UNIX_DEFAULT,
	APERTURE_ORANGE,
	AMBER,
	TERMINAL_FG,
	COLOR_COUNT // This can be used to determine the size of the enum
};
}

namespace consolelib::color_tools
{
inline constexpr const char* color_palette_names[] =
{
	"HAUNTED",
	"UNIQUE",
	"STRANGE",
	"UNUSUAL",
	"COLLECTORS",
	"VALVE_VIOLET",
	"COMMUNITY",
	"PINK_AS_HELL",
	"AUSTRALIUM_GOLD",
	"No_216_190_216",
	"SMARAGDINE",
	"CONSOLE_ART_UNIX_DEFAULT",
	"APERTURE_ORANGE",
	"AMBER",
	"TERMINAL_FG"
};
[[deprecated("For backwards compatibility only - use newer obtain_color(ColorPallete)")]]
Color get_color(ColorPallete color);
Color obtain_color(ColorPallete color);
}
#endif /* SRC_INC_COLOR_UTILS_H_ */
