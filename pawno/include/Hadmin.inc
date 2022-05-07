  /*---------------------------------------------------------++---------------------------------------------------------+
   |                       Hadmin v1                        <||>                                                        |
   |  Giriþ;                                                <||>  Ýçerik;                                               |
   |                                                        <||>                                                        |
   |     Öncelikle bu sistemi yazmamýn nedenini açýklayayým <||>     Kayýt olan alanlarý rahatlýkla deðiþtirebilirsiniz |
   | Herkesin "Ladminv2" kullanmasý yüzünden yazmýþ olduðum <||> (Bknz:Skor, Skin, Aranma Seviyesi..)                   |
   | Sistem bilenin ve bilmeyenin Türkçeye cevirme çabasýna <||>                                                        |
   | girmesine gerek kalmadan ve sadece basit deðiþiklikler <||>     Türkçe: Ýçerik tamamen türkçe fakat komut isimleri |
   | yaparak kullanabileceði bu sistem sayesinde artýk daha <||> ingilizce mi yoksa türkçe mi olsun diye düþündüm fakat |
   | rahatýz.                                               <||> karar vermedim o yüzden anket sonucuna göre komutlarýn |
   |                                                        <||> isimlernin türkçe yada ingilizceye çevireceðim.        |
   |                                                        <||>                                                        |
   |      Biraz içerikten bahsedeyim komutlara alýþmak gibi <||>     Skin Kaydetme: Her oyuncu kayýt olduðunda skinleri |
   | bir sorun olmasýn diye, komutlarýn çoðunu ayný yaptým. <||> 0 olarak kayýda geçer. Spawn olurken eðer deðer 0 ise; |
   | Ayrýca komutlarýn hepsini tektek kendimi yazdým sadece <||> skini deðiþtirmez var olan skini kalýr eðer 0 deðilse, |
   | komutlarýn isimlerine baktým çünkü hepsini bilmiyordum <||> Spawnda skinini kayýttaki skin olarak deðiþtirir, peki |
   |                                                        <||> kayýttaki skin nasýl deðiþecek ? - Skin deðiþtirme ile |
   |      Gereksinimler;                                    <||> komudu ile.                                            |
   |                                                        <||>                                                        |
   |      Gereðimiz olan inculudeler :"ZCMD, sscanf, Y_ini" <||>     Modu çalýþtýrmadan önce:                           |
   | sscanf'in Plug-in'i kullanmanýzý tavsiye ederim çünkü; <||> 53. satýrdan baþlayan tanýmlamalarý kendinize göre yap-|
   | Hem C++'da yazýldýðý için daha hýzlý ve önemli buglarý <||> ýn. Ayarladýktan sonra; 75. satýrý silin yoksa compile |
   | Fixlenmiþ versiyonudur. Plug-in'i kullanmak isterseniz <||> hatasý alýrsýnýz.                                      |
   | Sadece sscanf2'yi Pawno/include'ye atýp Plug-ini açmak <||>                                                        |
   | Yeterli olacaktýr.                                     <||>     Peki ya Filterscriptsler?                          |
   |                                                        <||> - Anti Para hilesinin çalýþabilmesi için Filterscripts |
   |                                                        <||> lere #include <HadminFS> eklemelisiniz yoksa; verilen, |
   |       Y_ini Kullanmamýn nedeni:                        <||> alýnan paralar kayýt olmaz ve eski parasýna geri döner |                                  |
   |                                                        <||> ayrýca hile yapýyormuþ gibi görünüp sunucudan atýlmasý |
   |       Özetlemek gerekirse, diðerlerinden daha optimize <||> veya yasaklanmasýna neden olabilir.                    |
   | olduðu için kullanmayý seçtim.Aþaðýda bilinen bazý ini <||>                                                        |
   | yazýcýlarýnýn test sonuçlarý var;                      <||>                                                        |
   |                                                        <||>                                                        |
   | y_ini: 1564  - dini: 63810 -  emu : 27297 - SII: 52807 <||>                                                        |
   |                                                        <||>                                        Sarp Aykent     |
   +---------------------------------------------------------++---------------------------------------------------------*/

//---------------------------------------------[-Includelar-]---------------------------------------------//
#include	 <a_samp>
#tryinclude  <ZCMD>
#if !defined _zcmd_included
#error Lütfen ZCMD.inc'i Pawno/include'ye atin
#endif
#if !defined sscanf
#tryinclude	 <sscanf2>
#endif
#tryinclude  <YSI/y_ini>
#if !defined MAX_INI_TAG
#error Lütfen y_ini.inc'i Pawno/include/YSI'ye atin
#endif
//---------------------------------------------[-Includelar-]---------------------------------------------//
//--------------------------------------------[-Cezalar-]--------------------------------------------//
#define ANTI_JETPACK             1      // 0 = Kapatma, 1 = Engelleme (Önerilen 1)
#define ANTI_PARA                1      // 0 = Kapatma, 1 = Engelleme (Önerilen 1)
#define ANTI_HIZ                 2      // 0 = Kapatma, 1 = Kick, 2 = Ban (Önerilen 2)
#define ANTI_SILAH               1      // 0 = Kapatma, 1 = Kick,  2 = Ban (Önerilen 1)
#define AIR_BRAKE                1      // 0 = Kapatma, 1 = Kick,  2 = Ban (Önerilen 1)
#define ANTI_FLY                1       // 0 = Kapatma, 1 = Kick,  2 = Ban (Önerilen 1) Bilgi : Sobeit'in 4.1.0.0 versiyonunda gelen yaya FLY hilesi içindir
//--------------------------------------------[-Cezalar-]--------------------------------------------//
//--------------------------------------------[-Ayarlamalar-]--------------------------------------------//
#define BASLANGIC_PARA_MIKTAR    1000      // Oyuncu Kayýt olduðunada gelcek para miktarý
#define BASLANGIC_SKOR_MIKTAR    10        // Oyuncu Kayýt olduðunada gelcek Skor miktarý
#define BASLANGIC_ASEVIYE_MIKTAR 31        // Oyuncu Kayýt olduðunada gelcek aranma seviyesi
#define MAX_PING                 1000       // Maksimum Ping Miktarý
#define MAX_LEVEL                5         // Maksimum Yönetici Seviyesi
#define MAX_UYARI                3         // /uyar komudundaki uyarý miktarý
#define SKOR_KAYIT               true      // true = Skoru kayýt eder, false = Skor kayýt etmez
#define SKIN_KAYIT               true      // true = Parayý kayýt eder, false = Parayý kayýt etmez
#define ASEVIYE_KAYIT            true      // true = Aranma seviyesini kayýt eder, false = Aranma seviyesini kayýt etmez.
#define GIRIS_LOG_GOSTER         false     // true = Giriþte bilgileri gösterir, false = Giriþte bilgileri göstermez
#define ZORUNLU_GIRIS            true      // true = Oyuncu Pawn Olmasý için giriþ yapmalý, false = Giriþ yapmadanda spawn olabilir.
#define MAX_HIZ                  321       // Gidilebilecek maksimum hýz (320.974902 infernus)
#define MAX_KONTROL              5         // Hilelerde Banlanmasý için kaç kere kontrol edileceðidir Örnek: Hýz hilesi
#define HILE_SEVIYE              10         // Hile Yapabilecek minimum yönetici seviyesi
//#error Lutfen Defineleri Kendinize gore duzenleyin. (daha sonra 67. Satiri Silin)
//==================================================[Diðer Ayarlamalar]==================================================
#define HATALI_KOMUT  "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Hatalý bir komut girdiniz.  {555555}))" // Hatalý komut yazýsý.
#define YONETICI_MEKAN_POS 1825.4650,-1271.8357,120.2661 // Yönetici mekanýnýn pozisyonu
#define YONETICI_MEKAN_INT 0                             // Yönetici mekanýnýn Interior IDsi
#define YONETICI_MEKAN_VW 0                              // Yönetici mekanýnýn Virtual World IDsi
#define MAX_CLASS 300                                    // Maksimum Class sayýsý
//--------------------------------------------[-Ayarlamalar-]--------------------------------------------//
#define H_LOG_DOSYA "/Hadmin/Hlog.HackHerS"
#define PLAYER_AIRBRAKE 1     // OnPlayerCheat public'i için
#define PLAYER_JETPACK 2      // OnPlayerCheat public'i için
#define PLAYER_SILAH 3        // OnPlayerCheat public'i için
#define PLAYER_PARA 4         // OnPlayerCheat public'i için
#define PLAYER_HIZ 5          // OnPlayerCheat public'i için
#define PLAYER_FLY 6          // OnPlayerCheat public'i için
//--------------------------------------------[-Macrolar-]--------------------------------------------//
#define H_HileDuyurusuEx(%0,%1) do{new _string[256]; format(_string,sizeof(_string),%0,%1); H_HileDuyurusu(_string);} while(FALSE) // Double-o-Seven
#define H_LogEx(%0,%1) do{new _string[256]; format(_string,sizeof(_string),%0,%1); H_Log(_string);} while(FALSE) // Double-o-Seven

//--------------------------------------------[Yazý Renk Baþlangýç]--------------------------------------------//
#define yKirmizi 		"{F81414}"

#define yAcikMavi   	"{00C0FF}"

#define yAcikKirmizi    "{FFA1A1}"

#define yYesil       	"{6EF83C}"

#define BilgiRenk       0x3A79C5FF

#define SunucuDuyuru    0xFF9900FF

#define Kirmizi         0xF81414FF

#define AcikYesil       0x4DE718FF
//--------------------------------------------[Yazý Renk Bitti]--------------------------------------------//
//--------------------------------------------[Dialog Baþlangýç]--------------------------------------------//
#define DIALOG_Kayit      10000

#define DIALOG_Kayit_REQ  10001

#define DIALOG_Giris      10002

#define DIALOG_Giris2     10003

#define DIALOG_LOG_BASAR  10004

#define DIALOG_LOG        10005

#define DIALOG_STATLAR    10006

#define DIALOG_HMENU      10007

#define DIALOG_CONSOLE    10045
//--------------------------------------------[Dialog Bitiþ]--------------------------------------------//
//--------------------------------------------[Sürüm - Yapýmcý]--------------------------------------------//
#define INCLUDE	"Hadmin"
#define DEVELOPER "Sarp Aykent"
#define VERSION	"v0.1a"
#define GUNCELLEME	"20 Ocak 2011"
#define GUNCELLEME_ICERIK "Çýkýþ sürümü"
//--------------------------------------------[Sürüm - Yapýmcý]--------------------------------------------//
//--------------------------------------------[Enumlar Baþlangýç]--------------------------------------------//
enum oBilgi
{
	Admin,
	Vip,
	Para,
	Skor,
	KTarih[ 15 + 10 ],
	Skin,
	God,
	GodCar,
	Sus,
	Hapis,
	Banlandi,
	pArac,
	Ycalisma,
	Donmama,
	aSeviye,
	JetPack,
	Uyari,
	Hiz,
	AirBrake,
	Fly,
};

new saniye = 0, saniyeT, SunucuGuncelle = 0;

new OyuncuVeri[MAX_PLAYERS][oBilgi];

static
	Float:Zdegisimi[MAX_PLAYERS],
	Isinlandi[MAX_PLAYERS],
	bool:HoPT,
	bool:HoPU,
	bool:HoPC,
	bool:HoPCo,
	bool:HoPDi,
	bool:HoPD,
	bool:HoPS,
	bool:HoPSC,
	bool:HoPUP,
	bool:HoPIC,
	bool:HoPDR,
	bool:HoPKSC;



static  // wups
	bool:OyuncuSilahlari[MAX_PLAYERS][47],
	bool:Spawnlandi[MAX_PLAYERS],
	WeaponPickup[MAX_PICKUPS],
	ClassSilahlari[MAX_CLASS][3],
	OyuncuClasslari[MAX_PLAYERS];


new
	Float:Jx[MAX_PLAYERS],
	Float:Jy[MAX_PLAYERS],
	Float:Jz[MAX_PLAYERS],
	JT[MAX_PLAYERS];
//--------------------------------------------[EnumLar Bitiþ]--------------------------------------------//
//--------------------------------------------[Forward Baþlangýç]--------------------------------------------//
forward SunucuGuncelleme();
forward AraciSil(vehicleid);
forward SilmeyiTamamla(vehicleid);
forward AracSpawnla(playerid, model);
forward H_OnGameModeInit();
forward H_Ban(playerid, neden[]);
forward H_Kick(playerid, neden[]);
forward H_OnPlayerSpawn(playerid);
forward H_OnPlayerUpdate(playerid);
forward H_OnPlayerConnect(playerid);
forward H_OnPlayerText(playerid, text[]);
forward H_OnPlayerDisconnect(playerid,reason);
forward H_OnPlayerPickUpPickup(playerid,pickupid);
forward H_OnPlayerDeath(playerid, killerid, reason);
forward H_OnPlayerStateChange(playerid, newstate, oldstate);
forward H_OnPlayerInteriorChange(playerid,newinteriorid,oldinteriorid);
forward H_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
//--------------------------------------------[Forward Bitiþ]--------------------------------------------//
//public OnFilterScriptInit( )	return 1;
//public OnFilterScriptExit( )	return 1;

new AracIsimleri[212][] = {
{"Landstalker"},{"Bravura"},{"Buffalo"},{"Linerunner"},{"Perrenial"},{"Sentinel"},{"Dumper"},
{"Firetruck"},{"Trashmaster"},{"Stretch"},{"Manana"},{"Infernus"},{"Voodoo"},{"Pony"},{"Mule"},
{"Cheetah"},{"Ambulance"},{"Leviathan"},{"Moonbeam"},{"Esperanto"},{"Taxi"},{"Washington"},
{"Bobcat"},{"Mr Whoopee"},{"BF Injection"},{"Hunter"},{"Premier"},{"Enforcer"},{"Securicar"},
{"Banshee"},{"Predator"},{"Bus"},{"Rhino"},{"Barracks"},{"Hotknife"},{"Trailer 1"},{"Previon"},
{"Coach"},{"Cabbie"},{"Stallion"},{"Rumpo"},{"RC Bandit"},{"Romero"},{"Packer"},{"Monster"},
{"Admiral"},{"Squalo"},{"Seasparrow"},{"Pizzaboy"},{"Tram"},{"Trailer 2"},{"Turismo"},
{"Speeder"},{"Reefer"},{"Tropic"},{"Flatbed"},{"Yankee"},{"Caddy"},{"Solair"},{"Berkley's RC Van"},
{"Skimmer"},{"PCJ-600"},{"Faggio"},{"Freeway"},{"RC Baron"},{"RC Raider"},{"Glendale"},{"Oceanic"},
{"Sanchez"},{"Sparrow"},{"Patriot"},{"Quad"},{"Coastguard"},{"Dinghy"},{"Hermes"},{"Sabre"},
{"Rustler"},{"ZR-350"},{"Walton"},{"Regina"},{"Comet"},{"BMX"},{"Burrito"},{"Camper"},{"Marquis"},
{"Baggage"},{"Dozer"},{"Maverick"},{"News Chopper"},{"Rancher"},{"FBI Rancher"},{"Virgo"},{"Greenwood"},
{"Jetmax"},{"Hotring"},{"Sandking"},{"Blista Compact"},{"Police Maverick"},{"Boxville"},{"Benson"},
{"Mesa"},{"RC Goblin"},{"Hotring Racer A"},{"Hotring Racer B"},{"Bloodring Banger"},{"Rancher"},
{"Super GT"},{"Elegant"},{"Journey"},{"Bike"},{"Mountain Bike"},{"Beagle"},{"Cropdust"},{"Stunt"},
{"Tanker"}, {"Roadtrain"},{"Nebula"},{"Majestic"},{"Buccaneer"},{"Shamal"},{"Hydra"},{"FCR-900"},
{"NRG-500"},{"HPV1000"},{"Cement Truck"},{"Tow Truck"},{"Fortune"},{"Cadrona"},{"FBI Truck"},
{"Willard"},{"Forklift"},{"Tractor"},{"Combine"},{"Feltzer"},{"Remington"},{"Slamvan"},
{"Blade"},{"Freight"},{"Streak"},{"Vortex"},{"Vincent"},{"Bullet"},{"Clover"},{"Sadler"},
{"Firetruck LA"},{"Hustler"},{"Intruder"},{"Primo"},{"Cargobob"},{"Tampa"},{"Sunrise"},{"Merit"},
{"Utility"},{"Nevada"},{"Yosemite"},{"Windsor"},{"Monster A"},{"Monster B"},{"Uranus"},{"Jester"},
{"Sultan"},{"Stratum"},{"Elegy"},{"Raindance"},{"RC Tiger"},{"Flash"},{"Tahoma"},{"Savanna"},
{"Bandito"},{"Freight Flat"},{"Streak Carriage"},{"Kart"},{"Mower"},{"Duneride"},{"Sweeper"},
{"Broadway"},{"Tornado"},{"AT-400"},{"DFT-30"},{"Huntley"},{"Stafford"},{"BF-400"},{"Newsvan"},
{"Tug"},{"Trailer 3"},{"Emperor"},{"Wayfarer"},{"Euros"},{"Hotdog"},{"Club"},{"Freight Carriage"},
{"Trailer 3"},{"Andromada"},{"Dodo"},{"RC Cam"},{"Launch"},{"Police Car (LSPD)"},{"Police Car (SFPD)"},
{"Police Car (LVPD)"},{"Police Ranger"},{"Picador"},{"S.W.A.T. Van"},{"Alpha"},{"Phoenix"},{"Glendale"},
{"Sadler"},{"Luggage Trailer A"},{"Luggage Trailer B"},{"Stair Trailer"},{"Boxville"},{"Farm Plow"},
{"Utility Trailer"}
};

forward ParsePlayerPass( playerid, name[ ], value[ ] );
public ParsePlayerPass( playerid, name[ ], value[ ] )
{
    if ( !strcmp( name, "Sifre" ) )
    {
        SetPVarString( playerid, "pPass", value );
    }
}

