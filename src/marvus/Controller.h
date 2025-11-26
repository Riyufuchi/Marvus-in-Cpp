//==============================================================================
// File       : Controller.h
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Nov 26, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_CONTROLLER_H_
#define MARVUS_CONTROLLER_H_

#include <wx/wx.h>

#include "../marvus/database/MarvusDB.h"
#include "../marvus/dialogs/PaymentDialog.h"
// ConsoleLib
#include "ArgumentParser.h"

namespace marvus
{
inline const std::string DATABASE_FILE = "marvus.db";
class Controller
{
private:
	std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
	MarvusDB marvusDB;
public:
	Controller();
	virtual ~Controller() = default;
	void configure(ConsoleLib::argVector& config);
	bool initDB(std::string& errorMsg);
	void dropDB();
	MarvusDB& getDB();
};

} /* namespace marvus */

#endif /* MARVUS_CONTROLLER_H_ */
