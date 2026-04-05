//######################################################################################
// WinMain.cpp - Código Completo com Mini Skill Bar Profissional
//######################################################################################

#include "globals.h"

#define _SINBARAM

#include "Discord.h"
#include "Def.h"

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ZMOUSE.H>
#include <process.h>
#include "Utils/common.h"
#include "imGui/imgui_impl_win32.h"
#include "smlib3d\\smd3d.h"
#include "smwsock.h"
#include "smreg.h"
#include <io.h>
#include <fcntl.h>
#include "character.h"
#include "playmain.h"
#include "srcsound\\dxwav.h"
#include "effectsnd.h"
#include "fileread.h"
#include "netplay.h"
#include "makeshadow.h"
//#include "cSelect.h"
#include "particle.h"
#include "field.h"
#include "hoBaram\\holinkheader.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"
#include "TitleBox/TitleBox.h"
#include "Engine/Timer/Timer.h"

#ifdef _SINBARAM
#include "sinbaram\\sinlinkheader.h"
#endif

#include "HUD\\MixWindow.h"
#include "playsub.h"
#include "cracker.h"
#include "SkillSub.h"
#include "Montarias\\CMountHandler.h"
#include "resource.h"

#include "TextMessage.h"      //¹®ÀÚ ¸Þ¼¼Áö Çì´õ
#include "srcLang\\jts.h"     //ÀÏº»¾î ÄÚµå Ã½Å©

#include "CurseFilter.h"      //¿å¼³ÇÊÅÍ
#include "damage.h"
#include "AreaServer.h"

#include "BellatraFontEffect.h"

#include "actiongame.h"

#include <thread>
#include <string>
#include <map>
#include <algorithm>

void AutoPickupGold();


// ===== SISTEMA DE NEVOEIRO PARA SERVIDOR 3 =====
float g_fFogIntensity = 0.0f;
float g_fFogTargetIntensity = 0.0f;
DWORD g_dwFogColor = 0x884466AA; // Roxo/azul escuro para combinar com o tema
BOOL g_bFogEnabled = FALSE;

// Parâmetros do nevoeiro (ajustáveis)// Parâmetros do nevoeiro (ajustáveis) - VALORES MAIS PRÓXIMOS
#define FOG_START_DISTANCE    1.0f   // Começa a aparecer a 250 unidades (bem mais perto)
#define FOG_END_DISTANCE      150.0f   // Totalmente opaco a 650 unidades (antes era 1800)
#define FOG_DENSITY           0.038f   // Densidade mais alta do nevoeiro

/// ===== SISTEMA DE PALETA DE CORES ANIMADA PARA SERVIDOR 3 - TEMA ROXO/LILÁS VIVO =====
float g_fWarmColorIntensity = 0.0f;
float g_fWarmColorTarget = 0.0f;
float g_fColorAnimationTime = 0.0f;
float g_fPulseIntensity = 0.0f;
float g_fPulseDirection = 1.0f;
BOOL g_bIsServer3 = FALSE;

// Cores base para o tema roxo/lilás VIVO e BRILHANTE
#define PURPLE_BRIGHT_R_BOOST      1.85f    // Vermelho mais intenso
#define PURPLE_BRIGHT_G_BOOST      0.45f    // Verde reduzido para dar o tom roxo
#define PURPLE_BRIGHT_B_BOOST      2.15f    // Azul forte para o roxo vibrante
#define PURPLE_BRIGHT_SATURATION   2.15f    // Saturação alta para cores vivas
#define PURPLE_BRIGHT_GAMMA        0.92f    // Gamma levemente reduzido para contraste

// Cores atmosféricas
#define PURPLE_ATMOS_R    85     // Vermelho mais intenso
#define PURPLE_ATMOS_G    25     // Verde baixo
#define PURPLE_ATMOS_B    125    // Azul alto para roxo rico

// Efeitos de brilho
#define PURPLE_GLOW_INTENSITY  1.25f
#define PURPLE_PULSE_SPEED     0.8f   // Velocidade da pulsação
#define PURPLE_BLOOM_AMOUNT    1.35f  // Efeito de brilho

// Novos parâmetros para controle de qualidade visual
float g_fBloomIntensity = 0.0f;
float g_fContrastBoost = 1.0f;
float g_fSharpness = 1.0f;

BOOL IsServer3() {
    return (TCP_SERVPORT == 40629 || smConfig.dwServerPort == 40629);
}
void UpdateWarmPalette() {
    g_bIsServer3 = IsServer3();

    // Transição suave entre servidores
    float fDelta = 0.025f;
    if (g_bIsServer3) {
        g_fWarmColorTarget = 1.0f;
        g_fFogTargetIntensity = 1.0f;  // Ativa nevoeiro no servidor 3

        // Efeito de pulsação suave para dar vida
        g_fColorAnimationTime += 0.016f;
        g_fPulseIntensity = 0.85f + (sinf(g_fColorAnimationTime * PURPLE_PULSE_SPEED) * 0.15f);

        // Bloom varia com a pulsação
        g_fBloomIntensity = PURPLE_BLOOM_AMOUNT * (0.9f + (sinf(g_fColorAnimationTime * 1.2f) * 0.1f));

        // Contraste dinâmico
        g_fContrastBoost = 1.1f + (sinf(g_fColorAnimationTime * 0.5f) * 0.05f);

        // Cor do nevoeiro varia com a pulsação (mais dramático)
        int fogR = 70 + (int)(25 * sinf(g_fColorAnimationTime * 0.6f));
        int fogG = 35 + (int)(20 * sinf(g_fColorAnimationTime * 0.6f));
        int fogB = 95 + (int)(35 * sinf(g_fColorAnimationTime * 0.6f));
        g_dwFogColor = RGBA(fogR, fogG, fogB, 255);

    }
    else {
        g_fWarmColorTarget = 0.0f;
        g_fFogTargetIntensity = 0.0f;  // Desativa nevoeiro em outros servidores
        g_fPulseIntensity = 1.0f;
        g_fBloomIntensity = 0.0f;
        g_fContrastBoost = 1.0f;
    }

    // Transição suave da intensidade principal
    if (g_fWarmColorIntensity < g_fWarmColorTarget) {
        g_fWarmColorIntensity += fDelta * 2.0f;
        if (g_fWarmColorIntensity > g_fWarmColorTarget)
            g_fWarmColorIntensity = g_fWarmColorTarget;
    }
    else if (g_fWarmColorIntensity > g_fWarmColorTarget) {
        g_fWarmColorIntensity -= fDelta * 2.0f;
        if (g_fWarmColorIntensity < g_fWarmColorTarget)
            g_fWarmColorIntensity = g_fWarmColorTarget;
    }

    // Transição suave do nevoeiro
    if (g_fFogIntensity < g_fFogTargetIntensity) {
        g_fFogIntensity += fDelta * 1.5f;
        if (g_fFogIntensity > g_fFogTargetIntensity)
            g_fFogIntensity = g_fFogTargetIntensity;
    }
    else if (g_fFogIntensity > g_fFogTargetIntensity) {
        g_fFogIntensity -= fDelta * 1.5f;
        if (g_fFogIntensity < g_fFogTargetIntensity)
            g_fFogIntensity = g_fFogTargetIntensity;
    }

    // Ativa/desativa o nevoeiro baseado na intensidade
    g_bFogEnabled = (g_fFogIntensity > 0.01f);
}
// Função para aplicar o nevoeiro no render - VERSÃO CORRIGIDA
// Função para aplicar o nevoeiro no render - VERSÃO COM DISTÂNCIAS AJUSTÁVEIS
void ApplyFogEffect() {
    if (!g_bFogEnabled || g_fFogIntensity <= 0.01f) {
        // Desativa fog se não estiver no servidor 3
        if (GRAPHICDEVICE) {
            GRAPHICDEVICE->SetRenderState(D3DRS_FOGENABLE, FALSE);
        }
        smRender.m_FogMode = FALSE;
        return;
    }

    float f = g_fFogIntensity;

    // Distâncias dinâmicas baseadas na intensidade do fog
    // Quanto maior a intensidade, mais próximo o fog começa
    float fogStart = FOG_START_DISTANCE * (1.0f - (f * 0.5f));  // 250 a 125 unidades
    float fogEnd = FOG_END_DISTANCE * (1.0f - (f * 0.3f));       // 650 a 455 unidades

    // Garante valores mínimos
    if (fogStart < 50.0f) fogStart = 50.0f;
    if (fogEnd < 200.0f) fogEnd = 200.0f;

    // Aplica o fog diretamente no Direct3D
    if (GRAPHICDEVICE) {
        // Ativa o fog
        GRAPHICDEVICE->SetRenderState(D3DRS_FOGENABLE, TRUE);

        // Define a cor do fog (com a cor roxa/azulada)
        GRAPHICDEVICE->SetRenderState(D3DRS_FOGCOLOR, g_dwFogColor);

        // Usa o modo de fog linear (mais suave)
        GRAPHICDEVICE->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

        // Define as distâncias de início e fim do fog
        DWORD dwFogStart = *(DWORD*)&fogStart;
        DWORD dwFogEnd = *(DWORD*)&fogEnd;
        GRAPHICDEVICE->SetRenderState(D3DRS_FOGSTART, dwFogStart);
        GRAPHICDEVICE->SetRenderState(D3DRS_FOGEND, dwFogEnd);

        // Para um efeito mais denso, podemos usar modo exponencial quando a intensidade é alta
        if (f > 0.8f) {
            GRAPHICDEVICE->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
            float density = FOG_DENSITY * (f * 1.5f);
            GRAPHICDEVICE->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)&density);
        }
    }

    // Atualiza as flags do render
    smRender.m_FogMode = TRUE;
    smRender.m_FogIsRend = TRUE;
}
// Função para aplicar névoa com partículas (efeito mais dramático)
void ApplyParticleFog() {
    if (!g_bFogEnabled || g_fFogIntensity <= 0.5f) return;

    float f = g_fFogIntensity;

    // Adiciona partículas de névoa flutuantes (opcional)
    // Isso criaria um efeito de "névoa em movimento"
    static DWORD dwLastParticleTime = 0;
    DWORD dwCurrentTime = GetTickCount();

    if (dwCurrentTime - dwLastParticleTime > 100 && f > 0.7f) {
        dwLastParticleTime = dwCurrentTime;

        // Cria algumas partículas de névoa ao redor do jogador
        for (int i = 0; i < 3; i++) {
            int offsetX = (rand() % 400) - 200;
            int offsetZ = (rand() % 400) - 200;
            int offsetY = (rand() % 100) - 50;

            // Adiciona efeito de partícula (se você tiver sistema de partículas)
            // AddFogParticle(lpCurPlayer->pX + offsetX * fONE, 
            //                lpCurPlayer->pY + offsetY * fONE, 
            //                lpCurPlayer->pZ + offsetZ * fONE);
        }
    }
}


// Nova função para aplicar efeitos especiais de brilho nos elementos da UI
void ApplySpecialGlowEffects() {
    if (!g_bIsServer3 || g_fWarmColorIntensity <= 0.001f) return;

    float f = g_fWarmColorIntensity;
    float pulse = g_fPulseIntensity;

    // Efeito de brilho nos textos importantes
    DWORD glowColor = RGBA(
        (int)(85 * f * pulse),
        (int)(25 * f),
        (int)(125 * f * pulse),
        200
    );

    // Você pode usar esta cor para efeitos especiais na UI
    // Exemplo: dsDrawColorBox(glowColor, x, y, w, h);
}

// Função para animar o título do servidor com brilho
void AnimateServerTitle() {
    if (!g_bIsServer3) return;

    float pulse = 0.8f + (sinf(g_fColorAnimationTime * 3.0f) * 0.2f);
    int r = (int)(255 * pulse);
    int g = (int)(100 * pulse);
    int b = (int)(255 * pulse);

    // Aplica nos títulos (pode ser usado em outros lugares)
    SetFontTextColor(RGB(r, g, b));
}

// Função para ajustar o brilho geral do render
void AdjustGlobalBrightness() {
    if (!g_bIsServer3) return;

    float f = g_fWarmColorIntensity;
    float pulse = g_fPulseIntensity;

    // Aumenta o brilho geral para tirar o aspecto opaco
    int brightnessBoost = (int)(35 * f * (0.8f + pulse * 0.2f));

    smRender.Color_R += brightnessBoost;
    smRender.Color_G += (int)(brightnessBoost * 0.85f);
    smRender.Color_B += brightnessBoost;



}

void ApplyWarmPaletteToRender() {
    if (g_fWarmColorIntensity <= 0.001f) return;

    float f = g_fWarmColorIntensity;
    float pulse = g_fPulseIntensity;

    // Aplica cores roxas/lilás VIVAS e com brilho
    int rBoost = (int)((PURPLE_BRIGHT_R_BOOST * 45) * f * pulse);
    int gBoost = (int)((PURPLE_BRIGHT_G_BOOST * 15) * f);
    int bBoost = (int)((PURPLE_BRIGHT_B_BOOST * 60) * f * pulse);

    smRender.Color_R += rBoost;
    smRender.Color_G += gBoost;
    smRender.Color_B += bBoost;

    // Adiciona brilho extra (efeito bloom)
    if (g_fBloomIntensity > 0) {
        int bloomBoost = (int)(35 * g_fBloomIntensity * f);
        smRender.Color_R += bloomBoost;
        smRender.Color_G += (int)(bloomBoost * 0.6f);
        smRender.Color_B += bloomBoost;
    }

    // Ajuste de contraste para maior nitidez
    if (g_fContrastBoost > 1.0f) {
        int contrast = (int)(30 * (g_fContrastBoost - 1.0f) * f);
        smRender.Color_R += contrast;
        smRender.Color_G += (int)(contrast * 0.7f);
        smRender.Color_B += contrast;
    }
}


extern DWORD dwMainServ_RecvTime;
extern DWORD dwLastRecvGameServerTime;
//######################################################################################
// Definição do M_PI caso não esteja definido
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//######################################################################################

//######################################################################################
//ÀÛ ¼º ÀÚ : ¹ÚÃ¶È£
#define WM_CALLMEMMAP                WM_USER+3   //¸Þ¸ð¸®¸Ê¿¡ ¸Þ¼¼Áö°¡ ÀÖ´Ù°¡ Åëº¸
//######################################################################################

//######################################################################################
//ÀÛ ¼º ÀÚ : ¿À ¿µ ¼®
#include "WinInt\\WinIntThread.h"
#include "FullZoomMap.h"
#include "FontImage.h"
//######################################################################################
#include "TextMessage.h"
#include "HUD\\Roleta.h"
#include "Engine\\Directx\\DXSelectGlow.h"
#include "Engine\\Directx\\PostProcess.h"


// ===== VARIÁVEIS PARA O SELETOR DE SERVIDOR =====
char szServerName[64] = "Servidor: Babel";
RECT rcServerSelector;
bool bShowServerSelector = false;
int g_hoverWorld = -1;
extern void ReloadWorldConfig();
DWORD g_dwLastServerReadTime = 0;
// Ícones para os mundos (opcional)
int iWorldIcon[3] = { 0, 0, 0 };
extern char UserAccount[256];
extern char UserPassword[256];
extern int ReconnServer;
extern smWINSOCK* ConnectServer_GameMain(char* szIP1, DWORD dwPort1, char* szIP2, DWORD dwPort2);
extern int DisconnectServer_GameMain(void);
extern smWINSOCK* ConnectServer_GameMain(char* szIP1, DWORD dwPort1, char* szIP2, DWORD dwPort2);

// ===== VARIÁVEIS PARA MONITORAMENTO =====
int g_nLastWorldChecked = 0;
DWORD g_dwLastWorldCheckTime = 0;
bool g_bReconnecting = false;

void SetMapTitle(const char* mapName);

// ===== CONSTANTES DE DECAY =====
#define DECAY_TIME_TOTAL        20000      // 10 segundos até desaparecer
#define DECAY_STAGE1             3000      // 3 segundos - normal
#define DECAY_STAGE2             6000      // 3 segundos - começando a apodrecer
#define DECAY_STAGE3             10000      // 2 segundos - podre
#define DECAY_STAGE4            13000      // 2 segundos - desaparecendo

// Cores para o efeito de apodrecimento
#define DECAY_COLOR_NORMAL       RGBA(255, 255, 255, 255)  // Branco normal
#define DECAY_COLOR_STAGE1       RGBA(255, 255, 200, 255)  // Amarelado
#define DECAY_COLOR_STAGE2       RGBA(200, 150, 100, 230)  // Marrom claro
#define DECAY_COLOR_STAGE3       RGBA(100, 70, 40, 180)    // Marrom escuro
#define DECAY_COLOR_STAGE4       RGBA(50, 30, 10, 100)     // Quase preto, transparente

// ===== DECLARAÇÕES EXTERNAS =====
extern HDC hdc;
extern int OpenPlaySkill(sSKILL * lpSkill);

// ===== VARIÁVEIS GLOBAIS DO CHAT (JÁ EXISTEM NO JOGO) =====
// REMOVA estas linhas:
// extern char ChatBuff[2048][256];
// extern int ChatBuffCnt;

// ===== NOSSO PRÓPRIO SISTEMA DE CHAT =====
#define MAX_CHAT_MESSAGES 50
#define MAX_CHAT_LENGTH 256

struct SkillChatMessage {
    char text[MAX_CHAT_LENGTH];
    DWORD time;
    int r, g, b;
};

SkillChatMessage g_SkillChatMessages[MAX_CHAT_MESSAGES];
int g_SkillChatMessageCount = 0;

void AddSkillChatMessage(const char* message, int r = 255, int g = 255, int b = 0) {
    if (!message || !message[0]) return;

    char formattedMsg[MAX_CHAT_LENGTH];
    sprintf(formattedMsg, "    ", message);

    // Adiciona ao nosso buffer circular
    if (g_SkillChatMessageCount < MAX_CHAT_MESSAGES) {
        strcpy(g_SkillChatMessages[g_SkillChatMessageCount].text, formattedMsg);
        g_SkillChatMessages[g_SkillChatMessageCount].time = dwPlayTime;
        g_SkillChatMessages[g_SkillChatMessageCount].r = r;
        g_SkillChatMessages[g_SkillChatMessageCount].g = g;
        g_SkillChatMessages[g_SkillChatMessageCount].b = b;
        g_SkillChatMessageCount++;
    }
    else {
        // Move todas as mensagens uma posição para trás
        for (int i = 1; i < MAX_CHAT_MESSAGES; i++) {
            strcpy(g_SkillChatMessages[i - 1].text, g_SkillChatMessages[i].text);
            g_SkillChatMessages[i - 1].time = g_SkillChatMessages[i].time;
            g_SkillChatMessages[i - 1].r = g_SkillChatMessages[i].r;
            g_SkillChatMessages[i - 1].g = g_SkillChatMessages[i].g;
            g_SkillChatMessages[i - 1].b = g_SkillChatMessages[i].b;
        }
        strcpy(g_SkillChatMessages[MAX_CHAT_MESSAGES - 1].text, formattedMsg);
        g_SkillChatMessages[MAX_CHAT_MESSAGES - 1].time = dwPlayTime;
        g_SkillChatMessages[MAX_CHAT_MESSAGES - 1].r = r;
        g_SkillChatMessages[MAX_CHAT_MESSAGES - 1].g = g;
        g_SkillChatMessages[MAX_CHAT_MESSAGES - 1].b = b;
    }
}

void DrawSkillChatMessages() {
    int y = 200; // Posição Y inicial
    int x = 10;  // Posição X

    for (int i = 0; i < g_SkillChatMessageCount; i++) {
        // Mostra apenas mensagens com menos de 5 segundos
        if (dwPlayTime - g_SkillChatMessages[i].time < 5000) {
            SetFontTextColor(RGB(g_SkillChatMessages[i].r, g_SkillChatMessages[i].g, g_SkillChatMessages[i].b));
            dsTextLineOut(hdc, x, y, g_SkillChatMessages[i].text, strlen(g_SkillChatMessages[i].text));
            y += 20;
        }
    }
}
// ===== MINI SKILL BAR - VERSÃO FINAL COM MOVIMENTO E BOTÃO FORA =====
class CMiniSkillBar
{
private:
    struct SkillSlot
    {
        int nSkillCode;
        int nShortKey;
        int nIcon;
        int nIconGray;
        BOOL bIsEmpty;
        BOOL bInUse;
        char szKey[4];
        char szSkillName[64];
        char szFileName[64];

        // Dados de Cooldown
        DWORD dwCooldownEndTime;
        float fCooldownDuration;
        BOOL bOnCooldown;

        SkillSlot() {
            Reset();
        }

        void Reset() {
            nSkillCode = 0;
            nShortKey = 0;
            nIcon = 0;
            nIconGray = 0;
            bIsEmpty = TRUE;
            bInUse = FALSE;
            szKey[0] = 0;
            szSkillName[0] = 0;
            szFileName[0] = 0;
            dwCooldownEndTime = 0;
            fCooldownDuration = 0.0f;
            bOnCooldown = FALSE;
        }

        void SetCooldown(DWORD dwCurrentTime, float fDurationSec) {
            if (fDurationSec > 0.0f) {
                dwCooldownEndTime = dwCurrentTime + (DWORD)(fDurationSec * 1000.0f);
                fCooldownDuration = fDurationSec;
                bOnCooldown = TRUE;
            }
        }

        void UpdateCooldown(DWORD dwCurrentTime) {
            if (bOnCooldown && dwCurrentTime >= dwCooldownEndTime) {
                bOnCooldown = FALSE;
                fCooldownDuration = 0.0f;
                bInUse = FALSE;
            }
        }

        float GetRemainingCooldown(DWORD dwCurrentTime) const {
            if (!bOnCooldown || dwCurrentTime >= dwCooldownEndTime) return 0.0f;
            return (float)(dwCooldownEndTime - dwCurrentTime) / 1000.0f;
        }

        float GetCooldownProgress(DWORD dwCurrentTime) const {
            if (!bOnCooldown || fCooldownDuration <= 0.0f) return 1.0f;
            if (dwCurrentTime >= dwCooldownEndTime) return 1.0f;
            float fElapsed = (float)(dwCurrentTime - (dwCooldownEndTime - (DWORD)(fCooldownDuration * 1000.0f))) / 1000.0f;
            return min(1.0f, fElapsed / fCooldownDuration);
        }
    };

    SkillSlot m_Slots[8];
    int m_nPosX;
    int m_nPosY;
    int m_nSlotSize;
    int m_nSpacing;
    int m_nBorderSize;
    BOOL m_bVisible;
    BOOL m_bDragging;
    int m_nDragOffsetX;
    int m_nDragOffsetY;

    DWORD m_dwLastUpdateTime;

    std::map<std::string, int> m_TextureCache;

    RECT m_CloseButtonRect;
    BOOL m_bMouseOverClose;

    // Função interna para desenhar texto
    void InternalDrawText(int x, int y, const char* text, int len, int r, int g, int b, int size = 12) {
        if (!text || len <= 0) return;

        HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
        HFONT tempFont = CreateFontA(size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, NULL, NULL, ANTIALIASED_QUALITY,
            FF_DONTCARE, "Arial");
        SelectObject(hdc, tempFont);

        SetFontTextColor(RGB(r, g, b));
        dsTextLineOut(hdc, x, y, (char*)text, len);

        SelectObject(hdc, oldFont);
        DeleteObject(tempFont);
    }

public:
    CMiniSkillBar() {
        m_nPosX = 496;
        m_nPosY = 514;
        m_nSlotSize = 32;
        m_nSpacing = 2;
        m_nBorderSize = 2;
        m_bVisible = TRUE;
        m_bDragging = FALSE;
        m_nDragOffsetX = 0;
        m_nDragOffsetY = 0;
        m_dwLastUpdateTime = 0;
        m_bMouseOverClose = FALSE;

        for (int i = 0; i < 8; i++) {
            m_Slots[i].nShortKey = i + 1;
            sprintf(m_Slots[i].szKey, "F%d", i + 1);
        }

        PreloadAllSkillIcons();
        UpdateCloseButtonRect();
    }

