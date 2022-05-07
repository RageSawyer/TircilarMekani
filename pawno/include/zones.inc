/*  SA:MP Functions
 *  
 *  ZONES Functions By ~Cueball~
 *  ZONES Functions Aided By Betamaster (locations), Mabako (locations), Simon (finetuning)
 *
 *  (c) Copyright 2005-2008, SA:MP Team
 *
 */

#if defined _zones_included
	#endinput
#endif
#define _zones_included
#pragma library samp
#include <a_samp>

#define MAX_ZONE_NAME 28

//---------------------------------------------------------------------------------------------------

//NATIVES: KEEP THESE COMMENTED! THEY WILL STILL SHOW IN THE RIGHT HAND SIDE OF PAWN!

//native GetPlayer2DZone(playerid, zone[], len);
//native GetPlayer3DZone(playerid, zone[], len);
//native IsPlayerInZone(playerid, zone[]);

//---------------------------------------------------------------------------------------------------

//OUR MAJOR ARRAY: (GLOBAL)

//---------------------------------------------------------------------------------------------------

/* GetPlayer2DZone(playerid, zone[], len)
 * @Info:   Used to retrieve the players zone/area name. DOES NOT COMPARE HEIGHTS!
 *
 * @params: playerid      - The id of the player whose zone you will retrieve.
 * @params: zone[]        - The string with which the zone name will be formatted into.
 * @params: len		  - The maximum length you wish to format the zone name into. RECOMMENDED 28!
 */

stock GetPlayer2DZone(playerid, zone[], len) //Credits to Cueball, Betamaster, Mabako, and Simon (for finetuning).
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
 	for(new i = 0; i != sizeof(gSAZones); i++ )
 	{
		if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4])
		{
		    return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
		}
	}
	return 0;
}

//---------------------------------------------------------------------------------------------------

/* GetPlayer3DZone(playerid, zone[], len)
 * @Info:   Used to retrieve the players zone/area name and comparing with heights.
 *
 * @params: playerid      - The id of the player whose zone you will retrieve.
 * @params: zone[]        - The string with which the zone name will be formatted into.
 * @params: len		  - The maximum length you wish to format the zone name into. RECOMMENDED 28!
 */

stock GetPlayer3DZone(playerid, zone[], len) //Credits to Cueball, Betamaster, Mabako, and Simon (for finetuning).
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
 	for(new i = 0; i != sizeof(gSAZones); i++ )
 	{
		if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4] && z >= gSAZones[i][SAZONE_AREA][2] && z <= gSAZones[i][SAZONE_AREA][5])
		{
		    return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
		}
	}
	return 0;
}

//---------------------------------------------------------------------------------------------------

/* IsPlayerInZone(playerid, zone[])
 * @Info:   Used to check if the player is inside the zone[] parameter.
 *
 * @params: playerid      - The id of the player whose zone you will check.
 * @params: zone[]        - The string with which we will compare the players zone name to.
 */

stock IsPlayerInZone(playerid, zone[]) //Credits to Cueball, Betamaster, Mabako, and Simon (for finetuning).
{
	new TmpZone[MAX_ZONE_NAME];
	GetPlayer3DZone(playerid, TmpZone, sizeof(TmpZone));
	for(new i = 0; i != sizeof(gSAZones); i++)
	{
		if(strfind(TmpZone, zone, true) != -1)
			return 1;
	}
	return 0;
}