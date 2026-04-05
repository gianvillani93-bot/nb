#pragma once

#define MAX_TRADE_ITEM			20
#define MAX_CRAFTITEM_INFO		300
#define MAX_AGINGITEM_INFO		100
#define MAX_MAKEITEM_INFO		100

#define T_SET_BOX				0
#define T_MONEY_POSI			1
#define T_MONEY_TEXT_POSI		2
#define T_WEIGHT_TEXT_POSI		3
#define T_CHECK_POSI			4
#define T_CLOSE_POSI			5
#define T_TRADE_CLOSE_POSI		6
#define T_COIN_POSI				7
#define T_COIN_TEXT_POSI		8

#define MAX_SHELTOM				19
#define MAX_AGING				20 // Nível do Aging aqui máximo
#define MAX_RUNE				14
#define MAX_RECIPE_KIND			11
#define MAX_RECIPE_ITEM			60
#define MAX_HANDMADEITEM		176

#define MAX_SEEL_COUNT			12


struct sTRADE{
	sITEM TradeItem[MAX_TRADE_ITEM];
	int Money;	
	int Coin;
	int Weight;
	int CheckFlag;
	int CheckMoney;
};

///////Ã¢°í ±¸Á¶Ã¼ 
struct sWAREHOUSE{
	sITEM WareHouseItem[100]; 
	int Money;
	short Weight[2];
	int BuyAreaCount; //Ã¢°í¸¦ ¾ó¸¶¸¸Å­ »ç°ÔµÇ¾ú³ª 
	int FakeMoney;


};

struct sCARAVAN 
{
	sITEM CaravanItem[100];
	int Money;
	short Weight[2];
	int BuyAreaCount;
	int FakeMoney;
};

struct sCRAFTITEM{
	sITEM CraftItem[15];
	int   SheltomIndex[12];

};

struct sCRAFTITEM_SERVER{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesCraftItem;
	DWORD SheltomCode[12];
	DWORD Head[12];
	DWORD CheckSum[12];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};

struct sCRAFTITEM_INFO{
	int iMixType;
	DWORD MainItemCode[8];
	int AddItem[15];
	int PlusElementCode[8];
	float AddElement[8];
	int ElementKind[8];
	char Doc[256];
};


struct sMIXTURE_RESET_ITEM
{
	sITEM	MixtureResetItem[2];

	sMIXTURE_RESET_ITEM()
	{
		ZeroMemory(&MixtureResetItem, sizeof(MixtureResetItem));
	}
};

struct sMIXTURE_RESET_ITEM_SERVER
{
	int		size, code;
	int		DocIndex;
	int		Result;
	int		Index;

	sITEM	DesMixtureResetItem;

	DWORD	dwMixtureResetStoneItemCode;
	DWORD	dwMixtureResetStoneHead;
	DWORD	dwMixtureResetStoneCheckSum;

	sMIXTURE_RESET_ITEM_SERVER()
	{
		size = 0;
		code = 0;
		DocIndex = 0;
		Result = 0;
		Index = 0;

		dwMixtureResetStoneItemCode = 0;
		dwMixtureResetStoneHead = 0;
		dwMixtureResetStoneCheckSum = 0;
	}

};

struct sAGINGITEM{
	sITEM AgingItem[15];
	int   SheltomIndex[12];
	int   AgingOkFlag;

	sAGINGITEM()
	{
		ZeroMemory(&AgingItem, sizeof(AgingItem));
	}

};

struct sAGINGITEM_INFO{
	DWORD MainItemCode;		//Á¶ÇÕÇÒ ¾ÆÀÌÅÛ ÄÚµå 
	int PlusElementCode[8];	//Ãß°¡µÉ ¿äÀÎ 
	float AddElement[8];	//Ãß°¡µÈ ¼öÄ¡ 
	int ElementKind[8];		//¼öÄ¡ÀÇ ±âÁØ (+ % ¼Ò¼ö)
	char Doc[128];			//¼³¸í 

	sAGINGITEM_INFO()
	{
		MainItemCode = 0;
		ZeroMemory(&PlusElementCode, sizeof(PlusElementCode));
		ZeroMemory(&AddElement, sizeof(AddElement));
		ZeroMemory(&ElementKind, sizeof(ElementKind));
		ZeroMemory(Doc, sizeof(Doc));
	}

};

///// MakeItem
struct sMAKEITEM_INFO{
	DWORD CODE[15];			//Á¶ÇÕµÇ´Â ¾ÆÀÌÅÛÀÇ ÄÚµå
	DWORD Result_CODE;		//Á¶ÇÕµÈ ¾ÆÀÌÅÛ ÄÚµå 

};