    void PreloadAllSkillIcons() {
        struct _finddata_t fileinfo;
        long handle;
        char searchPath[256];
        char fullPath[256];

        sprintf(searchPath, "assets/miniskill/*.png");

        handle = _findfirst(searchPath, &fileinfo);
        if (handle == -1) return;

        do {
            std::string filename = fileinfo.name;
            size_t dotPos = filename.find_last_of(".");
            if (dotPos != std::string::npos) {
                filename = filename.substr(0, dotPos);
            }

            sprintf(fullPath, "assets/miniskill/%s", fileinfo.name);

            int textureID = CreateTextureMaterial((char*)fullPath, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
            if (textureID > 0) {
                m_TextureCache[filename] = textureID;
            }

            char grayPath[256];
            sprintf(grayPath, "assets/miniskill/%s_gray.png", filename.c_str());
            int grayTextureID = CreateTextureMaterial((char*)grayPath, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
            if (grayTextureID > 0) {
                m_TextureCache[filename + "_gray"] = grayTextureID;
            }
            else {
                m_TextureCache[filename + "_gray"] = textureID;
            }

        } while (_findnext(handle, &fileinfo) == 0);

        _findclose(handle);
    }

    int GetTextureForFile(const char* filename, BOOL bGray = FALSE) {
        if (!filename || !filename[0]) return 0;

        std::string key(filename);
        if (bGray) key += "_gray";

        auto it = m_TextureCache.find(key);
        if (it != m_TextureCache.end()) {
            return it->second;
        }

        if (bGray) {
            return GetTextureForFile(filename, FALSE);
        }

        char fullPath[256];
        sprintf(fullPath, "assets/miniskill/%s.png", filename);
        int textureID = CreateTextureMaterial((char*)fullPath, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
        if (textureID > 0) {
            m_TextureCache[key] = textureID;
        }
        return textureID;
    }

    void SetPosition(int x, int y) {
        if (!m_bDragging) {
            m_nPosX = x;
            m_nPosY = y;
            UpdateCloseButtonRect();
        }
    }

    int GetX() { return m_nPosX; }
    int GetY() { return m_nPosY; }

    int GetWidth() {
        return 4 * (m_nSlotSize + m_nSpacing) - m_nSpacing + m_nBorderSize * 2;
    }

    int GetHeight() {
        return 2 * (m_nSlotSize + m_nSpacing) - m_nSpacing + m_nBorderSize * 2;
    }

    void Show() { m_bVisible = TRUE; }
    void Hide() { m_bVisible = FALSE; }
    BOOL IsVisible() { return m_bVisible; }

    BOOL IsMouseOver() {
        if (!m_bVisible) return FALSE;
        int width = GetWidth();
        int height = GetHeight();
        return (pCursorPos.x >= m_nPosX && pCursorPos.x <= m_nPosX + width &&
            pCursorPos.y >= m_nPosY && pCursorPos.y <= m_nPosY + height);
    }

    BOOL IsMouseOverCloseButton() {
        if (!m_bVisible) return FALSE;
        // Botão fora da barra - 5 pixels à direita
        return (pCursorPos.x >= m_CloseButtonRect.left && pCursorPos.x <= m_CloseButtonRect.right &&
            pCursorPos.y >= m_CloseButtonRect.top && pCursorPos.y <= m_CloseButtonRect.bottom);
    }

    void StartDrag(int mouseX, int mouseY) {
        if (IsMouseOverCloseButton()) return; // Não arrasta se for no botão fechar
        m_bDragging = TRUE;
        m_nDragOffsetX = mouseX - m_nPosX;
        m_nDragOffsetY = mouseY - m_nPosY;
    }

    void Drag(int mouseX, int mouseY) {
        if (m_bDragging) {
            m_nPosX = mouseX - m_nDragOffsetX;
            m_nPosY = mouseY - m_nDragOffsetY;
            m_nPosX = max(0, min(m_nPosX, WinSizeX - GetWidth()));
            m_nPosY = max(0, min(m_nPosY, WinSizeY - GetHeight()));
            UpdateCloseButtonRect();
        }
    }

    void StopDrag() {
        m_bDragging = FALSE;
    }

    void UpdateCloseButtonRect() {
        // Botão fora da barra - 5 pixels à direita e centralizado verticalmente
        m_CloseButtonRect.left = m_nPosX + GetWidth() + 5;
        m_CloseButtonRect.right = m_nPosX + GetWidth() + 15;
        m_CloseButtonRect.top = m_nPosY + (GetHeight() / 2) - 5;
        m_CloseButtonRect.bottom = m_nPosY + (GetHeight() / 2) + 5;
    }

    void DrawRect(int x, int y, int width, int height, DWORD color) {
        dsDrawColorBox(color, x, y, width, height);
    }

    void DrawCooldownOverlay(int x, int y, int size, float remaining) {
        if (remaining <= 0.0f) return;

        int centerX = x + size / 2;
        int centerY = y + size / 2;

        // Sempre mostra o número do cooldown
        char timeText[8];
        if (remaining >= 1.0f) {
            sprintf(timeText, "%d", (int)remaining);
        }
        else {
            sprintf(timeText, "%.1f", remaining);
        }
        int textLen = strlen(timeText);
        int textX = centerX - (textLen * 4);
        int textY = centerY - 6;

        // Fundo preto semi-transparente para o texto
        DrawRect(textX - 2, textY - 1, textLen * 8 + 4, 14, RGBA(0, 0, 0, 180));
        InternalDrawText(textX, textY, timeText, textLen, 255, 255, 255, 11);
    }

    void Update() {
        DWORD dwCurrentTime = dwPlayTime;
        if (dwCurrentTime - m_dwLastUpdateTime < 50) {
            return;
        }
        m_dwLastUpdateTime = dwCurrentTime;

        for (int i = 0; i < 8; i++) {
            m_Slots[i].UpdateCooldown(dwCurrentTime);
            m_Slots[i].nSkillCode = 0;
            m_Slots[i].bIsEmpty = TRUE;
            m_Slots[i].bInUse = FALSE;
        }

        for (int j = 1; j < SIN_MAX_USE_SKILL; j++) {
            if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point > 0) {
                int nShortKey = sinSkill.UseSkill[j].ShortKey;
                if (nShortKey >= 1 && nShortKey <= 8) {
                    int idx = nShortKey - 1;

                    m_Slots[idx].nSkillCode = sinSkill.UseSkill[j].CODE;
                    strcpy(m_Slots[idx].szSkillName, sinSkill.UseSkill[j].Skill_Info.SkillName);
                    m_Slots[idx].bInUse = sinSkill.UseSkill[j].UseSkillFlag;

                    if (strcmp(m_Slots[idx].szFileName, sinSkill.UseSkill[j].FileName) != 0) {
                        strcpy(m_Slots[idx].szFileName, sinSkill.UseSkill[j].FileName);
                        m_Slots[idx].nIcon = GetTextureForFile(sinSkill.UseSkill[j].FileName, FALSE);
                        m_Slots[idx].nIconGray = GetTextureForFile(sinSkill.UseSkill[j].FileName, TRUE);
                    }

                    m_Slots[idx].bIsEmpty = FALSE;
                }
            }
        }
    }

    void Render() {
        if (!m_bVisible) return;

        int slotSize = m_nSlotSize;
        int spacing = m_nSpacing;
        int border = m_nBorderSize;

        int hoverSlot = -1;
        int hoverRow = -1, hoverCol = -1;

        int startX = m_nPosX + border;
        int startY = m_nPosY + border;

        // Verifica hover nos slots
        for (int row = 0; row < 2; row++) {
            for (int col = 0; col < 4; col++) {
                int idx = row * 4 + col;
                int x = startX + col * (slotSize + spacing);
                int y = startY + row * (slotSize + spacing);

                if (pCursorPos.x > x && pCursorPos.x < x + slotSize &&
                    pCursorPos.y > y && pCursorPos.y < y + slotSize) {
                    hoverSlot = idx;
                    hoverRow = row;
                    hoverCol = col;
                    break;
                }
            }
        }

        m_bMouseOverClose = IsMouseOverCloseButton();

        // ===== BARRA PRINCIPAL =====
        // FUNDO TRANSPARENTE
        DrawRect(m_nPosX, m_nPosY, GetWidth(), GetHeight(), RGBA(20, 20, 20, 40));

        // BORDA SUTIL
        DWORD borderColor = RGBA(150, 150, 150, 60);
        DrawRect(m_nPosX, m_nPosY, GetWidth(), 1, borderColor);
        DrawRect(m_nPosX, m_nPosY + GetHeight() - 1, GetWidth(), 1, borderColor);
        DrawRect(m_nPosX, m_nPosY, 1, GetHeight(), borderColor);
        DrawRect(m_nPosX + GetWidth() - 1, m_nPosY, 1, GetHeight(), borderColor);

        // ===== BOTÃO FECHAR FORA DA BARRA =====
        int btnX = m_CloseButtonRect.left;
        int btnY = m_CloseButtonRect.top;
        int btnSize = 10;

        // Fundo do botão (sutil)
        DrawRect(btnX - 2, btnY - 2, btnSize + 4, btnSize + 4, RGBA(20, 20, 20, 100));

        // O "X" - vermelho no hover, cinza normalmente
        DWORD closeColor = m_bMouseOverClose ? RGBA(255, 80, 80, 255) : RGBA(180, 180, 180, 200);
        for (int i = 0; i < btnSize; i++) {
            DrawRect(btnX + i, btnY + i, 1, 1, closeColor);
            DrawRect(btnX + (btnSize - i), btnY + i, 1, 1, closeColor);
        }

        // ===== SLOTS =====
        for (int row = 0; row < 2; row++) {
            for (int col = 0; col < 4; col++) {
                int idx = row * 4 + col;
                int x = startX + col * (slotSize + spacing);
                int y = startY + row * (slotSize + spacing);

                // Fundo do slot (mais visível no hover)
                DWORD slotBg = (hoverSlot == idx) ? RGBA(80, 80, 80, 80) : RGBA(40, 40, 40, 30);
                DrawRect(x, y, slotSize, slotSize, slotBg);

                // Borda do slot no hover
                if (hoverSlot == idx) {
                    DWORD slotBorder = RGBA(200, 200, 200, 150);
                    DrawRect(x, y, slotSize, 1, slotBorder);
                    DrawRect(x, y + slotSize - 1, slotSize, 1, slotBorder);
                    DrawRect(x, y, 1, slotSize, slotBorder);
                    DrawRect(x + slotSize - 1, y, 1, slotSize, slotBorder);
                }

                if (!m_Slots[idx].bIsEmpty) {
                    int iconX = x + 4;
                    int iconY = y + 4;
                    int iconSize = slotSize - 8;
                    int textureToUse = m_Slots[idx].bOnCooldown ? m_Slots[idx].nIconGray : m_Slots[idx].nIcon;

                    if (textureToUse > 0) {
                        int alpha = m_Slots[idx].bInUse ? 255 : 180;
                        dsDrawTexImage(textureToUse, iconX, iconY, iconSize, iconSize, alpha);
                    }

                    // SEMPRE mostra o número do cooldown quando em cooldown
                    if (m_Slots[idx].bOnCooldown) {
                        float remaining = m_Slots[idx].GetRemainingCooldown(dwPlayTime);
                        DrawCooldownOverlay(x, y, slotSize, remaining);
                    }
                }
                else {
                    // Slot vazio - ponto sutil
                    int centerX = x + slotSize / 2;
                    int centerY = y + slotSize / 2;
                    DrawRect(centerX - 1, centerY - 1, 2, 2, RGBA(150, 150, 150, 80));
                }

                // Tecla de atalho (F1-F8)
                DrawRect(x + 2, y + 2, 16, 10, RGBA(0, 0, 0, 120));
                InternalDrawText(x + 5, y + 2, m_Slots[idx].szKey, 2, 220, 220, 220, 9);
            }
        }

        // DICA FIXA NA PARTE INFERIOR
        int msgX = m_nPosX + 8;
        int msgY = m_nPosY + GetHeight() + 2;
        InternalDrawText(msgX, msgY, "Shift+Botão Dir para equipar", 28, 180, 180, 180, 10);

        // TOOLTIP DO NOME (só quando passa o mouse)
        if (hoverSlot >= 0 && !m_Slots[hoverSlot].bIsEmpty) {
            int x = startX + hoverCol * (slotSize + spacing);
            int y = startY + hoverRow * (slotSize + spacing);
            int tooltipX = x;
            int tooltipY = y - 20;

            if (tooltipY < m_nPosY) tooltipY = y + slotSize + 4;

            DrawRect(tooltipX, tooltipY, strlen(m_Slots[hoverSlot].szSkillName) * 7 + 8, 16, RGBA(20, 20, 20, 200));
            InternalDrawText(tooltipX + 4, tooltipY + 2, m_Slots[hoverSlot].szSkillName,
                strlen(m_Slots[hoverSlot].szSkillName), 255, 255, 255, 11);
        }
    }

    // ===== FUNÇÃO HandleShortKey =====
    BOOL HandleShortKey(int nVKKey) {
        if (!m_bVisible) return FALSE;

        int slotIndex = -1;
        switch (nVKKey) {
        case VK_F1: slotIndex = 0; break;
        case VK_F2: slotIndex = 1; break;
        case VK_F3: slotIndex = 2; break;
        case VK_F4: slotIndex = 3; break;
        case VK_F5: slotIndex = 4; break;
        case VK_F6: slotIndex = 5; break;
        case VK_F7: slotIndex = 6; break;
        case VK_F8: slotIndex = 7; break;
        default: return FALSE;
        }

        if (slotIndex >= 0 && slotIndex < 8 && !m_Slots[slotIndex].bIsEmpty) {
            if (m_Slots[slotIndex].bOnCooldown) {
                return TRUE;
            }

            for (int j = 1; j < SIN_MAX_USE_SKILL; j++) {
                if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point > 0 &&
                    sinSkill.UseSkill[j].ShortKey == (slotIndex + 1)) {

                    if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK &&
                        lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL &&
                        lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD) {

                        if (OpenPlaySkill(&sinSkill.UseSkill[j])) {
                            m_Slots[slotIndex].SetCooldown(dwPlayTime, 2.0f);
                            m_Slots[slotIndex].bInUse = TRUE;
                        }
                    }
                    break;
                }
            }
            return TRUE;
        }

        return FALSE;
    }
};

// ===== VARIÁVEL GLOBAL DA MINI SKILL BAR =====
CMiniSkillBar* g_pMiniSkillBar = NULL;


// ===== FUNÇÃO PARA OBTER A PORTA DO MUNDO =====
int GetPortFromWorld(int world)
{
    switch (world)
    {
    case 1: return 40627;
    case 2: return 40628;
    case 3: return 40629;
    }
}

// ===== FUNÇÃO PARA MOSTRAR NOTIFICAÇÃO NO TOPO =====
// ===== FUNÇÃO PARA MOSTRAR NOTIFICAÇÃO NO TOPO =====
void ShowWorldChangeNotification(const char* worldName)
{
    if (worldName && worldName[0])
    {
        char notification[128];
        sprintf(notification, "Servidor: %s", worldName);
        SetMapTitle(notification);
    }
}


// ===== MAPEAMENTO DE NOMES DOS MUNDOS =====
const char* GetWorldName(int world)
{
    switch (world)
    {
    case 1: return "Babel";
    case 2: return "Morion";
    case 3: return "Requiem";
    default: return "Servidor Babel";
    }
}
// ===== FUNÇÃO PARA RECONECTAR AO SERVIDOR =====
void ReconnectToServer(int newPort, int newWorld)
{
    if (g_bReconnecting || GameMode != 2) return;

    g_bReconnecting = true;

    // Mostra notificação
    const char* worldName = GetWorldName(newWorld);
    ShowWorldChangeNotification(worldName);

    char msg[256];
    sprintf(msg, "[Sistema] Mudando para %s...", worldName);
    AddSkillChatMessage(msg, 255, 255, 0);

    // Salva o IP atual
    char szCurrentIP[64];
    strcpy(szCurrentIP, smConfig.szServerIP);

    // DESATIVA A RECONEXÃO AUTOMÁTICA TEMPORARIAMENTE
    extern DWORD dwMainServ_RecvTime;
    extern DWORD dwLastRecvGameServerTime;
    dwMainServ_RecvTime = GetTickCount() + 30000;
    dwLastRecvGameServerTime = GetTickCount() + 30000;

    extern int ReconnServer;
    ReconnServer = 0;

    // DESCONECTA
    DisconnectServer_GameMain();

    // ATUALIZA A PORTA (REDUNDÂNCIA PARA GARANTIR)
    smConfig.dwServerPort = newPort;
    TCP_SERVPORT = newPort;

    printf("DEBUG: ReconnectToServer - Nova porta: %d\n", newPort);
    printf("DEBUG: TCP_SERVPORT = %d\n", TCP_SERVPORT);

    // Aguarda
    Sleep(2000);

    // RECONECTA
    ConnectServer_GameMain(szCurrentIP, newPort, szCurrentIP, newPort);

    g_bReconnecting = false;
    g_dwLastWorldCheckTime = GetTickCount();
}
// ===== FUNÇÃO PARA VERIFICAR MUDANÇA NO MUNDO =====
// ===== FUNÇÃO PARA VERIFICAR MUDANÇA NO MUNDO =====
void CheckWorldChange()
{
    if (g_bReconnecting || GameMode != 2) return;

    DWORD dwCurrentTime = GetTickCount();

    // Verifica a cada 3 segundos
    if (dwCurrentTime - g_dwLastWorldCheckTime < 3000) return;

    g_dwLastWorldCheckTime = dwCurrentTime;

    // Lê o mundo atual do game.ini
    int currentWorld = GetPrivateProfileIntA("ConnectServer", "Mundo", 1, ".\\game.ini");

    // Se for a primeira leitura, apenas guarda o valor
    if (g_nLastWorldChecked == 0)
    {
        g_nLastWorldChecked = currentWorld;
        return;
    }

    // Se mudou, reconecta
    if (currentWorld != g_nLastWorldChecked)
    {
        int newPort = GetPortFromWorld(currentWorld);

        // NÃO reconecta se já estiver na porta certa
        if (TCP_SERVPORT != newPort)
        {
            ReconnectToServer(newPort, currentWorld);
            g_nLastWorldChecked = currentWorld;
        }
    }
}

// ===== VARIÁVEIS GLOBAIS =====
HWND hwnd;
HWND hTextWnd;
HWND hFocusWnd;
extern sSKILL sSkill[SIN_MAX_SKILL];
extern sUSESKILL sinSkill;
extern int sinChatDisplayMode;
extern int sinChatInputMode;

extern void Init(HWND hWindow);

HDC hdc = NULL;
int quit = 0;
int QuitSave = 0;
int WinSizeX = 640;
int WinSizeY = 480;
int WinColBit = 16;

int TCP_SERVPORT = 32299;

float g_fWinSizeRatio_X;
float g_fWinSizeRatio_Y;

int horaHost = 0;
int minHost = 0;
int secHost = 0;
int diaHost = 0;
int PLayerPvP = 0;

int TextMode;
int BrCtrl = 0;
DWORD dwM_BlurTime = 0;

extern int TimeStreak;
extern int killStreak;

int MouseButton[3] = { 0, 0, 0 };
extern int TJwheel;
extern int keydownEnt;

#pragma comment( lib, "imm32.lib" )

#define DLLEXPORT __declspec(dllexport)

extern "C" {
    DLLEXPORT BOOL _stdcall smSetCurrentWindows(HWND wnd);
    DLLEXPORT int _stdcall InitD3D(HWND hWnd);
    DLLEXPORT void _stdcall CloseD3d();
    DLLEXPORT void _stdcall smPlayD3D(int x, int y, int z, int ax, int ay, int az);
    DLLEXPORT int _stdcall smSetMode(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP);
}

extern "C" BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved
);

#include "ime.h"

ImeClass IMETest;
CStrClass sz;
LRESULT CALLBACK EditWndProc01(HWND, UINT, WPARAM, LPARAM);
WNDPROC OldEditProc01;
char szIME_Buff[10][64];

extern char szCurrentMapName[64];
extern DWORD dwMapTitleShowTime;
extern BOOL bShowMapTitle;
extern float fMapTitleAlpha;

extern int Width, Height;
extern int GetClick(DWORD x, DWORD y, DWORD L, DWORD A);
extern int iSave;
extern BOOL bWidescreen;
extern BOOL bDone;

extern void SaveConfig();
extern void Relog();
extern char ratio_pt[4];
extern BOOL bIsWidescreen;
BOOL bShowFPS = FALSE;
BOOL bShowDrops = FALSE;
DWORD dwDebugBack;
DWORD dwDebugXor;

int MouseX, MouseY;
int MousemX, MousemY;
int angX = 0;
int angY = 0;
DWORD dwLastMouseMoveTime;
DWORD dwLastCharMoveTime;

int iSettingsBg;
int iSettingsButton[2];
int iSettingsRelog;
int iSettingsSave;
int iSettingsClose;
int iSettingsCheckBox[2];
int iBellatraBg;
int iBellatrOK;

extern Graphics::Camera* camera;