forward LoadUser( playerid, name[ ], value[ ] );
public LoadUser( playerid, name[ ], value[ ] )
{
    if ( !strcmp(name, "Kayit_Tarih" ) ) strmid(OyuncuVeri[playerid][KTarih], value, 0, strlen(value), 50);

    if ( !strcmp(name, "Para" ) ) OyuncuVeri[playerid][Para] = strval( value );
	#if SKOR_KAYIT == true
    if ( !strcmp(name, "Skor" ) ) OyuncuVeri[playerid][Skor] = strval( value );
    #endif
    #if SKIN_KAYIT == true
    if ( !strcmp(name, "Skin" ) ) OyuncuVeri[playerid][Skin] = strval( value );
    #endif
    #if ASEVIYE_KAYIT == true
    if ( !strcmp(name, "Aranma" ) ) OyuncuVeri[playerid][aSeviye] = strval( value );
    #endif
    if ( !strcmp(name, "Admin" ) ) OyuncuVeri[playerid][Admin] = strval( value );
    if ( !strcmp(name, "Vip" ) ) OyuncuVeri[playerid][Vip] = strval( value );
    if ( !strcmp(name, "Hapis" ) ) OyuncuVeri[playerid][Hapis] = strval( value );
    if ( !strcmp(name, "Banlandi" ) ) OyuncuVeri[playerid][Banlandi] = strval( value );
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch( dialogid )
	{
	    case DIALOG_Kayit:
	    {
	        if ( response )
	        {
	            if ( sscanf( inputtext, "s[21]", inputtext[ 0 ] || strlen( inputtext[ 0 ] ) == 0 ) )
	                return ShowPlayerDialog( playerid, DIALOG_Kayit, DIALOG_STYLE_INPUT, "{33AA33}.:[Kayýt]:. {FFFFFF}Þifre", ""yKirmizi"* {555555}((  {FF0000}.:[HATA]:. {FFFFFF}Þifre boþ olamaz.{555555}))\n\
																							{FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Lütfen kullanmak istediðiniz þifreyi girin.{555555}))\n",
																							">>>", "Çýkýþ");
        		if ( strlen( inputtext[ 0 ] ) < 3 || strlen( inputtext[ 0 ] ) > 20 )
	                return ShowPlayerDialog( playerid, DIALOG_Kayit, DIALOG_STYLE_INPUT, "{33AA33}.:[Kayýt]:. {FFFFFF}Þifre", ""yKirmizi"* {555555}((  {FF0000}.:[HATA]:. {FFFFFF}Þifre uzunluðunuz Kýsa veya Uzun.{555555}))\n\
																							{FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Þifre uzunluðu 3-20 arasýnda olmalýdýr..  {555555}))\n",
																							">>>", "Çýkýþ");
				new
					PlayerFile[ 19 + MAX_PLAYER_NAME ],
					pDate[ 8 + 15 ], //HH:MM:SS + DD.MM.YYYY = 18
					pYear,
					pMonth,
					pDay,
					pHour,
					pMinute,
					pSecond,
					pIP[ 20 ],
					InfBox[ 512 ]
				;
				getdate(pYear, pMonth, pDay ),gettime(pHour, pMinute, pSecond );
				GetPlayerIp( playerid, pIP, 20 );

				format( PlayerFile , sizeof PlayerFile, "Hadmin/Hesaplar/%s.ini", Encode( pName( playerid ) ) );
				format( pDate, sizeof pDate, "%d:%d:%d  %d/%d/%d",pHour, pMinute, pSecond , pDay, pMonth, pYear );
			    format( InfBox, sizeof InfBox, "{FFFFFF}Hesabýnýz baþarýyla yaratýldý!\n\n\
			                                            "yAcikMavi"Hesap: {FFFFFF}%s\n\
			                                            "yAcikMavi"Þifre: {FFFFFF}%s\n\n\
			                                            {FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Kayýt olduðunuz için"yYesil" %dTL{FFFFFF} aldýnýz.  {555555}))\n\
			                                            {FFFFFF}* {555555}((  {800080}.:[SORU]:. {FFFFFF}Giriþ yapmak istermisiniz?   {555555}))", pName( playerid ),
																				 			 inputtext,
					                                                                         BASLANGIC_PARA_MIKTAR);
				ShowPlayerDialog( playerid, DIALOG_LOG, DIALOG_STYLE_MSGBOX, "{33AA33}.:[Giriþ]:.", InfBox, "Evet", "Hayýr" );

				new
					INI:PlayerAcc = INI_Open( PlayerFile );

                INI_WriteString( PlayerAcc, "Isim",				  pName( playerid )	   );
			 	INI_WriteString( PlayerAcc, "Sifre", 		  inputtext 	           );
				INI_WriteString( PlayerAcc, "Kayit_Tarih", 		  pDate 			   );
				INI_WriteInt( PlayerAcc,    "Para",             BASLANGIC_PARA_MIKTAR  );
				#if SKOR_KAYIT == true
				INI_WriteInt( PlayerAcc,    "Skor",             BASLANGIC_SKOR_MIKTAR  );
				#endif
				#if SKIN_KAYIT == true
				INI_WriteInt( PlayerAcc,    "Skin",             0 );
				#endif
				#if ASEVIYE_KAYIT == true
				INI_WriteInt( PlayerAcc,    "Aranma",             0 );
				#endif
				INI_WriteInt( PlayerAcc,    "Admin",            0  );
				INI_WriteInt( PlayerAcc,    "Vip",            0  );
				INI_WriteInt( PlayerAcc,    "Hapis",            0  );
				INI_WriteInt( PlayerAcc,    "Banlandi",            0  );
				INI_Close( PlayerAcc );

				//SetPVarString( playerid, "Kayit_Tarih", pDate );
				strmid(OyuncuVeri[playerid][KTarih], pDate, 0, sizeof(pDate), 50);
				SetPVarInt( playerid, "Gyapti", 0 );
				GivePlayerMoneyEx( playerid, BASLANGIC_PARA_MIKTAR );
				SetPlayerScoreEx( playerid, BASLANGIC_SKOR_MIKTAR );
				SetPlayerWantedLevelEx( playerid, BASLANGIC_ASEVIYE_MIKTAR );
			}
		}
		case DIALOG_Kayit_REQ:
		{
		    if ( response ) cmd_kayit( playerid, "");
		    if ( !response ) return 0;

		}

		case DIALOG_Giris:
		{
		if ( response )
  			return ShowPlayerDialog( playerid, DIALOG_Giris2, DIALOG_STYLE_INPUT, "{33AA33}.:[Giriþ]:. {FFFFFF}Þifre", 	""yKirmizi"{FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Lütfen kullanmakta olduðunuz þifreyi girin.{555555}))\n",
																												"Giriþ", "Çýkýþ");

		else return SendHataMessage(playerid, "Sunucuya girmek için giriþ yapmak zorunludur."), Kick(playerid);
		}
		
		case DIALOG_LOG:
		{
		    if ( response )
			        ShowPlayerDialog( playerid, DIALOG_Giris2, DIALOG_STYLE_INPUT, "{33AA33}.:[Giriþ]:. {FFFFFF}Þifre", 	""yKirmizi"{FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Lütfen kullanmakta olduðunuz þifreyi girin.{555555}))\n",
																												"Giriþ", "Çýkýþ");
			else
			    return SendHataMessage(playerid, "Sunucuya girmek için giriþ yapmak zorunludur."), Kick(playerid);
		}
		case DIALOG_Giris2:
		{
		    if ( !response ) return Kick( playerid );
		    if ( response )
		    {
			    if ( strlen( inputtext ) == 0 )
			        return ShowPlayerDialog( playerid, DIALOG_Giris2, DIALOG_STYLE_INPUT, "{33AA33}.:[Giriþ]:. {FFFFFF}Þifre", 	""yKirmizi"* {555555}((  {FF0000}.:[HATA]:. {FFFFFF}Þifre boþ olamaz.{555555}))\n\
																							{FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Lütfen kullanmakta olduðunuz þifreyi girin.{555555}))\n",
																												"Giriþ", "Çýkýþ");
			    new
					PlayerFile[ 13 + MAX_PLAYER_NAME ],
					Password[ 20 + 1 ]
				;
			    format( PlayerFile , sizeof PlayerFile, "Hadmin/Hesaplar/%s.ini", Encode( pName( playerid ) ) );
		        INI_ParseFile( PlayerFile, "ParsePlayerPass", false, true, playerid );
		        GetPVarString( playerid, "pPass", Password, sizeof Password );

		        if ( !strcmp ( inputtext, Password, false ) )
	        	{
					SetPVarInt( playerid, "Gyapti", 1 );
					format( PlayerFile , sizeof PlayerFile, "Hadmin/Hesaplar/%s.ini", Encode( pName( playerid ) ) );
	        	    INI_ParseFile( PlayerFile, "LoadUser", false, true, playerid, true, false );
					#if SKOR_KAYIT == true
					SetPlayerScoreEx( playerid, OyuncuVeri[playerid][Skor]  );
					#endif
					#if ASEVIYE_KAYIT == true
					SetPlayerWantedLevelEx( playerid, OyuncuVeri[playerid][aSeviye]);
					#endif
					if(OyuncuVeri[playerid][Banlandi] == 1)
					{
					SendBilgiMessage(playerid, "Bu hesap yasaklanmýþ bu yüzden otomatik olarak yasaklandýnýz.");
					H_Ban(playerid, "Yasaklanmýþ hesap");
					return 1;
					}
					new Yazi[128];
					if(OyuncuVeri[playerid][Admin] != 0)
					format(Yazi, sizeof(Yazi), "%d Seviye yönetici olarak giriþ yaptýnýz.", OyuncuVeri[playerid][Admin]),
					SendBilgiMessage(playerid, Yazi);
					#if GIRIS_LOG_GOSTER == true
	    			new
						sTitle[ 21 + MAX_PLAYER_NAME + 25 ],
						sBoxInfo[ 512 ]
					;
	        	    //GetPVarString( playerid, "Kayit_Tarih", Pdata, 8 + 10 );
	        	    format( sTitle, sizeof sTitle, "{FFFFFF}Yeniden hoþgeldiniz, "yAcikMavi"%s{FFFFFF}!", pName( playerid ) );
	        	    format( sBoxInfo, sizeof sBoxInfo, "{FFFFFF}Sizin bilgileriniz:\n\n\
	        	                                        {FFFFFF}Bakiye: "yAcikMavi"%d\n\
	        	                                        {FFFFFF}Skor: "yAcikMavi"%d\n\
	        	                                        {FFFFFF}Kayýt tarihi: "yAcikMavi"%s\n\
														{FFFFFF}Skin: "yAcikMavi"%d",  OyuncuVeri[playerid][Para],
							       											OyuncuVeri[playerid][Skor],
											    						    OyuncuVeri[playerid][KTarih],
																			GetPlayerSkinEx(playerid) );
					ShowPlayerDialog(playerid, DIALOG_LOG_BASAR, DIALOG_STYLE_MSGBOX, sTitle, sBoxInfo, "Ok", "");
					#endif

	        	}
	        	else ShowPlayerDialog(playerid, DIALOG_Giris2, DIALOG_STYLE_INPUT, "{FF0000}.:[HATA]:.", "* {555555}((  {FF0000}.:[HATA]:. {FFFFFF}Hatalý þifre girdiniz.{555555}))\n{FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Lütfen doðru þifrenizi girerek giriþ yapýnýz.{555555}))", "Giriþ", "Çýkýþ");
        	}
		}
		case DIALOG_HMENU:
		{
		    if(!response)
		    return TogglePlayerControllableEx(playerid,true);
			if(listitem == 0) //Sunucu Havasý
			{
			if(OyuncuVeri[playerid][Admin] < 3)
			return HataVer(playerid, 1);

			return ShowPlayerDialog(playerid, DIALOG_HMENU+1, DIALOG_STYLE_LIST,
			"Sunucu Havasý", "Mavi Gökyüzü\nKum Fýrtýnasý\nÞimþek Fýrtýnasý\nSisli\nBulutlu\nFýrtýna\nMor Gökyüzü\nSiyah/Beyaz Gökyüzü\nSiyah, yeþil Hava\nKuru Hava", "Select", "Back") &&
			TogglePlayerControllableEx(playerid,true);

			}
			//==================[Sunucu Zamaný]==================
			if(listitem == 1)
			{
			if(OyuncuVeri[playerid][Admin] < 3)
			return HataVer(playerid, 1);

			return ShowPlayerDialog(playerid, DIALOG_HMENU+2, DIALOG_STYLE_LIST,
			"Sunucu Zamaný", "Sabah\nÖðlen\nÖðlenden sonra\nAkþam\nGece", "Select", "Back") &&
			TogglePlayerControllableEx(playerid,true);
			}
			//==================[Araçlar]==================
			if(listitem == 2)
			{
			if(OyuncuVeri[playerid][Admin] < 3)
			return HataVer(playerid, 1);

 			if(IsPlayerInAnyVehicle(playerid))
	   	    return TogglePlayerControllableEx(playerid,true) && SendHataMessage(playerid,"Zaten aracýnýz var.");
        	else
			{
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			}

            }
			//==================[Modifiye Menu]==================
			if(listitem == 3)
		    {
			if(OyuncuVeri[playerid][Admin] < 3)
			return HataVer(playerid, 1);

			if(IsPlayerInAnyVehicle(playerid))
			{

			new HVehicleID = GetPlayerVehicleID(playerid), HModel = GetVehicleModel(HVehicleID);
		    switch(HModel)
			{
				case 448,461,462,463,468,471,509,510,521,522,523,581,586,449:
				{
				SendHataMessage(playerid,"Bu aracý modifiye edemezsiniz");
				TogglePlayerControllableEx(playerid,true);
				return 1;
				}
			}
			TogglePlayerControllableEx(playerid,true);
            ShowPlayerDialog(playerid, DIALOG_HMENU+24, DIALOG_STYLE_LIST, "Modifiye Menüsü",
	  	    "NOS\nHidrolik\nTekerlekler\nDýþ Görünüm\nRenkler", "Seç", "Geri");
		    }
			else
			{
			SendHataMessage(playerid,"Araçta deðilsiniz");
			TogglePlayerControllableEx(playerid,true);
			}

			}
			//==================[Silahlar]==================
			if(listitem == 4)
			{
			if(OyuncuVeri[playerid][Admin] < 3)
			return HataVer(playerid, 1);

        	TogglePlayerControllableEx(playerid,true);
			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			}
  		}
		case DIALOG_HMENU+1:
  		{
			new string[128];
			switch(response)
			{
			    case 0:
				{
		    	ShowPlayerDialog(playerid, DIALOG_HMENU, DIALOG_STYLE_LIST, "Hadmin Anamenü",
			    "Sunucu Havasý\nSunucu Zamaný\nAraç\nModifiye Menüsü\nSilahlar", "Seç","Ýptal");
				}
	            case 1:
				{
	   			switch(listitem)
	   			{
	   			    case 0:
				    {
						 SetWeather(5);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
		            case 1:
					{
		 	        	 SetWeather(19);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
					case 2:
					{
						 SetWeather(8);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }

					case 3:
					{
		 	             SetWeather(20);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
					case 4:
					{
		 	             SetWeather(9);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
					case 5:
					{
		 	             SetWeather(16);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
					case 6:
					{
		 	             SetWeather(45);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
					case 7:
					{
		 	             SetWeather(44);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
		  			case 8:
					{
		 	             SetWeather(22);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
		            case 9:
					{
		 	             SetWeather(11);
				 		 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Havayý deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
				}
	            }
	  		}
  		}
		case DIALOG_HMENU+2:
  		{
			new string[128];
			switch(response)
			{
			    case 0:
				{
		    	ShowPlayerDialog(playerid, DIALOG_HMENU, DIALOG_STYLE_LIST, "Hadmin Anamenü",
			    "Sunucu Havasý\nSunucu Zamaný\nAraç\nModifiye Menüsü\nSilahlar", "Seç","Ýptal");
				}
	            case 1:
				{
	   			switch(listitem)
	   			{
	   			    case 0:
				    {
						 for(new i = 0; i < MAX_PLAYERS; i++)
						 if(IsPlayerConnected(i))
						 SetPlayerTime(i,7,0);
						 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Sunucu Saatini deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
		            case 1:
					{
						 for(new i = 0; i < MAX_PLAYERS; i++)
						 if(IsPlayerConnected(i))
						 SetPlayerTime(i,12,0);
						 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Sunucu Saatini deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
					case 2:
					{
						 for(new i = 0; i < MAX_PLAYERS; i++)
						 if(IsPlayerConnected(i))
						 SetPlayerTime(i,16,0);
						 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Sunucu Saatini deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }

					case 3:
					{
						 for(new i = 0; i < MAX_PLAYERS; i++)
						 if(IsPlayerConnected(i))
						 SetPlayerTime(i,20,0);
						 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Sunucu Saatini deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
					case 4:
					{
						 for(new i = 0; i < MAX_PLAYERS; i++)
						 if(IsPlayerConnected(i))
						 SetPlayerTime(i,0,0);
						 PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
			    		 format(string, sizeof(string),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, Sunucu Saatini deðiþtirdi. {555555}))",pName(playerid));
						 SendClientMessageToAll(0xFFFFFFFF, string);
		            }
				}
	            }
	  		}
  		}
  		case DIALOG_HMENU+3:
  		{
		    switch(response)
			{
				case 0:
			  	ShowPlayerDialog(playerid, DIALOG_HMENU, DIALOG_STYLE_LIST, "Hadmin Anamenü",
	   			"Sunucu Havasý\nSunucu Zamaný\nAraç\nModifiye Menüsü\nSilahlar", "Seç","Ýptal");
			    case 1:
			    {
				if(listitem == 0){ ShowPlayerDialog(playerid, DIALOG_HMENU+4, DIALOG_STYLE_LIST, "Bisikletler", "Bisiklet\nBMX\nDað Bisikleti", "Seç", "Geri");}
				if(listitem == 1){ ShowPlayerDialog(playerid, DIALOG_HMENU+5, DIALOG_STYLE_LIST, "Motorlar", "NRG-500\nFaggio\nFCR-900\nPCJ-600\nFreeway\nBF-400\nPizzaBoy\nWayfarer\nCop Bike\nSanchez\nQuad", "Seç", "Geri");}
				if(listitem == 2){ ShowPlayerDialog(playerid, DIALOG_HMENU+6, DIALOG_STYLE_LIST, "4x4ler", "Dumper\nDuneride\nMonster\nMonster A\nMonster B", "Seç", "Geri");}
		 		if(listitem == 3){ ShowPlayerDialog(playerid, DIALOG_HMENU+7, DIALOG_STYLE_LIST, "Botlar", "Coastguard\nDinghy\nJetmax\nLaunch\nMarquis\nPredator\nReefer\nSpeeder\nSqualo\nTropic", "Seç", "Geri");}
				if(listitem == 4){ ShowPlayerDialog(playerid, DIALOG_HMENU+8, DIALOG_STYLE_LIST, "Helikopterler", "Cargobob\nHunter\nLeviathn\nMaverick\nPolmav\nRaindanc\nSeasparr\nSparrow\nVCN Helicopter", "Seç", "Geri");}
				if(listitem == 5){ ShowPlayerDialog(playerid, DIALOG_HMENU+9, DIALOG_STYLE_LIST, "Uçaklar", "Hydra\nRustler\nDodo\nNevada\nSuntplane\nCropdust\nAT-400\nAndromeda\nBeagle\nVortex\nSkimmer\nShamal", "Seç", "Geri");}
				if(listitem == 6){ ShowPlayerDialog(playerid, DIALOG_HMENU+10, DIALOG_STYLE_LIST, "Arabalar", "Yavaþ Araçlar\nSokak Yarýþ Araçlarý\nKas Araçlarý\nSuvs & Wagons\nSpor Araçlar\nKüçük araçlar\nSivil Araçlar\nDevlet Araçlarý\n4 Kapýlý Araçlar\n2 Kapýlý Araçlar\nBüyük Kamyonetler\nKüçük araçlar", "Seç", "Geri");}
				if(listitem == 7){ ShowPlayerDialog(playerid, DIALOG_HMENU+11, DIALOG_STYLE_LIST, "Minyatür araçlar","RC Goblin\nRC Raider\nRC Barron \nRC Bandit\nRC Cam\nRC Tiger", "Seç", "Geri");}
				}
			}
  		}
  		case DIALOG_HMENU+4:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
			if(listitem == 0){ AracSpawnla(playerid,509);}
			if(listitem == 1){ AracSpawnla(playerid,481);}
			if(listitem == 2){ AracSpawnla(playerid,510);}
			TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+5:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	  		if(listitem == 0){AracSpawnla(playerid,522);}
	  		if(listitem == 1){AracSpawnla(playerid,462);}
	  		if(listitem == 2){AracSpawnla(playerid,521);}
	  		if(listitem == 3){AracSpawnla(playerid,461);}
	  		if(listitem == 4){AracSpawnla(playerid,463);}
	  		if(listitem == 5){AracSpawnla(playerid,581);}
	  		if(listitem == 6){AracSpawnla(playerid,448);}
	  		if(listitem == 7){AracSpawnla(playerid,586);}
	  		if(listitem == 8){AracSpawnla(playerid,523);}
	  		if(listitem == 9){AracSpawnla(playerid,468);}
	  		if(listitem == 10){AracSpawnla(playerid,471);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+6:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	  		if(listitem == 0){ AracSpawnla(playerid,406);}
	  		if(listitem == 1){ AracSpawnla(playerid,573);}
	  		if(listitem == 2){ AracSpawnla(playerid,444);}
	  		if(listitem == 3){ AracSpawnla(playerid,556);}
	  		if(listitem == 4){ AracSpawnla(playerid,557);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+7:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	  		if(listitem == 0){ AracSpawnla(playerid,472);}
	    	if(listitem == 1){ AracSpawnla(playerid,473);}
	    	if(listitem == 2){ AracSpawnla(playerid,493);}
	    	if(listitem == 3){ AracSpawnla(playerid,595);}
	    	if(listitem == 4){ AracSpawnla(playerid,484);}
	    	if(listitem == 5){ AracSpawnla(playerid,430);}
	    	if(listitem == 6){ AracSpawnla(playerid,453);}
	    	if(listitem == 7){ AracSpawnla(playerid,452);}
	    	if(listitem == 8){ AracSpawnla(playerid,446);}
	    	if(listitem == 9){ AracSpawnla(playerid,454);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+8:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	  		if(listitem == 0){ AracSpawnla(playerid,548);}
	  		if(listitem == 1){ AracSpawnla(playerid,425);}
	  		if(listitem == 2){ AracSpawnla(playerid,417);}
		    if(listitem == 3){ AracSpawnla(playerid,487);}
		    if(listitem == 4){ AracSpawnla(playerid,497);}
	  		if(listitem == 5){ AracSpawnla(playerid,563);}
	  		if(listitem == 6){ AracSpawnla(playerid,447);}
	  		if(listitem == 7){ AracSpawnla(playerid,469);}
			if(listitem == 8){ AracSpawnla(playerid,488);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+9:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,520);}
	        if(listitem == 1){ AracSpawnla(playerid,476);}
	        if(listitem == 2){ AracSpawnla(playerid,593);}
	        if(listitem == 3){ AracSpawnla(playerid,553);}
	        if(listitem == 4){ AracSpawnla(playerid,513);}
	        if(listitem == 5){ AracSpawnla(playerid,512);}
	        if(listitem == 6){ AracSpawnla(playerid,577);}
	        if(listitem == 7){ AracSpawnla(playerid,592);}
	        if(listitem == 8){ AracSpawnla(playerid,511);}
	        if(listitem == 9){ AracSpawnla(playerid,539);}
	        if(listitem == 10){ AracSpawnla(playerid,460);}
	        if(listitem == 11){ AracSpawnla(playerid,519);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+10:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
	        {
			if(listitem == 0){ ShowPlayerDialog(playerid, DIALOG_HMENU+12, DIALOG_STYLE_LIST, "Yavaþ Araçlar", "Blade\nBroadway\nRemmington\nSavanna\nSlamvan\nTornado\nVoodoo", "Select", "Back");}
			if(listitem == 1){ ShowPlayerDialog(playerid, DIALOG_HMENU+13, DIALOG_STYLE_LIST, "Sokak Yarýþ Araçlarý","Elegy\nFlash\nJester\nStratum\nSultan\nUranus", "Select", "Back");}
			if(listitem == 2){ ShowPlayerDialog(playerid, DIALOG_HMENU+14, DIALOG_STYLE_LIST, "Kas Araçlarý", "Buffalo\nClover\nPhoenix\nSabre", "Select", "Back");}
	 		if(listitem == 3){ ShowPlayerDialog(playerid, DIALOG_HMENU+15, DIALOG_STYLE_LIST, "Suvs & Wagons", "Huntley\nLandstalker\nPerenial\nRancher\nRegina\nRomero\nSolair", "Select", "Back");}
			if(listitem == 4){ ShowPlayerDialog(playerid, DIALOG_HMENU+16, DIALOG_STYLE_LIST, "Spor Araçlar", "Banshee\nBullet\nCheetah\nComet\nHotknife\nHotring Racer\nInfernus\nSuper GT\nTurismo\nWindsor\nZR-350", "Select", "Back");}
			if(listitem == 5){ ShowPlayerDialog(playerid, DIALOG_HMENU+17, DIALOG_STYLE_LIST, "Küçük araçlar", "Bandito\nBF Injection\nBloodring Banger\nCaddy\nCamper\nJourney\nKart\nMesa\nSandking\nVortex", "Select", "Back");}
			if(listitem == 6){ ShowPlayerDialog(playerid, DIALOG_HMENU+18, DIALOG_STYLE_LIST, "Sivil Araçlar", "Baggage\nBus\nCabbie\nCoach\nSweeper\nTaxi\nTowtruck\nTrashmaster\nUtiliy van", "Select", "Back");}
			if(listitem == 7){ ShowPlayerDialog(playerid, DIALOG_HMENU+19, DIALOG_STYLE_LIST, "Devlet Araçlarý", "Ambulance\nBarracks\nEnforcer\nFBI Rancher\nFBI Truck\nFiretruck\nPatriot\nPolite Car SF\nRanger\nSecuricar\nS.W.A.T", "Select", "Back");}
			if(listitem == 8){ ShowPlayerDialog(playerid, DIALOG_HMENU+20, DIALOG_STYLE_LIST, "4 Kapýlý Araçlar", "Admiral\nElegant\nEmperor\nEuros\nGlendale\nGreenwood\nIntruder\nMerit\nNebula\nOceanic\nPremier\nPrimo\nSentinel\nStretch\nSunrise\nTahoma\nVincent\nWashington\nWillard", "Select", "Back");}
			if(listitem == 9){ ShowPlayerDialog(playerid, DIALOG_HMENU+21, DIALOG_STYLE_LIST, "2 Kapýlý Araçlar", "Alpha\nBlista Compact\nBravura\nBaccaneer\nCadrona\nClub\nEsperanto\nFeltzer\nFortune\nHermer\nHustler\nMagestic\nManana\nPicador\nPrevion\nStafford\nStallion\nTampa\nVirgo", "Select", "Back");}
			if(listitem == 10){ ShowPlayerDialog(playerid, DIALOG_HMENU+22, DIALOG_STYLE_LIST, "Büyük Kamyonetler", "Benson\nBoxville\nCement truck\nCombine Harvester\nDFT-30\nDozer\nFlatbed\nHotdog\nLinerunner\nMr Whoopee\nMule\nPacker\nRoadtrain\nTanker\nTractor\nYankee", "Select", "Back");}
	 		if(listitem == 11){ ShowPlayerDialog(playerid, DIALOG_HMENU+23, DIALOG_STYLE_LIST, "Küçük araçlar", "Berkley's RC van\nBobcat\nBurrito\nForklift\nMoonbeam\nMower\nNewsvan\nNext page\nPony\nRumpo\nSadler\nTug\nWalton\nYosemite", "Select", "Back");}
			}
			}
  		}
  		case DIALOG_HMENU+11:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
		    if(listitem == 0){ AracSpawnla(playerid,501);}
	     	if(listitem == 1){ AracSpawnla(playerid,465);}
	     	if(listitem == 2){ AracSpawnla(playerid,464);}
	     	if(listitem == 3){ AracSpawnla(playerid,441);}
	     	if(listitem == 4){ AracSpawnla(playerid,594);}
	     	if(listitem == 5){ AracSpawnla(playerid,564);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+12:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,536);}
	        if(listitem == 1){ AracSpawnla(playerid,575);}
	        if(listitem == 2){ AracSpawnla(playerid,534);}
	        if(listitem == 3){ AracSpawnla(playerid,567);}
	        if(listitem == 4){ AracSpawnla(playerid,535);}
	        if(listitem == 5){ AracSpawnla(playerid,576);}
	        if(listitem == 6){ AracSpawnla(playerid,412);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+13:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,562);}
	        if(listitem == 1){ AracSpawnla(playerid,565);}
	        if(listitem == 2){ AracSpawnla(playerid,559);}
	        if(listitem == 3){ AracSpawnla(playerid,561);}
	        if(listitem == 4){ AracSpawnla(playerid,560);}
	        if(listitem == 5){ AracSpawnla(playerid,558);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+14:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,402);}
	        if(listitem == 1){ AracSpawnla(playerid,542);}
	        if(listitem == 2){ AracSpawnla(playerid,603);}
	        if(listitem == 3){ AracSpawnla(playerid,475);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+15:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,579);}
	        if(listitem == 1){ AracSpawnla(playerid,400);}
	        if(listitem == 2){ AracSpawnla(playerid,404);}
	        if(listitem == 3){ AracSpawnla(playerid,489);}
	        if(listitem == 4){ AracSpawnla(playerid,479);}
	        if(listitem == 5){ AracSpawnla(playerid,442);}
	        if(listitem == 6){ AracSpawnla(playerid,458);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+16:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,429);}
	        if(listitem == 1){ AracSpawnla(playerid,541);}
	        if(listitem == 2){ AracSpawnla(playerid,415);}
	        if(listitem == 3){ AracSpawnla(playerid,480);}
	        if(listitem == 4){ AracSpawnla(playerid,434);}
	        if(listitem == 5){ AracSpawnla(playerid,494);}
	        if(listitem == 6){ AracSpawnla(playerid,411);}
	        if(listitem == 7){ AracSpawnla(playerid,506);}
	        if(listitem == 8){ AracSpawnla(playerid,451);}
	        if(listitem == 9){ AracSpawnla(playerid,555);}
	        if(listitem == 10){ AracSpawnla(playerid,477);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+17:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,568);}
	        if(listitem == 1){ AracSpawnla(playerid,424);}
	        if(listitem == 2){ AracSpawnla(playerid,504);}
	        if(listitem == 3){ AracSpawnla(playerid,457);}
	        if(listitem == 4){ AracSpawnla(playerid,483);}
	        if(listitem == 5){ AracSpawnla(playerid,508);}
	        if(listitem == 6){ AracSpawnla(playerid,571);}
	        if(listitem == 7){ AracSpawnla(playerid,500);}
	        if(listitem == 8){ AracSpawnla(playerid,495);}
	        if(listitem == 9){ AracSpawnla(playerid,539);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+18:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,485);}
	        if(listitem == 1){ AracSpawnla(playerid,431);}
	        if(listitem == 2){ AracSpawnla(playerid,438);}
	        if(listitem == 3){ AracSpawnla(playerid,437);}
	        if(listitem == 4){ AracSpawnla(playerid,574);}
	        if(listitem == 5){ AracSpawnla(playerid,420);}
	        if(listitem == 6){ AracSpawnla(playerid,525);}
	        if(listitem == 7){ AracSpawnla(playerid,408);}
	        if(listitem == 8){ AracSpawnla(playerid,552);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+19:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,416);}
	        if(listitem == 1){ AracSpawnla(playerid,433);}
	        if(listitem == 2){ AracSpawnla(playerid,427);}
	        if(listitem == 3){ AracSpawnla(playerid,490);}
	        if(listitem == 4){ AracSpawnla(playerid,528);}
	        if(listitem == 5){ AracSpawnla(playerid,407);}
	        if(listitem == 6){ AracSpawnla(playerid,570);}
	        if(listitem == 7){ AracSpawnla(playerid,597);}
	        if(listitem == 8){ AracSpawnla(playerid,599);}
	        if(listitem == 9){ AracSpawnla(playerid,428);}
	        if(listitem == 10){ AracSpawnla(playerid,601);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+20:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
	        if(listitem == 0){ AracSpawnla(playerid,445);}
	        if(listitem == 1){ AracSpawnla(playerid,507);}
	        if(listitem == 2){ AracSpawnla(playerid,585);}
	        if(listitem == 3){ AracSpawnla(playerid,587);}
	        if(listitem == 4){ AracSpawnla(playerid,466);}
	        if(listitem == 5){ AracSpawnla(playerid,492);}
	        if(listitem == 6){ AracSpawnla(playerid,546);}
	        if(listitem == 7){ AracSpawnla(playerid,551);}
	        if(listitem == 8){ AracSpawnla(playerid,516);}
	        if(listitem == 9){ AracSpawnla(playerid,467);}
	        if(listitem == 10){ AracSpawnla(playerid,426);}
	        if(listitem == 11){ AracSpawnla(playerid,547);}
	        if(listitem == 12){ AracSpawnla(playerid,405);}
	        if(listitem == 13){ AracSpawnla(playerid,409);}
	        if(listitem == 14){ AracSpawnla(playerid,550);}
	        if(listitem == 15){ AracSpawnla(playerid,566);}
	        if(listitem == 16){ AracSpawnla(playerid,540);}
	        if(listitem == 17){ AracSpawnla(playerid,421);}
	        if(listitem == 18){ AracSpawnla(playerid,529);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+21:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
            if(listitem == 0){ AracSpawnla(playerid,602);}
	        if(listitem == 1){ AracSpawnla(playerid,496);}
	        if(listitem == 2){ AracSpawnla(playerid,401);}
	        if(listitem == 3){ AracSpawnla(playerid,518);}
	        if(listitem == 4){ AracSpawnla(playerid,527);}
	        if(listitem == 5){ AracSpawnla(playerid,589);}
	        if(listitem == 6){ AracSpawnla(playerid,419);}
	        if(listitem == 7){ AracSpawnla(playerid,533);}
	        if(listitem == 8){ AracSpawnla(playerid,526);}
	        if(listitem == 9){ AracSpawnla(playerid,474);}
	        if(listitem == 10){ AracSpawnla(playerid,545);}
	        if(listitem == 11){ AracSpawnla(playerid,517);}
	        if(listitem == 12){ AracSpawnla(playerid,410);}
	        if(listitem == 13){ AracSpawnla(playerid,600);}
	        if(listitem == 14){ AracSpawnla(playerid,436);}
	        if(listitem == 15){ AracSpawnla(playerid,580);}
	        if(listitem == 16){ AracSpawnla(playerid,439);}
	        if(listitem == 17){ AracSpawnla(playerid,549);}
	        if(listitem == 18){ AracSpawnla(playerid,491);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+22:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
            if(listitem == 0){ AracSpawnla(playerid,499);}
	        if(listitem == 1){ AracSpawnla(playerid,498);}
	        if(listitem == 2){ AracSpawnla(playerid,524);}
	        if(listitem == 3){ AracSpawnla(playerid,532);}
	        if(listitem == 4){ AracSpawnla(playerid,578);}
	        if(listitem == 5){ AracSpawnla(playerid,486);}
	        if(listitem == 6){ AracSpawnla(playerid,455);}
	        if(listitem == 7){ AracSpawnla(playerid,588);}
	        if(listitem == 8){ AracSpawnla(playerid,403);}
	        if(listitem == 9){ AracSpawnla(playerid,423);}
	        if(listitem == 10){ AracSpawnla(playerid,414);}
	        if(listitem == 11){ AracSpawnla(playerid,443);}
	        if(listitem == 12){ AracSpawnla(playerid,515);}
	        if(listitem == 13){ AracSpawnla(playerid,514);}
	        if(listitem == 14){ AracSpawnla(playerid,531);}
	        if(listitem == 15){ AracSpawnla(playerid,456);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+23:
  		{
		    switch(response)
			{
   			case 0:
			ShowPlayerDialog(playerid, DIALOG_HMENU+3, DIALOG_STYLE_LIST,
			"Hadmin Araçlar","Bisikletler\nMotorlar\n4x4ler\nBotlar\nHelikopterler\nUçaklar\nArabalar\nMinyatür araçlar","Seç","Ýptal");
			case 1:
			{
            if(listitem == 0){ AracSpawnla(playerid,459);}
	        if(listitem == 1){ AracSpawnla(playerid,422);}
	        if(listitem == 2){ AracSpawnla(playerid,482);}
	        if(listitem == 3){ AracSpawnla(playerid,530);}
	        if(listitem == 4){ AracSpawnla(playerid,418);}
	        if(listitem == 5){ AracSpawnla(playerid,572);}
	        if(listitem == 6){ AracSpawnla(playerid,582);}
	        if(listitem == 7){ AracSpawnla(playerid,413);}
	        if(listitem == 8){ AracSpawnla(playerid,440);}
	        if(listitem == 9){ AracSpawnla(playerid,543);}
	        if(listitem == 10){ AracSpawnla(playerid,583);}
	        if(listitem == 11){ AracSpawnla(playerid,478);}
	        if(listitem == 12){ AracSpawnla(playerid,554);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+24:
  		{
		    switch(response)
			{
   			case 0:
		   	ShowPlayerDialog(playerid, DIALOG_HMENU, DIALOG_STYLE_LIST, "Hadmin Anamenü",
		    "Sunucu Havasý\nSunucu Zamaný\nAraç\nModifiye Menüsü\nSilahlar", "Seç","Ýptal");
			case 1:
			{
		    if(listitem == 0){ AddVehicleComponent(GetPlayerVehicleID(playerid),1010); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Hidrolik aracýnýza eklendi.");}
            if(listitem == 1){ AddVehicleComponent(GetPlayerVehicleID(playerid),1087); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Nitro aracýnýza eklendi.");
            }
			if(listitem == 2){ ShowPlayerDialog(playerid, DIALOG_HMENU+25, DIALOG_STYLE_LIST, "Tekerlekler","Wire\nTwist\nAccess\nMega\nImport\nAtomic\nOfTwistfroad\nClassic", "Seç", "Geri");}
			if(listitem == 3){ ShowPlayerDialog(playerid, DIALOG_HMENU+26, DIALOG_STYLE_LIST, "Dýþ Görünüm","Stil 1\nStil 2\nStil 3\nStil 4\nStil 5", "Seç", "Geri");}
			if(listitem == 4){ ShowPlayerDialog(playerid, DIALOG_HMENU+27, DIALOG_STYLE_LIST, "Araç Rengi","Siyah \nBeyaz \nKoyu Mavi \nAçýk Mavi \nYeþil \nKýrmýzý \nSarý \nPembe", "Seç", "Geri");}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+25:
  		{
		    switch(response)
			{
   			case 0:
            ShowPlayerDialog(playerid, DIALOG_HMENU+24, DIALOG_STYLE_LIST, "Modifiye Menüsü",
	  	    "NOS\nHidrolik\nTekerlekler\nDýþ Görünüm\nRenkler", "Seç", "Geri");
			case 1:
			{
		    if(listitem == 0){ AddVehicleComponent(GetPlayerVehicleID(playerid),1081); ModifiyeSes(playerid); SendHataMessage(playerid,"Wire tekerlekleri aracýza takýldý.");}
            if(listitem == 1){ AddVehicleComponent(GetPlayerVehicleID(playerid),1078); ModifiyeSes(playerid); SendHataMessage(playerid,"Twist tekerlekleri aracýza takýldý.");}
			if(listitem == 2){ AddVehicleComponent(GetPlayerVehicleID(playerid),1098); ModifiyeSes(playerid); SendHataMessage(playerid,"Access tekerlekleri aracýza takýldý.");}
			if(listitem == 3){ AddVehicleComponent(GetPlayerVehicleID(playerid),1074); ModifiyeSes(playerid); SendHataMessage(playerid,"Mega tekerlekleri aracýza takýldý.");}
			if(listitem == 4){ AddVehicleComponent(GetPlayerVehicleID(playerid),1082); ModifiyeSes(playerid); SendHataMessage(playerid,"Import tekerlekleri aracýza takýldý.");}
 			if(listitem == 5){ AddVehicleComponent(GetPlayerVehicleID(playerid),1085); ModifiyeSes(playerid); SendHataMessage(playerid,"Atomic tekerlekleri aracýza takýldý.");}
			if(listitem == 6){ AddVehicleComponent(GetPlayerVehicleID(playerid),1025); ModifiyeSes(playerid); SendHataMessage(playerid,"OfTwistfroad tekerlekleri aracýza takýldý.");}
 			if(listitem == 7){ AddVehicleComponent(GetPlayerVehicleID(playerid),1077); ModifiyeSes(playerid); SendHataMessage(playerid,"Classic tekerlekleri aracýza takýldý.");}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+26:
  		{
		    switch(response)
			{
   			case 0:
            ShowPlayerDialog(playerid, DIALOG_HMENU+24, DIALOG_STYLE_LIST, "Modifiye Menüsü",
	  	    "NOS\nHidrolik\nTekerlekler\nDýþ Görünüm\nRenkler", "Seç", "Geri");
			case 1:
			{
		    if(listitem == 0){ ChangeVehiclePaintjob(GetPlayerVehicleID(playerid),0); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn dýþ boyasý 1 deðiþtirildi."); }
            if(listitem == 1){ ChangeVehiclePaintjob(GetPlayerVehicleID(playerid),1); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn dýþ boyasý 2 deðiþtirildi."); }
			if(listitem == 2){ ChangeVehiclePaintjob(GetPlayerVehicleID(playerid),2); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn dýþ boyasý 3 deðiþtirildi."); }
			if(listitem == 3){ ChangeVehiclePaintjob(GetPlayerVehicleID(playerid),3); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn dýþ boyasý 4 deðiþtirildi."); }
			if(listitem == 4){ ChangeVehiclePaintjob(GetPlayerVehicleID(playerid),4); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn dýþ boyasý 5 deðiþtirildi."); }
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+27:
  		{
		    switch(response)
			{
   			case 0:
            ShowPlayerDialog(playerid, DIALOG_HMENU+24, DIALOG_STYLE_LIST, "Modifiye Menüsü",
	  	    "NOS\nHidrolik\nTekerlekler\nDýþ Görünüm\nRenkler", "Seç", "Geri");
			case 1:
			{
			if(listitem == 0){ ChangeVehicleColor(GetPlayerVehicleID(playerid),0,0);     ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn rengi siyah olarak deðiþtirildi.");      }
			if(listitem == 1){ ChangeVehicleColor(GetPlayerVehicleID(playerid),1,1);     ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn rengi beyaz olarak deðiþtirildi.");      }
			if(listitem == 2){ ChangeVehicleColor(GetPlayerVehicleID(playerid),425,425); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn rengi Koyu Mavi olarak deðiþtirildi.");  }
			if(listitem == 3){ ChangeVehicleColor(GetPlayerVehicleID(playerid),2,2);     ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn rengi Açýk Mavi olarak deðiþtirildi."); }
			if(listitem == 4){ ChangeVehicleColor(GetPlayerVehicleID(playerid),16,16);   ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn rengi Yeþil olarak deðiþtirildi.");      }
			if(listitem == 5){ ChangeVehicleColor(GetPlayerVehicleID(playerid),3,3);     ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn rengi Kýrmýzý olarak deðiþtirildi.");		 }
			if(listitem == 6){ ChangeVehicleColor(GetPlayerVehicleID(playerid),6,6);     ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn rengi Sarý olarak deðiþtirildi.");	 }
			if(listitem == 7){ ChangeVehicleColor(GetPlayerVehicleID(playerid),146,146); ModifiyeSes(playerid); SendBilgiMessage(playerid,"Aracýnýzýn rengi Pembe olarak deðiþtirildi.");		 }
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+28:
  		{
		    switch(response)
			{
   			case 0:
			return ShowPlayerDialog(playerid, DIALOG_HMENU, DIALOG_STYLE_LIST, "Hadmin Anamenü",
			"Sunucu Havasý\nSunucu Zamaný\nAraç\nModifiye Menüsü\nSilahlar", "Seç","Ýptal");
			case 1:
			{
			if(listitem == 0){ShowPlayerDialog(playerid, DIALOG_HMENU+29, DIALOG_STYLE_LIST, "Taramalýlar", "Micro SMG \nSMG \nAK47 \nM4 \nTec9", "Select", "Back");}
			if(listitem == 1){ShowPlayerDialog(playerid, DIALOG_HMENU+30, DIALOG_STYLE_LIST, "Tekliler", "9mm \nSilenced 9mm \nDeagle", "Select", "Back");}
			if(listitem == 2){ShowPlayerDialog(playerid, DIALOG_HMENU+31, DIALOG_STYLE_LIST, "Tüfekler", "Country Rifle \nSniper Rifle", "Select", "Back");}
   			if(listitem == 3){ShowPlayerDialog(playerid, DIALOG_HMENU+32, DIALOG_STYLE_LIST, "Pompalýlar", "Shotgun \nSawnoff Shotgun \nCombat Shotgun", "Select", "Back");}
   			if(listitem == 4){ShowPlayerDialog(playerid, DIALOG_HMENU+33, DIALOG_STYLE_LIST, "Aðýr Makinalý", "Rocket Launcher \nHS Rocket Launcher \nFlamethrower \nMinigun", "Select", "Back");}
   		    if(listitem == 5){ShowPlayerDialog(playerid, DIALOG_HMENU+34, DIALOG_STYLE_LIST, "Özel Silahlar", "Camera \nNightvision Goggles \nInfared Vision \nParachute", "Select", "Back");}
   			if(listitem == 6){ShowPlayerDialog(playerid, DIALOG_HMENU+35, DIALOG_STYLE_LIST, "Taþýnabilir", "Spraycan \nFire Extinguisher", "Select", "Back");}
   			if(listitem == 7){ShowPlayerDialog(playerid, DIALOG_HMENU+36, DIALOG_STYLE_LIST, "Yakýn Dövüþ","Brass Knuckles \nGolf Club \nNite Stick \nKnife \nBaseball Bat \nShovel \nPool Cue \nKatana \nChainsaw \nPurple Dildo \nSmall White Vibrator \nLarge White Vibrator \nSilver Vibrator \nFlowers \nCane", "Select", "Back");}
   			if(listitem == 8){ShowPlayerDialog(playerid, DIALOG_HMENU+37, DIALOG_STYLE_LIST, "Roket", "Bomba \nTear Gas \nMolotov Cocktail \nSatchel Charge \nDetonator", "Select", "Back");}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+29:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
		 	if(listitem == 0){GivePlayerWeaponEx(playerid,28, 300);}
		 	if(listitem == 1){GivePlayerWeaponEx(playerid,29, 300);}
	  		if(listitem == 2){GivePlayerWeaponEx(playerid,30, 300);}
			if(listitem == 3){GivePlayerWeaponEx(playerid,31, 300);}
			if(listitem == 4){GivePlayerWeaponEx(playerid,32, 300);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+30:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
			if(listitem == 0){GivePlayerWeaponEx(playerid,22, 300);}
			if(listitem == 1){GivePlayerWeaponEx(playerid,23, 300);}
			if(listitem == 2){GivePlayerWeaponEx(playerid,24, 300);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+31:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
			if(listitem == 0){GivePlayerWeaponEx(playerid,33, 300);}
			if(listitem == 1){GivePlayerWeaponEx(playerid,34, 300);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+32:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
			if(listitem == 0){GivePlayerWeaponEx(playerid,25, 300);}
			if(listitem == 1){GivePlayerWeaponEx(playerid,26, 300);}
			if(listitem == 2){GivePlayerWeaponEx(playerid,27, 300);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+33:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
			if(listitem == 0){GivePlayerWeaponEx(playerid,35, 300);}
			if(listitem == 1){GivePlayerWeaponEx(playerid,36, 300);}
			if(listitem == 2){GivePlayerWeaponEx(playerid,37, 300);}
			if(listitem == 3){GivePlayerWeaponEx(playerid,38, 300);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+34:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
			if(listitem == 0){GivePlayerWeaponEx(playerid,43, 300);}
			if(listitem == 1){GivePlayerWeaponEx(playerid,44, 300);}
			if(listitem == 2){GivePlayerWeaponEx(playerid,45, 300);}
			if(listitem == 3){GivePlayerWeaponEx(playerid,46, 300);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+35:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
			if(listitem == 0){GivePlayerWeaponEx(playerid,41, 300);}
			if(listitem == 1){GivePlayerWeaponEx(playerid,42, 300);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+36:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
			if(listitem == 0){GivePlayerWeaponEx(playerid,1, 300);}
			if(listitem == 1){GivePlayerWeaponEx(playerid,2, 300);}
			if(listitem == 2){GivePlayerWeaponEx(playerid,3, 300);}
			if(listitem == 3){GivePlayerWeaponEx(playerid,4, 300);}
			if(listitem == 4){GivePlayerWeaponEx(playerid,5, 300);}
			if(listitem == 5){GivePlayerWeaponEx(playerid,6, 300);}
			if(listitem == 6){GivePlayerWeaponEx(playerid,7, 300);}
			if(listitem == 7){GivePlayerWeaponEx(playerid,8, 300);}
			if(listitem == 8){GivePlayerWeaponEx(playerid,9, 300);}
			if(listitem == 9){GivePlayerWeaponEx(playerid,10, 300);}
			if(listitem == 10){GivePlayerWeaponEx(playerid,11, 300);}
			if(listitem == 11){GivePlayerWeaponEx(playerid,12, 300);}
			if(listitem == 12){GivePlayerWeaponEx(playerid,13, 300);}
			if(listitem == 13){GivePlayerWeaponEx(playerid,14, 300);}
			if(listitem == 14){GivePlayerWeaponEx(playerid,15, 300);}
			if(listitem == 15){GivePlayerWeaponEx(playerid,16, 300);}
	  		TogglePlayerControllableEx(playerid,true);
			}
			}
  		}
  		case DIALOG_HMENU+37:
  		{
		    switch(response)
			{
   			case 0:
  			return ShowPlayerDialog(playerid, DIALOG_HMENU+28, DIALOG_STYLE_LIST,
			"Silahlar", "Taramalýlar\nTekliler\nTüfek\nPompalý\nAðýr Makinalý\nÖzel Silahlar\nTaþýna bilen\nYakýn Dövüþ\nRoket", "Seç", "Geri");

			case 1:
			{
			if(listitem == 0){GivePlayerWeaponEx(playerid,16, 300);}
			if(listitem == 1){GivePlayerWeaponEx(playerid,17, 300);}
			if(listitem == 2){GivePlayerWeaponEx(playerid,18, 300);}
			if(listitem == 3){GivePlayerWeaponEx(playerid,39, 300);}
			if(listitem == 4){ GivePlayerWeaponEx(playerid,40, 300);}
	  		TogglePlayerControllableEx(playerid,true);
   	 		}
			}
  		}
  		case DIALOG_CONSOLE:
  		{
		    switch(response)
			{
   			
 			//return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			case 1:
			{
	  		if(listitem == 0) { ShowPlayerDialog(playerid,DIALOG_CONSOLE+1,DIALOG_STYLE_INPUT,"Hadmin Konsol","FilterScript Yükle:\n","Yükle!","Geri");}
	    	if(listitem == 1) { ShowPlayerDialog(playerid,DIALOG_CONSOLE+2,DIALOG_STYLE_INPUT,"Hadmin Konsol","Filterscript kapat:\n","Kapat!","Geri");}
	    	if(listitem == 2) { ShowPlayerDialog(playerid,DIALOG_CONSOLE+3,DIALOG_STYLE_INPUT,"Hadmin Konsol","Modu deðiþtir:\n","Deðiþtir!","Geri");}
			if(listitem == 3) { OnGameModeExit(); SetTimer("RestartGM",5000,0); SendBilgiMessage(playerid,"Konsol komudu gönderildi");}
			if(listitem == 4){  return ShowPlayerDialog(playerid,DIALOG_CONSOLE+4,DIALOG_STYLE_INPUT,"Hadmin Konsol","IPnin yasaklamasýný aç:\n","Aç!","Geri");}
			if(listitem == 5){  SendRconCommand("reloadbans"); SendBilgiMessage(playerid,"Konsol komudu göderildi"); }
			if(listitem == 6){  ShowPlayerDialog(playerid, DIALOG_CONSOLE+5, DIALOG_STYLE_INPUT, "Hadmin - Komut gönderme","Gönderilecek komudu Lütfen aþaðýya girin..", "Gönder", "iptal"); }
			}
			}
  		}
  		case DIALOG_CONSOLE+1:
  		{
		    switch(response)
			{
   			case 0:
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			case 1:
			{
	 		new string[64];
		 	format(string,sizeof(string),"loadfs %s",inputtext);
		 	SendRconCommand(string);
		 	SendBilgiMessage(playerid,"Konsol komudu gönderildi");
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			}
			}
		}
  		case DIALOG_CONSOLE+2:
  		{
		    switch(response)
			{
   			case 0:
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			case 1:
			{
	 		new string[64];
		 	format(string,sizeof(string),"unloadfs %s",inputtext);
		 	SendRconCommand(string);
		 	SendBilgiMessage(playerid,"Konsol komudu gönderildi");
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			}
			}
		}
  		case DIALOG_CONSOLE+3:
  		{
		    switch(response)
			{
   			case 0:
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			case 1:
			{
	 		new string[64];
		 	format(string,sizeof(string),"changemode %s",inputtext);
		 	SendRconCommand(string);
		 	SendBilgiMessage(playerid,"Konsol komudu gönderildi");
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			}
			}
		}
  		case DIALOG_CONSOLE+4:
  		{
		    switch(response)
			{
   			case 0:
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			case 1:
			{
	 		new string[64];
		 	format(string,sizeof(string),"unbanip %s",inputtext);
		 	SendRconCommand(string);
		 	SendBilgiMessage(playerid,"Konsol komudu gönderildi");
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			}
			}
		}
  		case DIALOG_CONSOLE+5:
  		{
		    switch(response)
			{
   			case 0:
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			case 1:
			{
	 		new string[64];
		 	format(string,sizeof(string),"%s",inputtext);
		 	SendRconCommand(string);
		 	SendBilgiMessage(playerid,"Konsol komudu gönderildi");
 			return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");
			}
			}
		}
		case 999+999:
  		{
  		    new Yazi[512];
  			if(OyuncuVeri[playerid][Admin] >= 4)
			{
			format(Yazi, sizeof(Yazi), "{FFFFFF}___________ |- Hadmin - Yüksek Yönetici (Seviye 4) -| ___________\n\
										{53D212}Herkes: herkes (cek, sustur, konustur, oldur, dondur, coz, patlat, at, saplak, aractanat)\n\
		                                {33F666}Oyuncu: ban, crash\n\
				  						{33F666}Yönetici: sunucuyusifrele, olumsuzluk, olumsuzarac, sahteolum\n\n",Yazi);
			}

			if(OyuncuVeri[playerid][Admin] >= 5)
			{
			format(Yazi, sizeof(Yazi), "%s{FFFFFF}___________ |- Hadmin - Lider Yönetici (Seviye 5) -| ___________\n\
										{53D212}Oyuncu: adminyap, vipyap, sahteyazi\n\
		                                {33F666}Yönetici: god, sgod, console\n",Yazi);
				  					//	{33F666}Diðer: pickup, object, respawncars\n\n",Yazi2);
			}
			ShowPlayerDialog(playerid, DIALOG_LOG_BASAR, DIALOG_STYLE_MSGBOX, "Yönetici Komutlarý", Yazi, "Ok", "");
		}
 	}
	if(HoPDR)
		return CallLocalFunction("H_OnDialogResponse","iiiis",playerid, dialogid, response, listitem, inputtext);
	else
		return 1;
}

public OnPlayerUpdate(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;

	switch(OyuncuVeri[playerid][Donmama])
	{
	case 0:return 0;
	}
    #if ANTI_PARA == 1
	if(GetPlayerMoney(playerid) != GetPlayerMoneyEx(playerid))
	ResetPlayerMoney(playerid),
	GivePlayerMoney(playerid, OyuncuVeri[playerid][Para]);
	#endif
	
	if(HoPU)
		return CallLocalFunction("H_OnPlayerUpdate","i",playerid);
	else
		return 1;
}

public OnPlayerSpawn(playerid)
{
	#if SKIN_KAYIT == true
	SetPlayerSkin(playerid, GetPlayerSkinEx(playerid));
	#endif

	for(new i;i<3;i++) OyuncuSilahlari[playerid][ClassSilahlari[OyuncuClasslari[playerid]][i]]=true;
	SetTimerEx("RealSpawn",800,false,"i",playerid);

	Isinlandi[playerid] = 0;

	if(HoPS)
		return CallLocalFunction("H_OnPlayerSpawn","i",playerid);
	else
		return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	Isinlandi[playerid] = 1;
	
	if(HoPD)
		return CallLocalFunction("H_OnPlayerDeath", "iis", playerid, killerid, reason);
	else
		return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		switch(GetVehicleModel(GetPlayerVehicleID(playerid)))
		{
			case 592,577,511,512,520,593,553,476,519,460,513,548,425,417,487,488,497,563,447,469: OyuncuSilahlari[playerid][46]=true;
			case 457: OyuncuSilahlari[playerid][2]=true;
			case 596,597,598,599: OyuncuSilahlari[playerid][25]=true;
		}
	}
	
	if(HoPSC)
		return CallLocalFunction("H_OnPlayerStateChange", "iii", playerid, newstate, oldstate);
	else
		return 1;
}

forward RealSpawn(playerid);
public RealSpawn(playerid)
{
    Spawnlandi[playerid]=true;
	if(OyuncuVeri[playerid][Hapis] > 0)
	{
	SetPlayerPosEx(playerid, 107.2300,1920.6311,18.5208);
	SetPlayerWorldBounds(playerid, 337.5694,101.5826,1940.9759,1798.7453); //285.3481,96.9720,1940.9755,1799.0811
	SetPlayerInterior(playerid,0);
	SendBilgiMessage(playerid, "Hapis süren dolmadýðý için hapiste doðdun.");
	}
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_FIRE)
    {
		if(Spawnlandi[playerid])
		{
			 static weapon;
			 weapon = GetPlayerWeapon(playerid);
			 if(!OyuncuSilahlari[playerid][weapon] && weapon != 40 && weapon != 0)
		     #if ANTI_SILAH == 2
			 H_Ban(playerid,"Silah Hilesi");
			 #elseif ANTI_SILAH == 1
			 H_Kick(playerid,"Silah Hilesi");
			 #endif
		}
    }
    
    if(newkeys & KEY_SECONDARY_ATTACK)
    {
        if(OyuncuVeri[playerid][JetPack] == 1)
		{
			GetPlayerPos(playerid, Jx[playerid], Jy[playerid], Jz[playerid]);
			if(JT[playerid] != 0)
			{
			KillTimer(JT[playerid]);
			JT[playerid] = SetTimerEx("Jxyz", 120000, false, "i", playerid);
			}
		}
    }


   	if(HoPKSC)
		return CallLocalFunction("H_OnPlayerKeyStateChange", "iii", playerid, newkeys, oldkeys);
	else
		return 1;
	
}
forward H_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);

forward Jxyz(playerid);
public Jxyz(playerid)
{
	if(Jx[playerid] != 0)
	Jx[playerid] = 0,
	Jy[playerid] = 0,
	Jz[playerid] = 0;
	return 1;
}


public OnGameModeInit()
{
	SetTimer("Credits", 1500, 0);
	if(!CallLocalFunction("H_OnGameModeInit",""))
	{
		print("_________________________________________________________________________\n");
	    H_Log("[UYARI!]");
	    H_Log("Hadmin OnGameModeInit'te cagrilamiyor. (return 0)");
	    H_Log("Hadmin.inc'i Modunuzda kullandiginiza emin olun.");
        H_Log("Hadmin'i FS'lerinizdede kullanýn HadminFS.inc");
       	print("_________________________________________________________________________");
	}
	HoPT = (funcidx("H_OnPlayerText") != -1);
	HoPC = (funcidx("H_OnPlayerCheat") != -1);
	HoPS = (funcidx("H_OnPlayerSpawn") != -1);
	HoPD = (funcidx("H_OnPlayerDeath") != -1);
	HoPU = (funcidx("H_OnPlayerUpdate") != -1);
	HoPCo = (funcidx("H_OnPlayerConnect") != -1);
	HoPDR = (funcidx("H_OnDialogResponse") != -1);
	HoPDi = (funcidx("H_OnPlayerDisconnect") != -1);
	HoPSC = (funcidx("H_OnPlayerStateChange") != -1);
	HoPUP = (funcidx("H_OnPlayerPickUpPickup") != -1);
	HoPIC = (funcidx("H_OnPlayerInteriorChange") != -1);
	HoPKSC = (funcidx("H_OnPlayerKeyStateChange") != -1);
	SunucuGuncelle = SetTimer("SunucuGuncelleme", 1000, 1);
	return 1;
}

public H_Kick(playerid,neden[])
{
	if(IsPlayerConnected(playerid))
	{
	    new string[256];
	    TogglePlayerControllableEx(playerid,false);
	    format(string, sizeof(string),"* {555555}((  {FF0000}.:[H-Anti Hile]:. %s sunucudan atýldý. Gerekçe: %s {555555}))",pName(playerid),neden);
		SendClientMessageToAll(Kirmizi, string);
		H_LogEx("%s (%s) sunucudan atýldý. Gerekçe:%s.",pName(playerid),pIp(playerid),neden);
	    Kick(playerid);
	    return 1;
	}
	return 0;
}

public H_Ban(playerid,neden[])
{
	if(IsPlayerConnected(playerid))
	{
	    new string[128];
	    TogglePlayerControllableEx(playerid,false);
	    format(string, sizeof(string),"* {555555}((  {FF0000}.:[H-Anti Hile]:. %s sunucudan yasaklandý. Gerekçe: %s {555555}))",pName(playerid),neden);
		SendClientMessageToAll(Kirmizi, string);
		OyuncuVeri[playerid][Banlandi] = 1;
	    H_LogEx("%s (%s) sunucudan yasaklandý. Gerekçe:%s.",pName(playerid),pIp(playerid),neden);
	    BanEx(playerid,neden);
	    return 1;
	}
	return 0;
}

public SunucuGuncelleme() //
{
	for(new i=0; i<MAX_PLAYERS; i++)
	{
		switch(IsPlayerConnected(i))
		{
			case 1:
			{
			    switch(GetPVarInt(i, "Gyapti"))
			    {
					case 1:
					{
					
					if(IsPlayerConnected(i) && OyuncuVeri[i][God] == 1)
					{
						SetPlayerHealth(i,100000);
					}
					if(IsPlayerConnected(i) && OyuncuVeri[i][GodCar] == 1 && IsPlayerInAnyVehicle(i))
					{
						SetVehicleHealth(GetPlayerVehicleID(i),10000);
					}
					if(OyuncuVeri[i][Sus] != 0)
					OyuncuVeri[i][Sus] --;
					if(OyuncuVeri[i][Hapis] > 0)
					OyuncuVeri[i][Hapis] --;
					else if(OyuncuVeri[i][Hapis] == 0)
					{
					SetPlayerWorldBounds(i, 20000.0000,-20000.0000,20000.0000,-20000.0000);
					SetPlayerPosEx(i, 1529.6,-1691.2,13.3);
					SetPlayerVirtualWorld(i, 0);
					SetPlayerInterior(i, 0);
					SendBilgiMessage(i, "Hapis süren doldu birdaha ayný hatayý yapmaman dileði ile..");
					OyuncuVeri[i][Hapis] = -1;
					}
					if(OyuncuVeri[i][Admin] >= HILE_SEVIYE)
					    return 1;
					new Yazi[128];
					if(GetPlayerPing(i) > MAX_PING)
					{
						switch(GetPVarInt(i, "PING"))
						{
							case 3:
							{
							format(Yazi, sizeof(Yazi), "Maksimum Pingi(%d) Geçtiðiniz için sunucudan atýldýnýz.", MAX_PING);
							SendClientMessage(i, SunucuDuyuru, Yazi);
							format(Yazi, sizeof(Yazi), "%s maksimum pingi(%d) geçtiði için sunucudan atýldý.", pName(i),MAX_PING);
							SendClientMessage(i, SunucuDuyuru, Yazi), H_Log(Yazi);
							Kick(i);
							}
		     				default: SetPVarInt(i, "PING", GetPVarInt(i, "PING")+1);
						}
					}
					#if ANTI_JETPACK == 1

	   				if(GetPlayerSpecialAction(i) == 2 && OyuncuVeri[i][JetPack] == 0)
	   				{

						for(new Ji; Ji < MAX_PLAYERS; Ji++)
						{
							if(IsPlayerInRangeOfPoint(i, 8, Jx[Ji], Jy[Ji], Jz[Ji]))
							{
			    			OyuncuVeri[i][JetPack] = 1;
							Jx[Ji] = 0;
							Jy[Ji] = 0;
							Jz[Ji] = 0;
							}
						}

						if(OyuncuVeri[i][JetPack] != 1)
	   					SetPlayerSpecialAction(i, 0), OnPlayerCheat(i, PLAYER_JETPACK);
	   					
					}
	   				else if(GetPlayerSpecialAction(i) != 2 && OyuncuVeri[i][JetPack] == 1)
		   				OyuncuVeri[i][JetPack] = 0;
					
	   				#endif
					new Float: XY, Float:Z;
					GetPlayerPos(i, XY, XY, Z);
					#if AIR_BRAKE != 0
					if(Isinlandi[i] != 1 && GetPlayerState(i) == PLAYER_STATE_ONFOOT && OyuncuVeri[i][JetPack] == 0 || Isinlandi[i] != 1 && GetPlayerState(i) == PLAYER_STATE_DRIVER && OyuncuVeri[i][JetPack] == 0)
					{
	    				if(Ucaktami(i) == 0)
			            {
			                if(GetPlayerState(i) == PLAYER_STATE_ONFOOT)
			                {
				                if(floatadd(Z, -Zdegisimi[i]) > 20)
				                {
				                    if(OyuncuVeri[i][AirBrake] > 0)
				                    {
				   	                    if(GetPlayerAnimationIndex(i) == 1231)
										{
										    if(floatadd(Z, -Zdegisimi[i]) > 5)
										    {
											H_HileDuyurusuEx("%s, Airbrake yapýyor olabilir. Yukseklik Degisimi:%0.3f ",pName(i), floatadd(Z, -Zdegisimi[i]));
											OyuncuVeri[i][AirBrake]++;
											OnPlayerCheat(i, PLAYER_AIRBRAKE);
											if(OyuncuVeri[i][AirBrake] == 3+1)
											{
											#if AIR_BRAKE == 1
											return H_Kick(i, "AIRBRAKE");
											#endif
					                        #if AIR_BRAKE == 2
		  			                        return H_Ban(i, "AIRBRAKE");
											#endif
											}
											}
										}
										else if(floatadd(Z, -Zdegisimi[i]) > 10)
										{
											H_HileDuyurusuEx("%s, Airbrake yapýyor olabilir. Yukseklik Degisimi:%0.3f ",pName(i), floatadd(Z, -Zdegisimi[i]));
											OyuncuVeri[i][AirBrake]++;
											OnPlayerCheat(i, PLAYER_AIRBRAKE);
											if(OyuncuVeri[i][AirBrake] == 3+1)
											{
											#if AIR_BRAKE == 1
											return H_Kick(i, "AIRBRAKE");
											#endif
					                        #if AIR_BRAKE == 2
		  			                        return H_Ban(i, "AIRBRAKE");
											#endif
											}
										}
									}
								}
								if(OyuncuVeri[i][AirBrake] < 0)
								{
	       							if(0 <= floatadd(Z, -Zdegisimi[i]) < 5)
									{
									OyuncuVeri[i][AirBrake] *= -1;
									}

									if(-20 < floatadd(Z, -Zdegisimi[i]) < 0 )
									{
									OyuncuVeri[i][AirBrake] *= -1;
									}
								}
								else
								{
									if(-20 > floatadd(Z, -Zdegisimi[i]) < 0 )
									{
				   	                    if(GetPlayerAnimationIndex(i) != 1130)
		                    			{
											H_HileDuyurusuEx("%s, Air Brake yapýyor olabilir. Yukseklik Degisim:%f ",pName(i), floatadd(Z, -Zdegisimi[i]));
											OyuncuVeri[i][AirBrake]++;
											OnPlayerCheat(i, PLAYER_AIRBRAKE);
											if(OyuncuVeri[i][AirBrake] == 3+1)
											{
											#if AIR_BRAKE == 1
											return H_Kick(i, "AIRBRAKE");
											#endif
						                    #if AIR_BRAKE == 2
						                    return H_Ban(i, "AIRBRAKE");
											#endif
											}
										}
									}
								}
							}
							else
							{
	  							if(OyuncuVeri[i][AirBrake] < 0 )
								{
	       							if(-140 < floatadd(Z, -Zdegisimi[i]) < 0 || 0 <= floatadd(Z, -Zdegisimi[i]) < 15)
									{
									OyuncuVeri[i][AirBrake] *= -1;
									}
								}
				                if(-140 > floatadd(Z, -Zdegisimi[i]) < 0 || floatadd(Z, -Zdegisimi[i]) > 15)
				                {
				                    if(OyuncuVeri[i][Hiz] >= 0 && OyuncuVeri[i][AirBrake] >= 0)
									{
										H_HileDuyurusuEx("%s, Air Brake yapýyor olabilir. Yukseklik Degisim:%f ",pName(i), floatadd(Z, -Zdegisimi[i]));
										OyuncuVeri[i][AirBrake]++;
										OnPlayerCheat(i, PLAYER_AIRBRAKE);
										if(OyuncuVeri[i][AirBrake] == 3+1)
										{
										#if AIR_BRAKE == 1
										return H_Kick(i, "AIRBRAKE");
										#endif
				                        #if AIR_BRAKE == 2
				                        return H_Ban(i, "AIRBRAKE");
										#endif
										}
									}
								}
							}
						}
						else
						{
							if(OyuncuVeri[i][AirBrake] < 0 )
							{
	       						if(-90 < floatadd(Z, -Zdegisimi[i]) < 0 || 0 <= floatadd(Z, -Zdegisimi[i]) < 90)
								{
								OyuncuVeri[i][AirBrake] *= -1;
								}
							}
			                if(-90 > floatadd(Z, -Zdegisimi[i]) < 0 || floatadd(Z, -Zdegisimi[i]) > 90)
			                {
	                  			if(OyuncuVeri[i][Hiz] >= 0 && OyuncuVeri[i][AirBrake] >= 0)
								{
									H_HileDuyurusuEx("%s, Air Brake yapýyor olabilir. Yukseklik Degisim:%f ",pName(i), floatadd(Z, -Zdegisimi[i]));
									OyuncuVeri[i][AirBrake]++;
									OnPlayerCheat(i, PLAYER_AIRBRAKE);
									if(OyuncuVeri[i][AirBrake] == 3+1)
									{
									#if AIR_BRAKE == 1
									return H_Kick(i, "AIRBRAKE");
									#endif
			                        #if AIR_BRAKE == 2
			                        return H_Ban(i, "AIRBRAKE");
									#endif
									}
								}
							}
						}
					}
					#endif
					#if ANTI_FLY != 0
        			if(Z > 0)
           			{
      					if(OyuncuVeri[i][Fly] >= 0)
			            {
							if(GetPlayerAnimationIndex(i) == 1538 || GetPlayerAnimationIndex(i) == 1539 || GetPlayerAnimationIndex(i) == 1543)
		           			{
								H_HileDuyurusuEx("%s, Fly Hilesi yapýyor olabilir. Z: %f index: %d ",pName(i), Z, GetPlayerAnimationIndex(i));
								OyuncuVeri[i][Fly]++;
								OnPlayerCheat(i, PLAYER_FLY);
								if(OyuncuVeri[i][Fly] == MAX_KONTROL)
								{
								#if ANTI_FLY == 1
								return H_Kick(i, "Fly Hilesi");
								#endif
			                    #if ANTI_FLY == 2
		                        return H_Ban(i, "Fly Hilesi");
								#endif
								}
							}
						}
					}
					#endif
					#if ANTI_HIZ != 0
					new
						Float:Xx,
						Float:Xy,
						Float:Xz,
						Float:vSpeed
					;

				    GetVehicleVelocity(GetPlayerVehicleID(i), Xx, Xy, Xz);
					vSpeed = floatsqroot(Xx*Xx + Xy*Xy + Xz*Xz)*200*1.3;
	   				if(OyuncuVeri[i][Hiz] < 0 && vSpeed < MAX_HIZ)
					{
					OyuncuVeri[i][Hiz] *= -1;
					OyuncuVeri[i][AirBrake] *= -1;
					}
					if(Isinlandi[i] != 1 && GetPlayerState(i) == PLAYER_STATE_ONFOOT || Isinlandi[i] != 1 && GetPlayerState(i) == PLAYER_STATE_DRIVER)
					{
						if(-50 < floatadd(Z, -Zdegisimi[i]) > 0 && IsPlayerInAnyVehicle(i) && GetPlayerState(i) == PLAYER_STATE_DRIVER)
						{
							if(Ucaktami(i) != 1 && OyuncuVeri[i][Hiz] > 0)
							{
								if(vSpeed > MAX_HIZ)
								{
									OnPlayerCheat(i, PLAYER_HIZ);
									H_HileDuyurusuEx("%s, hýz hilesi yapýyor olabilir. Gittiði Hýz: %f",pName(i), vSpeed);
					                TogglePlayerControllableEx(i, 0), OyuncuVeri[i][Hiz]++,SetTimerEx("HizKes", 1500, 0, "i", i);
									if(OyuncuVeri[i][Hiz] == MAX_KONTROL+1)
									#if ANTI_HIZ == 1
									return H_Kick(i, "Hiz Hilesi");
									#endif
			                        #if ANTI_HIZ == 2
			                        return H_Ban(i, "Hiz Hilesi");
									#endif
								}
							}
					    }
					}
					Isinlandi[i] = 0;
					#endif
					GetPlayerPos(i, XY, XY, Zdegisimi[i]);
					}
				}
			}
		}
	}
	return 1;
}

forward Credits();
public Credits()
{
	new HARITA[64];
    GetServerVarAsString("mapname", HARITA, sizeof(HARITA));
	new SUNUCU_ISIM[64];
    GetServerVarAsString("hostname", SUNUCU_ISIM, sizeof(SUNUCU_ISIM));
 	new SITE[64];
    GetServerVarAsString("weburl", SITE, sizeof(SITE));
 	new SIFRE[64];
    GetServerVarAsString("password", SIFRE, sizeof(SIFRE));
	print("_________________________________________________________________________\n");
	printf("> %s moda enjekte edildi. ", INCLUDE);
	printf("> Sunucu Adý : %s  ", SUNUCU_ISIM);
	printf("> Versiyon : %s  ", VERSION);
	printf("> Harita : %s  ", HARITA);
	printf("> Ýnternet Sitesi : %s  ", SITE);
	printf("> Geliþtirici : %s  ", DEVELOPER);
	printf("> Son Güncelleme : %s  ", GUNCELLEME);
	printf("> Güncelleme içeriði : %s  ", GUNCELLEME_ICERIK);
 	printf("> Þifre : %s  ", SIFRE);
	print("_________________________________________________________________________");
}

forward HizKes(playerid);
public HizKes(playerid)
{
TogglePlayerControllableEx(playerid, 1);
}

public OnPlayerText(playerid, text[])
{
	new Yazi[128];
	if(OyuncuVeri[playerid][Sus] != 0)
		return format(Yazi, sizeof(Yazi), "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Susturulmuþsunuz konuþamazsýnýz. Kalan saniye: %d {555555}))", OyuncuVeri[playerid][Sus]),
		SendClientMessage(playerid, 0xFFFFFFFF, Yazi), 0;

	if(HoPT)
		return CallLocalFunction("H_OnPlayerText","is",playerid,text);
	else
		return 1;
}

public OnPlayerConnect(playerid)
{
	OyuncuVeri[playerid][Admin] = 0;
	OyuncuVeri[playerid][Vip] = 0;
	OyuncuVeri[playerid][Para] = 0;
	OyuncuVeri[playerid][Skor] = 0;
	OyuncuVeri[playerid][KTarih] = 0;
	OyuncuVeri[playerid][Skin] = 0;
	OyuncuVeri[playerid][God] = 0;
	OyuncuVeri[playerid][GodCar] = 0;
	OyuncuVeri[playerid][Sus] = 0;
	OyuncuVeri[playerid][Hapis] = -1;
	OyuncuVeri[playerid][Banlandi] = 0;
	OyuncuVeri[playerid][pArac]= -1;
	OyuncuVeri[playerid][Ycalisma] = 0;
	OyuncuVeri[playerid][aSeviye] = 0;
	OyuncuVeri[playerid][JetPack] = 0;
	OyuncuVeri[playerid][Uyari] = 0;
	OyuncuVeri[playerid][Hiz] = 1;
	OyuncuVeri[playerid][AirBrake] = 1;
	OyuncuVeri[playerid][Fly] = 0;
	OyuncuVeri[playerid][Donmama] = 1;
	Isinlandi[playerid] = 0;
	
 	for(new i=0;i<47;i++) OyuncuSilahlari[playerid][i]=false; // wups
  	Spawnlandi[playerid]=false;
  	
	#if ZORUNLU_GIRIS == true
	if ( !INI_Exist( pName( playerid ) ) )
		ShowPlayerDialog( playerid, DIALOG_Giris, DIALOG_STYLE_MSGBOX, "{33AA33}.:[KAYIT]:. {FFFFFF}Merhaba,", "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Ýsminiz sunucumuza kayýt edilmemiþ.{555555}))\n{FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Sunucumuzda oynamak için kayýt olmuþ olmalýsýnýz.{555555}))\n{FFFFFF}* {555555}((  {800080}.:[SORU]:. {FFFFFF}Kayýt olmak istermisiniz ?{555555}))", "Kayýt ol", "Hayýr");
	else
	    ShowPlayerDialog( playerid, DIALOG_Giris, DIALOG_STYLE_MSGBOX, "{33AA33}.:[Giriþ]:. {FFFFFF}Merhaba,", "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Ýsminiz sunucumuza kayýt edilmiþ.{555555}))\n{FFFFFF}* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Sunucumuzda oynamak için giriþ yapmýþ olmalýsýnýz.{555555}))\n{FFFFFF}* {555555}((  {800080}.:[SORU]:. {FFFFFF}Giriþ yapmak istermisiniz ?{555555}))", "Evet", "Hayýr");
	#endif

	if(HoPCo)
		return CallLocalFunction("H_OnPlayerConnect","i",playerid);
	else
		return 1;
}

public OnPlayerInteriorChange(playerid,newinteriorid,oldinteriorid)
{
	switch(newinteriorid)
	{
		case 1, 4, 6,7:
		{
	    SetTimerEx("GirdimBen",500,false,"ii",playerid,newinteriorid);
		}
	}
	
	if(HoPIC)
		return CallLocalFunction("H_OnPlayerInteriorChange","iii",playerid,newinteriorid,oldinteriorid);
	else
		return 1;
}

forward GirdimBen(playerid, newinteriorid);
public GirdimBen(playerid, newinteriorid)
{
	switch(newinteriorid)
	{
		case 1:
		{
			if(IsPlayerInRangeOfPoint(playerid, 10, 286.148987, -40.644398, 1001.569946))
			{
			SetPlayerShopName(playerid, "FDPIZZA");
			}
		}
		case 4:
		{
			if(IsPlayerInRangeOfPoint(playerid, 10, 286.800995, -82.547600, 1001.539978))
			{
			SetPlayerShopName(playerid, "FDPIZZA");
			}
		}
		case 6:
		{
			if(IsPlayerInRangeOfPoint(playerid, 10, 296.919988, -108.071999, 1001.569946))
			{
			SetPlayerShopName(playerid, "FDPIZZA");
			}
			if(IsPlayerInRangeOfPoint(playerid, 10, 316.524994, -167.706985, 999.661987))
			{
			SetPlayerShopName(playerid, "FDPIZZA");
			}
		}
		case 7:
		{
			if(IsPlayerInRangeOfPoint(playerid, 10, 314.820984, -141.431992,999.661987))
			{
			SetPlayerShopName(playerid, "FDPIZZA");
			}
			if(IsPlayerInRangeOfPoint(playerid, 10, 302.292877, -143.139099, 1004.062500))
			{
			SetPlayerShopName(playerid, "FDPIZZA");
			}
			if(IsPlayerInRangeOfPoint(playerid, 10, 280.795104, -135.203353, 1004.062500))
			{
			SetPlayerShopName(playerid, "FDPIZZA");
			}
		}
	}
}

public OnPlayerDisconnect(playerid, reason)
{
    if ( GetPVarInt( playerid, "Gyapti" ) == 1 && INI_Exist( pName( playerid ) ) )
	{
		new
			PlayerFile[ 13 + MAX_PLAYER_NAME + 1];

	    format( PlayerFile , sizeof PlayerFile, "Hadmin/Hesaplar/%s.ini", Encode( pName( playerid ) ) );


	    new
			INI:PlayerAcc = INI_Open( PlayerFile );

		INI_WriteInt( PlayerAcc,    "Para",  GetPlayerMoneyEx( playerid ) );
		INI_WriteInt( PlayerAcc,    "Skor",  GetPlayerScoreEx( playerid ) );
		INI_WriteInt( PlayerAcc,    "Skin",  GetPlayerSkinEx ( playerid ) );
		INI_WriteInt( PlayerAcc,    "Admin", OyuncuVeri[playerid][Admin]  );
		INI_WriteInt( PlayerAcc,    "Vip", OyuncuVeri[playerid][Vip]  );
		INI_WriteInt( PlayerAcc,    "Hapis", OyuncuVeri[playerid][Hapis]  );
		INI_WriteInt( PlayerAcc,    "Banlandi", OyuncuVeri[playerid][Banlandi]  );
		INI_Close( PlayerAcc );
	}
	SetPVarInt( playerid, "Gyapti", 0 );
	
	if(OyuncuVeri[playerid][pArac] != -1)
	AraciSil(OyuncuVeri[playerid][pArac]);
	
	if(HoPDi)
		return CallLocalFunction("H_OnPlayerDisconnect","i",playerid);
	else
		return 1;
}

public OnPlayerPickUpPickup(playerid,pickupid)
{
	//SendClientMessage(playerid, -1, "Aldýn");
	if(WeaponPickup[pickupid]) OyuncuSilahlari[playerid][WeaponPickup[pickupid]]=true;

	if(HoPUP)
		return CallLocalFunction("H_OnPlayerPickUpPickup", "ii", playerid, pickupid);
	else
		return 1;
}

stock INI_Exist(nickname[])
{
  new tmp[255];
  format(tmp,sizeof(tmp),"Hadmin/Hesaplar/%s.ini",Encode( nickname ) );
  return fexist(tmp);
}

stock pName( playerid )
{
	new Name[ MAX_PLAYER_NAME ];
	GetPlayerName( playerid, Name, sizeof( Name ) );
	return Name;
}

stock pIp(playerid)
{
	new ip[16];
	GetPlayerIp(playerid,ip,sizeof(ip));
	return ip;
}

stock SendYoneticiMessage(playerid, string[])
{
	new Sonuc[128];
	format(Sonuc, sizeof(Sonuc), "* {555555}((  {FF0000}.:[Yönetici]:. {FFFFFF}%s  {555555}))", string);
	return SendClientMessage(playerid, 0xFFFFFFFF, Sonuc);
}

stock SendBilgiMessage(playerid, string[])
{
	new Sonuc[128];
	format(Sonuc, sizeof(Sonuc), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s  {555555}))", string);
	return SendClientMessage(playerid, 0xFFFFFFFF, Sonuc);
}

stock SendHataMessage(playerid, string[])
{
	new Sonuc[128];
	format(Sonuc, sizeof(Sonuc), "* {555555}((  {FF0000}.:[HATA]:. {FFFFFF}%s  {555555}))", string);
	return SendClientMessage(playerid, 0xFFFFFFFF, Sonuc);
}


stock H_isNumeric(const string[])
{
  new length=strlen(string);
  if (length==0) return false;
  for (new i = 0; i < length; i++)
    {
      if (
            (string[i] > '9' || string[i] < '0' && string[i]!='-' && string[i]!='+') // Not a number,'+' or '-'
             || (string[i]=='-' && i!=0)                                             // A '-' but not at first.
             || (string[i]=='+' && i!=0)                                             // A '+' but not at first.
         ) return false;
    }
  if (length==1 && (string[0]=='-' || string[0]=='+')) return false;
  return true;
}

stock AracinIsminiYazidanBul(vname[])
{
	for(new i = 0; i < 211; i++)
	{
	if ( strfind(AracIsimleri[i], vname, true) != -1 )
	return i + 400;
	}
	return -1;
}

stock H_strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock Ucaktami(playerid)
{
new model = GetVehicleModel(GetPlayerVehicleID(playerid));

switch(model)
{
case 413,417,425,447,460,469,476,487,488,497,511,512,513,519,520,548,553,563,577,592,593: return 1;
default: return 0;
}

return 0;

}

forward RestartGM();
public RestartGM()
{
SendRconCommand("gmx");
}

public OnGameModeExit()
{
	KillTimer(SunucuGuncelle);

	print("\n ___________________________________________________");
	print(" ");
    printf("                   H.A.S                            ");
   	print("                 -------------");
	print("             Hackhers Admin System                ");
	print(" ___________________________________________________\n");
	print(" -> Kapatýldý!");
	return 1;
}

forward ZamanDus();
public ZamanDus()
{
	if(saniye == 0)
	{
	    for(new i; i < MAX_PLAYERS; i++)
	    {
	    	if(OyuncuVeri[i][Donmama] == 0)
	    	{
				TogglePlayerControllableEx(i, 1);
			}
			PlaySound(i, 1058);
		}
		GameTextForAll("~r~Hadi!",1000,3);
		KillTimer(saniyeT);
	}
	else
	{
		new string[256];
	    for(new i; i < MAX_PLAYERS; i++)
	    {
		PlaySound(i, 1057);
		}
		format(string,256,"~g~%d",saniye);
		GameTextForAll(string,1000,3);
		saniye -= 1;
	}
	return 1;
}

stock PlaySound (playerid,sound)
{
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	PlayerPlaySound(playerid, sound, X, Y, Z);
	return sound;
}

stock IsValidWeapon(weaponid)
{
    if (weaponid > 0 && weaponid < 19 || weaponid > 21 && weaponid < 47) return 1;
    return 0;
}

//DracoBlue
stock Encode(nickname[])
{
  new tmp[255];
  set(tmp,nickname);
  tmp=strreplace("_","_00",tmp);
  tmp=strreplace(";","_01",tmp);
  tmp=strreplace("!","_02",tmp);
  tmp=strreplace("/","_03",tmp);
  tmp=strreplace("\\","_04",tmp);
  tmp=strreplace("[","_05",tmp);
  tmp=strreplace("]","_06",tmp);
  tmp=strreplace("?","_07",tmp);
  tmp=strreplace(".","_08",tmp);
  tmp=strreplace("*","_09",tmp);
  tmp=strreplace("<","_10",tmp);
  tmp=strreplace(">","_11",tmp);
  tmp=strreplace("{","_12",tmp);
  tmp=strreplace("}","_13",tmp);
  tmp=strreplace(" ","_14",tmp);
  tmp=strreplace("\"","_15",tmp);
  tmp=strreplace(":","_16",tmp);
  tmp=strreplace("|","_17",tmp);
  tmp=strreplace("=","_18",tmp);
  return tmp;
}

stock set(dest[],source[]) {
	new count = strlen(source);
	new i=0;
	for (i=0;i<count;i++) {
		dest[i]=source[i];
	}
	dest[count]=0;
}
stock strreplace(trg[],newstr[],src[]) {
    new f=0;
    new s1[255];
    new tmp[255];
    format(s1,sizeof(s1),"%s",src);
    f = strfind(s1,trg);
    tmp[0]=0;
    while (f>=0) {
        strcat(tmp,ret_memcpy(s1, 0, f));
        strcat(tmp,newstr);
        format(s1,sizeof(s1),"%s",ret_memcpy(s1, f+strlen(trg), strlen(s1)-f));
        f = strfind(s1,trg);
    }
    strcat(tmp,s1);
    return tmp;
}

ret_memcpy(source[],index=0,numbytes) {
	new tmp[255];
	new i=0;
	tmp[0]=0;
	if (index>=strlen(source)) return tmp;
	if (numbytes+index>=strlen(source)) numbytes=strlen(source)-index;
	if (numbytes<=0) return tmp;
	for (i=index;i<numbytes+index;i++) {
		tmp[i-index]=source[i];
		if (source[i]==0) return tmp;
	}
	tmp[numbytes]=0;
	return tmp;
}


#if !defined sscanf
stock sscanf(string[], format[], {Float,_}:...)
{
	#if defined isnull
		if (isnull(string))
	#else
		if (string[0] == 0 || (string[0] == 1 && string[1] == 0))
	#endif
		{
			return format[0];
		}
	#pragma tabsize 4
	new
		formatPos = 0,
		stringPos = 0,
		paramPos = 2,
		paramCount = numargs(),
		delim = ' ';
	while (string[stringPos] && string[stringPos] <= ' ')
	{
		stringPos++;
	}
	while (paramPos < paramCount && string[stringPos])
	{
		switch (format[formatPos++])
		{
			case '\0':
			{
				return 0;
			}
			case 'i', 'd':
			{
				new
					neg = 1,
					num = 0,
					ch = string[stringPos];
				if (ch == '-')
				{
					neg = -1;
					ch = string[++stringPos];
				}
				do
				{
					stringPos++;
					if ('0' <= ch <= '9')
					{
						num = (num * 10) + (ch - '0');
					}
					else
					{
						return -1;
					}
				}
				while ((ch = string[stringPos]) > ' ' && ch != delim);
				setarg(paramPos, 0, num * neg);
			}
			case 'h', 'x':
			{
				new
					num = 0,
					ch = string[stringPos];
				do
				{
					stringPos++;
					switch (ch)
					{
						case 'x', 'X':
						{
							num = 0;
							continue;
						}
						case '0' .. '9':
						{
							num = (num << 4) | (ch - '0');
						}
						case 'a' .. 'f':
						{
							num = (num << 4) | (ch - ('a' - 10));
						}
						case 'A' .. 'F':
						{
							num = (num << 4) | (ch - ('A' - 10));
						}
						default:
						{
							return -1;
						}
					}
				}
				while ((ch = string[stringPos]) > ' ' && ch != delim);
				setarg(paramPos, 0, num);
			}
			case 'c':
			{
				setarg(paramPos, 0, string[stringPos++]);
			}
			case 'f':
			{
				setarg(paramPos, 0, _:floatstr(string[stringPos]));
			}
			case 'p':
			{
				delim = format[formatPos++];
				continue;
			}
			case '\'':
			{
				new
					end = formatPos - 1,
					ch;
				while ((ch = format[++end]) && ch != '\'') {}
				if (!ch)
				{
					return -1;
				}
				format[end] = '\0';
				if ((ch = strfind(string, format[formatPos], false, stringPos)) == -1)
				{
					if (format[end + 1])
					{
						return -1;
					}
					return 0;
				}
				format[end] = '\'';
				stringPos = ch + (end - formatPos);
				formatPos = end + 1;
			}
			case 'u':
			{
				new
					end = stringPos - 1,
					id = 0,
					bool:num = true,
					ch;
				while ((ch = string[++end]) && ch != delim)
				{
					if (num)
					{
						if ('0' <= ch <= '9')
						{
							id = (id * 10) + (ch - '0');
						}
						else
						{
							num = false;
						}
					}
				}
				if (num && IsPlayerConnected(id))
				{
					setarg(paramPos, 0, id);
				}
				else
				{
					#if !defined foreach
						#define foreach(%1,%2) for (new %2 = 0; %2 < MAX_PLAYERS; %2++) if (IsPlayerConnected(%2))
						#define __SSCANF_FOREACH__
					#endif
					string[end] = '\0';
					num = false;
					new
						name[MAX_PLAYER_NAME];
					id = end - stringPos;
					foreach (Player, playerid)
					{
						GetPlayerName(playerid, name, sizeof (name));
						if (!strcmp(name, string[stringPos], true, id))
						{
							setarg(paramPos, 0, playerid);
							num = true;
							break;
						}
					}
					if (!num)
					{
						setarg(paramPos, 0, INVALID_PLAYER_ID);
					}
					string[end] = ch;
					#if defined __SSCANF_FOREACH__
						#undef foreach
						#undef __SSCANF_FOREACH__
					#endif
				}
				stringPos = end;
			}
			case 's', 'z':
			{
				new
					i = 0,
					ch;
				if (format[formatPos])
				{
					while ((ch = string[stringPos++]) && ch != delim)
					{
						setarg(paramPos, i++, ch);
					}
					if (!i)
					{
						return -1;
					}
				}
				else
				{
					while ((ch = string[stringPos++]))
					{
						setarg(paramPos, i++, ch);
					}
				}
				stringPos--;
				setarg(paramPos, i, '\0');
			}
			default:
			{
				continue;
			}
		}
		while (string[stringPos] && string[stringPos] != delim && string[stringPos] > ' ')
		{
			stringPos++;
		}
		while (string[stringPos] && (string[stringPos] == delim || string[stringPos] <= ' '))
		{
			stringPos++;
		}
		paramPos++;
	}
	do
	{
		if ((delim = format[formatPos++]) > ' ')
		{
			if (delim == '\'')
			{
				while ((delim = format[formatPos++]) && delim != '\'') {}
			}
			else if (delim != 'z')
			{
				return delim;
			}
		}
	}
	while (delim > ' ');
	return 0;
}
#endif

stock DuzeltKarakter(string[]) // Teþekkürler RyDeR'
{
   for(new i; string[i] != '\0'; ++i)
   {
       switch(string[i])
       {
         case 'ý': string[i] = 'i';
         case 'ö': string[i] = 'o';
         case 'ü': string[i] = 'u';
         case 'þ': string[i] = 's';
         case 'ð': string[i] = 'g';
         case 'Ý': string[i] = 'I';
         case 'Ð': string[i] = 'G';
         case 'Ö': string[i] = 'O';
		 case 'Ü': string[i] = 'U';
		 case 'Þ': string[i] = 'S';
         default: continue;
       }
   }
   return 1;
}

stock H_HileDuyurusu(string[])
{
	for(new i; i < MAX_PLAYERS;i++)
	{
	    if(IsPlayerConnected(i))
	    {
			if(OyuncuVeri[i][Ycalisma] == 1)
			{
			SendYoneticiMessage(i, string);
			}
	    }
	}
	H_Log(string);
}

stock H_Log(log[])
{
    printf("[H-System] %s",log);
	DuzeltKarakter(log);
	new string[256];
	format(string,sizeof(string),"%s | %s | %s\r\n",TarihDon(),ZamanDon(),log);
	new File:f=fopen(H_LOG_DOSYA,io_append);
	fwrite(f,string);
	return fclose(f);
}


stock ZamanDon()
{
	new H_Zaman[16],H_h,H_m,H_s;
	gettime(H_h,H_m,H_s);
	format(H_Zaman,sizeof(H_Zaman),"%02d:%02d:%02d",H_h,H_m,H_s);
	return H_Zaman;
}


stock TarihDon()
{
	new H_Tarih[32],H_Gun,H_Ay,H_Yil;
	getdate(H_Yil,H_Ay,H_Gun);
	format(H_Tarih,sizeof(H_Tarih),"%d. %s %d",H_Gun,GetMonth(H_Ay),H_Yil);
	return H_Tarih;
}

stock HataVer(playerid, errorID)
{
switch(errorID)
{
case 1:  return SendClientMessage(playerid,0xFFFFFFFF,"* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Yeterli yönetici seviyesine sahip deðilsiniz.  {555555}))");
case 2:  return SendClientMessage(playerid,0xFFFFFFFF,"* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Oyuncu aktif deðil.  {555555}))");
case 3:  return SendClientMessage(playerid,0xFFFFFFFF,"ERROR: Player is not connected or is yourself or is the highest level admin");
case 4:  return SendClientMessage(playerid,0xFFFFFFFF,"ERROR: Player is not connected or is yourself");
case 5:  return SendClientMessage(playerid,0xFFFFFFFF,"ERROR: You need to be Level 4 to use this Command");
case 6:  return SendClientMessage(playerid,0xFFFFFFFF,"ERROR: You need to be Level 3 to use this Command");
case 7:  return SendClientMessage(playerid,0xFFFFFFFF,"ERROR: You need to be Level 2 to use this Command");
case 8:  return SendClientMessage(playerid,0xFFFFFFFF,"ERROR: You need to be Level 1 to use this Command");
case 9: return SendClientMessage(playerid,0xFFFFFFFF,"* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Komudu kullanmak için araçta olmalýsýnýz.  {555555}))");
case 10: return SendClientMessage(playerid,0xFFFFFFFF,"* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Zaten bir araçtasýnýz.  {555555}))");
}
return 1;
}

stock GetMonth(number)  // Optimise eden Y_Less
{
    static const
        sc_months[][32] =
        {
            "\1", // NULL
            "Ocak",
            "Þubat",
            "Mart",
            "Nisan",
            "Mayýs",
            "Haziran",
            "Temmuz",
            "Aðustos",
            "Eylül",
            "Ekim",
            "Kasým",
            "Aralýk"
        };
    if (1 <= number <= 12)
    {
        return sc_months[number];
    }
    return sc_months[0];
}


//--------------------------------------------[Komutlar Baþlangýç]--------------------------------------------//
CMD:kayit( playerid, params[ ] )
{
	#pragma unused params
	if ( GetPVarInt( playerid, "Gyapti" ) == 1 )
	    return SendClientMessage( playerid, -1, ""yKirmizi"Hata:{FFFFFF} Zaten kayýtlýsýnýz ve giriþ yapmýþsýnýz.");

    ShowPlayerDialog( playerid, DIALOG_Kayit, DIALOG_STYLE_INPUT, "{FFFFFF}Kayýt Yapýlýyor...", "{FFFFFF}Lütfen mevcut þifrenizi girin.", ">>>", "Çýkýþ");
	return 1;
}
CMD:giris( playerid, params[ ] )
{
	#pragma unused params
	if ( GetPVarInt( playerid, "Gyapti" ) == 1 )
	    return SendClientMessage( playerid, -1, ""yKirmizi"Hata:{FFFFFF} Zaten kayýtlýsýnýz ve giriþ yapmýþsýnýz.");

    ShowPlayerDialog( playerid, DIALOG_Giris2, DIALOG_STYLE_INPUT, "{FFFFFF}Giriþ", "{FFFFFF}Lütfen mevcut þifrenizi girin", "Giriþ", "Çýkýþ");
	return 1;
}
CMD:bilgi( playerid, params[ ] )
{
	if ( GetPVarInt( playerid, "Gyapti" ) == 0 )
	    return SendClientMessage( playerid, -1, ""yKirmizi"ERROR:{FFFFFF}Bilgileriniz Görmek için Kayýt Yapmýþ olmalýsýnýz");

	new
		iBox[ 256 ],
		RegDate[ 10 + 15 ]
	;

	RegDate = OyuncuVeri[playerid][KTarih];
	format( iBox, sizeof iBox, "{FFFFFF}Merhaba "yAcikMavi"%s{FFFFFF}, Bunlar hesap bilgileriniz\n\n\
	                            {FFFFFF}Para: "yAcikMavi"%d\n\
	                            {FFFFFF}Skor: "yAcikMavi"%d\n\
	                            {FFFFFF}Kayýt Tarihi: "yAcikMavi"%s\n\
	                            {FFFFFF}Interior: "yAcikMavi"%d\n\
								{FFFFFF}Virtual World: "yAcikMavi"%d",pName( playerid ),
											  GetPlayerMoneyEx( playerid ),
											  GetPlayerScoreEx( playerid ),
											  RegDate,
											  GetPlayerInterior( playerid ),
											  GetPlayerVirtualWorld( playerid ) )
								;
	ShowPlayerDialog( playerid, DIALOG_STATLAR, DIALOG_STYLE_MSGBOX, "{FFFFFF}Bilgilerim!", iBox, "Tamam", "");
	return 1;
}
//--------------------------------------------[Seviye 1]--------------------------------------------//
cmd(yoneticiler, playerid, params[]) // RyDeR'
{
   new
      string[256],
      adminCount,
      i
   ;
   for( ; i != MAX_PLAYERS; ++i)
   {
      if(IsPlayerConnected(i) && !IsPlayerNPC(i))
      {
		 new admtext[64];
         if(OyuncuVeri[i][Admin] > 0)
         {
	        if(OyuncuVeri[i][Admin] == 5) { admtext = "Lider Yönetici"; }
  	        else if(OyuncuVeri[i][Admin] == 4) { admtext = "Yüksek Yönetici"; }
			else if(OyuncuVeri[i][Admin] == 3) { admtext = "Orta Yönetici"; }
			else if(OyuncuVeri[i][Admin] == 2) { admtext = "Baþlangýç Yönetici"; }
			else if(OyuncuVeri[i][Admin] == 1) { admtext = "Basit Yönetici"; }
            format(string, sizeof string, "%sYönetici:%s[%d] - %s\n", string, pName(i), i, admtext);
            ++adminCount;
         }
      }
   }
   return ShowPlayerDialog(playerid, 0xFF, DIALOG_STYLE_MSGBOX, "Aktif Yoneticiler", (!adminCount) ? ("Sunucuda yönetici yok!") : (string), "Kapat", ""), 1;
}

cmd(admins, playerid, parmas[])
{
return cmd_yoneticiler(playerid, parmas);
}

CMD:level(playerid, params[])
{
	if(OyuncuVeri[playerid][Admin] < 1)
		return HataVer(playerid, 1);

	new
		Yazi[1024]
	;

	if(OyuncuVeri[playerid][Admin] >= 1)
	{
	format(Yazi, sizeof(Yazi), "{FFFFFF}___________ |- Hadmin - Basit Yönetici (Seviye 1) -| ___________\n\
  								{53D212}Oyuncu: kontrol, git, cek, skinayar\n\
                                {33F666}Araç: tamir, nos, tcar\n\
								{53D212}Iþýnlanma: ygit [LS,SF,LV]\n\
		  						{33F666}Yönetici: acalisma, ymekan, tod\n\
           						{53D212}Diðer: zenginler\n\n");
	}
	if(OyuncuVeri[playerid][Admin] >= 2)
	{
	format(Yazi, sizeof(Yazi), "%s{FFFFFF}___________ |- Hadmin - Baþlangýç Yönetici (Seviye 2) -| ___________\n\
  								{53D212}Oyuncu: silahver, renkayar, yak, jetpack, cevir, sik, saplak, sustur, konustur\n\
                                {33F666}Araç: hcar, hbike, hheli, hboat, hplane\n\
		  						{33F666}Yönetici: Hmenu, chatsil, yaz, duyurun\n\n",Yazi);
	}
	if(OyuncuVeri[playerid][Admin] >= 3)
	{
	format(Yazi, sizeof(Yazi), "%s{FFFFFF}___________ |- Hadmin - Orta Yönetici (Seviye 3) -| ___________\n\
								{53D212}Ayarlama: ayar (can/zirh/para/skor/skin/aranma/isim/hava/saat/dunya/interior/ping/gravity)\n\
                                {33F666}Oyuncu: holdur, dondurcoz, kick, patlat, hapset, hapiscikar,  aractanat, parabitir\n\
								{33F666}Araç: arac, araccan, aracrenk, aracsil, araccek, aracver\n\
		  						{33F666}Yönetici: gerisayim, gorunur, gorunmez\n\n",Yazi);
	}
	if(OyuncuVeri[playerid][Admin] >= 4)
	{
  	ShowPlayerDialog(playerid, 999+999, DIALOG_STYLE_MSGBOX, "Yönetici Komutlarý", Yazi, "Ok", "");
  	}
  	else
  	{
  	ShowPlayerDialog(playerid, DIALOG_LOG_BASAR, DIALOG_STYLE_MSGBOX, "Yönetici Komutlarý", Yazi, "Ok", "");
  	}
	return 1;
}

/*===============================================[Seviye 1]===============================================*/
CMD:setskin(playerid, params[])
{
	if(OyuncuVeri[playerid][Admin] < 1)
		return HataVer(playerid, 1);
	new
		pID,
		sID,
		Yazi[128]
	;
	if(sscanf(params, "ri", pID, sID))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /setskin [Isim/ID] [SkinID].  {555555}))");

	if(!IsPlayerConnected(pID))
	    return HataVer(playerid, 2);

	if(sID > 300)
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Skin ID 0 ile 300 arasýnda olmalýdýr.  {555555}))");

	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizin skininizi %d olarak ayarladý.  {555555}))", pName(playerid), sID);
	SendClientMessage(pID, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, skinini %d olarak ayarladýnýz.  {555555}))", pName(pID), sID);
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	SetPlayerSkinEx(pID, sID);
	return 1;
}
cmd(skinayar, playerid, params[])
{
return cmd_setskin(playerid, params);
}

CMD:goto(playerid, params[])
{
	if(OyuncuVeri[playerid][Admin] < 1)
		return HataVer(playerid, 1);

	new
		pID,
		Yazi[128]
	;
	if(sscanf(params, "r", pID))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /goto [Isim/ID].  {555555}))");

	if(!IsPlayerConnected(pID))
	    return HataVer(playerid, 2);

	new
	    Float: Gx,
	    Float: Gy,
		Float: Gz
	;

	GetPlayerPos(pID, Gx, Gy, Gz);
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(pID));
	SetPlayerInterior(playerid, GetPlayerInterior(pID));
	AraclaGonder(playerid, Gx+1, Gy+1, Gz);

	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizin yanýnýza ýþýnlandý.  {555555}))", pName(playerid));
	SendClientMessage(pID, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, Yanýna ýþýnlandýnýz.  {555555}))", pName(pID));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}
cmd(git, playerid, params[])
{
return cmd_goto(playerid, params);
}


CMD:gethere(playerid, params[])
{
	if(OyuncuVeri[playerid][Admin] < 1)
		return HataVer(playerid, 1);

	new
		pID,
		Yazi[128]
	;
	if(sscanf(params, "r", pID))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /gethere [Isim/ID].  {555555}))");

	if(!IsPlayerConnected(pID))
	    return HataVer(playerid, 2);

	new
	    Float: Gx,
	    Float: Gy,
		Float: Gz
	;

	GetPlayerPos(playerid, Gx, Gy, Gz);
	SetPlayerVirtualWorld(pID, GetPlayerVirtualWorld(playerid));
	SetPlayerInterior(pID, GetPlayerInterior(playerid));
	AraclaGonder(pID, Gx+1, Gy+1, Gz);

	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizi yanýna çekti.  {555555}))", pName(playerid));
	SendClientMessage(pID, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, yanýnýza çektiniz.  {555555}))", pName(pID));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}
cmd(cek, playerid, params[])
{
return cmd_gethere(playerid, params);
}

CMD:kontrol(playerid, params[])
{
	if(OyuncuVeri[playerid][Admin] < 1)
		return HataVer(playerid, 1);

	new
		pID
	;
	if(sscanf(params, "r", pID))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /kontrol [Isim/ID].  {555555}))");

	if(!IsPlayerConnected(pID))
	    return HataVer(playerid, 2);

	new
		sTitle[ 21 + MAX_PLAYER_NAME + 25 ],
		sBoxInfo[ 512 ]
	;
	        	    //GetPVarString( playerid, "Kayit_Tarih", Pdata, 8 + 10 );
 	format( sTitle, sizeof sTitle, "{FFFFFF}Kontrol ettiðiniz Þahýs: "yAcikMavi"%s{FFFFFF}!", pName( pID ) );
  	format( sBoxInfo, sizeof sBoxInfo, "{FFFFFF}Hesap Bilgileri:\n\n\
   										{FFFFFF}Bakiye: "yAcikMavi"%d\n\
     									{FFFFFF}Skor: "yAcikMavi"%d\n\
              							{FFFFFF}Kayýt tarihi: "yAcikMavi"%s\n\
										{FFFFFF}Skin: "yAcikMavi"%d",  OyuncuVeri[pID][Para],
										OyuncuVeri[pID][Skor],
						    			OyuncuVeri[pID][KTarih],
										GetPlayerSkinEx(pID) );

	ShowPlayerDialog(playerid, DIALOG_LOG_BASAR, DIALOG_STYLE_MSGBOX, sTitle, sBoxInfo, "Ok", "");
	return 1;
}

CMD:tamir(playerid, params[])
{
    if(OyuncuVeri[playerid][Admin] < 1)
  		return HataVer(playerid, 1);

	if(!IsPlayerInAnyVehicle(playerid))
		return HataVer(playerid, 9);

	RepairVehicle(GetPlayerVehicleID(playerid));
	SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Aracýnýzý tamir ettiniz.  {555555}))");
	ModifiyeSes(playerid);
	return 1;
}
cmd(repair, playerid, params[])
{
return cmd_tamir(playerid, params);
}

CMD:nos(playerid, params[])
{
    if(OyuncuVeri[playerid][Admin] < 1)
  		return HataVer(playerid, 1);

	if(!IsPlayerInAnyVehicle(playerid))
		return HataVer(playerid, 9);

	AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
	SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Aracýnýza nos taktýnýz.  {555555}))");
	ModifiyeSes(playerid);
	return 1;
}

CMD:tcar(playerid, params[])
{
    if(OyuncuVeri[playerid][Admin] < 1)
  		return HataVer(playerid, 1);

	if(IsPlayerInAnyVehicle(playerid))
		return HataVer(playerid, 10);

	new Arac;
 	if(sscanf(params, "i", Arac))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /tcar [ID].  {555555}))");

	//=================================[1]=================================
	if(Arac == 1)
	{
	new Float:X,Float:Y,Float:Z,Float:Angle,HAracIDt;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
 	HAracIDt = CreateVehicle(560,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,HAracIDt,0);
	AddVehicleComponent(HAracIDt, 1028);	AddVehicleComponent(HAracIDt, 1030);	AddVehicleComponent(HAracIDt, 1031);	AddVehicleComponent(HAracIDt, 1138);	AddVehicleComponent(HAracIDt, 1140);  AddVehicleComponent(HAracIDt, 1170);
 	AddVehicleComponent(HAracIDt, 1028);	AddVehicleComponent(HAracIDt, 1030);	AddVehicleComponent(HAracIDt, 1031);	AddVehicleComponent(HAracIDt, 1138);	AddVehicleComponent(HAracIDt, 1140);  AddVehicleComponent(HAracIDt, 1170);
 	AddVehicleComponent(HAracIDt, 1080);	AddVehicleComponent(HAracIDt, 1086); AddVehicleComponent(HAracIDt, 1087); AddVehicleComponent(HAracIDt, 1010);
	ModifiyeSes(playerid);
	ChangeVehiclePaintjob(HAracIDt,1);
	SetVehicleVirtualWorld(HAracIDt, GetPlayerVirtualWorld(playerid));
 	LinkVehicleToInterior(HAracIDt, GetPlayerInterior(playerid));
	}
	//=================================[2]=================================
	else if(Arac == 2)
	{
	new Float:X,Float:Y,Float:Z,Float:Angle,HAracIDt;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
 	HAracIDt = CreateVehicle(560,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,HAracIDt,0);
	AddVehicleComponent(HAracIDt, 1028);	AddVehicleComponent(HAracIDt, 1030);	AddVehicleComponent(HAracIDt, 1031);	AddVehicleComponent(HAracIDt, 1138);	AddVehicleComponent(HAracIDt, 1140);  AddVehicleComponent(HAracIDt, 1170);
 	AddVehicleComponent(HAracIDt, 1080);	AddVehicleComponent(HAracIDt, 1086); AddVehicleComponent(HAracIDt, 1087); AddVehicleComponent(HAracIDt, 1010);
 	ModifiyeSes(playerid);
	ChangeVehiclePaintjob(HAracIDt,2);
	SetVehicleVirtualWorld(HAracIDt, GetPlayerVirtualWorld(playerid));
 	LinkVehicleToInterior(HAracIDt, GetPlayerInterior(playerid));
	}
	//=================================[3]=================================
	else if(Arac == 3)
	{
	new Float:X,Float:Y,Float:Z,Float:Angle,carid;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
 	carid = CreateVehicle(559,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,carid,0);
	AddVehicleComponent(carid,1065); AddVehicleComponent(carid,1067); AddVehicleComponent(carid,1162);
	AddVehicleComponent(carid,1010); AddVehicleComponent(carid,1073);
	ChangeVehiclePaintjob(carid,1);
	SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
  	LinkVehicleToInterior(carid, GetPlayerInterior(playerid));
	}
	//=================================[4]=================================
	else if(Arac == 4)
 	{
	new Float:X,Float:Y,Float:Z,Float:Angle,carid;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
 	carid = CreateVehicle(565,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,carid,0);
 	AddVehicleComponent(carid,1046);
	AddVehicleComponent(carid,1049); AddVehicleComponent(carid,1053);
	AddVehicleComponent(carid,1010); AddVehicleComponent(carid,1073);
	ChangeVehiclePaintjob(carid,1);
	SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
  	LinkVehicleToInterior(carid, GetPlayerInterior(playerid));
	}
	//=================================[5]=================================
	else if(Arac == 5)
 	{
	new Float:X,Float:Y,Float:Z,Float:Angle,carid;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
 	carid = CreateVehicle(558,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,carid,0);
	AddVehicleComponent(carid,1088); AddVehicleComponent(carid,1092);
	AddVehicleComponent(carid,1139); AddVehicleComponent(carid,1010);
	AddVehicleComponent(carid,1073);
	ChangeVehiclePaintjob(carid,1);
	SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(carid,
	GetPlayerInterior(playerid));
	}
	//=================================[6]=================================
	else if(Arac == 6)
 	{
	new Float:X,Float:Y,Float:Z,Float:Angle,HAracIDt;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
   	HAracIDt = CreateVehicle(560,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,HAracIDt,0);
	AddVehicleComponent(HAracIDt, 1087); AddVehicleComponent(HAracIDt, 1010);
	AddVehicleComponent(HAracIDt, 1138); AddVehicleComponent(HAracIDt, 1170);
	AddVehicleComponent(HAracIDt, 1030); AddVehicleComponent(HAracIDt, 1028);
	AddVehicleComponent(HAracIDt, 1170); AddVehicleComponent(HAracIDt, 1031);
   	AddVehicleComponent(HAracIDt, 1080); AddVehicleComponent(HAracIDt, 1140);
	AddVehicleComponent(HAracIDt, 1086); AddVehicleComponent(HAracIDt, 1028);
	AddVehicleComponent(HAracIDt, 1030);	AddVehicleComponent(HAracIDt, 1031);
	AddVehicleComponent(HAracIDt, 1140); AddVehicleComponent(HAracIDt, 1138);
    ModifiyeSes(playerid);
	ChangeVehiclePaintjob(HAracIDt,0);
	SetVehicleVirtualWorld(HAracIDt,GetPlayerVirtualWorld(playerid));
   	LinkVehicleToInterior(HAracIDt,GetPlayerInterior(playerid));
	}
	//=================================[7]=================================
	else if(Arac == 7)
 	{
	new Float:X,Float:Y,Float:Z,Float:Angle,carid;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
 	carid = CreateVehicle(562,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,carid,0);
	AddVehicleComponent(carid,1034); AddVehicleComponent(carid,1038);
	AddVehicleComponent(carid,1147); AddVehicleComponent(carid,1010);
	AddVehicleComponent(carid,1073);
	ChangeVehiclePaintjob(carid,1);
	SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
  	LinkVehicleToInterior(carid, GetPlayerInterior(playerid));
	}
	//=================================[8]=================================
	else if(Arac == 8)
 	{
	new Float:X,Float:Y,Float:Z,Float:Angle,carid;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
    carid = CreateVehicle(535,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,carid,0);
	ChangeVehiclePaintjob(carid,1); AddVehicleComponent(carid,1109);
	AddVehicleComponent(carid,1115); AddVehicleComponent(carid,1117);
	AddVehicleComponent(carid,1073); AddVehicleComponent(carid,1010);
 	AddVehicleComponent(carid,1087); AddVehicleComponent(carid,1114);
	AddVehicleComponent(carid,1081); AddVehicleComponent(carid,1119);
	AddVehicleComponent(carid,1121);
	SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
  	LinkVehicleToInterior(carid, GetPlayerInterior(playerid));
	}
	//=================================[9]=================================
	else if(Arac == 9)
 	{
	new Float:X,Float:Y,Float:Z,Float:Angle,carid;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
 	carid = CreateVehicle(558,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,carid,0);
   	AddVehicleComponent(carid,1092); AddVehicleComponent(carid,1166);
  	AddVehicleComponent(carid,1165); AddVehicleComponent(carid,1090);
   	AddVehicleComponent(carid,1094); AddVehicleComponent(carid,1010);
	AddVehicleComponent(carid,1087); AddVehicleComponent(carid,1163);
 	AddVehicleComponent(carid,1091);
	ChangeVehiclePaintjob(carid,2);
	SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
  	LinkVehicleToInterior(carid, GetPlayerInterior(playerid));
	}
	//=================================[10]=================================
	else if(Arac == 10)
	{
	new Float:X,Float:Y,Float:Z,Float:Angle,carid;
	GetPlayerPos(playerid,X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
 	carid = CreateVehicle(562,X,Y,Z,Angle,1,-1,-1);
	PutPlayerInVehicle(playerid,carid,0);
  	AddVehicleComponent(carid,1034); AddVehicleComponent(carid,1038);
  	AddVehicleComponent(carid,1147); AddVehicleComponent(carid,1010);
  	AddVehicleComponent(carid,1073);
  	ChangeVehiclePaintjob(carid,0);
  	SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
    LinkVehicleToInterior(carid, GetPlayerInterior(playerid));
	}
 	//======================================================================
	else
	{
  	return SendClientMessage(playerid, 0xFFFFFFFF, "{FFFFFF}* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Modifiye edilmiþ araç IDsi 1-10 arasýnda olmalýdýr.  {555555}))");
	}
	if(OyuncuVeri[playerid][pArac] != -1)
	AraciSil(OyuncuVeri[playerid][pArac]);
	OyuncuVeri[playerid][pArac] = GetPlayerVehicleID(playerid);
	return 1;
}

cmd(ygit, playerid, parmas[])
{
    if(OyuncuVeri[playerid][Admin] < 1)
  		return HataVer(playerid, 1);

	new str[70];
	if(sscanf(parmas, "s[64]", str))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /git [isim].  {555555}))");

	if(strfind(str, "istanbul", true) == 0 || strfind(str, "ls", true) == 0)
	AraclaGonder(playerid, 1529.6,-1691.2,13.3);
	else if (strfind(str, "sf", true) == 0)
	AraclaGonder(playerid, -1417.0,-295.8,14.1);
	else if (strfind(str, "lv", true) == 0)
	AraclaGonder(playerid, 1699.2,1435.1, 10.7);

	return 1;
}

cmd(acalisma, playerid, parmas[])
{
    if(OyuncuVeri[playerid][Admin] < 1)
  		return HataVer(playerid, 1);
	new Yazi[128];
	switch(OyuncuVeri[playerid][Ycalisma])
	{
		case 0:
		{
		format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, müsait.  {555555}))", pName(playerid));
		SendClientMessageToAll(0xFFFFFFFF, Yazi);
        SetPlayerColor(playerid,0xFF0000FF);
        OyuncuVeri[playerid][Ycalisma] = 1;
		}
		case 1:
		{
		format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, meþgul.  {555555}))", pName(playerid));
		SendClientMessageToAll(0xFFFFFFFF, Yazi);
		SetPlayerColor(playerid,0xFFFFFFFF);
  		OyuncuVeri[playerid][Ycalisma] = 0;
		}
	}
	return 1;
}
cmd(awork,playerid, params[])
{
return cmd_acalisma(playerid, params);
}

cmd(ymekan, playerid, parmas[])
{
    if(OyuncuVeri[playerid][Admin] < 1)
  		return HataVer(playerid, 1);
	SetPlayerVirtualWorld(playerid, YONETICI_MEKAN_VW);
	SetPlayerInterior(playerid, YONETICI_MEKAN_INT);
	SetPlayerPosEx(playerid, YONETICI_MEKAN_POS);
	SendClientMessage(playerid,0xFFFFFFFF, "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici Mekanýna ýþýnlandýnýz.  {555555}))");

	return 1;
}

cmd(zenginler, playerid, parmas[])
{
   if(OyuncuVeri[playerid][Admin] < 1)
   	return HataVer(playerid, 1);
   	
   new
      string[256],
      adminCount,
      i
   ;
   for( ; i != MAX_PLAYERS; ++i)
   {
      if(IsPlayerConnected(i) && !IsPlayerNPC(i))
      {
         if(GetPVarInt(playerid, "Gyapti") == 1)
         {
            format(string, sizeof string, "%sOyuncu:%s[%d] - %s\n", string, pName(i), i, GetPlayerMoneyEx(playerid));
            ++adminCount;
         }
      }
   }
   return ShowPlayerDialog(playerid, 0xFF, DIALOG_STYLE_MSGBOX, "Aktif Yoneticiler", (!adminCount) ? ("Sunucuda yönetici yok!") : (string), "Kapat", ""), 1;
}

/*===============================================[Seviye 2]===============================================*/
cmd(silahver, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new id, pMiktar, pTur, Yazi[128];

	if(sscanf(parmas, "iii", id,pMiktar,pTur))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /Silahver [ID/isim] [SilahID] [Mermi].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	    
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, size %d silahýný ve %d kadar mermi verdi.  {555555}))", pName(playerid),pMiktar, pTur);
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, %d silahýný ve %d kadar mermi verdiniz.  {555555}))", pName(id), pMiktar, pTur);
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	GivePlayerWeaponEx(id, pMiktar, pTur);
	return 1;
}
cmd(givegun, playerid, parmas[])
{
return cmd_silahver(playerid, parmas);
}

cmd(yak, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /yak [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizi yaktý.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, yaktýnýz.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);

	new Float:x, Float:y, Float:z;
	GetPlayerPos(id, x, y, z);
	return CreateExplosion(x, y , z + 3, 1, 10);
}

cmd(burn, playerid, parmas[])
{
return cmd_yak(playerid, parmas);
}

cmd(jetpack, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /jetpack [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, size jetpack verdi.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, jetpack verdiniz.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);

	return OyuncuVeri[id][JetPack] = 1,SetPlayerSpecialAction(id, 2);
}

cmd(cevir, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new VehicleID, Float:X, Float:Y, Float:Z, Float:Angle;
	GetPlayerPos(playerid, X, Y, Z);
	VehicleID = GetPlayerVehicleID(playerid);
	GetVehicleZAngle(VehicleID, Angle);
	SetVehiclePos(VehicleID, X, Y, Z);
	SetVehicleZAngle(VehicleID, Angle);
	SetVehicleHealth(VehicleID,1000.0);

	return 1;
}

cmd(flip, playerid, parmas[])
{
return cmd_cevir(playerid, parmas);
}

cmd(uyar, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new Yazi[256-64], id, neden[96];

	if(sscanf(parmas, "is[95]", id, neden))
		return SendHataMessage(playerid, "Kullaným: /uyar [ID/isim] [Neden]");

	OyuncuVeri[id][Uyari] += 1;
	switch(OyuncuVeri[id][Uyari])
	{
		case MAX_UYARI:
		{
		format(Yazi, sizeof(Yazi), "* {555555}((  {FF0000}.:[CEZA]:. {FFFFFF}Yönetici %s, %s adlý oyuncuyu attý. Gerekçe: %s (Uyarýlar: %d/%d) {555555}))", pName(playerid), pName(id), neden, OyuncuVeri[id][Uyari], MAX_UYARI);
		SendClientMessageToAll(0xFF0000FF, Yazi);
		H_LogEx("%s (%s) sunucudan atýldý. Gerekçe:%s.",pName(playerid),pIp(playerid),neden);
		Kick(id);
		}
		default:
		format(Yazi, sizeof(Yazi), "* {555555}((  {FF0000}.:[CEZA]:. {FFFFFF}Yönetici %s, %s adlý oyuncuyu uyardý. Gerekçe: %s (Uyarýlar: %d/%d) {555555}))", pName(playerid), pName(id), neden, OyuncuVeri[id][Uyari], MAX_UYARI),
		SendClientMessageToAll(0xFF0000FF, Yazi);
	}
	return 1;
}

cmd(warn, playerid, parmas[])
{
return cmd_uyar(playerid, parmas);
}


cmd(saplak, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /saplak [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	new Float:sXp,Float:sYp,Float:sZp;
	GetPlayerPos(id, sXp, sYp, sZp);
	SetPlayerPosEx(id, sXp, sYp, sZp+5);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, size þaplak attý.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, þaplak attýnýz.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}

cmd(slap, playerid, parmas[])
{
return cmd_saplak(playerid, parmas);
}

cmd(sustur, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new id, zaman, Yazi[128], neden[64];

	if(sscanf(parmas, "iis[64]", id, zaman, neden))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /sustur [ID/isim] [Dakika] [Gerekçe].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	    
	format(Yazi, sizeof(Yazi), "* {555555}((  {FF0000}.:[CEZA]:. {FFFFFF}Yönetici %s, %s adlý oyuncuyu susturdu. Gerekçe: %s {555555}))", pName(playerid), pName(id), neden, OyuncuVeri[id][Uyari], MAX_UYARI),
	SendClientMessageToAll(0xFF0000FF, Yazi);

	return OyuncuVeri[playerid][Sus] = zaman*60;
}

cmd(mute, playerid, parmas[])
{
return cmd_sustur(playerid, parmas);
}

cmd(konustur, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new id,Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /konustur [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	format(Yazi, sizeof(Yazi), "* {555555}((  {FF0000}.:[Düzeltme]:. {FFFFFF}Yönetici %s, %s adlý oyuncuyu susturmasýný kaldýrdý. {555555}))", pName(playerid), pName(id)),
	SendClientMessage(playerid, 0xFF0000FF, Yazi);

	return OyuncuVeri[playerid][Sus] = 0;
}

CMD:hcar(playerid,params[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);
		
	switch(!IsPlayerInAnyVehicle(playerid))
	{
	    case 1:
		return AracSpawnla(playerid,411),
		SendBilgiMessage(playerid, "Aracýnýz yaratýldý");
		case 0:
		return HataVer(playerid, 10);
	}
	return 1;
}

CMD:hheli(playerid,params[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	switch(!IsPlayerInAnyVehicle(playerid))
	{
	    case 1:
		return AracSpawnla(playerid,487),
		SendBilgiMessage(playerid, "Aracýnýz yaratýldý");
		case 0:
		return HataVer(playerid, 10);
	}
	return 1;
}

CMD:hboat(playerid,params[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	switch(!IsPlayerInAnyVehicle(playerid))
	{
	    case 1:
		return AracSpawnla(playerid,493),
	    SendBilgiMessage(playerid, "Aracýnýz yaratýldý");
		case 0:
		return HataVer(playerid, 10);
	}
	return 1;
}
CMD:hplane(playerid,params[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	switch(!IsPlayerInAnyVehicle(playerid))
	{
	    case 1:
		return AracSpawnla(playerid,520),
		SendBilgiMessage(playerid, "Aracýnýz yaratýldý");
		case 0:
		return HataVer(playerid, 10);
	}
	return 1;
}

CMD:hbike(playerid,params[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	switch(!IsPlayerInAnyVehicle(playerid))
	{
	    case 1:
		return AracSpawnla(playerid,522),
	    SendBilgiMessage(playerid, "Aracýnýz yaratýldý");
		case 0:
		return HataVer(playerid, 10);
	}
	return 1;
}

CMD:hmenu(playerid,params[])
{

	if(OyuncuVeri[playerid][Admin] < 2)
    	return HataVer(playerid, 1);

	TogglePlayerControllableEx(playerid,false);
	return ShowPlayerDialog(playerid, DIALOG_HMENU, DIALOG_STYLE_LIST, "Hadmin Anamenü",
	"Sunucu Havasý\nSunucu Zamaný\nAraç\nModifiye Menüsü\nSilahlar", "Seç","Ýptal");
}

cmd(chatsil, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);
		
	for(new i = 0; i != 64; i++)
	SendClientMessageToAll(0xFFFFFFFF, "");
	SendBilgiMessage(playerid, "Bütün Oyuncularýn Chat'i temizlendi");
	return 1;
}

cmd(clearchat, playerid, parmas[])
{
return cmd_chatsil(playerid, parmas);
}

cmd(duyuru, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 2)
		return HataVer(playerid, 1);

	new Yazi[128];

	if(sscanf(parmas, "s[64]", Yazi))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /duyuru [Yazý].  {555555}))");

	format(Yazi, sizeof(Yazi),"* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, %s. {555555}))",pName(playerid), Yazi);
 	SendClientMessageToAll(0xFFFFFFFF, Yazi);
 	return 1;
}
//============================================[3. Seviye]============================================//
cmd(ayar, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new Yazi[128], id, pMiktar;

	if(sscanf(parmas, "s[64]ii", Yazi, id, pMiktar))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /ayar [isim] [ID] [Miktar].  {555555}))");

	switch(IsPlayerConnected(id))
	{
	case 0: return SendHataMessage(playerid, "Oyuncu aktif deðil");
	}

	if(strfind(Yazi, "can", true) == 0 || strfind(Yazi, "health", true) == 0)
	{
	SetPlayerHealth(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin canýnýzý %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, canýný %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "zirh", true) == 0 || strfind(Yazi, "armour", true) == 0)
	{
	SetPlayerArmour(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin zýrh %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, zýrhýný %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "para", true) == 0 || strfind(Yazi, "money", true) == 0)
	{
	SetPlayerMoneyEx(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin paranýzý %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, paranýzý %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "skor", true) == 0 || strfind(Yazi, "score", true) == 0)
	{
	SetPlayerScoreEx(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin skorunuzu %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, skorunu %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "skin", true) == 0 || strfind(Yazi, "kiyafet", true) == 0)
	{
	SetPlayerSkinEx(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin skininizi %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, skinini %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "aranma", true) == 0 || strfind(Yazi, "wanted", true) == 0)
	{
	SetPlayerWantedLevel(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin aranma seviyenizi %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, aranma seviyesini %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "hava", true) == 0 || strfind(Yazi, "weather", true) == 0)
	{
	SetPlayerWeather(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin havanýzý %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, havasýný %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "saat", true) == 0 || strfind(Yazi, "time", true) == 0)
	{
	SetPlayerTime(id, pMiktar, 0);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin saatinizi %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, saatini %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "dunya", true) == 0 || strfind(Yazi, "world", true) == 0)
	{
	SetPlayerVirtualWorld(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin dünyanýzý %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, dünyasýný %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	else if(strfind(Yazi, "interior", true) == 0 || strfind(Yazi, "int", true) == 0)
	{
	SetPlayerInterior(id, pMiktar);
	format(Yazi, sizeof(Yazi), "Yönetici %s, sizin interiorunuzu %d olarak ayarladý.", pName(playerid), pMiktar);
	SendBilgiMessage(id, Yazi);
	format(Yazi, sizeof(Yazi), "%s, interiorunu %d olarak ayarladýnýz.", pName(id), pMiktar);
	SendBilgiMessage(playerid, Yazi);
	}
	return 1;
}
cmd(set, playerid, parmas[])
{
return cmd_ayar(playerid, parmas);
}

cmd(hkill, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /hkill [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	    
	SetPlayerHealth(id, 0);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizi öldürdü.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, öldürdünüz.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}
cmd(holdur, playerid, parmas[])
{
return cmd_hkill(playerid, parmas);
}

cmd(dondurcoz, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /dondurcoz [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	switch(OyuncuVeri[playerid][Donmama])
	{
		case 0:
		{
		TogglePlayerControllableEx(id, true);
		format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizi çözdü.  {555555}))", pName(playerid));
		SendClientMessage(id, 0xFFFFFFFF, Yazi);
		format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, çözdünüz.  {555555}))", pName(id));
		SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
		}
		case 1:
		{
		TogglePlayerControllableEx(id, false);
		format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizi dondurdu.  {555555}))", pName(playerid));
		SendClientMessage(id, 0xFFFFFFFF, Yazi);
		format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, dondurdu.  {555555}))", pName(id));
		SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
		}
	}
	return 1;
}

cmd(freeze, playerid, parmas[])
{
return cmd_dondurcoz(playerid, parmas);
}

cmd(kick, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, neden[96], Yazi[128];

	if(sscanf(parmas, "is[90]", id, neden))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /kick [ID/isim] [Neden].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	format(Yazi, sizeof(Yazi), "* {555555}((  {FF0000}.:[CEZA]:. {FFFFFF}Yönetici %s, %s adlý oyuncuyu attý. Gerekçe: %s  {555555}))", pName(playerid), pName(id), neden, OyuncuVeri[id][Uyari], MAX_UYARI);
	SendClientMessageToAll(0xFF0000FF, Yazi);
	H_LogEx("%s (%s) sunucudan atýldý. Gerekçe:%s.",pName(playerid),pIp(playerid),neden);
	Kick(id);
	return 1;
}

cmd(at, playerid, parmas[])
{
return cmd_kick(playerid, parmas);
}

cmd(patlat, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /patlat [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	new Float:pXy,
	    Float:pYy,
	    Float:pZy
	;
	GetPlayerPos(id, pXy, pYy, pZy);
	CreateExplosion(pXy, pYy, pZy, 7, 5.0);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizi patlattý.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, patlattýnýz.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}

cmd(explode, playerid, parmas[])
{
return cmd_patlat(playerid, parmas);
}

cmd(jail, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, dakika, neden[96],Yazi[128];

	if(sscanf(parmas, "iis[90]", id,dakika,neden))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /jail [ID/isim] [Dakika] [Gerekçe].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	    
	OyuncuVeri[id][Hapis] = dakika*60;
	SetPlayerPosEx(id, 107.2300,1920.6311,18.5208);
	SetPlayerWorldBounds(id, 337.5694,101.5826,1940.9759,1798.7453); //285.3481,96.9720,1940.9755,1799.0811
	SetPlayerInterior(id,0);
	format(Yazi, sizeof(Yazi), "* {555555}((  {FF0000}.:[CEZA]:. {FFFFFF}Yönetici %s, %s adlý kiþiyi %d dakika hapise attý. Gerekçe: %s {555555}))", pName(playerid), pName(id), dakika, neden);
	SendClientMessageToAll(0xFF0000FF, Yazi);
	return 1;
}
cmd(hapset, playerid, parmas[])
{
return cmd_jail(playerid, parmas);
}

cmd(unjail, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, neden[96],Yazi[128];

	if(sscanf(parmas, "is[90]", id,neden))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /jail [ID/isim] [Gerekçe].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	    
	if(OyuncuVeri[playerid][Hapis] == -1)
		return SendHataMessage(playerid, "Oyuncu hapiste deðil.");

	OyuncuVeri[id][Hapis] = 0;
	SetPlayerWorldBounds(id, 20000.0000,-20000.0000,20000.0000,-20000.0000);
	SetPlayerPosEx(id, 1529.6,-1691.2,13.3);
	SetPlayerVirtualWorld(id, 0);
	SetPlayerInterior(id, 0);
	format(Yazi, sizeof(Yazi), "* {555555}((  {FF9900}.:[Duyuru]:. {FFFFFF}Yönetici %s, %s adlý kiþiyi hapiseten çýkardý. Gerekçe: %s {555555}))", pName(playerid), pName(id), neden);
	SendClientMessageToAll(0xFF0000FF, Yazi);
	return 1;
}

cmd(hapistencikar, playerid, parmas[])
{
return cmd_unjail(playerid, parmas);
}

cmd(eject, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /eject [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	if(!IsPlayerInAnyVehicle(id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Oyuncu Araçta deðil.  {555555}))");

	new Float:pXy,
	    Float:pYy,
	    Float:pZy
	;
	GetPlayerPos(id, pXy, pYy, pZy);
	SetPlayerPos(id, pXy+1.5, pYy+1.5, pZy);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizi araçtan attý.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, araçtan attýnýz.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}

cmd(aractanat, playerid, parmas[])
{
return cmd_eject(playerid, parmas);
}

cmd(resetmoney, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /resetmoney [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	SetPlayerMoneyEx(id, 0);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizin paranýzý bitirdi.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, parasýný bitirdiniz.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}

cmd(parabitir, playerid, parmas[])
{
return cmd_resetmoney(playerid, parmas);
}

cmd(car,playerid,params[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);
		
	new Index;
    new tmp[256];  tmp  = H_strtok(params,Index);
	new tmp2[256]; tmp2 = H_strtok(params,Index);
	new tmp3[256]; tmp3 = H_strtok(params,Index);
    if(!strlen(tmp)) return SendHataMessage(playerid, "Kullaným: /arac [ModelID/isim] [renk1] [renk2]");
	new Arac;
	new colour1, colour2;
	if(!H_isNumeric(tmp))
	Arac = AracinIsminiYazidanBul(tmp);
  	else Arac = strval(tmp);
	if(Arac < 400 || Arac > 611) return SendHataMessage(playerid, "Yanlýþ araç IDsi");
	if(!strlen(tmp2)) colour1 = random(126); else colour1 = strval(tmp2);
	if(!strlen(tmp3)) colour2 = random(126); else colour2 = strval(tmp3);

	if(OyuncuVeri[playerid][pArac] != -1 && !IsPlayerAdmin(playerid))
	AraciSil(OyuncuVeri[playerid][pArac]);
	new HAracID;
	new Float:X,Float:Y,Float:Z;
	new Float:Angle,int1;
	GetPlayerPos(playerid, X,Y,Z);
	GetPlayerFacingAngle(playerid,Angle);
	int1 = GetPlayerInterior(playerid);
	HAracID = CreateVehicle(Arac, X+3,Y,Z, Angle, colour1, colour2, -1);
	LinkVehicleToInterior(HAracID,int1);
	OyuncuVeri[playerid][pArac] = HAracID;
	PutPlayerInVehicle(playerid, HAracID, 0);
	return SendBilgiMessage(playerid, "Aracýnýz yaratýldý");
}

cmd(carhealth, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, acan, Yazi[128];

	if(sscanf(parmas, "ii", id,acan))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /carhealth [ID/isim] [Can].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	SetVehicleHealth(GetPlayerVehicleID(id), acan);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizin aracýnýzýn canýný %d olarak ayarladý.  {555555}))", pName(playerid), acan);
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, aracýnýn canýný %d olarak ayarladýnýz.  {555555}))", pName(id), acan);
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}

cmd(araccan, playerid, parmas[])
{
return cmd_carhealth(playerid, parmas);
}

cmd(carcolour, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id = -1, renk1 = -1, renk2 = -1, Yazi[128];

	sscanf(parmas, "iii", id,renk1,renk2);
	
	if(id == -1)
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /carcolour [ID/isim] [Renk1] [Renk2].  {555555}))");

	if(renk1 == -1)
	renk1 = random(126);

	if(renk2 == -1)
	renk2 = random(126);

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	ChangeVehicleColor(GetPlayerVehicleID(id), renk1, renk2);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizin aracýnýzýn rengini deðiþtirdi.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, aracýnýn rengini degiþtirdiniz.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}

