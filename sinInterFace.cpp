#include "..\globals.h"

/*----------------------------------------------------------------------------*
*	ÆÄÀÏ¸í :  sinInterFace.cpp	
*	ÇÏ´ÂÀÏ :  ÀÎÅÍÆäÀÌ½º¿¡ °üÇÑ ¸ðµç°É °ü¸®ÇÑ´Ù 
*	ÀÛ¼ºÀÏ :  ÃÖÁ¾¾÷µ¥ÀÌÆ® 12¿ù
*	Àû¼ºÀÚ :  ¹Ú»ó¿­ 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "..\\tjboy\\clanmenu\\tjclan.h"
#include "..\\field.h"
/*----------------------------------------------------------------------------*
*								Àü¿ªº¯¼ö 			
*-----------------------------------------------------------------------------*/	
cINTERFACE	cInterFace;
sSHADOWSTATE sShadowState[3];

int sinBmpLength[5] = {0,0,0,0,0}; //¶óÀÌÇÁ ¸¶³ª ½ºÅ×¹Ì³ª °æÇèÄ¡ 

////////////////Ã¤ÆÃ°ü·Ã Flag
int sinChatEnter = 0;         //Ã¤ÆÃ ÇÃ·¢ (¿£ÅÍÅ°¸¦ ÀÔ·ÂÇÏ¸é Ã¤ÆÃ Ã¢ÀÌ ³ª¿Â´Ù )
int SubChatHeight = 0;	      //Ã¤ÆÃÃ¢ º¯°æ À§Ä¡ ÁÂÇ¥ °ª 	
int sinChatDisplayMode = 0;   //ÇöÀç Ã¤ÆÃÀÇ ¸ðµå 
int sinChatInputMode = 0;     //Ã¤ÆÃ ÀÔ·Â ¸ðµå 
////////////////

/////////////Test Key Msg
int TestKeyAniFlag = 0;

extern BOOL bDone;
extern int iSave;

extern int GetClick( DWORD x, DWORD y, DWORD L, DWORD A );
extern void SaveConfig();

////////////////¹öÆ°°ü·Ã Flag
int ExitButtonClick = 0;
int HelpButtonClick = 0;
int MouseButtonPosi=0;
int sinMenuBottonPosi = 0;
int sinRunCameraMapPosi = 0; //°È±â Ä«¸Þ¶ó ¸Ê 
int SunandMoonFlag[2] = {0,0}; //0 ÇØ 1 ´Þ 
int InterButtonDown = 0;  //ÀÎÅÍÆäÀÌ½º ¹öÆ° ´Ù¿î ÇÃ·¢ 
int sinFireShow = 1;      //ºÒÀ» º¸¿©ÁØ´Ù 



////////////////½ºÅ³ °ÔÀÌÁö (ÇöÀç´Â »ç¿ëµÇ°í ÀÖÁö ¾Ê´Ù )
int ReSizelpGage = 0;     //°ÔÀÌÁö ±×¸²À» Á¶Á¤ÇÑ´Ù 


////////////////
int InitStateFlag = 0;    //ÃÊ±âÈ­ ÇÃ·¢ 


//////////////// ¹é¾÷ Æ÷ÀÎÅÍ 
char szInfoMsgBuff5[512];  //»ý¸í·Â ±â·Â ±Ù·Â °æÇèÄ¡ ÀÇ ¼öÄ¡ ±â·Ï ¹öÆÛ 
char szInfoMsgBuff6[128];  //»ý¸í·Â ±â·Â ±Ù·Â °æÇèÄ¡ ÀÇ ¼öÄ¡ ±â·Ï ¹öÆÛ 
POINT InfoMessageBoxPos;  //ÅØ½º¸¦ Ç¥½ÃÇÒ ÁÂÇ¥ 


//////////////// Àü»ç (´Ù½Ã½ÃÀÛ )
int ReStartFlag = 0;  //°ªÀÌ µé¾î¿À¸é ´Ù½Ã½ÃÀÛ ÀÎÅÍÆäÀÌ½º¸¦ º¸¿©ÁØ´Ù 
POINT ReStartMainXY = {0,0}; //´Ù½Ã½ÃÀÛ ÁÂÇ¥ 
int ReStartIndex = 0;
POINT ReStartTextXY = {0,0};
char szReStartMsg[128];
char szReStartMsg2[128];

int RestartCheckExp = 0;
int ReStartOptionIndex = 0;
int ShowExpPercentFlag = 0;

//////////////// ½ºÅ³ Àü¾÷ Á¾·á  (´Ù½Ã½ÃÀÛ )

int SkillNpcFlag = 0;  //°ªÀÌ µé¾î¿À¸é ´Ù½Ã½ÃÀÛ ÀÎÅÍÆäÀÌ½º¸¦ º¸¿©ÁØ´Ù 
POINT SkillMasterMainXY = {0,0}; //´Ù½Ã½ÃÀÛ ÁÂÇ¥ 
int SkillMasterIndex = 0;
POINT SkillMasterTextXY = {0,0};
char szSkillMasterMsg[128];
char szSkillMasterMsg2[128];
int SkillMasterOptionIndex = 0;

////////½ºÅ³ »ç¿ë ºÒÃæÁ· ÀÌÆåÆ® 
int NotUseSkillEffect[3] = {0,0,0};

int SkillMouseButtonPosi[2] = {0,0};

/////////// ³· ¹ã
int DayOrNightFlag = 0;
int sinGageTime2 = 0;


int ReStartButtonRect[3][4] = {
	{21,22,21+44,22+44},			//ÇÊµå¿¡¼­ ½ÃÀÛ 
	{72,22,72+44,22+44},			//¸¶À»¿¡¼­ ½ÃÀÛ 
	{123,22,123+44,22+44},			//°ÔÀÓ Á¾·á 
	
};

int ButtonRect[6][5]= {   //¹Ú½º ¿ÀÇÂ ¹öÆ° 
	{648,560,648+25,560+27},
	{673,560,673+25,560+27},
	{698,560,698+25,560+27},
	{723,560,723+25,560+27},
	{748,560,748+25,560+27},
	{772,560,772+25,560+27},

};
/*
int ButtonRect[6][5]= {   //¹Ú½º ¿ÀÇÂ ¹öÆ° 
	{655,566,678,598},
	{678,566,701,598},
	{701,566,724,598},
	{724,566,747,598},
	{747,566,770,598},
	{770,566,792,598},

};
*/
int sinMenuRect[3][4] = {  //°ÔÀÓ Á¾·á ....
	{692,492,784,511},
	{692,517,784,536},
	{692,542,784,561}, //Á¾·á 


};

int sinRunCameraMap[3][4] = { //°È±â , Ä«¸Þ¶ó , ¸Ê 
	{569,555,569+26,555+26},
	{569+26,555,569+26+26,555+26},
	{569+26+26,555,569+26+26+26,555+26},

};


// Àü¾÷ °ü·Ã 
int ChangeJobButtonclick = 0;


//PK°ü·Ã
int sinPKWarningExpFlag = 0;
int sinPKWarnigExpTime = 0;
LPDIRECT3DTEXTURE9 lpGrowInterLeft;
LPDIRECT3DTEXTURE9 lpGrowInterMiddle;
LPDIRECT3DTEXTURE9 lpGrowInterRight;


//±ÛÀÚ ÀÌÆåÆ®°ü·Ã ===================================================================
struct HAEFFECT{
	int   Flag;
	int   Time;
	POINT Posi;
	POINT Size;
	int   Mat;
	int   Alpha;
};
char *HaEffectFilePath[] = {
	0,
	"Image\\SinImage\\Inter\\defense.tga", //1
	"Image\\SinImage\\Inter\\block.tga",   //2
	"Image\\SinImage\\Inter\\Evade.tga",   //3
	0,
};
#define  MAX_HAEFFECTNUM 10 //ÃÑ°¹¼ö

int HA_EffectIndex[4]={0,}; //

HAEFFECT HaEffect[MAX_HAEFFECTNUM];
//=====================================================================================

/*----------------------------------------------------------------------------*
*							Å¬·¡½º ÃÊ±â, Á¾·á 
*-----------------------------------------------------------------------------*/	
cINTERFACE::cINTERFACE()
{
	memset(&HaEffect,0,sizeof(HAEFFECT)); //±ÛÀÚÀÌÆåÆ®  ÃÊ±âÈ­ 
}
cINTERFACE::~cINTERFACE()
{


}

extern void Relog();
extern int iWidth, iHeight;

