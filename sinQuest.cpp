/*----------------------------------------------------------------------------*
*	ÆÄÀÏ¸í :  sinHelp.cpp	
*	ÇÏ´ÂÀÏ :  ½Å¹Ù¶÷ µµ¿ì¹Ì
*	ÀÛ¼ºÀÏ :  ÃÖÁ¾¾÷µ¥ÀÌÆ® 2002³â 7¿ù
*	Àû¼ºÀÚ :  ¹Ú»ó¿­ 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "..\\field.h"

extern bool bcanadd;
/*----------------------------------------------------------------------------*
*							Àü¿ª º¯¼ö 						
*-----------------------------------------------------------------------------*/	
sQUEST_CHANGEJOB	sinQuest_ChangeJob;	//Äù½ºÆ®ÀÇ Àü¹ÝÀûÀÎ ³»¿ëÀ» ´Ù·é´Ù (ÅÛ½ºÅ©·Ð)
sQUEST_CHANGEJOB	sinQuest_ChangeJob2;//Äù½ºÆ®ÀÇ Àü¹ÝÀûÀÎ ³»¿ëÀ» ´Ù·é´Ù (¸ð¶óÀÌ¿Â)
sQUEST_CHANGEJOB3   sinQuest_ChangeJob3;//ÅÛ½ºÅ©·Ð ¸ð¶óÀÌ¿Â 3Â÷ ÀüÁ÷Äù½ºÆ® 
sQUEST_CHANGEJOB3   sinQuest_ChangeJob4;//ÅÛ½ºÅ©·Ð ¸ð¶óÀÌ¿Â 3Â÷ ÀüÁ÷Äù½ºÆ® 

//·¹º§Äù½ºÆ®
sQUEST_CHANGEJOB3   sinQuest_Level30;
sQUEST_CHANGEJOB3   sinQuest_Level55;
sQUEST_CHANGEJOB3   sinQuest_Level55_2;
sQUEST_CHANGEJOB3   sinQuest_Level70;
sQUEST_CHANGEJOB3   sinQuest_Level80;
sQUEST_CHANGEJOB3   sinQuest_Level85;
sQUEST_CHANGEJOB3   sinQuest_Level90;

sQUEST_CHANGEJOB3   sinQuest_Level80_2; //»õ·ÎÃß°¡µÈ ½ºÅÝ +7Äù½ºÆ®
sQUEST_CHANGEJOB3   sinQuest_Level90_2; //»õ·ÎÃß°¡µÈ ½ºÅÝ +10Äù½ºÆ®

sQUEST_CHANGEJOB3	sinQuest_Daily;

DWORD sinQuest_levelLog = 0; //Äù½ºÆ®¸¦ ¼öÇàÇß³ª ·Î±×

sITEM TempQuestItem;

int sinChangeJobButtonShow  = 0; //ÅÛ½ºÅ©·Ð Àü¾÷ 2Â÷Àü¾÷
int sinChangeJobButtonShow2 = 0; //¸ð¶óÀÌ¿Â Àü¾÷ 2Â÷Àü¾÷
int sinChangeJobButtonShow3 = 0; //ÅÛ½ºÅ©·Ð ¸ð¶óÀÌ¿Â 3Â÷Àü¾÷
int sinChangeJobButtonShow4 = 0; //ÅÛ½ºÅ©·Ð ¸ð¶óÀÌ¿Â 4Â÷Àü¾÷

int CheckQuestComplete = 0;		 //Àü¾÷ÀÇ ÁøÇà»çÇ×
int CheckQuestButtonShow1 = 0;
int CheckQuestButtonShow2 = 0;
int CheckQuestButtonShow3 = 0;

POINT QuestMessageBoxPosi2 = {50,45};
POINT QuestMessageBoxSize2 = {9,10};

//Äù½ºÆ® ÆÄÀÏÀÇ °æ·Î 
char *QuestFilePath[] ={
	"image\\Sinimage\\Quest\\ChangeJob1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M3.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D3.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_Success.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M0.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D0.sin",
	"image\\Sinimage\\Quest\\ChangeJob1.sin",
};

char *QuestFilePath3[] ={
	"image\\Sinimage\\Quest\\ChangeJob3_0.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_1.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_2.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_3.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_4.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_5.sin",
};


char *WingQuestFilePath_a[] = {
	"image\\Sinimage\\Quest\\M_Wing_a.sin",
	"image\\Sinimage\\Quest\\S_Wing_a.sin",
	"image\\Sinimage\\Quest\\G_Wing_a.sin",
	"image\\Sinimage\\Quest\\D_Wing_a.sin",
	"image\\Sinimage\\Quest\\K_wing_a.sin", //ÄÉÀÌ¾Æ½ºÀ®
	"image\\Sinimage\\Quest\\E_wing_a.sin", //ÀÍ½ºÆ®¸²À® ·Î½ºÆ® ¾ÆÀÏ·£µå (¼º±ÙÃß°¡)
	"image\\Sinimage\\Quest\\Puzzle.sin",   //¾ê´Â ÆÛÁñ ~~~ °ÇµéÁö ¸¶¼¼¿° -0-

};

char *WingQuestFilePath_b[] = {
	"image\\Sinimage\\Quest\\M_Wing_b.sin",
	"image\\Sinimage\\Quest\\S_Wing_b.sin",
	"image\\Sinimage\\Quest\\G_Wing_b.sin",
	"image\\Sinimage\\Quest\\D_Wing_b.sin",
	"image\\Sinimage\\Quest\\K_wing_b.sin", //ÄÉÀÌ¾Æ½ºÀ®
	"image\\Sinimage\\Quest\\E_wing_b.sin", //ÀÍ½ºÆ®¸²À® ·Î½ºÆ® ¾ÆÀÏ·£µå (¼º±ÙÃß°¡)
	"image\\Sinimage\\Quest\\Wing_End.sin",

};

char *WarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\Default.sin",
	"image\\Sinimage\\WarpGateDoc\\Ricarten.sin",
	"image\\Sinimage\\WarpGateDoc\\Pilai.sin",
	"image\\Sinimage\\WarpGateDoc\\Forest2.sin",
	"image\\Sinimage\\WarpGateDoc\\Forest3.sin",
	"image\\Sinimage\\WarpGateDoc\\Ruinen.sin",
	"image\\Sinimage\\WarpGateDoc\\Nevisco.sin",
	"image\\Sinimage\\WarpGateDoc\\Desert4.sin",
	"image\\Sinimage\\WarpGateDoc\\yura.sin",
	"image\\Sinimage\\WarpGateDoc\\chaoticpost.sin",	//·Î½ºÆ® ¾ÆÀÏ·£µå (¼º±ÙÃß°¡)

};
char *HaWarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\B_Castle.sin"
};

char *WarningInitPoint[] = {
	"image\\Sinimage\\Help\\WarnigWeight.sin",

};
char *BabelEventDoc = "image\\Sinimage\\Quest\\BaBelEvent.sin";
char *NineTailFoxDoc = "image\\Sinimage\\Quest\\NineTailFoxEvent.sin";
char *StarDustDoc = "image\\Sinimage\\Quest\\StarDust.sin";		//Å©¸®½º¸¶½º¼öÁ¤
char *CristalEventDoc= "image\\Sinimage\\Quest\\CristalEvent.sin";//ÀÏ°ö°¡Áö Å©¸®½ºÅ»ÀÇ º¸Àº

//¹ÚÀç¿ø - ¼ö¹Ú ¸ð¾Æ¿À±â
char *WatermelonDoc = "image\\Sinimage\\Quest\\WatermelonEvent.sin";//¼ö¹Ú ¸ð¾Æ¿À±â ÀÌº¥Æ®
//¹ÚÀç¿ø - È£¹Ú ¸ð¾Æ¿À±â
char *PumpkinDoc = "image\\Sinimage\\Quest\\PumpkinEvent.sin";//È£¹Ú ¸ð¾Æ¿À±â ÀÌº¥Æ®
//¹ÚÀç¿ø - º°Á¶°¢ ¸ð¾Æ¿À±â
char *StarDoc = "image\\Sinimage\\Quest\\StarEvent.sin";//¹ÚÀç¿ø - ¹ãÇÏ´ÃÀÇ ¼Ò¿ø ÀÌº¥Æ®
//Àåº° - ¹ß·»Å¸ÀÎ ÃÊÄÝ¸´ ¸ð¾Æ¿À±â
char *ValentineDoc = "image\\Sinimage\\Quest\\ChocolateEvent.sin"; //¹ß·»Å¸ÀÎ ÃÊÄÝ¸´ ¸ð¾Æ¿À±â ÀÌº¥Æ®
// ¹ÚÀç¿ø - ¾ËÆÄºª Á¶ÇÕ ÀÌº¥Æ®
char *PristonAlphabetDoc = "image\\Sinimage\\Quest\\Priston.sin"; // ¹ÚÀç¿ø - ¾ËÆÄºª Á¶ÇÕ ÀÌº¥Æ®
// Àåº° - Äµµðµ¥ÀÌÁî
char *CandydaysDoc = "image\\Sinimage\\Quest\\CandydaysEvent.sin"; // Äµµð ¸ð¾Æ¿À±â ÀÌº¥Æ®
// Àåº° - ¸ÅÁöÄÃ±×¸°
char *MagicalGreenDoc = "image\\Sinimage\\Quest\\MagicalGreenEvent.sin"; 
// Àåº° - Ä«¶óÀÇ ´«¹°
char *TearOfKaraDoc = "image\\Sinimage\\Quest\\KarasTears.sin"; 

// Àåº° - Á¶»ç¿øÀ» Ã£¾Æ¶ó
char *Findinvestigator1_1Doc = "image\\Sinimage\\Quest\\Resercher_Start.sin"; 
char *Findinvestigator1_2Doc = "image\\Sinimage\\Quest\\Resercher_Pass1.sin"; 
char *Findinvestigator1_3Doc = "image\\Sinimage\\Quest\\Resercher_Pass2.sin"; 
char *Findinvestigator2_1Doc = "image\\Sinimage\\Quest\\Kamiyu_Start.sin"; 
char *Findinvestigator2_2Doc = "image\\Sinimage\\Quest\\Kamiyu_Pass.sin"; 
char *Findinvestigator3_1Doc = "image\\Sinimage\\Quest\\Eto_Start.sin"; 
char *Findinvestigator3_2Doc = "image\\Sinimage\\Quest\\Eto_Pass.sin"; 

char *LevelQuest30Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest30start.sin",
	"image\\Sinimage\\Quest\\LevelQuest30Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest30end.sin",
};

char *LevelQuest55Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55start.sin",
	"image\\Sinimage\\Quest\\LevelQuest55Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest55end.sin",

};

char *LevelQuest55_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55-2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest55-2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest55-2end.sin",

};

char *LevelQuest70Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest70start.sin",
	"image\\Sinimage\\Quest\\LevelQuest70Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest70end.sin",

};
char *LevelQuest80Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80start.sin",
	"image\\Sinimage\\Quest\\LevelQuest80Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest80end.sin",

};
char *LevelQuest85Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest85start.sin",
	"image\\Sinimage\\Quest\\LevelQuest85Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest85Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest85end.sin",

};
char *LevelQuest90Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90start.sin",
	"image\\Sinimage\\Quest\\LevelQuest90Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest90end.sin",

};

char *LevelQuest80_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80_2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2start2.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2end.sin",

};

char *LevelQuest90_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90_2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2start2.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2end.sin",

};

char *QuestFilePath4[] ={
	"image\\Sinimage\\Quest\\ChangeJob4_1Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_1Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_2Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_2Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_3Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_3Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_4Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_4End.sin",
};

char *DailyQuestDoc[] = {
	"image\\Sinimage\\Quest\\DailyQuestStart.sin",
	"image\\Sinimage\\Quest\\DailyQuestPath.sin",
	"image\\Sinimage\\Quest\\DailyQuestEnd.sin",
	"image\\Sinimage\\Quest\\DailyQuestWait.sin",
};



