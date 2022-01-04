#include "pch.h"
#include "bbtextlist.h"
#include "lanternapi.h"

#include "Blaze.h"

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");
NJS_MATERIAL* TemporaryMaterialArray[] = { nullptr };

int BurningBlazeFlames[] = { 12, 80, 81, 82, 83, 84, 85, 86, 87 }; //Textures IDs

void __cdecl Sonic_Main_r(ObjectMaster* obj);
Trampoline Sonic_Main_t((int)Sonic_Main, (int)Sonic_Main + 0x7, Sonic_Main_r);
void __cdecl Sonic_Main_r(ObjectMaster* obj) {
	// Prevent Sonic's cinematic head from appearing
	SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling = SONIC_OBJECTS[46];

	NonStaticFunctionPointer(void, original, (ObjectMaster * obj), Sonic_Main_t.Target());
	original(obj);
};

//Light Dash Aura for DX, colors in Alpha, Red, Green, Blue
void __cdecl SetLSDColor()
{
	SetMaterialAndSpriteColor_Float(0.8f, 0.7f, 0.15f, 0.04f);
}

//Light Dash Aura for DC conversion
void __cdecl Sonic_DisplayLightDashModel_mod(EntityData1* data1, CharObj2** data2_pp, CharObj2* data2)
{
	int v3; // eax
	__int16 v4; // t1
	float v5; // st7
	float basedepth = 8000.0f;
	NJS_ACTION v8; // [esp+4h] [ebp-18h]
	NJS_OBJECT** ___SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(GetModuleHandle(L"CHRMODELS_orig"), "___SONIC_OBJECTS");
	if (!MissedFrames)
	{
		v3 = (unsigned __int16)data2->AnimationThing.Index;
		v8.object = ___SONIC_OBJECTS[54];
		if (data2->AnimationThing.State == 2)
		{
			v4 = data2->AnimationThing.LastIndex;
			v8.motion = data2->AnimationThing.action->motion;
		}
		else
		{
			v8.motion = data2->AnimationThing.AnimData[v3].Animation->motion;
		}
		v5 = (float)(FrameCounterUnpaused & 0x7F);
		if (v5 >= 64.0f)
		{
			v5 = 128.0f - v5;
		}
		//v5 = 0;
		njPushMatrixEx();
		njControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL | NJD_CONTROL_3D_ENABLE_ALPHA | NJD_CONTROL_3D_CONSTANT_ATTR);
		njColorBlendingMode(0, NJD_COLOR_BLENDING_ONE);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);
		// Main
		SetMaterialAndSpriteColor_Float(1.0f, 0.7, 0.15f + (64.0f - v5) / 880.0f, 0.04f);
		DrawQueueDepthBias = basedepth;
		late_ActionMesh(&v8, data2->AnimationThing.Frame, 0);
		// Outer 1
		njScale(0, 1.05f, 1.05f, 1.05f);
		SetMaterialAndSpriteColor_Float(1.0f, 0.7f, (64.0f - v5) / 1050.0f, 0.04f);
		DrawQueueDepthBias = basedepth + 300.0f;
		late_ActionMesh(&v8, data2->AnimationThing.Frame, 0);
		// Outer 2
		njScale(0, 1.05f, 1.05f, 1.05f);
		SetMaterialAndSpriteColor_Float(1.0f, 0.05f, (64.0f - v5) / 2000.0f, 0.01f);
		DrawQueueDepthBias = basedepth + 600.0f;
		late_ActionMesh(&v8, data2->AnimationThing.Frame, 0);
		njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
		njPopMatrixEx();
		DrawQueueDepthBias = 0;
	}
}

Trampoline* LoadRegObjTextures_b = nullptr;
Trampoline* FreeRegObjTexlists_b = nullptr;

static NJS_TEXNAME BlazeGUI_TEXNAME[2] = {};
static NJS_TEXLIST BlazeGUI_TEXLIST = { arrayptrandlengthT(BlazeGUI_TEXNAME, int) };