int Tooltip;
/*----------------------------------------------------------------------------*
*							     ÃÊ±âÈ­ 
*-----------------------------------------------------------------------------*/	
void cINTERFACE::Init()
{

	//ReStart¸ÞÀÎ ÀÇ ÁÂÇ¥¸¦ ±¸ÇÑ´Ù 
	ReStartMainXY.x = (WinSizeX/2) - (187/2);
	ReStartMainXY.y = (WinSizeY/2) - (127/2)-100;

	ReStartTextXY.x = ReStartMainXY.x+23;
	ReStartTextXY.y = ReStartMainXY.y+73;

	SkillMasterMainXY.x = (WinSizeX/2) - (187/2)-30;
	SkillMasterMainXY.y = (WinSizeY/2) - (127/2)-100;

	SkillMasterTextXY.x = SkillMasterMainXY.x+23;
	SkillMasterTextXY.y = SkillMasterMainXY.y+73;



	InitState(); //»ý¸í·Â , ±â·Â , ±Ù·ÂÀ» ÃÊ±âÈ­ÇÑ´Ù 

	//MatMain = CreateTextureMaterial( "Image\\SinImage\\Inter\\Inter.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	MatMenu[0] = CreateTextureMaterial( "Image\\SinImage\\Inter\\Menu-1.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	MatMenu[1] = CreateTextureMaterial( "Image\\SinImage\\Inter\\Menu-2.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	MatChatDefault[0] = CreateTextureMaterial( "Image\\SinImage\\Inter\\Chat\\ChatDefault-1.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );//Ã¤ÆÃ±âº» 
	MatChatDefault[1] = CreateTextureMaterial( "Image\\SinImage\\Inter\\Chat\\ChatDefault-2.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );//Ã¤ÆÃ±âº» 
	
	MatChatSmall[0] = CreateTextureMaterial( "Image\\SinImage\\Inter\\Chat\\ChatSmall-1.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );  //»õ³¢ Ã¤ÆÃÃ¢
	MatChatSmall[1] = CreateTextureMaterial( "Image\\SinImage\\Inter\\Chat\\ChatSmall-2.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );  //»õ³¢ Ã¤ÆÃÃ¢				

	MatChatDoc[0] =	CreateTextureMaterial( "Image\\SinImage\\Inter\\Chat\\ChatDoc-1.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );  //³»¿ë Ã¢ 
	MatChatDoc[1] = CreateTextureMaterial( "Image\\SinImage\\Inter\\Chat\\ChatDoc-2.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );  //³»¿ë Ã¢ 

	
	MatExitMenu = CreateTextureMaterial( "Image\\SinImage\\Inter\\ExitMenu.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );  //³»¿ë Ã¢ 


	MatClock        = CreateTextureMaterial("Image\\SinImage\\Inter\\Clock.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA); //½Ã°è 
	MatComPass      = CreateTextureMaterial("Image\\SinImage\\Inter\\Compass.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA); //³ªÄ§¹Ý 

	MatLife			= CreateTextureMaterial("Image\\SinImage\\Inter\\ShadowLife.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA); //½Ã°è 
	MatMana			= CreateTextureMaterial("Image\\SinImage\\Inter\\ShadowMana.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA); //½Ã°è 
	MatStamina		= CreateTextureMaterial("Image\\SinImage\\Inter\\ShadowStamina.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA); //½Ã°è 

	Tooltip = CreateTextureMaterial("game\\meshes\\tooltip\\daynight_tooltip.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Load();

	
}
/*----------------------------------------------------------------------------*
*						    BmpÆÄÀÏÀ» ·ÎµåÇÑ´Ù 
*-----------------------------------------------------------------------------*/	

void cINTERFACE::Load()
{
	lpLIFE   =  LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Bar_Life.bmp" );
	lpMP     =  LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Bar_Mana.bmp" );
	lpSTM    =  LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Bar_Stamina.bmp" );

	lpButton[0] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bStatus.bmp" ); //¹«ºê ÀÌ¹ÌÁö 
	lpButton[1] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bInvenTory.bmp" );
	lpButton[2] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bSkill.bmp" );
	lpButton[3] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bParty.bmp" );
	lpButton[4] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bQuest.bmp" );
	lpButton[5] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bSystem.bmp" );

	lpButton2[0] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bStatus-1.bmp" ); //Å¬¸¯ ÀÌ¹ÌÁö 
	lpButton2[1] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bInvenTory-1.bmp" );
	lpButton2[2] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bSkill-1.bmp" );
	lpButton2[3] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bParty-1.bmp" );
	lpButton2[4] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bQuest-1.bmp" );
	lpButton2[5] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\bSystem-1.bmp" );

	lpInfoBox[0] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\StatusInfo.bmp" ); //Ç³¼± µµ¿ò¸»
	lpInfoBox[1] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\InvenInfo.bmp" ); //Ç³¼± µµ¿ò¸»
	lpInfoBox[2] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\SkillInfo.bmp" ); //Ç³¼± µµ¿ò¸»
	lpInfoBox[3] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\PartyInfo.bmp" ); //Ç³¼± µµ¿ò¸»
	lpInfoBox[4] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\QuestInfo.bmp" ); //Ç³¼± µµ¿ò¸»
	lpInfoBox[5] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\SystemInfo.bmp" ); //Ç³¼± µµ¿ò¸»


	lpMenuButton[0] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Option.bmp" ); //¿É¼Ç 
	lpMenuButton[1] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Settings.bmp" ); //´Ù½Ã½ÃÀÛ 
	lpMenuButton[2] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Exit.bmp" ); //³ª°¡±â


	lpWalk = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Button\\Walk.bmp" ); //°È±â 

	lpChatShowButton = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Chat\\ChatDownButton.bmp" ); //Ã¤ÆÃ¹öÆ°  
	

	lpSun  = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Flash\\Sun.bmp" ); //ÇØ 
	lpMoon = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Flash\\Moon.bmp" ); //´Þ 

	lpGage[0] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Skill\\P-skill.bmp" );  //¿ÞÂÊ  ½ºÅ³°ÔÀÌÁö
	lpGage[1] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Skill\\P-skill2.bmp" );  //¿À¸¥ÂÊ ½ºÅ³°ÔÀÌÁö

	lpBar_Anger		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\sinGage\\Bar_Anger.bmp" );  //°ÔÀÌÁö ÀüÃ¼  
	lpBar_Time		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\sinGage\\Bar_Time.bmp" );  //°ÔÀÌÁö ÀüÃ¼  
	lpBar_Exp = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\sinGage\\Bar_Exp.bmp" );  //°ÔÀÌÁö ÀüÃ¼  
	lpButton_Anger	= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\sinGage\\Button_Anger.bmp" );  //°ÔÀÌÁö ÀüÃ¼   
	
	lpRunInfo		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\Run.bmp");  //¶Ù±âÇ³¼± µµ¿ò¸» 
	lpWalkInfo      = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\Walk.bmp"); //°È±âÇ³¼± µµ¿ò¸» 
	
	lpCameraHandInfo= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\Camera_Hand.bmp");   //¼öµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 
	lpCameraFixInfo = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\Camera_Fix.bmp");   //¼öµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 
	lpCameraAutoInfo= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\Camera_Auto.bmp");   //ÀÚµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 
	
	lpMapOnInfo		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\MapOn.bmp");   //ÀÚµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 
	lpMapOffInfo	= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ButtonInfo\\MapOff.bmp");   //¼öµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 

	lpMapOnImage		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Button\\MapOnImage.bmp");  //¸ÊÇ¥½Ã ¿Â ÀÌ¹ÌÁö 
	lpCameraImage[0]	= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Button\\AutoCameraImage.bmp"); //Ä«¸Þ¶ó AutoÀÌ¹ÌÁö 
	lpCameraImage[1]	= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Button\\PixCameraImage.bmp"); //Ä«¸Þ¶ó °íÁ¤ ÀÌ¹ÌÁö

    lpLIFESpot		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Bar_LifeSpot.bmp");        //¶óÀÌÇÁ 
    lpSTMSpot		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Bar_StaminaSpot.bmp");        //½ºÅ×¹Ì³ª 
    lpMANASpot		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\Bar_ManaSpot.bmp");        //ºÐ³ë°ÔÀÌÁö 

	lpReStartMain		= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ReStart\\ReStartMain.bmp"); //´Ù½Ã½ÃÀÛ ¸ÞÀÎ 
	lpReStartButton[0]	= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ReStart\\ReStart_Field.bmp"); //´Ù½Ã½ÃÀÛ ¹öÆ° 
	lpReStartButton[1]	= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ReStart\\ReStart_Town.bmp"); //´Ù½Ã½ÃÀÛ ¹öÆ° 
	lpReStartButton[2]	= LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\ReStart\\ReStart_Exit.bmp"); //´Ù½Ã½ÃÀÛ ¹öÆ° 


	lpSelectSkill_Main[0]     = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\SkillIcon\\G_Select_Skill.bmp"); //½ºÅ³ ¹è¿ì±â 0 ±×·¹ÀÌ 1 È°¼º 
	lpSelectSkill_Main[1]     = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\SkillIcon\\Select_Skill.bmp"); //½ºÅ³ ¹è¿ì±â 0 ±×·¹ÀÌ 1 È°¼º 
	
	lpSelectChangeJob[0] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\SkillIcon\\G_Select_ChangeJob.bmp"); //Àü¾÷        0 ±×·¹ÀÌ 2 È°¼º 
	lpSelectChangeJob[1] = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\SkillIcon\\Select_ChangeJob.bmp"); //Àü¾÷        0 ±×·¹ÀÌ 2 È°¼º 

	lpTime7 = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\SkillIcon\\Select_ChangeJob.bmp"); //½Ã°£ °ÔÀÌÁö

	lpGrowInterLeft = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\inter_01.bmp"); //È®Àå ÀÎÅÍÆäÀÌ½º
	lpGrowInterMiddle = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\inter_02.bmp"); 
	lpGrowInterRight = LoadDibSurfaceOffscreen( "Image\\SinImage\\Inter\\inter_03.bmp"); 



}

extern BOOL bSettings;

/*----------------------------------------------------------------------------*
*						     Release
*-----------------------------------------------------------------------------*/	
void cINTERFACE::Release()
{
	int i;

	if(lpLIFE){
		lpLIFE->Release();
		lpLIFE = 0;

	}
	if(lpMP){
		lpMP->Release();
		lpMP = 0;
	}
	if(lpSTM){
		lpSTM->Release();
		lpSTM = 0;
	}

	for(i = 0 ; i < 6 ; i++){
		if(lpButton[i]){
			lpButton[i]->Release();
			lpButton[i] = 0;

		}
		if(lpButton2[i]){
			lpButton2[i]->Release();
			lpButton2[i] = 0;
		}
		if(lpInfoBox[i]){
			lpInfoBox[i]->Release();
			lpInfoBox[i] = 0;
		}
	}
	for(i=0 ; i < 3 ; i++){
		if(lpMenuButton[i]){
			lpMenuButton[i]->Release();
			lpMenuButton[i] = 0;
		}
	}

	if(lpWalk){
		lpWalk->Release();
		lpWalk = 0;	
	}
	if(lpChatShowButton){
		lpChatShowButton->Release();
		lpChatShowButton = 0;
	}	
	if(lpSun){
		lpSun->Release();
		lpSun = 0;

	}
	if(lpMoon){
		lpMoon->Release();
		lpMoon = 0;
	}
	if(lpGage[0]){
		lpGage[0]->Release();
		lpGage[0] = 0;
	}
	if(lpBar_Anger){
		lpBar_Anger->Release();
		lpBar_Anger = 0;
	}
	if(lpBar_Time){
		lpBar_Time->Release();
		lpBar_Time = 0;
	}
	if(lpBar_Exp){
		lpBar_Exp->Release();
		lpBar_Exp = 0;
	}
	if(lpButton_Anger){
		lpButton_Anger->Release();
		lpButton_Anger = 0;
	}

	if(lpRunInfo){
		lpRunInfo->Release();
		lpRunInfo = 0;
	}
	if(lpWalkInfo){
		lpWalkInfo->Release();
		lpWalkInfo = 0;
	}
	
	if(lpCameraAutoInfo){
		lpCameraAutoInfo->Release();
		lpCameraAutoInfo  = 0;
	}
	if(lpCameraHandInfo){
		lpCameraHandInfo->Release();
		lpCameraHandInfo = 0;
	}
	if(lpCameraFixInfo){
		lpCameraFixInfo->Release();
		lpCameraFixInfo = 0;
	}

	if(lpMapOnInfo){
		lpMapOnInfo->Release();
		lpMapOnInfo = 0;
	}
	if(lpMapOffInfo){
		lpMapOffInfo->Release();
		lpMapOffInfo = 0;
	}
	if(lpMapOnImage){
		lpMapOnImage->Release();
		lpMapOnImage = 0;
	}
	if(lpCameraImage[0]){
		lpCameraImage[0]->Release();
		lpCameraImage[0] = 0;
	}
	if(lpCameraImage[1]){
		lpCameraImage[1]->Release();
		lpCameraImage[1] = 0;
	}

	if(lpLIFESpot){
		lpLIFESpot->Release();
		lpLIFESpot = 0;
	}
    if(lpSTMSpot){
		lpSTMSpot->Release();
		lpSTMSpot = 0;
	}
    if(lpMANASpot){
		lpMANASpot->Release();
		lpMANASpot = 0;
	}
	if(lpReStartMain){
		lpReStartMain->Release();
		lpReStartMain = 0;

	}

	for(i=0; i < 3 ; i++){
		if(lpReStartButton[i]){
			lpReStartButton[i]->Release();
			lpReStartButton[i] = 0;
		}
	}
	if(lpReStartMain){
		lpReStartMain->Release();
		lpReStartMain = 0;
		
	}
	for(i=0; i < 3 ; i++){	
		if(lpReStartButton[i]){
			lpReStartButton[i]->Release();
			lpReStartButton[i] = 0;
			
		}
	}
	for(i=0; i < 2 ; i++){	
		if(lpSelectSkill_Main[i]){
			lpSelectSkill_Main[i]->Release();
			lpSelectSkill_Main[i] = 0;

		}

		if(lpSelectChangeJob[i] ){
			lpSelectChangeJob[i]->Release();
			lpSelectChangeJob[i] = 0;
	
		}
	}
}		
/*----------------------------------------------------------------------------*
*							     ±×¸®±â  
*-----------------------------------------------------------------------------*/	
int sinWinSizeX[] = {1024,1280,1600};
int sinWinSizeXindex[] = {2,6,11,23};
int nCheckSkillDraw = 0;		//ÇØ¿Ü

extern char ratio_pt[ 4 ];
extern BOOL bIsWidescreen;
extern int Width, Height;

int iCount = 0;

void cINTERFACE::Draw()
{

	int i = 0; 
	int j = 0;
	//dsDrawTexImage( MatMain , 0,  0, 256, 128 , 255 );  //ÀÎÅÍÆäÀÌ½º ¸ÞÀÎ 

	dsDrawTexImage( cInterFace.MatMenu[0] , 800-256-256, 600-128, 256, 128 , 255 );  //ÀÎÅÍÆäÀÌ½º ¸ÞÀÎ      
	dsDrawTexImage( cInterFace.MatMenu[1] , 800-256, 600-64, 256, 64 , 255 );      //ÀÎÅÍÆäÀÌ½º ¸ÞÀÎ 

	//È®Àå ÀÎÅÍÆäÀÌ½º 
	DrawSprite(800,WinSizeY-64,lpGrowInterLeft,0,0,66,64,777);  // È®ÀåÀÎÅÍÆäÀÌ½º ÇÃ·º         
	// edit xxstr
	for(i = 0; i < 4; i++){
		/*if(sinWinSizeX[i] == WinSizeX){*/
			for(j = 0; j < sinWinSizeXindex[i] ; j++){
				DrawSprite(800 + 66 + (64 * j),WinSizeY-64,lpGrowInterMiddle,0,0,64,64,777);
			}
		//}
	}

	DrawSprite(WinSizeX - 40,WinSizeY-64,lpGrowInterRight,0,0,40,64,777);


	//DrawSprite(100,200,lpGrowInterLeft,0,0,80,80);

	///////////////////////ÀÜ»óÈ¿°ú 
	for(i = 0 ; i < 3 ; i++){
		if(sShadowState[i].Flag){
			dsDrawColorBox( sShadowState[i].Color ,sShadowState[i].Posi.x,sShadowState[i].Posi.y,
				sShadowState[i].Size.x, sShadowState[i].Size.y );

		}
	}

	DrawSprite(319,500+(94-sinBmpLength[0]),lpLIFE,0,(94-sinBmpLength[0]),16,94 ); //¶óÀÌÇÁ        
	DrawSprite(465,500+(94-sinBmpLength[1]),lpMP  ,0,(94-sinBmpLength[1]), 16,94); //¸¶³ª   
	DrawSprite(303,518+(76-sinBmpLength[2]),lpSTM ,0,(76-sinBmpLength[2]), 8,76);  //½ºÅ×¹Ì³ª 


//	DrawSprite(319,500+(94-sinBmpLength[0]),lpLIFE,0,0,16, sinBmpLength[0]); //¶óÀÌÇÁ   
//	DrawSprite(465,500+(94-sinBmpLength[1]),lpMP  ,0,0, 16,sinBmpLength[1]); //¸¶³ª   
//	DrawSprite(303,518+(76-sinBmpLength[2]),lpSTM ,0,0, 8,sinBmpLength[2]);  //½ºÅ×¹Ì³ª 

	/*
	if(sinBmpLength[0] <= 123 && sinBmpLength[0]  !=0) //¶óÀÌÇÁ 
		DrawSprite(111+sinBmpLength[0]-4,4 ,lpLIFESpot,0,0, 4,17); //¶óÀÌÇÁ ²À´Ù¸® 
	*/
/*
	if(sinChatEnter){
		dsDrawTexImage( MatChatDoc[0] , 0, 600-32-SubChatHeight, 256, 32 , 255 );    //Ã¤ÆÃÃ¢³»¿ë  
		dsDrawTexImage( MatChatDoc[1] , 256, 600-32-SubChatHeight, 128, 32 , 255 );  
	}

	if(ChatFlag){	
		if(SubChatHeight){
				dsDrawTexImage( MatChatSmall[0] , 0, 600-152-128-21, 256, 128 , 255 );     //»õ³¢  Ã¤ÆÃÃ¢ 
				dsDrawTexImage( MatChatSmall[1] , 256, 600-152-128-21, 128, 128 , 255 );   //»õ³¢  Ã¤ÆÃÃ¢ 
			}
			else{
				dsDrawTexImage( MatChatDefault[0] , 0, 600-256, 256, 256 , 255 );   //±âº» Ã¤ÆÃÃ¢ 
				dsDrawTexImage( MatChatDefault[1] , 256, 600-256, 128, 256 , 255 ); //±âº» Ã¤ÆÃÃ¢ 
			}
		
	}
*/ 

	if (ExitButtonClick)
	{
		dsDrawTexImage(MatExitMenu, 698, 504 - 30, 129, 96, 255);

		if (sinMenuBottonPosi == 1)
			DrawSprite(700, 505, lpMenuButton[0], 0, 0, 96, 19);

		if (sinMenuBottonPosi == 2)
			DrawSprite(700, 476, lpMenuButton[1], 0, 0, 96, 19);

		if (sinMenuBottonPosi == 3)
			DrawSprite(700, 535, lpMenuButton[2], 0, 0, 96, 19);


	}

	// Quando aperta enter pra digitar mensagem no chat
	// Flag de digitação do novo chat
	
	if (hFocusWnd && sinChatInputMode && !usehFocus)
	{
		DrawSprite(7, 580 - SubChatHeight, lpChatShowButton, 0, 0, 22, 19);
	}


	if(DayOrNightFlag ==1){ //³·     
		DrawSprite(363,589,lpSun,0,0,13,13); //ÇØ  
		DrawSprite(375,593,lpBar_Time,0,0,sinGageTime2,5); //°ÔÀÌÁö 
	}
	else{	//¹ã
		DrawSprite(426,589,lpMoon,0,0,13,13); //´Þ 
		DrawSprite(375+(50-sinGageTime2),593,lpBar_Time,(50-sinGageTime2),0,50,5); //°ÔÀÌÁö 

	}

	/*
	//ÇØ¿Í´Þ 
	if(SunandMoonFlag[0]) 
		DrawSprite(12,62,lpSun,0,0,12,12); //ÇØ 

	if(SunandMoonFlag[1])
		DrawSprite(57,7,lpMoon,0,0,12,12); //´Þ
	*/


	int TempGage = 0;

	if (sinSkill.pLeftSkill)
	{
		TempGage = (int)((41.0f * (float)sinSkill.pLeftSkill->GageLength) / 35.0f);
		DrawSprite(338, 542 + (41 - TempGage), lpGage[0], 0, 41 - TempGage, 16, 41);
	}

	if (sinSkill.pRightSkill)
	{
		TempGage = (int)((41.0f * (float)sinSkill.pRightSkill->GageLength) / 35.0f);
		DrawSprite(446, 542 + (41 - TempGage), lpGage[1], 0, 41 - TempGage, 16, 41);

	}

	/*
	if(SelectInterSkill){  //ÀÎÅÍÆäÀÌ½º ½ºÅ³ ¼±ÅÃ 
		DrawSprite(sLeftRightSkill[SelectInterSkill-1].BoxRect.left-3,
			sLeftRightSkill[SelectInterSkill-1].BoxRect.top-3,CSKILL->lpSelectSkill,0,0,44,44);

	}
	*/

	
	//ºÐ³ë °ÔÀÌÁö (ÀÓ½Ã)
	//DrawSprite(82,18,lpBar_Anger,0,0,27,40-ReSizelpGage); //°ÔÀÌÁö 

	//ºÐ³ë ¹öÆ° 
	//DrawSprite(82,18,lpButton_Anger,0,0,27,40-ReSizelpGage); //°ÔÀÌÁö 

//posição da barra de exp

	if (sinPKWarningExpFlag)
	{
		if (sinPKWarnigExpTime <= 15)
			DrawSprite(485, 508 + (86 - sinBmpLength[3]), lpBar_Exp, 0, (86 - sinBmpLength[3]), 6, 86);


	}
	else
		DrawSprite(485, 508 + (86 - sinBmpLength[3]), lpBar_Exp, 0, (86 - sinBmpLength[3]), 6, 86);

	//DrawSprite(505,588,lpBar_Time,0,0,sinBmpLength[4],5); 

	if (!sInterFlags.RunFlag)
		DrawSprite(575, 565, lpWalk, 0, 0, 24, 25);

	if (sInterFlags.CameraAutoFlag == 1)
		DrawSprite(575 + 24, 565, lpCameraImage[0], 0, 0, 24, 25);

	if (sInterFlags.CameraAutoFlag == 2)
		DrawSprite(575 + 24, 565, lpCameraImage[1], 0, 0, 24, 25);


	if (sInterFlags.MapOnFlag)
	{
		DrawSprite(575 + 24 + 24, 565, lpMapOnImage, 0, 0, 24, 25);
	}

	switch (sinRunCameraMapPosi)
	{
	case 1:
		if (sInterFlags.RunFlag)
		{
			DrawSprite(575 + 12 - (76 / 2), 565 - 29, lpRunInfo, 0, 0, 77, 27);
		}
		else
		{
			DrawSprite(575 + 12 - (76 / 2), 565 - 29, lpWalkInfo, 0, 0, 77, 27);

		}
		break;
	case 2:
		if (sInterFlags.CameraAutoFlag == 0)
		{
			DrawSprite(575 + 24 + 12 - (76 / 2), 565 - 29, lpCameraHandInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Hand", 0);
		}
		if (sInterFlags.CameraAutoFlag == 2)
		{
			DrawSprite(575 + 24 + 12 - (76 / 2), 565 - 29, lpCameraFixInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Fix", 0);

		}
		if (sInterFlags.CameraAutoFlag == 1)
		{
			DrawSprite(575 + 26 + 13 - (76 / 2), 565 - 29, lpCameraAutoInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Auto", 0);

		}
		break;
	case 3:
		if (sInterFlags.MapOnFlag)
		{
			DrawSprite(575 + 24 + 24 + 12 - (76 / 2), 565 - 29, lpMapOffInfo, 0, 0, 77, 27);

		}
		else
		{
			DrawSprite(575 + 24 + 24 + 12 - (76 / 2), 565 - 29, lpMapOnInfo, 0, 0, 77, 27);

		}
		break;

	}

	for (int t = 0; t < 6; t++)
	{
		if (MouseButtonPosi == t + 1)
		{
			if (InterButtonDown)
			{
				DrawSprite(648 + (t * 25), 560, lpButton2[t], 0, 0, 25, 27);

			}
			else
			{
				DrawSprite(648 + (t * 25), 560, lpButton[t], 0, 0, 25, 27);
				DrawSprite(648 - (77 - 23 - 1) + (t * 25), 560 - 27, lpInfoBox[t], 0, 0, 77, 27);
			}
		}
	}
/*

	switch(MouseButtonPosi){
	case 1:
		if(InterButtonDown)
			DrawSprite(651,567,lpButton2[0],0,0,24,25); //Ä³¸¯ÅÍ ½ºÅ×ÀÌÅÍ½º
		else{
			DrawSprite(651,567,lpButton[0],0,0,24,25); //Ä³¸¯ÅÍ ½ºÅ×ÀÌÅÍ½º
			DrawSprite(651-(77-23-1),567-27,lpInfoBox[0],0,0,77,27); //Ä³¸¯ÅÍ ½ºÅ×ÀÌÅÍ½º
			
		}
	break;

	case 2:
		if(InterButtonDown)
			DrawSprite(678+1,576+1,lpButton2[1],0,0,,24,25); //ÀÎº¥Åä¸® 
		else {
			DrawSprite(678+1,576+1,lpButton[1],0,0,24,25); //ÀÎº¥Åä¸® 
			DrawSprite(678+1-(77-23-1),576+1-27,lpInfoBox[1],0,0,77,27); //ÀÎº¥Åä¸® 
		}
	break;

	case 3:
		if(InterButtonDown)
			DrawSprite(701+1,576+1,lpButton2[2],0,0,24,25); //½ºÅ³  
		else {
			DrawSprite(701+1,576+1,lpButton[2],0,0,24,25); //½ºÅ³  
			DrawSprite(701+1-(77-23-2),576+1-27,lpInfoBox[2],0,0,77,27); //½ºÅ³  
		}
	break;

	case 4:
		if(InterButtonDown)
			DrawSprite(724+1,576+1,lpButton2[3],0,0,24,25); //ÆÄÆ¼
		else{
			DrawSprite(724+1,576+1,lpButton[3],0,0,24,25); //ÆÄÆ¼
			DrawSprite(724+1-(77-23-2),576+1-27,lpInfoBox[3],0,0,77,27); //ÆÄÆ¼
		}
	break;

	case 5:
		if(InterButtonDown)
			DrawSprite(747+1,576+1,lpButton2[4],0,0,24,25); //Äù½ºÆ®
		else{ 
			DrawSprite(747+1,576+1,lpButton[4],0,0,24,25); //Äù½ºÆ®
			DrawSprite(747+1-(77-23-1),576+1-27,lpInfoBox[4],0,0,77,27); //Äù½ºÆ®
		}
	break;

	case 6:
		if(InterButtonDown)
			DrawSprite(770+1,576+1,lpButton2[5],0,0,24,25); //½Ã½ºÅÛ 

		else{
			DrawSprite(770+1,576+1,lpButton[5],0,0,24,25); //½Ã½ºÅÛ 
			DrawSprite(770+1-(77-23-1),576+1-27,lpInfoBox[5],0,0,77,27); //½Ã½ºÅÛ 
		}
	break;

	}
*/

	//DrawClockArrow(61,57,1000);                   //½Ã°è¹Ù´ÃÀ» ±×¸°´Ù 
	//DrawCompass(63,52,lpCurPlayer->Angle.y&ANGCLIP);  //³ªÄ§¹ÝÀ» ±×¸°´Ù 


	if(SkillNpcFlag)
	{
		DrawSprite(SkillMasterMainXY.x,SkillMasterMainXY.y,lpReStartMain,0,0,188,128);
		DrawSprite(SkillMasterMainXY.x+ReStartButtonRect[0][0],SkillMasterMainXY.y+ReStartButtonRect[0][1],lpSelectSkill_Main[0],0,0,44,44); 
		DrawSprite(SkillMasterMainXY.x+ReStartButtonRect[1][0],SkillMasterMainXY.y+ReStartButtonRect[1][1],lpSelectChangeJob[0],0,0,44,44); 
		if(SkillMasterIndex){
			if(SkillMasterIndex == 1 && SkillMasterOkFlag[0])
				DrawSprite(SkillMasterMainXY.x+ReStartButtonRect[SkillMasterIndex-1][0],SkillMasterMainXY.y+ReStartButtonRect[SkillMasterIndex-1][1],lpSelectSkill_Main[1],0,0,44,44); 
			if(SkillMasterIndex == 2 && SkillMasterOkFlag[1])
				DrawSprite(SkillMasterMainXY.x+ReStartButtonRect[SkillMasterIndex-1][0],SkillMasterMainXY.y+ReStartButtonRect[SkillMasterIndex-1][1],lpSelectChangeJob[1],0,0,44,44); 
			if(SkillMasterIndex == 3)
				DrawSprite(SkillMasterMainXY.x+ReStartButtonRect[SkillMasterIndex-1][0],SkillMasterMainXY.y+ReStartButtonRect[SkillMasterIndex-1][1],lpReStartButton[2],0,0,44,44); 

		}
	}
	
	if (ShowSkillClose)
	{
		DrawSprite(269, 571 + (256 - sinMoveKindInter[SIN_SKILL]), cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(269, 571 - 27 + (256 - sinMoveKindInter[SIN_SKILL]), cInvenTory.lpExitInfo, 0, 0, 47, 27);
	}


	for(int k=0;k<10;k++){
		if(HaEffect[k].Flag){
			dsDrawTexImage(HaEffect[k].Mat, HaEffect[k].Posi.x,HaEffect[k].Posi.y,HaEffect[k].Size.x,
				HaEffect[k].Size.y,HaEffect[k].Alpha );
		}
	}
	  
	HDC hdc = NULL;

	char strBuff2[256];
	char strBuff[256];
	int len=0;
	int x=0,y=0;

	SelectObject( hdc , hFont ); 

	char *lpInput;

	if ( hFocusWnd && sinChatInputMode && !usehFocus) {     
	//if ( hFocusWnd && sinChatInputMode ) { 
		//DrawSprite(7,582-SubChatHeight,lpChatShowButton,0,0,22,19); //Ã¤ÆÃ

		GetWindowText( hTextWnd , strBuff2 , 240 );
		strBuff2[242]=0x0D;
		len = lstrlen( strBuff2 );

		//SetBkMode( hdc, TRANSPARENT );
		
		//wsprintf( strBuff, "¢º %s" , strBuff2 );
		wsprintf( strBuff, "  %s" , strBuff2 );

		len=lstrlen( strBuff );       
		if ( len>=38 ) {
			lpInput = &strBuff[len-38];
			len=38;
		}
		else 
			lpInput = strBuff;

		if ( sinChatInputMode==1 ) {
			x = 16 ; y = 584-SubChatHeight;
		}
		else {
			x = 16 ; y = 584-SubChatHeight;
		}
		
		SetFontTextColor( RGB(0, 0, 0) );
		dsTextLineOut( hdc , x+1, y+1 , lpInput , len );
		SetFontTextColor( RGB(255, 255, 255) );
		dsTextLineOut( hdc , x , y , lpInput , len );

		SIZE sizecheck;
		GetFontTextExtentPoint( lpInput, lstrlen( lpInput ), &sizecheck );

		static int i = 0;
		if( i < 12 )
		{
			SetFontTextColor( RGB( 0, 0, 0 ) );
			dsTextLineOut( hdc, ( x + 2 ) + sizecheck.cx, y, "|", 1 );
			SetFontTextColor( RGB( 255, 255, 255 ) );
			dsTextLineOut( hdc, x + 1 + sizecheck.cx, y - 1, "|", 1 );
		}

		i++;
		if( i > 24 )
			i = 0;

	}

	if ( sinChatDisplayMode ) {                   
		if ( sinChatDisplayMode==1 ) {
			if(NoticeChatIndex == 1){

				x = 16 ; y = 570-SubChatHeight-125; i = 3;
				DisplayChatMessage3( hdc , x , y , 44 , i , 5 );

				x = 16 ; y = 570-SubChatHeight-20; i = 8;
				DisplayChatMessage2( hdc , x , y , 44 , i );

			}
			else if(NoticeChatIndex == 2){
				x = 16 ; y = 570-SubChatHeight-20; i = 12;
				DisplayChatMessage3( hdc , x , y , 44 , i , 5 );
			}
			else{
				x = 16 ; y = 570-SubChatHeight-20; i = 12;
				DisplayChatMessage2( hdc , x , y , 44 , i );
			}
		}
		else {
			if(NoticeChatIndex == 2){
				x = 16 ; y = 570-SubChatHeight-5; i = 8;
				DisplayChatMessage3( hdc , x , y , 44 , i , 5 );
			}
			else{
				x = 16 ; y = 570-SubChatHeight-5; i = 8;
				DisplayChatMessage2( hdc , x , y , 44 , i );
			}
		}

		//if(NoticeChatIndex != 2 )
		//	DisplayChatMessage2( hdc , x , y , 44 , i );
	}

	int dsDrawOffsetArrayBackup = dsDrawOffsetArray;

	dsDrawOffsetArray = dsARRAY_TOP;

	if(SkillMasterFlag == 1 ){ 
		for(i = 0; i < SkillUpInfo.x ; i++){
			for(int j = 0; j< SkillUpInfo.y ; j++){
				if(i == 0 && j == 0 ) 
					dsDrawTexImage( cItem.MatItemInfoBox_TopLeft , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );
				if(j == 0 && i !=0 && i+1 < SkillUpInfo.x )
					dsDrawTexImage( cItem.MatItemInfoBox_TopCenter , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );
				if(j == 0 && i+1 == SkillUpInfo.x)
					dsDrawTexImage( cItem.MatItemInfoBox_TopRight , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );

				if(i == 0 && j != 0 && j+1 != SkillUpInfo.y)
					dsDrawTexImage( cItem.MatItemInfoBox_Left , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );
				if(i != 0 && j != 0 && i+1 !=SkillUpInfo.x && j+1 !=SkillUpInfo.y)
					dsDrawTexImage( cItem.MatItemInfoBox_Center , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );
				if(i+1 == SkillUpInfo.x && j != 0 && j+1 != SkillUpInfo.y)
					dsDrawTexImage( cItem.MatItemInfoBox_Right , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );
				
				if(i == 0 && j+1 == SkillUpInfo.y)
					dsDrawTexImage( cItem.MatItemInfoBox_BottomLeft , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );
				if(i != 0 && j+1 == SkillUpInfo.y && i+1 !=SkillUpInfo.x)
					dsDrawTexImage( cItem.MatItemInfoBox_BottomCenter , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );
				if(j+1 == SkillUpInfo.y && i+1 ==SkillUpInfo.x)
					dsDrawTexImage( cItem.MatItemInfoBox_BottomRight , SkillUpInfoPosi.x+(i*16) , SkillUpInfoPosi.y+(j*16), 16, 16 , 255 );
			}
		}
		
		if(ShowSkillUpInfo){
			for( i = 0 ; i < 10 ; i ++ ) {
				if(	SkillIconIndex[i]){
					DrawSprite(SkillUpInfoPosi.x+SkillIconPosi.x+(i*18)-10,SkillUpInfoPosi.y+SkillIconPosi.y,CSKILL->lpWeaponIcon[SkillIconIndex[i]],0,0,18,24); 
				}
			}

		}
		
		

		HDC hdc = NULL;

		int BoldFlag = 0;
		int MasteryLen = 0;
		int MasteryShowX = 0;

		char strBuff[128];
		memset(strBuff,0,sizeof(strBuff));
		//lpDDSBack->GetDC( &hdc );
		SelectObject( hdc, sinFont);
		//SetBkMode( hdc, TRANSPARENT );
		SetFontTextColor( RGB(255,255,255) );

		if(SkillMasterFlag == 1 && !ShowSkillUpInfo){
			SelectObject( hdc, sinBoldFont);
			//SetBkMode( hdc, TRANSPARENT );
			SetFontTextColor( RGB(222,231,255) );
			dsTextLineOut(hdc,100,225-80,SkillUseInfoText[0]   , lstrlen(SkillUseInfoText[0]) );
			
			//½ºÅ³Æ÷ÀÎÆ®¸¦ Âï¾îÁØ´Ù.
			if(sinSkill.SkillPoint||sinSkill.SkillPoint4){
				SelectObject( hdc, sinFont);
				//SetBkMode( hdc, TRANSPARENT );
				SetFontTextColor( RGB(255,255,255) );

				dsTextLineOut(hdc,100,260-80,SkillUseInfoText[1], lstrlen(SkillUseInfoText[1]) );
				dsTextLineOut(hdc,100,280-80,SkillUseInfoText[2], lstrlen(SkillUseInfoText[2]) );
				wsprintf(strBuff,sinMsgSkillPoint,sinSkill.SkillPoint);
				SelectObject( hdc, sinBoldFont);
				//SetBkMode( hdc, TRANSPARENT );
				SetFontTextColor( RGB(247,243,193) );
				dsTextLineOut(hdc,100,310-80,strBuff   , lstrlen(strBuff) );

				wsprintf(strBuff,sinMsgEliteSkillPoint,sinSkill.SkillPoint4);  
				SelectObject( hdc, sinBoldFont);
				//SetBkMode( hdc, TRANSPARENT );
				SetFontTextColor( RGB(147,243,193) );
				dsTextLineOut(hdc,103,310-55,strBuff   , lstrlen(strBuff) );
			}
			else{
				SelectObject( hdc, sinFont);
				//SetBkMode( hdc, TRANSPARENT );
				SetFontTextColor( RGB(255,64,64) );

				dsTextLineOut(hdc,100,260-80,SkillUseInfoText[3], lstrlen(SkillUseInfoText[3]) );
				dsTextLineOut(hdc,100,280-80,SkillUseInfoText[4], lstrlen(SkillUseInfoText[4]) );

			}


		}
		//lpDDSBack->ReleaseDC( hdc );
		
	}

	//Àü¾÷ ¹öÆ°
	if(SkillMasterFlag && !ShowSkillUpInfo && (CheckQuestButtonShow1 ||CheckQuestButtonShow2 ||CheckQuestButtonShow3) )    //½ºÅ³Á¤º¸¸¦ º¸¿©ÁÖ´Â ¿É¼ÇÀÌ ¾Æ´Ò°æ¿ì¿¡¸¸ Àü¾÷ ¹öÆ°À» ¶ç¿î´Ù 
	{
		if(sinChangeJobButtonShow || sinChangeJobButtonShow2 || sinChangeJobButtonShow3 || sinChangeJobButtonShow4 )
		{
			DrawSprite(240,380,lpSelectChangeJob[1],0,0,44,44); 
			nCheckSkillDraw = 1;
		}
		else
		{
			DrawSprite(240,380,lpSelectChangeJob[0],0,0,44,44); 
			nCheckSkillDraw = 2;
		}
	}

	if(SkillMasterFlag && !ShowSkillUpInfo && (nCheckSkillDraw == 1))
	{
		DrawSprite(240,380,lpSelectChangeJob[1],0,0,44,44); 
	}

	if(SkillMasterFlag && !ShowSkillUpInfo && (nCheckSkillDraw == 2))
	{
		DrawSprite(240,380,lpSelectChangeJob[0],0,0,44,44); 
	}

	dsDrawOffsetArray = dsDrawOffsetArrayBackup;

	/////////////////////½ºÅ³ Á¤º¸ ¹Ú½º 
	if(SkillInfoShowFlag && !ShowSkillUpInfo){ 
		if(SkillInfoShowFlag == 2)
			dsDrawOffsetArray = dsARRAY_TOP;
		for(i = 0; i < SkillBoxSize.x ; i++){
			for(int j = 0; j< SkillBoxSize.y ; j++){
				if(i == 0 && j == 0 ) //ÁÂÃø»ó´Ü 
					dsDrawTexImage( cItem.MatItemInfoBox_TopLeft , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );
				if(j == 0 && i !=0 && i+1 < SkillBoxSize.x ) //°¡¿îµ¥
					dsDrawTexImage( cItem.MatItemInfoBox_TopCenter , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );
				if(j == 0 && i+1 == SkillBoxSize.x) //¿ìÃø»ó´Ü

					dsDrawTexImage( cItem.MatItemInfoBox_TopRight , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );

				if(i == 0 && j != 0 && j+1 != SkillBoxSize.y) //ÁÂÃø ÁÙ°Å¸® 
					dsDrawTexImage( cItem.MatItemInfoBox_Left , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );
				if(i != 0 && j != 0 && i+1 !=SkillBoxSize.x && j+1 !=SkillBoxSize.y) //°¡¿îµ¥ Åä¸·
					dsDrawTexImage( cItem.MatItemInfoBox_Center , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );
				if(i+1 == SkillBoxSize.x && j != 0 && j+1 != SkillBoxSize.y) //¿ìÃø ÁÙ°Å¸® 
					dsDrawTexImage( cItem.MatItemInfoBox_Right , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );
				
				if(i == 0 && j+1 == SkillBoxSize.y) //¹Ø¹Ù´Ú ¿ÞÂÊ
					dsDrawTexImage( cItem.MatItemInfoBox_BottomLeft , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );
				if(i != 0 && j+1 == SkillBoxSize.y && i+1 !=SkillBoxSize.x)//¹Ø¹Ù´Ú °¡¿îµ¥
					dsDrawTexImage( cItem.MatItemInfoBox_BottomCenter , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );
				if(j+1 == SkillBoxSize.y && i+1 ==SkillBoxSize.x)//¹Ø¹Ù´Ú ¿À¸¥ÂÊ 
					dsDrawTexImage( cItem.MatItemInfoBox_BottomRight , SkillInfoBoxPosi.x+(i*16) , SkillInfoBoxPosi.y+(j*16), 16, 16 , 255 );


			}
		}
		for( i = 0 ; i < 10 ; i ++ ) {
			if(	SkillIconIndex[i]){
				DrawSprite(SkillInfoBoxPosi.x+SkillIconPosi.x+(i*18),SkillInfoBoxPosi.y+SkillIconPosi.y,CSKILL->lpWeaponIcon[SkillIconIndex[i]],0,0,18,24); 

			}
		}
	}
	///////// »ý¸í·Â, °æÇèÄ¡ µîµîÀÇ ±Û¾¾¸¦ Àßº¸ÀÌ°ÔÇØÁÙ ¹è°æ 
	if(InfoMessageBoxPos.x != 0 || InfoMessageBoxPos.y != 0 ){ //Ç¥½ÃÀ§Ä¡¿¡ °¬À»¶§¸¸ Ç¥½ÃÇÑ´Ù   
		dsDrawTexImage( cItem.MatItemInfoBox_Center , InfoMessageBoxPos.x-5,InfoMessageBoxPos.y-1, lstrlen(szInfoMsgBuff5)*6, 13 , 255 );
	}

	//°æÇèÄ¡ µÞ¹è°æÀº ÀÌÁ¦ Áñ~ (ÀÎÅÍÆäÀÌ½º ¹Ù²ñ)
	//if(ShowExpPercentFlag)  
	//	dsDrawTexImage( cItem.MatItemInfoBox_Center , 489-5,543-1, lstrlen(szInfoMsgBuff6)*6, 13 , 255 );

 
	//½ºÅ³ ÃÊ±âÈ­ ¹Ú½º¸¦ ¶ç¿î´Ù 
	CSKILL->ShowClearSkillPointButton(SkillInfoBoxPosi.x + (SkillBoxSize.x*16) , SkillInfoBoxPosi.y + (SkillBoxSize.y*16));

	int iToolTipY = 521;

	if( GetClick( 363, smConfig.ScreenSize.y - 13, 78, 10 ) )
	{
		dsDrawTexImage( Tooltip, 400 - 80, iToolTipY, 164, 67, 255 );
		HDC opHdc = NULL;

		if( hFont != NULL )
		{
			HFONT oldFont;
			oldFont = ( HFONT )SelectObject( opHdc, hFont );

			//SetBkMode( opHdc, TRANSPARENT );
			SetFontTextColor( RGB( 205, 200, 160 ) );
			dsTextLineOut( opHdc, 400 - 50, iToolTipY + 20, "Horário do jogo:", strlen( "Horário do jogo:" ) );

			char szTime[ 10 ] = { 0 };
			wsprintf( szTime, "%02d:%02d", dwGameHour, dwGameMin );

			//SetBkMode( opHdc, TRANSPARENT );
			SetFontTextColor( RGB( 255, 255, 255 ) );
			dsTextLineOut( opHdc, 400 - 20, iToolTipY + 40, szTime, strlen( szTime ) );

			if( oldFont )
				SelectObject( opHdc, oldFont );
		}
		//lpDDSBack->ReleaseDC( opHdc );
	}
}


void cINTERFACE::resize()
{
	ReStartMainXY.x = (smScreenWidth / 2) - (187 / 2);
	ReStartMainXY.y = (smScreenHeight / 2) - (127 / 2) - 100;

	ReStartTextXY.x = ReStartMainXY.x + 23;
	ReStartTextXY.y = ReStartMainXY.y + 73;

	SkillMasterMainXY.x = (smScreenWidth / 2) - (187 / 2) - 30;
	SkillMasterMainXY.y = (smScreenHeight / 2) - (127 / 2) - 100;

	SkillMasterTextXY.x = SkillMasterMainXY.x + 23;
	SkillMasterTextXY.y = SkillMasterMainXY.y + 73;
}

void resizeSin()
{
	cInterFace.resize();
}

DWORD dwCheckTime;
int   CheckNotUseSkillTime[3] = {0,0,0};
int   CheckNotUseSkillCount[3] = {0,0,0};
int   CheckTime2[3] ={0,0,0};
int   CheckExpFlag = 0;
int   CheckExpFlag2 = 0;
int   CheckExpTime = 0;

DWORD dwTestKeyTime = 0;
int   TeskKeyMessageCnt = 0;
char *szTestKeyMsg[6] = {"³ª!  &(^_^)&    ",
						 "³ë!  /(^_^)/   ",
						 "³ª!  *(^_^)*  ",
						 "",
						 "",
						 "",};
					
void cINTERFACE::Main()
{
	if ( GetFieldMapCursor()==TRUE && cInterFace.sInterFlags.MapOnFlag ) {
		cHelpPet.PetMessage("*Mini_Map",0);
	}

	if(cInterFace.ChatFlag){	         
		if(SubChatHeight){  
			if (0< pCursorPos.x  && 300 > pCursorPos.x  && 
					294 < pCursorPos.y  && 294+116 > pCursorPos.y  ){
						if(!ChatKindIndexNum){
							cHelpPet.PetMessage("*ChatBox",0);
						}

			}
		}
		else{
			if (0< pCursorPos.x  && 305 > pCursorPos.x  && 
					600-192 < pCursorPos.y  && 600-192+210 > pCursorPos.y  ){
						if( !ChatKindIndexNum){
							cHelpPet.PetMessage("*ChatBox",0);
						}

			}
		}
	}

	//Pet ¸Þ¼¼Áö
	if (365< pCursorPos.x  && 435 > pCursorPos.x  && 
			589 < pCursorPos.y  && 596 > pCursorPos.y  ){
				cHelpPet.PetMessage("*DayandNight",0);

	}


	GetWordTimeDisplay();
	
	if(sinPKWarningExpFlag){ 
		sinPKWarnigExpTime++;
		if(sinPKWarnigExpTime > 30)
			sinPKWarnigExpTime = 0;

	}
	else
		sinPKWarnigExpTime = 0;

	sinMenuBottonPosi = 0;
	
	if ( lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD && lpCurPlayer->FrameCounter>100 ) {
		ReStartFlag =1;
		if(!CheckExpFlag && !CheckExpFlag2){
			if(!CheckFieldContExp())
				RestartCheckExp = 1;

			CheckExpFlag = 1;
		}

	}
	if(CheckExpFlag2){ //¶«»§ 
		CheckExpTime++;
		if(CheckExpTime > 100){
			CheckExpFlag2 = 0;
			CheckExpTime = 0;

		}
	}

	if(dwGameHour >= 8 && dwGameHour <=18){
		SunandMoonFlag[0] = 1;
		SunandMoonFlag[1] = 0;
	}
	else{
		SunandMoonFlag[0] = 0;
		SunandMoonFlag[1] = 1;

	}
	if(sinLoadOK){
		if(!InitStateFlag)InitState();
		CheckingState();
	}

	MouseButtonPosi = 0;
	for(int i=0;i<6;i++){
		if ( ButtonRect[i][0] < pCursorPos.x  && ButtonRect[i][2] > pCursorPos.x  && 
			ButtonRect[i][1] < pCursorPos.y  && ButtonRect[i][3] > pCursorPos.y  ){
			MouseButtonPosi = i+1;
			switch(MouseButtonPosi){
				case 1:
					cHelpPet.PetMessage("*CarStatus",0);
				break;
				case 2:
					cHelpPet.PetMessage("*InvenTory",0);
				break;
				case 3:
					cHelpPet.PetMessage("*Skill",0);
				break;
				case 4:
					cHelpPet.PetMessage("*Party",0);
				break;
				case 5:
					cHelpPet.PetMessage("*Quest",0);
				break;
				case 6:
					cHelpPet.PetMessage("*System",0);
				break;

			}
		}
	}
	sinRunCameraMapPosi = 0; //ÃÊ±âÈ­ 
	for(int i=0 ;i<3 ; i++){
		if ( sinRunCameraMap[i][0] < pCursorPos.x  && sinRunCameraMap[i][2] > pCursorPos.x  && 
			sinRunCameraMap[i][1] < pCursorPos.y  && sinRunCameraMap[i][3] > pCursorPos.y  ){
			sinRunCameraMapPosi = i+1;
			switch(sinRunCameraMapPosi){
				case 1:
					cHelpPet.PetMessage("*RunAndWalk",0);
				break;
				case 2:
					//cHelpPet.PetMessage("*RunAndWalk",0);
				break;
				case 3:
					//cHelpPet.PetMessage("*Mini_Map",0);
				break;

			}
		}
	}

	if(ExitButtonClick){
		if (700 < pCursorPos.x && 796 > pCursorPos.x &&
			535 < pCursorPos.y && 555 > pCursorPos.y)
			sinMenuBottonPosi = 3;

		if (700 < pCursorPos.x && 796 > pCursorPos.x &&
			505 < pCursorPos.y && 525 > pCursorPos.y)
			sinMenuBottonPosi = 1;

		if (700 < pCursorPos.x && 796 > pCursorPos.x &&
			476 < pCursorPos.y && 496 > pCursorPos.y)
			sinMenuBottonPosi = 2;
			
	}

	////////////////////  Ã¤ÆÃ°ü·Ã (º¹ÀâÇÏ´Ï±î ¾È°Çµå¸°´Ù)
	if(cInvenTory.OpenFlag || cCharStatus.OpenFlag || CSKILL->OpenFlag){
		SubChatHeight = 170;
		sinChatInputMode =0;
		sinChatDisplayMode = 0;
		if(SubChatHeight>=170){
			SubChatHeight = 170;

		}

	}
	else
		SubChatHeight =0;

	if(sinChatEnter){
		if(SubChatHeight >=170)
			sinChatInputMode = 2;
		else 
			sinChatInputMode = 1;

	}
	else
		sinChatInputMode = 0;

	if(ChatFlag){
		if(SubChatHeight >=170)
			sinChatDisplayMode = 2;
		else 
			sinChatDisplayMode = 1;

	}
	else
		sinChatDisplayMode = 0;

	//////////////////////Ã¤ÆÃ°ü·Ã Flag ³¡ 

	CheckingState(); // »ý¸í·Â ,±â·Â , ±Ù·ÂÀÇ º¯È­Ä¡¸¦ Ã¼Å©ÇØ¼­ ÇöÀçÄ¡¸¸Å­ Bmp¸¦ º¸¿©ÁØ´Ù 
	ShowParaState(); // »ý¸í·Â ±â·Â ±Ù·Â °æÇèÄ¡ ¼öÄ¡¸¦ Ç¥½ÃÇÑ´Ù 
	ShowExpPercent(); //°æÇèÄ¡´Â °è¼ÓÀûÀ¸·Î º¸¿©ÁØ´Ù


	///////////////////// Àü»ç (°ÔÀÓ ´Ù½Ã½ÃÀÛ ÇÊµå , ¸¶À» , Á¾·á )
	ReStartIndex = 0; //ÃÊ±âÈ­ 
	memset(szReStartMsg,0,lstrlen(szReStartMsg)); //ÃÊ±âÈ­ 
	memset(szReStartMsg2,0,lstrlen(szReStartMsg2)); //ÃÊ±âÈ­ 

	if(ReStartFlag){
		sinMenuBottonPosi = 0;
		for(int i=0 ;i<3 ; i++){
			if ( ReStartMainXY.x+ReStartButtonRect[i][0] < pRealCursorPos.x  && ReStartMainXY.x+ReStartButtonRect[i][2] > pRealCursorPos.x  && 
				ReStartMainXY.y+ReStartButtonRect[i][1] < pRealCursorPos.y  && ReStartMainXY.y+ReStartButtonRect[i][3] > pRealCursorPos.y  ){
				if(RestartCheckExp){ //°æÇèÄ¡°¡ ºÎÁ·ÇÏ¿© ÇÊµå¿¡¼­ ½ÃÀÛÇÒ¼ö¾ø´Â °Ü¿ì 
					if( i ==0 ){
						ReStartIndex = i+1;
						lstrcpy(szReStartMsg,ReStartMsg[3]);
						lstrcpy(szReStartMsg2,ReStartMsg2[3]);

					}
					else{
						ReStartIndex = i+1;
						lstrcpy(szReStartMsg,ReStartMsg[i]);
						lstrcpy(szReStartMsg2,ReStartMsg2[i]);
					}

				}
				else if(i ==0&&lpCurPlayer->OnStageField>=0 && StageField[lpCurPlayer->OnStageField]->State==FIELD_STATE_CASTLE){
					ReStartIndex=0;
				}
				else{
					ReStartIndex = i+1;
					lstrcpy(szReStartMsg,ReStartMsg[i]);
					lstrcpy(szReStartMsg2,ReStartMsg2[i]);
				}

			}
		}
		dwCheckTime++;
		if(dwCheckTime > 70*20){ //10ÃÊ°¡ ³Ñ¾î°¡¸é 
			ReStartFlag = 0; //ÇÃ·¢ ÃÊ±âÈ­ 
			ReStartOptionIndex = RESTART_TOWN; //Å¸¿î¿¡¼­ ½ÃÀÛÇÑ´Ù 
			CheckExpFlag = 0;
			CheckExpFlag2 = 1;
			RestartCheckExp = 0; //ÇÃ·¢µéÀ» ÃÊ±âÈ­ÇÑ´Ù
		}
	
	}
	else
		dwCheckTime = 0; //ÇÃ·¢ÀÌ ¾øÀ¸¸é ÃÊ±âÈ­ÇÑ´Ù 
	///////////////////// ½ºÅ³ , Àü¾÷ 
	SkillMasterIndex = 0; //ÃÊ±âÈ­ 
	memset(szSkillMasterMsg,0,lstrlen(szSkillMasterMsg)); //ÃÊ±âÈ­ 
	memset(szSkillMasterMsg2,0,lstrlen(szSkillMasterMsg2)); //ÃÊ±âÈ­ 

	/////////Å°¿öµå ½ºÅ³ 
	if(SkillNpcFlag){
		
		sinMenuBottonPosi = 0;
		for ( int i = 0; i<3; i++ )
		{
			if ( SkillMasterMainXY.x+ReStartButtonRect[i][0] < pCursorPos.x  && SkillMasterMainXY.x+ReStartButtonRect[i][2] > pCursorPos.x  && 
				SkillMasterMainXY.y+ReStartButtonRect[i][1] < pCursorPos.y  && SkillMasterMainXY.y+ReStartButtonRect[i][3] > pCursorPos.y  ){
				SkillMasterIndex = i+1;
				lstrcpy(szSkillMasterMsg,SkillMaster[i]);
				lstrcpy(szSkillMasterMsg2,SkillMaster2[i]);

			}
		}
	}
	//½ºÅ³ ÃæÁ·¿ä°Ç ºÎÁ·½Ã È¿°ú 
	for(int t = 0; t < 3 ; t++){
		if(NotUseSkillElement[t]){
			CheckNotUseSkillTime[t]++;
			if(CheckNotUseSkillTime[t] > 12 ){
				if(NotUseSkillEffect[t])NotUseSkillEffect[t] = 0;
				else NotUseSkillEffect[t] = 1;
				CheckNotUseSkillTime[t] = 0;
				CheckNotUseSkillCount[t]++;
				if(CheckNotUseSkillCount[t] > 4){
					CheckNotUseSkillCount[t] = 0;
					CheckNotUseSkillTime[t] = 0;
					NotUseSkillEffect[t] = 0;
					NotUseSkillElement[t] = 0;
					SkillMouseButtonPosi[0] = 0;
					SkillMouseButtonPosi[1] = 0;


				}

			}
		}
		if(NotUseSkillEffect[t]){
			CheckTime2[t]++;	//°ÔÀÌÁö°¡ ¾Èº¸ÀÎ´Ù°í ÇØ¼­ º¸Á¤ÇØÁá´Ù (³¯Ä¡±â·Î)

		}
		else
			CheckTime2[t] = 0;
		if(CheckTime2[t] > 20) //¿©±â¼­ º¸Á¤ÇØÁØ´Ù 
			NotUseSkillEffect[t] = 0;


	}
	
	//ÀÌÆåÆ®±ÛÀÚ¸¦ º¸¿©ÁØ´Ù====================================================
	for(int k = 0 ; k < MAX_HAEFFECTNUM ; k++){      
		if(HaEffect[k].Flag){ 
			if(HaEffect[k].Time<3000)
				HaEffect[k].Time+=20;
			
			switch(HaEffect[k].Time/255){
				case 0:
					HaEffect[k].Alpha=255;
				break;
				case 1:
					HaEffect[k].Alpha=255;
				break;
				case 2:	
				case 3:
				case 4:
				case 5:
				case 6:
					//±ÛÀÚ°¡ »ç¶óÁö´Â È¿°ú
					HaEffect[k].Alpha-=10;
					HaEffect[k].Posi.x-=1;
					HaEffect[k].Posi.y-=1; 
					HaEffect[k].Size.x+=3;
					HaEffect[k].Size.y+=3;
					if(HaEffect[k].Alpha<=0){
						HaEffect[k].Alpha=0;
						HaEffect[k].Time=0;
						HaEffect[k].Flag=0;
					}
				break;
			};
		}
	}
	//===========================================================================

}
/*----------------------------------------------------------------------------*
*							     Á¾·á 
*-----------------------------------------------------------------------------*/	
void cINTERFACE::Close()
{
	Release();
}
/*----------------------------------------------------------------------------*
*							   LButtonDown
*-----------------------------------------------------------------------------*/	
void cINTERFACE::LButtonDown(int x , int y)
{
	
	switch(sinRunCameraMapPosi){
		case 1:
			//cHelpPet.PetMessage("*RunAndWalk",1);
		break;
		case 3:
			//cHelpPet.PetMessage("*Mini_Map",1);
		break;
	}
	/*

	if(sInterFlags.CameraAutoFlag == 0){ //Ä«¸Þ¶ó ¼öµ¿ 
		cHelpPet.PetMessage("*Camera_Hand",1);
	}
	if(sInterFlags.CameraAutoFlag == 2){ //Ä«¸Þ¶ó °íÁ¤ 
		cHelpPet.PetMessage("*Camera_Fix",1);
	}
	if(sInterFlags.CameraAutoFlag ==1 ){//Ä«¸Þ¶ó ÀÚµ¿ 
		cHelpPet.PetMessage("*Camera_Auto",1);
	}

	*/

	//Pet ¸Þ¼¼Áö
	//PetMessage
	if (365< pCursorPos.x  && 435 > pCursorPos.x  &&  
			589 < pCursorPos.y  && 596 > pCursorPos.y  ){
				cHelpPet.PetMessage("*DayandNight",1);

	}

	//Pet ¸Þ¼¼Áö
	if(pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594){//¶óÀÌÇÁ 
		cHelpPet.PetMessage("*Bar_Life",1); 
	}
	if(pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595){//±â·Â
		cHelpPet.PetMessage("*Bar_Mana",1);
	}
	if(pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595){//±Ù·Â
		cHelpPet.PetMessage("*Bar_Stamina",1);
	}	
	if(pCursorPos.x > 483 && pCursorPos.x < 483+10 && pCursorPos.y > 513 && pCursorPos.y < 595){//°æÇèÄ¡
			cHelpPet.PetMessage("*Bar_Exp",1);
	}	
	if(pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 540 && pCursorPos.y < 594){//°æÇèÄ¡ 
		cHelpPet.PetMessage("*Exp_Num",1);
	}
	if ( GetFieldMapCursor()==TRUE && cInterFace.sInterFlags.MapOnFlag ) {
		cHelpPet.PetMessage("*Mini_Map",1); 

	}




	if(cInterFace.ChatFlag){	         
		if(SubChatHeight){ 
			if (0< pCursorPos.x  && 300 > pCursorPos.x  && 
					294 < pCursorPos.y  && 294+116 > pCursorPos.y  ){
						if(!ChatKindIndexNum){
							cHelpPet.PetMessage("*ChatBox",1);
						}

			}
		}
		else{
			if (0< pCursorPos.x  && 305 > pCursorPos.x  && 
					600-192 < pCursorPos.y  && 600-192+210 > pCursorPos.y  ){
						if(!ChatKindIndexNum){
							cHelpPet.PetMessage("*ChatBox",1);
						}

			}
		}
	}

	SkillMouseButtonPosi[0] = 1;
	ChangeJobButtonclick = 0;
	ReStartOptionIndex = 0; //ÀÎµ¦½º ÃÊ±âÈ­ 
	//Ã¤ÆÃÃ¢¿Ã¸®±â 
	if(x > 7 && 22 > x && y > 579-SubChatHeight && y < 579+19-SubChatHeight){ 
		if(!ChatFlag)ChatFlag = 1;
		else ChatFlag = 0;
		if(ChatFlag)sinChatEnter = 1;
	}
	switch(sinRunCameraMapPosi){
	case 1: //°È±â ´Þ¸®±â 
		if(sInterFlags.RunFlag)sInterFlags.RunFlag = 0;
		else sInterFlags.RunFlag =1;
	break;
	case 2: //Ä«¸Þ¶ó ÀÚµ¿ ¼öµ¿ 
		sInterFlags.CameraAutoFlag++;
		if(sInterFlags.CameraAutoFlag > 2)sInterFlags.CameraAutoFlag = 0;

	break;
	case 3: //¿ÀÅä¸Ê 
		if(sInterFlags.MapOnFlag)sInterFlags.MapOnFlag = 0;
		else sInterFlags.MapOnFlag = 1;

	break;
	
	};

	if(sinMenuBottonPosi == 3){ //°ÔÀÓÀ» Á¾·áÇÑ´Ù 
			QuitGame();
	}


	if( sinMenuBottonPosi == 2 )
	{ //°ÔÀÓÀ» Á¾·áÇÑ´Ù 
		Settings::GetInstance()->Open();
		ExitButtonClick = 0;
		//bSettings = TRUE;
	}

	char *HelpFilePath = "image\\Sinimage\\Help\\Help.sin"; 
	if(sinMenuBottonPosi == 1){ //µµ¿ò¸»À» ¶ç¿î´Ù (È£µ¿ÇÁ¸°½º°¡ -50ÇØ´Þ¶õ´Ù)
			cSinHelp.sinShowHelp(SIN_HELP_KIND_NORMAL,208,61-50,11,11, D3DCOLOR_RGBA(19,27,20,165),HelpFilePath); 
			ExitButtonClick = 0; 
			HelpBoxKindIndex = SIN_HELP;
	}

	if(MouseButtonPosi){ //¹öÆ°Æ÷Áö¼Ç¿¡¼­ ¸¶¿ì½º ¹öÆ°ÀÌ Å¬¸¯‰çÀ»¶§ 
		InterButtonDown = 1;
		switch(MouseButtonPosi){ //PetMessage
			case 1:
				cHelpPet.PetMessage("*CarStatus",1);
			break;
			case 2:
				cHelpPet.PetMessage("*InvenTory",1);
			break;
			case 3:
				cHelpPet.PetMessage("*Skill",1);
			break;
			case 4:
				cHelpPet.PetMessage("*Party",1);
			break;
			case 5:
				cHelpPet.PetMessage("*Quest",1);
			break;
			case 6:
				cHelpPet.PetMessage("*System",1);
			break;
		}

	}
	if(ReStartFlag){    //Àü»ç ¿É¼Ç ¹öÆ° 
		switch(ReStartIndex){
		case RESTART_TOWN:
			ReStartOptionIndex = RESTART_TOWN;
			ReStartFlag = 0;
			RestartCheckExp = 0; //ÃÊ±âÈ­ÇØÁØ´Ù 
		
		break;
		case RESTART_FEILD:
			if(RestartCheckExp)break;
			ReStartOptionIndex = RESTART_FEILD;
			ReStartFlag = 0;
			RestartCheckExp = 0; //ÃÊ±âÈ­ÇØÁØ´Ù 
		
		break;
		case RESTART_EXIT:
			ReStartOptionIndex = RESTART_EXIT;
			ReStartFlag = 0;
			RestartCheckExp = 0; //ÃÊ±âÈ­ÇØÁØ´Ù 

		break;

		}

		CheckExpFlag2 = 1;
		CheckExpFlag = 0;

	}
	//½ºÅ³ , Àü¾÷ 
	if(SkillMasterIndex){

		if(SkillMasterIndex==1 &&  SkillMasterOkFlag[0]){
			SkillMasterFlag = SkillMasterIndex; //½ºÅ³ 
			SkillNpcFlag = 0;
			CSKILL->OpenFlag = 1;
			cInterFace.CheckAllBox(SIN_SKILL); //Ã¢À» ÇÏ³ª¸¸ ¶ç¿î´Ù 

		}
		if(SkillMasterIndex==2 &&  SkillMasterOkFlag[1]){
			SkillMasterFlag = SkillMasterIndex; //Àü¾÷ 
			SkillNpcFlag = 0;
			////////////////////// ¸Þ¼¼Áö ¹Ú½º¸¦ ¶ç¿öÁØ´Ù 
			sinJobList = GetJobDataCode(sinChar->JOB_CODE , sinChar->ChangeJob+1);
			cMessageBox.ShowMessage3(MESSAGE_CHANGE_JOB,sinJobList->szName2);


		}

		if(SkillMasterIndex==3){
			SkillMasterFlag = SkillMasterIndex; //Á¾·á  
			SkillNpcFlag = 0;
		}
	}

}
/*----------------------------------------------------------------------------*
*							   LButtonUp
*-----------------------------------------------------------------------------*/	
void cINTERFACE::LButtonUp(int x , int y)
{
	if(MouseButtonPosi){
		switch(MouseButtonPosi){
		case 1: //Ä³¸¯ÅÍ ½ºÅ×ÀÌÅÍ½º 
			if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
			else cCharStatus.OpenFlag = SIN_OPEN;
			cInterFace.CheckAllBox(SIN_CHARSTATUS); //Ã¢À» ÇÏ³ª¸¸ ¶ç¿î´Ù 
			if(cCharStatus.OpenFlag){
				if(!sinFireShow){
					StartMenuFlame(0,350);
					sinPlaySound( 0 );
				
				}
				else
					sinPlaySound(SIN_SOUND_SHOW_INTER);
				sinFireShow = 1;
			}

		break;
		case 2: //ÀÎº¥Åä¸® 
			if(cInvenTory.OpenFlag)cInvenTory.OpenFlag = SIN_CLOSE;
			else cInvenTory.OpenFlag = SIN_OPEN;
			cInterFace.CheckAllBox(SIN_INVENTORY); //Ã¢À» ÇÏ³ª¸¸ ¶ç¿î´Ù 
			if(cInvenTory.OpenFlag){
				if(!sinFireShow){
					StartMenuFlame(0,350);
					sinPlaySound( 0 );
				}
				else
					sinPlaySound(SIN_SOUND_SHOW_INTER);

				sinFireShow = 1;
			}

		break;
		case 3: //½ºÅ³ 

			if(CSKILL->OpenFlag == SIN_CLOSE)CSKILL->OpenFlag = SIN_OPEN;
			else CSKILL->OpenFlag = SIN_CLOSE;
			cInterFace.CheckAllBox(SIN_SKILL); //Ã¢À» ÇÏ³ª¸¸ ¶ç¿î´Ù 
			if(CSKILL->OpenFlag){
				if(!sinFireShow){
					StartMenuFlame(0,350);
					sinPlaySound( 0 );
				}
				else
					sinPlaySound(SIN_SOUND_SHOW_INTER);

				sinFireShow = 1;
			}
			
		break;

		case 4:
			ShowParty();

		break;

		case 5:
			ShowQuest();
			
		break;

		case 6:
			if(!ExitButtonClick)ExitButtonClick =1;
			else ExitButtonClick = 0;
			cInterFace.CheckAllBox(SIN_SYSTEM); //Ã¢À» ÇÏ³ª¸¸ ¶ç¿î´Ù 

		break;
		}

	}

	InterButtonDown = 0; //¹öÆ°¾÷ÀÏ¶§´Â ÃÊ±âÈ­ 


}
/*----------------------------------------------------------------------------*
*							   RButtonDown
*-----------------------------------------------------------------------------*/	
void cINTERFACE::RButtonDown(int x , int y)
{

	if ( GetFieldMapCursor()==TRUE && cInterFace.sInterFlags.MapOnFlag ) {
		cHelpPet.PetMessage("*Mini_Map",2);

	}


	if(MouseButtonPosi){ //¹öÆ°Æ÷Áö¼Ç¿¡¼­ ¸¶¿ì½º ¹öÆ°ÀÌ Å¬¸¯‰çÀ»¶§ 
		switch(MouseButtonPosi){ //PetMessage
			case 1:
				cHelpPet.PetMessage("*CarStatus",2);
			break;
			case 2:
				cHelpPet.PetMessage("*InvenTory",2);
			break;
			case 3:
				cHelpPet.PetMessage("*Skill",2);
			break;
			case 4:
				cHelpPet.PetMessage("*Party",2);
			break;
			case 5:
				cHelpPet.PetMessage("*Quest",2);
			break;
			case 6:
				cHelpPet.PetMessage("*System",2);
			break;
		}

	}

	switch(sinRunCameraMapPosi){
		case 1:
			cHelpPet.PetMessage("*RunAndWalk",2);
		break;
		case 2:
			if(sInterFlags.CameraAutoFlag == 0){ //Ä«¸Þ¶ó ¼öµ¿ 
				cHelpPet.PetMessage("*Camera_Hand",2);
			}
			if(sInterFlags.CameraAutoFlag == 2){ //Ä«¸Þ¶ó °íÁ¤ 
				cHelpPet.PetMessage("*Camera_Fix",2);
			}
			if(sInterFlags.CameraAutoFlag ==1 ){//Ä«¸Þ¶ó ÀÚµ¿ 
				cHelpPet.PetMessage("*Camera_Auto",2);
			}

		break;
		case 3:
			//cHelpPet.PetMessage("*Mini_Map",2);
		break;
	}



	//Pet ¸Þ¼¼Áö
	//PetMessage
	if (365< pCursorPos.x  && 435 > pCursorPos.x  && 
			589 < pCursorPos.y  && 596 > pCursorPos.y  ){
				cHelpPet.PetMessage("*DayandNight",2);

	}

	//Pet ¸Þ¼¼Áö
	if(pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594){//¶óÀÌÇÁ 
		cHelpPet.PetMessage("*Bar_Life",2);
	}
	if(pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595){//±â·Â
		cHelpPet.PetMessage("*Bar_Mana",2);
	}
	if(pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595){//±Ù·Â
		cHelpPet.PetMessage("*Bar_Stamina",2);
	}	
	if(pCursorPos.x > 483 && pCursorPos.x < 483+10 && pCursorPos.y > 513 && pCursorPos.y < 595){//°æÇèÄ¡
		cHelpPet.PetMessage("*Bar_Exp",2);  
	}	
	if(pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 540 && pCursorPos.y < 594){//°æÇèÄ¡ 
		cHelpPet.PetMessage("*Exp_Num",2);
	}



	if(cInterFace.ChatFlag){	         
		if(SubChatHeight){ 
			if (0< pCursorPos.x  && 300 > pCursorPos.x  && 
					294 < pCursorPos.y  && 294+116 > pCursorPos.y  ){
						if(!ChatKindIndexNum){
							cHelpPet.PetMessage("*ChatBox",2);
						}

			}
		}
		else{
			if (0< pCursorPos.x  && 305 > pCursorPos.x  && 
					600-192 < pCursorPos.y  && 600-192+210 > pCursorPos.y  ){
						if(!ChatKindIndexNum){
							cHelpPet.PetMessage("*ChatBox",2);
						}

			}
		}
	}

	SkillMouseButtonPosi[1] = 1;
}
/*----------------------------------------------------------------------------*
*							   RButtonUp
*-----------------------------------------------------------------------------*/	
void cINTERFACE::RButtonUp(int x , int y)
{

}
/*----------------------------------------------------------------------------*
*							    KeyDown
*-----------------------------------------------------------------------------*/	
char InputSecretCode[256];
char sinBuff[256];
int  ResetQuset3Flag = 0;

void PassRankUp()
{
	for (int x = 0; x < 3; x++)
	{
		sinChar->ChangeJob++;
		CSKILL->SearchUseSkill();
	}

	if (sinChar->ChangeJob > 3)sinChar->ChangeJob = 3;
}

// Função para completar todas as quests - DESATIVADA POR PADRÃO
void CompleteAllQuests()
{
	/*
	ESTA FUNÇÃO FOI DESATIVADA PARA EVITAR USO INAPROPRIADO
	OU PARA SERVIDORES OFICIAIS ONDE COMANDOS DE DEBUG NÃO SÃO PERMITIDOS

	Para reativar, remova todos os comentários de bloco (/* ... * /)
	e as verificações de condição adicionadas.

	AVISO: Usar esta função pode violar os Termos de Serviço do jogo
	e resultar em banimento permanente.
	*/

#if DEBUG
	// Apenas para fins de debug em ambiente de desenvolvimento
	// SendChatMessageToServer("Todas as quests finalizadas.");
#endif

/*
// =============== QUESTS ELEMENTARES ===============
// Quest A
SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_A, 2, 0, 0);
haElementaryQuestLog |= QUESTBIT_ELEMENTARY_A;
sinPlaySound(SIN_SOUND_EAT_POTION2);
chaQuest.sHaQuestElementary[Quest_A].State = 100;
chaQuest.sHaQuestElementary[Quest_A].BackUpCode = chaQuest.sHaQuestElementary[Quest_A].CODE;
chaQuest.sHaQuestElementary[Quest_A].CODE = 0;
EndQuest_Code(chaQuest.sHaQuestElementary[Quest_A].BackUpCode);

// Quest B
SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_B, 2, 0, 0);
haElementaryQuestLog |= QUESTBIT_ELEMENTARY_B;
sinPlaySound(SIN_SOUND_EAT_POTION2);
chaQuest.sHaQuestElementary[Quest_B].State = 100;
chaQuest.sHaQuestElementary[Quest_B].BackUpCode = chaQuest.sHaQuestElementary[Quest_B].CODE;
chaQuest.sHaQuestElementary[Quest_B].CODE = 0;
EndQuest_Code(chaQuest.sHaQuestElementary[Quest_B].BackUpCode);

// Quest C
SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_C, 2, 10, 0);
haElementaryQuestLog |= QUESTBIT_ELEMENTARY_C;
sinPlaySound(SIN_SOUND_EAT_POTION2);
chaQuest.sHaQuestElementary[Quest_C].State = 100;
chaQuest.sHaQuestElementary[Quest_C].BackUpCode = chaQuest.sHaQuestElementary[Quest_C].CODE;
chaQuest.sHaQuestElementary[Quest_C].CODE = 0;
EndQuest_Code(chaQuest.sHaQuestElementary[Quest_C].BackUpCode);

// Quest D
SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_D, 2, 0, 0);
haElementaryQuestLog |= QUESTBIT_ELEMENTARY_D;
sinPlaySound(SIN_SOUND_EAT_POTION2);
chaQuest.sHaQuestElementary[Quest_D].State = 100;
chaQuest.sHaQuestElementary[Quest_D].BackUpCode = chaQuest.sHaQuestElementary[Quest_D].CODE;
chaQuest.sHaQuestElementary[Quest_D].CODE = 0;
EndQuest_Code(chaQuest.sHaQuestElementary[Quest_D].BackUpCode);

// Quest E
SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_E, 2, 0, 0);
haElementaryQuestLog |= QUESTBIT_ELEMENTARY_E;
sinPlaySound(SIN_SOUND_EAT_POTION2);
chaQuest.sHaQuestElementary[Quest_E].State = 100;
chaQuest.sHaQuestElementary[Quest_E].BackUpCode = chaQuest.sHaQuestElementary[Quest_E].CODE;
chaQuest.sHaQuestElementary[Quest_E].CODE = 0;
EndQuest_Code(chaQuest.sHaQuestElementary[Quest_E].BackUpCode);

// Quest G
SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_G, 2, 20, 0);
haElementaryQuestLog |= QUESTBIT_ELEMENTARY_G;
sinPlaySound(SIN_SOUND_EAT_POTION2);
chaQuest.sHaQuestElementary[Quest_G].State = 100;
chaQuest.sHaQuestElementary[Quest_G].BackUpCode = chaQuest.sHaQuestElementary[Quest_G].CODE;
chaQuest.sHaQuestElementary[Quest_G].CODE = 0;
EndQuest_Code(chaQuest.sHaQuestElementary[Quest_G].BackUpCode);

// =============== QUESTS POR NÍVEL ===============
// Level 30
if (sinQuest_Level30.State < 3 && sinChar.Level >= 30)
{
	CheckCharForm();
	sinChar.StatePoint += 5;
	sinQuest_levelLog |= QUESTBIT_LEVEL_30;
	sinQuest_Level30.State = 3;
	sinQuest_Level30.BackUpCode = sinQuest_Level30.CODE;
	sinQuest_Level30.CODE = 0;
	EndQuest_Code(sinQuest_Level30.BackUpCode);
	sinQuest_Level30.CODE = 0;
	ReformCharForm();
}

// Level 55 (para classes < 5)
if (sinQuest_Level55.State < 2 && sinChar.Level >= 55 && sinChar.JOB_CODE < 5)
{
	CheckCharForm();
	sinSkill.SkillPoint += 1;
	sinQuest_levelLog |= QUESTBIT_LEVEL_55;
	sinQuest_Level55.State = 3;
	sinQuest_Level55.BackUpCode = sinQuest_Level55.CODE;
	sinQuest_Level55.CODE = 0;
	EndQuest_Code(sinQuest_Level55.BackUpCode);
	sinQuest_Level55.CODE = 0;
	ReformCharForm();
}

// Level 55 (para classes > 4)
if (sinQuest_Level55_2.State < 2 && sinChar.Level >= 55 && sinChar.JOB_CODE > 4)
{
	CheckCharForm();
	sinSkill.SkillPoint += 1;
	sinQuest_levelLog |= QUESTBIT_LEVEL_55;
	sinQuest_Level55_2.State = 3;
	sinQuest_Level55_2.BackUpCode = sinQuest_Level55_2.CODE;
	sinQuest_Level55_2.CODE = 0;
	EndQuest_Code(sinQuest_Level55_2.BackUpCode);
	sinQuest_Level55_2.CODE = 0;
	ReformCharForm();
}

// Level 70
if (sinQuest_Level70.State < 2 && sinChar.Level >= 70)
{
	CheckCharForm();
	sinChar.StatePoint += 5;
	sinSkill.SkillPoint += 1;
	sinQuest_levelLog |= QUESTBIT_LEVEL_70;
	sinQuest_Level70.State = 3;
	sinQuest_Level70.BackUpCode = sinQuest_Level70.CODE;
	sinQuest_Level70.CODE = 0;
	EndQuest_Code(sinQuest_Level70.BackUpCode);
	sinQuest_Level70.CODE = 0;
	ReformCharForm();
}

// Level 80
if (sinQuest_Level80.State < 2 && sinChar.Level >= 80)
{
	CheckCharForm();
	sinChar.StatePoint += 5;
	sinSkill.SkillPoint += 2;
	sinQuest_levelLog |= QUESTBIT_LEVEL_80;
	sinQuest_Level80.State = 3;
	sinQuest_Level80.BackUpCode = sinQuest_Level80.CODE;
	sinQuest_Level80.CODE = 0;
	EndQuest_Code(sinQuest_Level80.BackUpCode);
	sinQuest_Level80.CODE = 0;
	ReformCharForm();
}

// Level 85
if (sinQuest_Level85.State < 4 && sinChar.Level >= 85)
{
	CheckCharForm();
	sinQuest_levelLog |= QUESTBIT_LEVEL_85;
	sinQuest_Level85.State = 4;
	sinQuest_Level85.BackUpCode = sinQuest_Level85.CODE;
	sinQuest_Level85.CODE = 0;
	EndQuest_Code(sinQuest_Level85.BackUpCode);
	sinQuest_Level85.CODE = 0;
	ReformCharForm();
}

// Level 90
if (sinQuest_Level90.State < 3 && sinChar.Level >= 90)
{
	CheckCharForm();
	sinQuest_levelLog |= QUESTBIT_LEVEL_90;
	sinQuest_Level90.State = 3;
	sinQuest_Level90.BackUpCode = sinQuest_Level90.CODE;
	sinQuest_Level90.CODE = 0;
	EndQuest_Code(sinQuest_Level90.BackUpCode);
	sinQuest_Level90.CODE = 0;
	ReformCharForm();
	cInvenTory.SetItemToChar();
	if (!cInvenTory.SearchItemCode(sinQT1 | sin07))
	{
		SendQuestCommandToServer(SIN_QUEST_CODE_LEVEL90, 0, 0, 0);
	}
}

// Limpeza de itens da Quest Level 80 (parte 2)
if (sinQuest_Level80_2.State == 3)
{
	DeleteQuestItem(sinQT1 | sin09);
	DeleteQuestItem(sinQT1 | sin10);
	DeleteQuestItem(sinQT1 | sin11);
}

// Level 80 (parte 2)
if (sinQuest_Level80_2.State < 5 && sinChar.Level >= 80)
{
	CheckCharForm();
	sinQuest_levelLog |= QUESTBIT_LEVEL_80_2;
	sinQuest_Level80_2.BackUpCode = sinQuest_Level80_2.CODE;
	sinQuest_Level80_2.CODE = 0;
	EndQuest_Code(sinQuest_Level80_2.BackUpCode);
	sinQuest_Level80_2.CODE = 0;
	sinQuest_Level80_2.State = 5;

	if (cInvenTory.SearchItemCode(sinQT1 | sin12))
	{
		DeleteQuestItem(sinQT1 | sin12);
	}

	ReformCharStatePoint(sinChar, sinQuest_levelLog);
	ReformCharForm();
	cInvenTory.SetItemToChar();
	sinPlaySound(SIN_SOUND_EAT_POTION2);
	SetQuestBoard();
}

// Level 90 (parte 2)
if (sinQuest_Level90_2.State < 4 && sinChar.Level >= 90)
{
	CheckCharForm();
	sinQuest_levelLog |= QUESTBIT_LEVEL_90_2;
	sinQuest_Level90_2.BackUpCode = sinQuest_Level90_2.CODE;
	sinQuest_Level90_2.CODE = 0;
	EndQuest_Code(sinQuest_Level90_2.BackUpCode);
	sinQuest_Level90_2.CODE = 0;
	sinQuest_Level90_2.State = 4;

	if (cInvenTory.SearchItemCode(sinQT1 | sin13))
	{
		DeleteQuestItem(sinQT1 | sin13);
	}

	ReformCharStatePoint(sinChar, sinQuest_levelLog);
	ReformCharForm();
	cInvenTory.SetItemToChar();
	SetQuestBoard();
}

// Quest nível 100 (Fury of Phantom)
CheckCharForm();
SendQuestCommandToServer(HAQUEST_CODE_FURYOFPHANTOM, 2, chaQuest.iFuryQuestIndex[1], 0);
haElementaryQuestLog |= QUESTBIT_FURYOFPHANTOM;
chaQuest.sHaQuest100LV.State = 100;
chaQuest.sHaQuest100LV.BackUpCode = chaQuest.sHaQuest100LV.CODE;
chaQuest.sHaQuest100LV.CODE = 0;
EndQuest_Code(chaQuest.sHaQuest100LV.BackUpCode);
cMessageBox.ShowMessage(MESSAGE_100LVITEM_OK);
ReformCharForm();
SetQuestBoard();

SaveGameData();
*/

// Log para indicar que a função foi chamada mas está desativada


	CheckCharForm();
	SendQuestCommandToServer(HAQUEST_CODE_FURYOFPHANTOM, 2, chaQuest.iFuryQuestIndex[1], 0);
	haElementaryQuestLog |= QUESTBIT_FURYOFPHANTOM;
	chaQuest.sHaQuest100LV.State = 100;
	chaQuest.sHaQuest100LV.BackUpCode = chaQuest.sHaQuest100LV.CODE;
	chaQuest.sHaQuest100LV.CODE = 0;
	EndQuest_Code(chaQuest.sHaQuest100LV.BackUpCode);
	cMessageBox.ShowMessage(MESSAGE_100LVITEM_OK);
	ReformCharForm();
	SetQuestBoard();

	SaveGameData();
}

void cINTERFACE::KeyDown()
{
	if(hFocusWnd)
	{  
		if(smConfig.DebugMode)
		{
			GetWindowText( hFocusWnd , InputSecretCode , 90 );
			if ( InputSecretCode[0] ) {
				if ( InputSecretCode[0]=='/'){
						memset(sinBuff,0,sizeof(sinBuff));
						wsprintf( sinBuff , "%s" , InputSecretCode );
				}
			}
		}
	}

	if( VRKeyBuff[VK_CONTROL]  ){
		CheckExpPercentControl();

	}
	else
		sinPKWarningExpFlag = 0;
}

int DefaultLength[4] = {94,94,76,86};
float sinOldNowState[4] = {0,0,0,0};  
float sinOldMaxState[4] = {0,0,0,0};

void cINTERFACE::InitState()
{

	float sinTemp;
	float sinMaxState[4] = {(float)sinChar->Life[1],(float)sinChar->Mana[1] ,(float)sinChar->Stamina[1]};  
	float sinNowState[4] = {(float)sinGetLife(),(float)sinGetMana() ,(float)sinGetStamina()};  

	for(int i=0 ;i < 3; i++){
		if(sinMaxState[i])
			sinTemp = (sinNowState[i]/sinMaxState[i])*100; 
		else
			sinTemp = 0;
		sinBmpLength[i] = (int)((DefaultLength[i]*(sinTemp/100)));
		sinOldNowState[i] = sinNowState[i];

	}

	if ( sinChar->Level<79 ) {	
		sinMaxState[3] = (float)(ExpLevelTable[sinChar->Level] - ExpLevelTable[sinChar->Level-1]);
		sinNowState[3] = (float)((GetXorExp64( sinChar))- ExpLevelTable[sinChar->Level-1]);
	}
	else {
		sinMaxState[3] = (float)((ExpLevelTable[sinChar->Level] - ExpLevelTable[sinChar->Level-1])/1000000);
		sinNowState[3] = (float)(((GetXorExp64( sinChar))- ExpLevelTable[sinChar->Level-1])/1000000);
	}

	InitStateFlag = 1;

}

void cINTERFACE::CheckingState()
{	
	float	sinTemp;
	float sinMaxState[4] = {(float)(sinChar->Life[1]),(float)sinChar->Mana[1] ,(float)sinChar->Stamina[1]};
	float sinNowState[4] = {(float)sinGetLife(),(float)sinGetMana() ,(float)sinGetStamina()};

	if ( sinChar->Level<79 ) {	
		sinMaxState[3] = (float)(ExpLevelTable[sinChar->Level] - ExpLevelTable[sinChar->Level-1]);
		sinNowState[3] = (float)((GetXorExp64( sinChar))- ExpLevelTable[sinChar->Level-1]);
	}
	else {
		sinMaxState[3] = (float)((ExpLevelTable[sinChar->Level] - ExpLevelTable[sinChar->Level-1])/1000000);
		sinNowState[3] = (float)(((GetXorExp64( sinChar))- ExpLevelTable[sinChar->Level-1])/1000000);
	}

	for(int i = 0 ; i < 4 ; i++)
	{
		if(sinOldNowState[i] != sinNowState[i] || sinOldNowState[i] != sinMaxState[i])
		{
			if(sinOldNowState[i] != sinNowState[i])
			{
				sinTemp = ((sinNowState[i])/sinMaxState[i])*100; 
				sinBmpLength[i] = (int)((DefaultLength[i]*(sinTemp/100)));
				if(sinBmpLength[i] >DefaultLength[i])sinBmpLength[i] = DefaultLength[i];
				sinOldNowState[i] = sinNowState[i];

			}
	
		}
	}	
}

void cINTERFACE::ShowParaState()
{

	InfoMessageBoxPos.x = 0;
	InfoMessageBoxPos.y = 0;

	szInfoMsgBuff5[0] = 0;
	lstrcpy(szInfoMsgBuff5,"");

	if(pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594)
	{
		if(AddVirtualLife[1]){
			AddVirtualLife[0] = (int)((float)sinGetLife() * ((float)sinVirtualLifePercent / 100.f));
		}
			cHelpPet.PetMessage("*Bar_Life",0);
			wsprintf(szInfoMsgBuff5,sinStateName[0],(int)sinGetLife()+AddVirtualLife[0],(int)sinChar->Life[1]+AddVirtualLife[1]);
			InfoMessageBoxPos.x = 343;   
			InfoMessageBoxPos.y = 500;

	}
	
	if(pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595){//±â·Â
		if(AddVirtualMana[1]){
			AddVirtualMana[0] = (int)((float)sinGetMana() * ((float)sinVirtualManaPercent / 100.f));
		}
		wsprintf(szInfoMsgBuff5,sinStateName[1],(int)sinGetMana(),(int)sinChar->Mana[1]);
		cHelpPet.PetMessage("*Bar_Mana",0);
		InfoMessageBoxPos.x = 490;
		InfoMessageBoxPos.y = 498;

	}
	if(pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595)
	{
		if(AddVirtualStamina[1]){
			AddVirtualStamina[0] = (int)((float)sinGetStamina() * ((float)sinVirtualStaminaPercent / 100.f));
		}
		cHelpPet.PetMessage("*Bar_Stamina",0);
		wsprintf(szInfoMsgBuff5,sinStateName[2],(int)sinGetStamina(),(int)sinChar->Stamina[1]);
		InfoMessageBoxPos.x = 320;
		InfoMessageBoxPos.y = 513;

	}	

	if(pCursorPos.x > 483 && pCursorPos.x < 483+10 && pCursorPos.y > 513 && pCursorPos.y < 595){
		cHelpPet.PetMessage("*Bar_Exp",0);

	}	
	if(pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 540 && pCursorPos.y < 594){
		cHelpPet.PetMessage("*Exp_Num",0);
	}
}

void cINTERFACE::DrawInterText()
{
	HDC hdc = NULL;

	SelectObject( hdc, sinFont);
	SetFontTextColor( RGB(255,255,255) );

	if(InfoMessageBoxPos.x != 0 || InfoMessageBoxPos.y != 0)
		dsTextLineOut(hdc,InfoMessageBoxPos.x,InfoMessageBoxPos.y , szInfoMsgBuff5,lstrlen(szInfoMsgBuff5));

	if(ShowExpPercentFlag)
	{  
		SetFontTextColor( RGB(202,254,251) );
		dsDrawOffsetArray = dsARRAY_BOTTOM;
		dsTextLineOut(511, 551, szInfoMsgBuff6, lstrlen(szInfoMsgBuff6));
		dsDrawOffsetArray = dsARRAY_TOP;
	}

	SetFontTextColor( RGB(255,255,255) );
	if(SkillNpcFlag){
		if(szSkillMasterMsg[0]){
			dsTextLineOut(hdc,SkillMasterTextXY.x,SkillMasterTextXY.y+2 , szSkillMasterMsg,lstrlen(szSkillMasterMsg));
		}
		if(szReStartMsg2[0]){
			dsTextLineOut(hdc,SkillMasterTextXY.x,SkillMasterTextXY.y+18 , szSkillMasterMsg2,lstrlen(szSkillMasterMsg2));
		}

	}
}

void cINTERFACE::CheckAllBox(int ButtonFlag)
{

	int i = 0;
	for(i = 0 ; i < SIN_MAX_HELP_NUMBER; i++){        
		if(sSinHelp[i].KindFlag){
			if(( ButtonFlag ==SIN_CRAFTITEM || ButtonFlag ==SIN_AGING || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE ))return;
		}
		if(sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL ){
			if ( cTrade.OpenFlag ) 
			{
					SendRequestTrade( cTrade.TradeCharCode , 3 );
					cTrade.CancelTradeItem();
			}
			if(( ButtonFlag == SIN_MYSHOP || ButtonFlag == SIN_TRADE ))return;		
		}
	}
	
	if(cWareHouse.OpenFlag || Caravana::GetInstance()->OpenFlag){
		if(ButtonFlag == SIN_TRADE ||ButtonFlag == SIN_SHOP || 
			ButtonFlag == SIN_CRAFTITEM || ButtonFlag == SIN_AGING ||ButtonFlag == SIN_MYSHOP
			|| ButtonFlag == SIN_CHARSHOP || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE )return;
		
	}
	if(MyShopSendButton || cMyShop.OpenFlag || cCharShop.OpenFlag){
		if(ButtonFlag == SIN_TRADE ||ButtonFlag == SIN_SHOP || ButtonFlag == SIN_WAREHOUSE ||
			ButtonFlag == SIN_CRAFTITEM || ButtonFlag == SIN_AGING  ||
			ButtonFlag == SIN_CHARSHOP || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE || ButtonFlag == SIN_CARAVANA)return;

	}
	if(cShop.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || cTrade.OpenFlag ||
		cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag ){
			if(ButtonFlag == SIN_MYSHOP || ButtonFlag == SIN_CHARSHOP)return;

		}

	if(cShop.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || cTrade.OpenFlag ||
		cMyShop.OpenFlag || cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag ){
			if(ButtonFlag == SIN_CHARSHOP)return;

		}
	
	switch(ButtonFlag){
	case SIN_CHARSTATUS: //Ä³¸¯ÅÍ ½ºÅ×ÀÌÅÍ½º 	
		if(cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_CLOSE;
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0; //½Ã½ºÅÛ Ã¢ ´Ý±â 
		
	break;
	case SIN_SKILL: //½ºÅ³Ã¢ 
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0; //½Ã½ºÅÛ Ã¢ ´Ý±â 
		
		break;
	case SIN_INVENTORY: //ÀÎº¥Åä¸® 
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0; //½Ã½ºÅÛ Ã¢ ´Ý±â 

		break;

	case SIN_TRADE: //Æ®·¹ÀÌµå 
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
		if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE; //»óÁ¡À» ´Ý¾ÆÁØ´Ù 
		if(cWareHouse.OpenFlag)cWareHouse.OpenFlag = SIN_CLOSE; //»óÁ¡À» ´Ý¾ÆÁØ´Ù 
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN; //ÀÎº¥Åä¸®°¡ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		if (Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_CLOSE;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}
		// pluto Á¦·Ã
		if( SmeltingItem.OpenFlag )
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}
		// pluto Á¦ÀÛ
		if( ManufactureItem.m_OpenFlag )
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		cTrade.ReFormTradeItem();	//Æ®·¹ÀÌµå ¾ÆÀÌÅÛ Ã¼Å©¼¶ ÃÊ±âÈ­ 
		cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù

	break;

	case SIN_SHOP: //»óÁ¡ 
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
		if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE; 
		if(cWareHouse.OpenFlag)cWareHouse.OpenFlag = SIN_CLOSE; 
		if (Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_CLOSE;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		// pluto Á¦·Ã
		if( SmeltingItem.OpenFlag )
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}
		// pluto Á¦ÀÛ
		if( ManufactureItem.m_OpenFlag )
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN; //ÀÎº¥Åä¸®°¡ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
		if(!cShop.OpenFlag) cShop.OpenFlag = SIN_OPEN; //»óÁ¡ÀÌ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 
		cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
				
	break;

	case SIN_SYSTEM: //½Ã½ºÅÛ 
		if(cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_CLOSE;
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;

	break;
	case SIN_ALL_CLOSE:
		if(cTrade.OpenFlag)break;
		if(cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_CLOSE;
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;
		// Àåº° - Á¦·ÃÃ¢, Á¦ÀÛÃ¢ Á¾·á
		// pluto Á¦·Ã
	//	if( SmeltingItem.OpenFlag )
	//	{
	//		SmeltingItem.OpenFlag = SIN_CLOSE;
	//	}
		// pluto Á¦ÀÛ
	//	if( ManufactureItem.m_OpenFlag )
	//	{
	//		ManufactureItem.m_OpenFlag = SIN_CLOSE;
	//	}
		ExitButtonClick = 0; 
	break;

	case SIN_WAREHOUSE: //Ã¢°í 
		//¹Ì´Ï¸ÊÀÌ¶°ÀÖÀ»°Ü¿ì¿¡´Â Ã¢°í°¡ ¿­¸®Áö¾Ê´Â´Ù
		if(g_IsDxProjectZoomIn)break;

		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE; 
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE; 
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if (Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_CLOSE;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN; //ÀÎº¥Åä¸®°¡ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
		if(!cWareHouse.OpenFlag) cWareHouse.OpenFlag = SIN_OPEN; //»óÁ¡ÀÌ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
		// pluto Á¦·Ã
		if( SmeltingItem.OpenFlag )
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}
		// pluto Á¦ÀÛ
		if( ManufactureItem.m_OpenFlag )
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		cWareHouse.ReFormWareHouse();
		cWareHouse.CheckCopyItem(); //º¹»çµÈ ¾ÆÀÌÅÛÀÌ ÀÖ´ÂÁö¸¦ Ã¼Å©ÇÑ´Ù 
		cWareHouse.DeleteCopyItem(); //Ã¢°íÀÇ º¹»ç¾ÆÀÌÅÛÀ» °Ë»öÇØ¼­ ¾ø¾ÖÁØ´Ù 
		cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
	break;

	case SIN_CARAVANA:
		if (g_IsDxProjectZoomIn)break;

		if (cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
		if (CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if (!cWareHouse.OpenFlag) cWareHouse.OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN; 		 

		if (!Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_OPEN;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}

		if (SmeltingItem.OpenFlag)
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}

		if (ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		Caravana::GetInstance()->ReFormCaravan();
		Caravana::GetInstance()->CheckCopyItem();
		Caravana::GetInstance()->DeleteCopyItem();
		cInvenTory.ChangeSpecialItem(2);
		break;

	case SIN_CRAFTITEM: //¾ÆÀÌÅÛ Á¶ÇÕ 
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE; 
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE; 
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if(cWareHouse.OpenFlag) cWareHouse.OpenFlag = SIN_CLOSE;


		if (Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_CLOSE;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}

		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN; //ÀÎº¥Åä¸®°¡ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
		if(!cCraftItem.OpenFlag) cCraftItem.OpenFlag = SIN_OPEN; //»óÁ¡ÀÌ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
		// pluto Á¦·Ã
		if( SmeltingItem.OpenFlag )
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}
		// pluto Á¦ÀÛ
		if( ManufactureItem.m_OpenFlag )
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		cCraftItem.ReFormCraftItem(); //¹Í½ºÃÄ ¾ÆÀÌÅÛÀ» È®ÀÎÇØÁØ´Ù 
		cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù

		
	break;
	case SIN_AGING:	//¿¡ÀÌÂ¡ 
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE; 
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE; 
		if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if (Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_CLOSE;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}
		if(cWareHouse.OpenFlag) cWareHouse.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN; //ÀÎº¥Åä¸®°¡ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
		if(!cAging.OpenFlag)cAging.OpenFlag = SIN_OPEN;
		// pluto Á¦·Ã
		if( SmeltingItem.OpenFlag )
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}
		// pluto Á¦ÀÛ
		if( ManufactureItem.m_OpenFlag )
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
//		cCraftItem.ReFormCraftItem(); //¹Í½ºÃÄ ¾ÆÀÌÅÛÀ» È®ÀÎÇØÁØ´Ù 

		break;
	case SIN_MIXTURE_RESET:	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ »©°ï ÀüºÎ ´Ý´Â´Ù.
		if(cTrade.OpenFlag)			cTrade.OpenFlag			= SIN_CLOSE;	// Æ®·¹ÀÌµå Ã¢ ´Ý±â
		if(cShop.OpenFlag)			cShop.OpenFlag			= SIN_CLOSE;	// »óÁ¡ Ã¢ ´Ý±â
		if(CSKILL->OpenFlag)			CSKILL->OpenFlag			= SIN_CLOSE;	// ½ºÅ³ Ã¢ ´Ý±â
		if(cCraftItem.OpenFlag)		cCraftItem.OpenFlag		= SIN_CLOSE;	// Á¶ÇÕ Ã¢ ´Ý±â
		if(cWareHouse.OpenFlag)		cWareHouse.OpenFlag		= SIN_CLOSE;	// Ã¢°í ´Ý±â
		if(cCharStatus.OpenFlag)	cCharStatus.OpenFlag	= SIN_CLOSE;	// Ä³¸¯Á¤º¸ Ã¢ ´Ý±â
		if (Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_CLOSE;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}
		if(cAging.OpenFlag)			cAging.OpenFlag			= SIN_CLOSE;	// ¿¡ÀÌÂ¡ Ã¢ ´Ý±â
		if( SmeltingItem.OpenFlag )	SmeltingItem.OpenFlag	= SIN_CLOSE;	// Á¦·Ã Ã¢ ´Ý±â
		if( ManufactureItem.m_OpenFlag )	ManufactureItem.m_OpenFlag = SIN_CLOSE;	// Á¦ÀÛ Ã¢ ´Ý±â

		if(!cInvenTory.OpenFlag)	cInvenTory.OpenFlag		= SIN_OPEN;		// ÀÎº¥Åä¸®°¡ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 	
		if(!cMixtureReset.OpenFlag)	// ¹Í½ºÃÄ ¸®¼Â Ã¢ÀÌ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù.
		{
			cMixtureReset.OpenFlag = SIN_OPEN;
		}
		cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
		break;
	case SIN_SMELTING:		// pluto Á¦·Ã
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
		if( cTrade.OpenFlag )
		{
			cTrade.OpenFlag = SIN_CLOSE;
		}

		if( cShop.OpenFlag )
		{
			cShop.OpenFlag = SIN_CLOSE;
		}

		if( CSKILL->OpenFlag )
		{
			CSKILL->OpenFlag = SIN_CLOSE;
		}

		if( cCraftItem.OpenFlag )
		{
			cCraftItem.OpenFlag = SIN_CLOSE;
		}

		if( cWareHouse.OpenFlag )
		{
			cWareHouse.OpenFlag = SIN_CLOSE;
		}

		if (Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_CLOSE;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}

		if( cCharStatus.OpenFlag )
		{
			cCharStatus.OpenFlag = SIN_CLOSE;
		}

		if( cAging.OpenFlag )
		{
			cAging.OpenFlag = SIN_CLOSE;
		}
		// pluto Á¦ÀÛ
		if( ManufactureItem.m_OpenFlag )
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		if( !cInvenTory.OpenFlag )
		{
			cInvenTory.OpenFlag = SIN_OPEN;
		}
		if( !SmeltingItem.OpenFlag )
		{
			SmeltingItem.OpenFlag = SIN_OPEN;
		}
		cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
	break;
	case SIN_MANUFACTURE:		// pluto Á¦ÀÛ
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
		if( cTrade.OpenFlag )
		{
			cTrade.OpenFlag = SIN_CLOSE;
		}

		if( cShop.OpenFlag )
		{
			cShop.OpenFlag = SIN_CLOSE;
		}

		if( CSKILL->OpenFlag )
		{
			CSKILL->OpenFlag = SIN_CLOSE;
		}

		if( cCraftItem.OpenFlag )
		{
			cCraftItem.OpenFlag = SIN_CLOSE;
		}

		if( cWareHouse.OpenFlag )
		{
			cWareHouse.OpenFlag = SIN_CLOSE;
		}

		if (Caravana::GetInstance()->OpenFlag)
		{
			Caravana::GetInstance()->OpenFlag = SIN_CLOSE;
			Caravana::GetInstance()->ChangeName = SIN_CLOSE;
		}

		if( cCharStatus.OpenFlag )
		{
			cCharStatus.OpenFlag = SIN_CLOSE;
		}

		if( cAging.OpenFlag )
		{
			cAging.OpenFlag = SIN_CLOSE;
		}
		if( SmeltingItem.OpenFlag )
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}
		if( !cInvenTory.OpenFlag )
		{
			cInvenTory.OpenFlag = SIN_OPEN;
		}
		if( !ManufactureItem.m_OpenFlag )
		{
			ManufactureItem.m_OpenFlag = SIN_OPEN;
			// pluto Á¦ÀÛ ¾ÆÀÌÅÛ °¡°Ý, ¹«°Ô Á¤º¸ °¡Á® ¿Ã·Á°í
			if( !g_Manufacture_ItemInfo[0].ItemCode ) // Ã³À½ Á¦ÀÛÃ¢ ¿­¶§¸¸ º¸³½´Ù
			{
				smTRANS_COMMAND	TransCommand;
				TransCommand.code =	smTRANSCODE_MANUFACTURE_WEIGHT_PRICE;
				TransCommand.size = sizeof(smTRANS_COMMAND);
				TransCommand.WParam = 0;
				TransCommand.LParam = 0;
				TransCommand.SParam = 0;
				smWINSOCK* lpsmSock;
				lpsmSock = GetAreaServerSock();		//º¸³¾ ¼­¹ö±¸ÇÏ±â
				if( lpsmSock )
				{
					lpsmSock->Send( (char*)&TransCommand, TransCommand.size, TRUE );
				}
			}
		}
		cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
	break;
	case SIN_MYSHOP:
		if(lpCurPlayer->OnStageField>=0 && StageField[ lpCurPlayer->OnStageField ]->State == FIELD_STATE_VILLAGE ){
			if(cMixtureReset.OpenFlag)cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
			if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE; 
			if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE; 
			if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
			if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
			if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
			if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
			// pluto Á¦·Ã
			if( SmeltingItem.OpenFlag )
			{
				SmeltingItem.OpenFlag = SIN_CLOSE;
			}
			// pluto Á¦ÀÛ
			if( ManufactureItem.m_OpenFlag )
			{
				ManufactureItem.m_OpenFlag = SIN_CLOSE;
			}
			if(cCharShop.OpenFlag){
				cCharShop.OpenFlag = 0; //»óÁ¡À» ´Ý´Â´Ù
				memset(cCharShop.CharShopItem,0,sizeof(sITEM)*30); //¾ÆÀÌÅÛÀ» Áö¿öÁØ´Ù
			}
			if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN; //ÀÎº¥Åä¸®°¡ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
			if(!cMyShop.OpenFlag) cMyShop.OpenFlag = SIN_OPEN; //»óÁ¡ÀÌ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 
			cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
		}
		
	break;
	case SIN_CHARSHOP:
		if(lpCurPlayer->OnStageField>=0 && StageField[ lpCurPlayer->OnStageField ]->State == FIELD_STATE_VILLAGE){
			if(cMixtureReset.OpenFlag)cMixtureReset.OpenFlag = SIN_CLOSE;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ Ãß°¡
			if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE; 
			if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE; 
			if(CSKILL->OpenFlag) CSKILL->OpenFlag = SIN_CLOSE;
			if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
			if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
			if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
			// pluto Á¦·Ã
			if( SmeltingItem.OpenFlag )
			{
				SmeltingItem.OpenFlag = SIN_CLOSE;
			}
			// pluto Á¦ÀÛ
			if( ManufactureItem.m_OpenFlag )
			{
				ManufactureItem.m_OpenFlag = SIN_CLOSE;
			}
			if(cMyShop.OpenFlag){
				cMyShop.OpenFlag = SIN_CLOSE;
				cMyShop.OpenFlag = 0;
				memset(cMyShop.MyShopItem,0,sizeof(sITEM)*30); //¾ÆÀÌÅÛÀ» Áö¿öÁØ´Ù
				memset(MyShopItemIndex,0,sizeof(int)*100);
				MyShopSendButton = 0; //µî·Ï¹öÆ° ÃÊ±âÈ­
			}
			if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN; //ÀÎº¥Åä¸®°¡ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
			if(!cCharShop.OpenFlag) cCharShop.OpenFlag = SIN_OPEN; //»óÁ¡ÀÌ ´ÝÇôÀÖÀ¸¸é ¿­¾îÁØ´Ù 		 
			cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
		}
	break;

	}
}

int cINTERFACE::DrawClockArrow( int x, int y, int Angle )
{
	float fx[4],fy[4];
	int sinY,cosY;
	int dx[4],dy[4];
	int cnt;

	int sinTimeAngle;
	float TempTime , TempTime2 , TempTime3;

	TempTime2 = (float)dwGameHour*60;
	TempTime3 = (float)(TempTime2+dwGameMin)/1440;
	
	TempTime = (float)TempTime3*100;
	
	sinTimeAngle = (int)(2190+(780*(TempTime/100)));

	sinY = GetSin[ sinTimeAngle&ANGCLIP ];
	cosY = GetCos[ sinTimeAngle&ANGCLIP ];

	dx[0] = 8; dy[0] = 48;
	dx[1] = 8; dy[1] = 32;
	dx[2] =  -8; dy[2] = 48;
	dx[3] =  -8; dy[3] = 32;

	for( cnt=0;cnt<4;cnt++) {
		fx[cnt] = (float) (( dy[cnt]*sinY + dx[cnt]*cosY )>>8);
		fy[cnt] = (float) (( dy[cnt]*cosY - dx[cnt]*sinY )>>8);
		fx[cnt] /= 256;
		fy[cnt] /= 256;
		fx[cnt] += (float)x;
		fy[cnt] += (float)y;
	}


	psDrawTexImage2( smMaterial[cInterFace.MatClock].smTexture[0] , fx , fy, 0,0,1,1,255,0 );

	return TRUE;
}

int cINTERFACE::DrawCompass(int x , int y ,int Angle)
{

	float fx[4],fy[4];
	int sinY,cosY;
	int dx[4],dy[4];
	int cnt;

	sinY = GetSin[ Angle&ANGCLIP ];
	cosY = GetCos[ (Angle+ANGLE_180)&ANGCLIP ];

	dx[0] = 8; dy[0] = 13+16;
	dx[1] = 8; dy[1] = 13;
	dx[2] =  -8; dy[2] = 13+16;
	dx[3] =  -8; dy[3] = 13;

	for( cnt=0;cnt<4;cnt++) {
		fx[cnt] = (float) (( dy[cnt]*sinY + dx[cnt]*cosY )>>8);
		fy[cnt] = (float) (( dy[cnt]*cosY - dx[cnt]*sinY )>>8);
		fx[cnt] /= 256;
		fy[cnt] /= 256;
		fx[cnt] += (float)x;
		fy[cnt] += (float)y;
	}


	psDrawTexImage2( smMaterial[cInterFace.MatComPass].smTexture[0] , fx , fy, 0,0,1,1,255,0 );


	return TRUE;
}

int cINTERFACE::CheckExpPercentControl()
{
	return TRUE;
}


int cINTERFACE::GetWordTimeDisplay()
{
	float TempfHour = (float)dwGameHour;
	//float TempfHour = (float)TestTime4;
	if(TempfHour >= 23 || TempfHour < 4)
		DayOrNightFlag = 2;
	else 
		DayOrNightFlag = 1;

	if(DayOrNightFlag == 1 ){
		sinGageTime2 = (int)(50.0f*((TempfHour-4.0f)/19.0f));
	}
	else{
		sinGageTime2 = (int)(50.0f*((TempfHour+1)/5.0f));
	}
	if(sinGageTime2 >  50)sinGageTime2 = 50;
	
	return TRUE;
}

// % do level aqui
void cINTERFACE::ShowExpPercent()
{
	ShowExpPercentFlag = 1; 

	INT64 ExpPercent  = 0;
	int ExpPercentSpot = 0;
	INT64 ExpSize = 0;
	INT64 ExpNowSize  = 0;

	szInfoMsgBuff6[0] = 0;

	if(sinChar->Level > 150 ){ 
		ExpSize = ((GetNextExp( sinChar->Level ) - GetNextExp( sinChar->Level-1 ))/1000000);
		ExpNowSize = (cCharStatus.sinGetNowExp()-(GetNextExp( sinChar->Level-1 )/1000000));
		ExpPercent = (100000.0f/(float)ExpSize * (float)ExpNowSize); 
		ExpPercentSpot = (ExpPercent%1000);
		ExpPercent = ExpPercent/1000; 


		if(ExpPercent >=100){
			ExpPercent = 99;
			ExpPercentSpot =999;
		}

		if(ExpPercentSpot < 10 ){
			wsprintf(szInfoMsgBuff6,"%I64d.00%d%s",ExpPercent,ExpPercentSpot,"%  ");
		}
		else if ( ExpPercentSpot >= 10 &&  ExpPercentSpot < 100 ){
			wsprintf(szInfoMsgBuff6,"%I64d.0%d%s",ExpPercent,ExpPercentSpot,"%  ");
		}
		else
			wsprintf(szInfoMsgBuff6,"%I64d.%d%s",ExpPercent,ExpPercentSpot,"%  ");


	}
	else{ 
		ExpSize = GetNextExp( sinChar->Level ) - GetNextExp( sinChar->Level-1 );  
		ExpNowSize = cCharStatus.sinGetNowExp()-GetNextExp( sinChar->Level-1 );
		ExpPercent = (100000.0f/(float)ExpSize * (float)ExpNowSize); 
		ExpPercentSpot = (ExpPercent%1000);
		ExpPercent = ExpPercent/1000;

		cHelpPet.PetExp = ExpPercent;

		if(ExpPercentSpot < 10 ){
			wsprintf(szInfoMsgBuff6,"%I64d.00%d%s",ExpPercent,ExpPercentSpot,"%  ");
		}
		else if ( ExpPercentSpot >= 10 &&  ExpPercentSpot < 100 ){
			wsprintf(szInfoMsgBuff6,"%I64d.0%d%s",ExpPercent,ExpPercentSpot,"%  ");
		}
		else
			wsprintf(szInfoMsgBuff6,"%I64d.%d%s",ExpPercent,ExpPercentSpot,"%  ");

	}

}

int cINTERFACE::SetStringEffect(int Index)
{
	smTRANS_COMMAND smTransCommand = {};

	smTransCommand.code = SMTRANSCODE_DISPLAY_DEF;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = lpCurPlayer->dwObjectSerial;
	smTransCommand.LParam = Index;

	if (smWsockServer)
		smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	//if(!HA_EffectIndex[Index]){
	//		HA_EffectIndex[Index]=CreateTextureMaterial(HaEffectFilePath[Index], 0, 0, 0,0, SMMAT_BLEND_ALPHA); 
	//		ReadTextures();
	//}
	//for(int i=0;i<MAX_HAEFFECTNUM;i++){
	//	if(!HaEffect[i].Flag){
	//		HaEffect[i].Flag = 1;
	//		HaEffect[i].Time = 0;
	//		HaEffect[i].Mat  = HA_EffectIndex[Index];
	//		HaEffect[i].Posi.x = 354;
	//		HaEffect[i].Posi.y = 488;
	//		HaEffect[i].Size.x = 128;
	//		HaEffect[i].Size.y = 64;
	//		return true;
	//	}
	//}
	return false;
	
}