struct sPOSTBOX_ITEM{
	char	szName[64];
	DWORD	CODE;

	sPOSTBOX_ITEM()
	{
		ZeroMemory(szName, sizeof(szName));
		CODE = 0;
	}
};

//¾ÆÀÌÅÛ Àç±¸¼º ±¸Á¶Ã¼
struct sRECON_ITEM{
	DWORD  dwCODE;    //..
	int	   iLevel[2]; //min~max
	int	   iCount;    //ÇÊ¿ä ¼ö·®
	int    iPrice;    //°¡°İ?
};

// pluto Á¦·Ã
struct SSmeltingItem
{
	sITEM SmeltingItem[5];	//Á¶ÇÕµÉ ¾ÆÀÌÅÛ 
	int   SheltomIndex[12];
};

// pluto Á¦·Ã
struct sSMELTINGITEM_SERVER
{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesSmeltingItem;
	DWORD SmeltingCode[5];
	DWORD Head[5];
	DWORD CheckSum[5];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};

// pluto Á¦ÀÛ
struct SManufactureItem
{
	sITEM	ManufactureItem[4];
	int		RuneIndex[12];
};

// pluto Á¦ÀÛ
struct SManufactureItem_Server
{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesManufactureItem;
	DWORD RuneCode[4];
	DWORD Head[4];
	DWORD CheckSum[4];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};

// pluto Á¦ÀÛ
struct SManufacture_Rune
{
	int RecipeCode;
	int NeedRuneIndex[3];
};

// pluto Á¦ÀÛ ·é Á¶ÇÕ °ø½Ä ¸ÂÀ¸¸é ÇØ´ç ¾ÆÀÌÅÛ ÄÚµå ¹ß»ı
struct SManufacture_CreateItemCode
{
	DWORD RecipeKind[2];
	DWORD CheckRuneCode[8][3];
	DWORD CreateItemCode[2][8];
};

// pluto Á¦ÀÛ ¾ÆÀÌÅÛ ¹«°Ô, °¡°İ Á¤º¸
struct SManufacture_ResultItemInfo
{
	DWORD ItemCode;
	int	Weight;
	int Price;
	char ItemName[32];
};

// pluto Á¦ÀÛ ¾ÆÀÌÅÛ ¹«°Ô, °¡°İ Á¤º¸  // Àåº° - Á¦ÀÛ 160(144) // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
struct SManufacture_ResultItemInfo_Server
{
	smTRANS_COMMAND		smTransCommand;
	DWORD ItemCode[MAX_HANDMADEITEM];
	int Weight[MAX_HANDMADEITEM];
	int Price[MAX_HANDMADEITEM];
	char ItemName[MAX_HANDMADEITEM][32];
};
/*----------------------------------------------------------------------------*
*							¿¡ÀÌÂ¡  ¾ÆÀÌÅÛ Å¬·¡½º 
*-----------------------------------------------------------------------------*/
class cAGING{
public:

	int OpenFlag;
	int AgingItemCheckSum;
	LPDIRECT3DTEXTURE9	lpGraySheltom[MAX_SHELTOM];

public:
	//¿¡ÀÌÂ¡ ¿¡ »ç¿ëµÅ´Â Á¾·ù   //1.¿¡ÀÌÂ¡½ºÅæ 
	int  AginStoneKind;         //2.ÄÚÆÛ ¿À¾î
								//¹ÚÀç¿ø - 3.¿¤´õ ÄÚÆÛ ¿À¾î
								//¹ÚÀç¿ø - 4.½´ÆÛ ¿¡ÀÌÂ¡ ½ºÅæ
                                //Â÷ÈÄ Ãß°¡µÊ
	
public:

	int  AgingItem(int MakeItemFlag =0);		//¾ÆÀÌÅÛÀ» ¿¡ÀÌÂ¡ÇÑ´Ù 
	int  CancelAgingItem(int Flag=0);	//¿¡ÀÌÂ¡ ¾ÆÀÌÅÛÀ» Äµ½½ÇÑ´Ù 
	int  CheckItem(sITEM *pItem);		//¿¡ÀÌÂ¡ÇÒ ¾ÆÀÌÅÛÀ» Ã¼Å©ÇÑ´Ù 
	int  CheckAgingItemOk(); //¿¡ÀÌÂ¡À» ÇÒ¼öÀÖ´ÂÁö¸¦ Ã¼Å©ÇÑ´Ù 

	int  SetAgingItemAreaCheck(sITEM *pItem );	//¿¡ÀÌÂ¡ ¾ÆÀÌÅÛÀÌ ¼ÂÆÃµÉ °ø°£À» Ã¼Å©ÇÑ´Ù 
	