// ===========================================
// SISTEMA DE JOB QUESTS (SEM AUTO-COMPLETE)
// ===========================================
int sinCheckChageJob()
{
	// ===========================================
	// SISTEMA ORIGINAL DE QUESTS (ATIVADO)
	// ===========================================

	// JOB QUEST 1 (Nível 20)
	if (CheckQuestButtonShow1 && sinChar->Level >= 20 && sinChar->ChangeJob == 0) {
		if (!sinQuest_ChangeJob.CODE && sinChar->JOB_CODE <= 4)
			sinChangeJobButtonShow = 1;
		if (!sinQuest_ChangeJob2.CODE && sinChar->JOB_CODE > 4 && sinChar->JOB_CODE <= 8) {
			if (!FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_M) &&
				!FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_D) &&
				sinChar->ChangeJob < 1) {
				sinChangeJobButtonShow2 = 1;
			}
		}
	}

	// JOB QUEST 2 (Nível 40)
	if (CheckQuestButtonShow2 && sinChar->Level >= 40 && sinChar->ChangeJob == 1) {
		if (!sinQuest_ChangeJob3.CODE && !FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB3)) {
			sinChangeJobButtonShow3 = 1;

			// Verifica se tem skills suficientes
			int ChangeJobSkillPlus = 0;
			switch (sinChar->ChangeJob) {
			case 0:	ChangeJobSkillPlus = 5;	break;
			case 1:	ChangeJobSkillPlus = 9;	break;
			case 2:	ChangeJobSkillPlus = 13; break;
			case 3: ChangeJobSkillPlus = 17; break;
			}
			for (int i = 1; i < ChangeJobSkillPlus; i++) {
				if (!sinSkill.UseSkill[i].Point)
					sinChangeJobButtonShow3 = 0;
			}
		}
	}

	// JOB QUEST 3 (Nível 60)
	if (CheckQuestButtonShow3 && sinChar->Level >= 60 && sinChar->ChangeJob == 2) {
		if (!sinQuest_ChangeJob4.CODE) {
			sinChangeJobButtonShow4 = 1;

			// Verifica se tem skills suficientes
			int ChangeJobSkillPlus = 0;
			switch (sinChar->ChangeJob) {
			case 0:	ChangeJobSkillPlus = 5;	break;
			case 1:	ChangeJobSkillPlus = 9;	break;
			case 2:	ChangeJobSkillPlus = 13; break;
			case 3: ChangeJobSkillPlus = 17; break;
			}
			for (int i = 1; i < ChangeJobSkillPlus; i++) {
				if (!sinSkill.UseSkill[i].Point)
					sinChangeJobButtonShow4 = 0;
			}
		}
	}

	return TRUE;
}

// ===========================================
// SISTEMA AUTO-COMPLETE (DESATIVADO)
// ===========================================
/*
int sinCheckChageJob_AutoComplete()
{
	if (sinChar->Level >= 20 && sinChar->ChangeJob <= 0) {
		sinChar->ChangeJob = 1;
		ChangeJobFace();
	}

	if (sinChar->Level >= 40 && sinChar->ChangeJob <= 1) {
		sinChar->ChangeJob = 2;
		ChangeJobFace();
	}

	if (sinChar->Level >= 60 && sinChar->ChangeJob <= 2) {
		sinChar->ChangeJob = 3;
		ChangeJobFace();
	}
	return TRUE;
}
*/