cmd(aracrenk, playerid, parmas[])
{
return cmd_carcolour(playerid, parmas);
}

cmd(destroycar, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id, Yazi[128];
	
	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /destroycar [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	AraciSil(GetPlayerVehicleID(id));
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}Yönetici %s, sizin aracýnýzýn yok etti.  {555555}))", pName(playerid));
	SendClientMessage(id, 0xFFFFFFFF, Yazi);
	format(Yazi, sizeof(Yazi), "* {555555}((  {3A79C5}.:[BÝLGÝ]:. {FFFFFF}%s, aracýnýzý yok etti.  {555555}))", pName(id));
	SendClientMessage(playerid, 0xFFFFFFFF, Yazi);
	return 1;
}

cmd(aracsil, playerid, parmas[])
{
return cmd_destroycar(playerid, parmas);
}

cmd(getcar, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	new id;

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /getcar [ID].  {555555}))");

	new
	    Float:vX,
	    Float:vY,
	    Float:vZ
	;
	GetPlayerPos(playerid, vX, vY, vZ);
	SetVehiclePos(id, vX+1.5, vY+1.5, vZ);
	SendBilgiMessage(playerid, "Aracý çektiniz");
	return 1;
}

cmd(araccek, playerid, parmas[])
{
return cmd_getcar(playerid, parmas);
}