	///////////// ¿¡ÀÌÂ¡ µ¥ÀÌÅÍÀÇ Á¶ÀÛ¿©ºÎ¸¦ °¡¸°´Ù 
	int  CheckAgingData();

	/////////// ¼­¹ö¿¡¼­ ¾ÆÀÌÅÛÀ» ¿¡ÀÌÂ¡ÇÑ´Ù
	int sinSendAgingItem();
	int sinRecvAgingItem(sCRAFTITEM_SERVER *pCraftItem_Server);
	int sinRecvAgingItemResult(sCRAFTITEM_SERVER *pCraftItem_Server);

	//new functions aging xxstr
	bool isSheltomAreaEmpty(sITEM* Item, int Area);
	bool isAgeableItem(sITEM * pItem);
	bool isItemAreaEmpty();
	bool isStoneAreaEmpty();

};

/*----------------------------------------------------------------------------*
*						¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Å¬·¡½º 
*-----------------------------------------------------------------------------*/
class cMIXTURERESET
{
public:

	int	OpenFlag;					// ¿­·ÁÀÖ´Â°¡?
	int	MixtureResetItemCheckSum;	// °Ë»ç¿ë
	int	HaveMixtureResetStone;		// ¹Í½ºÃÄ ¸®¼Â ½ºÅæÀÌ ÀÖ´Â°¡?

public:

	int	SetMixtureItemResetAreaCheck(sITEM *pItem);		// ¹Í½ºÃÄ ¸®¼ÂµÉ ¾ÆÀÌÅÛÀÇ ¿µ¿ªÀ» Ã¼Å©ÇÑ´Ù.
	int PickUpMixtureResetItem( int x, int y, int PickUpFlag = 0, int Kind = 0 );	// ¹Í½ºÃÄ ¸®¼Â ¾ÆÀÌÅÛÀ» ¼±ÅÃÇÑ´Ù.
	int LastSetMixtureResetItem( sITEM *pItem, int kind );	// ¹Í½ºÃÄ ¸®¼Â¿¡ ÇÊ¿äÇÑ ¾ÆÀÌÅÛ ³õ´Â´Ù
	int	CancelMixtureItemReset(int Flag=0);		// ¹Í½ºÃÄ ¸®¼ÂÀ» Ãë¼ÒÇÏ¸ç Ã¢À» ´İ´Â´Ù.
	int	CheckMixtureResetItemForm();	// ¾ÆÀÌÅÛ Ã¼Å©?
	int	ReformMixtureResetItem();		// ¾ÆÀÌÅÛ ´Ù½Ã Ã¼Å©?


	bool cMIXTURERESET::isStoneOkay(sITEM* pItem);
	bool cMIXTURERESET::isItemOkay(sITEM* pItem);
	bool cMIXTURERESET::isEmpty(int Index);

	int	MixtureItemReset();	
	int	CheckItem();
	int	CheckMixtureItemResetOk();
	int	CheckMixtureItemData();	



	int	sinSendMixtureItemReset();			// ¼­¹ö·Î ¹Í½ºÃÄ¸®¼ÂÇÒ ¾ÆÀÌÅÛÀ» Àü¼Û
	int	sinRecvMixtureItemReset(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem);		// ¹Í½ºÃÄ ¸®¼ÂµÈ ¾ÆÀÌÅÛÀ» Recv¿ë º¯¼ö·Î º¹»ç
	int	sinRecvMixtureItemResetResult(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server);
};

// pluto
/*----------------------------------------------------------------------------*
*								¾ÆÀÌÅÛ Á¦·Ã Å¬·¡½º 
*-----------------------------------------------------------------------------*/
class CSmeltingItem
{
public:
	int OpenFlag;
	int SmeltingItemCheckSum;
	int m_SmeltingPrice;
public:
	int CancelSmeltingItem();
	int SetSmeltingItemAreaCheck( sITEM *pItem, int Kind = 0 );
	int LastSetSmeltingItem( sITEM *pItem, int Kind = 0);
	int CheckSmeltingItemForm();
	int ReFormSmeltingItem();
	int PickUpSmeltingItem( int x, int y, int PickUpFlag = 0, int Kind = 0 );
	int sinSendSmeltingItem(); // ¼­¹ö¿¡ Á¦·Ã ¾ÆÀÌÅÛ º¸³½´Ù
	int sinRecvSmeltingItem( sSMELTINGITEM_SERVER *pSmeltingItem_Server ); // Á¦·Ã ¾ÆÀÌÅÛ ¹Ş´Â´Ù
	int sinRecvSmeltingItemResult( sSMELTINGITEM_SERVER *pSmeltingItem_Server );
	int SmeltingCheckEmptyArea( sITEM *pItem );
	int GetSmeltingCheckEmptyArea();
	int CheckSmeltingPrice();		// Á¦·Ã ºñ¿ë °Ë»ç
	int GetSheltomIndex( DWORD SmeltingItemCode ); // Á¦·Ã È¸»ö ÀÌ¹ÌÁö ½©ÅÒ
	bool CSmeltingItem::GetEmptyArea(POINT* Area);
	bool CSmeltingItem::isAreaEmpty(sITEM* pITEM, int Index);
};

