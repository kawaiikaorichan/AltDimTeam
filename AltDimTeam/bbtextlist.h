DataArray(NJS_TEXLIST, SSArua01, 0x01422160, 8); //0xC0
DataArray(NJS_TEXLIST, SSArua02, 0x014221A0, 8); //0x120
DataArray(NJS_TEXLIST, SSSplash, 0x014221E0, 8); //0x180
DataArray(NJS_TEXLIST, SSHoming, 0x01422228, 49); //0x24C

NJS_TEXNAME BurningBlazeTexName[] = {
	{ (void*)"blazefur" },
	{ (void*)"s_hando2" },
	{ (void*)"s_testhand" },
	{ (void*)"alltx_dwhite" },
	{ (void*)"blazeeye" },
	{ (void*)"blazefur2" },
	{ (void*)"blazetail" },
	{ (void*)"stx_hanasaki" },
	{ (void*)"blazecoat" },
	{ (void*)"blazecoat2" },
	{ (void*)"blazecoat3" },
	{ (void*)"blazecoat4" },
	{ (void*)"coatflames" },
	{ (void*)"jewel" },
	{ (void*)"atx_kutuzoko0" },
	{ (void*)"atx_kutuzoko1" },
	{ (void*)"s1sonic01" }, //16th entry (0x0C0)
	{ (void*)"s1sonic02" },
	{ (void*)"s1sonic03" },
	{ (void*)"s1sonic04" },
	{ (void*)"s1sonic05" },
	{ (void*)"s1sonic06" },
	{ (void*)"s1sonic07" },
	{ (void*)"s1sonic08" },
	{ (void*)"s2sonic01" }, //24th entry (0x120)
	{ (void*)"s2sonic02" },
	{ (void*)"s2sonic03" },
	{ (void*)"s2sonic04" },
	{ (void*)"s2sonic05" },
	{ (void*)"s2sonic06" },
	{ (void*)"s2sonic07" },
	{ (void*)"s2sonic08" },
	{ (void*)"ss_waterl01" }, //32nd entry (0x180)
	{ (void*)"ss_waterl02" },
	{ (void*)"ss_waterl03" },
	{ (void*)"ss_waterl04" },
	{ (void*)"ss_waterl05" },
	{ (void*)"ss_waterl06" },
	{ (void*)"ss_waterl07" },
	{ (void*)"ss_waterl08" },
	{ (void*)"ss_waterl09" },
	{ (void*)"ss_waterl10" },
	{ (void*)"ss_waterl11" },
	{ (void*)"ss_waterl12" },
	{ (void*)"ss_waterl13" },
	{ (void*)"ss_waterl14" },
	{ (void*)"ss_waterl15" },
	{ (void*)"ss_waterl16" },
	{ (void*)"ss_ball_a" },
	{ (void*)"ss_ball_b" }, //49th entry (0x24C)
	{ (void*)"ss_dash01" }, //50 0x258
	{ (void*)"ss_dash02" }, //51 0x264
	{ (void*)"ss_dash03" }, //52 0x270
	{ (void*)"ss_dash04" }, //53 0x27C
	{ (void*)"ss_dash05" }, //54 0x288
	{ (void*)"ss_dash06" }, //55 0x294
	{ (void*)"ss_dash07" }, //56 0x2A0
	{ (void*)"ss_dash08" }, //57 0x2AC
	{ (void*)"ss_dash09" }, //58 0x2B8
	{ (void*)"ss_dash10" }, //59 0x2C4
	{ (void*)"ss_dash11" }, //60 0x2D0
	{ (void*)"ss_dash12" }, //61 0x2DC
	{ (void*)"ss_dash13" }, //62 0x2E8
	{ (void*)"ss_dash14" }, //63 0x2F4
	{ (void*)"ss_dash15" }, //64 0x300
	{ (void*)"ss_dash16" }, //65 0x30C
	{ (void*)"ss_dash17" }, //66 0x318
	{ (void*)"ss_dash18" }, //67 0x324
	{ (void*)"ss_dash19" }, //68 0x330
	{ (void*)"ss_dash20" }, //69 0x33C
	{ (void*)"ss_dash21" }, //70 0x348
	{ (void*)"ss_dash22" }, //71 0x354
	{ (void*)"ss_dash23" }, //72 0x360
	{ (void*)"bblazespin" },
	{ (void*)"btx_shoose6" },
	{ (void*)"btx_shoose6" },
	{ (void*)"mtx_kuchinaka0" },
	{ (void*)"mtx_kuchinaka1" },
	{ (void*)"btx_hada" },
	{ (void*)"bblazespin2" },
	{ (void*)"coatflames2" },
	{ (void*)"coatflames3" },
	{ (void*)"coatflames4" },
	{ (void*)"coatflames5" },
	{ (void*)"coatflames6" },
	{ (void*)"coatflames7" },
	{ (void*)"coatflames8" },
	{ (void*)"coatflames9"}
};

