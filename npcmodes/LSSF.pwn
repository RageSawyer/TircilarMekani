	#define RECORDING "LSSF" // RECORDING yerine dikkat.Buras� /vrecord yazarken npc nin ad�n� yazd���m�z yerdir.Mesela /npcrecord RECORDING
	#define RECORDING_TYPE 1

	#include <a_npc>
	main(){}
	public OnRecordingPlaybackEnd() StartRecordingPlayback(RECORDING_TYPE, RECORDING);

	#if RECORDING_TYPE == 1
	    public OnNPCEnterVehicle(vehicleid, seatid) StartRecordingPlayback(RECORDING_TYPE, RECORDING);
	    public OnNPCExitVehicle() StopRecordingPlayback();
	#else
	    public OnNPCSpawn() StartRecordingPlayback(RECORDING_TYPE, RECORDING);
	#endif