/*----------------------------------------------------------------------------*
* pluto							¾ÆÀÌÅÛ Á¦ÀÛ Å¬·¡½º 
*-----------------------------------------------------------------------------*/

class CManufacture
{
public:
	int m_OpenFlag;
	int m_ManufactureItemCheckSum;
	int m_ManufacturePrice;
	LPDIRECT3DTEXTURE9 m_lpGrayRune[MAX_SHELTOM];
public:
	void RuneIndexInit();	// ÇÊ¿äÇÑ ·é È¸»ö ÀÌ¹ÌÁö
	int CancelManufactureItem(); // Á¦ÀÛ Ãë¼Ò
	int SetManufactureItemAreaCheck( sITEM *pItem ); // Á¦ÀÛ ¾ÆÀÌÅÛ µé¾î°¥ ÀÚ¸® °Ë»ç
	int LastSetManufactureItem( sITEM *pItem );		// Á¦ÀÛ ¾ÆÀÌÅÛ ³õ´Â´Ù
	int CheckManufactureItem();
	int ReFormManufactureItem();
	int PickUpManufactureItem( int x, int y, int PickUpFlag = 0 );
	int sinSendManufactureItem();	// ¼­¹ö·Î º¸³½´Ù
	int sinRecvManufactureItem( SManufactureItem_Server *pManufactureItem_Server );
	int RecvManufactureItemResult( SManufactureItem_Server *pManufactureItem_Server ); // ¼­¹ö¿¡¼­ ¹ŞÀº °á°ú
	int ManufactureCheckEmptyArea( sITEM *pItem );
	int GetRecipeIndex( DWORD Code ); // ·¹½ÃÇÇ ÀÎµ¦½º¸¦ °¡Á®¿Â´Ù
	int GetManufactureCheckEmptyArea();
	SManufacture_ResultItemInfo ManufactureCheckItem( sITEM *pItemCode, smCHAR_INFO *charInfo );	// Á¦ÀÛµÉ ¾ÆÀÌÅÛ ÄÚµå. ¹«°Ô °Ë»ç ÇÒ·Á°í // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
	bool CManufacture::GetEmptyArea(sITEM* pItem, POINT* Area);
	bool CManufacture::isAreaEmpty(int Index);
};

/*----------------------------------------------------------------------------*
*							Å©·¡ÇÁÆ® ¾ÆÀÌÅÛ Å¬·¡½º 
*-----------------------------------------------------------------------------*/
class cCRAFTITEM{
public:
	int OpenFlag;
	int CraftItemCheckSum;
	int ForceFlag;
	int ForceItemPrice;
	int iReconItemFlag;
public:

	int SetCraftItemAreaCheck(sITEM *pItem,int Kind=0); //¾ÆÀÌÅÛÀ» ¼ÂÆÃÇÑ´Ù 
	int LastSetCraftItem(sITEM *pItem,int Kind=0);
	int PickUpCraftItem(int x , int y , int PickUpFlag=0,int Kind=0); //¾ÆÀÌÅÛÀ» Áı°Å³ª Á¤º¸¸¦ º¸¿©ÁØ´Ù 

	//¾ÆÀÌÅÛÀ» Á¶ÇÕÇÑ´Ù 
	int MixingItem();

	//¾ÆÀÌÅÛ °ø°£À» Ã¼Å©ÇÑ´Ù 
	int CraftCheckEmptyArea(sITEM *pItem);
	int CancelMixItem(); //¹Í½ºÃÄ ¾ÆÀÌÅÛÀ» Ãë¼ÒÇÑ´Ù 

	int CheckHackCraftItem(); //Å©·¡ÇÁÆ® ¾ÆÀÌÅÛ Á¶ÀÛ ¹æÁö
	int CheckCraftItemForm(); //Á¶ÀÛÇÏ´Â »ó³ğÀÇ ÀÚ½ÄµéÀ» Á×¿©¹ö¸®ÀÚ Æ¡!!
	int ReFormCraftItem();    //Á¶ÀÛÇÏ´Â »ó³ğÀÇ ÀÚ½ÄµéÀ» Á×¿©¹ö¸®ÀÚ Æ¡!!