void ReadTexSettings()
{
    iSettingsBg = CreateTextureMaterial("game\\images\\settings\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iSettingsButton[0] = CreateTextureMaterial("game\\images\\settings\\settings.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iSettingsButton[1] = CreateTextureMaterial("game\\images\\settings\\settings_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iSettingsRelog = CreateTextureMaterial("game\\images\\settings\\help_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iSettingsSave = CreateTextureMaterial("game\\images\\settings\\save_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iSettingsClose = CreateTextureMaterial("game\\images\\settings\\close_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iSettingsCheckBox[0] = CreateTextureMaterial("game\\images\\settings\\checkbox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iSettingsCheckBox[1] = CreateTextureMaterial("game\\images\\settings\\checkbox_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iBellatraBg = CreateTextureMaterial("game\\images\\bellatra\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    iBellatrOK = CreateTextureMaterial("game\\images\\bellatra\\ok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

int xPos, yPos;
POINT3D TraceCameraPosi;
POINT3D TraceTargetPosi;
int PlayCameraMode = 1;
int AutoCameraFlag = FALSE;
int CameraInvRot = 0;
int CameraSight = 0;

LPDIRECT3DTEXTURE9 lpDDSMenu;

int DisplayDebug = 0;
int DispInterface = TRUE;
int DebugPlayer = FALSE;
int LastAttackDamage = 0;
int HoMsgBoxMode = 0;

#define TRADEBUTTONMAIN_X        513
#define TRADEBUTTONMAIN_Y        3

POINT pHoPartyMsgBox = { TRADEBUTTONMAIN_X, TRADEBUTTONMAIN_Y };

char* szOperationIP[5] = {
    "46.224.228.49",
    "211.108.45.",
    "211.44.231.",
    "221.148.123.",
    0
};

char szExitInfo_URL[128] = { 0, };

#define ANX_NONE    -32768

int pX;
int pY;
int pZ;
int dpX = 0;
int dpY = 0;
int dpZ = 0;

int whAnx = 48;
int anx = 48;
int ViewAnx = 48;
int ViewDist = 100;
int PlayFloor = 0;
int any_pt = 0;
int anz = 0;
int dist = 100;
int CaTarDist = 0;
int CaMovAngle = 0;

int tX = 0;
int tY = 0;
int tZ = 0;

int ImeChatLen = 0;
POINT ImePositon;

int WaveCameraMode = FALSE;
POINT3D WaveCameraPosi;
int WaveCameraFactor = 0;
int WaveCameraTimeCount = 0;
int WaveCameraDelay = 0;
BOOL WaveCameraFlag = FALSE;

int GameInit();
int GameClose();
int SetGameMode(int mode);
int SetChatingLine(char* szMessage);

int GameMode = 0;

CRITICAL_SECTION cDrawSection;
CRITICAL_SECTION cSection_Main;

int HoInstallFont();
int HoUninstallFont();

HINSTANCE hinst;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    hinst = hinstDLL;
    return TRUE;
}

#define IDC_TEXT    101

BYTE VRKeyBuff[256];

LONG APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);
void PlayD3D();
int DecodeCmdLine(char* lpCmdLine);
int HaejukReg();

HFONT hFont = 0;
int SetCreateFont();

HIMC hImc;
HIMC hImcEdit;

extern rsRECORD_DBASE rsRecorder;
extern INT WINAPI ServerWinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, INT nCmdShow);
extern int DrawTwoLineMessageTitle(int x, int y, char* message1, char* message2, char* message3, DWORD color1 = RGB(0, 0, 0), DWORD color2 = RGB(0, 0, 0), DWORD color3 = RGB(0, 0, 0), LPDIRECT3DTEXTURE9 clanMark = NULL, BOOL selected = FALSE, int bellaMarkIndex = -1);

char szCmdLine[128];

extern int InitCloseBetaUser();
extern int CheckServerRecordData();
extern int RestoreBackupData(char* szListFile, char* BackupPath);

#ifdef _W_SERVER
#include "mini_dump.h"
Mini_Dump CMiniDump;
#endif

#ifdef _DEBUG
extern "C" WINBASEAPI int WINAPI AllocConsole();
#endif

CRITICAL_SECTION cSection;

int LeIniInt(char* Section, char* Key, char* szFileIni)
{
    char Pasta[600] = { 0 };
    char PastaEmu[512] = { 0 };
    GetCurrentDirectoryA(512, PastaEmu);
    wsprintfA(Pasta, "%s\\%s", (char*)PastaEmu, szFileIni);
    return GetPrivateProfileIntA(Section, Key, 0, Pasta);
}

void WriteIniInt(char* Section, char* Key, char* szFileIni, DWORD Value)
{
    char Pasta[600] = { 0 };
    char PastaEmu[512] = { 0 };
    char Value2[30] = { 0 };
    GetCurrentDirectoryA(512, PastaEmu);
    wsprintfA(Value2, "%d", Value);
    wsprintfA(Pasta, "%s\\%s", (char*)PastaEmu, szFileIni);
    WritePrivateProfileStringA(Section, Key, Value2, Pasta);
}

void WriteIniStr(char* Section, char* Key, char* szFileIni, char* Value)
{
    char Pasta[600] = { 0 };
    char PastaEmu[512] = { 0 };
    GetCurrentDirectoryA(512, PastaEmu);
    wsprintfA(Pasta, "%s\\%s", (char*)PastaEmu, szFileIni);
    WritePrivateProfileStringA(Section, Key, Value, Pasta);
}

void LeIniStr(char* Section, char* Key, char* szFileIni, char* Var1)
{
    char Pasta[600] = { 0 };
    char szResult[255] = { 0 };
    char PastaEmu[512] = { 0 };
    GetCurrentDirectoryA(512, PastaEmu);
    wsprintfA(Pasta, "%s\\%s", (char*)PastaEmu, szFileIni);
    GetPrivateProfileStringA(Section, Key, 0, szResult, 255, Pasta);
    strcpy(Var1, szResult);
}

#ifndef _AC
#define _AC
#include "AntiCheat.h"
#endif
#include "Shop/NewShop.h"
#include "Shop/NewShopTime.h"
#include "ofuscate.h"
#include "Engine/Mouse/Mouse.h"

extern CAntiCheat* pcAntiCheat;

BOOL bAdjustWindow = FALSE;
BOOL bNoLag = FALSE;

inline bool checkLauncher(const std::string & name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

BOOL HookAPI(char* moduleName, char* apiName, void* callBack, void* backup = NULL)
{
    DWORD old = 0;
    void* pAPIHandle = GetProcAddress(GetModuleHandleA(moduleName), apiName);

    if (pAPIHandle == NULL)
        return FALSE;

    if (backup != NULL)
        MoveMemory(backup, pAPIHandle, 5);

    VirtualProtect(pAPIHandle, 5, PAGE_EXECUTE_READWRITE, &old);
    *(BYTE*)((DWORD)pAPIHandle) = 0xE9;
    *(DWORD*)((DWORD)pAPIHandle + 1) = (DWORD)callBack - (DWORD)pAPIHandle - 5;
    VirtualProtect(pAPIHandle, 5, old, &old);

    return TRUE;
}

LONG WINAPI RedirectedSetUnhandledExceptionFilter(EXCEPTION_POINTERS * p)
{
    return NULL;
}

void AntiDebugger()
{
#ifndef _DEBUG
    HMODULE h = LoadLibraryA(AY_OBFUSCATE("ntdll.dll"));
    if (h)
    {
        DWORD d = (DWORD)GetProcAddress(h, AY_OBFUSCATE("DbgUiRemoteBreakin"));
        if (d)
        {
            DWORD dold = 0;
            VirtualProtect((void*)d, 8, PAGE_EXECUTE_READWRITE, &dold);
            (*(DWORD*)d) = 0x6A6A6A6A;
            VirtualProtect((void*)d, 8, dold, NULL);
        }
    }
#endif
}
// WinMain.cpp - Substitua a função ReloadWorldConfig existente
void ReloadWorldConfig()
{
    const char* ServerIP = "46.224.228.49";
    int Mundo = GetPrivateProfileIntA("ConnectServer", "Mundo", 1, ".\\game.ini");
    int ServerPort = 0;

    // Garante que o mundo está dentro dos limites (1-3)
    if (Mundo < 1) Mundo = 1;
    if (Mundo > 3) Mundo = 3;

    switch (Mundo)
    {
    case 1: ServerPort = 40627; break;
    case 2: ServerPort = 40628; break;
    case 3: ServerPort = 40629; break;
    default: ServerPort = 40627; break;
    }

    // ATUALIZA TUDO que usa a porta
    lstrcpy(smConfig.szServerIP, ServerIP);
    lstrcpy(smConfig.szDataServerIP, ServerIP);
    smConfig.dwServerPort = ServerPort;

    // ESTAS SÃO AS VARIÁVEIS CRÍTICAS
    TCP_SERVPORT = ServerPort;

    // Se já estiver conectado, força a reconexão
    if (GameMode == 2) {
        extern DWORD dwMainServ_RecvTime;
        extern DWORD dwLastRecvGameServerTime;
        dwMainServ_RecvTime = GetTickCount() + 30000;
        dwLastRecvGameServerTime = GetTickCount() + 30000;

        extern int ReconnServer;
        ReconnServer = 0;
    }

    printf("DEBUG: Mundo recarregado: %d\n", Mundo);
    printf("DEBUG: Nova porta: %d\n", ServerPort);
    printf("DEBUG: TCP_SERVPORT agora = %d\n", TCP_SERVPORT);
}

int iNumWindowsFound = 0;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam)
{
    char szWindowName[64] = { 0 };
    char szClassName[64] = { 0 };

    if (GetWindowText(hWnd, szWindowName, _countof(szWindowName)) > 0)
        GetClassNameA(hWnd, szClassName, _countof(szClassName));

    if (lstrcmpiA(szWindowName, szAppName) == 0 || lstrcmpiA(szClassName, "apt-window") == 0)
        iNumWindowsFound++;

    return TRUE;
}

#include "mini_dump.h"
#include "Engine/DynamicAnimation/AnimationHandler.h"

int ConfigUseDynamicLights = 0;
int ConfigUseDynamicShadows = 0;

auto timer = std::make_unique<CTimer>();

// ===== FUNÇÃO SetMousePlay COMPLETA COM MINI SKILL BAR =====
int SetMousePlay(int flag)
{
    int ax, az, ay;
    char szBuff[256];
    int cnt;

    if (GameMode != 2) return TRUE;

    if (!lpCurPlayer->MotionInfo || dwNextWarpDelay || lpCurPlayer->PlayStunCount) return FALSE;

    if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD) return FALSE;

    // ===== MINI SKILL BAR - ARRASTO E CLIQUE =====
    extern POINT pCursorPos;

    if (g_pMiniSkillBar && g_pMiniSkillBar->IsVisible()) {

        // Botão esquerdo pressionado
        if (flag == 1) {
            if (g_pMiniSkillBar->IsMouseOverCloseButton()) {
                g_pMiniSkillBar->Hide();
                return TRUE;
            }
            if (g_pMiniSkillBar->IsMouseOver()) {
                g_pMiniSkillBar->StartDrag(pCursorPos.x, pCursorPos.y);
                return TRUE;
            }
        }

        // Botão esquerdo solto
        else if (flag == 0) {
            g_pMiniSkillBar->StopDrag();
        }

        // Durante o arrasto
        if (g_pMiniSkillBar->IsMouseOver()) {
            if (flag == 2) {
                g_pMiniSkillBar->Drag(pCursorPos.x, pCursorPos.y);
            }
            if (flag == 1 || flag == 11) {
                return TRUE;
            }
        }
    }
    // =============================================

#ifdef _SINBARAM
    if (g_IsDxProjectZoomIn <= 0)
    {
        dsMenuCursorPos(&pCursorPos, 2);
        if (StopCharMotion(pCursorPos.x, pCursorPos.y) == TRUE)
        {
            if (lpCurPlayer->MotionInfo->State < 0x100 && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_STAND)
            {
                lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_STAND);
                lpCurPlayer->MoveFlag = FALSE;
            }
            flag = 0;
        }
        dsMenuCursorPos(&pCursorPos, 0);
    }
#endif

    switch (flag)
    {
    case 1:
        if (!ActionGameMode)
        {
            if (lpCharSelPlayer || lpSelItem)
            {
                SelMouseButton = 1;
                TraceAttackPlay();
                AutoCameraFlag = FALSE;
            }
            else
            {
                if (MsTraceMode && !lpCharSelPlayer && !lpSelItem)
                {
                    if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK &&
                        lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL)
                        lpCurPlayer->SetTargetPosi(0, 0);
                    CancelAttack();
                }
                AutoCameraFlag = TRUE;
            }
        }
        else
        {
            ActionMouseClick[0] = 1;
        }

        AutoMouse_WM_Count++;

        if (SkillMasterFlag)
        {
            sinSkillMasterClose();
        }

        lpCurPlayer->MoveFlag = TRUE;
        DispEachMode = 0;

        if (hFocusWnd)
        {
            GetWindowText(hFocusWnd, szBuff, 240);
            if (szBuff[0] == 0)
            {
                hFocusWnd = 0;
                szLastWhisperName[0] = 0;
                LastWhisperLen = 0;
                InterfaceParty.chat_WhisperPartyPlayer_close();
                chatlistSPEAKERflagChg(0);
                SetIME_Mode(0);
                ChatScrollPoint = 0;
            }
        }
        break;

    case 0:
        if (Moving_DblClick)
        {
            TraceMode_DblClick = TRUE;
            Moving_DblClick = 0;
            lpCurPlayer->MoveFlag = TRUE;
            ActionMouseClick[0] = 2;
        }
        else
        {
            if (!lpCharMsTrace && !lpMsTraceItem)
            {
                lpCurPlayer->SetAction(0);
            }
        }
        return TRUE;

    case 11:
        if (hFocusWnd)
        {
            GetWindowText(hFocusWnd, szBuff, 240);
            if (szBuff[0] == 0)
            {
                hFocusWnd = 0;
                SetIME_Mode(0);
                ChatScrollPoint = 0;
            }
        }
        if (sinSkill.pRightSkill && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK &&
            lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL)
        {
            if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_EAT)
            {
                if (OpenPlaySkill(sinSkill.pRightSkill))
                    break;
            }
        }

        if (!ActionGameMode)
        {
            if (lpCharSelPlayer)
            {
                SelMouseButton = 2;
                TraceAttackPlay();
                AutoCameraFlag = FALSE;
                lpCurPlayer->MoveFlag = TRUE;
                DispEachMode = 0;
            }
        }
        else
        {
            ActionMouseClick[1] = TRUE;
        }
        AutoMouse_WM_Count++;
        break;

    case 10:
        if (!lpCharMsTrace && !lpMsTraceItem)
        {
            lpCurPlayer->SetAction(0);
        }
        break;

    case 3:
        extern int msX;
        extern int msY;
        extern int dist;
        extern int anx;
        extern int CaTarDist;
        extern int CaMovAngle;
        extern int CameraInvRot;

        ay = msY * 4;
        ax = msX * 8;

        if (ay)
        {
            if (!CaTarDist) CaTarDist = dist;
            CaTarDist -= ay;

            if (CaTarDist < 100)
            {
                if (anx <= 40)
                {
                    if (CaTarDist < 40)
                        CaTarDist = 40;
                }
                else
                    CaTarDist = 100;
            }

            if (CaTarDist > 440)
            {
                CaTarDist = 440;
            }
        }

        if (ax)
        {
            if (CameraInvRot) ax = -ax;

            az = ANGLE_45 >> 1;
            if (ax < -az) ax = -az;
            if (ax > az) ax = az;

            CaMovAngle += ax;
        }

        return TRUE;

    case 4:
        if (DebugPlayer)
        {
            extern int msY;
            extern int msX;
            extern int any_pt;
            extern int anx;

            ay = msY * 2;
            ax = msX * 2;

            any_pt += ax;
            anx += ay;

            any_pt &= ANGCLIP;
            anx &= ANGCLIP;
        }
        return TRUE;
    }

    if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_ATTACK ||
        lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_SKILL ||
        lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_YAHOO
        ) return FALSE;

    if (lpCurPlayer->MoveFlag)
    {
        if (MsTraceMode)
        {
            lpCurPlayer->Angle.y = GetMouseSelAngle();
        }
        else
        {
            if (ActionGameMode)
            {
                extern int GetActionGame_PlayMouseAngle();
                lpCurPlayer->Angle.y = GetActionGame_PlayMouseAngle();
            }
            else
            {
                extern int GetPlayMouseAngle();
                lpCurPlayer->Angle.y = GetPlayMouseAngle();
            }
        }
    }

    return TRUE;
}
void ShowGameNotification(HWND hWnd, const char* title, const char* message) {

    NOTIFYICONDATA ntf = { 0 };
    ntf.cbSize = sizeof(ntf);
    ntf.hWnd = hWnd;
    ntf.uFlags = NIF_ICON | NIF_INFO;
    ntf.dwInfoFlags = NIIF_USER | NIIF_LARGE_ICON;

    ntf.hIcon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_DEFAULT_ICON));

    if (!Shell_NotifyIcon(NIM_ADD, &ntf)) Shell_NotifyIcon(NIM_MODIFY, &ntf);

    strcpy_s(ntf.szInfoTitle, title);
    strcpy_s(ntf.szInfo, message);
    //by ViGo , discord: 7vig0
    if (!Shell_NotifyIcon(NIM_ADD, &ntf)) Shell_NotifyIcon(NIM_MODIFY, &ntf);

}
// ===== FUNÇÃO PRINCIPAL WinMain =====
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, INT nCmdShow)
{



    SetUnhandledExceptionFilter(unhandled_handler);
    HookAPI("kernel32.dll", "SetUnhandledExceptionFilter", RedirectedSetUnhandledExceptionFilter);

    if (strcmp(lpCmdLine, "Zaraki_APT-2") != 0)
    {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        CreateProcess("LauncherUpdater.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
        exit(0);
    }

    EnumWindows(EnumWindowsProc, 0);
    int LimiteClient = 4;
    if (iNumWindowsFound > LimiteClient)
    {
        ExitProcess(0);
    }

#ifdef _DEBUG
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
#endif

    pcAntiCheat = new CAntiCheat();
    pcAntiCheat->AddNewThreadException(GetCurrentThreadId());
    pcAntiCheat->CheckThread();

    AntiDebugger();

    Utils_Log(LOG_DEBUG, " ------------ WINMAIN ---------------- ");
    MSG msg;
    WNDCLASSEX wndclass = { 0 };
    hinst = hInst;
    int sx, sy;

    lstrcpy(szCmdLine, lpCmdLine);

    initSinCos();
    smConfigDecode("");
    ReadShotcutMessage("ShortCut.ini");
    DecodeCmdLine(lpCmdLine);

    InitializeCriticalSection(&cSection);
    InitializeCriticalSection(&cDrawSection);
    InitializeCriticalSection(&cSection_Main);
    srand(GetCurrentTime());

    char AutoAdjust[10] = { 0 };
    LeIniStr("Screen", "AutoAdjust", "game.ini", AutoAdjust);

    {
        char WindowMode[10] = { 0 };
        LeIniStr("Screen", "Windowed", "game.ini", WindowMode);

        if (lstrcmpiA(WindowMode, "True") == 0)
            smConfig.WinMode = 1;
        else
            smConfig.WinMode = 0;
    }

    {
        int Width = LeIniInt("Screen", "Width", "game.ini");
        int Height = LeIniInt("Screen", "Height", "game.ini");

        smConfig.ScreenSize.x = Width;
        smConfig.ScreenSize.y = Height;
    }

    {
        int BPP = LeIniInt("Graphics", "BitDepth", "game.ini");
        smConfig.ScreenColorBit = BPP;
    }

    {
        char Quality[10] = { 0 };
        LeIniStr("Graphics", "HighTextureQuality", "game.ini", Quality);

        if (lstrcmpiA(Quality, "True") == 0)
            smConfig.TextureQuality = 0;
        else
            smConfig.TextureQuality = 3;
    }

    {
        char Sound[10] = { 0 };
        LeIniStr("Audio", "NoSound", "game.ini", Sound);

        if (lstrcmpiA(Sound, "True") == 0)
            smConfig.BGM_Mode = 1;
        else
            smConfig.BGM_Mode = 0;
    }

    {
        char FOG[10] = { 0 };
        LeIniStr("Camera", "FarCameraSight", "game.ini", FOG);

        if (lstrcmpiA(FOG, "True") == 0)
            CameraSight = 1;
        else
            CameraSight = 0;
    }

    {
        char cam[10] = { 0 };
        LeIniStr("Camera", "InvertedCamera", "game.ini", cam);

        CameraInvRot = 0;

        if (lstrcmpiA(cam, "On") == 0)
            CameraInvRot = 1;
        else
            CameraInvRot = 0;
    }

    {
        char autoadjust[10] = { 0 };
        LeIniStr("Screen", "AutoAdjust", "game.ini", autoadjust);

        if (lstrcmpiA(autoadjust, "True") == 0)
            bAdjustWindow = true;
        else
            bAdjustWindow = false;
    }




    {
        const char* ServerIP = "46.224.228.49";
        int Mundo = LeIniInt("ConnectServer", "Mundo", "game.ini");
        int ServerPort = 0;

        switch (Mundo)
        {
        case 1: ServerPort = 40627; break;
        case 2: ServerPort = 40628; break;
        case 3: ServerPort = 60629; break;
        default: ServerPort = 40627; break;
        }

        printf("DEBUG: Mundo lido: %d\n", Mundo);
        printf("DEBUG: Porta definida: %d\n", ServerPort);

        lstrcpy(smConfig.szServerIP, ServerIP);
        lstrcpy(smConfig.szDataServerIP, ServerIP);
        smConfig.dwServerPort = ServerPort;
        TCP_SERVPORT = ServerPort;
    }

    InitDirectSound();

    WinSizeX = smConfig.ScreenSize.x;
    WinSizeY = smConfig.ScreenSize.y;
    WinColBit = smConfig.ScreenColorBit;
    WindowMode = smConfig.WinMode;

    sx = WinSizeX;
    sy = WinSizeY;

    if (!hPreInst)
    {
        wndclass.cbSize = sizeof(WNDCLASSEX);
        wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wndclass.lpfnWndProc = WndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInst;
        wndclass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_DEFAULT_ICON));
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wndclass.lpszMenuName = NULL;
        wndclass.lpszClassName = szAppName;
        RegisterClassEx(&wndclass);
    }

    if (WindowMode)
    {
        UINT uWindowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

        RECT srcRect = { 0, 0, sx, sy };
        AdjustWindowRect(&srcRect, uWindowStyle, FALSE);

        srcRect.right -= srcRect.left;
        srcRect.bottom -= srcRect.top;

        int iX, iY, iWindowW, iWindowH;

        iX = (GetSystemMetrics(SM_CXSCREEN) / 2) - (srcRect.right / 2);
        iY = (GetSystemMetrics(SM_CYSCREEN) / 2) - (srcRect.bottom / 2);
        iWindowW = srcRect.right;
        iWindowH = srcRect.bottom;

        hwnd = CreateWindowExA(NULL, szAppName, "PristonPK",
            uWindowStyle, iX, iY, iWindowW, iWindowH, NULL, NULL,
            hInst, NULL);
    }
    else
    {
        hwnd = CreateWindow(szAppName, "PristonPK",
            WS_VISIBLE | WS_POPUP | WS_EX_TOPMOST, CW_USEDEFAULT,
            CW_USEDEFAULT, sx, sy, NULL, NULL,
            hInst, NULL);
    }

    SetWindowTextA(hwnd, "NorthGoblin");

    if (InitD3D(hwnd) == NULL)
        return FALSE;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    ShowCursor(TRUE);

    hTextWnd = CreateWindow("EDIT", "",
        WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_WANTRETURN,
        10, 400, 500, 40,
        hwnd, (HMENU)IDC_TEXT,
        hInst, NULL);

    OldEditProc01 = (WNDPROC)SetWindowLong(hTextWnd, GWL_WNDPROC, (LONG)EditWndProc01);
    IMETest.SetHWND(hTextWnd);

    FONTHANDLER->Init();
    FONTHANDLER->CreateFont("Arial", 15, 0, FALSE, FALSE, -1);
    FONTHANDLER->CreateFont("Arial", 15, 6, FALSE, FALSE, -1);
    FONTHANDLER->CreateFont("Arial", 15, 0, FALSE, FALSE, -1);
    FONTHANDLER->CreateFont("Century Schoolbook", 15, 6, FALSE, FALSE, -1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(GRAPHICDEVICE);

    Discord_Handle.Initialize();
    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Arial.ttf", 14);

    InitLoadingLamp(hwnd);

    hImc = ImmGetContext(hwnd);
    hImcEdit = ImmGetContext(hTextWnd);

    SetIME_Mode(0);
    SetCreateFont();
    TextMode = 0;

    InitGameSocket();

    SetGameMode(1);
    CharacterName1[0] = 0;
    CharacterName2[0] = 0;

    SetTimer(hwnd, 0, GAME_WORLDTIME_MIN / 4, NULL);

    SetForegroundWindow(hwnd);

    SYSTEM_INFO sys_info;
    GetSystemInfo((LPSYSTEM_INFO)&sys_info);

    bool isMultiCore = sys_info.dwNumberOfProcessors > 1;
    timer->SetMultiCore(FALSE);

    while (TRUE)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);

            if (msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP)
            {
                if (msg.wParam != 0xF4 && msg.wParam != VK_F10) continue;
            }

            DispatchMessage(&msg);
        }
        else
        {
            EnterCriticalSection(&cSection_Main);
            PlayD3D();
            PlayRecvMessageQue();
            LeaveCriticalSection(&cSection_Main);
        }

        if (quit != 0 && !dwTradeMaskTime)
        {
            if (GameMode != 2) break;

            if (smWsockServer && !QuitSave)
            {
                if (cTrade.OpenFlag)
                {
                    SendRequestTrade(cTrade.TradeCharCode, 3);
                    cTrade.CancelTradeItem();
                }

                if (cWareHouse.OpenFlag)
                {
                    cWareHouse.RestoreInvenItem();
                }

                if (Caravana::GetInstance()->OpenFlag)
                {
                    Caravana::GetInstance()->RestoreInvenItem();
                }

                cInvenTory.ResetMouseItem();

                SaveGameData();
                QuitSave = TRUE;
            }
            else
            {
                if (!smWsockServer || GetSaveResult() == TRUE) break;
                if ((dwPlayTime - rsRecorder.dwRecordTime) > 15000) break;
            }
        }
    }

    SetGameMode(0);

    Discord_Handle.Shutdown();

    if (pcAntiCheat)
    {
        delete pcAntiCheat;
        pcAntiCheat = nullptr;
    }

    GAMECOREHANDLE->Shutdown();

    DeleteObject(hFont);
    CloseBindSock();
    CloseD3d();

    if (fpNetLog) fclose(fpNetLog);

    if (szExitInfo_URL[0])
        ShellExecute(NULL, NULL, szExitInfo_URL, NULL, NULL, NULL);

    return msg.wParam;
}



int msX = 0, msY = 0;
int msXo = 0, msYo = 0;
int xPs;
int yPs;

POINT pCursorPos;
POINT pRealCursorPos;
DWORD GameWindowMessage(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam);
DWORD dwTimerCount = 0;

BOOL DisplayIME = FALSE;

int SetIME_Mode(BOOL mode)
{
    if (mode)
    {
        DisplayIME = TRUE;
        ImmSetOpenStatus(hImc, TRUE);
#ifdef _LANGUAGE_JAPANESE
        ImmSetConversionStatus(hImc, IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE, IME_SMODE_PHRASEPREDICT);
        ImmSetConversionStatus(hImcEdit, IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE, IME_SMODE_PHRASEPREDICT);
#else
        ImmSetConversionStatus(hImc, IME_CMODE_NATIVE, IME_CMODE_NATIVE);
        ImmSetConversionStatus(hImcEdit, IME_CMODE_NATIVE, IME_CMODE_NATIVE);
#endif
    }
    else
    {
        ImmSetConversionStatus(hImc, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);
        ImmSetConversionStatus(hImcEdit, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);
        ImmSetOpenStatus(hImc, FALSE);
        DisplayIME = FALSE;
    }

    return TRUE;
}

int CheckCode_2Byte(char* Str)
{
#ifdef _LANGUAGE_ENGLISH
    return 1;
#endif

#ifdef _LANGUAGE_THAI
    if (CheckTHAI_ptr(Str, 0) == 1) return 1;
    else if (CheckTHAI_ptr(Str, 0) == 2) return 2;
    return 1;
#endif

#ifdef _LANGUAGE_JAPANESE
    if (CheckJTS_ptr(Str, 0) == 2)
    {
        return 2;
    }
#else
    if (Str[0] < 0)
    {
        return 2;
    }
#endif

    return 1;
}

extern bool msgHistoryUp;
extern bool msgHistoryDown;
extern bool FOCUS_CHAT;
extern string strMessage;

LRESULT CALLBACK EditWndProc01(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    wmId = LOWORD(wParam);
    wmEvent = HIWORD(wParam);

    switch (message)
    {
    case WM_KEYDOWN:
#ifdef _IME_ACTIVE
        IMETest.GetInfoPerTime();
#endif
        break;
    }
    return CallWindowProc(OldEditProc01, hWnd, message, wParam, lParam);
}

BOOL bSettings;

#ifdef _LANGUAGE_JAPANESE
char g_bufEdit[256];
char g_bufFixed[256];

int WndProc_Japanese(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HIMC imc;
    static DWORD conv = IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE | IME_CMODE_ROMAN;
    static DWORD sent = IME_SMODE_PHRASEPREDICT;
    static BOOL setFont = FALSE;

    switch (messg)
    {
    case WM_IME_COMPOSITION:
        if ((imc = ImmGetContext(hWnd)))
        {
            if (lParam & GCS_RESULTSTR)
            {
                ZeroMemory(g_bufFixed, 256);
                ImmGetCompositionString(imc, GCS_RESULTSTR, g_bufFixed, 256);
            }
            else if (lParam & GCS_COMPSTR)
            {
                ZeroMemory(g_bufEdit, 256);
                ImmGetCompositionString(imc, GCS_COMPSTR, g_bufEdit, 256);
            }
            ImmReleaseContext(hWnd, imc);
        }
        break;

    case WM_IME_NOTIFY:
        switch (wParam)
        {
        case IMN_SETCONVERSIONMODE:
        case IMN_SETSENTENCEMODE:
            if ((imc = ImmGetContext(hWnd)))
            {
                ImmGetConversionStatus(imc, &conv, &sent);
                ImmReleaseContext(hWnd, imc);
            }
            break;

        case IMN_SETOPENSTATUS:
            if ((imc = ImmGetContext(hWnd)))
            {
                if (ImmGetOpenStatus(imc))
                {
                    ImmSetConversionStatus(imc, conv, sent);
                }
                else
                {
                    ImmGetConversionStatus(imc, &conv, &sent);
                }
                ImmReleaseContext(hWnd, imc);
            }

            if (!setFont && (imc = ImmGetContext(hWnd)))
            {
                LOGFONT lf;
                ZeroMemory(&lf, sizeof(LOGFONT));
                lf.lfHeight = 12;
                lf.lfItalic = FALSE;
                lf.lfUnderline = FALSE;
                lf.lfStrikeOut = FALSE;
                lf.lfCharSet = OEM_CHARSET;
                lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
                lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
                lf.lfQuality = DEFAULT_QUALITY;
                lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
                strcpy(lf.lfFaceName, _T("‚l‚r ‚oƒSƒVƒbƒN"));
                ImmSetCompositionFont(imc, &lf);
                ImmReleaseContext(hWnd, imc);
                setFont = TRUE;
            }
            break;

        case IMN_OPENCANDIDATE:
        case IMN_CHANGECANDIDATE:
            if ((imc = ImmGetContext(hWnd)))
            {
                CANDIDATEFORM cf;
                ZeroMemory(&cf, sizeof(CANDIDATEFORM));
                cf.dwStyle = CFS_CANDIDATEPOS;
                cf.ptCurrentPos.x = 100000;
                cf.ptCurrentPos.y = 100000;
                ImmSetCandidateWindow(imc, &cf);
                ImmReleaseContext(hWnd, imc);
            }
            break;
        }
        break;
    }

    return TRUE;
}
#endif

extern void clan_Mouse(int msg, WPARAM wParam);

