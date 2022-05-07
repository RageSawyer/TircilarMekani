#include "a_npc"
#include "file"

#define LOGLAR          "FusionalRWRP/Loglar"

#define DURUM_S1_D  0
#define DURUM_S1_S2 1
#define DURUM_S2_D  2
#define DURUM_S2_S1 3

new ODurum;

main(){}

public OnRecordingPlaybackEnd()
{
	DurumAyarla();
}


public OnNPCEnterVehicle(vehicleid, seatid)
{
	DurumDegistir(-1);
	DurumAyarla();
}

forward DurumAyarla();
public DurumAyarla()
{
	if(ODurum == -1 || ODurum == DURUM_S2_S1)
	{
	    StartRecordingPlayback(PLAYER_RECORDING_TYPE_DRIVER,"LS_LV_D");
	    DurumDegistir(DURUM_S1_D);
	}else if(ODurum == DURUM_S1_D)
	{
		StartRecordingPlayback(PLAYER_RECORDING_TYPE_DRIVER,"LS-LV");
		DurumDegistir(DURUM_S1_S2);
	}else if(ODurum == DURUM_S1_S2)
	{
	    StartRecordingPlayback(PLAYER_RECORDING_TYPE_DRIVER,"LV_LS_D");
	    DurumDegistir(DURUM_S2_D);
	}else if(ODurum == DURUM_S2_D)
	{
		StartRecordingPlayback(PLAYER_RECORDING_TYPE_DRIVER,"LV-LS");
		DurumDegistir(DURUM_S2_S1);
	}
}

forward DurumDegistir(durumid);
public DurumDegistir(durumid)
{
	new DosyaIsmi[256],DosyaYazi[256];
	format(DosyaIsmi,256,"%s/otobusler.txt",LOGLAR);
	
	if(fexist(DosyaIsmi))
	{
 		new File:Dosya=fopen(DosyaIsmi,io_read);
	    new DigerDosyaYazi[256];
	    

	    while(fread(Dosya,DigerDosyaYazi,256))
	    {
	        if(!strcmp("LS_SF",ini_GetKey(DigerDosyaYazi),true)) { format(DosyaYazi,256,"LS_SF=%d\r\n",strval( ini_GetValue(DigerDosyaYazi) )); }
	        if(!strcmp("LS_LV",ini_GetKey(DigerDosyaYazi),true)) { format(DosyaYazi,256,"%sLS_LV=%d\r\n",DosyaYazi,durumid); }
	        if(!strcmp("SF_LV",ini_GetKey(DigerDosyaYazi),true)) { format(DosyaYazi,256,"%sSF_LV=%d",DosyaYazi,strval( ini_GetValue(DigerDosyaYazi) )); }
		}

		fclose(Dosya);
		
		new File:Dosya2=fopen(DosyaIsmi,io_write);
		fwrite(Dosya2,DosyaYazi);
		fclose(Dosya2);
		
	}else{
	    new File:Dosya=fopen(DosyaIsmi,io_append);
		format(DosyaYazi,256,"LS_SF=%d\r\nLS_LV=%d\r\nSF_LV=%d",0,durumid,0);
		fwrite(Dosya,DosyaYazi);
		fclose(Dosya);
	}
	
	ODurum=durumid;
}

// ini_GetKey
stock ini_GetKey(yazi[])
{
	new key[2][256];
	split(yazi,key,'=');
	return key[0];
}

// ini_GetValue
stock ini_GetValue(yazi[])
{
	new key[2][256];
	split(yazi,key,'=');
	return key[1];
}

// split
split(const strsrc[], strdest[][], delimiter)
{
	new i, li,aNum,len;
	while(i <= strlen(strsrc))
	{
	    if(strsrc[i]==delimiter || i==strlen(strsrc))
		{
	        len = strmid(strdest[aNum], strsrc, li, i, 128);
	        strdest[aNum][len] = 0;
	        li = i+1;
	        aNum++;
		}
		i++;
	}
	return aNum;
}