	int sinSendCraftItem();	  //¼­¹ö¿¡ ¹Í½ºÇÒ ¾ÆÀÌÅÛÀ» º¸³½´Ù 	
	int sinRecvCraftItem(sCRAFTITEM_SERVER *pCraftItem_Server);   //¼­¹ö¿¡¼­ ¹Í½ºÇÒ ¾ÆÀÌÅÛÀ» ¹Ş´Â´Ù 

	//¹Í½ºµÈ °á°ú¹°À» ¹Ş´Â´Ù 
	int sinRecvCraftItemResult(sCRAFTITEM_SERVER *pCraftItem_Server);

	//Force Orb ¾ÆÀÌÅÛÀÇ °¡°İÀ» Ã¼Å©ÇÑ´Ù
	int CheckForceOrbPrice();
	int CheckForceOrbPrice(sITEM *pItem);

	//¾ÆÀÌÅÛ Àç±¸¼º ½Ã½ºÅÛ
	int haCheckReconItem(); //¾ÆÀÌÅÛ Àç±¸¼º 
	int haSendReconItem();  //¾ÆÀÌÅÛ Àç±¸¼º À» ¼­¹ö·Î º¸³½´Ù.
	/*----------------------------------------------------------------------------*
	* ÀÛ¼ºÀÚ : ÇÏ´ë¿ë  			
	* Desc   : Ãß°¡µÅ´Â ÇÔ¼öµé  		
	*-----------------------------------------------------------------------------*/

	//ÀÎº£Åä¸® ºó°÷À» Ã¼Å©ÇÑ´Ù.
	int GetCraftCheckEmptyArea();
	//sorting function
	int haCraftSortItem(sCRAFTITEM *pCraftItem);

	// new functions mix xxstr
	bool isSheltomAreaEmpty(sITEM* Item, int Area);
	bool isMixableItem(sITEM* Item);

	bool isItemAreaEmpty();
	bool isStoneAreaEmpty();
};



/*----------------------------------------------------------------------------*
*								Ã¢°í Å¬·¡½º 
*-----------------------------------------------------------------------------*/

class cWAREHOUSE{
public:
	int OpenFlag;	//ÇÔ¼öÀÇ °ø¿ëÈ­¸¦ À§ÇØ ¾îÂ¿¼ö ¾øÀÌ Å¬·¡½º »ı¼º 
	int WareHouseCheckSum;

public:

	int SetWareHouseItemAreaCheck(sITEM *pItem); //°ø°£À» Ã¼Å©ÇÑ´Ù 
	int CrashWareHouseItem(RECT &desRect, int PassItemIndex=0); //¾ÆÀÌÅÛÀÌ °ãÃÄÁ³´ÂÁö¸¦ Ã£´Â´Ù 
	int ChangeWareHouseItem(sITEM *pItem); //°ãÃÄÁø ¾ÆÀÌÅÛÀ» ¼ÂÆÃÇÑ´Ù 
	int LastSetWareHouseItem(sITEM *pItem); //¾ÆÀÌÅÛÀ» ¼ÂÆÃÇÑ´Ù 
	int PickUpWareHouseItem(int x , int y , int PickUpFlag=0); //¾ÆÀÌÅÛÀ» Áı°Å³ª Á¤º¸¸¦ º¸¿©ÁØ´Ù 
	bool cWAREHOUSE::GetEmptyArea(sITEM* pItem, POINT* EmptyPos);
	bool cWAREHOUSE::CanStoreItem(sITEM* pItem);
	//¹«°Ô¸¦ ±¸ÇÑ´Ù 
	int GetWeight();

	//¾ÆÀÌÅÛ ÀÌ¹ÌÁö¸¦ ·ÎµåÇÑ´Ù
	int LoadWareHouseItemIamge();	
	
	//ÀÎº¥Åä¸® ¾ÆÀÌÅÛÀ» Àá½Ã ¹é¾÷ÇÑ´Ù 
	int BackUpInvenItem();
	//¾ÆÀÌÅÛÀ» º¹±¸ÇØÁØ´Ù 
	int RestoreInvenItem(); 
	//Ã¢°í¸¦ ´İ´Â´Ù 
	int CloseWareHouse();

	//////////////////Á¶ÀÛ ¹æÁö 
	int ReFormWareHouse();
	int CheckWareHouseForm();