static void __cdecl LoadRegObjTextures_r(int a1)
{
	LoadPVM("BlazeGUI", &BlazeGUI_TEXLIST);
	((decltype(LoadRegObjTextures_r)*)LoadRegObjTextures_b->Target())(a1);
}

static void __cdecl FreeRegObjTexlists_r()
{
	njReleaseTexture(&BlazeGUI_TEXLIST);
	((decltype(FreeRegObjTexlists_r)*)FreeRegObjTexlists_b->Target())();
}

void BlazeGUI_Init()
{
	LoadRegObjTextures_b = new Trampoline(0x4212E0, 0x4212E5, LoadRegObjTextures_r, false);
	FreeRegObjTexlists_b = new Trampoline(0x420F40, 0x420F45, FreeRegObjTexlists_r, false);
}

uint16_t Blaze_UpperArmIndices_DC[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

uint16_t Blaze_LowerArmIndices_DC[] = {
	4, 6,
	5, 7,
	1, 3,
	0, 2,
};

uint16_t Blaze_KneeIndices_DC[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

uint16_t Blaze_LegIndices_DC[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

uint16_t Blaze_ShoeIndices_DC[] = {
	2, 3,
	12, 8,
	0, 1,
	1, 0,
	17, 13,
	3, 2,
};

uint16_t Blaze_HandIndices_DC[] = {
	0, 14,
	1, 13,
	5, 12,
	4, 15,
};

void InitSonicWeldInfo_DC();
Trampoline InitSonicWeldInfo_t((int)InitSonicWeldInfo, (int)InitSonicWeldInfo + 0x5, InitSonicWeldInfo_DC);
void InitSonicWeldInfo_DC() {
	VoidFunc(original, InitSonicWeldInfo_t.Target());
	original(); // For Metal Sonic compatibility with other mods

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_UpperArmIndices_DC) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Blaze_UpperArmIndices_DC;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LowerArmIndices_DC) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Blaze_LowerArmIndices_DC;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_UpperArmIndices_DC) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Blaze_UpperArmIndices_DC;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Blaze_LowerArmIndices_DC;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LowerArmIndices_DC) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_KneeIndices_DC) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Blaze_KneeIndices_DC;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LegIndices_DC) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Blaze_LegIndices_DC;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Blaze_KneeIndices_DC;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_KneeIndices_DC) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LegIndices_DC) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Blaze_LegIndices_DC;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_ShoeIndices_DC) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Blaze_ShoeIndices_DC;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Blaze_ShoeIndices_DC;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_ShoeIndices_DC) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_HandIndices_DC) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Blaze_HandIndices_DC;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_HandIndices_DC) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Blaze_HandIndices_DC;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_ShoeIndices_DC) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Blaze_ShoeIndices_DC;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_ShoeIndices_DC) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Blaze_ShoeIndices_DC;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LowerArmIndices_DC) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Blaze_LowerArmIndices_DC;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_UpperArmIndices_DC) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Blaze_UpperArmIndices_DC;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LowerArmIndices_DC) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Blaze_LowerArmIndices_DC;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_UpperArmIndices_DC) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Blaze_UpperArmIndices_DC;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LowerArmIndices_DC) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Blaze_LowerArmIndices_DC;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_KneeIndices_DC) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Blaze_KneeIndices_DC;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LegIndices_DC) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = Blaze_LegIndices_DC;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Blaze_KneeIndices_DC;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_KneeIndices_DC) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_LegIndices_DC) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = Blaze_LegIndices_DC;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_ShoeIndices_DC) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = Blaze_ShoeIndices_DC;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_ShoeIndices_DC) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = Blaze_ShoeIndices_DC;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_HandIndices_DC) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Blaze_HandIndices_DC;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Blaze_HandIndices_DC;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_HandIndices_DC) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_HandIndices_DC) / 2);
	SonicWeldInfo[34].VertIndexes = Blaze_HandIndices_DC;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Blaze_HandIndices_DC;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Blaze_HandIndices_DC) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void __cdecl InitNPCSonicWeldInfo_mod()
{
	NJS_OBJECT* v0; // ebp
	NJS_OBJECT* v1; // ebp
	NJS_OBJECT* v2; // ebp
	NJS_OBJECT* v3; // ebp
	NJS_OBJECT* v4; // eax

	NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[0].anonymous_5 = 0;
	NPCSonicWeldInfo[0].VertexBuffer = 0;
	NPCSonicWeldInfo[0].VertIndexes = Blaze_UpperArmIndices_DC;
	NPCSonicWeldInfo[0].WeldType = 2;
	NPCSonicWeldInfo[0].VertexPairCount = 4;
	NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	NPCSonicWeldInfo[1].VertexPairCount = 4;
	NPCSonicWeldInfo[1].WeldType = 2;
	NPCSonicWeldInfo[1].anonymous_5 = 0;
	NPCSonicWeldInfo[1].VertexBuffer = 0;
	NPCSonicWeldInfo[1].VertIndexes = (unsigned __int16*)&Blaze_LowerArmIndices_DC;
	NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	NPCSonicWeldInfo[2].VertexPairCount = 4;
	NPCSonicWeldInfo[2].WeldType = 2;
	NPCSonicWeldInfo[2].anonymous_5 = 0;
	NPCSonicWeldInfo[2].VertexBuffer = 0;
	NPCSonicWeldInfo[2].VertIndexes = Blaze_UpperArmIndices_DC;
	NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	NPCSonicWeldInfo[3].VertIndexes = (unsigned __int16*)&Blaze_LowerArmIndices_DC;
	NPCSonicWeldInfo[3].ModelB = v0;
	NPCSonicWeldInfo[3].VertexPairCount = 4;
	NPCSonicWeldInfo[3].WeldType = 2;
	NPCSonicWeldInfo[3].anonymous_5 = 0;
	NPCSonicWeldInfo[3].VertexBuffer = 0;
	NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[4].VertexPairCount = 4;
	NPCSonicWeldInfo[4].WeldType = 2;
	NPCSonicWeldInfo[4].anonymous_5 = 0;
	NPCSonicWeldInfo[4].VertexBuffer = 0;
	NPCSonicWeldInfo[4].VertIndexes = (unsigned __int16*)Blaze_KneeIndices_DC;
	NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	NPCSonicWeldInfo[5].VertexPairCount = 4;
	NPCSonicWeldInfo[5].WeldType = 2;
	NPCSonicWeldInfo[5].anonymous_5 = 0;
	NPCSonicWeldInfo[5].VertexBuffer = 0;
	NPCSonicWeldInfo[5].VertIndexes = (unsigned __int16*)Blaze_LegIndices_DC;
	NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	NPCSonicWeldInfo[6].VertexPairCount = 4;
	NPCSonicWeldInfo[6].WeldType = 2;
	NPCSonicWeldInfo[6].anonymous_5 = 0;
	NPCSonicWeldInfo[6].VertexBuffer = 0;
	NPCSonicWeldInfo[6].VertIndexes = (unsigned __int16*)Blaze_KneeIndices_DC;
	NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	v1 = SONIC_OBJECTS[19];
	NPCSonicWeldInfo[7].VertIndexes = (unsigned __int16*)Blaze_LegIndices_DC;
	NPCSonicWeldInfo[7].ModelB = v1;
	NPCSonicWeldInfo[7].VertexPairCount = 4;
	NPCSonicWeldInfo[7].WeldType = 2;
	NPCSonicWeldInfo[7].anonymous_5 = 0;
	NPCSonicWeldInfo[7].VertexBuffer = 0;
	NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	NPCSonicWeldInfo[8].VertexPairCount = 11;
	NPCSonicWeldInfo[8].WeldType = 2;
	NPCSonicWeldInfo[8].anonymous_5 = 0;
	NPCSonicWeldInfo[8].VertexBuffer = 0;
	NPCSonicWeldInfo[8].VertIndexes = (unsigned __int16*)Blaze_ShoeIndices_DC;
	NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	NPCSonicWeldInfo[9].VertIndexes = (unsigned __int16*)Blaze_ShoeIndices_DC;
	NPCSonicWeldInfo[9].ModelB = v2;
	NPCSonicWeldInfo[9].VertexPairCount = 11;
	NPCSonicWeldInfo[9].WeldType = 2;
	NPCSonicWeldInfo[9].anonymous_5 = 0;
	NPCSonicWeldInfo[9].VertexBuffer = 0;
	NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	NPCSonicWeldInfo[10].VertexPairCount = 7;
	NPCSonicWeldInfo[10].WeldType = 2;
	NPCSonicWeldInfo[10].anonymous_5 = 0;
	NPCSonicWeldInfo[10].VertexBuffer = 0;
	NPCSonicWeldInfo[10].VertIndexes = (unsigned __int16*)Blaze_HandIndices_DC;
	NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	NPCSonicWeldInfo[11].VertexPairCount = 7;
	NPCSonicWeldInfo[11].WeldType = 2;
	NPCSonicWeldInfo[11].anonymous_5 = 0;
	NPCSonicWeldInfo[11].VertexBuffer = 0;
	NPCSonicWeldInfo[11].VertIndexes = (unsigned __int16*)Blaze_HandIndices_DC;
	NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	NPCSonicWeldInfo[12].VertexPairCount = 9;
	NPCSonicWeldInfo[12].anonymous_5 = 0;
	NPCSonicWeldInfo[12].VertexBuffer = 0;
	NPCSonicWeldInfo[12].WeldType = 2;
	NPCSonicWeldInfo[12].VertIndexes = (unsigned __int16*)Blaze_ShoeIndices_DC;
	NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	v3 = SONIC_OBJECTS[61];
	NPCSonicWeldInfo[13].anonymous_5 = 0;
	NPCSonicWeldInfo[13].VertexBuffer = 0;
	NPCSonicWeldInfo[13].ModelB = v3;
	NPCSonicWeldInfo[13].VertIndexes = (unsigned __int16*)Blaze_ShoeIndices_DC;
	NPCSonicWeldInfo[13].VertexPairCount = 9;
	NPCSonicWeldInfo[13].WeldType = 2;
	NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	v4 = SONIC_OBJECTS[63];
	NPCSonicWeldInfo[14].anonymous_5 = 0;
	NPCSonicWeldInfo[14].VertexBuffer = 0;
	NPCSonicWeldInfo[15].BaseModel = 0;
	NPCSonicWeldInfo[15].ModelA = 0;
	NPCSonicWeldInfo[15].ModelB = 0;
	*(_DWORD*)&NPCSonicWeldInfo[15].VertexPairCount = 0;
	NPCSonicWeldInfo[15].VertexBuffer = 0;
	NPCSonicWeldInfo[14].VertexPairCount = 4;
	NPCSonicWeldInfo[14].ModelB = v4;
	NPCSonicWeldInfo[14].WeldType = 2;
	NPCSonicWeldInfo[14].VertIndexes = Blaze_UpperArmIndices_DC;
	NPCSonicWeldInfo[15].VertIndexes = 0;
}