/*----------------------------------------------------------------------------*
*					Äù½ºÆ® µ¥ÀÌÅ¸¸¦ ·ÎµåÇÑ´Ù 
*-----------------------------------------------------------------------------*/	
int sinLoadQuest(int CODE ,void *Buff )	//Äù½ºÆ® µ¥ÀÌÅ¸¸¦ ·ÎµåÇÑ´Ù 
{
	//sQUEST_CHANGEJOB Temp;
	if(CODE == SIN_QUEST_CODE_CHANGEJOB){
		memcpy( &sinQuest_ChangeJob , Buff , sizeof(sQUEST_CHANGEJOB) );
	}
	if(CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M || CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D){
		memcpy( &sinQuest_ChangeJob2 , Buff , sizeof(sQUEST_CHANGEJOB) );
	}
	if(CODE == SIN_QUEST_CODE_CHANGEJOB3 ){
		memcpy( &sinQuest_ChangeJob3 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL30 ){
		memcpy(  &sinQuest_Level30 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL55 ){
		memcpy(  &sinQuest_Level55 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL55_2 ){
		memcpy(  &sinQuest_Level55_2 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL70 ){
		memcpy(  &sinQuest_Level70, Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL80 ){
		memcpy(  &sinQuest_Level80 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL85 ){
		memcpy(  &sinQuest_Level85 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL90 ){
		memcpy(  &sinQuest_Level90 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL80_2 ){
		memcpy(  &sinQuest_Level80_2 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_LEVEL90_2 ){
		memcpy(  &sinQuest_Level90_2 , Buff , sizeof(sQUEST_CHANGEJOB3) );
	}
	if(CODE == SIN_QUEST_CODE_CHANGEJOB4 ){
		memcpy( &sinQuest_ChangeJob4 , Buff , sizeof(sQUEST_CHANGEJOB3) );
		if(sinQuest_ChangeJob4.AgingCount){
			if(sinQuest_ChangeJob4.State==3||sinQuest_ChangeJob4.State==1){
				sinSetQuestTimer(&sinQuest_ChangeJob4,sinQuest_ChangeJob4.AgingCount,sinQuest_ChangeJob4.StartLevel);
				lstrcpy(szQuestMonsterName,sinGetMonsterName(sinQuest_ChangeJob4.Kind));
			}

		}
	}
	//½Å±Ô Æ©Åä¸®¾ó Äù½ºÆ®
	if(CODE == HAQUEST_CODE_ELEMENTARY_A){
		memcpy( &chaQuest.sHaQuestElementary[Quest_A], Buff , sizeof(sQUEST_ELEMENTARY) );
	}
	if(CODE == HAQUEST_CODE_ELEMENTARY_B){
		chaQuest.QuestKeyCode = Quest_B;
		memcpy( &chaQuest.sHaQuestElementary[Quest_B], Buff , sizeof(sQUEST_ELEMENTARY) );
		if(chaQuest.sHaQuestElementary[Quest_B].State==100){
			chaQuest.sHaQuestElementary[Quest_B].State=3;
		}		
		if(chaQuest.sHaQuestElementary[Quest_B].State==2 || chaQuest.sHaQuestElementary[Quest_B].State==3){
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuestElementary[Quest_B]);
			if(sinChar->JOB_CODE < 5)
				lstrcpy(chaQuest.szQuestMonsterName,haQuestMonsterName[0]);
			else
				lstrcpy(chaQuest.szQuestMonsterName,haQuestMonsterName[1]);
		}
	}
	if(CODE == HAQUEST_CODE_ELEMENTARY_C){
		memcpy( &chaQuest.sHaQuestElementary[Quest_C], Buff , sizeof(sQUEST_ELEMENTARY) );
	}
	if(CODE == HAQUEST_CODE_ELEMENTARY_D){
		chaQuest.QuestKeyCode = Quest_D;
		memcpy( &chaQuest.sHaQuestElementary[Quest_D], Buff , sizeof(sQUEST_ELEMENTARY) );
		if(chaQuest.sHaQuestElementary[Quest_D].State==100){
			chaQuest.sHaQuestElementary[Quest_D].State=3;
		}
		if(chaQuest.sHaQuestElementary[Quest_D].State==2 || chaQuest.sHaQuestElementary[Quest_D].State==3){
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuestElementary[Quest_D]);
			if(sinChar->JOB_CODE < 5)
				lstrcpy(chaQuest.szQuestMonsterName,haQuestMonsterName[2]);
			else
				lstrcpy(chaQuest.szQuestMonsterName,haQuestMonsterName[3]);
		}

	}
	if(CODE == HAQUEST_CODE_ELEMENTARY_E){
		chaQuest.QuestKeyCode = Quest_E;
		memcpy( &chaQuest.sHaQuestElementary[Quest_E], Buff , sizeof(sQUEST_ELEMENTARY) );
		if(chaQuest.sHaQuestElementary[Quest_E].State==100){
			chaQuest.sHaQuestElementary[Quest_E].State=3;
		}		
		if(chaQuest.sHaQuestElementary[Quest_E].State==2 || chaQuest.sHaQuestElementary[Quest_E].State==3){
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuestElementary[Quest_E]);
			if(sinChar->JOB_CODE < 5)
				lstrcpy(chaQuest.szQuestMonsterName,haQuestMonsterName[4]);
			else
				lstrcpy(chaQuest.szQuestMonsterName,haQuestMonsterName[5]);
		}

	}
	if(CODE == HAQUEST_CODE_ELEMENTARY_F){
		chaQuest.QuestKeyCode = Quest_F;
		memcpy( &chaQuest.sHaQuestElementary[Quest_F], Buff , sizeof(sQUEST_ELEMENTARY) );
		if(chaQuest.sHaQuestElementary[Quest_F].State==100){
			chaQuest.sHaQuestElementary[Quest_F].State=3;
		}		
		if(chaQuest.sHaQuestElementary[Quest_F].State==2 || chaQuest.sHaQuestElementary[Quest_F].State==3){
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuestElementary[Quest_F]);
			lstrcpy(chaQuest.szQuestMonsterName,haQuestMonsterName[6]);
		}
	}
	if(CODE == HAQUEST_CODE_ELEMENTARY_G){
		memcpy( &chaQuest.sHaQuestElementary[Quest_G], Buff , sizeof(sQUEST_ELEMENTARY) );
	}
	//100LV  Quest
	if(CODE == HAQUEST_CODE_FURYOFPHANTOM){
		memcpy( &chaQuest.sHaQuest100LV, Buff , sizeof(sQUEST_ELEMENTARY) );	

		if(chaQuest.sHaQuest100LV.State == 2 || chaQuest.sHaQuest100LV.State == 3){
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuest100LV);
			lstrcpy(chaQuest.szQuestMonsterName,ha100LVQuestMonterName[0]);		
		}
		if(chaQuest.sHaQuest100LV.State == 7 || chaQuest.sHaQuest100LV.State == 8){
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuest100LV);
			lstrcpy(chaQuest.szQuestMonsterName,ha100LVQuestMonterName[1]);		
		}
	}
	


	return TRUE;
}

/*----------------------------------------------------------------------------*
*					Äù½ºÆ® µ¥ÀÌÅ¸¸¦ ÀúÀåÇÑ´Ù 
*-----------------------------------------------------------------------------*/	
int sinSaveQuest(void *Buff )	//Äù½ºÆ® µ¥ÀÌÅ¸¸¦ ¼¼ÀÌºêÇÑ´Ù 
{

	//4Â÷Àü¾÷    (¿ì¼±±ÇÀ» 4Â÷Àü¾÷À¸·Î ÇÑ´Ù ±×·¡¼­ À§·Î ¿Ã¸²)
	int ContinueSkillIndex = 0;
	if(sinQuest_ChangeJob4.CODE == SIN_QUEST_CODE_CHANGEJOB4){
		if(ContinueSkillIndex = CSKILL->SearchContiueSkillIndex(CHANGE_JOB3_QUEST)){
			sinQuest_ChangeJob4.AgingCount =  ContinueSkill[ContinueSkillIndex-1].UseTime; //À¯Áö½Ã°£
			sinQuest_ChangeJob4.StartLevel =  ContinueSkill[ContinueSkillIndex-1].CheckTime; //ÁøÇà½Ã°£
		}
		memcpy(  Buff , &sinQuest_ChangeJob4 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_ChangeJob4.CODE;
	}

	//3Â÷Àü¾÷    (¿ì¼±±ÇÀ» 3Â÷Àü¾÷À¸·Î ÇÑ´Ù ±×·¡¼­ À§·Î ¿Ã¸²)
	if(sinQuest_ChangeJob3.CODE == SIN_QUEST_CODE_CHANGEJOB3){
		memcpy(  Buff , &sinQuest_ChangeJob3 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_ChangeJob3.CODE;
	}

	//ÅÛ½ºÅ©·Ð 2Â÷ ½ºÅ³ Àü¾÷
	if(sinQuest_ChangeJob.CODE == SIN_QUEST_CODE_CHANGEJOB ){

		memcpy(  Buff , &sinQuest_ChangeJob , sizeof(sQUEST_CHANGEJOB) );
		return sinQuest_ChangeJob.CODE;
	}
	//¸ð¶óÀÌ¿Â 2Â÷ ½ºÅ³ Àü¾÷
	if(sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M ||
		sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D ){
		memcpy(  Buff , &sinQuest_ChangeJob2 , sizeof(sQUEST_CHANGEJOB) );
		return sinQuest_ChangeJob2.CODE;
	}

	//·¹º§Äù½ºÆ® 30
	if(sinQuest_Level30.CODE == SIN_QUEST_CODE_LEVEL30 ){
		memcpy(  Buff , &sinQuest_Level30 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level30.CODE;
	}
	//·¹º§Äù½ºÆ® 50
	if(sinQuest_Level55.CODE == SIN_QUEST_CODE_LEVEL55 ){
		memcpy(  Buff , &sinQuest_Level55 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level55.CODE;
	}
	//·¹º§Äù½ºÆ® 55_2
	if(sinQuest_Level55_2.CODE == SIN_QUEST_CODE_LEVEL55_2 ){
		memcpy(  Buff , &sinQuest_Level55_2 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level55_2.CODE;
	}
	//·¹º§Äù½ºÆ® 70
	if(sinQuest_Level70.CODE == SIN_QUEST_CODE_LEVEL70 ){
		memcpy(  Buff , &sinQuest_Level70 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level70.CODE;
	}
	//·¹º§Äù½ºÆ® 80
	if(sinQuest_Level80.CODE == SIN_QUEST_CODE_LEVEL80 ){
		memcpy(  Buff , &sinQuest_Level80 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level80.CODE;
	}

	//·¹º§Äù½ºÆ® 85
	if(sinQuest_Level85.CODE == SIN_QUEST_CODE_LEVEL85 ){
		memcpy(  Buff , &sinQuest_Level85 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level85.CODE;
	}
	//·¹º§Äù½ºÆ® 90
	if(sinQuest_Level90.CODE == SIN_QUEST_CODE_LEVEL90 ){
		memcpy(  Buff , &sinQuest_Level90 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level90.CODE;
	}

	//·¹º§Äù½ºÆ® 80_2
	if(sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2 ){
		memcpy(  Buff , &sinQuest_Level80_2 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level80_2.CODE;
	}
	//·¹º§Äù½ºÆ® 90
	if(sinQuest_Level90_2.CODE == SIN_QUEST_CODE_LEVEL90_2 ){
		memcpy(  Buff , &sinQuest_Level90_2 , sizeof(sQUEST_CHANGEJOB3) );
		return sinQuest_Level90_2.CODE;
	}
	//½Å±Ô Æ©Åä¸®¾ó Äù½ºÆ®
	if(chaQuest.sHaQuestElementary[Quest_A].CODE == HAQUEST_CODE_ELEMENTARY_A ){
		memcpy(  Buff , &chaQuest.sHaQuestElementary[Quest_A] , sizeof(sQUEST_ELEMENTARY) );
		return chaQuest.sHaQuestElementary[Quest_A].CODE;
	}
	if(chaQuest.sHaQuestElementary[Quest_B].CODE == HAQUEST_CODE_ELEMENTARY_B ){
		memcpy(  Buff , &chaQuest.sHaQuestElementary[Quest_B] , sizeof(sQUEST_ELEMENTARY) );
		return chaQuest.sHaQuestElementary[Quest_B].CODE;
	}
	if(chaQuest.sHaQuestElementary[Quest_C].CODE == HAQUEST_CODE_ELEMENTARY_C ){
		memcpy(  Buff , &chaQuest.sHaQuestElementary[Quest_C] , sizeof(sQUEST_ELEMENTARY) );
		return chaQuest.sHaQuestElementary[Quest_C].CODE;
	}
	if(chaQuest.sHaQuestElementary[Quest_D].CODE == HAQUEST_CODE_ELEMENTARY_D ){
		memcpy(  Buff , &chaQuest.sHaQuestElementary[Quest_D] , sizeof(sQUEST_ELEMENTARY) );
		return chaQuest.sHaQuestElementary[Quest_D].CODE;
	}
	if(chaQuest.sHaQuestElementary[Quest_E].CODE == HAQUEST_CODE_ELEMENTARY_E ){
		memcpy(  Buff , &chaQuest.sHaQuestElementary[Quest_E] , sizeof(sQUEST_ELEMENTARY) );
		return chaQuest.sHaQuestElementary[Quest_E].CODE;
	}
	if(chaQuest.sHaQuestElementary[Quest_F].CODE == HAQUEST_CODE_ELEMENTARY_F ){
		memcpy(  Buff , &chaQuest.sHaQuestElementary[Quest_F] , sizeof(sQUEST_ELEMENTARY) );
		return chaQuest.sHaQuestElementary[Quest_F].CODE;
	}
	if(chaQuest.sHaQuestElementary[Quest_G].CODE == HAQUEST_CODE_ELEMENTARY_G ){
		memcpy(  Buff , &chaQuest.sHaQuestElementary[Quest_G] , sizeof(sQUEST_ELEMENTARY) );
		return chaQuest.sHaQuestElementary[Quest_G].CODE;
	}
	//100LV Äù½ºÆ®
	if(chaQuest.sHaQuest100LV.CODE == HAQUEST_CODE_FURYOFPHANTOM ){
		memcpy(  Buff , &chaQuest.sHaQuest100LV , sizeof(sQUEST_ELEMENTARY) );
		return chaQuest.sHaQuest100LV.CODE;
	}
	return FALSE;
}

/*----------------------------------------------------------------------------*
*					Äù½ºÆ®½Ã NPCÀÇ ´ë»ç¸¦ º¸¿©ÁØ´Ù 
*-----------------------------------------------------------------------------*/	
int sinMorayionNpcChangeJob_Two()	
{
	//if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç ÃÊº¸ Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	
	int i = 0 ;
	////////¾ÆÀÌÅÛÀÌ ÀÖ´ÂÁö¸¦ Ã¼Å©ÇÑ´Ù
	for( i=0 ; i < INVENTORY_MAXITEM ; i++){
		if(cInvenTory.InvenItem[i].Flag){
			if(cInvenTory.InvenItem[i].CODE == (sinQT1|sin04) ||  //·Î¾âÁ¦¸®
				cInvenTory.InvenItem[i].CODE == (sinQT1|sin05) ){ //¹ß¸ðÁ¦
				sinQuest_ChangeJob2.State = 3;
				//¾ÆÀÌÅÛÀ» »èÁ¦ÇÑ´Ù
				cInvenTory.InvenItem[i].Flag = 0;
				cInvenTory.ReFormInvenItem(); //¿ÀÅä ¼ÂÆÃµÈ´ÙÀ½¿¡µµ Ã¼Å©¼¶À» °»½ÅÇÑ´Ù 
				break;
			}
		}
		if(cInvenTory.InvenItemTemp[i].Flag){
			if(cInvenTory.InvenItemTemp[i].CODE == (sinQT1|sin04) ||  //·Î¾âÁ¦¸®
				cInvenTory.InvenItemTemp[i].CODE == (sinQT1|sin05) ){ //¹ß¸ðÁ¦
				sinQuest_ChangeJob2.State = 3;
				cInvenTory.InvenItemTemp[i].Flag = 0;
				cInvenTory.ReFormInvenItem(); //¿ÀÅä ¼ÂÆÃµÈ´ÙÀ½¿¡µµ Ã¼Å©¼¶À» °»½ÅÇÑ´Ù 
				break;
			}
		}
	}
	//¸ð¶óÀÌ¿Â 2Â÷Àü¾÷
	if(sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M){
			
		switch(sinQuest_ChangeJob2.State){
			case 1: //Àü¾÷°ü·Ã ¸Þ¼¼Áö¸¦ ¶ç¿À°í ¾ÆÀÌÅÛÀ» ÁØ´Ù 
				cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath[3]);  
				sinQuest_ChangeJob2.State = 2;
			break;
			case 2:
				cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath[4]);  
			break;
			case 3:
				cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath[5]);  
				sinQuest_ChangeJob2.State = 4;
				sinQuest_ChangeJob2.BackUpCode = sinQuest_ChangeJob2.CODE;
				sinQuest_ChangeJob2.CODE = 0; //Äù½ºÆ®°¡ ¿Ï·áµÇ¸é ÄÚµå°¡ »ç¶óÁø´Ù 
				EndQuest_Code(sinQuest_ChangeJob2.BackUpCode);
				sinQuest_ChangeJob2.CODE = 0;
				sinChar->wVersion[1]     = 0;
			
				//Àü¾÷Äù½ºÆ® ¿Ï·á
			break;
		}
	}
	if(sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D){
		switch(sinQuest_ChangeJob2.State){
			case 1: //Àü¾÷°ü·Ã ¸Þ¼¼Áö¸¦ ¶ç¿À°í ¾ÆÀÌÅÛÀ» ÁØ´Ù 
				cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath[6]);  
				sinQuest_ChangeJob2.State = 2;
			break;
			case 2:
				cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath[7]);  
			break;
			case 3:
				cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath[8]);  
				sinQuest_ChangeJob2.BackUpCode = sinQuest_ChangeJob2.CODE;
				sinQuest_ChangeJob2.CODE = 0; //Äù½ºÆ®°¡ ¿Ï·áµÇ¸é ÄÚµå°¡ »ç¶óÁø´Ù 
				EndQuest_Code(sinQuest_ChangeJob2.BackUpCode);
				sinQuest_ChangeJob2.CODE = 0;
				sinChar->wVersion[1]     = 0;
				//Àü¾÷Äù½ºÆ®¿Ï·á
			break;
		}
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*				Äù½ºÆ®½Ã NPCÀÇ ´ë»ç¸¦ º¸¿©ÁÖ°í ¾ÆÀÌÅÛÀ» Ã³¸®ÇÑ´Ù (3Â÷ÀüÁ÷)
*-----------------------------------------------------------------------------*/	
int sinNpcChangeJob3()	
{
	sITEM *pItem=0;  
	int   Count = 0;
	int   i = 0;
	int   TempItemIndex[3] = {0,0,0};

	if(!sinQuest_ChangeJob3.CODE)return FALSE;

	if(sinQuest_ChangeJob3.State == 1 ){ //Áßº¹Ã¼Å©¸¦ ¸·±âÀ§ÇØ  
		for( i = 0; i < INVENTORY_MAXITEM*2 ; i++){
			if(i<100){
				if(!cInvenTory.InvenItem[i].Flag)continue;
				pItem = &cInvenTory.InvenItem[i];
			}
			else{
				if(!cInvenTory.InvenItemTemp[i-100].Flag)continue;
				pItem = &cInvenTory.InvenItemTemp[i-100];
			}
			//¿©±â¼­´Â ÀÏ´Ü ½©ÅÒ¸¸À» Ã¼Å©ÇÑ´Ù
			if(pItem->sItemInfo.CODE == (sinQT1|sin06)){
				TempItemIndex[Count] = i;
				Count++;
			}
		}


		if(Count >= 3){
			sinQuest_ChangeJob3.State = 2;
			memset(&sWingItem_Send,0,sizeof(sCRAFTITEM_SERVER)); //ÃÊ±âÈ­
			for(int j = 0 ; j < Count ; j++){
				if(TempItemIndex[j] < 100){ 
					//cInvenTory.InvenItem[TempItemIndex[j]].Flag = 0; //½©ÅÒÀ» Áö¿î´Ù
					sWingItem_Send.SheltomCode[j] =  cInvenTory.InvenItem[TempItemIndex[j]].sItemInfo.CODE;
					sWingItem_Send.Head[j] =  cInvenTory.InvenItem[TempItemIndex[j]].sItemInfo.ItemHeader.Head;
					sWingItem_Send.CheckSum[j] =  cInvenTory.InvenItem[TempItemIndex[j]].sItemInfo.ItemHeader.dwChkSum;

				}
				else{
					//cInvenTory.InvenItemTemp[TempItemIndex[j]].Flag = 0; //½©ÅÒÀ» Áö¿î´Ù
					sWingItem_Send.SheltomCode[j] =  cInvenTory.InvenItemTemp[TempItemIndex[j]].sItemInfo.CODE;
					sWingItem_Send.Head[j] =  cInvenTory.InvenItemTemp[TempItemIndex[j]].sItemInfo.ItemHeader.Head;
					sWingItem_Send.CheckSum[j] =  cInvenTory.InvenItemTemp[TempItemIndex[j]].sItemInfo.ItemHeader.dwChkSum;

				}
			}
			cInvenTory.ReFormInvenItem(); //ÀÎº¥ ReForm
		}
	}

	switch(sinQuest_ChangeJob3.State){
		case 1:
			//cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath3[1]);  
			//return TRUE;
		break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath3[2]);  
			return TRUE;
		break;
		case 3:
			//cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath3[3]);  
			//return TRUE;
		break;
		case 4:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath3[4]);  
			return TRUE;
		break;
		case 6:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath3[5]);  
		break;
	}
	return FALSE;
}

int DeleteQuestItem(DWORD CODE)
{
	sITEM *pItem=0;
	int i = 0;
	for( i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else{
			if(!cInvenTory.InvenItemTemp[i-100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i-100];
		}
		
		if(pItem->sItemInfo.CODE == CODE){
			pItem->Flag = 0;
			if(i<100){
				if(pItem->ItemPosition){
					sInven[pItem->ItemPosition-1].ItemIndex = 0;
					if(pItem->SetModelPosi)
						sinSetCharItem(pItem->CODE , pItem->SetModelPosi, FALSE); 

				}
			}
		}
	}
	cInvenTory.ReFormInvenItem();
	ReformCharForm();
	cInvenTory.ReFormPotionNum();
	cInvenTory.SetItemToChar();
	cInvenTory.CheckWeight();
	return TRUE;
}

sITEM* DeleteItemByName(char name[64])
{
	sITEM* pItem = 0;
	int i = 0;
	for (i = 0; i < INVENTORY_MAXITEM * 2; i++) {
		if (i < 100) {
			if (!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else {
			if (!cInvenTory.InvenItemTemp[i - 100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i - 100];
		}

		if (lstrcmpi(pItem[i].sItemInfo.ItemName, name) == 0) {
			return pItem;
		}
	}


	return FALSE;
}
	
int  QuestMonsterCount[] = {30,40,50,25,35,45,50,70,100};


// Atualiza os mobs localmente pra não precisar ficar enviando pacote do servidor o tempo todo
int CheckDailyQuestMonsters( DWORD Monster_CODE )
{
	if(Monster_CODE == 100)
		return false;

	if(sinQuest_Daily.CODE)
	{ 
		if( StageField[ lpCurPlayer->OnStageField ]->FieldCode == sinQuest_Daily.AgingCount )
		{
			if(sinQuest_Daily.State == 1)
			{
				sinQuest_Daily.Monster[0]++;

				//Check if quest is finished
				if(sinQuest_Daily.Monster[0] ==  sinQuest_Daily.Monster[1] )
					sinQuest_Daily.State = 2;
			}
		}
	}

	return true;
}

int CheckChangeJob3QuestItem(DWORD Monster_CODE)
{
	if(Monster_CODE == 100)
		return false;

	char szTemp[128];
	char szBuff[128];
	memset(&szTemp,0,sizeof(szTemp));
	if(chaQuest.sHaQuest100LV.CODE){
		if(chaQuest.sHaQuest100LV.Kind){
			if(chaQuest.sHaQuest100LV.State==2 && StageField[lpCurPlayer->OnStageField]->FieldCode == 28){
				chaQuest.sHaQuest100LV.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp,sinLevelQusetDoc,chaQuest.sHaQuest100LV.Monster[0],ha100LVQuestMonterName[0]);
#else
				wsprintf(szTemp,sinLevelQusetDoc,ha100LVQuestMonterName[0],chaQuest.sHaQuest100LV.Monster[0]);
#endif
				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);

				if(chaQuest.sHaQuest100LV.Monster[0]==chaQuest.sHaQuest100LV.Monster[1] ){
#ifdef	_LANGUAGE_ENGLISH
					wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef	_LANGUAGE_BRAZIL
					wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef	_LANGUAGE_ARGENTINA
					wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef _LANGUAGE_CHINESE
					wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
					wsprintf(szBuff,sinLevelQusetDoc4, ha100LVQuestMonterName[0], chaQuest.sHaQuest100LV.Monster[1]);
#endif
#endif
#endif
#endif
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuest100LV.Kind  = 0;
					chaQuest.sHaQuest100LV.State = 3;
				}
			}
			if(chaQuest.sHaQuest100LV.State==7 && StageField[lpCurPlayer->OnStageField]->FieldCode == 31){
				chaQuest.sHaQuest100LV.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
					wsprintf(szTemp,sinLevelQusetDoc, chaQuest.sHaQuest100LV.Monster[0],ha100LVQuestMonterName[1]);
#else
					wsprintf(szTemp,sinLevelQusetDoc, ha100LVQuestMonterName[1],chaQuest.sHaQuest100LV.Monster[0]);
#endif

				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);

				if(chaQuest.sHaQuest100LV.Monster[0]==chaQuest.sHaQuest100LV.Monster[1] ){
#ifdef	_LANGUAGE_ENGLISH
					wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[1]);
#else
#ifdef	_LANGUAGE_BRAZIL
					wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef	_LANGUAGE_ARGENTINA
					wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef _LANGUAGE_CHINESE
					wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[1]);
#else
					wsprintf(szBuff,sinLevelQusetDoc4, ha100LVQuestMonterName[1], chaQuest.sHaQuest100LV.Monster[1]);
#endif
#endif
#endif
#endif
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuest100LV.Kind  = 0;
					chaQuest.sHaQuest100LV.State = 8;
				}
			
			}
		}
	}	
	//½Å±Ô ÃÊº¸ Äù½ºÆ®
	//µÎ·Á¿î ¸¶À½
	if(chaQuest.sHaQuestElementary[Quest_B].CODE){
		if(chaQuest.sHaQuestElementary[Quest_B].Kind &&chaQuest.sHaQuestElementary[Quest_B].Kind==Monster_CODE){
			chaQuest.sHaQuestElementary[Quest_B].Monster[0]++;
			if(sinChar->JOB_CODE <5)
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_B].Monster[0], haQuestMonsterName[0]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[0], chaQuest.sHaQuestElementary[Quest_B].Monster[0]);
#endif
			else
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_B].Monster[0], haQuestMonsterName[1]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[1], chaQuest.sHaQuestElementary[Quest_B].Monster[0]);
#endif
	
			CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);

			if(chaQuest.sHaQuestElementary[Quest_B].Monster[0] ==  chaQuest.sHaQuestElementary[Quest_B].Monster[1] ){
#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_B].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_B].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_B].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_CHINESE
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_B].Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff,sinLevelQusetDoc4, szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_B].Monster[1]);
#endif
#endif
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_B].Kind  = 0;
				chaQuest.sHaQuestElementary[Quest_B].State = 3;
			}
		
		}
	}
	//°íºí¸° µ¿»ê
	if(chaQuest.sHaQuestElementary[Quest_D].CODE)
	{
		if(chaQuest.sHaQuestElementary[Quest_D].Kind &&chaQuest.sHaQuestElementary[Quest_D].Kind==Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_D].Monster[0]++;
			if(sinChar->JOB_CODE <5)
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_D].Monster[0], haQuestMonsterName[2]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[2], chaQuest.sHaQuestElementary[Quest_D].Monster[0]);
#endif
			else
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_D].Monster[0], haQuestMonsterName[3]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[3], chaQuest.sHaQuestElementary[Quest_D].Monster[0]);
#endif
				
			CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
			if(chaQuest.sHaQuestElementary[Quest_D].Monster[0] ==  chaQuest.sHaQuestElementary[Quest_D].Monster[1] )
			{
#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_D].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_D].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_D].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_CHINESE
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_D].Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff, sinLevelQusetDoc4,szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_D].Monster[1]);
#endif
#endif
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_D].Kind  = 0;
				chaQuest.sHaQuestElementary[Quest_D].State = 3;
			}
		
		}
	}
	//¾ðµ¥µåÀÇ À§Çù
	if(chaQuest.sHaQuestElementary[Quest_E].CODE)
	{
		if(chaQuest.sHaQuestElementary[Quest_E].Kind &&chaQuest.sHaQuestElementary[Quest_E].Kind==Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_E].Monster[0]++;
			if(sinChar->JOB_CODE <5)
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_E].Monster[0], haQuestMonsterName[4]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[4], chaQuest.sHaQuestElementary[Quest_E].Monster[0]);
#endif
			else
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_E].Monster[0], haQuestMonsterName[5]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[5], chaQuest.sHaQuestElementary[Quest_E].Monster[0]);
#endif
				
	
			CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
			if(chaQuest.sHaQuestElementary[Quest_E].Monster[0] ==  chaQuest.sHaQuestElementary[Quest_E].Monster[1] )
			{
#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_E].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_E].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_E].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_CHINESE
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_E].Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff,sinLevelQusetDoc4, szQuestMonsterName , chaQuest.sHaQuestElementary[Quest_E].Monster[1]);
#endif
#endif
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_E].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_E].State = 3;
			}
		
		}
	}
	//¿Ü´«¹ÚÀÌ ±«¹°
	if(chaQuest.sHaQuestElementary[Quest_F].CODE){
		if(chaQuest.sHaQuestElementary[Quest_F].Kind &&chaQuest.sHaQuestElementary[Quest_F].Kind==Monster_CODE){
			chaQuest.sHaQuestElementary[Quest_F].Monster[0]++;
#ifdef _LANGUAGE_CHINESE
			wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_F].Monster[0], haQuestMonsterName[6]);