	//////////////////º¹»ç ¾ÆÀÌÅÛ¿¡ °üÇÑ Ã³¸® (¾ÆÀÌÅÛÀ» ÁıÀ»¼ö¾ø´Ù)
	int CopyItemNotPickUp(sITEM *pItem,int JumpIndex);
	int CheckCopyItem(); //º¹»çµÈ ¾ÆÀÌÅÛÀÌ ÀÖ´ÂÁö¸¦ Ã¼Å©ÇÑ´Ù 
	int DeleteCopyItem(); //º¹»ç ¾ÆÀÌÅÛÀ» ¾ø¾ÖÁØ´Ù (¼­¹ö ÀÌ»óÀ¸·Î Ã¢°í¿¡ º¹»ç¾ÆÀÌÅÛÀÌ ¸¹ÀÌ »ı°åÀ½)

};

/*----------------------------------------------------------------------------*
*								½ºÅ³ Å¬·¡½º 
*-----------------------------------------------------------------------------*/
class cTRADE{

public:

	int OpenFlag;
	int MatTrade[4];
	int MatWareHouse[3]; //Ã¢°í (ÀÌ¹ÌÁöÇÏ³ª´Â »óÁ¡¿¡¼­ °¡Á®¿Â´Ù)
	int MatTradebuttonMain;
	int LpButtonYes;
	int LpButtonYes_;
	int LpButtonNo;
	int LpButtonNo_;

	LPDIRECT3DTEXTURE9 lpbuttonCancel;

	LPDIRECT3DTEXTURE9 lpbuttonCancelInfo;

	LPDIRECT3DTEXTURE9 lpbuttonOk;
	LPDIRECT3DTEXTURE9 lpCheck;

	LPDIRECT3DTEXTURE9 lpCheck_Glay;
	LPDIRECT3DTEXTURE9 lpCheckInfo;
	LPDIRECT3DTEXTURE9 lpDelayCheck;

	LPDIRECT3DTEXTURE9 lpCenterBox;

	sITEM CheckItem[100];
	sITEM CheckRecvItem[MAX_TRADE_ITEM];

	////»ç¿ë º¯¼ö 
	int   TradeRequestFlag;
	DWORD TradeCharCode;
	char  szTradeCharName[64];

	int   TradeItemCheckSum;



public:
	cTRADE();
	~cTRADE();

	void Init(); //Å¬·¡½º ÃÊ±âÈ­
	void Load();
	void Release();
	void Draw();
	void DrawImage(int Mat, int x, int y, int w, int h);
	void Close();//Å¬·¡½º Á¾·á 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	void DrawTradeText(); //ÅØ½º¸¦ Âï¾îÁØ´Ù 

	///////////// Æ®·¹ÀÌµå ÇÔ¼ö 
	int SetTradeItemAreaCheck(sITEM *pItem); //°ø°£À» Ã¼Å©ÇÑ´Ù 
	int CrashTradeItem(RECT &desRect, int PassItemIndex=0 , int Kind=0); //¾ÆÀÌÅÛÀÌ °ãÃÄÁ³´ÂÁö¸¦ Ã£´Â´Ù 
	int InitTradeColorRect(); //ÄÃ·¯ ¹Ú½º ÃÊ±âÈ­ 
	int ChangeTradeItem(sITEM *pItem); //°ãÃÄÁø ¾ÆÀÌÅÛÀ» ¼ÂÆÃÇÑ´Ù 
	int LastSetTradeItem(sITEM *pItem); //¾ÆÀÌÅÛÀ» ¼ÂÆÃÇÑ´Ù 
	int PickUpTradeItem(int x , int y , int PickUpFlag=0); //¾ÆÀÌÅÛÀ» Áı°Å³ª Á¤º¸¸¦ º¸¿©ÁØ´Ù 
	bool cTRADE::GetEmptyArea(sITEM* pItem, POINT* EmptyPos);
	bool cTRADE::IsItemOkay(sITEM* pItem);
	//¾ÆÀÌÅÛÀÌ ¼ÂÆÃ°¡´ÉÇÑÁö ¾Ë¾Æº»´Ù 
	int CheckTradeItemSet(); //¼ÂÆÃ Ã¼Å© ¸ŞÀÎ(¹«°Ô¸¦ Ã¼Å©ÇÏ°í ³ª¸ÓÁö ÇÔ¼ö¸¦ È£ÃâÇÑ´Ù)
	int TradeCheckEmptyArea(sITEM *pItem); //¾ÆÀÌÅÛÀÌ ¼ÂÆÃµÉ¼öÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù
	int ChecketInvenItem(sITEM *pItem); //¾ÆÀÌÅÛÀ» ÀÓ½Ã·Î ¼ÂÆÃÇÑ´Ù 