cmd(countdown, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 3)
		return HataVer(playerid, 1);

	if(saniye != 0)
	{
	return SendBilgiMessage(playerid, "Zaten bir geri sayým var");
	}

	new donma, Yazi[128];

	if(sscanf(parmas, "ii", saniye, donma))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /countdown [Saniye] [Donma].  {555555}))");

	format(Yazi, sizeof(Yazi), "Yönetici %s, %d saniyelik geri sayýmý baþlattý", pName(playerid), saniye);
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	SendBilgiMessage(i,  Yazi);
	if(donma == 1)
	TogglePlayerControllableEx(i, 0);
	}
	saniyeT = SetTimer("ZamanDus",1000,1);
	return 1;
}


cmd(gerisayim, playerid, parmas[])
{
return cmd_countdown(playerid, parmas);
}
//============================================[4. Seviye]============================================//
cmd(herkes, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 4)
		return HataVer(playerid, 1);

	new Yazi[128];

	if(sscanf(parmas, "s[64]", Yazi))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /herkes [isim].  {555555}))");
	new
	    Float:pXi,
	    Float:pYi,
		Float:pZi
	;
	
	if(strfind(Yazi, "cek", true) == 0 || strfind(Yazi, "get", true) == 0)
	{
	GetPlayerPos(playerid, pXi, pYi, pZi);
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
	    SetPlayerPos(i, pXi+i/10,pYi+i/10,pZi+i/10);
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesi yanýna çekti.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}
	
	if(strfind(Yazi, "sustur", true) == 0 || strfind(Yazi, "mute", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
	    OyuncuVeri[i][Sus] = 60;
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesi 1 dakikalýðýna susturdu.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}

	if(strfind(Yazi, "konustur", true) == 0 || strfind(Yazi, "unmute", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
	    OyuncuVeri[i][Sus] = 0;
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesin konuþma yasaðýný kaldýrdý.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}
	
	if(strfind(Yazi, "oldur", true) == 0 || strfind(Yazi, "kill", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
	    SetPlayerHealth(i, 0);
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesi öldürdü.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}

	if(strfind(Yazi, "dondur", true) == 0 || strfind(Yazi, "freeze", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
	    TogglePlayerControllableEx(i, 0);
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesi dondurdu.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}
	
	if(strfind(Yazi, "coz", true) == 0 || strfind(Yazi, "unfreeze", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
	    TogglePlayerControllableEx(i, 1);
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesi cözdü.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}
	
	if(strfind(Yazi, "patlat", true) == 0 || strfind(Yazi, "explode", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
	    CreateExplosion(pXi, pYi, pZi, 7, 5.0);
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesi patlattý.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}
	
	if(strfind(Yazi, "at", true) == 0 || strfind(Yazi, "kick", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
		Kick(i);
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesi sunucudan attý.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}
	
	if(strfind(Yazi, "saplak", true) == 0 || strfind(Yazi, "slap", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid)
		GetPlayerPos(i, pXi, pYi, pZi),
		SetPlayerPos(i, pXi, pYi, pZi+ 6);
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkese þaplak attý.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}
	
	if(strfind(Yazi, "aractanat", true) == 0 || strfind(Yazi, "eject", true) == 0)
	{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i != playerid && IsPlayerInAnyVehicle(i))
		GetPlayerPos(i, pXi, pYi, pZi),
		SetPlayerPos(i, pXi+2, pYi+2, pZi);
	}
	format(Yazi, sizeof(Yazi), "Yönetici %s, herkesi araçtan attý.", pName(playerid));
	SendClientMessageToAll(-1, Yazi);
	}
	
	return 1;
}

cmd(all, playerid, parmas[])
{
return cmd_herkes(playerid, parmas);
}

cmd(ban, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 4)
		return HataVer(playerid, 1);

	new id, neden[96], Yazi[128];

	if(sscanf(parmas, "is[90]", id, neden))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /ban [ID/isim] [Neden].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	format(Yazi, sizeof(Yazi), "* {555555}((  {FF0000}.:[CEZA]:. {FFFFFF}Yönetici %s, %s adlý oyuncuyu sunucudan yasakladý. Gerekçe: %s  {555555}))", pName(playerid), pName(id), neden, OyuncuVeri[id][Uyari], MAX_UYARI);
	SendClientMessageToAll(0xFF0000FF, Yazi);
	H_LogEx("%s (%s) sunucudan yasaklandý. Gerekçe:%s.",pName(playerid),pIp(playerid),neden);
	OyuncuVeri[id][Banlandi] = 1;
	BanEx(id, neden);
	return 1;
}

cmd(crash, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 4)
		return HataVer(playerid, 1);

	new id, Yazi[128];

	if(sscanf(parmas, "i", id))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /crash [ID/isim].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	    
	GameTextForPlayer(id, "•¤¶§!$$%&'()*+,-./01~!@#$^&*()_-+={[}]:;'<,>.?/", 1000, 0);
	GameTextForPlayer(id, "•¤¶§!$$%&'()*+,-./01~!@#$^&*()_-+={[}]:;'<,>.?/", 2000, 1);
	GameTextForPlayer(id, "•¤¶§!$$%&'()*+,-./01~!@#$^&*()_-+={[}]:;'<,>.?/", 3000, 2);
	GameTextForPlayer(id, "•¤¶§!$$%&'()*+,-./01~!@#$^&*()_-+={[}]:;'<,>.?/", 4000, 3);
	GameTextForPlayer(id, "•¤¶§!$$%&'()*+,-./01~!@#$^&*()_-+={[}]:;'<,>.?/", 5000, 4);
	GameTextForPlayer(id, "•¤¶§!$$%&'()*+,-./01~!@#$^&*()_-+={[}]:;'<,>.?/", 6000, 5);
	GameTextForPlayer(id, "•¤¶§!$$%&'()*+,-./01~!@#$^&*()_-+={[}]:;'<,>.?/", 7000, 6);
	format(Yazi, sizeof(Yazi), "%s, adlý oyuncuya crash attýnýz.", pName(id));
	SendBilgiMessage(playerid, Yazi);

	return 1;
}

cmd(sunucuyusifrele, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 4)
		return HataVer(playerid, 1);

	new neden[96], Yazi[128];

	sscanf(parmas, "s[90]", neden);

	if(strlen(neden) == 0)
	return SendRconCommand("password 0") && SendBilgiMessage(playerid, "Sunucunun þifresi kaldýrýldý");
	
	format(Yazi, sizeof(Yazi),"password %s", neden);
	SendRconCommand(Yazi);
	SendBilgiMessage(playerid, "Sunucu þifelendi");

	return 1;
}

cmd(setpass, playerid, parmas[])
{
return cmd_sunucuyusifrele(playerid, parmas);
}

cmd(sahteolum, playerid, parmas[])
{
	new id, olduren, silah;

	if(sscanf(parmas, "iii", id, olduren, silah))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /crash [Ölen ID] [Öldüren ID] [Silah ID].  {555555}))");

	if(!IsValidWeapon(silah))
	return SendHataMessage(playerid,"Yanlýþ silah IDsi");
	
	SendDeathMessage(id,olduren,silah);
	SendBilgiMessage(playerid, "Sahte mesaj gönderildi");
	return 1;
}

