// vi: set ts=4 sw=4 :
// vim: set tw=75 :


#include <extdll.h>
#include <string>

#include <dllapi.h>
#include <meta_api.h>
#include "TebexMetaMod.h"

extern cvar_t tebex_showinfo;

void cmdTebexInfo( void )
{
	SERVER_PRINT("Tebex Info Called");
}

// Load the pm_messages.txt file at startup
void InitPlugin( void )
{
//	char tmp[1024];
//	GET_GAME_DIR(tmp);

	TebexMetaMod *plugin = new TebexMetaMod();

	LOG_CONSOLE( &Plugin_info, "[TEBEX] Tebex-MetaMod v0.1\n");

	REG_SVR_COMMAND("tebexinfo", cmdTebexInfo);

}


// It seems that when you use messagemode or messagemode2 the text you type is returned
// between quote marks, but when you type say or say_team in console these quotes marks aren't included.
// This function fills the g_szText global variable.
char g_szText[1024];
void StripQuotes( const char *cmd )
{
	if( (cmd[0] == '\"') && (cmd[strlen(cmd)-1] == '\"') )
	{
		strcpy(g_szText, &cmd[1]);
		g_szText[strlen(g_szText)-1] = '\0';
	}
	else
		strcpy(g_szText, cmd);
}

// The simpler the better :p
inline bool StringBeginsWith( char *str, char *begin )
{
	return (strstr(str, begin) == str);
}

inline char LowerCase( char c )
{
	return (c >= 'A') && (c <= 'Z') ? c - 'A' + 'a' : c;
}

bool StringContains( char *str, char *search )
{
	int st = strlen( str );
	int se = strlen( search );
	for( int i = 0; i <= st-se; ++i )
	{
		int j;
		for( j = 0; j < se; ++j )
		{
			if( LowerCase(str[i+j]) != LowerCase(search[j]) )
				break;
		}
		if( j == se )
			return true;
	}
	return false;
}

void SendMessage(edict_t *pPlayer, char* txt)
{
	char tmp[1024];
	sprintf(tmp, "%s\n", txt);
	MESSAGE_BEGIN(MSG_ONE, GET_USER_MSG_ID(PLID,"TextMsg",NULL), NULL, pPlayer);
		WRITE_BYTE(HUD_PRINTTALK);
		WRITE_STRING(tmp);
	MESSAGE_END();
}

void ClientCommand( edict_t *pPlayer )
{
	if( FNullEnt( pPlayer ) )
		RETURN_META(MRES_IGNORED);

	if( ( FStrEq(CMD_ARGV(0), "say_team") || FStrEq(CMD_ARGV(0), "say") ) && (CMD_ARGC() > 1) )
	{
		StripQuotes(CMD_ARGS());

		if( StringBeginsWith(g_szText, "!donate") )
		{

			SendMessage(pPlayer, "Donate URL!");
			RETURN_META(MRES_SUPERCEDE);
		}

	}
	RETURN_META(MRES_IGNORED);
}


static DLL_FUNCTIONS gFunctionTable = 
{
	NULL,					// pfnGameInit
	NULL,					// pfnSpawn
	NULL,					// pfnThink
	NULL,					// pfnUse
	NULL,					// pfnTouch
	NULL,					// pfnBlocked
	NULL,					// pfnKeyValue
	NULL,					// pfnSave
	NULL,					// pfnRestore
	NULL,					// pfnSetAbsBox

	NULL,					// pfnSaveWriteFields
	NULL,					// pfnSaveReadFields

	NULL,					// pfnSaveGlobalState
	NULL,					// pfnRestoreGlobalState
	NULL,					// pfnResetGlobalState

	NULL,					// pfnClientConnect
	NULL,					// pfnClientDisconnect
	NULL,					// pfnClientKill
	NULL,					// pfnClientPutInServer
	ClientCommand,			// pfnClientCommand
	NULL,					// pfnClientUserInfoChanged
	NULL,					// pfnServerActivate
	NULL,					// pfnServerDeactivate

	NULL,					// pfnPlayerPreThink
	NULL,					// pfnPlayerPostThink

	NULL,					// pfnStartFrame
	NULL,					// pfnParmsNewLevel
	NULL,					// pfnParmsChangeLevel

	NULL,					// pfnGetGameDescription
	NULL,					// pfnPlayerCustomization

	NULL,					// pfnSpectatorConnect
	NULL,					// pfnSpectatorDisconnect
	NULL,					// pfnSpectatorThink
	
	NULL,					// pfnSys_Error

	NULL,					// pfnPM_Move
	NULL,					// pfnPM_Init
	NULL,					// pfnPM_FindTextureType
	
	NULL,					// pfnSetupVisibility
	NULL,					// pfnUpdateClientData
	NULL,					// pfnAddToFullPack
	NULL,					// pfnCreateBaseline
	NULL,					// pfnRegisterEncoders
	NULL,					// pfnGetWeaponData
	NULL,					// pfnCmdStart
	NULL,					// pfnCmdEnd
	NULL,					// pfnConnectionlessPacket
	NULL,					// pfnGetHullBounds
	NULL,					// pfnCreateInstancedBaselines
	NULL,					// pfnInconsistentFile
	NULL,					// pfnAllowLagCompensation
};

C_DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, 
		int *interfaceVersion)
{
	if(!pFunctionTable) {
		UTIL_LogPrintf("GetEntityAPI2 called with null pFunctionTable");
		return(FALSE);
	}
	else if(*interfaceVersion != INTERFACE_VERSION) {
		UTIL_LogPrintf("GetEntityAPI2 version mismatch; requested=%d ours=%d", *interfaceVersion, INTERFACE_VERSION);
		//! Tell metamod what version we had, so it can figure out who is out of date.
		*interfaceVersion = INTERFACE_VERSION;
		return(FALSE);
	}
	memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));
	return(TRUE);
}
