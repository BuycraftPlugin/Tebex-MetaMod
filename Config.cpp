#pragma once

namespace tebexConfig {

	struct Config {
		bool buyEnabled = true;
		const char *buyCommand = "!donate";
		const char *secret = "";
		const char *baseUrl = "https://plugin.tebex.io";
	};
}