cmd(fakedeath, playerid, parmas[])
{
return cmd_sahteolum(playerid, parmas);
}

//============================================[5. Seviye]============================================//
cmd(adminyap, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 5)
		return HataVer(playerid, 1);

	new id, seviye, Yazi[128];

	if(sscanf(parmas, "ii", id, seviye))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /adminyap [ID/isim] [seviye].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	OyuncuVeri[id][Admin] = seviye;
	format(Yazi, sizeof(Yazi), "Yönetici %s, %s adlý oyuncuya %d seviye yönetici olarak yönetime aldý.", pName(playerid));
	for(new i; i < MAX_PLAYERS; i++)
	if(IsPlayerConnected(i))
	SendBilgiMessage(playerid, Yazi);

	return 1;
}

cmd(setlevel, playerid, parmas[])
{
return cmd_adminyap(playerid, parmas);
}

cmd(vipyap, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 5)
		return HataVer(playerid, 1);

	new id, seviye, Yazi[128];

	if(sscanf(parmas, "ii", id, seviye))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /vipyap [ID/isim] [seviye].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);

	OyuncuVeri[id][Vip] = seviye;
	format(Yazi, sizeof(Yazi), "Yönetici %s, %s adlý oyuncuya %d seviye vip yaptý.", pName(playerid));
	for(new i; i < MAX_PLAYERS; i++)
	if(IsPlayerConnected(i))
	SendBilgiMessage(playerid, Yazi);

	return 1;
}