#else
			wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[6], chaQuest.sHaQuestElementary[Quest_F].Monster[0]);
#endif

			CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
			if(chaQuest.sHaQuestElementary[Quest_F].Monster[0] ==  chaQuest.sHaQuestElementary[Quest_F].Monster[1] ){
#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_F].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_F].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_F].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_CHINESE
				wsprintf(szBuff,sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_F].Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff,sinLevelQusetDoc4, szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_F].Monster[1]);
#endif
#endif
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_F].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_F].State = 3;
				SetQuestBoard();
			}
		
		}
	}
	
	//4Â÷½ºÅ³ Àü¾÷Äù½ºÆ®
	if(sinQuest_ChangeJob4.CODE){
		if(sinQuest_ChangeJob4.Kind &&Monster_CODE == sinQuest_ChangeJob4.Kind && sinQuest_ChangeJob4.State <= 4){
			sinQuest_ChangeJob4.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
			wsprintf(szTemp, sinLevelQusetDoc, sinQuest_ChangeJob4.Monster[0], szQuestMonsterName);
#else
			wsprintf(szTemp,sinLevelQusetDoc,szQuestMonsterName,sinQuest_ChangeJob4.Monster[0]);
#endif

			CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
			if(sinQuest_ChangeJob4.Monster[0] ==  sinQuest_ChangeJob4.Monster[1] ){

#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff,sinLevelQusetDoc4, sinQuest_ChangeJob4.Monster[1],szQuestMonsterName );
#else
//Áß±¹
#ifdef _LANGUAGE_CHINESE
				wsprintf(szBuff,sinLevelQusetDoc4, sinQuest_ChangeJob4.Monster[1],szQuestMonsterName );
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff,sinLevelQusetDoc4, sinQuest_ChangeJob4.Monster[1],szQuestMonsterName );				
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff,sinLevelQusetDoc4, sinQuest_ChangeJob4.Monster[1],szQuestMonsterName );				
#else
				wsprintf(szBuff,sinLevelQusetDoc4, szQuestMonsterName, sinQuest_ChangeJob4.Monster[1]);
#endif
#endif			    
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_ChangeJob4.Kind = 0;
			}
		}
	}

	//·¹º§Äù½ºÆ® 30
	if(sinQuest_Level30.CODE){ 
		if(MONSTER_BAGON == Monster_CODE){
			if(sinQuest_Level30.State == 1){
				sinQuest_Level30.Monster[0]++;
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level30.Monster[0], sinLevelQuestMonster[0]);
#else

				wsprintf(szTemp,sinLevelQusetDoc,sinLevelQuestMonster[0],sinQuest_Level30.Monster[0]);
#endif
				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
				if(sinQuest_Level30.Monster[0] ==  sinQuest_Level30.Monster[1] ){

#ifdef _LANGUAGE_BRAZIL
					cMessageBox.ShowMessageEvent("Voce matou 20 Bargons.");
#else
					cMessageBox.ShowMessageEvent("Voce matou 20 Bargons.");
#endif
					sinQuest_Level30.State =2;
				}
			}
		}
	}

	//¿ä±â´Â ·¹º§Äù½ºÆ® 55 (ÅÛ½ºÅ©·Ð)
	if(sinQuest_Level55.CODE){ 
		if(MONSTER_MURPIN == Monster_CODE){
			if(sinQuest_Level55.State == 1){
				sinQuest_Level55.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level55.Monster[0], sinLevelQuestMonster[1]);
#else
				wsprintf(szTemp,sinLevelQusetDoc,sinLevelQuestMonster[1],sinQuest_Level55.Monster[0]);
#endif
				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
				if(sinQuest_Level55.Monster[0] ==  sinQuest_Level55.Monster[1] ){
					sinQuest_Level55.State =2;
				}
			}
		}
	}

	//¿ä±â´Â ·¹º§Äù½ºÆ® 55 (¸ð¶óÀÌ¿Â)
	if(sinQuest_Level55_2.CODE){  
		if(MONSTER_DIREBEE == Monster_CODE){
			if(sinQuest_Level55_2.State == 1){
				sinQuest_Level55_2.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level55_2.Monster[0], sinLevelQuestMonster[2]);
#else
				wsprintf(szTemp,sinLevelQusetDoc,sinLevelQuestMonster[2],sinQuest_Level55_2.Monster[0]);
#endif
				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
				if(sinQuest_Level55_2.Monster[0] ==  sinQuest_Level55_2.Monster[1] ){
					sinQuest_Level55_2.State =2;
				}
			}
		}
	}

	//¿ä±â´Â ·¹º§Äù½ºÆ® 70
	if(sinQuest_Level70.CODE){ 
		if(MONSTER_TYPOON == Monster_CODE){
			if(sinQuest_Level70.State ==1){
				sinQuest_Level70.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp,sinLevelQusetDoc,sinQuest_Level70.Monster[0],sinLevelQuestMonster[3]);
#else
				wsprintf(szTemp,sinLevelQusetDoc,sinLevelQuestMonster[3],sinQuest_Level70.Monster[0]);
#endif
				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
				if(sinQuest_Level70.Monster[0] ==  sinQuest_Level70.Monster[1] ){
					sinQuest_Level70.State =2;
				}
			}
		}
	}
	//¿ä±â´Â ·¹º§Äù½ºÆ® 80
	if(sinQuest_Level80.CODE){ 
		if(MONSTER_RATOO == Monster_CODE){
			if(sinQuest_Level80.State ==1){
				sinQuest_Level80.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp,sinLevelQusetDoc,sinQuest_Level80.Monster[0],sinLevelQuestMonster[4]);
#else
				wsprintf(szTemp,sinLevelQusetDoc,sinLevelQuestMonster[4],sinQuest_Level80.Monster[0]);
#endif
				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
				if(sinQuest_Level80.Monster[0] ==  sinQuest_Level80.Monster[1] ){
					sinQuest_Level80.State =2;
				}
			}
		}
	}
	//¿ä±â´Â ·¹º§Äù½ºÆ® 85
	if(sinQuest_Level85.CODE){ 
		if(MONSTER_GROTESQUE == Monster_CODE){
			if(sinQuest_Level85.State == 2){
				sinQuest_Level85.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp,sinLevelQusetDoc,sinQuest_Level85.Monster[0],sinLevelQuestMonster[5]);
#else
				wsprintf(szTemp,sinLevelQusetDoc,sinLevelQuestMonster[5],sinQuest_Level85.Monster[0]);
#endif

				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
				if(sinQuest_Level85.Monster[0] ==  sinQuest_Level85.Monster[1] ){
					sinQuest_Level85.State =3;
				}
			}
		}
	}
	//¿ä±â´Â ·¹º§Äù½ºÆ® 90
	if(sinQuest_Level90.CODE){ 
		if(MONSTER_IRONFIST == Monster_CODE){
			if(sinQuest_Level90.State == 1){
				sinQuest_Level90.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp,sinLevelQusetDoc,sinQuest_Level90.Monster[0],sinLevelQuestMonster[6]);
#else
				wsprintf(szTemp,sinLevelQusetDoc,sinLevelQuestMonster[6],sinQuest_Level90.Monster[0]);
#endif

				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
				if(sinQuest_Level90.Monster[0] ==  sinQuest_Level90.Monster[1] ){
					sinQuest_Level90.State =2;
				}
			}
		}
	}
	int sinQuestMonFlag = 0;
	if(sinQuest_Level90_2.CODE){ 
		if(sinQuest_Level90_2.State == 2){
			switch(sinQuest_Level90_2.Kind){
				case 1:
					if(MONSTER_OMEGA == Monster_CODE){
						sinQuest_Level90_2.Monster[0]++;
						sinQuestMonFlag = 1;
					}
				break;
				case 2:
					if(MONSTER_D_MACHINE == Monster_CODE){
						sinQuest_Level90_2.Monster[0]++;
						sinQuestMonFlag = 1;
					}
				break;
				case 3:
					if(MONSTER_MOUNTAIN == Monster_CODE){
						sinQuest_Level90_2.Monster[0]++;
						sinQuestMonFlag = 1;
					}
				break;

			}
			if(sinQuestMonFlag){

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp,sinLevelQusetDoc,sinQuest_Level90_2.Monster[0],sinLevelQuest90_2Mon[sinQuest_Level90_2.Kind-1]);
#else
				wsprintf(szTemp,sinLevelQusetDoc,sinLevelQuest90_2Mon[sinQuest_Level90_2.Kind-1],sinQuest_Level90_2.Monster[0]);
#endif

				CHATGAMEHANDLE->AddChatBoxText(szTemp, EChatColor::CHATCOLOR_Notice);
			}

			if(sinQuest_Level90_2.Monster[0] >=  sinQuest_Level90_2.Monster[1] ){
				sinQuest_Level90_2.State =3;
			}
		}
	}
	
	sITEM *pItem = 0; 
	if(sInven[0].ItemIndex){
		pItem = &cInvenTory.InvenItem[sInven[0].ItemIndex-1];

	}
	if(!pItem)return FALSE;

	
	//Àü¾÷¾ÆÀÌÅÛÀÌ ¾Æ´Ñ°æ¿ì´Â ¸®ÅÏÇÑ´Ù
	if(pItem->sItemInfo.ItemAgingNum[0] > 3 ||
		pItem->sItemInfo.ItemKindCode != ITEM_KIND_QUEST_WEAPON)return FALSE;
	
	if(pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON ){ 
		switch(sinChar->JOB_CODE){
			case 1:		//ÆÄÀÌÅÍ
			case 2:		//¸ÞÄ«´Ï¼Ç
			case 4:		//ÆÄÀÌÅ©¸Ç
			case 6:		//³ªÀÌÆ®
			case 3:		//¾ÆÃÄ
			case 5:		//¾ÆÅ»¶õÅ¸
				if((pItem->sItemInfo.ItemAgingNum[1]+1) == Monster_CODE){
					pItem->sItemInfo.ItemAgingCount[0]--;

				}
			break;
			case 7:		//¸ÅÁö¼Ç
			case 8:		//ÇÁ¸®½ºÆ¼½º
				if(pItem->sItemInfo.ItemAgingNum[0] == 1){
					if(StageField[lpCurPlayer->OnStageField]->FieldCode == 8)  //»ç¸· 1
						pItem->sItemInfo.ItemAgingCount[0]--;
				}
				if(pItem->sItemInfo.ItemAgingNum[0] == 2){
					if(StageField[lpCurPlayer->OnStageField]->FieldCode == 10)  //»ç¸· 1
						pItem->sItemInfo.ItemAgingCount[0]--;
				}
				if(pItem->sItemInfo.ItemAgingNum[0] == 3){
					if(StageField[lpCurPlayer->OnStageField]->FieldCode == 13)  //´øÀü1
						pItem->sItemInfo.ItemAgingCount[0]--;
				}
			break;
		}
	}
		
	if((pItem->sItemInfo.ItemAgingCount[0] < 1 ) || (ResetQuset3Flag ==2)){
		//WÅ°·Î ¹«±â¼ÂÆÃÀ» ¹Ù²Ù´Â°É ¸·¾ÆÁØ´Ù
		NotChangeSetItemFlag = 1;
		memset(&sAging_Send,0,sizeof(sCRAFTITEM_SERVER));
		memcpy(&sAging_Send.DesCraftItem,pItem,sizeof(sITEM));
		SendAgingItemToServer( &sAging_Send );
		
		memcpy(&TempQuestItem,pItem,sizeof(sITEM));

		//¼­¹ö¿¡ º¸³»°í ¾ÆÀÌÅÛÀ» Áö¿î´Ù
		//cInvenTory.DeleteInvenItemToServer(pItem->sItemInfo.CODE, pItem->sItemInfo.ItemHeader.Head,pItem->sItemInfo.ItemHeader.dwChkSum);
		//SetChangeJob3QuestItem(pItem);

	}
	return TRUE;

}
int SetChangeJob3QuestItem(sITEMINFO *pItem,int Down)
{

	int Temp =0;
	float fTemp = 0;
	if(pItem->ItemAgingNum[0] > 3)return FALSE; //3Â÷±îÁö¸¸ ÇÒ¼öÀÖ´Ù

	switch(pItem->CODE&sinITEM_MASK2){
		case sinWA1: 
		case sinWC1:
		case sinWP1:
		case sinWS2:
			if(Down){
				//pItem->Attack_Speed -=2;
				/*
				Temp = GetRandomPos(2,4);
				pItem->Damage[0] -=Temp;
				pItem->Damage[1] -=Temp;
				Temp = GetRandomPos(15,20);
				pItem->Attack_Rating -=Temp;
				*/

			}
			else{
				if(pItem->ItemAgingNum[0]){
					pItem->fIncrease_Life += 4;
					Temp = GetRandomPos(1,2);
					pItem->Damage[0] +=Temp;
					pItem->Damage[1] +=Temp;
					Temp = GetRandomPos(10,15);
					pItem->Attack_Rating +=Temp;
					pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX |SIN_ADD_ATTACK_RATE |SIN_ADD_LIFE;
				}
				pItem->ItemAgingNum[1] = pItem->ItemAgingNum[0];
				pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]]; //ÃÖ´ëÄ¡ ¼ÂÆÃ
				pItem->ItemAgingNum[0]++; //·¹º§¾÷
				
			}
		break;
		case sinWS1:
		case sinWT1:
			if(Down){
				//pItem->Attack_Speed -=2;
				/*
				Temp = GetRandomPos(2,4);
				pItem->Damage[0] -=Temp;
				pItem->Damage[1] -=Temp;
				Temp = GetRandomPos(15,20);
				pItem->Attack_Rating -=Temp;
				*/

			}
			else{
				if(pItem->ItemAgingNum[0]){
					pItem->fIncrease_Life += 4;
					Temp = GetRandomPos(1,2);
					pItem->Damage[0] +=Temp;
					pItem->Damage[1] +=Temp;
					Temp = GetRandomPos(10,15);
					pItem->Attack_Rating +=Temp;
					pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX |SIN_ADD_ATTACK_RATE |SIN_ADD_LIFE;
				}

				pItem->ItemAgingNum[1] = 3+pItem->ItemAgingNum[0];
				pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]]; //ÃÖ´ëÄ¡ ¼ÂÆÃ
				pItem->ItemAgingNum[0]++; //·¹º§¾÷
				
			}
		break;
		case sinWM1:
			if(Down){
				//pItem->Attack_Speed -=2;
				/*
				Temp = GetRandomPos(2,4);
				pItem->Damage[0] -=Temp;
				pItem->Damage[1] -=Temp;
				Temp = GetRandomPos(4,8);
				fTemp = (float)Temp/10.0f;
				pItem->fMana_Regen -= fTemp;
				*/

			}
			else{
				if(pItem->ItemAgingNum[0]){
					pItem->fIncrease_Life += 4;
					Temp = GetRandomPos(1,2);
					pItem->Damage[0] +=Temp;
					pItem->Damage[1] +=Temp;
					Temp = GetRandomPos(3,6);
					fTemp = (float)Temp/10.0f;
					pItem->fMana_Regen += fTemp;
					pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX |SIN_ADD_MANAREGEN |SIN_ADD_LIFE;

				}
				pItem->ItemAgingNum[1] = 6+pItem->ItemAgingNum[0];
				pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]]; //ÃÖ´ëÄ¡ ¼ÂÆÃ
				pItem->ItemAgingNum[0]++; //·¹º§¾÷
				
			}
		break;
	}
	//ÇÑ¹ø¸¸ ¼ÂÆÃÀÌµÇ°í (¿¡ÀÌÂ¡ ¹æ½ÄÀ¸·Î ¿Ã¶ó°£°Ç ¹ÞÀº´ÙÀ½ ¼ÂÆÃÇØÁà¾ßÇÑ´Ù)
	pItem->ItemAgingCount[0] = pItem->ItemAgingCount[1]; //0¹øÀº °íÄ¥¼öÀÖ´Ù
	ReformItem(pItem);  //¾ÆÀÌÅÛ ÀÎÁõ ¹Þ±â 
	return TRUE;
}