BOOL bCtrl = FALSE;
bool bCaptureScreen = false;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LONG APIENTRY WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    short zDelta;
    char strBuff[256] = { 0 };
    char strBuff2[256] = { 0 };
    char* lpString;
    int len, CrCode;

    ImGui_ImplWin32_WndProcHandler(hWnd, messg, wParam, lParam);

    switch (messg)
    {
    case WM_SETCURSOR:
        if ((HWND)wParam == hWnd)
        {
            MOUSEHANDLER->SetCursorGame(CursorClass);
            return TRUE;
        }
        break;
    case WM_NCRBUTTONDOWN:
    case WM_NCLBUTTONDOWN:
    case WM_EXITSIZEMOVE:
    case WM_NCLBUTTONDBLCLK:
        CancelAttack();
        return DefWindowProc(hWnd, messg, wParam, lParam);
        break;

    case WM_SIZE:
        if (smConfig.WinMode)
        {
            if (wParam == SIZE_MAXIMIZED && Settings::GetInstance()->bAutoAdjust)
            {
                WinSizeX = LOWORD(lParam);
                WinSizeY = HIWORD(lParam);

                smScreenWidth = WinSizeX;
                smScreenHeight = WinSizeY;

                smConfig.ScreenSize.x = WinSizeX;
                smConfig.ScreenSize.y = WinSizeY;

                extern void resizeOpening();
                extern void resizeLogin();

                resizeOpening();
                resizeLogin();

                MidX = WinSizeX / 2;
                MidY = WinSizeY / 2;

                g_fWinSizeRatio_X = float(WinSizeX) / 800.f;
                g_fWinSizeRatio_Y = float(WinSizeY) / 600.f;

                viewdistZ = ((WinSizeY / 3) * 4);

                SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 24000.f);

                smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
                smRender.SMMULT_PERSPECTIVE_HEIGHT = 0;

                SetDisplayMode(hWnd, WinSizeX, WinSizeY, WinColBit);

                if (GRAPHICENGINE && GAMECOREHANDLE && GameMode == 2)
                    GAMECOREHANDLE->OnResolutionChanged();
            }
            else
            {
                if (wParam == SIZE_RESTORED)
                {
                    WinSizeX = LOWORD(lParam);
                    WinSizeY = HIWORD(lParam);

                    smScreenWidth = WinSizeX;
                    smScreenHeight = WinSizeY;

                    smConfig.ScreenSize.x = WinSizeX;
                    smConfig.ScreenSize.y = WinSizeY;

                    extern void resizeOpening();
                    extern void resizeLogin();

                    resizeOpening();
                    resizeLogin();

                    MidX = WinSizeX / 2;
                    MidY = WinSizeY / 2;

                    g_fWinSizeRatio_X = float(WinSizeX) / 800.f;
                    g_fWinSizeRatio_Y = float(WinSizeY) / 600.f;

                    viewdistZ = ((WinSizeY / 3) * 4);

                    SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);

                    smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
                    smRender.SMMULT_PERSPECTIVE_HEIGHT = 0;

                    SetDisplayMode(hWnd, WinSizeX, WinSizeY, WinColBit);

                    if (GRAPHICENGINE && GAMECOREHANDLE && GameMode == 2)
                        GAMECOREHANDLE->OnResolutionChanged();
                }
            }
        }
        break;
    case WM_CALLMEMMAP:
        void PacketParsing();
        PacketParsing();
        break;

    case WM_CREATE:
        break;

    case WM_CLOSE:
        QuitGame();
        break;

    case WSA_ACCEPT:
        WSAMessage_Accept(wParam, lParam);
        break;

    case WSA_READ:
        WSAMessage_Read(wParam, lParam);
        break;

    case SWM_RECVSUCCESS:
        RecvPlayData((smTHREADSOCK*)wParam);
        break;

    case SWM_MCONNECT:
        ConnectOtherPlayer(wParam);
        break;

    case SWM_MDISCONNECT:
        ((smWINSOCK*)wParam)->CloseSocket();
        break;

    case WM_KEYDOWN:
        if (GetForegroundWindow() != hWnd)
            return 0;

        // ===== MINI SKILL BAR - SHORTCUTS =====
        if (g_pMiniSkillBar && g_pMiniSkillBar->IsVisible()) {
            switch (wParam) {
            case VK_F1: case VK_F2: case VK_F3: case VK_F4:
            case VK_F5: case VK_F6: case VK_F7: case VK_F8:
                if (g_pMiniSkillBar->HandleShortKey(wParam)) {
                    VRKeyBuff[wParam] = 1;
                    return 0;
                }
                break;
            }
        }
        // =======================================

        if (!NewShop::GetInstance()->editingNick)
        {
            if (KEYBOARDHANDLER->OnKeyPress(wParam, TRUE) && !sinMessageBoxShowFlag)
                return 0;
        }

        if (g_IsDxProjectZoomIn > 0)
        {
            if (KeyFullZoomMap(wParam))
            {
                VRKeyBuff[wParam] = 1;
                break;
            }
            else
            {
                SetFullZoomMap(0);
                pCursorPos.x = g_iFzmCursorPosX;
                pCursorPos.y = g_iFzmCursorPosY;

                if (wParam == VK_ESCAPE)
                    break;
            }
        }

        if (wParam == VK_RETURN)
        {
            keydownEnt = 1;
        }

        if (wParam == VK_CONTROL) VRKeyBuff[wParam] = 1;

        if (!VRKeyBuff[VK_CONTROL] && wParam == VK_F12)
        {
            static bool fullscreen = false;

            if (!fullscreen)
            {
                LONG value = GetWindowLong(hWnd, GWL_STYLE);
                SetWindowLong(hWnd, GWL_STYLE, value & 0xDE33FFFF);

                value = GetWindowLong(hWnd, GWL_EXSTYLE);
                SetWindowLong(hWnd, GWL_STYLE, value & 0xFFFDFDFE);
                SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOOWNERZORDER);

                ShowWindow(hWnd, SW_SHOWMAXIMIZED);
                fullscreen = true;
                Sleep(200);
            }
            else
            {
                ShowWindow(hWnd, SW_SHOWDEFAULT);
                SetWindowLong(hWnd, GWL_STYLE, 0x94CF0008);
                SetWindowLong(hWnd, GWL_EXSTYLE, 0x100);

                fullscreen = false;
                Sleep(200);
            }
        }

        if (wParam == VK_F12 && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
        {
            CaptureOpening();
            chaSiege.bCaptureScreen = TRUE;
            chaSiege.dwTickScreen = GetTickCount();
            Capture(hwnd);
        }

        if (!hFocusWnd)
        {
            if (!VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag && VRKeyBuff[wParam] == 0)
            {
                if (wParam == VK_F1 || wParam == VK_F2 || wParam == VK_F3 || wParam == VK_F4 || wParam == VK_F5 ||
                    wParam == VK_F6 || wParam == VK_F7 || wParam == VK_F8 || wParam == VK_F9 || wParam == VK_F10)
                {
                    SetChatingLine("");
                }
            }
        }

        if (hFocusWnd)
        {
            lpString = 0;
            CrCode = 0;
            if (!VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag)
            {
                if (wParam == VK_F1 && szShotCutMessage[1][0]) lpString = szShotCutMessage[1];
                if (wParam == VK_F2 && szShotCutMessage[2][0]) lpString = szShotCutMessage[2];
                if (wParam == VK_F3 && szShotCutMessage[3][0]) lpString = szShotCutMessage[3];
                if (wParam == VK_F4 && szShotCutMessage[4][0]) lpString = szShotCutMessage[4];
                if (wParam == VK_F5 && szShotCutMessage[5][0]) lpString = szShotCutMessage[5];
                if (wParam == VK_F6 && szShotCutMessage[6][0]) lpString = szShotCutMessage[6];
                if (wParam == VK_F7 && szShotCutMessage[7][0]) lpString = szShotCutMessage[7];
                if (wParam == VK_F8 && szShotCutMessage[8][0]) lpString = szShotCutMessage[8];
                if (wParam == VK_F9 && szShotCutMessage[9][0]) lpString = szShotCutMessage[9];
                if (wParam == VK_F10 && szShotCutMessage[0][0]) lpString = szShotCutMessage[0];

                if (lpString)
                {
#ifdef _LANGUAGE_VEITNAM
                    GetWindowText(hFocusWnd, strBuff2, 80);
#else
                    GetWindowText(hFocusWnd, strBuff2, 90);
#endif
                    len = lstrlen(strBuff2) + lstrlen(lpString);
                    if (len < 80)
                    {
                        lstrcat(strBuff2, lpString);
                        if (strBuff2[len - 1] == 0x0D)
                        {
                            len--;
                            strBuff2[len] = 0;
                            CrCode = TRUE;
                        }
                        SetWindowText(hFocusWnd, strBuff2);
                        SendMessage(hFocusWnd, EM_SETSEL, len, len);
                    }
                }
            }
            if (!sinMessageBoxShowFlag &&
                ((wParam == VK_RETURN && VRKeyBuff[wParam] == 0 && !VRKeyBuff[VK_CONTROL]) || CrCode == TRUE))
            {
                GetWindowText(hFocusWnd, strBuff2, 90);

                if (GameMode == 2)
                    cHelpPet.PetOnOff(strBuff2);

                if (strBuff2[0])
                {
                    if (strBuff2[0] == '/' || (smConfig.DebugMode && strBuff2[0] == '~') || strBuff2[0] == '`' || strBuff2[0] == '@')
                        wsprintf(strBuff, "%s", strBuff2);
                    else
                    {
                    }

                    if (GameMode == 2)
                    {
                        if (chatlistSPEAKERflag() && lstrlen(strBuff) > LastWhisperLen)
                        {
                            SetClanChatting();

                            if (szLastWhisperName[0])
                            {
                                szLastWhisperName[0] = 0;
                            }
                        }
                        else
                            if (szLastWhisperName[0] && lstrlen(strBuff) > LastWhisperLen)
                            {
                                WhisperPartyPlayer(szLastWhisperName);
                            }
                            else
                            {
                                SetWindowText(hFocusWnd, "");
                                szLastWhisperName[0] = 0;
                                LastWhisperLen = 0;
                                InterfaceParty.chat_WhisperPartyPlayer_close();
                                chatlistSPEAKERflagChg(0);
                            }
                    }
                    else
                    {
                        hFocusWnd = 0;
                    }
                }
                else
                {
                    hFocusWnd = 0;

                    if (GameMode == 2)
                    {
                        szLastWhisperName[0] = 0;
                        LastWhisperLen = 0;
                        InterfaceParty.chat_WhisperPartyPlayer_close();
                        chatlistSPEAKERflagChg(0);
                    }
                }
            }

            if (GameMode == 2)
            {
                if (wParam == VK_TAB && VRKeyBuff[wParam] == 0)
                {
                    IsClanChatting();
                    break;
                }
                if (wParam == VK_ESCAPE && VRKeyBuff[wParam] == 0)
                {
                    if (SendMessage(hTextWnd, EM_GETLIMITTEXT, 78, 0) >= 78)
                    {
                        hFocusWnd = 0;
                        cInterFace.ChatFlag = 0;
                        szLastWhisperName[0] = 0;
                        LastWhisperLen = 0;
                        InterfaceParty.chat_WhisperPartyPlayer_close();
                        chatlistSPEAKERflagChg(0);
                    }
                }
            }
            break;
        }

        if (wParam == VK_F10)
        {
            if (Settings::GetInstance()->IsOpen())
                Settings::GetInstance()->Close();
            else
                Settings::GetInstance()->Open();
        }

        if (wParam == VK_ESCAPE && VRKeyBuff[wParam] == 0)
        {
            if (VRKeyBuff[VK_SHIFT])
                QuitGame();
            else
            {
                if (cInterFace.ChatFlag)
                    cInterFace.ChatFlag = 0;
                else
                {
                    if (cInvenTory.OpenFlag || cCharStatus.OpenFlag || CSKILL->OpenFlag || ExitButtonClick)
                    {
                        cInterFace.CheckAllBox(SIN_ALL_CLOSE);
                    }
                    else
                    {
                        if (InterfaceParty.PartyPosState == PARTY_PROCESS)
                        {
                            InterfaceParty.PartyPosState = PARTY_END;
                            InterfaceParty.qN_Pressf_CLEAR();
                        }
                        else
                        {
                            ExitButtonClick = 1;
                        }
                    }
                }
            }
        }

        if (GameMode == 2)
        {
            if (GameWindowMessage(hWnd, messg, wParam, lParam) == FALSE) break;
        }
        if (GameMode == 2 && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField] &&
            StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM)
        {
        }
        else
        {
            if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField] &&
                StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_CASTLE)
            {
            }
            else
            {
            }
        }

        VRKeyBuff[wParam] = 1;
        clan_Mouse(WM_KEYDOWN, wParam);

        break;

    case WM_KEYUP:
        if (GetForegroundWindow() != hWnd)
            return 0;
        if (KEYBOARDHANDLER->OnKeyPress(wParam, FALSE))
            return 0;

        if (g_IsDxProjectZoomIn > 0)
        {
            if (KeyFullZoomMap(wParam))
            {
                VRKeyBuff[wParam] = 0;
                break;
            }
        }

        if (hFocusWnd)
        {
            SendMessage(hFocusWnd, messg, wParam, lParam);
        }
        VRKeyBuff[wParam] = 0;
        clan_Mouse(WM_KEYUP, wParam);
        break;

    case WM_SYSKEYDOWN:
        if (wParam == VK_F10)
        {
            PostMessage(hWnd, WM_KEYDOWN, wParam, lParam);
            return FALSE;
        }
        if (hFocusWnd)
            SendMessage(hFocusWnd, messg, wParam, lParam);
        break;

    case WM_SYSKEYUP:
        if (GetForegroundWindow() != hWnd)
            return 0;
        if (KEYBOARDHANDLER->OnKeyPress(wParam, FALSE))
            return 0;

        if (wParam == VK_F10)
        {
            PostMessage(hWnd, WM_KEYUP, wParam, lParam);
            return FALSE;
        }
        if (hFocusWnd)
            SendMessage(hFocusWnd, messg, wParam, lParam);
        break;

    case WM_MOUSEMOVE:
    {
        int iX = (int)round(LOWORD(lParam));
        int iY = (int)round(HIWORD(lParam));

        MOUSEHANDLER->OnMouseMoveHandler(iX, iY);

        if (g_IsDxProjectZoomIn)
        {
            g_iFzmCursorPosX = LOWORD(lParam);
            g_iFzmCursorPosY = HIWORD(lParam);

            if (g_iFzmCursorPosX > 30 * g_fWinSizeRatio_X && g_iFzmCursorPosX < 350 * g_fWinSizeRatio_X &&
                g_iFzmCursorPosY > 338 * g_fWinSizeRatio_Y && g_iFzmCursorPosY < 578 * g_fWinSizeRatio_Y)
            {
                if (g_iFzmCursorFocusGame == 0)
                {
                    g_iFzmCursorFocusGame = 1;

                    xPs = pCursorPos.x = msXo = int(((float)g_iFzmCursorPosX - g_fZoomInAdd_x) * g_fZoomInDiv_x);
                    yPs = pCursorPos.y = msYo = int(((float)g_iFzmCursorPosY - g_fZoomInAdd_y) * g_fZoomInDiv_y);
                }

                xPs = int(((float)g_iFzmCursorPosX - g_fZoomInAdd_x) * g_fZoomInDiv_x);
                yPs = int(((float)g_iFzmCursorPosY - g_fZoomInAdd_y) * g_fZoomInDiv_y);

                AutoMouse_Distance += abs(pCursorPos.x - xPs);
                AutoMouse_Distance += abs(pCursorPos.y - yPs);

                pCursorPos.x = xPs;
                pCursorPos.y = yPs;

                msX = msXo - xPs;
                msY = msYo - yPs;

                msXo = xPs;
                msYo = yPs;

                if ((wParam & MK_MBUTTON))
                    SetMousePlay(3);
                else
                {
                    if (wParam == MK_LBUTTON || TraceMode_DblClick)
                        SetMousePlay(2);
                    else if (wParam == MK_RBUTTON)
                        SetMousePlay(4);
                }
                dwLastMouseMoveTime = dwPlayTime;
            }
            else
                g_iFzmCursorFocusGame = 0;
        }
        else
        {
            xPs = LOWORD(lParam);
            yPs = HIWORD(lParam);

            if (xPs > smConfig.ScreenSize.x + 200)
                break;

            AutoMouse_Distance += abs(pCursorPos.x - xPs);
            AutoMouse_Distance += abs(pCursorPos.y - yPs);

            g_iFzmCursorPosX = pCursorPos.x = xPs;
            g_iFzmCursorPosY = pCursorPos.y = yPs;
            msX = msXo - xPs;
            msY = msYo - yPs;

            msXo = xPs;
            msYo = yPs;

            if ((wParam & MK_MBUTTON))
                SetMousePlay(3);
            else
            {
                if (wParam == MK_LBUTTON || TraceMode_DblClick)
                    SetMousePlay(2);
                else
                    if (wParam == MK_RBUTTON)
                        SetMousePlay(4);
            }
        }

        dwLastMouseMoveTime = dwPlayTime;
        break;
    }

    case WM_LBUTTONDBLCLK:
        MouseDblClick = TRUE;

        if (GameMode == 2)
        {
            SKILLMANAGERHANDLER->OnMouseClickSkillPet();

            dsMenuCursorPos(&pCursorPos, 2);
            if (StopCharMotion(pCursorPos.x, pCursorPos.y) != TRUE)
            {
                Moving_DblClick = TRUE;
                MousePos_DblClick.x = xPs;
                MousePos_DblClick.y = yPs;
                MousePos_DblClick.z = 0;
            }
            dsMenuCursorPos(&pCursorPos, 0);
        }
        break;

    case WM_LBUTTONDOWN:
        if (GetForegroundWindow() != hWnd)
            return 0;

        if (MOUSEHANDLER->OnMouseClickHandler(messg))
            return 0;
        // Verifica clique no seletor de servidor
        if (pCursorPos.x >= rcServerSelector.left && pCursorPos.x <= rcServerSelector.right &&
            pCursorPos.y >= rcServerSelector.top && pCursorPos.y <= rcServerSelector.bottom)
        {
            bShowServerSelector = !bShowServerSelector;
            return 0;
        }

        // Verifica clique nas opções
        if (bShowServerSelector)
        {
            int serverX = WinSizeX - 200;
            int serverY = 30;
            int selectorX = serverX;
            int selectorY = serverY + 22;

            for (int i = 0; i < 2; i++)  //NUMERO DE SERVIDORES
            {
                int optionY = selectorY + 5 + (i * 25);

                if (pCursorPos.x >= selectorX && pCursorPos.x <= selectorX + 180 &&
                    pCursorPos.y >= optionY - 2 && pCursorPos.y <= optionY + 20)
                {
                    // Muda o mundo
                    int newWorld = i + 1;

                    // Salva no game.ini
                    char szMundo[10];
                    sprintf(szMundo, "%d", newWorld);
                    WritePrivateProfileStringA("ConnectServer", "Mundo", szMundo, ".\\game.ini");
                    // FORÇA O SISTEMA DE ARQUIVOS A ATUALIZAR (IMPORTANTE!)
                    char szFullPath[MAX_PATH];
                    GetCurrentDirectoryA(MAX_PATH, szFullPath);
                    strcat(szFullPath, "\\game.ini");
                    HANDLE hFile = CreateFileA(szFullPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                    if (hFile != INVALID_HANDLE_VALUE)
                    {
                        FlushFileBuffers(hFile);
                        CloseHandle(hFile);
                    }

                    // Atualiza o texto
                    sprintf(szServerName, "Servidor: %s",
                       newWorld == 1 ? "Babel" :
                       newWorld == 2 ? "Morion" : "Requiem");

                    // Atualiza o texto (apenas 2 mundos)
                    //sprintf(szServerName, "Servidor: %s",
                    //    newWorld == 1 ? "Babel" :
                    //    newWorld == 2 ? "Morion" : "Babel");  // Fallback para Babel se algo der errado

                    // Fecha o seletor
                    bShowServerSelector = false;

                    // Força a verificação de mudança
                    g_nLastWorldChecked = 0;  // Reseta para forçar leitura
                    g_dwLastWorldCheckTime = 0;

                    // CHAMA DIRETAMENTE A FUNÇÃO DE RECONEXÃO
                    int newPort = GetPortFromWorld(newWorld);
                    if (TCP_SERVPORT != newPort)
                    {
                        ReconnectToServer(newPort, newWorld);
                    }
                    return 0;
                }
            }

            // Clicou fora, fecha o seletor
            bShowServerSelector = false;
        }

        if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
        {
            SetMousePlay(1);
            sinLButtonDown();
            MouseButton[0] = TRUE;

            clan_Mouse(WM_LBUTTONDOWN, wParam);
        }
        else
        {
            g_FzmMouseButton[0] = TRUE;
        }
        if (GameMode == 2 && DisconnectFlag)
        {
            quit = TRUE;
        }

        break;

    case WM_LBUTTONUP:
        if (GetForegroundWindow() != hWnd)
            return 0;
        if (MOUSEHANDLER->OnMouseClickHandler(messg))
            return 0;

        if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame || MouseButton[0])
        {
            SetMousePlay(0);
            sinLButtonUp();

            MouseButton[0] = FALSE;
            MouseDblClick = FALSE;
            clan_Mouse(WM_LBUTTONUP, wParam);
        }
        else
        {
            MouseDblClick = FALSE;
            g_FzmMouseButton[0] = FALSE;
        }
        break;

    case WM_RBUTTONDOWN:
        if (GetForegroundWindow() != hWnd)
            return 0;
        if (MOUSEHANDLER->OnMouseClickHandler(messg))
            return 0;

        if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
        {
            SetMousePlay(11);
            MouseButton[1] = TRUE;
            clan_Mouse(WM_RBUTTONDOWN, wParam);
        }
        else
            g_FzmMouseButton[1] = TRUE;

        break;

    case WM_RBUTTONUP:
        if (GetForegroundWindow() != hWnd)
            return 0;
        if (MOUSEHANDLER->OnMouseClickHandler(messg))
            return 0;

        if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
        {
            SetMousePlay(10);
            sinRButtonUp();
            MouseButton[1] = FALSE;
            clan_Mouse(WM_RBUTTONUP, wParam);
        }
        else
            g_FzmMouseButton[1] = FALSE;

        break;

    case WM_MBUTTONDOWN:
        if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
        {
            clan_Mouse(WM_MBUTTONDOWN, wParam);
        }
        else
            g_FzmMouseButton[2] = TRUE;

        break;

    case WM_MBUTTONUP:
        if (g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame)
        {
            MouseButton[2] = FALSE;
            clan_Mouse(WM_MBUTTONUP, wParam);
        }
        else
            g_FzmMouseButton[2] = FALSE;

        break;

    case WM_MOUSEWHEEL:
        if (GetForegroundWindow() != hWnd)
            return 0;
        if (MOUSEHANDLER->OnMouseScrollHandler(GET_WHEEL_DELTA_WPARAM(wParam)))
            return 0;

        if (!NewShop::GetInstance()->openFlag && !NewShopTime::GetInstance()->openFlag && !MixWindow::GetInstance()->openFlag && !Roleta::GetInstance()->openFlag && !Roleta::GetInstance()->openRoleta)
        {
            if (hFocusWnd)
            {
                if (((short)HIWORD(wParam)) / 120 > 0 && sinChatEnter)
                {
                    if (ChatScrollPoint < 32 && ChatBuffCnt - ChatScrollPoint >= 14)
                        ChatScrollPoint += 1;
                }
                if (((short)HIWORD(wParam)) / 120 < 0 && sinChatEnter)
                {
                    if (ChatScrollPoint != 0)
                        ChatScrollPoint -= 1;
                }
            }

            if (g_IsDxProjectZoomIn <= 0 && !hFocusWnd || g_iFzmCursorFocusGame && !hFocusWnd)
            {
                zDelta = (short)HIWORD(wParam);

                if (cSinHelp.sinGetScrollMove(-zDelta / 16) == TRUE) break;
                if (TJBscrollWheel(zDelta) == TRUE) break;

                if (whAnx == ANX_NONE) whAnx = anx + zDelta;
                else whAnx += zDelta;
                AutoCameraFlag = FALSE;
            }
        }

        break;

    case WM_CHAR:
        if (GetForegroundWindow() != hWnd)
            return 0;
        if (KEYBOARDHANDLER->OnKeyChar(wParam))
            return 0;

        if (wParam == 0x0D || wParam == 0x0A || (GameMode == 2 && wParam == VK_TAB)) return TRUE;
        if (!smConfig.DebugMode && wParam == 22 && lpCurPlayer->szChatMessage[0]) return TRUE;

    case WM_IME_CHAR:
        if (GetForegroundWindow() != hWnd)
            return 0;
        if (KEYBOARDHANDLER->OnKeyChar(wParam))
            return 0;
        if (g_IsDxProjectZoomIn > 0)
            break;
        if (hFocusWnd)
            SendMessage(hFocusWnd, messg, wParam, lParam);

    case WM_KILLFOCUS:
        SetFocus(hWnd);
        return TRUE;

    case WM_COMMAND:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_MOVING:
        CancelAttack();
        break;

    case WM_ACTIVATE:
        switch (wParam) {
        case WA_ACTIVE:
            CancelAttack();
            break;
        }
        break;

    case WM_NCACTIVATE:
        if (GameMode == 2 && lpCurPlayer->dwObjectSerial)
        {
            CheckCracker();
            CheckCracker(NULL);
            CheckCharForm();
        }
        break;

    case WM_TIMER:
        if ((dwTimerCount & 3) == 0)
        {
            dwGameWorldTime++;

            dwGameHour = dwGameWorldTime + dwGameTimeOffset;
            dwGameHour = dwGameHour / 60;
            dwGameHour = dwGameHour - (((int)(dwGameHour / 24)) * 24);
            dwGameMin = dwGameWorldTime - (((int)(dwGameWorldTime / 60)) * 60);

            if (EventoArena::GetInstance()->timeArena == TRUE) {
                extern int arenaTimer;
                arenaTimer--;
            }

            if (TimeStreak > 0 && killStreak > 0)
            {
                TimeStreak--;
            }
            else if (TimeStreak == 0 && killStreak > 0) {
                killStreak = 0;

                smTRANS_COMMAND smTransCommand;
                smTransCommand.size = sizeof(smTRANS_COMMAND);
                smTransCommand.code = 0x50501003;
                smTransCommand.WParam = 0;
                smTransCommand.LParam = 0;
                smTransCommand.SParam = 0;
                smTransCommand.EParam = 0;

                if (smWsockDataServer)
                    smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
            }
        }

        if (smWsockServer && smWsockDataServer && smWsockUserServer)
        {
            smCheckWaitMessage();
        }

        dwTimerCount++;
        break;

    case WM_NPROTECT_EXIT_TWO:
        DisconnectServerCode = 4;
        DisconnectFlag = GetCurrentTime();
        break;

    case WM_NPROTECT_SPEEDHACK:
    case WM_NPROTECT_SH_ERROR:
    case WM_NPROTECT_SOFTICE:
        DisconnectServerCode = 4;
        DisconnectFlag = GetCurrentTime();
        quit = 1;
        break;

    default:
        return DefWindowProc(hWnd, messg, wParam, lParam);
        break;
    }

    return 0L;
}

char szCurrentMapName[64] = { 0 };
DWORD dwMapTitleShowTime = 0;
BOOL bShowMapTitle = FALSE;
float fMapTitleAlpha = 0.0f;

int MoveAngle(int step, int angY)
{
    int x, z;

    x = ((pX << 16) + GetSin[angY & ANGLE_MASK] * step) >> 16;
    z = ((pZ << 16) + GetCos[angY & ANGLE_MASK] * step) >> 16;

    pX = x;
    pZ = z;

    return TRUE;
}

#define CAMERA_MOVE_STEP		(8*fONE)

int TraceCameraMain()
{
    if (TraceCameraPosi.x < TraceTargetPosi.x)
    {
        TraceCameraPosi.x += CAMERA_MOVE_STEP;
        if (TraceCameraPosi.x > TraceTargetPosi.x)
            TraceCameraPosi.x = TraceTargetPosi.x;
    }
    if (TraceCameraPosi.x > TraceTargetPosi.x)
    {
        TraceCameraPosi.x -= CAMERA_MOVE_STEP;
        if (TraceCameraPosi.x < TraceTargetPosi.x)
            TraceCameraPosi.x = TraceTargetPosi.x;
    }

    if (TraceCameraPosi.y < TraceTargetPosi.y)
    {
        TraceCameraPosi.y += CAMERA_MOVE_STEP;
        if (TraceCameraPosi.y > TraceTargetPosi.y)
            TraceCameraPosi.y = TraceTargetPosi.y;
    }
    if (TraceCameraPosi.y > TraceTargetPosi.y)
    {
        TraceCameraPosi.y -= CAMERA_MOVE_STEP / 2;
        if (TraceCameraPosi.y < TraceTargetPosi.y)
            TraceCameraPosi.y = TraceTargetPosi.y;
    }

    if (TraceCameraPosi.z < TraceTargetPosi.z)
    {
        TraceCameraPosi.z += CAMERA_MOVE_STEP;
        if (TraceCameraPosi.z > TraceTargetPosi.z)
            TraceCameraPosi.z = TraceTargetPosi.z;
    }
    if (TraceCameraPosi.z > TraceTargetPosi.z)
    {
        TraceCameraPosi.z -= CAMERA_MOVE_STEP;
        if (TraceCameraPosi.z < TraceTargetPosi.z)
            TraceCameraPosi.z = TraceTargetPosi.z;
    }

    return TRUE;
}

