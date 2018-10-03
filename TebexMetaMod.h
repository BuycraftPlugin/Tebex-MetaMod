#pragma once
#include <fstream>
#include <random>
#include "WebstoreInfo.cpp"
#include "Config.cpp"
#include "json.hpp"
#include <string>

using json = nlohmann::json;
using Config = tebexConfig::Config;

class TebexMetaMod
{
	private:
		WebstoreInfo webstoreInfo;
		Config config;
		void saveConfig();
		int nextCheck = 15 * 60;
		time_t lastCalled = time(nullptr);
		void ReplaceStringInPlace(const char *subject, const char *search, const char *replace);

	public:
		TebexMetaMod();
		void logWarning(const char *message);
		void logError(const char *message);
		//void setWebstore(json json);
		WebstoreInfo getWebstore();
		Config getConfig();
		void setConfig(const char *key, const char *value);
		void readConfig();
		void setNextCheck(int newVal);
		bool doCheck();
		const char *buildCommand(const char *command, const char *playerName, const char *playerId, const char *UE4ID);
;};

TebexMetaMod::TebexMetaMod() {

	logWarning("Plugin Loading...");
	lastCalled -= 14 * 60;
}


void TebexMetaMod::logWarning(const char *message) {
	LOG_CONSOLE( &Plugin_info, "[TEBEX] [Warn] %s\n", message);
	LOG_MESSAGE( &Plugin_info, "%s\n", message);
}

void TebexMetaMod::logError(const char *message) {
	LOG_CONSOLE( &Plugin_info, "[TEBEX] [Err] %s\n", message);
	LOG_ERROR( &Plugin_info, "%s\n", message);
}
/*
void TebexMetaMod::setWebstore(json json) {
	webstoreInfo.id = json["account"]["id"].get<int>();
	webstoreInfo.name = json["account"]["name"].get<std::string>().c_str();
	webstoreInfo.domain = json["account"]["domain"].get<std::string>().c_str();
	webstoreInfo.currency = json["account"]["currency"]["iso_4217"].get<std::string>().c_str();
	webstoreInfo.currencySymbol = json["account"]["currency"]["symbol"].get<std::string>().c_str();
	webstoreInfo.gameType = json["account"]["game_type"].get<std::string>().c_str();

	webstoreInfo.serverName = json["server"]["name"].get<std::string>().c_str();
	webstoreInfo.serverId = json["server"]["id"].get<int>();

}*/

WebstoreInfo TebexMetaMod::getWebstore() {
	return webstoreInfo;
}

Config TebexMetaMod::getConfig()
{
	return config;
}

void TebexMetaMod::setConfig(const char *key, const char *value) {
	if (key == "secret") {
		config.secret = value;
	}

	saveConfig();
}

void TebexMetaMod::saveConfig()
{
	const char *config_path = "\\ArkApi\\Plugins\\TebexArk\\config.json";
/*	json configJson;

	logWarning(std::string("Save config to" + config_path).c_str());

	configJson["baseUrl"] = config.baseUrl;
	configJson["buyCommand"] = config.buyCommand;
	configJson["secret"] = config.secret;
	configJson["buyEnabled"] = config.buyEnabled;
	
	std::fstream configFile;
	configFile.open(config_path);
	configFile << configJson.dump();
	configFile.close();*/
}

void TebexMetaMod::readConfig()
{
	const char *config_path = "\\ArkApi\\Plugins\\TebexArk\\config.json";
	/*std::fstream configFile;
	configFile.open(config_path);

	if (!configFile.is_open()) {
		logWarning("No config file found, creating default");
	} else {
		json configJson;
		configFile >> configJson;
		if (!configJson["baseUrl"].is_null()) {
			config.baseUrl = configJson["baseUrl"].get<std::string>().c_str();
		}
		if (!configJson["buyCommand"].is_null()) {
			config.buyCommand = configJson["buyCommand"].get<std::string>().c_str();
		}
		if (!configJson["secret"].is_null()) {
			config.secret = configJson["secret"].get<std::string>().c_str();
		}
		if (!configJson["buyEnabled"].is_null()) {
			config.buyEnabled = configJson["buyEnabled"].get<bool>();
		}
		configFile.close();
	}
	saveConfig();*/
}

void TebexMetaMod::setNextCheck(int newVal) {
	nextCheck = newVal;
}

bool TebexMetaMod::doCheck() {
	time_t now = time(nullptr);
	if ((now - lastCalled) > nextCheck) {
		lastCalled = time(nullptr);
		return true;
	}
	return false;
}

const char *TebexMetaMod::buildCommand(const char *command, const char *playerName, const char *playerId, const char *UE4ID) {

	//ReplaceStringInPlace(command, "{username}", playerName);
	//ReplaceStringInPlace(command, "{id}", playerId);
	//ReplaceStringInPlace(command, "{ue4id}", UE4ID);
	return command;
}

void TebexMetaMod::ReplaceStringInPlace(const char *subject, const char *search, const char *replace) {
	//size_t pos = 0;
	//while ((pos = subject.find(search, pos)) != std::string::npos) {
	//	subject.replace(pos, search.length(), replace);
	//	pos += replace.length();
	//}
}