int CheckQuestItemDownFlag = 0;
//3Â÷Àü¾÷ÀÌ ³¡³µ´ÂÁö¸¦ Ã¼Å©ÇÑ´Ù
int CheckChangeJob_QuestItem()
{

	int ItemIndex = 0;
	sITEM *pTempItem = 0; 
	///////////½Ã°£À» Ã¼Å©ÇØ¼­ ¾ÆÀÌÅÛÀ» ¾ø¾Ø´Ù
	if(sinQuest_ChangeJob3.CODE && sinQuest_ChangeJob3.State == 5 && sinChar->ChangeJob ==2){ 
		while(1){
			ItemIndex = cInvenTory.SearchItemIndex(0,ITEM_KIND_QUEST_WEAPON);
			if(ItemIndex){
				if(ItemIndex < 100) //5ÀÏ°æ°úÈÄ Áö¿î´Ù
					pTempItem = &cInvenTory.InvenItem[ItemIndex-1];
				else pTempItem = &cInvenTory.InvenItemTemp[(ItemIndex-100)-1];

				if(sinItemTime > pTempItem->sItemInfo.dwCreateTime +(60*60*24*5) ){
				//if(sinItemTime > pTempItem->sItemInfo.dwCreateTime +(60*3) ){ //Å×½ºÆ®¸¦ À§ÇØ 30ºÐ
					//¸µ°ú ¹«±â¸¦ °°ÀÌ ¾ø¾Ø´Ù
					cInvenTory.DeleteInvenItemToServer(pTempItem->sItemInfo.CODE,
						pTempItem->sItemInfo.ItemHeader.Head,pTempItem->sItemInfo.ItemHeader.dwChkSum);
					DeleteQuestItem(sinOR2|sin02);
					DeleteQuestItem(sinOR2|sin03);
					DeleteQuestItem(sinOR2|sin04);

					//¸¶¿ì½º ¾ÆÀÌÅÛµµ Ã¼Å©ÇÑ´Ù
					if(MouseItem.Flag && MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON){
							cInvenTory.DeleteInvenItemToServer(MouseItem.sItemInfo.CODE,
								MouseItem.sItemInfo.ItemHeader.Head,MouseItem.sItemInfo.ItemHeader.dwChkSum);
					}
				}
				else break;
			}
			else break;
			
		}
	}


	if(sinQuest_ChangeJob3.CODE && sinQuest_ChangeJob3.State == 5 && sinChar->ChangeJob ==2){
		if(!cInvenTory.SearchItemCode(0,ITEM_KIND_QUEST_WEAPON)){
			//Äù½ºÆ® ¾ÆÀÌÅÛÀÌ »ç¶óÁü
			switch(sinChar->JOB_CODE){
				case 1:		//ÆÄÀÌÅÍ
					lstrcpy(sLost_Item.szDoc,Quest3ItemName[0]);
					sLost_Item.LostItem[0].CODE = (sinWA1 | sin08);
					sLost_Item.LostItem[1].CODE = (sinOR2|sin02);

				break;
				case 2:		//¸ÞÄ«´Ï¼Ç
					lstrcpy(sLost_Item.szDoc,Quest3ItemName[1]);
					sLost_Item.LostItem[0].CODE = (sinWC1 | sin08);
					sLost_Item.LostItem[1].CODE = (sinOR2|sin02);
				break;
				case 3:		//¾ÆÃÄ
					lstrcpy(sLost_Item.szDoc,Quest3ItemName[2]);
					sLost_Item.LostItem[0].CODE = (sinWS1 | sin10);
					sLost_Item.LostItem[1].CODE = (sinOR2|sin03);
				break;
				case 4:		//ÆÄÀÌÅ©¸Ç
					lstrcpy(sLost_Item.szDoc,Quest3ItemName[3]);
					sLost_Item.LostItem[0].CODE = (sinWP1 | sin09);
					sLost_Item.LostItem[1].CODE = (sinOR2|sin02);
				break;
				case 5:		//¾ÆÅ»¶õÅ¸
					lstrcpy(sLost_Item.szDoc,Quest3ItemName[4]);
					sLost_Item.LostItem[0].CODE = (sinWT1 | sin09);
					sLost_Item.LostItem[1].CODE = (sinOR2|sin03);
				break;
				case 6:		//³ªÀÌÆ®
					lstrcpy(sLost_Item.szDoc,Quest3ItemName[5]);
					sLost_Item.LostItem[0].CODE = (sinWS2 | sin10);
					sLost_Item.LostItem[1].CODE = (sinOR2|sin02);
				break;
				case 7:		//¸ÅÁö¼Ç
				case 8:		//ÇÁ¸®½ºÆ¼½º
					lstrcpy(sLost_Item.szDoc,Quest3ItemName[6]);
					sLost_Item.LostItem[0].CODE = (sinWM1 | sin09);
					sLost_Item.LostItem[1].CODE = (sinOR2|sin04);
				break;
			}
			sinQuest_ChangeJob3.State = 6;
			sLost_Item.Flag = 1;
			cInvenTory.CheckInvenEmpty(&sLost_Item.LostItem[0]); //ÀÌ¹ÌÁö·Îµå 
			cInvenTory.CheckInvenEmpty(&sLost_Item.LostItem[1]); //ÀÌ¹ÌÁö·Îµå 

		}
	}


	ItemIndex = 0;
	////////¿ä±â¼­´Â ÀÌ³ðÀÌ Äù½ºÆ®´Â ¾ÈÇÏ°í ·¾¾÷¸¸Çß´ÂÁö È®ÀÎÇÑ´Ù
	if(sinQuest_ChangeJob3.CODE && !CheckQuestItemDownFlag){
		ItemIndex = cInvenTory.SearchItemIndex(0,ITEM_KIND_QUEST_WEAPON);
		if(ItemIndex){
			if(sinChar->Level > sinQuest_ChangeJob3.StartLevel+2){
				sinQuest_ChangeJob3.StartLevel  = sinChar->Level;
				CheckQuestItemDownFlag = 1;
			}
		}
	}

	if(sinChar->ChangeJob >= 1 ){
		DeleteQuestItem((sinQT1|sin01)); //ºÒÇÊ¿äÇÑ Äù½ºÆ® ¾ÆÀÌÅÛÀ» Áö¿öÁØ´Ù
		DeleteQuestItem((sinQT1|sin02));
		DeleteQuestItem((sinQT1|sin03));
		DeleteQuestItem((sinQT1|sin04));
		DeleteQuestItem((sinQT1|sin05));
	}
	if(sinChar->ChangeJob >= 2 && !sinQuest_ChangeJob3.CODE){ //¸µ°ú ¹ìÇÁ°¡ ÀÖÀ»°æ¿ì Áö¿öÁØ´Ù
		DeleteQuestItem((sinQT1|sin06));
		DeleteQuestItem(sinOR2|sin02);
		DeleteQuestItem(sinOR2|sin03);
		DeleteQuestItem(sinOR2|sin04);

	}
	return TRUE;
}