cmd(sahteyazi, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 5)
		return HataVer(playerid, 1);

	new id,  Yazi[128];

	if(sscanf(parmas, "is[90]", id, Yazi))
		return SendClientMessage(playerid, 0xFFFFFFFF, "* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Kullaným: /adminyap [ID/isim] [Yazý].  {555555}))");

	if(!IsPlayerConnected(id))
	    return HataVer(playerid, 2);
	SendPlayerMessageToAll(id, Yazi);
	SendBilgiMessage(playerid, "Sahte yazý gönderildi");

	return 1;
}

cmd(fakechat, playerid, parmas[])
{
return cmd_sahteyazi(playerid, parmas);
}

cmd(god, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 5)
		return HataVer(playerid, 1);

	if(OyuncuVeri[playerid][God] == 0)
	{
   	    	OyuncuVeri[playerid][God] = 1;
    	    SetPlayerHealth(playerid,100000);
			GivePlayerWeaponEx(playerid,16,50000);
			GivePlayerWeaponEx(playerid,26,50000);
           	return SendBilgiMessage(playerid, "|- God modu açýldý -|");
			}
			else
			{
   	        OyuncuVeri[playerid][God] = 0;
        	SetPlayerHealth(playerid, 100);
        	return SendBilgiMessage(playerid, "|- God modu kapatýldý -|");
	}
}