int RendSightPos = 0;
int RendSightOffset = 0;

int SetRendSight()
{
    if (smRender.m_GameFieldView)
    {
        ViewPointLen = 38 * SizeMAPCELL + RendSightPos;
        ccDistZMin = ViewPointLen - (20 * SizeMAPCELL + RendSightPos / 4);

        return TRUE;
    }

    return FALSE;
}

int RendSightSub(int flag)
{
    if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldSight)
    {
        RendSightOffset = StageField[lpCurPlayer->OnStageField]->FieldSight * SizeMAPCELL;
    }
    else
    {
        RendSightOffset = smRender.m_GameFieldViewStep * SizeMAPCELL;
        if (flag) RendSightPos = RendSightOffset;
    }

    if (RendSightPos < RendSightOffset) RendSightPos += 4;
    else
        if (RendSightPos > RendSightOffset) RendSightPos -= 4;

    return TRUE;
}

#define FPS_TIME		(1000/70)

DWORD FrameSkipTimer = 0;
int fps = 70;
int FpsTime;

#define AC_MOVE_STEP	4
#define AC_MOVE_MIN		256

int dsCameraRotation = 0;

int iTickCount = 0;
int iSeconds = 0;
int iSecondsInCity = 0;

static void SetMapTitle(const char* mapName)  // <-- NOTA: é "static"
{
    if (mapName && mapName[0])
    {
        STRINGCOPY(szCurrentMapName, mapName);
        dwMapTitleShowTime = dwPlayTime + 10000;
        bShowMapTitle = TRUE;
        fMapTitleAlpha = 1.5f;
    }
}

void PlayMain()
{
    // ===== AUTO-PICKUP DE OURO =====
    AutoPickupGold();  // <--- ADICIONE ESTA LINHA AQUI, NO INÍCIO

    UpdateWarmPalette();
    // Adicionar animação do título do servidor
    if (g_bIsServer3) {
        AnimateServerTitle();
    }

    // ===== ATUALIZA O TEXTO DO SERVIDOR A CADA 1 SEGUNDO =====
    DWORD dwCurrentTime = GetTickCount();
    if (dwCurrentTime - g_dwLastServerReadTime > 1000)  // 1000ms = 1 segundo
    {
        g_dwLastServerReadTime = dwCurrentTime;

        // Lê o mundo atual do game.ini
        int currentWorld = GetPrivateProfileIntA("ConnectServer", "Mundo", 1, ".\\game.ini");

        // Atualiza o texto do seletor
        sprintf(szServerName, "Servidor: %s",
            currentWorld == 1 ? "Babel" :
            currentWorld == 2 ? "Morion" : "Requiem");
    }

    // ===== VERIFICA MUDANÇA DE MUNDO =====
    // CheckWorldChange();  // <--- COMENTE ESTA LINHA PARA DESATIVAR A RECONEXÃO AUTOMÁTICA

    // ===== ATUALIZA A MINI SKILL BAR =====
    if (g_pMiniSkillBar) {
        g_pMiniSkillBar->Update();
    }
    // ======================================

    if (bShowMapTitle)
    {
        if (dwPlayTime > dwMapTitleShowTime)
        {
            fMapTitleAlpha -= 0.02f;
            if (fMapTitleAlpha <= 0.0f)
            {
                fMapTitleAlpha = 0.0f;
                bShowMapTitle = FALSE;
            }
        }
        else if (fMapTitleAlpha > 1.0f)
        {
            fMapTitleAlpha -= 0.03f;
            if (fMapTitleAlpha < 1.0f)
                fMapTitleAlpha = 1.0f;
        }
    }

    if (lpCurPlayer && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField])
    {
        static int lastMap = -1;
        int currentMap = StageField[lpCurPlayer->OnStageField]->FieldCode;

        if (lastMap != currentMap)
        {
            lastMap = currentMap;

            printf("DEBUG: Mudança de mapa detectada! Código: %d\n", currentMap);

            const char* mapName = "Unknown Area";

            switch (currentMap)
            {
            case 0: mapName = "Arredores de Ricarten"; break;
            case 1: mapName = "Arredores de Ricarten"; break;
            case 2: mapName = "Arredores de Ricarten"; break;
            case 3: mapName = "Ricarten"; break;
            case 4: mapName = "Ruinas"; break;
            case 5: mapName = "Ruinas"; break;
            case 6: mapName = "Vila Ruinem"; break;
            case 7: mapName = "Ruinas"; break;
            case 8: mapName = "Desertos"; break;
            case 9: mapName = "Cidade de Navisko"; break;
            case 10: mapName = "Desertos"; break;
            case 11: mapName = "Arredores de Navisko"; break;
            case 12: mapName = "Desertos"; break;
            case 13: mapName = "Calabouços"; break;
            case 14: mapName = "Calabouços"; break;
            case 15: mapName = "Calabouços"; break;
            case 16: mapName = "Desconhecido"; break;
            case 17: mapName = "Arredores de Pillai"; break;
            case 18: mapName = "Arredores de Pillai"; break;
            case 19: mapName = "Vale Tranquilo"; break;
            case 20: mapName = "Arredores de Pillai"; break;
            case 21: mapName = "Cidade dos Morions"; break;
            case 22: mapName = "Templos Malditos"; break;
            case 23: mapName = "Templos Malditos"; break;
            case 24: mapName = "Cavernas dos Cogumelos"; break;
            case 25: mapName = "Caverna das Abelhas"; break;
            case 26: mapName = "Santuario Sombrio"; break;
            case 27: mapName = "Estradas de Ferro"; break;
            case 28: mapName = "Estradas de Ferro"; break;
            case 29: mapName = "Eura"; break;
            case 31: mapName = "Arredores de Eura"; break;
            case 32: mapName = "Desconhecido"; break;
            case 33: mapName = "Arredores do Castelo"; break;
            case 34: mapName = "Lago da Ganancia"; break;
            case 35: mapName = "Terras Congeladas"; break;
            case 36: mapName = "Covil"; break;
            case 37: mapName = "Desconhecido"; break;
            case 38: mapName = "Norte das Ilhas Perdidas"; break;

            default:
                if (currentMap < 100)
                    mapName = "Campo Desconhecido";
                else if (currentMap < 200)
                    mapName = "Calabouço Desconhecido";
                else if (currentMap < 300)
                    mapName = "Cidade Desconhecida";
                else
                    mapName = "Área Desconhecida";
                break;
            }

            SetMapTitle(mapName);
        }
    }

    int mv;

    if (_PACKET_PASS_XOR != 0x8B)
        QuitGame();

    if (iTickCount == 0)
        iTickCount = GetTickCount();

    GAMECOREHANDLE->pcItemInfoBox->Update(dwPlayTime);

    if (GetTickCount() - iTickCount > 100)
    {
        CHUDCONTROLLER->Update(dwPlayTime);
    }

    if (GetTickCount() - iTickCount > 1000)
    {
        CMINIMAPHANDLE->Update();
        MESSAGEBOX->Update();
        PARTYHANDLER->Update(dwPlayTime);

        GAMECOREHANDLE->pcMessageBalloon->Update(dwPlayTime);

        iTickCount = 0;
        iSeconds += 1;

        if ((StageField[lpCurPlayer->OnStageField]->FieldCode == 3) || (StageField[lpCurPlayer->OnStageField]->FieldCode == 33) || (StageField[lpCurPlayer->OnStageField]->FieldCode == 21))
            iSecondsInCity += 1;
        else
        {
            chaPremiumitem.UpdatePremiumTime();
        }

        if (chaPremiumitem.GetBigHeadTime() > 0 && StageField[lpCurPlayer->OnStageField]->FieldCode != 3 && StageField[lpCurPlayer->OnStageField]->FieldCode != 21)
            chaPremiumitem.SetItemPremiumTime(nsPremiumItem::BIGHEAD1, chaPremiumitem.GetBigHeadTime() - 1);
    }

    if (ActionGameMode)
    {
        ActionGameMain();
    }
    else if (cSinHelp.sinGetHelpShowFlag() != TRUE)
    {
        if (CameraInvRot)
        {
            if (VRKeyBuff[VK_RIGHT])
            {
                any_pt += 16; AutoCameraFlag = FALSE;
            }
            if (VRKeyBuff[VK_LEFT])
            {
                any_pt -= 16; AutoCameraFlag = FALSE;
            }
        }
        else
        {
            if (VRKeyBuff[VK_RIGHT])
            {
                any_pt -= 16; AutoCameraFlag = FALSE;
            }
            if (VRKeyBuff[VK_LEFT])
            {
                any_pt += 16; AutoCameraFlag = FALSE;
            }
        }

        if (VRKeyBuff[VK_CONTROL])
        {
            if (VRKeyBuff[VK_UP])
            {
                anx -= 16; AutoCameraFlag = FALSE;
            }
            if (VRKeyBuff[VK_DOWN])
            {
                anx += 16; AutoCameraFlag = FALSE;
            }
        }
        else
        {
            if (VRKeyBuff[VK_UP])
            {
                dist -= 8;
                if (dist < 34)
                {
                    if (anx <= 40)
                    {
                        if (dist < 40)
                            dist = 40;
                    }
                    else
                        dist = 34;

                    CaTarDist = 0;
                }
            }

            if (VRKeyBuff[VK_DOWN])
            {
                dist += 8;
                if (Settings::GetInstance()->cCamRange == 0)
                    if (dist > 440) { dist = 440; CaTarDist = 0; }
                if (Settings::GetInstance()->cCamRange == 1)
                    if (dist > 500) { dist = 500; CaTarDist = 0; }
                if (Settings::GetInstance()->cCamRange == 2)
                    if (dist > 550) { dist = 550; CaTarDist = 0; }
                if (Settings::GetInstance()->cCamRange == 3)
                    if (dist > 600) { dist = 600; CaTarDist = 0; }
            }
        }

        if (VRKeyBuff[VK_NEXT])
        {
            anx -= 16; AutoCameraFlag = FALSE;
        }
        if (VRKeyBuff[VK_PRIOR])
        {
            anx += 16; AutoCameraFlag = FALSE;
        }
    }

    if (cInterFace.sInterFlags.CameraAutoFlag != 2)
    {
        if (pCursorPos.x >= 8 && pCursorPos.x <= WinSizeX - 8)
        {
            dsCameraRotation = 0;
        }

        if (pCursorPos.x < 8)
        {
            if (!dsCameraRotation) dsCameraRotation = -512;
            mv = dsCameraRotation / 16;
            if (mv < -16) mv = -16;
            any_pt += mv;
            dsCameraRotation++;
            if (dsCameraRotation >= 0)
            {
                dsCameraRotation = 0;
                pCursorPos.x = 8;
            }
            AutoCameraFlag = FALSE;
        }

        if (pCursorPos.x > WinSizeX - 8)
        {
            if (!dsCameraRotation) dsCameraRotation = 512;
            mv = dsCameraRotation / 16;
            if (mv > 16) mv = 16;
            any_pt += mv;
            dsCameraRotation--;
            if (dsCameraRotation <= 0)
            {
                dsCameraRotation = 0;
                pCursorPos.x = WinSizeX - 8;
            }
            AutoCameraFlag = FALSE;
        }
    }

    if (CaTarDist)
    {
        if (dist < CaTarDist)
        {
            dist += 12;
            if (dist >= CaTarDist)
            {
                dist = CaTarDist; CaTarDist = 0;
            }
        }
        else
            if (dist > CaTarDist)
            {
                dist -= 12;
                if (dist <= CaTarDist)
                {
                    dist = CaTarDist; CaTarDist = 0;
                }
            }
    }

    if (CaMovAngle)
    {
        mv = CaMovAngle >> 4;
        if (CaMovAngle > 0)
        {
            if (mv > 32) mv = 32;
            any_pt += mv; CaMovAngle -= mv;
            if (CaMovAngle < 0) CaMovAngle = 0;
        }
        else
        {
            if (mv < -32) mv = -32;
            any_pt += mv; CaMovAngle -= mv;
            if (CaMovAngle > 0) CaMovAngle = 0;
        }
        if (mv == 0) CaMovAngle = 0;

        if (CaMovAngle == 0)
            AutoCameraFlag = TRUE;
        else
            AutoCameraFlag = FALSE;
    }

    if (whAnx != ANX_NONE)
    {
        if (anx < whAnx)
        {
            anx += 8;
            if (anx >= whAnx)
            {
                whAnx = ANX_NONE;
                AutoCameraFlag = TRUE;
            }
        }
        else
        {
            anx -= 8;
            if (anx <= whAnx)
            {
                whAnx = ANX_NONE;
                AutoCameraFlag = TRUE;
            }
        }
    }

    {
        if (ViewAnx < anx)
        {
            ViewAnx += 8;
            if (ViewAnx > anx) ViewAnx = anx;
        }
        if (ViewAnx > anx)
        {
            ViewAnx -= 8;
            if (ViewAnx < anx) ViewAnx = anx;
        }

        if (CaTarDist)
            mv = 100;
        else
            mv = 8;

        if (ViewDist < dist)
        {
            ViewDist += mv;
            if (ViewDist > dist) ViewDist = dist;
        }
        if (ViewDist > dist)
        {
            ViewDist -= mv;
            if (ViewDist < dist) ViewDist = dist;
        }
    }

    if (DebugPlayer)
    {
        if (dpX == 0 && dpZ == 0)
        {
            dpX = lpCurPlayer->pX;
            dpY = lpCurPlayer->pY;
            dpZ = lpCurPlayer->pZ;
        }

        if (VRKeyBuff[VK_SPACE])
        {
            GetMoveLocation(0, 0, fONE * 2, anx, any_pt, 0);
            dpX += GeoResult_X;
            dpY += GeoResult_Y;
            dpZ += GeoResult_Z;
        }

        if (VRKeyBuff['Z']) anz -= 8;
        if (VRKeyBuff['X']) anz += 8;

        lpCurPlayer->pX = dpX;
        lpCurPlayer->pZ = dpZ;

        anx &= ANGCLIP;

        if (anx >= ANGLE_90 && anx < ANGLE_270)
        {
            if (anx < ANGLE_180)
                anx = ANGLE_90 - 32;
            else
                anx = ANGLE_270 + 32;
        }
        ViewAnx = anx;
        whAnx = ANX_NONE;
    }
    else
    {
        if (anx >= (ANGLE_90 - 48))
        {
            anx = (ANGLE_90 - 48);
            whAnx = ANX_NONE;
        }
        if (anx < 48)
        {
            anx = 48;
            whAnx = ANX_NONE;
        }
    }

    if (anx > 48 && dist < 34)
    {
        dist = 34; CaTarDist = 0;
    }
    if (Settings::GetInstance()->cCamRange == 0)
        if (dist > 440) { dist = 440; CaTarDist = 0; }
    if (Settings::GetInstance()->cCamRange == 1)
        if (dist > 500) { dist = 500; CaTarDist = 0; }
    if (Settings::GetInstance()->cCamRange == 2)
        if (dist > 550) { dist = 550; CaTarDist = 0; }
    if (Settings::GetInstance()->cCamRange == 3)
        if (dist > 600) { dist = 600; CaTarDist = 0; }

    int ay;
    int astep;

    if (PlayCameraMode != cInterFace.sInterFlags.CameraAutoFlag)
    {
        if (cInterFace.sInterFlags.CameraAutoFlag == 2) any_pt = ANGLE_45;
        PlayCameraMode = cInterFace.sInterFlags.CameraAutoFlag;

        if (!dwM_BlurTime)
        {
            dwM_BlurTime = dwPlayTime + 600;
        }
    }

    if (PlayCameraMode == 1 && AutoCameraFlag && any_pt != lpCurPlayer->Angle.y && lpCurPlayer->MoveFlag)
    {
        ay = (any_pt - lpCurPlayer->Angle.y) & ANGCLIP;

        if (ay >= ANGLE_180)
        {
            ay = ay - ANGLE_360;
        }

        if (abs(ay) < (ANGLE_90 + 180))
        {
            if (ay < 0)
            {
                astep = abs(ay) >> 6;
                if (astep < AC_MOVE_STEP) astep = AC_MOVE_STEP;

                if (ay < -AC_MOVE_MIN)
                {
                    ay += astep;
                    if (ay > 0)
                    {
                        any_pt = lpCurPlayer->Angle.y;
                    }
                    else
                        any_pt = (any_pt + astep) & ANGCLIP;
                }
            }
            else
            {
                astep = abs(ay) >> 6;
                if (astep < AC_MOVE_STEP) astep = AC_MOVE_STEP;

                if (ay > AC_MOVE_MIN)
                {
                    ay -= astep;
                    if (ay < 0)
                    {
                        any_pt = lpCurPlayer->Angle.y;
                    }
                    else
                        any_pt = (any_pt - astep) & ANGCLIP;
                }
            }
        }
    }

    NetWorkPlay();
    PlayPat3D();
    MainEffect();

    if (g_IsDxProjectZoomIn)
        MainFullZoomMap();

    dwMemError = dwMemError ^ dwPlayTime;
    dwPlayTime = GetCurrentTime();
    dwMemError = dwMemError ^ dwPlayTime;

    TraceCameraMain();
    RendSightSub(0);
}

POINT3D TargetPosi = { 0, 0, 0 };
POINT3D GeoResult = { 0, 0, 0 };

int timeg = 0;
int RenderCnt = 0;
int DispRender;
int DispMainLoop;

DWORD dwLastPlayTime = 0;
DWORD dwLastOverSpeedCount = 0;
int PlayTimerMax = 0;
int MainLoopCount = 0;
DWORD dwLastRenderTime = 0;

void PlayD3D()
{
    DWORD dwTime;

    dwTime = GetCurrentTime();

    if (dwLastPlayTime)
    {
        if (dwTime < dwLastPlayTime && dwLastOverSpeedCount > 1000)
        {
            SendSetHackUser2(1200, dwLastPlayTime - dwTime);
            dwLastOverSpeedCount = 0;
        }
    }

    dwLastPlayTime = dwTime;

    if (FrameSkipTimer == 0)
    {
        FrameSkipTimer = dwTime;
        FpsTime = 1000 / fps;
    }

    if (((int)(dwTime - FrameSkipTimer)) > 5000)
    {
        FrameSkipTimer = dwTime;
    }

    if (FrameSkipTimer > dwTime)
    {
        dwTime = GetCurrentTime();
        dwLastPlayTime = dwTime;
    }

    pRealCursorPos.x = pCursorPos.x;
    pRealCursorPos.y = pCursorPos.y;

    while (1)
    {
        if (FrameSkipTimer >= dwTime) break;

        FrameSkipTimer += FPS_TIME;

        switch (GameMode)
        {
        case 1:
            if (MainOpening() == TRUE)
            {
                SetGameMode(2);
            }
            break;
        case 2:
            PlayMain();
#ifdef _SINBARAM
            if (g_IsDxProjectZoomIn <= 0)
            {
                dsMenuCursorPos(&pCursorPos, 1);
                sinMain();
                dsMenuCursorPos(&pCursorPos, 0);

                MainInterfaceParty(pHoPartyMsgBox.x, pHoPartyMsgBox.y);
            }
            else
                MainSub();
#endif
            if (BellatraEffectInitFlag)
                MainBellatraFontEffect();

            break;
        }

        MainLoopCount++;
        dwLastOverSpeedCount++;
    }

    if (ParkPlayMode)
    {
        if (ParkPlayMode < 0)
        {
            if ((smFlipCount & 1) == 0)
                return;
        }
        else
        {
            if (ParkPlayMode <= 1000)
            {
                if ((dwLastRenderTime + ParkPlayMode) > dwTime)
                    return;
            }
        }
    }
    else
    {
        if (GetForegroundWindow() != hwnd)
        {
            Sleep(200);
        }
    }

    dwLastRenderTime = dwTime;

    auto fElapsedTime = timer->Update();

    TitleBox::GetInstance()->Update(static_cast<float>(fElapsedTime));
    Core::Timer::Update(static_cast<float>(fElapsedTime));
    Graphics::Graphics::GetInstance()->GetRenderer()->Update(static_cast<float>(fElapsedTime));

    extern int bHoldingSpace;
    extern float progressHoldingSpace;
    extern void ToggleMountVisible();

    if (bHoldingSpace)
    {
        progressHoldingSpace += fElapsedTime / 10.f;

        if (progressHoldingSpace >= 100.f)
        {
            progressHoldingSpace = 0.f;
            bHoldingSpace = false;
            ToggleMountVisible();
        }
    }

    int i;

    if (smRender.TerrainShader == nullptr)
    {
        std::vector<Graphics::ShaderDefine> defines{};

        if (Graphics::Graphics::GetInstance()->GetPixelShaderVersionMajor() == 3)
            defines.push_back(Graphics::ShaderDefine{ "_PS_3_0", "1" });

        TitleBox::GetInstance()->Init();
        DX::cSelectGlow1.Init();
        DX::cSelectGlow2.Init();
        DX::postProcess.Init();
        cMountManager.Load();

        smRender.TerrainShader = Graphics::Graphics::GetInstance()->GetShaderFactory()->Create("game\\scripts\\shaders\\Terrain.fx", defines);
    }
    else
    {
        smRender.TerrainShader->SetMatrix("Projection", camera->Projection().Get());
        smRender.TerrainShader->SetTechnique("Terrain");
        smRender.TerrainShader->SetFloat("FogEnd", 1500.f);
        smRender.TerrainShader->SetInt("NumActiveLights", ConfigUseDynamicLights ? smRender.Lights.size() : 0);

        Graphics::Graphics::GetInstance()->GetRenderer()->SetFogEnd(1500.f);

        if (ConfigUseDynamicLights)
        {
            if (smRender.Lights.size())
                smRender.TerrainShader->SetData("Lights", (const char*)&smRender.Lights[0], smRender.Lights.size() * sizeof(Graphics::RenderLight));
        }

        smRender.Lights.clear();
    }

    if (GameMode == 1)
    {
        DrawOpening();
        return;
    }

    if (PlayCameraMode == 2)
    {
        dist = 400;
        anx = ANGLE_45 - 128;
        ViewAnx = anx;
        ViewDist = dist;
    }

    any_pt &= ANGCLIP;
    anx &= ANGCLIP;

    if (WaveCameraFlag && WaveCameraMode)
    {
        WaveCameraTimeCount++;

        if ((WaveCameraTimeCount > WaveCameraDelay))
        {
            WaveCameraTimeCount = 0;
            if (WaveCameraDelay > 1 && WaveCameraFactor < 40)
                WaveCameraFactor = -int((float)WaveCameraFactor / 10.f * 9.f);
            else
                WaveCameraFactor = -int((float)WaveCameraFactor / 10.f * 8.f);
            ViewDist += WaveCameraFactor;
        }

        if (abs(WaveCameraFactor) < 1)
        {
            WaveCameraFlag = FALSE;
            WaveCameraTimeCount = 0;
        }
    }
    else
    {
        WaveCameraFlag = FALSE;
    }

    GetMoveLocation(0, 0, -(ViewDist << FLOATNS), ViewAnx & ANGCLIP, any_pt, 0);
    if (GeoResult_X == GeoResult.x && GeoResult_Y == GeoResult.y && GeoResult_Z == GeoResult.z)
    {
        pX += lpCurPlayer->pX - TargetPosi.x;
        pY += lpCurPlayer->pY - TargetPosi.y;
        pZ += lpCurPlayer->pZ - TargetPosi.z;
    }
    else
    {
        pX = lpCurPlayer->pX;
        pY = lpCurPlayer->pY;
        pZ = lpCurPlayer->pZ;

        pX += GeoResult_X;
        pZ += GeoResult_Z;
        pY += GeoResult_Y;

        GeoResult.x = GeoResult_X;
        GeoResult.y = GeoResult_Y;
        GeoResult.z = GeoResult_Z;
    }

    TargetPosi.x = lpCurPlayer->pX;
    TargetPosi.y = lpCurPlayer->pY;
    TargetPosi.z = lpCurPlayer->pZ;

    i = GetCurrentTime();

    if (timeg < i)
    {
        timeg = i + 1000;
        DispRender = RenderCnt;
        RenderCnt = 0;
        DispMainLoop = MainLoopCount;
        MainLoopCount = 0;
    }
    RenderCnt++;

    if (DebugPlayer)
    {
        lpCurPlayer->Angle.y = any_pt;

        pX = dpX;
        pY = dpY;
        pZ = dpZ;

        any_pt = lpCurPlayer->Angle.y;
    }
    else
        anz = 0;

    if (smConfig.DebugMode && VRKeyBuff[VK_SHIFT])
    {
        if (VRKeyBuff[VK_HOME])
            DarkLevel = 220;
        if (VRKeyBuff[VK_END])
            DarkLevel = 0;
    }
    LockSpeedProtect(lpCurPlayer);

    EnterCriticalSection(&cDrawSection);
    smEnterTextureCriticalSection();

    DWORD dwSkilChkSum = 0;
    DWORD dwChkSum;
    DWORD dwLevelQuestSum;
    int cnt, k;

    for (cnt = 0; cnt < SIN_MAX_USE_SKILL; cnt++)
    {
        k = (cnt + 5) << 2;
        dwSkilChkSum += sinSkill.UseSkill[cnt].UseSkillCount * k;
        dwSkilChkSum += sinSkill.UseSkill[cnt].Point * k;
        dwSkilChkSum += sinSkill.UseSkill[cnt].Mastery * k;
        dwSkilChkSum += sinSkill.UseSkill[cnt].GageLength * k;
        dwSkilChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[0] * k;
        dwSkilChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[1] * k;
    }

    dwLevelQuestSum = sinQuest_levelLog & 0x576321cc;

    smPlayD3D(pX, pY, pZ, (ViewAnx & ANGCLIP), (any_pt & ANGCLIP), (anz & ANGCLIP));

    dwChkSum = 0;
    for (cnt = 0; cnt < SIN_MAX_USE_SKILL; cnt++)
    {
        k = (cnt + 5) << 2;
        dwChkSum += sinSkill.UseSkill[cnt].UseSkillCount * k;
        dwChkSum += sinSkill.UseSkill[cnt].Point * k;
        dwChkSum += sinSkill.UseSkill[cnt].Mastery * k;
        dwChkSum += sinSkill.UseSkill[cnt].GageLength * k;
        dwChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[0] * k;
        dwChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[1] * k;
    }

    if (dwSkilChkSum != dwChkSum)
    {
        SendSetHackUser3(8540, dwSkilChkSum, dwChkSum);
    }

    if (dwLevelQuestSum != (sinQuest_levelLog & 0x576321cc))
    {
        SendSetHackUser3(8820, (dwLevelQuestSum & 0x576321cc), sinQuest_levelLog);
    }

    int mapY;
    int x, z, y;

    GetMoveLocation(0, 0, -(dist << FLOATNS), anx, any_pt, 0);

    x = lpCurPlayer->pX + GeoResult_X;
    y = lpCurPlayer->pY + GeoResult_Y;
    z = lpCurPlayer->pZ + GeoResult_Z;

    PlayFloor = 0;
    y = 0;

    if (!DebugPlayer)
    {
        if (smGameStage[0])
        {
            mapY = (smGameStage[0]->GetHeight2(x, z));
            if (mapY > CLIP_OUT) y++;
        }
        if (smGameStage[1])
        {
            mapY = (smGameStage[1]->GetHeight2(x, z));
            if (mapY > CLIP_OUT) y++;
        }
        if (!y) PlayFloor = 64;
    }
    smLeaveTextureCriticalSection();
    LeaveCriticalSection(&cDrawSection);
    UnlockSpeedProtect(lpCurPlayer);

    GRAPHICENGINE->lpD3DDev->EndScene();
}