/*----------------------------------------------------------------------------*
*					·¹º§ Äù½ºÆ®
*-----------------------------------------------------------------------------*/	
/*
#define SIN_QUEST_CODE_LEVEL30			0x0005
#define SIN_QUEST_CODE_LEVEL55			0x0006
#define SIN_QUEST_CODE_LEVEL70			0x0007
#define SIN_QUEST_CODE_LEVEL80			0x0008

sQUEST_CHANGEJOB3   sinQuest_Level30;
sQUEST_CHANGEJOB3   sinQuest_Level55;
sQUEST_CHANGEJOB3   sinQuest_Level55_2;
sQUEST_CHANGEJOB3   sinQuest_Level70;
sQUEST_CHANGEJOB3   sinQuest_Level80;
*/

//Äù½ºÆ®¸¦ ¹ÞÀ»¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
int sinCheckLevelQuest30()
{
	if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL30))return FALSE;
	if(sinChar->Level >= 30 && (sinQuest_levelLog & QUESTBIT_LEVEL_30) == 0){
		switch(sinQuest_Level30.State){
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest30Doc[0]);  
			break;
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest30Doc[1]);  
			break;
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest30Doc[2]);  
			break;

		}
	}
	
	return TRUE;
}

//Äù½ºÆ®¸¦ ¹ÞÀ»¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
int sinCheckLevelQuest55()
{  
	if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(sinQuest_ChangeJob.CODE|| sinQuest_ChangeJob2.CODE || sinQuest_ChangeJob3.CODE || sinQuest_ChangeJob4.CODE )return FALSE; //¸Þ¼¼Áö°¡ Áßº¹À¸·Î ¶äÀ¸·Î Ã¼Å© 
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL55))return FALSE;
	if(sinChar->Level >= 55 && (sinQuest_levelLog & (QUESTBIT_LEVEL_30 |QUESTBIT_LEVEL_55)) == QUESTBIT_LEVEL_30){
		switch(sinQuest_Level55.State){
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest55Doc[0]);  
			break;
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest55Doc[1]);  
			break;
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest55Doc[2]);  
			break;

		}
		
	}
	return TRUE;
}

//Äù½ºÆ®¸¦ ¹ÞÀ»¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
int sinCheckLevelQuest55_2()
{
	if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(sinQuest_ChangeJob.CODE|| sinQuest_ChangeJob2.CODE || sinQuest_ChangeJob3.CODE || sinQuest_ChangeJob4.CODE )return FALSE; //¸Þ¼¼Áö°¡ Áßº¹À¸·Î ¶äÀ¸·Î Ã¼Å© 
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL55_2))return FALSE;
	if(sinChar->Level >= 55 && (sinQuest_levelLog & (QUESTBIT_LEVEL_30 |QUESTBIT_LEVEL_55)) == QUESTBIT_LEVEL_30){
		switch(sinQuest_Level55_2.State){
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest55_2Doc[0]);  
			break;
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest55_2Doc[1]);  
			break;
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest55_2Doc[2]);  
			break;

		}
		
	}
	return TRUE;
}

// quest diaria xxstr
int sinCheckDailyQuest()
{
	if(!chaQuest.haQuestCheck())
		return FALSE;

	switch(sinQuest_Daily.State){
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_DAILYQUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),DailyQuestDoc[0]);  
		break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_DAILYQUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),DailyQuestDoc[1]);  
		break;
		case 2:
			sinQuest_Daily.State = 3;
			cSinHelp.sinShowHelp(SIN_HELP_DAILYQUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),DailyQuestDoc[2]);  
			
			//Finish Date
			smTRANS_COMMAND pck;
			pck.code = 0x43550005;
			pck.WParam = sinQuest_Daily.CODE;
			pck.size = sizeof( pck );

			if ( smWsockDataServer ) 
				smWsockDataServer->Send( (char *)&pck , pck.size , TRUE );

			if( sinQuest_Daily.CODE == 435501 )
			{
				//cMessageBox.ShowMessageEvent("You have earned 5,000,000,000 EXP as a reward!" );
				cMessageBox.ShowMessageEvent("You got an Celesto sheltom as reward!"); // 80
				cMessageBox.ShowMessageEvent("The reward was send to the Item Distributor!"); // 80 msg
				bcanadd = true;
				//AddExp( 10000000000 );
				//AddExp( 10000000000 );

				SaveGameData();
			}
			else if( sinQuest_Daily.CODE == 435502 )
			{
				//cMessageBox.ShowMessageEvent("You have earned 15,000,000,000 EXP as a reward!");
				cMessageBox.ShowMessageEvent("You got an Mirage sheltom as reward!"); //90
				cMessageBox.ShowMessageEvent("The reward was send to the Item Distributor!"); // 90 msg
				bcanadd = true;
				//AddExp(30000000000);
				//AddExp(30000000000);
				SaveGameData();
			}
			else if( sinQuest_Daily.CODE == 435503 )// quest 100 or 3% for all
			{
				//cMessageBox.ShowMessageEvent("You have earned 30,000,000,000 EXP as a reward!");
				cMessageBox.ShowMessageEvent("You got an Inferna sheltom as reward!"); // 100 msg
				cMessageBox.ShowMessageEvent("The reward was send to the Item Distributor!"); // 100 msg
				bcanadd = true;
				//AddExp(30000000000);
				//AddExp( 150000000000 );

				SaveGameData();
			}

			break;
		case 3:
			cSinHelp.sinShowHelp(SIN_HELP_DAILYQUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),DailyQuestDoc[3]);  
			break;
		
	}
	return TRUE;
}

