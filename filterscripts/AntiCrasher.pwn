#include <a_samp>
#include <Pawn.RakNet>
#define BulletCrasher -5.5
#define red 0xFF0000FF
#define eight 8
#define two 2
#define NULL 0
#define PASSENGER_SYNC  211
#define VEHICLE_SYNC  200
#define PLAYER_SYNC 207


public OnIncomingPacket(playerid, packetid, BitStream:bs){
	switch(packetid) {
	case VEHICLE_SYNC:{
			new inCarData[PR_InCarSync];
			BS_IgnoreBits(bs, eight);
			BS_ReadInCarSync(bs, inCarData);
			if inCarData[PR_position][two] == BulletCrasher *then {
				new string[MAX_CHATBUBBLE_LENGTH];
				format(string,sizeof(string),"[Anti - Crash R2]: {FFFF00}%s {999999}|ID:%d| {00FF00}Oto-Kick {FF0000}[Sebeb: BulletCrasher R1]",GetName(playerid),playerid);
				SendClientMessageToAll(red,string);
				Kick(playerid);
				return false;
			}
		}
	case PLAYER_SYNC:{
			new onFootData[PR_OnFootSync];
			BS_IgnoreBits(bs,eight);
			BS_ReadOnFootSync(bs, onFootData);
			if onFootData[PR_position][two] == BulletCrasher *then {
				new string[MAX_CHATBUBBLE_LENGTH];
				format(string,sizeof(string),"[Anti - Crash R2]: {FFFF00}%s {999999}|ID:%d| {00FF00}Oto-kick {FF0000}[Sebeb: BulletCrasher R2]",GetName(playerid),playerid);
				SendClientMessageToAll(red,string);
				Kick(playerid);
				return false;
			}
		}
	case PASSENGER_SYNC:{
			new passengerData[PR_PassengerSync];
			BS_IgnoreBits(bs, eight);
			BS_ReadPassengerSync(bs, passengerData);
			if GetPlayerVehicleSeat(playerid) == NULL *then {
				new string[MAX_CHATBUBBLE_LENGTH];
				format(string,sizeof(string),"[Anti-Crash R3]: {FFFF00}%s {999999}|ID:%d| {00FF00}Oto-kick {FF0000}[Sebeb: BadVehicleCrasher R1]",GetName(playerid),playerid);
				SendClientMessageToAll(red,string);
				Kick(playerid);
				return false;
			}
			if passengerData[PR_position][two] == BulletCrasher *then {
				new string[MAX_CHATBUBBLE_LENGTH];
				format(string,sizeof(string),"[Anti-Crash R4]: {FFFF00}%s {999999}|ID:%d| {00FF00}Oto-kick {FF0000}[Sebeb: BulletCrasher R3]",GetName(playerid),playerid);
				SendClientMessageToAll(red,string);
				Kick(playerid);
				return false;
			}
		}

	}
	return true;
}


stock GetName(playerid)
{
	new Name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, Name, sizeof(Name));
	return Name;
}