extern int DispPolyCnt;
extern int GetMouseMapPoint(int x, int y);

extern int xframe;

int GetPlayMouseAngle()
{
    int ax, az, ay;

    ax = xPs - (WinSizeX >> 1);
    az = yPs - (WinSizeY >> 1);
    ay = GetRadian2D(0, 0, ax, -az);

    return ay + any_pt;
}

int GetActionGame_PlayMouseAngle()
{
    int ax, az, ay;

    ax = xPs - lpCurPlayer->RendPoint.x;
    az = yPs - lpCurPlayer->RendPoint.x;
    ay = GetRadian2D(0, 0, ax, -az);

    return ay;
}

extern int TestTraceMatrix();

int _stdcall InitD3D(HWND hWnd)
{
    hwnd = hWnd;

    MidX = WinSizeX / 2;
    MidY = WinSizeY / 2;
    MidY -= 59;

    int iZCamera = (WinSizeX / 4) * 3;
    if (iZCamera == WinSizeY)
        viewdistZ = WinSizeX;
    else
        viewdistZ = ((WinSizeY / 3) * 4);

    if (!GRAPHICENGINE->InitD3D(hwnd, WinSizeX, WinSizeY))
    {
        return FALSE;
    }

    if (!SetDisplayMode(hWnd, WinSizeX, WinSizeY, WinColBit))
    {
        return FALSE;
    }

    TestTraceMatrix();
    InitRender();
    InitTexture();

    smSetTextureLevel(smConfig.TextureQuality);

    Check_CodeSafe((DWORD)GameInit);

    InitSoundEffect(hwnd);
    InitPatterns();

    lpCurPlayer = InitRotPlayer();

    return Code_VRamBuffOpen();
}

void _stdcall CloseD3d()
{
    CloseRotPlayer();
    CloseSoundEffect();
    CloseTexture();
}

int GameInit()
{
    g_IsReadTextures = 1;

    if (smConfig.DebugMode)
        SendAdminMode(TRUE);
    //servidores icones
    npSetUserID(UserAccount);
    // iWorldIcon[0] = CreateTextureMaterial("assets\\8.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    //  iWorldIcon[1] = CreateTextureMaterial("assets\\8.pkg", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    //  iWorldIcon[2] = CreateTextureMaterial("assets\\9.pkg", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    ReadTextures();


    // Carrega o mundo atual
    int currentWorld = GetPrivateProfileIntA("ConnectServer", "Mundo", 1, ".\\game.ini");

    // Se for mundo 3, força para mundo 1 (Babel)
    if (currentWorld > 2) currentWorld = 1;

    sprintf(szServerName, "Servidor: %s",
    //    currentWorld == 1 ? "Babel" : "Morion
             currentWorld == 1 ? "Babel" :
        currentWorld == 2 ? "Morion" : "Requiem");

    //COM 3 SERVIDORES
    // Carrega o mundo atual
    //int currentWorld = GetPrivateProfileIntA("ConnectServer", "Mundo", 1, ".\\game.ini");
    //sprintf(szServerName, "Servidor: %s",
    //    currentWorld == 1 ? "Babel" :
    //    currentWorld == 2 ? "Morion" : "Valento");


// RECARREGA A CONFIGURAÇÃO DO MUNDO ANTES DE QUALQUER COISA
    ReloadWorldConfig();

    g_IsReadTextures = 1;
    // ... resto do código


        

    dwPlayTime = GetCurrentTime();
    dwMemError = dwMemError ^ dwPlayTime;
    Check_nProtect();

    InitMaterial();
    smRender.SetMaterialGroup(smMaterialGroup);

    ReformCharForm();

    InitEffect();
    InitMotionBlur();
    InitBackGround();

    Check_CodeSafe((DWORD)CloseD3d);

    InitStage();
    InitPat3D();

#ifdef _XTRAP_GUARD_4_CLIENT
    XTrap_C_SetUserInfo(UserAccount, szConnServerName, lpCurPlayer->smCharInfo.szName, "class name", 1);
#endif

    CreateItem2PassTexture();

    CheckCharForm();

#ifdef _SINBARAM
    lpDDSMenu = 0;
    sinInit();
#else
    lpDDSMenu = LoadDibSurfaceOffscreen(smConfig.szFile_Menu);
#endif

    g_fWinSizeRatio_X = float(WinSizeX) / 800.f;
    g_fWinSizeRatio_Y = float(WinSizeY) / 600.f;

    CreateBeforeFullZoomMap();
    CreateFontImage();

    TraceCameraPosi.x = lpCurPlayer->pX;
    TraceCameraPosi.y = lpCurPlayer->pY;
    TraceCameraPosi.z = lpCurPlayer->pZ;

    TraceTargetPosi.x = lpCurPlayer->pX;
    TraceTargetPosi.y = lpCurPlayer->pY;
    TraceTargetPosi.z = lpCurPlayer->pZ;

    InitMessageBox();

    smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
    MidX = WinSizeX / 2;
    MidY = WinSizeY / 2;

    int iZCamera = (WinSizeX / 4) * 3;
    if (iZCamera == WinSizeY)
        viewdistZ = WinSizeX;
    else
        viewdistZ = ((WinSizeY / 3) * 4);

    g_IsReadTextures = 1;

    ReadTextures();

    CheckOftenMeshTextureSwap();

    if (smConfig.BGM_Mode)
    {
        if (StageField[0])
            PlayBGM_Direct(StageField[0]->BackMusicCode);
        else
        {
            OpenBGM("wav\\bgm\\Field - Desert - Pilgrim.bgm");
            PlayBGM();
        }
    }
    CharPlaySound(lpCurPlayer);
    StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
    RestartPlayCount = 700;

    hFocusWnd = 0;
    szLastWhisperName[0] = 0;
    LastWhisperLen = 0;
    InterfaceParty.chat_WhisperPartyPlayer_close();
    chatlistSPEAKERflagChg(0);
    SendMessage(hTextWnd, EM_SETLIMITTEXT, 78, 0);

    MouseButton[0] = 0;
    MouseButton[1] = 0;
    MouseButton[2] = 0;

#ifdef _XTRAP_GUARD_4_CLIENT
    XTrap_CE1_Func11_Protect(&sinChar, sizeof(sinChar));
#endif

#ifdef _XIGNCODE_CLIENT
    Xigncode_Client_Start();
#endif

    smCHAR* lpTempChar;
    lpTempChar = SelectRotPlayer(lpCurPlayer);
    if (lpTempChar)
    {
        lpCurPlayer = lpTempChar;
        sinChar = &lpCurPlayer->smCharInfo;
    }
    lpTempChar = SelectRotPlayer(lpCurPlayer);
    if (lpTempChar)
    {
        lpCurPlayer = lpTempChar;
        sinChar = &lpCurPlayer->smCharInfo;
    }

#ifdef _XTRAP_GUARD_4_CLIENT
    XTrap_CE1_Func12_Protect(&sinChar, sizeof(sinChar));
    XTrap_CE1_Func13_Free(&sinChar, sizeof(sinChar));
#endif

    SetIME_Mode(0);

    ReformSkillInfo();

    HoMsgBoxMode = 1;
    SetMessageFrameSelect(HoMsgBoxMode);

    // ===== INICIALIZA A MINI SKILL BAR =====
    g_pMiniSkillBar = new CMiniSkillBar();
    g_pMiniSkillBar->SetPosition(496, 514);
    // =======================================

    CreateWinIntThread();
    int mundo = GetPrivateProfileIntA("ConnectServer", "Mundo", 1, ".\\game.ini");

    const char* nomeServidor = "";
    switch (mundo) {
    case 1: nomeServidor = "Conectado em  Babel"; break;
    case 2: nomeServidor = "Conectado em  Morion"; break;
    case 3: nomeServidor = "Conectado em  Requiem"; break;
    }

    char tituloJanela[256];
    sprintf(tituloJanela, "NorthGoblin [%s]", nomeServidor);
    SetWindowTextA(hwnd, tituloJanela);
    // ==================================================

    return TRUE;
}

int GameClose()
{
#ifdef _XIGNCODE_CLIENT
    ZCWAVE_Cleanup();
    ZCWAVE_SysExit();
#endif

    if (lpDDSMenu) lpDDSMenu->Release();

    // ===== LIBERA A MINI SKILL BAR =====
    if (g_pMiniSkillBar) {
        delete g_pMiniSkillBar;
        g_pMiniSkillBar = NULL;
    }
    // ===================================

    ClosePat3D();
    CloseBackGround();
    CloseStage();

#ifdef _SINBARAM
    sinClose();
#endif
    CloseMaterial();

    DestroyWinIntThread();

    if (BellatraEffectInitFlag)
    {
        DestroyBellatraFontEffect();
    }

    return TRUE;
}

int SetGameMode(int mode)
{
    Discord_Handle.Set_Game_Mode(mode);

    int OldMode;

    OldMode = GameMode;
    GameMode = mode;

    sinChar = &lpCurPlayer->smCharInfo;

    switch (OldMode)
    {
    case 1:
        CloseOpening();
        CloseMaterial();
        break;

    case 2:
        GameClose();
        break;
    }

    switch (GameMode)
    {
    case 1:
        SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);

        smRender.CreateRenderBuff(CameraSight);

        InitMaterial();
        smRender.SetMaterialGroup(smMaterialGroup);
        InitEffect();

        InitOpening();

        AnimationHandler::Get().LoadDynamicAnimation();

        smRender.SMMULT_PERSPECTIVE_HEIGHT = 0;
        MidX = WinSizeX / 2;
        MidY = WinSizeY / 2;

        if (CheckCrackProcess(TRUE)) quit = 1;

        dwM_BlurTime = 0;

        break;

    case 2:
        if (smRender.m_GameFieldView)
        {
            smRender.m_GameFieldViewStep = 22;
            smRender.SetGameFieldViewStep();
        }

        GAMECOREHANDLE->Init();
        GameInit();

        if (CheckCrackProcess()) quit = 1;
        break;
    }

    WaveCameraFlag = FALSE;

    return TRUE;
}

float xr = 0;
int jcnt = 0;
float brt = 1;
float bs = 0;

int ox = 0, oy = 0, oz = 0;

int GoText = 0;

char strBuff[240];
char strBuff2[256];

int RestoreFlag = 0;

char* szRestore = "Áö±Ý ±×¸² µ¥ÀÌÅÍ¸¦ ¾ÆÁÖ ¿­½ÉÈ÷ ·ÎµåÇÏ±¸ ÀÖ½À´Ï´Ù. ÂÉ±Ý¸¸ ±â´Ù¸®¼¼¿ä !";

int NumPoly;
int Disp_tx, Disp_ty;
int Disp_rx, Disp_ry;
smCHAR* lpCharMsgSort[OTHER_PLAYER_MAX];
int ChatMsgSortCnt;

extern int Debug_RecvCount1;
extern int Debug_RecvCount2;
extern int Debug_SendCount;

int RestoreInterfaceTexture()
{
    int cnt;

    smRender.Color_R = 0;
    smRender.Color_G = 0;
    smRender.Color_B = 0;
    smRender.Color_A = 0;

    cnt = 0;

    GRAPHICDEVICE->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_MODULATE);
    GRAPHICDEVICE->SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    GRAPHICDEVICE->SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

    GRAPHICDEVICE->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    GRAPHICDEVICE->SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
    GRAPHICDEVICE->SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

    GRAPHICDEVICE->SetTexture(cnt, 0);

    for (cnt = 1; cnt < 8; cnt++)
    {
        GRAPHICDEVICE->SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
        GRAPHICDEVICE->SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        GRAPHICDEVICE->SetTexture(cnt, 0);
    }

    return TRUE;
}

void VirtualDrawGameState(void)
{
    smRender.ClearLight();

    int BackDarkLevel;

    BackDarkLevel = DarkLevel;
    DarkLevel = 0;

    RestoreInterfaceTexture();

    if (DisconnectFlag)
    {
        if (DisconnectServerCode == 0)
        {
            Utils_Log(3, "DC: WinMain.cpp 3798");
            DrawMessage(MidX - 64, MidY, mgDiconnect, 36, BOX_ONE);
        }
        if (DisconnectServerCode == 1)
        {
            DrawMessage(MidX - 64, MidY, mgDiconnect1, 36, BOX_ONE);
        }
        if (DisconnectServerCode == 2)
        {
            DrawMessage(MidX - 64, MidY, mgDiconnect2, 36, BOX_ONE);
        }
        if (DisconnectServerCode == 3)
        {
            DrawMessage(MidX - 64, MidY, mgDiconnect3, 36, BOX_ONE);
        }
        if (DisconnectServerCode == 4)
        {
            DrawMessage(MidX - 64, MidY, mgDiconnect4, 36, BOX_ONE);
        }

#ifdef _WINMODE_DEBUG
        if (!smConfig.DebugMode && !quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime) quit = TRUE;
#else
        if (!quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime) quit = TRUE;
#endif
    }
    else
    {
        if (quit)
            TitleBox::GetInstance()->SetText("Saindo do Jogo", 3);
        else
        {
            if (dwCloseBoxTime && dwCloseBoxTime > dwPlayTime)
            {
                TitleBox::GetInstance()->SetText("Por favor, feche as janelas!", 3);
            }
            else
            {
                if (dwBattleQuitTime)
                {
                    if ((dwBattleQuitTime + 5000) > dwPlayTime)
                        TitleBox::GetInstance()->SetText("Você não pode sair durante a batalha!", 3);
                    else
                        dwBattleQuitTime = 0;
                }
            }
        }
    }

    DarkLevel = BackDarkLevel;
}

int GetViewCam()
{
    if (Settings::GetInstance()->cCamView == 0)
        return 12 * 64 * fONE;
    if (Settings::GetInstance()->cCamView == 1)
        return 12 * 64 * fONE * 2;
    if (Settings::GetInstance()->cCamView == 2)
        return 12 * 64 * fONE * 4;
}

void showFPS()
{
    GRAPHICDEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    GRAPHICDEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

    std::string frames = "FPS: " + std::to_string(DispRender);

    if (DispRender < 20)
    {
        SetFontTextColor(RGB(255, 0, 0));
    }
    else if (DispRender >= 20 && DispRender < 40)
    {
        SetFontTextColor(RGB(255, 0, 0));
    }
    else
    {
        SetFontTextColor(RGB(11, 252, 0));
    }

    dsTextLineOut(hdc, smScreenWidth - 120, smScreenHeight - 210, frames.c_str(), frames.length());
}

int flagDropItens = false;
extern int bHoldingSpace;
extern float progressHoldingSpace;

#define STATE_BAR_WIDTH		100
#define STATE_BAR_HEIGHT	16
#define STATE_BAR_SIZE		100

void RenderCharacterHP(smCHAR * pcUnitData, int iX, int iY)
{
    if (pcUnitData == NULL)
        return;

    const int iCurrHp = sinGetLife();
    const int iMaxHp = pcUnitData->smCharInfo.Life[1];

    DWORD dwColor;

    if (iCurrHp == 0)
        return;

    if (iX < 0 || (iX + STATE_BAR_WIDTH) >= RESOLUTION_WIDTH)
        return;

    if (iY < 0 || (iY + STATE_BAR_WIDTH) >= RESOLUTION_HEIGHT)
        return;

    int iPercent;
    int iPercent2;
    int iPercent3;

    iPercent = (iCurrHp * STATE_BAR_SIZE) / iMaxHp;
    iPercent2 = (iCurrHp * 511) / iMaxHp;
    iPercent2 = (iPercent2 * iPercent2) / 512;
    iPercent3 = iPercent2 & 0xFF;

    if (iPercent2 < 256)
        dwColor = D3DCOLOR_RGBA(255, iPercent3, 0, 255);
    else
        dwColor = D3DCOLOR_RGBA(255 - iPercent3, 255, 0, 255);

    int iHeight = (RESOLUTION_WIDTH / 4) * 3;
    float fSizeH = 0.0f, fSizeW = 0.0f;

    if (iHeight == RESOLUTION_HEIGHT)
        fSizeH = ((float)RESOLUTION_WIDTH / 800.0f);
    else
        fSizeH = ((float)RESOLUTION_WIDTH / (float)((RESOLUTION_HEIGHT / 3) * 4));

    fSizeH = ((float)RESOLUTION_WIDTH / 800.0f);
    fSizeW = ((float)RESOLUTION_WIDTH / 800.0f);

    dsDrawTexImageFloat(MatEnergyBox[3], (float)iX, (float)iY, 60, 6, 128, STATE_BAR_HEIGHT, 0, 0, STATE_BAR_WIDTH, 15, 255);

    if (iCurrHp > 0)
        dsDrawTexImageFloatColor(MatEnergyBox[4], (float)iX, (float)iY, (float)(iPercent + 3) * 0.6f, 6, 128, STATE_BAR_HEIGHT, 0, 0, (float)iPercent + 3, 15, dwColor);

    return;
}