cmd(godcar, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 5)
		return HataVer(playerid, 1);

	if(OyuncuVeri[playerid][GodCar] == 0)
	{
   	    	OyuncuVeri[playerid][GodCar] = 1;
           	return SendBilgiMessage(playerid, "|- Araç God modu açýldý -|");
			}
			else
			{
   	        OyuncuVeri[playerid][GodCar] = 0;
        	SetPlayerHealth(playerid, 100);
        	return SendBilgiMessage(playerid, "|- Araç God modu kapatýldý -|");
	}
}

cmd(console, playerid, parmas[])
{
	if(OyuncuVeri[playerid][Admin] < 5)
		return HataVer(playerid, 1);

	return ShowPlayerDialog(playerid, DIALOG_CONSOLE, DIALOG_STYLE_LIST, "Hadmin Konsol","Filterscript yükle\nFilterscript kapat\nModu Deðiþtir\nRestart (Gmx)\nIPnin yasaklamasýný aç\nYasaklamalarý Yeniden Yükle\nKomut Gönder", "Seç", "Ýptal");

}

//--------------------------------------------[Komutlar Bitiþ]--------------------------------------------//
public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
if(OyuncuVeri[playerid][Hapis] > 0)
{
return SendBilgiMessage(playerid, "Hapiste bulunduðun süre zarfýnda komut kullanamazsýnýz.");
}
#if ZORUNLU_GIRIS == true
switch(GetPVarInt(playerid, "Gyapti"))
{
case 0: return SendClientMessage(playerid, Kirmizi, "{FFFFFF}* {555555}((  {FF0000}.:[HATA]:.  {FFFFFF}Ýlk Baþta Sunucuya Giriþ Yapmalýsýnýz.  {555555}))");
}
#endif
#if defined HATALI_KOMUT
if(!success)return SendClientMessage(playerid, 0xFFFFFFFF, HATALI_KOMUT);
#endif
return 1;
}