void Init_Blaze()
{
	SONIC_OBJECTS[0] = &object_0056AF50;
	SONIC_OBJECTS[1] = &object_00563B7C;
	SONIC_OBJECTS[2] = &object_00563D0C;
	SONIC_OBJECTS[3] = &object_005654EC;
	SONIC_OBJECTS[4] = &object_00564CD0;
	SONIC_OBJECTS[5] = &object_005647B8;
	SONIC_OBJECTS[6] = &object_00564A78;
	SONIC_OBJECTS[7] = &object_00561F14;
	SONIC_OBJECTS[8] = &object_005620A4;
	SONIC_OBJECTS[9] = &object_005638CC;
	SONIC_OBJECTS[10] = &object_005630B0;
	SONIC_OBJECTS[11] = &object_00562B80;
	SONIC_OBJECTS[12] = &object_0056044C;
	SONIC_OBJECTS[13] = &object_005605DC;
	SONIC_OBJECTS[14] = &object_00561C68;
	SONIC_OBJECTS[15] = &object_005613F8;
	SONIC_OBJECTS[16] = &object_00560DD0;
	SONIC_OBJECTS[17] = &object_0055E99C;
	SONIC_OBJECTS[18] = &object_0055EB2C;
	SONIC_OBJECTS[19] = &object_005601B8;
	SONIC_OBJECTS[20] = &object_0055F948;
	SONIC_OBJECTS[21] = &object_0055F330;
	SONIC_OBJECTS[22] = &object_0062DE88;
	SONIC_OBJECTS[23] = &object_00626AB4;
	SONIC_OBJECTS[24] = &object_00626C44;
	SONIC_OBJECTS[25] = &object_0062840C;
	SONIC_OBJECTS[26] = &object_00627BF0;
	SONIC_OBJECTS[27] = &object_006276D8;
	SONIC_OBJECTS[28] = &object_00624E3C;
	SONIC_OBJECTS[29] = &object_00624FCC;
	SONIC_OBJECTS[30] = &object_006267F4;
	SONIC_OBJECTS[31] = &object_00625FD8;
	SONIC_OBJECTS[32] = &object_00625AA8;
	SONIC_OBJECTS[33] = &object_00623474;
	SONIC_OBJECTS[34] = &object_00623604;
	SONIC_OBJECTS[35] = &object_00624B78;
	SONIC_OBJECTS[36] = &object_00624308;
	SONIC_OBJECTS[37] = &object_00623C14;
	SONIC_OBJECTS[38] = &object_00621AC4;
	SONIC_OBJECTS[39] = &object_00621C54;
	SONIC_OBJECTS[40] = &object_006231E0;
	SONIC_OBJECTS[41] = &object_00622970;
	SONIC_OBJECTS[42] = &object_00622254;
	SONIC_OBJECTS[44] = &object_0057BC44;
	SONIC_OBJECTS[45] = &object_0056998C;
	SONIC_OBJECTS[46] = &object_00569594;
	SONIC_OBJECTS[48] = &object_00569DEC;
	SONIC_OBJECTS[49] = &object_00569594;
	SONIC_OBJECTS[50] = &object_00569E20;
	SONIC_OBJECTS[51] = &object_00569CE8;
	SONIC_OBJECTS[52] = &object_005698F0;
	SONIC_OBJECTS[54] = &object_006837E8;
	SONIC_OBJECTS[55] = &object_00682EF4;
	SONIC_OBJECTS[56] = &object_0061B4DC;
	SONIC_OBJECTS[57] = &object_0061AA94;
	SONIC_OBJECTS[58] = &object_00581FB8;
	SONIC_OBJECTS[59] = &object_005818AC;
	SONIC_OBJECTS[60] = &object_00582CC0;
	SONIC_OBJECTS[61] = &object_005825A4;
	SONIC_OBJECTS[62] = &object_00565520;
	SONIC_OBJECTS[63] = &object_00583284;
	SONIC_OBJECTS[65] = &object_00585EB4;
	SONIC_OBJECTS[66] = &object_005729CC;
	SONIC_OBJECTS[67] = &object_0057BC44;
	SONIC_ACTIONS[0]->object = &object_0056AF50;
	SONIC_ACTIONS[1]->object = &object_0056AF50;
	SONIC_ACTIONS[2]->object = &object_0056AF50;
	SONIC_ACTIONS[3]->object = &object_0056AF50;
	SONIC_ACTIONS[4]->object = &object_0056AF50;
	SONIC_ACTIONS[5]->object = &object_0056AF50;
	SONIC_ACTIONS[6]->object = &object_0056AF50;
	SONIC_ACTIONS[7]->object = &object_0056AF50;
	SONIC_ACTIONS[8]->object = &object_0056AF50;
	SONIC_ACTIONS[9]->object = &object_0056AF50;
	SONIC_ACTIONS[10]->object = &object_0056AF50;
	SONIC_ACTIONS[11]->object = &object_0056AF50;
	SONIC_ACTIONS[12]->object = &object_0056AF50;
	SONIC_ACTIONS[13]->object = &object_0056AF50;
	SONIC_ACTIONS[14]->motion = &___SONIC_ACTIONS_14;
	SONIC_ACTIONS[14]->object = &object_005729CC;
	SONIC_ACTIONS[15]->object = &object_0056AF50;
	SONIC_ACTIONS[16]->object = &object_0056AF50;
	SONIC_ACTIONS[17]->object = &object_0056AF50;
	SONIC_ACTIONS[18]->object = &object_0056AF50;
	SONIC_ACTIONS[19]->object = &object_0056AF50;
	SONIC_ACTIONS[20]->object = &object_0056AF50;
	SONIC_ACTIONS[21]->motion = &___SONIC_ACTIONS_21;
	SONIC_ACTIONS[21]->object = &object_0057BC44;
	SONIC_ACTIONS[22]->object = &object_0056AF50;
	SONIC_ACTIONS[23]->object = &object_0056AF50;
	SONIC_ACTIONS[27]->object = &object_0056AF50;
	SONIC_ACTIONS[28]->object = &object_0056AF50;
	SONIC_ACTIONS[29]->object = &object_0056AF50;
	SONIC_ACTIONS[30]->object = &object_0056AF50;
	SONIC_ACTIONS[31]->object = &object_0056AF50;
	SONIC_ACTIONS[32]->object = &object_0056AF50;
	SONIC_ACTIONS[33]->object = &object_0056AF50;
	SONIC_ACTIONS[34]->object = &object_0056AF50;
	SONIC_ACTIONS[35]->object = &object_0056AF50;
	SONIC_ACTIONS[36]->object = &object_0056AF50;
	SONIC_ACTIONS[37]->object = &object_0056AF50;
	SONIC_ACTIONS[38]->object = &object_0056AF50;
	SONIC_ACTIONS[39]->object = &object_0056AF50;
	SONIC_ACTIONS[40]->object = &object_0056AF50;
	SONIC_ACTIONS[41]->object = &object_0056AF50;
	SONIC_ACTIONS[42]->object = &object_0056AF50;
	SONIC_ACTIONS[43]->object = &object_0056AF50;
	SONIC_ACTIONS[44]->object = &object_0056AF50;
	SONIC_ACTIONS[45]->object = &object_0056AF50;
	SONIC_ACTIONS[46]->object = &object_0056AF50;
	SONIC_ACTIONS[47]->object = &object_0056AF50;
	SONIC_ACTIONS[48]->object = &object_0056AF50;
	SONIC_ACTIONS[49]->object = &object_0056AF50;
	SONIC_ACTIONS[50]->object = &object_0056AF50;
	SONIC_ACTIONS[51]->object = &object_0056AF50;
	SONIC_ACTIONS[52]->object = &object_0056AF50;
	SONIC_ACTIONS[53]->object = &object_0056AF50;
	SONIC_ACTIONS[54]->object = &object_0056AF50;
	SONIC_ACTIONS[55]->object = &object_0056AF50;
	SONIC_ACTIONS[56]->object = &object_0056AF50;
	SONIC_ACTIONS[57]->object = &object_0056AF50;
	SONIC_ACTIONS[58]->object = &object_0056AF50;
	SONIC_ACTIONS[59]->object = &object_0056AF50;
	SONIC_ACTIONS[60]->object = &object_0056AF50;
	SONIC_ACTIONS[61]->object = &object_0056AF50;
	SONIC_ACTIONS[62]->object = &object_0056AF50;
	SONIC_ACTIONS[63]->object = &object_0056AF50;
	SONIC_ACTIONS[64]->object = &object_0056AF50;
	SONIC_ACTIONS[65]->object = &object_0056AF50;
	SONIC_ACTIONS[66]->object = &object_0056AF50;
	SONIC_ACTIONS[67]->object = &object_0056AF50;
	SONIC_ACTIONS[68]->object = &object_0056AF50;
	SONIC_ACTIONS[69]->object = &object_0056AF50;
	SONIC_ACTIONS[70]->object = &object_0056AF50;
	SONIC_ACTIONS[71]->object = &object_0056AF50;
	SONIC_ACTIONS[72]->object = &object_0056AF50;
	SONIC_ACTIONS[87]->object = &object_0056AF50;
	SONIC_ACTIONS[88]->object = &object_0056AF50;
	SONIC_ACTIONS[89]->object = &object_0056AF50;
	SONIC_ACTIONS[90]->object = &object_0056AF50;
	SONIC_ACTIONS[91]->object = &object_0056AF50;
	SONIC_ACTIONS[92]->object = &object_0056AF50;
	SONIC_ACTIONS[93]->object = &object_0056AF50;
	SONIC_ACTIONS[94]->object = &object_0056AF50;
	SONIC_ACTIONS[95]->object = &object_0056AF50;
	SONIC_ACTIONS[96]->object = &object_0056AF50;
	SONIC_ACTIONS[97]->object = &object_0056AF50;
	SONIC_ACTIONS[98]->object = &object_0056AF50;
	SONIC_ACTIONS[99]->object = &object_0056AF50;
	SONIC_ACTIONS[100]->object = &object_0056AF50;
	SONIC_ACTIONS[101]->object = &object_0056AF50;
	SONIC_ACTIONS[102]->object = &object_0056AF50;
	SONIC_ACTIONS[103]->object = &object_0056AF50;
	SONIC_ACTIONS[104]->object = &object_0056AF50;
	SONIC_ACTIONS[105]->object = &object_0056AF50;
	SONIC_ACTIONS[106]->object = &object_0056AF50;
	SONIC_ACTIONS[107]->object = &object_0056AF50;
	SONIC_ACTIONS[108]->object = &object_0056AF50;
	SONIC_ACTIONS[109]->object = &object_0056AF50;
	SONIC_ACTIONS[113]->object = &object_0056AF50;
	SONIC_ACTIONS[114]->object = &object_0056AF50;
	SONIC_ACTIONS[115]->object = &object_0056AF50;
	SONIC_ACTIONS[116]->object = &object_0056AF50;
	SONIC_ACTIONS[117]->object = &object_0056AF50;
	SONIC_ACTIONS[118]->object = &object_0056AF50;
	SONIC_ACTIONS[119]->object = &object_0056AF50;
	SONIC_ACTIONS[120]->object = &object_0056AF50;
	SONIC_ACTIONS[121]->object = &object_0056AF50;
	SONIC_ACTIONS[122]->object = &object_0056AF50;
	SONIC_ACTIONS[123]->object = &object_0056AF50;
	SONIC_ACTIONS[124]->object = &object_0056AF50;
	SONIC_ACTIONS[125]->object = &object_0056AF50;
	SONIC_ACTIONS[126]->object = &object_0056AF50;
	SONIC_ACTIONS[127]->object = &object_0056AF50;
	SONIC_ACTIONS[128]->object = &object_0056AF50;
	SONIC_ACTIONS[129]->object = &object_0056AF50;
	SONIC_ACTIONS[130]->object = &object_0062DE88;
	SONIC_ACTIONS[131]->object = &object_0062DE88;
	SONIC_ACTIONS[132]->object = &object_0062DE88;
	SONIC_ACTIONS[133]->object = &object_0062DE88;
	SONIC_ACTIONS[134]->object = &object_0056AF50;
	SONIC_ACTIONS[135]->object = &object_0056AF50;
	SONIC_ACTIONS[136]->object = &object_0056AF50;
	SONIC_ACTIONS[137]->object = &object_0056AF50;
	SONIC_ACTIONS[138]->object = &object_0062DE88;
	SONIC_ACTIONS[139]->object = &object_0062DE88;
	SONIC_ACTIONS[140]->object = &object_0062DE88;
	SONIC_ACTIONS[141]->object = &object_0062DE88;
	SONIC_ACTIONS[142]->motion = &___SONIC_ACTIONS_21;
	SONIC_ACTIONS[142]->object = &object_0062FE6C;
	SONIC_ACTIONS[143]->object = &object_0062DE88;
	SONIC_ACTIONS[144]->object = &object_0062DE88;
	SONIC_ACTIONS[145]->object = &object_0056AF50;
	SONIC_ACTIONS[146]->object = &object_0056AF50;
	SONIC_ACTIONS[147]->object = &object_0056AF50;
	SONIC_ACTIONS[148]->object = &object_0056AF50;
	SONIC_MODELS[0] = &attach_0055F304;
	SONIC_MODELS[1] = &attach_00560DA4;
	SONIC_MODELS[8] = &attach_00569568;
	SONIC_MODELS[9] = &attach_00579C68;
	SONIC_MOTIONS[2] = &___SONIC_ACTIONS_21;
	WriteData((NJS_OBJECT**)0x00664C3E, &object_029D8708);
	WriteData((NJS_OBJECT**)0x0069E24B, &object_029D8708);
	WriteData((NJS_OBJECT**)0x006D010C, &object_029D8708);
	WriteData((NJS_OBJECT**)0x006D711E, &object_029D8708);
	WriteData((NJS_TEXLIST**)0x55E65C, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E751, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E712, SSAura02);
	WriteData((NJS_TEXLIST**)0x55E7CD, SSWaterThing);
	WriteData((NJS_TEXLIST**)0x55F2B3, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1D1, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1DC, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F2BE, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F677, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F669, SSHomingTex3);
	SUPERSONIC_TEXLIST = SS_PVM;
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_DC);
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_mod);
}

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		HMODULE handle = GetModuleHandle(L"CHRMODELS_orig");
		NJS_OBJECT** ___SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___SONIC_OBJECTS");
		NJS_ACTION** ___SONIC_ACTIONS = (NJS_ACTION**)GetProcAddress(handle, "___SONIC_ACTIONS");
		NJS_MODEL_SADX** ___SONIC_MODELS = (NJS_MODEL_SADX**)GetProcAddress(handle, "___SONIC_MODELS");
		NJS_MOTION** ___SONIC_MOTIONS = (NJS_MOTION**)GetProcAddress(handle, "___SONIC_MOTIONS");
		Init_Blaze();
		___SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling = ___SONIC_OBJECTS[46];
		BlazeGUI_Init();
		WriteCall((void*)0x4A1705, SetLSDColor);
		WriteJump((void*)0x4A1630, Sonic_DisplayLightDashModel_mod);
		//Replace textures
		ReplacePVM("sonic", "Blaze");
		ReplacePVM("supersonic", "BurningBlaze");
		ReplacePVM("son_eff", "blz_eff");
		ReplacePVM("hypersonic", "HBurningBlaze");
		ReplacePVM("hypersonic_dc", "HBurningBlaze");
		ReplacePVM("hypersonic_g_dc", "HBurningBlaze");
		ReplacePVM("hypersonic_v_dc", "HBurningBlaze");
		ReplacePVM("hypersonic_v_p_dc", "HBurningBlaze");
		ReplacePVM("SUPERSONIC_EXTRA", "BurningBlazeGUI");
	}

	__declspec(dllexport) void __cdecl OnFrame() {
		//(FrameCounter / 3) =Speed     //% 16] = Number of textures
		material_8D9CA5A7EEFBD30DA3B[0].attr_texId = BurningBlazeFlames[(FrameCounter / 3) % 9];
		material_8D9CA5A8500DE8EA770[0].attr_texId = BurningBlazeFlames[(FrameCounter / 3) % 9];
		material_8D9CA5A8EB915BA2A8E[1].attr_texId = BurningBlazeFlames[(FrameCounter / 3) % 9];
		material_8D9CA5A94005C1216FA[1].attr_texId = BurningBlazeFlames[(FrameCounter / 3) % 9];
	}
}

extern "C" __declspec(dllexport) const ModInfo SADXModInfo = { ModLoaderVer };