int DrawGameState()
{
    int i = 0;
    int cnt = 0, cnt2 = 0;
    int y = 0, DispMaster = 0;
    smCHAR* lpChar = nullptr;
    scITEM* lpItem = nullptr;
    RECT ddRect;
    int BackDarkLevel = 0;
    DWORD dwColor;

    char msg[256] = { 0 };

    ddRect.left = 0;
    ddRect.right = 800;
    ddRect.top = 0;
    ddRect.bottom = 150;

    if (lpDDSMenu) {
        DrawSprite(0, WinSizeY - 150, lpDDSMenu, 0, 0, 800, 150);
    }

    smRender.ClearLight();

    BackDarkLevel = DarkLevel;
    DarkLevel = 0;

    RestoreInterfaceTexture();

    if (lpCharMsTrace && lpCharMsTrace->RendSucess)
    {
        Disp_tx = lpCharMsTrace->RendPoint.x - 32;
        Disp_ty = lpCharMsTrace->RendPoint.y - 12;
    }

    if (lpCharSelPlayer && lpCharMsTrace != lpCharSelPlayer)
    {
        if (lpCharSelPlayer->RendSucess)
        {
            Disp_rx = lpCharSelPlayer->RendPoint.x - 32;
            Disp_ry = lpCharSelPlayer->RendPoint.y - 12;
        }
    }

    lpChar = 0;
    lpItem = 0;

    if (lpMsTraceItem)
        lpItem = lpMsTraceItem;
    else
        lpItem = lpSelItem;

    if (VRKeyBuff['A'] || bShowDrops)
    {
        for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
        {
            if (scItems[cnt].Flag && scItems[cnt].ItemCode != 0 && lpSelItem != &scItems[cnt] && CanViewDropItem(&scItems[cnt]))
            {
                if (scItems[cnt].RendPoint.z >= 32 * fONE && scItems[cnt].RendPoint.z < GetViewCam())
                {
                    ESkinID ItemSkin = SKINID_Normal;
                    GAMECOREHANDLE->pcMessageBalloon->ResetMessage();
                    GAMECOREHANDLE->pcMessageBalloon->SetSkin(ItemSkin);
                    GAMECOREHANDLE->pcMessageBalloon->SetMessage(scItems[cnt].szName);

                    ARGBNew rarityColor = rarityColorsGround[0];
                    GAMECOREHANDLE->pcMessageBalloon->SetColor(RGBA(rarityColor.red, rarityColor.green, rarityColor.blue, rarityColor.alpha));
                    GAMECOREHANDLE->pcMessageBalloon->Render(scItems[cnt].RendPoint.x, scItems[cnt].RendPoint.y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
                }
            }
        }
    }

    if (lpSelItem && !lpCharSelPlayer && !lpCharMsTrace)
    {
        Disp_tx = MsSelPos.x;
        Disp_ty = MsSelPos.y;

        ESkinID ItemSkin = SKINID_Normal;
        GAMECOREHANDLE->pcMessageBalloon->ResetMessage();

        GAMECOREHANDLE->pcMessageBalloon->SetSkin(ItemSkin);
        GAMECOREHANDLE->pcMessageBalloon->SetMessage(lpSelItem->szName);

        ARGBNew rarityColor = rarityColorsGround[0];
        GAMECOREHANDLE->pcMessageBalloon->SetColor(RGBA(rarityColor.red, rarityColor.green, rarityColor.blue, rarityColor.alpha));
        GAMECOREHANDLE->pcMessageBalloon->Render(lpSelItem->RendPoint.x, lpSelItem->RendPoint.y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
    }

    if (MOUSEHANDLER->iLastCursorID != CursorClass)
    {
        GAMECOREHANDLE->pcItemInfoBox->Invalidate();
    }

    int SelFlag = 0;
    int z = 0;
    ChatMsgSortCnt = 0;

    for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
    {
        if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].RendSucess && chrOtherPlayer[cnt].smCharInfo.szName[0])
        {
            SelFlag = 0;

            if (PARTYHANDLER->IsPartyMember(chrOtherPlayer[cnt].dwObjectSerial))
                chrOtherPlayer[cnt].PartyFlag = 1;
            else if (PARTYHANDLER->IsRaidMember(chrOtherPlayer[cnt].dwObjectSerial))
                chrOtherPlayer[cnt].PartyFlag = 2;
            else
                chrOtherPlayer[cnt].PartyFlag = 0;

            if (chrOtherPlayer[cnt].RendPoint.z < GetViewCam())
            {
                if (chrOtherPlayer[cnt].szChatMessage[0])
                {
                    if (chrOtherPlayer[cnt].dwChatMessageTimer < dwPlayTime)
                    {
                        chrOtherPlayer[cnt].szChatMessage[0] = 0;
                    }
                    else if ((lstrlenA(chrOtherPlayer[cnt].szChatMessage) == 2 && chrOtherPlayer[cnt].szChatMessage[0] == 'e') && isdigit(chrOtherPlayer[cnt].szChatMessage[1]))
                    {
                        chrOtherPlayer[cnt].szChatMessage[0] = 0;
                    }
                    else if (chrOtherPlayer[cnt].smCharInfo.State)
                    {
                        lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
                        SelFlag++;
                    }
                }
            }

            if (chrOtherPlayer[cnt].dwTradeMsgCode && !SelFlag)
            {
                lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
                SelFlag++;
            }

            if (!SelFlag)
            {
                if (lpCharMsTrace == &chrOtherPlayer[cnt] ||
                    lpCharSelPlayer == &chrOtherPlayer[cnt] ||
                    (chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_NPC && chrOtherPlayer[cnt].RendPoint.z < GetViewCam()) ||
                    (chrOtherPlayer[cnt].smCharInfo.Life[0] > 0 && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY && chrOtherPlayer[cnt].smCharInfo.Brood == smCHAR_MONSTER_USER) ||
                    (chrOtherPlayer[cnt].smCharInfo.ClassClan && chrOtherPlayer[cnt].smCharInfo.ClassClan == UNITDATA->smCharInfo.ClassClan) ||
                    (HoMsgBoxMode && chrOtherPlayer[cnt].dwClanManageBit) ||
                    chrOtherPlayer[cnt].PartyFlag)
                {
                    lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
                }
            }
        }
    }
   /* // ===== DESENHA O SELETOR DE SERVIDOR =====
    int serverX = WinSizeX - 200;  // Ajuste a posição
    int serverY = 30;               // Ajuste a posição

    // Área clicável
    rcServerSelector.left = serverX;
    rcServerSelector.top = serverY;
    rcServerSelector.right = serverX + 180;
    rcServerSelector.bottom = serverY + 20;

    // Fundo do seletor (igual ao boss timer)
    dsDrawColorBox(RGBA(0, 0, 0, 150), serverX - 2, serverY - 2, 184, 24);
    dsDrawColorBox(RGBA(50, 50, 50, 200), serverX, serverY, 180, 20);

    // Texto do servidor
    SetFontTextColor(RGB(255, 255, 0));
    dsTextLineOut(hdc, serverX + 5, serverY + 2, szServerName, strlen(szServerName));

    // Seta indicando que é clicável
    SetFontTextColor(RGB(255, 255, 255));
    dsTextLineOut(hdc, serverX + 165, serverY + 2, "v", 2);

    // ===== JANELA DE SELEÇÃO (se aberta) =====
    if (bShowServerSelector)
    {
        int selectorX = serverX;
        int selectorY = serverY + 22;
        int selectorW = 180;
        int selectorH = 80;  // Altura para 3 mundos

        // Fundo da janela
        dsDrawColorBox(RGBA(0, 0, 0, 220), selectorX, selectorY, selectorW, selectorH);
        dsDrawColorBox(RGBA(80, 80, 80, 200), selectorX + 2, selectorY + 2, selectorW - 4, selectorH - 4);

        // Opções de mundo   //AQUI REMOVE OPÇÕES DO SELETOR
        const char* worlds[] = { "Servidor: Babel", "Servidor: Morion" };

        for (int i = 0; i < 2; i++)  //tem que ajustar pelo numero de servidores em
        {
            int optionY = selectorY + 5 + (i * 25);

            // Destaca se o mouse está em cima
            if (g_hoverWorld == i)
            {
                dsDrawColorBox(RGBA(100, 100, 100, 255), selectorX + 2, optionY - 2, selectorW - 4, 22);
            }

            // Ícone do mundo (se tiver)
            if (iWorldIcon[i] > 0)
            {
                dsDrawTexImage(iWorldIcon[i], selectorX + 5, optionY, 16, 16, 255);
                dsTextLineOut(hdc, selectorX + 25, optionY + 2, worlds[i], strlen(worlds[i]));
            }
            else
            {
                dsTextLineOut(hdc, selectorX + 10, optionY + 2, worlds[i], strlen(worlds[i]));
            }
        }
    }*/
    if (UNITDATA->szChatMessage[0])
    {
        if (UNITDATA->dwChatMessageTimer < dwPlayTime)
            UNITDATA->szChatMessage[0] = 0;
        else if ((lstrlenA(UNITDATA->szChatMessage) == 2 && UNITDATA->szChatMessage[0] == 'e') && isdigit(UNITDATA->szChatMessage[1]))
            UNITDATA->szChatMessage[0] = 0;
        else
            lpCharMsgSort[ChatMsgSortCnt++] = UNITDATA;
    }
    else
    {
        if (UNITDATA->dwTradeMsgCode)
        {
            lpCharMsgSort[ChatMsgSortCnt++] = UNITDATA;
        }
    }

    if (ChatMsgSortCnt > 0)
    {
        for (cnt = 0; cnt < ChatMsgSortCnt; cnt++)
        {
            for (cnt2 = cnt + 1; cnt2 < ChatMsgSortCnt; cnt2++)
            {
                if (lpCharMsgSort[cnt]->RendPoint.z < lpCharMsgSort[cnt2]->RendPoint.z ||
                    lpCharMsgSort[cnt] == lpCharMsTrace || lpCharMsgSort[cnt] == lpCharSelPlayer)
                {
                    lpChar = lpCharMsgSort[cnt];
                    lpCharMsgSort[cnt] = lpCharMsgSort[cnt2];
                    lpCharMsgSort[cnt2] = lpChar;
                }
            }
        }
    }

    int x;
    int pos = 0;
    y = 8 + (ViewAnx >> 6);

    if (Settings::GetInstance()->bShowLife)
    {
        if (MAP_ID != MAPID_RicartenTown && MAP_ID != MAPID_PillaiTown && MAP_ID != MAPID_Eura && MAP_ID != MAPID_Atlantis)
        {
            RenderCharacterHP(UNITDATA, UNITDATA->RendPoint.x - 30, UNITDATA->RendRect2D.top + y - 24);
        }
    }

    if (UNITDATA->RendPoint.z < GetViewCam() && !UNITDATA->szChatMessage[0] && !UNITDATA->dwTradeMsgCode)
    {
        if (!Settings::GetInstance()->bHidePlayerNames)
        {
            GAMECOREHANDLE->pcMessageBalloon->ResetMessage();
            GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
            GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Normal);
            GAMECOREHANDLE->pcMessageBalloon->SetMessage(UNITDATA->smCharInfo.szName);
            GAMECOREHANDLE->pcMessageBalloon->SetColor(RGBA(255, 255, 255, 200));
            GAMECOREHANDLE->pcMessageBalloon->Render(UNITDATA->RendPoint.x, UNITDATA->RendRect2D.top + y - 20, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
        }
    }

    for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
    {
        if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].RendSucess && chrOtherPlayer[cnt].smCharInfo.szName[0])
        {
            cSHOW_DMG::getInstance()->DrawDmg(chrOtherPlayer[cnt].dwObjectSerial, chrOtherPlayer[cnt].RendPoint.x, chrOtherPlayer[cnt].RendRect2D.top + y);
        }
    }

    cSHOW_DMG::getInstance()->DrawDmg(lpCurPlayer->dwObjectSerial, lpCurPlayer->RendPoint.x, lpCurPlayer->RendRect2D.top + y);

    for (cnt = 0; cnt < ChatMsgSortCnt; cnt++)
    {
        DWORD dwColor = RGBA(255, 255, 255, 200);
        DWORD dwTitleColor = RGBA(255, 225, 150, 255);
        BOOL bShowBar = FALSE;
        BOOL bShowOwner = FALSE;
        BOOL bSelected = FALSE;

        smCHAR* pc = lpCharMsgSort[cnt];

        if (pc)
        {
            char Classe[32] = { 0 };

            switch (pc->smCharInfo.JOB_CODE)
            {
            case 1:
                STRINGCOPY(Classe, "Lutador Grandioso");
                break;
            case 2:
                STRINGCOPY(Classe, "Lord Metal");
                break;
            case 3:
                STRINGCOPY(Classe, "Arqueira Sagitaria");
                break;
            case 4:
                STRINGCOPY(Classe, "Mestre Assassino");
                break;
            case 5:
                STRINGCOPY(Classe, "Rainhda de Valhalla");
                break;
            case 6:
                STRINGCOPY(Classe, "Cavaleiro Real");
                break;
            case 7:
                STRINGCOPY(Classe, "Mestre dos Magos");
                break;
            case 8:
                STRINGCOPY(Classe, "Alta Sacerdotisa");
                break;
            }

            for (x = 0; x <= EventoArena::GetInstance()->qtJogadores; x++)
            {
                string namePlayer = pc->smCharInfo.szName;
                string namePlayerTeam = EventoArena::GetInstance()->getPlayersFromTeam.pckgTeam[x].name;

                if (namePlayer.compare(namePlayerTeam) == 0)
                {
                    pc->nEquipeArena = EventoArena::GetInstance()->getPlayersFromTeam.pckgTeam[x].equipeNum;
                }
            }

            if (pc->PartyFlag == 1)
            {
                dwColor = RGBA(160, 200, 240, 180);
                bShowBar = TRUE;
            }
            else if (pc->PartyFlag == 2)
            {
                dwColor = RGBA(255, 40, 240, 230);
                bShowBar = TRUE;
            }
            else if (pc->smCharInfo.State == smCHAR_STATE_ENEMY)
            {
                if (pc->smCharInfo.Brood == smCHAR_MONSTER_USER)
                {
                    dwColor = RGBA(255, 220, 255, 160);

                    if (pc->smCharInfo.Next_Exp == UNITDATA->dwObjectSerial || pc->smCharInfo.ClassClan)
                    {
                        dwColor = RGBA(255, 0, 162, 232);
                        bShowOwner = TRUE;
                        bShowBar = TRUE;
                    }
                    else
                        bShowOwner = TRUE;
                }
                else
                    dwColor = RGBA(255, 255, 210, 210);
            }
            else if (pc->smCharInfo.State == smCHAR_STATE_NPC)
            {
                dwColor = RGBA(255, 180, 180, 255);
            }

            if (pc == lpCharMsTrace)
            {
                if (pc->smCharInfo.State == smCHAR_STATE_ENEMY && pc->PkMode_CharState != smCHAR_MONSTER_USER)
                    dwColor = RGBA(255, 255, 230, 200);
                else
                    dwColor = RGBA(255, 255, 255, 255);

                bSelected = TRUE;
            }
            else
            {
                if (pc == lpCharSelPlayer && pc->szChatMessage[0])
                    bSelected = TRUE;
            }

            LPDIRECT3DTEXTURE9 psTextureClanIcon = NULL;
            char* pszClanName = NULL;

            if (pc->smCharInfo.ClassClan)
            {
                if (pc == UNITDATA)
                {
                    psTextureClanIcon = cldata.hClanMark;
                    pszClanName = cldata.name;
                }
                else if (pc->ClanInfoNum >= 0)
                {
                    psTextureClanIcon = ClanInfo[pc->ClanInfoNum].hClanMark32;
                    pszClanName = ClanInfo[pc->ClanInfoNum].ClanInfoHeader.ClanName;
                }
            }

            if (((pc->szChatMessage[0] || pc->dwTradeMsgCode) && (pc->RendPoint.z < GetViewCam()) ||
                pc == UNITDATA))
            {
                if (pszClanName && pc != lpCharMsTrace && pc != lpCharSelPlayer)
                {
                    if (!UNITDATA->smCharInfo.ClassClan || pc->smCharInfo.ClassClan != UNITDATA->smCharInfo.ClassClan)
                        pszClanName = NULL;
                }

                if (pc->szChatMessage[0])
                {
                    GAMECOREHANDLE->pcMessageBalloon->ResetMessage();

                    if (psTextureClanIcon)
                        GAMECOREHANDLE->pcMessageBalloon->SetClanIconTexture(psTextureClanIcon);

                    GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
                    GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Normal);

                    if (pc->smCharInfo.State == smCHAR_STATE_NPC)
                    {
                        GAMECOREHANDLE->pcMessageBalloon->SetMessage(FormatString("%s: %s", pc->smCharInfo.szName, pc->szChatMessage));
                        GAMECOREHANDLE->pcMessageBalloon->GetTextMessage()->SetHighlightTextColor(dwColor);
                        GAMECOREHANDLE->pcMessageBalloon->SetColor(-1);
                    }
                    else
                    {
                        if (pc->PlayCurseTopLVL && !pc->PlayCursePvP)
                            GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText(Classe, 3);
                        else if (pc->PlayCursePvP && !pc->PlayCurseTopLVL)
                            GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText("Rei do PVP", 2);
                        else if (pc->PlayCurseTopLVL && pc->PlayCursePvP)
                        {
                            GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText("Rei do PVP", 2);
                        }

                        GAMECOREHANDLE->pcMessageBalloon->SetMessage(pc->szChatMessage);
                        GAMECOREHANDLE->pcMessageBalloon->SetColor(dwColor);
                    }

                    GAMECOREHANDLE->pcMessageBalloon->Render(pc->RendPoint.x, pc->RendRect2D.top + y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
                }
                else
                {
                    if (pc->szTradeMessage[0])
                    {
                        GAMECOREHANDLE->pcMessageBalloon->ResetMessage();

                        if (psTextureClanIcon)
                            GAMECOREHANDLE->pcMessageBalloon->SetClanIconTexture(psTextureClanIcon);

                        GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
                        GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Blue);
                        GAMECOREHANDLE->pcMessageBalloon->SetMessage(pc->szTradeMessage);
                        GAMECOREHANDLE->pcMessageBalloon->SetColor(dwColor);
                        GAMECOREHANDLE->pcMessageBalloon->Render(pc->RendPoint.x, pc->RendRect2D.top + y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
                    }
                }
            }
            else if (pc->RendPoint.z < GetViewCam())
            {
                if (StageField[UNITDATA->OnStageField]->FieldCode == FIELD_ARENA && EventoArena::GetInstance()->stageArena == 2)
                {
                    if (pc->nEquipeArena != UNITDATA->nEquipeArena)
                    {
                        GAMECOREHANDLE->pcMessageBalloon->ResetMessage();

                        if (psTextureClanIcon)
                            GAMECOREHANDLE->pcMessageBalloon->SetClanIconTexture(psTextureClanIcon);

                        GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
                        GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Blue);
                        GAMECOREHANDLE->pcMessageBalloon->SetMessage(pc->smCharInfo.szName);
                        GAMECOREHANDLE->pcMessageBalloon->SetColor(RGBA(255, 255, 0, 0));
                        GAMECOREHANDLE->pcMessageBalloon->Render(pc->RendPoint.x, pc->RendRect2D.top + y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
                    }
                    else
                    {
                        GAMECOREHANDLE->pcMessageBalloon->ResetMessage();

                        if (psTextureClanIcon)
                            GAMECOREHANDLE->pcMessageBalloon->SetClanIconTexture(psTextureClanIcon);

                        GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
                        GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Blue);
                        GAMECOREHANDLE->pcMessageBalloon->SetMessage(pc->smCharInfo.szName);
                        GAMECOREHANDLE->pcMessageBalloon->SetColor(dwColor);
                        GAMECOREHANDLE->pcMessageBalloon->Render(pc->RendPoint.x, pc->RendRect2D.top + y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
                    }
                }
                else
                {
                    if (pc->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R ||
                        pc->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G ||
                        pc->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B ||
                        pc->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_N)
                    {
                    }
                    else if (bShowOwner && !pc->smCharInfo.ClassClan)
                    {
                        GAMECOREHANDLE->pcMessageBalloon->ResetMessage();

                        if (psTextureClanIcon)
                            GAMECOREHANDLE->pcMessageBalloon->SetClanIconTexture(psTextureClanIcon);

                        GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
                        GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Normal);
                        GAMECOREHANDLE->pcMessageBalloon->SetMessage(pc->smCharInfo.szName);
                        GAMECOREHANDLE->pcMessageBalloon->SetColor(pc->PlayerPvPMode ? RGBA(255, 255, 0, 0) : dwColor);
                        GAMECOREHANDLE->pcMessageBalloon->Render(pc->RendPoint.x, pc->RendRect2D.top + y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
                    }
                    else
                    {
                        if (pszClanName)
                        {
                            if (smConfig.DebugMode && VRKeyBuff[VK_CONTROL])
                                STRINGFORMATLEN(strBuff, 240, "%d/%d", pc->smCharInfo.ClassClan, pc->ClanInfoNum);
                            else
                                STRINGFORMATLEN(strBuff, 240, "[%s]", pszClanName);

                            GAMECOREHANDLE->pcMessageBalloon->ResetMessage();

                            if (psTextureClanIcon)
                                GAMECOREHANDLE->pcMessageBalloon->SetClanIconTexture(psTextureClanIcon);

                            GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
                            GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Normal);
                            GAMECOREHANDLE->pcMessageBalloon->SetMessage(pc->smCharInfo.szName);
                            GAMECOREHANDLE->pcMessageBalloon->SetBellatraIconID(pc->dwClanManageBit);
                            GAMECOREHANDLE->pcMessageBalloon->SetClanName(pszClanName);
                            GAMECOREHANDLE->pcMessageBalloon->SetColor(pc->PlayerPvPMode ? RGBA(255, 255, 0, 0) : dwColor);

                            if ((pc->smCharInfo.State == smCHAR_STATE_USER || pc->PkMode_CharState == smCHAR_STATE_USER))
                            {
                                if (pc->PlayCurseTopLVL && !pc->PlayCursePvP)
                                    GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText(Classe, 3);
                                else if (pc->PlayCursePvP && !pc->PlayCurseTopLVL)
                                    GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText("Rei do PVP", 2);
                                else if (pc->PlayCurseTopLVL && pc->PlayCursePvP)
                                {
                                    GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText("Rei do PVP", 2);
                                }
                            }

                            if (!Settings::GetInstance()->bHidePlayerNames || (pc->smCharInfo.State == smCHAR_STATE_NPC) || (pc->smCharInfo.State == smCHAR_STATE_ENEMY))
                                GAMECOREHANDLE->pcMessageBalloon->Render(pc->RendPoint.x, pc->RendRect2D.top + y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
                        }
                        else
                        {
                            GAMECOREHANDLE->pcMessageBalloon->ResetMessage();

                            if (UNITDATA->sPosition.WithinXZDistance(&pc->sPosition, 1228800))
                            {
                                if (psTextureClanIcon)
                                    GAMECOREHANDLE->pcMessageBalloon->SetClanIconTexture(psTextureClanIcon);

                                if (pc->smCharInfo.State == smCHAR_STATE_NPC)
                                {
                                    GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
                                    GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Normal);
                                    GAMECOREHANDLE->pcMessageBalloon->SetMessage(pc->smCharInfo.szName);
                                    GAMECOREHANDLE->pcMessageBalloon->SetColor(dwColor);
                                }
                                else
                                {
                                    GAMECOREHANDLE->pcMessageBalloon->IsCharacterMessage(TRUE);
                                    GAMECOREHANDLE->pcMessageBalloon->SetSkin(SKINID_Normal);
                                    GAMECOREHANDLE->pcMessageBalloon->SetMessage(pc->smCharInfo.szName);
                                    GAMECOREHANDLE->pcMessageBalloon->SetBellatraIconID(pc->dwClanManageBit);
                                    GAMECOREHANDLE->pcMessageBalloon->SetColor(pc->PlayerPvPMode ? RGBA(255, 255, 0, 0) : dwColor);
                                }

                                if ((pc->smCharInfo.State == smCHAR_STATE_USER || pc->PkMode_CharState == smCHAR_STATE_USER))
                                {
                                    if (pc->PlayCurseTopLVL && !pc->PlayCursePvP)
                                        GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText(Classe, 3);
                                    else if (pc->PlayCursePvP && !pc->PlayCurseTopLVL)
                                        GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText("Rei do PVP", 2);
                                    else if (pc->PlayCurseTopLVL && pc->PlayCursePvP)
                                    {
                                        GAMECOREHANDLE->pcMessageBalloon->AddCharTitleText("Rei do PVP", 2);
                                    }
                                }

                                if (!Settings::GetInstance()->bHidePlayerNames || (pc->smCharInfo.State == smCHAR_STATE_NPC) || (pc->smCharInfo.State == smCHAR_STATE_ENEMY))
                                    GAMECOREHANDLE->pcMessageBalloon->Render(pc->RendPoint.x, pc->RendRect2D.top + y, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
                            }
                        }
                    }
                }
            }
        }
    }

    if (lpCurPlayer->AttackSkil)
    {
        switch (lpCurPlayer->AttackSkil & 0xFF)
        {
        case SKILL_PLAY_CHARGING_STRIKE:
            cnt = lpCurPlayer->frame - lpCurPlayer->MotionInfo->StartFrame * 160;
            if (lpCurPlayer->MotionInfo->EventFrame[0] < (DWORD)cnt && lpCurPlayer->MotionInfo->EventFrame[1] > (DWORD)cnt)
            {
                cnt -= (int)lpCurPlayer->MotionInfo->EventFrame[0];
                cnt2 = (int)(lpCurPlayer->MotionInfo->EventFrame[1] - lpCurPlayer->MotionInfo->EventFrame[0]);
                lpCurPlayer->DrawChargingBar(lpCurPlayer->RendPoint.x - 30, lpCurPlayer->RendRect2D.bottom, cnt, cnt2);
            }
            break;
        case SKILL_PLAY_PHOENIX_SHOT:
            cnt = lpCurPlayer->frame - lpCurPlayer->MotionInfo->StartFrame * 160;
            if (lpCurPlayer->MotionInfo->EventFrame[0] < (DWORD)cnt && lpCurPlayer->MotionInfo->EventFrame[1] > (DWORD)cnt)
            {
                cnt -= (int)lpCurPlayer->MotionInfo->EventFrame[0];
                cnt2 = (int)(lpCurPlayer->MotionInfo->EventFrame[1] - lpCurPlayer->MotionInfo->EventFrame[0]);
                lpCurPlayer->DrawChargingBar(lpCurPlayer->RendPoint.x - 30, lpCurPlayer->RendRect2D.bottom, cnt, cnt2);
            }
            break;
        }
    }

    if (bHoldingSpace)
    {
        if (VRKeyBuff[VK_SPACE])
        {
            lpCurPlayer->DrawChargingBar(lpCurPlayer->RendPoint.x - 30, lpCurPlayer->RendRect2D.bottom, (int)progressHoldingSpace, 100.f);
        }
        else
            bHoldingSpace = false;
    }

    if (DispInterface)
    {
        if (DispEachMode)
        {
        }
        else
        {
            DrawEachPlayer(0, 0, 0);

            if (chrEachMaster)
            {
                if (lpCharMsTrace)
                    CHUDCONTROLLER->pcLastUnitDataTarget = lpCharMsTrace;

                if (CHUDCONTROLLER->pcLastUnitDataTarget)
                    CHUDCONTROLLER->UpdateTargetInfo(CHUDCONTROLLER->pcLastUnitDataTarget);
                else
                    CHUDCONTROLLER->UpdateTargetInfo(chrEachMaster);

                CHUDCONTROLLER->SetRenderTarget(TRUE);
            }
            else
            {
                CHUDCONTROLLER->pcLastUnitDataTarget = NULL;
                CHUDCONTROLLER->SetRenderTarget(FALSE);
            }

            dsDrawOffset_X = WinSizeX - 800;
            dsDrawOffset_Y = WinSizeY - 600;
            dsDrawOffsetArray = dsARRAY_RIGHT | dsARRAY_BOTTOM;
            dsMenuCursorPos(&pCursorPos, 3);

            dsMenuCursorPos(&pCursorPos, 0);
            dsDrawOffsetArray = dsARRAY_TOP;
            dsDrawOffset_X = 0;
            dsDrawOffset_Y = 0;

            DrawInterfaceParty(pHoPartyMsgBox.x, pHoPartyMsgBox.y);
        }
        if (smConfig.DebugMode)
        {
            extern int Debug_TalkZoomMode;
            if (Debug_TalkZoomMode && lpCurPlayer->TalkPattern)
            {
                extern void DrawTalkZoom(smCHAR * lpChar, smPAT3D * lpPattern, float fx, float fy);
                DrawTalkZoom(lpCurPlayer, lpCurPlayer->TalkPattern, 0.2f, 0.32f);
            }
        }
    }

    if (EachTradeButton && chrEachMaster)
    {
        DisplayPartyTradeButton();
    }

    DisplaySodScore();

#ifdef _SINBARAM
    RestoreInterfaceTexture();

    dsDrawOffset_X = WinSizeX - 800;
    dsDrawOffset_Y = WinSizeY - 600;

    if (DispInterface) sinDraw();

    dsDrawOffset_X = 0;
    dsDrawOffset_Y = 0;
#endif

    if (BellatraEffectInitFlag)
        DrawBellatraFontEffect();

    // ===== DESENHA A MINI SKILL BAR =====
    if (g_pMiniSkillBar && g_pMiniSkillBar->IsVisible()) {
        g_pMiniSkillBar->Render();
    }
    // =====================================

#ifdef _WINMODE_DEBUG
    int rcv1, rcv2, snd1, snd2, arcv1, brcv1, arcv2, brcv2;
    int LineY;

    if (DisplayDebug)
    {
        rcv1 = 0;
        rcv2 = 0;
        snd1 = 0;
        snd2 = 0;
        arcv1 = 0;
        brcv1 = 0;
        arcv2 = 0;
        brcv2 = 0;

        if (smWsockServer)
        {
            rcv1 = smWsockServer->RecvPacketCount;
            snd1 = smWsockServer->SendPacketCount;
            arcv1 = smWsockServer->RecvPopCount;
            brcv1 = smWsockServer->RecvPopErrorCount;
        }
        else
        {
            rcv1 = 0; snd1 = 0;
        }

        if (smWsockUserServer)
        {
            rcv2 = smWsockUserServer->RecvPacketCount;
            snd2 = smWsockUserServer->SendPacketCount;
            arcv2 = smWsockUserServer->RecvPopCount;
            brcv2 = smWsockUserServer->RecvPopErrorCount;
        }
        else
        {
            rcv2 = 0; snd2 = 0;
        }

        wsprintf(strBuff, "%d(%d) %d x=%d z=%d y=%d VRAM=%d R1=%d(%d) R2=%d(%d) S1=%d S2=%d (%d/%d) (%d/%d) RcvTurb( %d )", DispRender, DispMainLoop, DispPolyCnt, lpCurPlayer->pX >> (FLOATNS), lpCurPlayer->pZ >> (FLOATNS), lpCurPlayer->pY >> (FLOATNS), (VramTotal / (1024 * 1024)),
            rcv1, Debug_RecvCount1, rcv2, Debug_RecvCount2, snd1, snd2, brcv1, arcv1, brcv2, arcv2, smTransTurbRcvMode);

        SetFontTextColor(RGB(0, 0, 0));
        dsTextLineOut(hdc, 11, 11, strBuff, lstrlen(strBuff));
        SetFontTextColor(RGB(255, 255, 255));
        dsTextLineOut(hdc, 10, 10, strBuff, lstrlen(strBuff));

        wsprintf(strBuff, "Stage : %s , %s", szGameStageName[0], szGameStageName[1]);
        SetFontTextColor(RGB(0, 0, 0));
        dsTextLineOut(hdc, 11, 31, strBuff, lstrlen(strBuff));
        SetFontTextColor(RGB(255, 255, 255));
        dsTextLineOut(hdc, 10, 30, strBuff, lstrlen(strBuff));

        wsprintf(strBuff, "World Time (%d:%d)", dwGameHour, dwGameMin);
        SetFontTextColor(RGB(0, 0, 0));
        dsTextLineOut(hdc, (WinSizeX >> 1) + 1, 31, strBuff, lstrlen(strBuff));
        SetFontTextColor(RGB(255, 255, 255));
        dsTextLineOut(hdc, (WinSizeX >> 1), 30, strBuff, lstrlen(strBuff));

        if (lpCurPlayer->PatLoading == FALSE)
        {
            if (AdminCharMode)
                wsprintf(strBuff, "%s", lpCurPlayer->smCharInfo.szName);
            else
                wsprintf(strBuff, "%s", lpCurPlayer->lpDinaPattern->szPatName);

            SetFontTextColor(RGB(0, 0, 0));
            dsTextLineOut(hdc, (WinSizeX >> 1) + 1 + 120, 31, strBuff, lstrlen(strBuff));
            SetFontTextColor(RGB(255, 255, 255));
            dsTextLineOut(hdc, (WinSizeX >> 1) + 120, 30, strBuff, lstrlen(strBuff));

            wsprintf(strBuff, "      X: %d   Y: %d", pCursorPos.x, pCursorPos.y);
            SetFontTextColor(RGB(255, 255, 255));
            dsTextLineOut(hdc, pCursorPos.x, pCursorPos.y, strBuff, lstrlen(strBuff));

            wsprintf(strBuff, "Damage : %d", LastAttackDamage);
            SetFontTextColor(RGB(0, 0, 0));
            dsTextLineOut(hdc, 9, 48, strBuff, lstrlen(strBuff));
            SetFontTextColor(RGB(255, 255, 255));
            dsTextLineOut(hdc, 8, 47, strBuff, lstrlen(strBuff));

            wsprintf(strBuff, "RcvDamage:(%d) [%d] %d %d", Record_TotalRecvDamageCount, Record_RecvDamageCount, Record_DefenceCount, Record_BlockCount);
            SetFontTextColor(RGB(0, 0, 0));
            dsTextLineOut(hdc, 9, 62, strBuff, lstrlen(strBuff));
            SetFontTextColor(RGB(255, 255, 255));
            dsTextLineOut(hdc, 8, 61, strBuff, lstrlen(strBuff));

            if (AreaServerMode)
            {
                if (lpWSockServer_Area[0])
                {
                    wsprintf(strBuff, "Area Server[0]: (%s)", lpWSockServer_Area[0]->szIPAddr);
                    SetFontTextColor(RGB(0, 0, 0));
                    dsTextLineOut(hdc, 9, 82, strBuff, lstrlen(strBuff));
                    SetFontTextColor(RGB(255, 255, 255));
                    dsTextLineOut(hdc, 8, 81, strBuff, lstrlen(strBuff));
                }
                if (lpWSockServer_Area[1])
                {
                    wsprintf(strBuff, "Area Server[1]: (%s)", lpWSockServer_Area[1]->szIPAddr);
                    SetFontTextColor(RGB(0, 0, 0));
                    dsTextLineOut(hdc, 9, 96, strBuff, lstrlen(strBuff));
                    SetFontTextColor(RGB(255, 255, 255));
                    dsTextLineOut(hdc, 8, 95, strBuff, lstrlen(strBuff));
                }

                if (lpWSockServer_DispArea[0])
                {
                    wsprintf(strBuff, "Area Server[0]: (%s)", lpWSockServer_DispArea[0]->szIPAddr);
                    SetFontTextColor(RGB(0, 0, 0));
                    dsTextLineOut(hdc, 209, 82, strBuff, lstrlen(strBuff));
                    SetFontTextColor(RGB(255, 255, 255));
                    dsTextLineOut(hdc, 208, 81, strBuff, lstrlen(strBuff));
                }
                if (lpWSockServer_DispArea[1])
                {
                    wsprintf(strBuff, "Area Server[1]: (%s)", lpWSockServer_DispArea[1]->szIPAddr);
                    SetFontTextColor(RGB(0, 0, 0));
                    dsTextLineOut(hdc, 209, 96, strBuff, lstrlen(strBuff));
                    SetFontTextColor(RGB(255, 255, 255));
                    dsTextLineOut(hdc, 208, 95, strBuff, lstrlen(strBuff));
                }

                wsprintf(strBuff, "AreaCount(%d) AreaConn(%d) AreaIP( [%d] %d %d ) Step(%d)",
                    dwDebugAreaCount, dwDebugAreaConnCount,
                    dwDebugAreaIP[0], dwDebugAreaIP[1], dwDebugAreaIP[2], dwDebugAreaStep);

                SetFontTextColor(RGB(0, 0, 0));
                dsTextLineOut(hdc, 9, 108, strBuff, lstrlen(strBuff));
                SetFontTextColor(RGB(255, 255, 255));
                dsTextLineOut(hdc, 8, 108, strBuff, lstrlen(strBuff));
            }
        }

        SetFontTextColor(RGB(255, 255, 255));

        LineY = 48;
        for (i = 0; i < OTHER_PLAYER_MAX; i++)
        {
            if (chrOtherPlayer[i].Flag && chrOtherPlayer[i].Pattern && chrOtherPlayer[i].smCharInfo.State == smCHAR_STATE_USER)
            {
                wsprintf(strBuff, "%s", chrOtherPlayer[i].smCharInfo.szName);
                SetFontTextColor(RGB(0, 0, 0));
                dsTextLineOut(hdc, WinSizeX - 220, LineY + 1, strBuff, lstrlen(strBuff));
                SetFontTextColor(RGB(255, 255, 255));
                dsTextLineOut(hdc, WinSizeX - 221, LineY, strBuff, lstrlen(strBuff));
                LineY += 16;
                if (LineY > 460) break;
            }
        }

        int MonCharBuff[OTHER_PLAYER_MAX];
        int MonCharCnt = 0;
        int MonCnt;

        for (i = 0; i < OTHER_PLAYER_MAX; i++)
        {
            if (chrOtherPlayer[i].Flag && chrOtherPlayer[i].Pattern && chrOtherPlayer[i].smCharInfo.State != smCHAR_STATE_USER)
            {
                MonCharBuff[MonCharCnt++] = i;
            }
        }

        LineY = 48;
        for (i = 0; i < MonCharCnt; i++)
        {
            if (MonCharBuff[i] >= 0)
            {
                MonCnt = 1;
                for (cnt = i + 1; cnt < MonCharCnt; cnt++)
                {
                    if (MonCharBuff[cnt] >= 0 &&
                        lstrcmp(chrOtherPlayer[MonCharBuff[cnt]].smCharInfo.szName,
                            chrOtherPlayer[MonCharBuff[i]].smCharInfo.szName) == 0)
                    {
                        MonCharBuff[cnt] = -1;
                        MonCnt++;
                    }
                }

                wsprintf(strBuff, "%s x %d", chrOtherPlayer[MonCharBuff[i]].smCharInfo.szName, MonCnt);
                SetFontTextColor(RGB(0, 0, 0));
                dsTextLineOut(hdc, WinSizeX - 380, LineY + 1, strBuff, lstrlen(strBuff));
                if (chrOtherPlayer[MonCharBuff[i]].smCharInfo.State == smCHAR_STATE_NPC)
                    SetFontTextColor(RGB(192, 192, 255));
                else
                    SetFontTextColor(RGB(255, 192, 192));
                dsTextLineOut(hdc, WinSizeX - 381, LineY, strBuff, lstrlen(strBuff));
                LineY += 16;
                if (LineY > 460) break;
            }
        }
    }
