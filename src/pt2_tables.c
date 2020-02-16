#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include "pt2_mouse.h"

uint32_t *aboutScreenBMP   = NULL, *arrowBMP           = NULL, *clearDialogBMP     = NULL;
uint32_t *diskOpScreenBMP  = NULL, *editOpModeCharsBMP = NULL, *mod2wavBMP         = NULL;
uint32_t *editOpScreen1BMP = NULL, *editOpScreen2BMP   = NULL, *samplerVolumeBMP   = NULL;
uint32_t *editOpScreen3BMP = NULL, *editOpScreen4BMP   = NULL, *spectrumVisualsBMP = NULL;
uint32_t *muteButtonsBMP   = NULL, *posEdBMP           = NULL, *samplerFiltersBMP  = NULL;
uint32_t *samplerScreenBMP = NULL, *pat2SmpDialogBMP   = NULL, *trackerFrameBMP    = NULL;
uint32_t *yesNoDialogBMP   = NULL, *bigYesNoDialogBMP  = NULL;

const uint32_t cursorColors[6][3] =
{
	{ 0x444444, 0x777777, 0xAAAAAA }, // gray
	{ 0x444400, 0x777700, 0xAAAA00 }, // yellow
	{ 0x000066, 0x004499, 0x0055BB }, // blue
	{ 0x440044, 0x770077, 0xAA00AA }, // purple
	{ 0x004400, 0x007700, 0x00AA00 }, // green
	{ 0x770000, 0x990000, 0xCC0000 }  // red
};

int8_t pNoteTable[32] = // for drumpad
{
	24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
	24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
	24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
	24, 24
};

const char noteNames1[36][4] =
{
	"C-1", "C#1", "D-1", "D#1", "E-1", "F-1", "F#1" ,"G-1", "G#1", "A-1", "A#1", "B-1",
	"C-2", "C#2", "D-2", "D#2", "E-2", "F-2", "F#2" ,"G-2", "G#2", "A-2", "A#2", "B-2",
	"C-3", "C#3", "D-3", "D#3", "E-3", "F-3", "F#3" ,"G-3", "G#3", "A-3", "A#3", "B-3"
};

const char noteNames2[36][4] =
{
	"C-1", { 'D', 127, '1'}, "D-1", { 'E', 127, '1'}, "E-1", "F-1", { 'G', 127, '1'}, "G-1", { 'A', 127, '1'}, "A-1", { 'B', 127, '1'}, "B-1",
	"C-2", { 'D', 127, '2'}, "D-2", { 'E', 127, '2'}, "E-2", "F-2", { 'G', 127, '2'}, "G-2", { 'A', 127, '2'}, "A-2", { 'B', 127, '2'}, "B-2",
	"C-3", { 'D', 127, '3'}, "D-3", { 'E', 127, '3'}, "E-3", "F-3", { 'G', 127, '3'}, "G-3", { 'A', 127, '3'}, "A-3", { 'B', 127, '3'}, "B-3"
};

const uint8_t vibratoTable[32] =
{
	0x00, 0x18, 0x31, 0x4A, 0x61, 0x78, 0x8D, 0xA1,
	0xB4, 0xC5, 0xD4, 0xE0, 0xEB, 0xF4, 0xFA, 0xFD,
	0xFF, 0xFD, 0xFA, 0xF4, 0xEB, 0xE0, 0xD4, 0xC5,
	0xB4, 0xA1, 0x8D, 0x78, 0x61, 0x4A, 0x31, 0x18
};

