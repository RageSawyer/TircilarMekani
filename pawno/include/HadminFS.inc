/*
+-----------------------------------------------------------------------+
¦                        JunkBuster Anti-Cheat                          ¦
¦                                  by                                   ¦
¦                           Double-O-Seven                              ¦
¦                                                                       ¦
¦ You should use JunkBuster in your gamemode! If you want to use it in  ¦
¦                                                                       ¦
+-----------------------------------------------------------------------+
*/

#include <a_samp>

stock H_SetPlayerMoney(playerid, pMiktar)
   return CallRemoteFunction("SetPlayerMoneyEx","ii", playerid, pMiktar);

stock H_GivePlayerMoney(playerid, pMiktar)
	return CallRemoteFunction("GivePlayerMoneyEx","ii",playerid, pMiktar);

stock H_GetPlayerMoney(playerid)
	return CallRemoteFunction("GetPlayerMoneyEx","i",playerid);

stock H_ResetPlayerMoney(playerid)
	return CallRemoteFunction("ResetPlayerMoneyEx","i",playerid);

stock H_SetPlayerScore(playerid, sMiktar)
	return CallRemoteFunction("SetPlayerScoreEx","ii",playerid, sMiktar);

stock H_GetPlayerScore(playerid)
	return CallRemoteFunction("GetPlayerScoreEx","i",playerid);

stock H_SetPlayerSkin(playerid, sID)
	return CallRemoteFunction("SetPlayerSkinEx","ii",playerid, sID);

stock H_GetPlayerSkin(playerid)
	return CallRemoteFunction("GetPlayerSkinEx","i",playerid);

stock H_SetPlayerWantedLevel(playerid, wL)
	return CallRemoteFunction("SetPlayerWantedLevelEx","ii",playerid, wL);

stock H_GetPlayerWantedLevel(playerid)
	return CallRemoteFunction("GetPlayerWantedLevelEx","i",playerid);

stock H_SetPlayerSpecialAction(playerid, SAid)
	return CallRemoteFunction("SetPlayerSpecialActionEx","ii",playerid, SAid);

stock H_GivePlayerWeapon(playerid,weaponid,ammo)
	return CallRemoteFunction("GivePlayerWeaponEx","iii",playerid,weaponid,ammo);

stock H_AddStaticPickup(model,type,Float:X,Float:Y,Float:Z,virtualworld)
	return CallRemoteFunction("AddStaticPickupEx","iifffi",model,type,X,Y,Z,virtualworld);

stock H_CreatePickup(model,type,Float:X,Float:Y,Float:Z,virtualworld)
	return CallRemoteFunction("CreatePickupEx","iifffi",model,type,X,Y,Z,virtualworld);

stock H_H_AddPlayerClass(modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo)
	return CallRemoteFunction("H_AddPlayerClass","iffffiiiiii",modelid,spawn_x,spawn_y,spawn_z,z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);

stock H_H_AddPlayerClassEx(teamid,modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo)
	return CallRemoteFunction("H_AddPlayerClassEx","iiffffiiiiii",teamid,modelid,spawn_x,spawn_y,spawn_z,z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);

stock H_SetSpawnInfo(playerid,team,skin,Float:x,Float:y,Float:z,rotation,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo)
	return CallRemoteFunction("SetSpawnInfoEx","iiifffiiiiiii",playerid,team,skin,x,y,z,rotation,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);

stock H_SetPlayerPos(playerid,Float:iX,Float:iY,Float:iZ)
    return CallRemoteFunction("SetPlayerPosEx","ifff", playerid,iX, iY, iZ);

stock H_SetVehicleVelocity(vehicleid,Float:sX,Float:sY,Float:sZ)
	return CallRemoteFunction("SetVehicleVelocityEx","ifff",vehicleid, sX, sY, sZ);

stock H_SetPlayerVelocity(playerid, Float:vX, Float:vY, Float:vZ)
	return CallRemoteFunction("SetPlayerVelocityEx","ifff",playerid, vX, vY, vZ);

stock H_TogglePlayerControllable(playerid, durum)
	return CallRemoteFunction("TogglePlayerControllableEx","ii",playerid, durum);

stock H_Ban_(playerid)
	return CallRemoteFunction("Ban_","i",playerid);

stock H_BanEx_(playerid, neden)
	return CallRemoteFunction("BanEx_","is",playerid,neden);

stock H_GetPlayerAdminLevel(playerid)
	return CallRemoteFunction("GetPlayerAdminLevel","i",playerid);

stock H_OyuncuAdminLevel(playerid)
	return CallRemoteFunction("GetPlayerAdminLevel","ii",playerid);

stock H_GetPlayerVipLevel(playerid)
	return CallRemoteFunction("GetPlayerVipLevel","i",playerid);

stock H_OyuncuVipLevel(playerid)
	return CallRemoteFunction("GetPlayerVipLevel","ii",playerid);

#define GetPlayerMoney H_GetPlayerMoney
#define ResetPlayerMoney H_ResetPlayerMoney
#define GivePlayerMoney H_GivePlayerMoney
#define SetPlayerMoney H_SetPlayerMoney
#define SetPlayerScore H_SetPlayerScore
#define GetPlayerScore H_GetPlayerScore
#define SetPlayerSkin H_SetPlayerSkin
#define GetPlayerSkin H_GetPlayerSkin
#define SetPlayerWantedLevel H_SetPlayerWantedLevel
#define GetPlayerWantedLevel H_GetPlayerWantedLevel
#define SetPlayerSpecialAction H_SetPlayerSpecialAction
#define GivePlayerWeapon H_GivePlayerWeapon
#define AddStaticPickup H_AddStaticPickup
#define CreatePickup H_CreatePickup
#define AddPlayerClass H_H_AddPlayerClass
#define AddPlayerClassEx H_H_AddPlayerClassEx
#define SetSpawnInfo H_SetSpawnInfo
#define SetPlayerPos H_SetPlayerPos
#define SetVehicleVelocity H_SetVehicleVelocity
#define SetPlayerVelocity H_SetPlayerVelocity
#define TogglePlayerControllable H_TogglePlayerControllable
#define Ban H_Ban_
#define BanEx H_BanEx_
#define GetPlayerAdminLevel H_GetPlayerAdminLevel
#define OyuncuAdminLevel H_OyuncuAdminLevel
#define GetPlayerVipLevel H_GetPlayerVipLevel
#define OyuncuVipLevel H_OyuncuVipLevel