#endif

    if (DisconnectFlag)
    {
        if (DisconnectServerCode == 0)
        {
            Utils_Log(3, "DC: WinMain.cpp 3798");
            DrawMessage(MidX - 64, MidY, mgDiconnect, 36, BOX_ONE);
        }
        if (DisconnectServerCode == 1)
        {
            DrawMessage(MidX - 64, MidY, mgDiconnect1, 36, BOX_ONE);
        }
        if (DisconnectServerCode == 2)
        {
            DrawMessage(MidX - 64, MidY, mgDiconnect2, 36, BOX_ONE);
        }
        if (DisconnectServerCode == 3)
        {
            DrawMessage(MidX - 64, MidY, mgDiconnect3, 36, BOX_ONE);
        }
        if (DisconnectServerCode == 4)
        {
            DrawMessage(MidX - 64, MidY, mgDiconnect4, 36, BOX_ONE);
        }

#ifdef _WINMODE_DEBUG
        if (!smConfig.DebugMode && !quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime) quit = TRUE;
#else
        if (!quit && ((DWORD)DisconnectFlag + 5000) < dwPlayTime) quit = TRUE;
#endif
    }
    else
    {
        if (quit)
            TitleBox::GetInstance()->SetText("Saindo do Jogo", 3);
        else
        {
            if (dwCloseBoxTime && dwCloseBoxTime > dwPlayTime)
            {
                TitleBox::GetInstance()->SetText("Por favor, feche as janelas!", 3);
            }
            else
            {
                if (dwBattleQuitTime)
                {
                    if ((dwBattleQuitTime + 5000) > dwPlayTime)
                        TitleBox::GetInstance()->SetText("Você não pode sair durante a batalha!", 3);
                    else
                        dwBattleQuitTime = 0;
                }
            }
        }
    }

    DarkLevel = BackDarkLevel;

    if (bShowMapTitle && fMapTitleAlpha > 0.0f && szCurrentMapName[0])
    {
        float alpha = min(fMapTitleAlpha, 1.0f);
        if (alpha < 0.05f) return TRUE;

        int alphaInt = (int)(alpha * 255.0f);
        TitleBox::GetInstance()->SetText(szCurrentMapName, 0);
    }
    DrawSkillChatMessages();
    return TRUE;
}

void _stdcall smPlayD3D(int x, int y, int z, int ax, int ay, int az)
{
    eCAMERA_TRACE eTrace;
    int ap;

    DispPolyCnt = 0;

    if (Graphics::Graphics::GetInstance()->IsDeviceReady())
    {
        if (Graphics::Graphics::GetInstance()->GetRenderer()->Begin())
        {
            ImGuiFlags::GetInstance()->InstancesFlag();

            SetRendSight();

            int Mapfl;
            int cy;
            int mapY;

            Mapfl = 0;
            cy = y + 16 * fONE;

            if (!DebugPlayer)
            {
                if (smGameStage[0])
                {
                    mapY = (smGameStage[0]->GetHeight(x, z));
                    if (y < mapY)
                    {
                        y = mapY;
                        y += 8 << FLOATNS;
                    }
                    if (mapY > CLIP_OUT) Mapfl++;
                }
                if (smGameStage[1])
                {
                    mapY = (smGameStage[1]->GetHeight(x, z));
                    if (y < mapY)
                    {
                        y = mapY;
                        y += 8 << FLOATNS;
                    }
                    if (mapY > CLIP_OUT)
                        Mapfl++;
                }
            }
            if (g_bIsServer3) {
                ApplyFogEffect();  // ou ApplyFogEffectAlt()
            }
            Mix_CodeVram();

            smRender.Color_R = BrCtrl;
            smRender.Color_G = BrCtrl;
            smRender.Color_B = BrCtrl;
            smRender.Color_A = BrCtrl;

            smRender.Color_R = -DarkLevel + BackColor_R;
            smRender.Color_G = -DarkLevel + BackColor_G;
            smRender.Color_B = -DarkLevel + BackColor_B;

            if (smRender.Color_R < -100)
                smRender.Color_R = -100;
            if (smRender.Color_G < -100)
                smRender.Color_G = -100;
            if (smRender.Color_B < -85)
                smRender.Color_B = -85;

            if (DarkLevel > 50) {
                smRender.Color_B += (int)(DarkLevel * 0.2f);
                smRender.Color_R -= (int)(DarkLevel * 0.07f);
            }
            if (dwM_BlurTime)
            {
                if (dwM_BlurTime < dwPlayTime)
                {
                    dwM_BlurTime = 0;
                }
            }

            auto ambientColor = Math::Color(smRender.Color_R, smRender.Color_G, smRender.Color_B);

            if (smRender.TerrainShader)
                smRender.TerrainShader->SetFloatArray("AmbientColor", &ambientColor.r, 4);

            Graphics::Graphics::GetInstance()->GetRenderer()->SetAmbientColor(ambientColor);

            GRAPHICDEVICE->Clear(0, 0, 2, smBackColor, 1.0f, 0);

            y += (32 << FLOATNS);

            if (anx <= 40 && dist <= 100)
                y -= ((110 - dist) << FLOATNS);

            TraceTargetPosi.x = x;
            TraceTargetPosi.y = y;
            TraceTargetPosi.z = z;

            if (AutoCameraFlag)
            {
                TraceCameraMain();

                x = TraceCameraPosi.x;
                y = TraceCameraPosi.y;
                z = TraceCameraPosi.z;
            }

            int ey = lpCurPlayer->pY + (32 * fONE);
            if (anx <= 40 && dist <= 100)
                ey += ((100 - dist) * fONE);

            ActionGameMode = FALSE;

            if (lpCurPlayer && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ACTION)
            {
                x = lpCurPlayer->pX;
                y = StageField[lpCurPlayer->OnStageField]->ActionCamera.FixPos.y + 80 * fONE;
                z = StageField[lpCurPlayer->OnStageField]->ActionCamera.FixPos.z * fONE;

                if (x < StageField[lpCurPlayer->OnStageField]->ActionCamera.LeftX * fONE) x = StageField[lpCurPlayer->OnStageField]->ActionCamera.LeftX * fONE;
                else if (x > StageField[lpCurPlayer->OnStageField]->ActionCamera.RightX * fONE) x = StageField[lpCurPlayer->OnStageField]->ActionCamera.RightX * fONE;

                MakeTraceMatrix(&eTrace, x, y, z, x, lpCurPlayer->pY, 326711 * fONE);

                x = lpCurPlayer->pX;
                y = 213140 + 80 * fONE;
                z = (36711 - 290) * fONE;

                MakeTraceMatrix(&eTrace, x, y, z, lpCurPlayer->pX, lpCurPlayer->pY, 326711 * fONE);

                ax = eTrace.AngX;
                ay = eTrace.AngY;
                smRender.OpenCameraPosi(x, y, z, &eTrace.eRotMatrix);

                ActionGameMode = TRUE;
            }
            else if (!DebugPlayer)
            {
                MakeTraceMatrix(&eTrace, x, y, z, lpCurPlayer->pX, ey, lpCurPlayer->pZ);

                camera->SetPosition(Math::Vector3(x / 256.0f, y / 256.0f, z / 256.0f), Math::Vector3(lpCurPlayer->pX / 256.0f, ey / 256.0f, lpCurPlayer->pZ / 256.0f));

                ax = eTrace.AngX;
                ay = eTrace.AngY;
                smRender.OpenCameraPosi(x, y, z, &eTrace.eRotMatrix);
            }

            smRender.ClearLight();

            if (DarkLevel > 0) {
                if (StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON) {
                    DarkLightRange = 220 * fONE;
                    ap = DarkLevel * 0.7f;
                }
                else if (StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE) {
                    DarkLightRange = 300 * fONE;
                    ap = DarkLevel * 0.9f;
                }
                else {
                    DarkLightRange = 250 * fONE;
                    ap = DarkLevel * 0.8f;
                }

                if (ConfigUseDynamicLights) {
                    int warmLight = (int)(ap * 0.5f);
                    int warmRed = warmLight;
                    int warmGreen = (int)(warmLight * 0.85f);
                    int warmBlue = (int)(warmLight * 0.7f);

                    int fillLight = (int)(ap * 0.1f);
                    int fillRed = fillLight;
                    int fillGreen = (int)(fillLight * 1.1f);
                    int fillBlue = (int)(fillLight * 1.3f);

                    Graphics::Graphics::GetInstance()->GetRenderer()->PushLight(
                        Graphics::RenderLight{
                            Math::Vector3(lpCurPlayer->pX / 256.0f, (lpCurPlayer->pY / 256.0f) + 48, lpCurPlayer->pZ / 256.0f),
                            (float)DarkLightRange * 0.9f,
                            Math::Color(warmRed, warmGreen, warmBlue, 255)
                        });

                    smRender.Lights.push_back(
                        RenderLight{
                            Math::Vector3(lpCurPlayer->pX / 256.0f, (lpCurPlayer->pY / 256.0f) + 48, lpCurPlayer->pZ / 256.0f),
                            (float)DarkLightRange * 0.9f,
                            Math::Color(warmRed, warmGreen, warmBlue, 255)
                        });

                    smRender.AddDynamicLight(lpCurPlayer->pX, lpCurPlayer->pY + 48 * fONE,
                        lpCurPlayer->pZ, warmRed, warmGreen, warmBlue, 0, DarkLightRange * 0.9f);

                    if (DarkLevel > 30) {
                        Graphics::Graphics::GetInstance()->GetRenderer()->PushLight(
                            Graphics::RenderLight{
                                Math::Vector3(lpCurPlayer->pX / 256.0f, (lpCurPlayer->pY / 256.0f) + 100, lpCurPlayer->pZ / 256.0f),
                                (float)DarkLightRange * 2.5f,
                                Math::Color(fillRed, fillGreen, fillBlue, 180)
                            });

                        smRender.Lights.push_back(
                            RenderLight{
                                Math::Vector3(lpCurPlayer->pX / 256.0f, (lpCurPlayer->pY / 256.0f) + 100, lpCurPlayer->pZ / 256.0f),
                                (float)DarkLightRange * 2.5f,
                                Math::Color(fillRed, fillGreen, fillBlue, 180)
                            });
                    }
                }
            }
            
            ApplyWarmPaletteToRender();  // ← Ativa a atmosfera de horror

            // Base de brilho reduzida para criar o aspecto opaco/escuro
            smRender.Color_R = (int)(BrCtrl * 0.75f);
            smRender.Color_G = (int)(BrCtrl * 0.55f);
            smRender.Color_B = (int)(BrCtrl * 0.90f);
            smRender.Color_A = BrCtrl;

            if (g_fWarmColorIntensity > 0.001f) {
                float f = g_fWarmColorIntensity;

// Boost roxo/lilás
smRender.Color_R += (int)(75 * f);
smRender.Color_G -= (int)(35 * f);  // Tira o verde/amarelado
smRender.Color_B += (int)(105 * f); // Lilás vibrante

                // --- AJUSTE DE OPACIDADE (O toque final de horror) ---
                // Se o brilho for muito alto, nós o "achatamos" para o tom não brilhar, 
                // mantendo-o fosco e pesado.
                if (smRender.Color_R > 180) smRender.Color_R = 180;
                if (smRender.Color_G < 0)   smRender.Color_G = 0;
                if (smRender.Color_B < 0)   smRender.Color_B = 0;

                // Adiciona um leve "noise" visual se quiser (opcional):
                // smRender.Color_R -= (rand() % 5); // Opcional: instabilidade na cor
            }
            
            Graphics::Graphics::GetInstance()->GetRenderer()->RenderShadowMap();

            DX::postProcess.SetEffect(DX::PostProcessEffect::None);

            if ((lpCurPlayer) && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD)
                DX::postProcess.SetEffect(DX::PostProcessEffect::Dead);

            DX::postProcess.Begin();

            DynLightApply();

            DrawSky(x, y, z, ax, ay, az);

            smRender.DeviceRendMode = FALSE;

            // Aplica o nevoeiro do servidor 3 (substitui o fog padrão)
            ApplyFogEffect();

            // Se quiser manter o fog original do jogo, use este bloco condicional:
            // if (!g_bIsServer3) {
            //     if (smRender.m_FogIsRend && smRender.m_FogMode)
            //         GRAPHICDEVICE->SetRenderState(D3DRS_FOGENABLE, TRUE);
            // }


            smRender.bApplyRendObjLight = TRUE;
            DrawPat3D(x, y, z, ax, ay, az);

            smRender.bApplyRendObjLight = FALSE;
            NumPoly = DisplayStage(x, y, z, ax, ay, az);

            smRender.bApplyRendObjLight = TRUE;
            DrawPat3D_Alpha();

            smRender.ClearObjLight();

            if (smRender.m_FogIsRend && smRender.m_FogMode)
                GRAPHICDEVICE->SetRenderState(D3DRS_FOGENABLE, FALSE);

            smRender.ClearLight();
            smRender.Color_A = 0;
            smRender.Color_R = 0;
            smRender.Color_G = 0;
            smRender.Color_B = 0;

            DrawPatShadow(x, y, z, ax, ay, az);

            smRender.DeviceRendMode = TRUE;

            RestoreInterfaceTexture();

            DrawEffect(x, y, z, ax, ay, az);
            cSin3D.Draw(x, y, z, ax, ay, az);
            DrawPat2D(x, y, z, ax, ay, az);

            DX::postProcess.End();

            if ((lpCurPlayer) && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
            {
                DX::cSelectGlow1.Draw();
                DX::cSelectGlow2.Draw();
            }

            DX::postProcess.Draw();

            if ((!MsTraceMode && MouseButton[0] == 0) || lpCurPlayer->smCharInfo.Stamina[0] > (lpCurPlayer->smCharInfo.Stamina[1] >> 2))
            {
                lpCurPlayer->MoveMode = cInterFace.sInterFlags.RunFlag;

                if (ActionGameMode)
                    lpCurPlayer->MoveMode = ActionDashMode;
            }
            else
            {
                if (lpCurPlayer->smCharInfo.Stamina[0] == 0)
                    lpCurPlayer->MoveMode = FALSE;
            }

            smRender.CloseCameraPosi();

            Disp_tx = MsSelPos.x - 32;
            Disp_ty = MsSelPos.y;

            if (g_IsDxProjectZoomIn <= 0)
                DrawGameState();
            else
                VirtualDrawGameState();

            if (bShowFPS)
                showFPS();

            Discord_Handle.Update(lpCurPlayer);
            TitleBox::GetInstance()->Render();
            Graphics::Graphics::GetInstance()->GetRenderer()->End();
        }
    }

    IncTextureFrame();
}

char* CompCmdStr(char* strCmdLine, char* strword)
{
    int len, len2;
    int cnt, cnt2;

    len = lstrlen(strCmdLine);
    len2 = lstrlen(strword);

    for (cnt = 0; cnt < len - len2; cnt++)
    {
        for (cnt2 = 0; cnt2 < len2; cnt2++)
        {
            if (strword[cnt2] != strCmdLine[cnt + cnt2]) break;
        }
        if (cnt2 == len2)
            return &strCmdLine[cnt + cnt2];
    }

    return NULL;
}

int DecodeCmdLine(char* lpCmdLine)
{
    char* lpChar;
    int cnt;

    lpChar = CompCmdStr(lpCmdLine, "/reload=");
    if (lpChar)
    {
        for (cnt = 0; cnt < 16; cnt++)
        {
            if (lpChar[cnt] == ' ' || lpChar[cnt] == '&' || lpChar[cnt] == 0) break;
        }
        if (atoi(lpChar) == 0)
        {
            smSetMeshReload(0, 1);
        }
    }

    return TRUE;
}

char* RegPath_3DMax = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\3D Studio MAX R3.1L";
char* RegPath_3DMax2 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\3D Studio MAX R3.1";
char* RegPath_Photoshop = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Adobe Photoshop 6.0";
char* RegPath_ACDSee = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\ACDSee";

int HaejukReg()
{
    return TRUE;
}

int SetCreateFont()
{
    hFont = CreateFontA(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, NULL, NULL, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial");
    return TRUE;
}

int SetChatingLine(char* szMessage)
{
    cInterFace.ChatFlag = TRUE;
    hFocusWnd = hTextWnd;
    SetWindowText(hFocusWnd, szMessage);
    SetIME_Mode(1);

    return TRUE;
}

DWORD GameWindowMessage(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    int stm, cnt;

    switch (messg)
    {
    case WM_KEYDOWN:
        if (GameMode == 2)
        {
            if (wParam == VK_BACK && VRKeyBuff[wParam] == 0)
            {
                if (HoMsgBoxMode)
                    HoMsgBoxMode = 0;
                else
                    HoMsgBoxMode = 1;

                SetMessageFrameSelect(HoMsgBoxMode);
            }

            if (wParam == 'M' && VRKeyBuff[wParam] == 0 && !NewShop::GetInstance()->openFlag)
            {
                if (StageField[lpCurPlayer->OnStageField]->FieldCode >= 0)
                {
                }
                else
                    sinCheck_ShowHelpMap();
            }

            if (dwYahooTime > dwPlayTime && dwYahooTime < (dwPlayTime + 60 * 1000))
            {
                if (wParam == VK_SPACE && VRKeyBuff[wParam] == 0)
                {
                    if (lpCurPlayer && lpCurPlayer->MotionInfo)
                    {
                        stm = sinGetStamina();
                        cnt = (lpCurPlayer->smCharInfo.Stamina[1] * 3) / 100;
                        if (lpCurPlayer->MotionInfo->State < 0x100 && stm > cnt)
                        {
                            if (lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO))
                            {
                                if (cnt > 0) sinSetStamina(stm - cnt);
                            }
                        }
                    }
                    VRKeyBuff[wParam] = 1;
                    return FALSE;
                }
            }

            if (smRender.m_GameFieldView && !VRKeyBuff[wParam])
            {
                if (wParam == VK_ADD)
                {
                    if (smRender.m_GameFieldViewStep < 22)
                    {
                        smRender.m_GameFieldViewStep++;
                        RendSightSub(1);
                    }
                }
                else if (wParam == VK_SUBTRACT)
                {
                    if (smRender.m_GameFieldViewStep > 1)
                    {
                        smRender.m_GameFieldViewStep--;
                        RendSightSub(1);
                    }
                }
            }

#ifdef _WINMODE_DEBUG
            if (smConfig.DebugMode)
            {
#ifdef GAME_GM
                if (wParam == VK_F9 && VRKeyBuff[VK_F9] == 0)
                {
                    if (DisplayDebug) DisplayDebug = FALSE;
                    else DisplayDebug = TRUE;
                }
#endif

                if (VRKeyBuff[VK_CONTROL] && wParam == 'E' && VRKeyBuff['E'] == 0)
                {
                    lstrcpy(szSOD_String, "Score up 500 pts");
                    bSOD_StringColor[0] = 128;
                    bSOD_StringColor[1] = 255;
                    bSOD_StringColor[2] = 128;
                    SOD_StringCount = 256;
                }

                if (VRKeyBuff[VK_SHIFT] && !VRKeyBuff[VK_CONTROL])
                {
                    if (wParam == VK_F5 && VRKeyBuff[VK_F5] == 0)
                    {
                        SkipNextField = 1;
                    }
                    if (wParam == VK_F6 && VRKeyBuff[VK_F6] == 0)
                    {
                        SkipNextField = 2;
                    }

                    if (wParam == VK_F7 && VRKeyBuff[VK_F7] == 0)
                    {
                        if (smRender.dwMatDispMask)
                            smRender.dwMatDispMask = 0;
                        else
                            smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
                    }

                    if (wParam == VK_F8 && VRKeyBuff[wParam] == 0)
                    {
                        if (ktj_imsiDRAWinfo) ktj_imsiDRAWinfo = 0;
                        else ktj_imsiDRAWinfo = 1;
                    }
                }

                if (wParam == VK_F11 && VRKeyBuff[wParam] == 0)
                {
                    if (DispInterface == 0) DispInterface = TRUE;
                    else DispInterface = FALSE;
                }

                if (AdminCharMode)
                {
                    if (wParam == VK_INSERT && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
                    {
                        SendAdd_Npc(lpCurPlayer, 0);
                    }
                    if (wParam == VK_DELETE && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
                    {
                        if (lpCharSelPlayer)
                        {
                            SendDelete_Npc(lpCharSelPlayer);
                        }
                    }
                }
                else
                {
                    if (wParam == VK_INSERT && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
                    {
                        SendAddStartPoint(lpCurPlayer->pX, lpCurPlayer->pZ);
                    }

                    if (wParam == VK_DELETE && VRKeyBuff[wParam] == 0 && VRKeyBuff[VK_CONTROL])
                    {
                        if (lpSelItem)
                        {
                            SendDeleteStartPoint(lpSelItem->pX, lpSelItem->pZ);
                        }
                    }
                }
            }
#endif
        }
        break;
    }

    return TRUE;
}

#include "sinbaram\\HaQuestBoard.h"

int StartQuest_Code(DWORD wCode)
{
    SetQuestBoard();

    if (InterfaceParty.PartyPosState == PARTY_NONE)
    {
        ShowQuest();
        InterfaceParty.quest_Sel_Progress();
    }

    return TRUE;
}

int EndQuest_Code(DWORD wCode)
{
    Record_LastQuest((WORD)wCode);
    SetQuestBoard();

    return TRUE;
}

int HoInstallFont()
{
#ifdef _LANGUAGE_ENGLISH
    AddFontResource("ptz.ttf");
#endif

#ifdef _LANGUAGE_THAI
    AddFontResource("ssee874.fon");
#endif

    OSVERSIONINFO vi;
    vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    char szKey[255];
    GetVersionEx(&vi);
    if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
        strcpy(szKey, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");
    else
        strcpy(szKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Fonts");

#ifdef _LANGUAGE_ENGLISH
    SetRegString(HKEY_LOCAL_MACHINE, szKey, "ptz", "ptz.ttf");
#endif
#ifdef _LANGUAGE_THAI
    SetRegString(HKEY_LOCAL_MACHINE, szKey, "MS Sans Serif", "ssee874.fon");
#endif

    return TRUE;
}

int HoUninstallFont()
{
#ifdef _LANGUAGE_ENGLISH
    RemoveFontResource("ptz.ttf");
#endif
#ifdef _LANGUAGE_THAI
    RemoveFontResource("ssee874.fon");
#endif

    OSVERSIONINFO vi;
    vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    char szKey[255];
    GetVersionEx(&vi);
    if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
        strcpy(szKey, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");
    else
        strcpy(szKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Fonts");
    HKEY key;
    DWORD dwDisp;
    RegCreateKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp);

#ifdef _LANGUAGE_ENGLISH
    RegDeleteValue(key, "ptz");
#endif
#ifdef _LANGUAGE_THAI
    RegDeleteValue(key, "MS Sans Serif");
#endif

    RegCloseKey(key);

    return TRUE;
}