public AraciSil(vehicleid)
{
    for(new i=0;i<MAX_PLAYERS;i++)
	{
		if(IsPlayerConnected(i))
		{
	        new Float:X,Float:Y,Float:Z;
	    	if(IsPlayerInVehicle(i, vehicleid))
			{
	  		RemovePlayerFromVehicle(i);
	  		GetPlayerPos(i,X,Y,Z);
	 		SetPlayerPosEx(i,X,Y+3,Z);
		    }
		    SetVehicleParamsForPlayer(vehicleid,i,0,1);
	    }
	}
    SetTimerEx("SilmeyiTamamla",1500,0,"i",vehicleid);
}

public SilmeyiTamamla(vehicleid)
{
    DestroyVehicle(vehicleid);
}
public AracSpawnla(playerid, model)
{
	switch(IsPlayerInAnyVehicle(playerid))
	{
		case 1:SendHataMessage(playerid, "Zaten aracýnýz var!");
		default:
		{
		    new Float:x, Float:y, Float:z, Float:angle;
			GetPlayerPos(playerid, x, y, z);
		 	GetPlayerFacingAngle(playerid, angle);

			if(OyuncuVeri[playerid][pArac] != -1)
			AraciSil(OyuncuVeri[playerid][pArac]);
		    new vehicleid=CreateVehicle(model, x, y, z, angle, -1, -1, -1);
			PutPlayerInVehicle(playerid, vehicleid, 0);
			SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
			LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));
			ChangeVehicleColor(vehicleid,0,3);
	        OyuncuVeri[playerid][pArac] = vehicleid;
		}
	}
	return 1;
}

stock ModifiyeSes(playerid)
{
PlayerPlaySound(playerid,1133,0.0,0.0,0.0);
return 1;
}

stock AraclaGonder(playerid, Float:X,Float:Y,Float:Z)
{
	switch
	    (IsPlayerInAnyVehicle(playerid))
	{
	case 0: SetPlayerPosEx(playerid, Float:X,Float:Y,Float:Z);
	case 1: SetVehiclePos(GetPlayerVehicleID(playerid), Float:X,Float:Y,Float:Z);
	}
	return 1;
}

forward OnPlayerCheat(playerid, cheatid);
public OnPlayerCheat(playerid, cheatid)
{

	if(HoPC)
		return CallLocalFunction("H_OnPlayerCheat","ii",playerid, cheatid);
	else
		return 1;

}

forward OyuncuVipSeviye(playerid);
public OyuncuVipSeviye(playerid)
{
return GetPlayerVipLevel(playerid);
}

forward GetPlayerVipLevel(playerid);
public GetPlayerVipLevel(playerid)
{
return OyuncuVeri[playerid][Vip];
}

forward OyuncuAdminSeviye(playerid);
public OyuncuAdminSeviye(playerid)
{
return GetPlayerAdminLevel(playerid);
}

forward GetPlayerAdminLevel(playerid);
public GetPlayerAdminLevel(playerid)
{
return OyuncuVeri[playerid][Admin];
}

forward GivePlayerMoneyEx(playerid, pMiktar);
public GivePlayerMoneyEx(playerid, pMiktar)
{
    #if ANTI_PARA == 1
	OyuncuVeri[playerid][Para] = OyuncuVeri[playerid][Para] + pMiktar;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, OyuncuVeri[playerid][Para]);
	return OyuncuVeri[playerid][Para];
	#else
	GivePlayerMoney(playerid, pMiktar);
	return GetPlayerMoney(playerid);
	#endif
}

forward SetPlayerMoneyEx(playerid, pMiktar);
public SetPlayerMoneyEx(playerid, pMiktar)
{
   #if ANTI_PARA == 1
      OyuncuVeri[playerid][Para] = pMiktar;
      ResetPlayerMoney(playerid);
      GivePlayerMoney(playerid, OyuncuVeri[playerid][Para]);
      return OyuncuVeri[playerid][Para];
   #else
      ResetPlayerMoney(playerid);
      GivePlayerMoney(playerid, pMiktar);
      return GetPlayerMoney(playerid);
   #endif
}

forward ResetPlayerMoneyEx(playerid);
public ResetPlayerMoneyEx(playerid)
{
    #if ANTI_PARA == 1
	OyuncuVeri[playerid][Para] = 0;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, OyuncuVeri[playerid][Para]);
	return OyuncuVeri[playerid][Para];
	#else
	ResetPlayerMoney(playerid);
	return GetPlayerMoney(playerid);
	#endif
}

forward GetPlayerMoneyEx(playerid);
public GetPlayerMoneyEx(playerid)
{
    #if ANTI_PARA == 1
	return OyuncuVeri[playerid][Para];
	#else
	return GetPlayerMoney(playerid);
	#endif
}

forward SetPlayerScoreEx(playerid, sMiktar);
public SetPlayerScoreEx(playerid, sMiktar)
{
    #if SKOR_KAYIT == true
	OyuncuVeri[playerid][Skor] = sMiktar;
	#endif
	SetPlayerScore(playerid, sMiktar);
}

forward GetPlayerScoreEx(playerid);
public GetPlayerScoreEx(playerid)
{
    #if SKOR_KAYIT == true
	return OyuncuVeri[playerid][Skor];
	#else
	return GetPlayerScore(playerid);
	#endif
}

forward SetPlayerSkinEx(playerid, sID);
public SetPlayerSkinEx(playerid, sID)
{
    #if SKIN_KAYIT == true
	OyuncuVeri[playerid][Skin] = sID;
	#endif
	SetPlayerSkin(playerid, sID);
}

forward GetPlayerSkinEx(playerid);
public GetPlayerSkinEx(playerid)
{
    #if SKIN_KAYIT == true
    switch (OyuncuVeri[playerid][Skin])
	{
		case 0: return GetPlayerSkin(playerid);
		default: return OyuncuVeri[playerid][Skin];
	}
	#else
	return GetPlayerSkin(playerid);
	#endif
	return 0;
}

forward SetPlayerWantedLevelEx(playerid, wL);
public SetPlayerWantedLevelEx(playerid, wL)
{
    #if ASEVIYE_KAYIT == true
	OyuncuVeri[playerid][aSeviye] = wL;
	#endif
	SetPlayerWantedLevel(playerid, wL);
}

forward GetPlayerWantedLevelEx(playerid);
public GetPlayerWantedLevelEx(playerid)
{
    #if ASEVIYE_KAYIT == true
	return OyuncuVeri[playerid][aSeviye];
	#else
	return GetPlayerWantedLevel(playerid);
	#endif
}

forward SetPlayerSpecialActionEx(playerid, SAid);
public SetPlayerSpecialActionEx(playerid, SAid)
{
    #if ANTI_JETPACK == 1
	if(SAid == 2)
	OyuncuVeri[playerid][JetPack] = 1;
	#endif
	SetPlayerSpecialAction(playerid, SAid);
}

forward GivePlayerWeaponEx(playerid,weaponid,ammo);
public GivePlayerWeaponEx(playerid,weaponid,ammo)
{
    OyuncuSilahlari[playerid][weaponid]=true; // Player Has the weapon.
    return GivePlayerWeapon(playerid,weaponid,ammo); // To realy give him the weapon.
}

stock GetWeaponModel(weaponid) // credits Double-O-Seven
{
	switch(weaponid)
	{
	    case 1:
	        return 331;

		case 2..8:
		    return weaponid+331;

        case 9:
		    return 341;

		case 10..15:
			return weaponid+311;

		case 16..18:
		    return weaponid+326;

		case 22..29:
		    return weaponid+324;

		case 30,31:
		    return weaponid+325;

		case 32:
		    return 372;

		case 33..45:
		    return weaponid+324;

		case 46:
		    return 371;
	}
	return 0;
}

forward AddStaticPickupEx(model,type,Float:X,Float:Y,Float:Z,virtualworld);
public AddStaticPickupEx(model,type,Float:X,Float:Y,Float:Z,virtualworld)
{
	new id = CreatePickup(model,type,X,Y,Z,virtualworld);
	if(type==2 || type==3 || type==15 || type==22)
	{
		for(new i;i<47;i++)
		{
			if(GetWeaponModel(i)==model)
			{
				WeaponPickup[id]=i;
			}
		}
	}
	return id;
}

forward CreatePickupEx(model,type,Float:X,Float:Y,Float:Z,virtualworld);
public CreatePickupEx(model,type,Float:X,Float:Y,Float:Z,virtualworld)
{
	new id = CreatePickup(model,type,X,Y,Z,virtualworld);
	if(type==2 || type==3 || type==15 || type==22)
	{
		for(new i;i<47;i++)
		{
			if(GetWeaponModel(i)==model)
			{
				WeaponPickup[id]=i;
			}
		}
	}
	return id;
}

forward H_AddPlayerClass(modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);
public H_AddPlayerClass(modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo)
{
	new class = AddPlayerClass(modelid,spawn_x,spawn_y,spawn_z,z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);
	if(class<MAX_CLASS)
	{
		if(weapon1 != -1) ClassSilahlari[class][0]=weapon1;
		if(weapon2 != -1) ClassSilahlari[class][1]=weapon2;
		if(weapon3 != -1) ClassSilahlari[class][2]=weapon3;
	}
	else printf("H-Admindeki MAX_CLASS'i degistirin su anki: %i",class);
	return class;
}

forward H_AddPlayerClassEx(teamid,modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);
public H_AddPlayerClassEx(teamid,modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo)
{
	new class = AddPlayerClassEx(teamid,modelid,spawn_x,spawn_y,spawn_z,z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);
	if(class<MAX_CLASS)
	{
		if(weapon1 != -1) ClassSilahlari[class][0]=weapon1;
		if(weapon2 != -1) ClassSilahlari[class][1]=weapon2;
		if(weapon3 != -1) ClassSilahlari[class][2]=weapon3;
	}
	else printf("H-Admindeki MAX_CLASS'i degistirin su anki: %i",class);
	return class;
}

forward SetSpawnInfoEx(playerid,team,skin,Float:x,Float:y,Float:z,rotation,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);
public SetSpawnInfoEx(playerid,team,skin,Float:x,Float:y,Float:z,rotation,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo)
{
	if(weapon1 != -1) OyuncuSilahlari[playerid][weapon1]=true;
	if(weapon2 != -1) OyuncuSilahlari[playerid][weapon2]=true;
	if(weapon3 != -1) OyuncuSilahlari[playerid][weapon3]=true;
	return SetSpawnInfo(playerid,team,skin,x,y,z,rotation,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);
}

forward SetPlayerPosEx(playerid, Float:iX, Float:iY, Float:iZ);
public SetPlayerPosEx(playerid, Float:iX, Float:iY, Float:iZ)
{
Isinlandi[playerid] = 1;
return SetPlayerPos(playerid, iX, iY, iZ);
}

forward SetVehicleVelocityEx(vehicleid, Float:vX, Float:vY, Float:vZ);
public SetVehicleVelocityEx(vehicleid, Float:vX, Float:vY, Float:vZ)
{
for(new Surucu = 0; Surucu != MAX_PLAYERS; Surucu++)
{
	if(IsPlayerConnected(Surucu))
	{
		if(GetPlayerVehicleID(Surucu) == vehicleid)
		{
		    if(GetPlayerState(Surucu) == PLAYER_STATE_DRIVER)
		    {
		        if(OyuncuVeri[Surucu][Hiz] > 0)
		        {
		    	OyuncuVeri[Surucu][Hiz] *= -1;
				}
				if(OyuncuVeri[Surucu][AirBrake] > 0)
				{
		    	OyuncuVeri[Surucu][AirBrake] *= -1;
		    	}
		    }
	    }
	}
}
return SetVehicleVelocity(vehicleid, vX, vY, vZ);
}

forward SetPlayerVelocityEx(playerid, Float:vX, Float:vY, Float:vZ);
public SetPlayerVelocityEx(playerid, Float:vX, Float:vY, Float:vZ)
{
	if(OyuncuVeri[playerid][AirBrake] > 0)
	{
	OyuncuVeri[playerid][AirBrake] *= -1;
	}
	return SetPlayerVelocity(playerid, vX, vY, vZ);
}

forward TogglePlayerControllableEx(playerid, durum);
public TogglePlayerControllableEx(playerid, durum)
{
	OyuncuVeri[playerid][Donmama] = durum;
    TogglePlayerControllable(playerid, durum);
    return 1;
}

forward Ban_(playerid);
public Ban_(playerid)
{
    return H_Ban(playerid, "Belirtilmemiþ");
}

forward BanEx_(playerid, neden[]);
public BanEx_(playerid, neden[])
{
    return H_Ban(playerid, neden);
}
#define GetPlayerMoney GetPlayerMoneyEx
#define ResetPlayerMoney ResetPlayerMoneyEx
#define GivePlayerMoney GivePlayerMoneyEx
#define SetPlayerMoney SetPlayerMoneyEx
#define SetPlayerScore SetPlayerScoreEx
#define GetPlayerScore GetPlayerScoreEx
#define SetPlayerSkin SetPlayerSkinEx
#define GetPlayerSkin GetPlayerSkinEx
#define SetPlayerWantedLevel SetPlayerWantedLevelEx
#define GetPlayerWantedLevel GetPlayerWantedLevelEx
#define SetPlayerSpecialAction SetPlayerSpecialActionEx
#define GivePlayerWeapon GivePlayerWeaponEx
#define AddStaticPickup AddStaticPickupEx
#define CreatePickup CreatePickupEx
#define AddPlayerClass H_AddPlayerClass
#define AddPlayerClassEx H_AddPlayerClassEx
#define SetSpawnInfo H_SetSpawnInfo
#define SetPlayerPos SetPlayerPosEx
#define SetVehicleVelocity SetVehicleVelocityEx
#define SetPlayerVelocity SetPlayerVelocityEx
#define TogglePlayerControllable TogglePlayerControllableEx
#define BanEx BanEx_
#define Ban Ban_
//OnGameModeInit
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit H_OnGameModeInit

//OnPlayerUpdate
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate H_OnPlayerUpdate

//OnPlayerText
#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText H_OnPlayerText

//OnPlayerConnect
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect H_OnPlayerConnect

//OnPlayerCheat
#if defined _ALS_OnPlayerCheat
	#undef OnPlayerCheat
#else
	#define _ALS_OnPlayerCheat
#endif
#define OnPlayerCheat H_OnPlayerCheat

forward OnPlayerCheat(playerid, cheatid);

//OnPlayerConnect
#if defined _ALS_OnPlayerInteriorChange
	#undef OnPlayerInteriorChange
#else
	#define _ALS_OnPlayerInteriorChange
#endif
#define OnPlayerInteriorChange H_OnPlayerInteriorChange

//OnPlayerDisconnect
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect H_OnPlayerDisconnect

//OnPlayerPickUpPickup
#if defined _ALS_OnPlayerPickUpPickup
    #undef OnPlayerPickUpPickup
#else
    #define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup H_OnPlayerPickUpPickup

//OnPlayerSpawn
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn H_OnPlayerSpawn

//OnPlayerDeath
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath H_OnPlayerDeath


//OnPlayerStateChange
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange H_OnPlayerStateChange

//OnPlayerKeyStateChange
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange H_OnPlayerKeyStateChange

//OnDialogResponse
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse H_OnDialogResponse