//Äù½ºÆ®¸¦ ¹ÞÀ»¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
int sinCheckLevelQuest70()
{
	if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL70))return FALSE;
	if(sinChar->Level >= 70 && (sinQuest_levelLog & (QUESTBIT_LEVEL_55 |QUESTBIT_LEVEL_70)) == QUESTBIT_LEVEL_55){
		switch(sinQuest_Level70.State){
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest70Doc[0]);  
			break;
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest70Doc[1]);  
			break;
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest70Doc[2]);  
			break;

		}
	}
	return TRUE;
}

//Äù½ºÆ®¸¦ ¹ÞÀ»¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
int sinCheckLevelQuest80()
{
	if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL80))return FALSE;
	if(sinChar->Level >= 80 && (sinQuest_levelLog & (QUESTBIT_LEVEL_70 |QUESTBIT_LEVEL_80)) == QUESTBIT_LEVEL_70){
		switch(sinQuest_Level80.State){
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest80Doc[0]);  
			break;
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest80Doc[1]);  
			break;
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest80Doc[2]);  
			break;

		}

	}
	return TRUE;
}

//Äù½ºÆ®¸¦ ¹ÞÀ»¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
int sinCheckLevelQuest85()
{
	if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL85))return FALSE;
	if(sinChar->Level >= 85 && (sinQuest_levelLog & (QUESTBIT_LEVEL_80 |QUESTBIT_LEVEL_85)) == QUESTBIT_LEVEL_80){
		switch(sinQuest_Level85.State){
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest85Doc[0]);  
			break;
			case 1: //»ç¸Á½Ã ¸Þ¼¼Áö¿Í ÇÔ²² ¾ÆÀÌÅÛÀ» ´Ù½ÃÁØ´Ù
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest85Doc[1]);  				
			break;
			case 2: 
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest85Doc[2]);   
			break;
			case 3:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest85Doc[3]);  
			break;

		}

	}

	return TRUE;
}

int sinCheckQuest85Die()
{
	//85Äù½ºÆ®
	if(sinQuest_Level85.CODE && sinQuest_Level85.State){
		sinQuest_Level85.State = 1;
		DeleteQuestItem(sinQT1|sin08);

	}
	//90_2Äù½ºÆ®
	if(sinQuest_Level90_2.CODE && sinQuest_Level90_2.State == 2){
		sinQuest_Level90_2.State = 1;
		sinQuest_Level90_2.Monster[0] = 0;
		sinQuest_Level90_2.Monster[1] = 0;
		sinQuest_Level90_2.Kind = 0;
		cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_90_2_MON);
		cInvenTory.SetItemToChar();
		SetQuestBoard();

	}
	return TRUE;
}

//Äù½ºÆ®¸¦ ¹ÞÀ»¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
int sinCheckLevelQuest90()
{
	if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL90))return FALSE;
	if(sinChar->Level >= 90 && (sinQuest_levelLog & (QUESTBIT_LEVEL_85 |QUESTBIT_LEVEL_90)) == QUESTBIT_LEVEL_85){
		switch(sinQuest_Level90.State){
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest90Doc[0]);  
			break;
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest90Doc[1]);  
			break;
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest90Doc[2]);  
			break;

		}
	}

	return TRUE;
}

//Äù½ºÆ®¸¦ ¹ÞÀ»¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
int sinCheckLevelQuest80_2(int NpcNum) //µ¥·Ð 0 ¹Ì´º·»1
{
	if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL80_2))return FALSE;   
	if((sinQuest_levelLog & QUESTBIT_LEVEL_80_2) == QUESTBIT_LEVEL_80_2)return FALSE;
	if(sinQuest_Level80_2.State >= 5)return FALSE; 
	if(sinChar->Level >= 80){
		switch(sinQuest_Level80_2.State){
			case 0:
				if(NpcNum)break; //µ¥·Ð¿¡¼­ ¹Ì´º·»À¸·Î ³Ñ¾î°¨
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest80_2Doc[0]);  
			break;
			case 1:
				if(!NpcNum)break; //µ¥·Ð¿¡¼­ ¹Ì´º·»À¸·Î ³Ñ¾î°¨
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest80_2Doc[1]);  
			break;
			case 2:
				if(!NpcNum)break; //µ¥·Ð¿¡¼­ ¹Ì´º·»À¸·Î ³Ñ¾î°¨
				if(sinCheckLevelQuest80_2Item()){  //¹ìÇÁ¸¦ ´Ù±¸ÇØ¿ÔÀ¸¸é Àç±ÍÈ£ÃâÇÑ´Ù
					sinSetSendItem80_2();
					sinQuest_Level80_2.State = 3;
					sinCheckLevelQuest80_2(1);
				}
				else cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest80_2Doc[2]);  
			break;
			case 3:
				if(!NpcNum)break; //µ¥·Ð¿¡¼­ ¹Ì´º·»À¸·Î ³Ñ¾î°¨
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest80_2Doc[3]);  
			break;
			case 4:
				if(NpcNum)break; //´Ù½Ã µ¥·ÐÀ¸·Î 
				if(cInvenTory.SearchItemCode(sinQT1|sin12)){
					cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest80_2Doc[4]);  
				}
			break;

		}
	}

	return TRUE;
}

int sinCheckLevelQuest80_2Item()
{
	if(cInvenTory.SearchItemCode(sinQT1|sin09) &&
		cInvenTory.SearchItemCode(sinQT1|sin10) &&
		cInvenTory.SearchItemCode(sinQT1|sin11))
		return TRUE;
	return FALSE;
}
//¼­¹ö·Î ½©ÅÒÄÚµå¸¦ º¸³½´Ù
int sinSetSendItem80_2()	
{
	sITEM *pItem=0;  
	int   Count = 0;
	int   i = 0;
	int   TempItemIndex[3] = {0,0,0};
	short TempItemIndex2[4] = {0,};
	memset(&sWingItem_Send,0,sizeof(sCRAFTITEM_SERVER)); //ÃÊ±âÈ­
	for( i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else{
			if(!cInvenTory.InvenItemTemp[i-100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i-100];
		}
		//¿©±â¼­´Â ÀÏ´Ü ½©ÅÒ¸¸À» Ã¼Å©ÇÑ´Ù
		switch(pItem->sItemInfo.CODE){
			case (sinQT1|sin09):
				if(sWingItem_Send.SheltomCode[0])break;
				sWingItem_Send.SheltomCode[0] =  pItem->sItemInfo.CODE;
				sWingItem_Send.Head[0] =  pItem->sItemInfo.ItemHeader.Head;
				sWingItem_Send.CheckSum[0] =  pItem->sItemInfo.ItemHeader.dwChkSum;
			break;
			case (sinQT1|sin10):
				if(sWingItem_Send.SheltomCode[1])break;
				sWingItem_Send.SheltomCode[1] =  pItem->sItemInfo.CODE;
				sWingItem_Send.Head[1] =  pItem->sItemInfo.ItemHeader.Head;
				sWingItem_Send.CheckSum[1] =  pItem->sItemInfo.ItemHeader.dwChkSum;

			break;
			case (sinQT1|sin11):
				if(sWingItem_Send.SheltomCode[2])break;
				sWingItem_Send.SheltomCode[2] =  pItem->sItemInfo.CODE;
				sWingItem_Send.Head[2] =  pItem->sItemInfo.ItemHeader.Head;
				sWingItem_Send.CheckSum[2] =  pItem->sItemInfo.ItemHeader.dwChkSum;

			break;

		}
	}
	return TRUE;
}

//½ºÅÝ +10 90Äù½ºÆ®
int sinCheckLevelQuest90_2(int NpcNum) //µ¥¸¯ 0 ·Î¿­¸ÞÀÌÁö 1
{
	if(NpcNum == 0)
		if(!chaQuest.haQuestCheck())return FALSE; //ÇöÀç HaQuest Äù½ºÆ® °¡ ÁøÇàÁßÀÌ¸é
	if(!CheckNowQuestState(SIN_QUEST_CODE_LEVEL90_2))return FALSE;   
	if((sinQuest_levelLog & QUESTBIT_LEVEL_90_2) == QUESTBIT_LEVEL_90_2)return FALSE;
	if(sinChar->Level >= 90){
		switch(sinQuest_Level90_2.State){
			case 0:
				if(NpcNum)break; //µ¥¸¯ÀÏ°æ¿ì¿¡¸¸ ¼öÇà
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest90_2Doc[0]);
			break;
			case 1:
				if(!NpcNum)break; //·Î¿­¸ÞÀÌÁö
				if(!sinQuest_Level90_2.Kind){ //¸ó½ºÅÍ 3Á¾·ùÁß ·£´ý ¼±ÅÃµÈ´Ù
					sinQuest_Level90_2.Kind = GetRandomPos(1,3);
					sinQuest_Level90_2.Monster[1] = 50; //ÀâÀ» ¸ó½ºÅÍ¼ö
				}
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest90_2Doc[1]);
			break;
			case 2:
				if(!NpcNum){
					cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest90_2Doc[2]);
				}
				else{
					cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest90_2Doc[3]);
				}
			break;
			case 3:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),LevelQuest90_2Doc[4]);
			break;

		}

	}
	return TRUE;
}

void *pQuestCode[] = { //voidÇü Æ÷ÀÎÅÍ·Î ¹è¿­À» Àâ´Â´Ù 
  &sinQuest_ChangeJob,
  &sinQuest_ChangeJob2,
  &sinQuest_ChangeJob3,
  &sinQuest_Level30,
  &sinQuest_Level55,
  &sinQuest_Level55_2,
  &sinQuest_Level70,
  &sinQuest_Level80,
  &sinQuest_Level85,
  &sinQuest_Level90,
  &sinQuest_Level80_2,
  &sinQuest_Level90_2,
  &sinQuest_ChangeJob4,
  0,
};

struct QuestCodeFlag{
	DWORD	CODE;
};

//ÇöÀç ÁøÇàÁßÀÎ Äù½ºÆ®°¡ ÀÖ³ª¸¦ È®ÀÎÇÑ´Ù
int CheckNowQuestState(DWORD CODE)
{
	int cnt = 0;
	while(1){
		if(pQuestCode[cnt] == 0)break;
		if(((QuestCodeFlag *)pQuestCode[cnt])->CODE && ((QuestCodeFlag *)pQuestCode[cnt])->CODE !=CODE ){
			cMessageBox.ShowMessage(MESSAGE_QUEST_NOW_EXIT);
			return FALSE;

		}
		cnt++;
	}
	return TRUE;
}