	//¾ÆÀÌÅÛÀ» ÀÎº¥Åä¸®·Î ¼ÂÆÃÇÑ´Ù 
	int CheckOkTradeItem();			//Æ®·¹ÀÌµå È®ÀÎ 
	int CancelTradeItem();			//Æ®·¹ÀÌµå Ãë¼Ò 
	int LoadTradeItemIamge();		//¾ÆÀÌÅÛ ÀÌ¹ÌÁö¸¦ ·ÎµåÇÑ´Ù

	//½ÂÀÎ °ü·Ã 
	int CheckTradeButtonOk();		//¼­¹ö¿¡ ½ÂÀÎÀ» ¾ò´Â´Ù 

	//¹«°Ô¸¦ ±¸ÇÑ´Ù 
	int GetWeight();

	////////////////////¾ÆÀÌÅÛÀ» Á¶ÀÛÇÏ´Â »ó³ğÀÇ ÀÚ½ÄµéÀ» Á×¿©¹ö¸°´Ù Æ¡!!
	int CheckTradeItemForm();	//°Ë»ç 
	int ReFormTradeItem();		//ÀÎÁõ 


};
// pluto Á¦ÀÛ ¾ÆÀÌÅÛ ¹«°Ô, °¡°İ
int ManufactureItemResultInfo( SManufacture_ResultItemInfo_Server *pResultItemInfo );
///////////// ÇÔ¼ö
int CopyMixItemCheckDelete(sITEM *pItem);
int sinMakeItemCheck(); //MakeItemÀ» Ã¼Å©ÇÑ´Ù
int sinPosBoxNpc();     //PostBox NpcÇÑÅ×¼­ ¸Ş¼¼Áö¸¦ ¹Ş´Â´Ù 
extern SManufacture_ResultItemInfo g_Manufacture_ItemInfo[MAX_HANDMADEITEM]; // Àåº° - Á¦ÀÛ // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
extern cTRADE cTrade;
extern sTRADE sTrade;
extern sTRADE sTradeRecv;

extern int RequestTradeButtonFlag; //°Å·¡¿ä±¸ ¹öÆ° Å¬¸¯ 
	   
extern cWAREHOUSE cWareHouse; //Ã¢°í Å¬·¡½º 
extern sWAREHOUSE sWareHouse; //Ã¢°í ±¸Á¶Ã¼ 
extern sITEM *BackUpInvenItem2; //ÀÎº¥¾ÆÀÌÅÛ ÀÓ½Ã ¹é¾÷ 

extern sCARAVAN sCaravan;

extern int TempShowCoin;
extern cCRAFTITEM cCraftItem;	//¾ÆÀÌÅÛ Á¶ÇÕ 

extern CSmeltingItem SmeltingItem; // pluto Á¦·Ã
extern SSmeltingItem S_smeltingItem; // pluto Á¦·Ã
extern sSMELTINGITEM_SERVER sSmeltingItem_Send; // pluto Á¦·Ã ¼­¹ö·Î º¸³¿
extern sSMELTINGITEM_SERVER sSmeltingItem_Recv; // pluto Á¦·Ã ¼­¹ö¿¡¼­ ¹ŞÀ½

extern CManufacture ManufactureItem; // pluto Á¦ÀÛ
extern SManufactureItem g_sManufactureItem; // pluto Á¦ÀÛ
extern SManufactureItem_Server g_sManufactureItem_Send; // pluto Á¦·Ã ¼­¹ö·Î º¸³¿
extern SManufactureItem_Server g_sManufactureItem_Recv; // pluto Á¦·Ã ¼­¹ö¿¡¼­ ¹ŞÀ½
extern SManufacture_Rune g_sManufacture_Rune[MAX_RECIPE_KIND];
//extern SManufacture_ResultItemInfo_Server g_Item_Recv;
extern sCRAFTITEM sCraftItem;
extern sCRAFTITEM_INFO sCraftItem_Info[MAX_CRAFTITEM_INFO]; //¾ÆÀÌÅÛ Á¶ÇÕ °ø½Ä

extern sCRAFTITEM_SERVER sCraftItem_Send; //¼­¹ö·Î º¸³»Áú ¾ÆÀÌÅÛ 
extern sCRAFTITEM_SERVER sCraftItem_Recv; //¼­¹ö¿¡¼­ ¹ŞÀ» ¾ÆÀÌÅÛ

extern sCRAFTITEM_SERVER sAging_Send; //¼­¹ö·Î º¸³»Áú ¾ÆÀÌÅÛ 
extern sCRAFTITEM_SERVER sAging_Recv; //¼­¹ö¿¡¼­ ¹ŞÀ» ¾ÆÀÌÅÛ 