NJS_TEXLIST SS_PVM = { arrayptrandlength(BurningBlazeTexName) };

NJS_TEXLIST SSAura01[] = {
	{ &BurningBlazeTexName[16], 1 },
	{ &BurningBlazeTexName[17], 1 },
	{ &BurningBlazeTexName[18], 1 },
	{ &BurningBlazeTexName[19], 1 },
	{ &BurningBlazeTexName[20], 1 },
	{ &BurningBlazeTexName[21], 1 },
	{ &BurningBlazeTexName[22], 1 },
	{ &BurningBlazeTexName[23], 1 }
};

NJS_TEXLIST SSAura02[] = {
	{ &BurningBlazeTexName[24], 1 },
	{ &BurningBlazeTexName[25], 1 },
	{ &BurningBlazeTexName[26], 1 },
	{ &BurningBlazeTexName[27], 1 },
	{ &BurningBlazeTexName[28], 1 },
	{ &BurningBlazeTexName[29], 1 },
	{ &BurningBlazeTexName[30], 1 },
	{ &BurningBlazeTexName[31], 1 }
};

NJS_TEXLIST SSWaterThing[] = {
	{ &BurningBlazeTexName[32], 2 },
	{ &BurningBlazeTexName[34], 2 },
	{ &BurningBlazeTexName[36], 2 },
	{ &BurningBlazeTexName[38], 2 },
	{ &BurningBlazeTexName[40], 2 },
	{ &BurningBlazeTexName[42], 2 },
	{ &BurningBlazeTexName[44], 2 },
	{ &BurningBlazeTexName[46], 2 }
};

NJS_TEXLIST SSHomingTex1[] = {
	{ &BurningBlazeTexName[48], 1 }
};

NJS_TEXLIST SSHomingTex2[] = {
	{ &BurningBlazeTexName[49], 1 },
	{ &BurningBlazeTexName[50], 1 },
	{ &BurningBlazeTexName[51], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[52], 1 },
	{ &BurningBlazeTexName[53], 1 },
	{ &BurningBlazeTexName[54], 1 },
	{ &BurningBlazeTexName[55], 1 },
	{ &BurningBlazeTexName[56], 1 },
	{ &BurningBlazeTexName[57], 1 },
	{ &BurningBlazeTexName[58], 1 },
	{ &BurningBlazeTexName[59], 1 },
	{ &BurningBlazeTexName[60], 1 }
};

NJS_TEXLIST SSHomingTex3[] = {
	{ &BurningBlazeTexName[61], 1 },
	{ &BurningBlazeTexName[50], 1 },
	{ &BurningBlazeTexName[62], 1 },
	{ &BurningBlazeTexName[63], 1 },
	{ &BurningBlazeTexName[63], 1 },
	{ &BurningBlazeTexName[63], 1 },
	{ &BurningBlazeTexName[63], 1 },
	{ &BurningBlazeTexName[63], 1 },
	{ &BurningBlazeTexName[63], 1 },
	{ &BurningBlazeTexName[63], 1 },
	{ &BurningBlazeTexName[63], 1 },
	{ &BurningBlazeTexName[64], 1 },
	{ &BurningBlazeTexName[65], 1 },
	{ &BurningBlazeTexName[66], 1 },
	{ &BurningBlazeTexName[67], 1 },
	{ &BurningBlazeTexName[68], 1 },
	{ &BurningBlazeTexName[69], 1 },
	{ &BurningBlazeTexName[70], 1 },
	{ &BurningBlazeTexName[71], 1 },
	{ &BurningBlazeTexName[72], 1 }
};