//ÇöÀç ÁøÇàÁßÀÎ Äù½ºÆ®¸¦ ÃÊ±âÈ­ÇÑ´Ù (»ç¿ë¾ÈÇÔ)
int ClearNowQuest()
{
	int cnt = 0;
	while(1){
		if(pQuestCode[cnt] == 0)break;
		if(((QuestCodeFlag *)pQuestCode[cnt])->CODE){
			((QuestCodeFlag *)pQuestCode[cnt])->CODE = 0;
			return FALSE;

		}
		cnt++;
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*					4Â÷½ºÅ³ Àü¾÷Äù½ºÆ®
*-----------------------------------------------------------------------------*/	

int sinChangeJob4MonCode[][2] ={
	{MONSTER_MURPIN,MONSTER_SKELETON_KNIGHT },
	{MONSTER_HEAD_CUTTER,MONSTER_SOLID_SNAIL},
	{MONSTER_THORN_CROWLER,MONSTER_MUMMY},
	{MONSTER_DOOM_GUARD ,MONSTER_FIGON},
	{MONSTER_STONE_GIANT,MONSTER_STONE_COLEM},
	{MONSTER_IRON_GUARD,MONSTER_AVELLRIN},
};
int sinChangeJob4MonCode2[][2] = {
	{MONSTER_AVELRISK_L,MONSTER_BEEBUL},
	{MONSTER_ILLUSION_KNIGHT,MONSTER_NIGHT_MARE },
	{MONSTER_WITCH,MONSTER_HEAVY_GOBLIN},
	{MONSTER_DAWLIN ,MONSTER_STYGIAN},
	{MONSTER_INCUBUS,MONSTER_CHAIN_GOLEM},
	{MONSTER_DARK_SPECTOR,MONSTER_METRON},
};
int sinChangeJob4MonCode3[] = {
	MONSTER_SOLID_SNAIL,
	MONSTER_ILLUSION_KNIGHT,
	MONSTER_AVELRISK_LOAD,
	MONSTER_DUSK,
	MONSTER_CHAIN_GOLEM ,
	MONSTER_SADNESS
};

//ÄÚµå¿¡ ÇØ´çÇÏ´Â ¸ó½ºÅÍÀÇ ÀÌ¸§À» ¸®ÅÏÇÑ´Ù
char *sinGetMonsterName(int CODE)
{

	return sinMonCodeName[CODE];
}

int QuestLevelTable[7] = {60,65,70,75,80,85,200};
char szQuestMonsterName[64];
int sinChangeJob4MonSet(sQUEST_CHANGEJOB3 *pQuset)
{
	
	int QuestLevel = 0;
	char szBuff[128];
	//·¹º§À» Ã¼Å©ÇÑ´Ù
	for(int i = 0; i < 6 ; i++){
		if( sinChar->Level >=QuestLevelTable[i] && sinChar->Level < QuestLevelTable[i+1])
			QuestLevel = i;
	}
	int RandomIndex = 0;
	switch(pQuset->State){
		case 1:
			RandomIndex = GetRandomPos(0,1);
			if(QuestLevel<4)
				pQuset->Monster[1] = 50; 
			else pQuset->Monster[1] = 30; 
			pQuset->Kind = sinChangeJob4MonCode[QuestLevel][RandomIndex];
			lstrcpy(szQuestMonsterName ,sinGetMonsterName(pQuset->Kind));

#ifdef	_LANGUAGE_ENGLISH
			wsprintf(szBuff,sinLevelQusetDoc2,pQuset->Monster[1],szQuestMonsterName);
#else
//Áß±¹
#ifdef	_LANGUAGE_CHINESE
			wsprintf(szBuff,sinLevelQusetDoc2,pQuset->Monster[1],szQuestMonsterName);
#else
#ifdef  _LANGUAGE_BRAZIL
			wsprintf(szBuff,sinLevelQusetDoc2,pQuset->Monster[1],szQuestMonsterName);
#else
#ifdef  _LANGUAGE_ARGENTINA
			wsprintf(szBuff,sinLevelQusetDoc2,pQuset->Monster[1],szQuestMonsterName);
#else
			wsprintf(szBuff,sinLevelQusetDoc2,szQuestMonsterName , pQuset->Monster[1]);
#endif
#endif
#endif
#endif

			cMessageBox.ShowMessageEvent(szBuff);
			sinSetQuestTimer(pQuset);
		break;
		case 2:
			RandomIndex = GetRandomPos(0,1);
			if(QuestLevel<4)
				pQuset->Monster[1] = 50; 
			else pQuset->Monster[1] = 30; 
			pQuset->Kind = sinChangeJob4MonCode2[QuestLevel][RandomIndex];
			lstrcpy(szQuestMonsterName ,sinGetMonsterName(pQuset->Kind));
#ifdef	_LANGUAGE_ENGLISH
			wsprintf(szBuff,sinLevelQusetDoc2, pQuset->Monster[1],szQuestMonsterName);
#else
//Áß±¹
#ifdef	_LANGUAGE_CHINESE
			wsprintf(szBuff,sinLevelQusetDoc2, pQuset->Monster[1],szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
			wsprintf(szBuff,sinLevelQusetDoc2, pQuset->Monster[1],szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
			wsprintf(szBuff,sinLevelQusetDoc2, pQuset->Monster[1],szQuestMonsterName);
#else
			wsprintf(szBuff,sinLevelQusetDoc2,szQuestMonsterName , pQuset->Monster[1]);
#endif
#endif
#endif
#endif
			cMessageBox.ShowMessageEvent(szBuff);
			sinSetQuestTimer(pQuset);
		break;
		case 4:
			pQuset->Kind = sinChangeJob4MonCode3[QuestLevel];
			lstrcpy(szQuestMonsterName ,sinGetMonsterName(pQuset->Kind));
			wsprintf(szBuff,sinLevelQusetDoc3,szQuestMonsterName);
			cMessageBox.ShowMessageEvent(szBuff);
		break;
	}
	

	return TRUE;

}
int sinCheckChangeJobQuest4()
{
	if(!CheckNowQuestState(SIN_QUEST_CODE_CHANGEJOB4))return FALSE;   
	if(sinQuest_ChangeJob4.CODE && sinChar->Level >= 60){
		switch(sinQuest_ChangeJob4.State){
			case 0:
				if(sinQuest_ChangeJob4.Monster[1])
					cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[0]);  
			break;
			case 1:
				if(sinQuest_ChangeJob4.Monster[0] ==  sinQuest_ChangeJob4.Monster[1] ){
					sinQuest_ChangeJob4.State = 2;
					sinCheckChangeJobQuest4();//Àç±ÍÈ£Ãâ
					SetQuestBoard();
				}
				else{
					cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[1]);  
				}
			break;
			case 2:
				if(CSKILL->SearchContiueSkill(CHANGE_JOB3_QUEST)){
					CSKILL->CancelContinueSkill(CHANGE_JOB3_QUEST);
					sinQuest_ChangeJob4.Monster[0] = 0;
					sinQuest_ChangeJob4.Monster[1] = 0;
					sinQuest_ChangeJob4.Kind = 0;

				}
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[2]);  
			break;
			case 3:
				if(sinQuest_ChangeJob4.Monster[0] ==  sinQuest_ChangeJob4.Monster[1] ){
					sinQuest_ChangeJob4.State = 4;
					sinCheckChangeJobQuest4();//Àç±ÍÈ£Ãâ
					SetQuestBoard();
				}
				else{
					cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[3]);  
				}
			break;
			case 4:
			case 7:
				if(CSKILL->SearchContiueSkill(CHANGE_JOB3_QUEST)){
					CSKILL->CancelContinueSkill(CHANGE_JOB3_QUEST);
					sinQuest_ChangeJob4.Monster[0] = 0;
					sinQuest_ChangeJob4.Monster[1] = 0;
					sinQuest_ChangeJob4.Kind = 0;

				}
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[4]);  
			break;
			case 5:
				if(cInvenTory.SearchItemCode(sinQT1|sin13)){
					sinQuest_ChangeJob4.State = 6;
					sinCheckChangeJobQuest4();//Àç±ÍÈ£Ãâ
					SetQuestBoard();
				}
				else{
					cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[5]);  
				}
			case 6:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[6]);  
			break;
			case 8:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[7]);  
			break;
		}
	}
	return TRUE;
}

//Äù½ºÆ® Å¸ÀÌ¸Ó¸¦ Ç¥½ÃÇÑ´Ù
int sinSetQuestTimer(sQUEST_CHANGEJOB3 *pQuset , int UseTime , int CheckTime)
{

	sSKILL TempSkill;
	memset(&TempSkill,0,sizeof(sSKILL)); 
	//ÅØ½ºÃÄ ·Îµù
	char *Path = "image\\Sinimage\\skill\\keep\\QuestTimer.tga";      
	if(!MatQuestTimer){
		MatQuestTimer = CreateTextureMaterial(Path, 0, 0, 0,0, SMMAT_BLEND_ALPHA );
		ReadTextures();	//ÅØ½ºÃÄ ·Îµù
	}

	TempSkill.CODE = CHANGE_JOB3_QUEST; 
	TempSkill.UseTime = 70*70;
	if(UseTime)TempSkill.UseTime = UseTime;
	if(CheckTime)TempSkill.CheckTime = CheckTime;
	TempSkill.Point = 1;
	TempSkill.MatIcon = MatQuestTimer;
	sinContinueSkillSet(&TempSkill);
	sinPlaySound(SIN_SOUND_EAT_POTION2);//´ë¹Ú »ç¿îµå
	return TRUE;
}

//npc¿ÍÀÇ °áÀü¿¡¼­ÀÇ ½ÂºÎ°á°ú¸¦ ¹Þ´Â´Ù
int sinBattleNpcResult(int WinFlag)
{
	if(WinFlag){
		sinQuest_ChangeJob4.State = 8;
		SetQuestBoard();
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[7]);  
	}
	else{
		sinQuest_ChangeJob4.State = 4;
		SetQuestBoard();
	
	}
	return TRUE;
}

//4Â÷½ºÅ³À» ÀÓÀÇKey·Î ¼ÂÆÃÇÑ´Ù
int sinCompleteChangeJob4(int Index)
{
	//ÇöÀç Äù½ºÆ® À¯Áö¹öÆ°Àº ´Ù Áö¿öÁØ´Ù.
	if(CSKILL->SearchContiueSkill(CHANGE_JOB3_QUEST)){
			CSKILL->CancelContinueSkill(CHANGE_JOB3_QUEST);
			sinQuest_ChangeJob4.Monster[0] = 0;
			sinQuest_ChangeJob4.Monster[1] = 0;
			sinQuest_ChangeJob4.Kind = 0;

	}
	switch(Index){
		case 1: //Ã¹¹øÂ° ´Ü°è (½Ã°£³»¿¡ »ç³É)
			if(sinQuest_ChangeJob4.State==8)break;
			sinQuest_ChangeJob4.CODE  = SIN_QUEST_CODE_CHANGEJOB4;
			StartQuest_Code(sinQuest_ChangeJob4.CODE);
			
		
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[0]);
			sinQuest_ChangeJob4.State = 1;
			SetQuestBoard();
			sinChangeJob4MonSet(&sinQuest_ChangeJob4); //¸ó½ºÅÍ¸¦ ¼ÂÆÃÇÑ´Ù
			SaveGameData();
		break;
		case 2: //µÎ¹øÂ° ´Ü°è  (½Ã°£³»¿¡ »ç³É)
			if(sinQuest_ChangeJob4.State==8)break;
			sinQuest_ChangeJob4.CODE  = SIN_QUEST_CODE_CHANGEJOB4;
			StartQuest_Code(sinQuest_ChangeJob4.CODE); 
			
			sinQuest_ChangeJob4.State = 2;
			sinCheckChangeJobQuest4();
			SaveGameData();
		break;
		case 3: //¼¼¹øÂ° ´Ü°è (¾ÆÀÌÅÛ È¹µæ)
			if(sinQuest_ChangeJob4.State==8)break;
			sinQuest_ChangeJob4.CODE  = SIN_QUEST_CODE_CHANGEJOB4;
			StartQuest_Code(sinQuest_ChangeJob4.CODE); 
			
			sinQuest_ChangeJob4.State = 3;
			sinCheckChangeJobQuest4();
			SaveGameData();
		break;
		case 4: //º£¸£Ä­ ÀÌ±â±â & ¾ó±¼¹Ù²Ù°í ,Àü¾÷
			if(sinQuest_ChangeJob4.State==8)break;
			sinQuest_ChangeJob4.CODE  = SIN_QUEST_CODE_CHANGEJOB4;
			StartQuest_Code(sinQuest_ChangeJob4.CODE);
			
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0,15,128,125),QuestFilePath4[7]);  
			sinQuest_ChangeJob4.State = 8;
			SetQuestBoard();
			SaveGameData();
		break;
	}
	return TRUE;
}