extern int ShowItemCraftMessageFlag; //Á¶ÇÕµÈ ¾ÆÀÌÅÛ ÀÎÀÚ¸¦ º¸¿©ÁØ´Ù 
extern int ShowItemAgingMessageFlag; //¾ÆÀÌÅÛÀÌ ¿¡ÀÌÂ¡‰çÀ»¶§ ¸Ş¼¼Áö¸¦ º¸¿©ÁØ´Ù 
extern int ShowItemSmeltingMessageFlag; // pluto ¾ÆÀÌÅÛÀÌ Á¦·Ã ‰çÀ»¶§
extern int ShowItemManufactureMessageFlag; // pluto ¾ÆÀÌÅÛÀÌ Á¦ÀÛ ‰çÀ»¶§
extern int ShowItemOverSpace;	// pluto °ø°£ºÎÁ·

extern int TempShowMoney;	  //º¸¿©Áö±â¸¸ ÇÏ´Â µ· 
extern int ItemPickUpFlag;	  //»ç±â¹æÁö¸¦ À§ÇØ¼­ µô·¹ÀÌ¸¦ ÁØ´Ù 	
extern int WareHouseSaveFlag;
extern int CaravanSaveFlag;

extern cAGING	cAging;		  //¿¡ÀÌÂ¡ 
extern sAGINGITEM sAgingItem;
extern sAGINGITEM_INFO sAgingItem_Info[MAX_AGINGITEM_INFO];

extern int AgingLevelAttack[20];
extern int AgingLevelCritical[20];

extern char szAgingItemBuff[128];
extern POINT CraftItemMessageSize;

extern int AgingCheckSheltomFlag; //¿¡ÀÌÂ¡ °¡´É ÇÃ·¢ ÃÊ±âÈ­ 
extern int AgingSheltomCnt2;
extern int MixItemNoCopyFlag;
extern int CheckMixItemCopyFlag;
extern sMAKEITEM_INFO sMakeItem_Info[MAX_MAKEITEM_INFO];

// ¹Í½ºÃÄ ¸®¼Â °´Ã¼ ¹× º¯¼öµé Àü¿ªÈ­ ÇÏ±â
extern cMIXTURERESET cMixtureReset;						// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â °´Ã¼
extern sMIXTURE_RESET_ITEM	sMixtureResetItem;			// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â ¾ÆÀÌÅÛ Á¤º¸ ±¸Á¶Ã¼
extern sMIXTURE_RESET_ITEM sMixtureResetItemBackUp;		// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â ¾ÆÀÌÅÛ Á¤º¸ ±¸Á¶Ã¼ ¹é¾÷
extern int	MixtureResetCheckFlag;						// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼ÂÀÌ °¡´ÉÇÑ°¡?
extern sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Send;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â ¼­¹ö·Î Àü¼ÛÇÒ ±¸Á¶Ã¼
extern sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Recv;	// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â ¼­¹ö¿¡¼­ ¹ŞÀ» ±¸Á¶Ã¼

extern char *PostBoxDocFilePath[];

extern sPOSTBOX_ITEM sPostbox_Item[50];
extern int PostBoxIndexCnt;
extern DWORD ExpressItemCode;
extern char  szExpressItemName[64]; //¹ŞÀ» ¾ÆÀÌÅÛ ÀÌ¸§ 

extern sCRAFTITEM_SERVER sWingItem_Send; //¼­¹ö·Î º¸³»Áú À®¾ÆÀÌÅÛ
extern sCRAFTITEM_SERVER sWingItem_Recv; //¼­¹ö¿¡¼­ ¹ŞÀ» ¾ÆÀÌÅÛ (Çè ÇÊ¿äÇÑ°¡ ¸Ö°Ú³×)

extern int DownTradePosi[9][4];
extern DWORD SheltomCode2[];
extern DWORD MagicSheltomCode[]; // ¹ÚÀç¿ø - ¸ÅÁ÷ Æ÷½º Ãß°¡
extern DWORD BillingMagicSheltomCode[]; // ¹ÚÀç¿ø - ºô¸µ ¸ÅÁ÷ Æ÷½º Ãß°¡
extern int ForceItemPrice2;
extern sRECON_ITEM sReconItem[MAX_SEEL_COUNT]; // ¹ÚÀç¿ø - Å×ÀÌ¿ÍÁî ¾Á Ãß°¡
extern int		MixCancelButtonDelayFlag; // pluto ¿ÜºÎ º¯¼ö·Î ¹Ù²å´Ù -_-