const int16_t periodTable[606] =
{
	856,808,762,720,678,640,604,570,538,508,480,453,
	428,404,381,360,339,320,302,285,269,254,240,226,
	214,202,190,180,170,160,151,143,135,127,120,113,0,
	850,802,757,715,674,637,601,567,535,505,477,450,
	425,401,379,357,337,318,300,284,268,253,239,225,
	213,201,189,179,169,159,150,142,134,126,119,113,0,
	844,796,752,709,670,632,597,563,532,502,474,447,
	422,398,376,355,335,316,298,282,266,251,237,224,
	211,199,188,177,167,158,149,141,133,125,118,112,0,
	838,791,746,704,665,628,592,559,528,498,470,444,
	419,395,373,352,332,314,296,280,264,249,235,222,
	209,198,187,176,166,157,148,140,132,125,118,111,0,
	832,785,741,699,660,623,588,555,524,495,467,441,
	416,392,370,350,330,312,294,278,262,247,233,220,
	208,196,185,175,165,156,147,139,131,124,117,110,0,
	826,779,736,694,655,619,584,551,520,491,463,437,
	413,390,368,347,328,309,292,276,260,245,232,219,
	206,195,184,174,164,155,146,138,130,123,116,109,0,
	820,774,730,689,651,614,580,547,516,487,460,434,
	410,387,365,345,325,307,290,274,258,244,230,217,
	205,193,183,172,163,154,145,137,129,122,115,109,0,
	814,768,725,684,646,610,575,543,513,484,457,431,
	407,384,363,342,323,305,288,272,256,242,228,216,
	204,192,181,171,161,152,144,136,128,121,114,108,0,
	907,856,808,762,720,678,640,604,570,538,508,480,
	453,428,404,381,360,339,320,302,285,269,254,240,
	226,214,202,190,180,170,160,151,143,135,127,120,0,
	900,850,802,757,715,675,636,601,567,535,505,477,
	450,425,401,379,357,337,318,300,284,268,253,238,
	225,212,200,189,179,169,159,150,142,134,126,119,0,
	894,844,796,752,709,670,632,597,563,532,502,474,
	447,422,398,376,355,335,316,298,282,266,251,237,
	223,211,199,188,177,167,158,149,141,133,125,118,0,
	887,838,791,746,704,665,628,592,559,528,498,470,
	444,419,395,373,352,332,314,296,280,264,249,235,
	222,209,198,187,176,166,157,148,140,132,125,118,0,
	881,832,785,741,699,660,623,588,555,524,494,467,
	441,416,392,370,350,330,312,294,278,262,247,233,
	220,208,196,185,175,165,156,147,139,131,123,117,0,
	875,826,779,736,694,655,619,584,551,520,491,463,
	437,413,390,368,347,328,309,292,276,260,245,232,
	219,206,195,184,174,164,155,146,138,130,123,116,0,
	868,820,774,730,689,651,614,580,547,516,487,460,
	434,410,387,365,345,325,307,290,274,258,244,230,
	217,205,193,183,172,163,154,145,137,129,122,115,0,
	862,814,768,725,684,646,610,575,543,513,484,457,
	431,407,384,363,342,323,305,288,272,256,242,228,
	216,203,192,181,171,161,152,144,136,128,121,114,0,

	// PT BUGFIX: overflowing arpeggio on -1 finetuned samples, add extra zeroes
	0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

// button tables taken from the ptplay project + modified

const guiButton_t bAsk[] =
{
	{171, 71,196, 81, PTB_SUREY},
	{234, 71,252, 81, PTB_SUREN}
};

const guiButton_t bPat2SmpAsk[] =
{
	{168, 71,185, 81, PTB_PAT2SMP_HI},
	{192, 71,210, 81, PTB_PAT2SMP_LO},
	{217, 71,256, 81, PTB_PAT2SMP_ABORT}
};

const guiButton_t bClear[] =
{
	{166, 57,198, 67, PTB_CLEARSONG},
	{204, 57,257, 67, PTB_CLEARSAMPLES},

	{166, 73,198, 83, PTB_CLEARALL},
	{204, 73,257, 83, PTB_CLEARCANCEL}
};

const guiButton_t bTopScreen[] =
{
	{  0,  0, 39, 10, PTB_POSED},
	{ 40,  0, 50, 10, PTB_POSINS},
	{ 51,  0, 61, 10, PTB_POSDEL},
	{ 62,  0, 97, 10, PTB_POSS},
	{ 98,  0,108, 10, PTB_POSU},
	{109,  0,119, 10, PTB_POSD},
	{120,  0,181, 10, PTB_PLAY},
	{182,  0,243, 10, PTB_STOP},
	{244,  0,305, 10, PTB_MOD2WAV},
	{306,  0,319, 10, PTB_CHAN1},

	{ 62, 11, 97, 21, PTB_PATTERNS},
	{ 98, 11,108, 21, PTB_PATTERNU},
	{109, 11,119, 21, PTB_PATTERND},
	{120, 11,181, 21, PTB_PATTERN},
	{182, 11,243, 21, PTB_CLEAR},
	{244, 11,305, 21, PTB_PAT2SMP},
	{306, 11,319, 21, PTB_CHAN2},

	{ 62, 22, 97, 32, PTB_LENGTHS},
	{ 98, 22,108, 32, PTB_LENGTHU},
	{109, 22,119, 32, PTB_LENGTHD},
	{120, 22,181, 32, PTB_EDIT},
	{182, 22,243, 32, PTB_EDITOP},
	{244, 22,305, 32, PTB_POSED},
	{306, 22,319, 32, PTB_CHAN3},

	{ 98, 33,108, 43, PTB_FTUNEU},
	{109, 33,119, 43, PTB_FTUNED},
	{120, 33,181, 43, PTB_RECORD},
	{182, 33,243, 43, PTB_DISKOP},
	{244, 33,305, 43, PTB_SAMPLER},
	{306, 33,319, 43, PTB_CHAN4},

	{ 62, 44, 97, 54, PTB_SAMPLES},
	{ 98, 44,108, 54, PTB_SAMPLEU},
	{109, 44,119, 54, PTB_SAMPLED},
	{306, 44,319, 54, PTB_ABOUT}, // 'about' has priority over PTB_VISUALS
	{120, 44,319, 98, PTB_VISUALS},

	{ 62, 55, 97, 65, PTB_SVOLUMES},
	{ 98, 55,108, 65, PTB_SVOLUMEU},
	{109, 55,119, 65, PTB_SVOLUMED},

	{ 62, 66, 97, 76, PTB_SLENGTHS},
	{ 98, 66,108, 76, PTB_SLENGTHU},
	{109, 66,119, 76, PTB_SLENGTHD},

	{ 62, 77, 97, 87, PTB_SREPEATS},
	{ 98, 77,108, 87, PTB_SREPEATU},
	{109, 77,119, 87, PTB_SREPEATD},

	{ 62, 88, 97, 98, PTB_SREPLENS},
	{ 98, 88,108, 98, PTB_SREPLENU},
	{109, 88,119, 98, PTB_SREPLEND}
};

const guiButton_t bMidScreen[] =
{
	{  0, 99,319,109, PTB_SONGNAME},

	{  0,110,286,120, PTB_SAMPLENAME},
	{287,110,319,120, PTB_LOADSAMPLE}
};

const guiButton_t bBotScreen[] =
{
	{  0,121, 25,137, PTB_PATTBOX},
	{ 26,121, 43,137, PTB_TEMPOU},
	{ 43,121, 59,137, PTB_TEMPOD},

	{  0,138,319,254, PTB_PATTDATA}
};

const guiButton_t bDiskOp[] =
{
	{ 80,  0,145, 10, PTB_DO_PACKMOD},
	{146,  0,155, 10, PTB_DO_MODARROW},
	{156,  0,237, 10, PTB_DO_LOADMODULE},
	{238,  0,319, 10, PTB_DO_SAVEMODULE},

	{ 80, 11,145, 21, PTB_DO_SAMPLEFORMAT},
	{146, 11,155, 21, PTB_DO_SAMPLEARROW},
	{156, 11,237, 21, PTB_DO_LOADSAMPLE},
	{238, 11,319, 21, PTB_DO_SAVESAMPLE},

	{  0, 22,237, 32, PTB_DO_DATAPATH},
	{238, 22,272, 32, PTB_DO_PARENT},
	{273, 22,307, 32, PTB_DO_REFRESH},
	{308, 22,319, 30, PTB_DO_SCROLLTOP},

	{308, 31,319, 39, PTB_DO_SCROLLUP},
	{  2, 34,304, 93, PTB_DO_FILEAREA},
	{308, 40,319, 80, PTB_DO_EXIT},
	{308, 81,319, 89, PTB_DO_SCROLLDOWN},
	{308, 90,319, 99, PTB_DO_SCROLLBOT},
};

const guiButton_t bPosEd[] =
{
	{ 120,  0,171, 10, PTB_POSINS},
	{ 172,  0,267, 21, PTB_STOP},
	{ 268,  0,319, 10, PTB_PLAY},

	{ 120, 11,171, 21, PTB_POSDEL},
	{ 178, 22,307, 98, PTB_DUMMY},
	{ 268, 11,319, 21, PTB_PATTERN},

	{ 120, 22,177, 98, PTB_PE_PATT},
	{ 308, 22,319, 32, PTB_PE_SCROLLTOP},

	{ 308, 33,319, 43, PTB_PE_SCROLLUP},
	{ 308, 44,319, 76, PTB_PE_EXIT},
	{ 308, 77,319, 87, PTB_PE_SCROLLDOWN},
	{ 308, 88,319, 98, PTB_PE_SCROLLBOT}
};

const guiButton_t bEditOp1[] =
{
	{120, 44,319, 54, PTB_EO_TITLEBAR},

	{120, 55,212, 65, PTB_EO_TRACK_NOTE_UP},
	{213, 55,305, 65, PTB_EO_PATT_NOTE_UP},
	{306, 55,319, 65, PTB_DUMMY},

	{120, 66,212, 76, PTB_EO_TRACK_NOTE_DOWN},
	{213, 66,305, 76, PTB_EO_PATT_NOTE_DOWN},
	{306, 66,319, 76, PTB_EO_2},

	{120, 77,212, 87, PTB_EO_TRACK_OCTA_UP},
	{213, 77,305, 87, PTB_EO_PATT_OCTA_UP},
	{306, 77,319, 87, PTB_EO_3},

	{120, 88,212, 98, PTB_EO_TRACK_OCTA_DOWN},
	{213, 88,305, 98, PTB_EO_PATT_OCTA_DOWN},
	{306, 88,319, 98, PTB_EO_EXIT}
};

const guiButton_t bEditOp2[] =
{
	{120, 44,319, 54, PTB_EO_TITLEBAR},

	{120, 55,212, 65, PTB_EO_RECORD},
	{213, 55,259, 65, PTB_EO_DELETE},
	{260, 55,305, 65, PTB_EO_KILL},
	{306, 55,319, 65, PTB_EO_1},

	{120, 66,212, 76, PTB_EO_QUANTIZE},
	{213, 66,259, 76, PTB_EO_EXCHGE},
	{260, 66,305, 76, PTB_EO_COPY},
	{306, 66,319, 76, PTB_DUMMY},

	{120, 77,188, 87, PTB_EO_METRO_1},
	{189, 77,212, 87, PTB_EO_METRO_2},
	{213, 77,259, 87, PTB_EO_FROM},
	{260, 77,283, 87, PTB_EO_FROM_NUM},
	{284, 77,294, 87, PTB_EO_FROM_UP},
	{295, 77,305, 87, PTB_EO_FROM_DOWN},
	{306, 77,319, 87, PTB_EO_3},

	{120, 88,212, 98, PTB_EO_KEYS},
	{213, 88,259, 98, PTB_EO_TO},
	{260, 88,283, 98, PTB_EO_TO_NUM},
	{284, 88,294, 98, PTB_EO_TO_UP},
	{295, 88,305, 98, PTB_EO_TO_DOWN},
	{306, 88,319, 98, PTB_EO_EXIT},
};

const guiButton_t bEditOp3[] =
{
	{120, 44,319, 54, PTB_EO_TITLEBAR},

	{120, 55,165, 65, PTB_EO_MIX},
	{166, 55,212, 65, PTB_EO_ECHO},
	{213, 55,243, 65, PTB_DUMMY},
	{244, 55,283, 65, PTB_EO_POS_NUM},
	{284, 55,294, 65, PTB_EO_POS_UP},
	{295, 55,305, 65, PTB_EO_POS_DOWN},
	{306, 55,319, 65, PTB_EO_1},

	{120, 66,165, 76, PTB_EO_BOOST},
	{166, 66,212, 76, PTB_EO_FILTER},
	{213, 66,243, 76, PTB_EO_MOD},
	{244, 66,283, 76, PTB_EO_MOD_NUM},
	{284, 66,294, 76, PTB_EO_MOD_UP},
	{295, 66,305, 76, PTB_EO_MOD_DOWN},
	{306, 66,319, 76, PTB_EO_2},

	{120, 77,165, 87, PTB_EO_X_FADE},
	{166, 77,212, 87, PTB_EO_BACKWD},
	{213, 77,230, 87, PTB_EO_CB},
	{231, 77,269, 87, PTB_EO_CHORD},
	{270, 77,287, 87, PTB_EO_FU},
	{288, 77,305, 87, PTB_EO_FD},
	{306, 77,319, 87, PTB_DUMMY},

	{120, 88,165, 98, PTB_EO_UPSAMP},
	{166, 88,212, 98, PTB_EO_DNSAMP},
	{213, 88,243, 98, PTB_EO_VOL},
	{244, 88,283, 98, PTB_EO_VOL_NUM},
	{284, 88,294, 98, PTB_EO_VOL_UP},
	{295, 88,305, 98, PTB_EO_VOL_DOWN},
	{306, 88,319, 98, PTB_EO_EXIT}
};

const guiButton_t bEditOp4[] =
{
	{120, 44,319, 54, PTB_EO_TITLEBAR},

	{120, 55,165, 65, PTB_EO_DOCHORD},
	{166, 55,204, 65, PTB_EO_MAJOR},
	{205, 55,251, 65, PTB_EO_MAJOR7},
	{251, 55,283, 65, PTB_EO_NOTE1},
	{284, 55,294, 65, PTB_EO_NOTE1_UP},
	{295, 55,305, 65, PTB_EO_NOTE1_DOWN},
	{306, 55,319, 65, PTB_EO_1},

	{120, 66,165, 76, PTB_EO_RESET},
	{166, 66,204, 76, PTB_EO_MINOR},
	{205, 66,251, 76, PTB_EO_MINOR7},
	{251, 66,283, 76, PTB_EO_NOTE2},
	{284, 66,294, 76, PTB_EO_NOTE2_UP},
	{295, 66,305, 76, PTB_EO_NOTE2_DOWN},
	{306, 66,319, 76, PTB_EO_2},

	{120, 77,165, 87, PTB_EO_UNDO},
	{166, 77,204, 87, PTB_EO_SUS4},
	{205, 77,251, 87, PTB_EO_MAJOR6},
	{251, 77,283, 87, PTB_EO_NOTE3},
	{284, 77,294, 87, PTB_EO_NOTE3_UP},
	{295, 77,305, 87, PTB_EO_NOTE3_DOWN},
	{306, 77,319, 87, PTB_EO_3},

	{120, 88,157, 98, PTB_EO_LENGTH},
	{158, 88,204, 98, PTB_DUMMY},
	{205, 88,251, 98, PTB_EO_MINOR6},
	{251, 88,283, 98, PTB_EO_NOTE4},
	{284, 88,294, 98, PTB_EO_NOTE4_UP},
	{295, 88,305, 98, PTB_EO_NOTE4_DOWN},
	{306, 88,319, 98, PTB_EO_EXIT}
};

const guiButton_t bSampler[] =
{
	{  6,124, 25,134, PTB_SA_EXIT},
	{  0,138,319,201, PTB_SA_SAMPLEAREA},
	{  3,205,316,210, PTB_SA_ZOOMBARAREA},

	{ 32,211, 95,221, PTB_SA_PLAYWAVE},
	{ 96,211,175,221, PTB_SA_SHOWRANGE},
	{176,211,245,221, PTB_SA_ZOOMOUT},

	{  0,222, 30,243, PTB_SA_STOP},
	{ 32,222, 95,232, PTB_SA_PLAYDISPLAY},
	{ 96,222,175,232, PTB_SA_SHOWALL},
	{176,222,245,232, PTB_SA_RANGEALL},
	{246,222,319,232, PTB_SA_LOOP},

	{ 32,233, 94,243, PTB_SA_PLAYRANGE},
	{ 96,233,115,243, PTB_SA_RANGEBEG},
	{116,233,135,243, PTB_SA_RANGEEND},
	{136,233,174,243, PTB_SA_RANGECENTER},
	{176,233,245,243, PTB_SA_RESAMPLE},
	{246,233,319,243, PTB_SA_RESAMPLENOTE},

	{  0,244, 31,254, PTB_SA_CUT},
	{ 32,244, 63,254, PTB_SA_COPY},
	{ 64,244, 95,254, PTB_SA_PASTE},
	{ 96,244,135,254, PTB_SA_VOLUME},
	{136,244,175,254, PTB_SA_TUNETONE},
	{176,244,210,254, PTB_SA_FIXDC},
	{211,244,245,254, PTB_SA_FILTERS}
};
