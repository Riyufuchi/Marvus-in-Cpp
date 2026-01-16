//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-16
// Last edit  : 2026-01-16
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MARVUS_CONFIG_HPP
#define MARVUS_CONFIG_HPP

#include <glib.h>

namespace marvus
{

inline const char* MARVUS_FOLDER = "marvus";

struct MarvusConfig
{
	gboolean dark_mode;
};

inline void write_config(const MarvusConfig& config)
{
	GKeyFile* keyfile = g_key_file_new();

	g_key_file_set_string(keyfile, "Appearance", "theme", config.dark_mode ? "dark" : "light");

	gsize len;
	char* data = g_key_file_to_data(keyfile, &len, NULL);

	const char* base = g_get_user_config_dir();
	char* dir = g_build_filename(base, MARVUS_FOLDER, NULL);
	char* file = g_build_filename(dir, "config.ini", NULL);

	g_mkdir_with_parents(dir, 0700);
	g_file_set_contents(file, data, len, NULL);

	g_free(data);
	g_free(file);
	g_free(dir);
	g_key_file_free(keyfile);
}

inline MarvusConfig load_config()
{
	MarvusConfig config { false };

	const char* base_dir = g_get_user_config_dir();
	char* dir = g_build_filename(base_dir, MARVUS_FOLDER, NULL);
	char* file = g_build_filename(dir, "config.ini", NULL);

	GKeyFile* keyfile = g_key_file_new();

	if (g_key_file_load_from_file(keyfile, file, G_KEY_FILE_NONE, NULL))
	{
		if (g_key_file_has_key(keyfile, "Appearance", "theme", NULL))
		{
			char* theme = g_key_file_get_string(keyfile, "Appearance", "theme", NULL);
			config.dark_mode = g_strcmp0(theme, "dark") == 0;
			g_free(theme);
		}
	}
	else
	{
		config.dark_mode = true;
		write_config(config);
	}

	g_key_file_free(keyfile);
	g_free(file);
	g_free(dir);

	return config;
}

}

#endif // MARVUS_CONFIG_HPP
