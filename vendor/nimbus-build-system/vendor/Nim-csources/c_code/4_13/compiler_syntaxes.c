/* Generated by Nim Compiler v0.18.0 */
/*   (c) 2018 Andreas Rumpf */
/* The generated code is subject to the original license. */
#define NIM_NEW_MANGLING_RULES
#define NIM_INTBITS 64

#include "nimbase.h"
#include <string.h>
#include <stdio.h>
#undef LANGUAGE_C
#undef MIPSEB
#undef MIPSEL
#undef PPC
#undef R3000
#undef R4000
#undef i386
#undef linux
#undef mips
#undef near
#undef powerpc
#undef unix
typedef struct tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw;
typedef struct tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw;
typedef struct tyObject_TParsers_WENTuyElSRFloaVOQEDvMg tyObject_TParsers_WENTuyElSRFloaVOQEDvMg;
typedef struct tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw;
typedef struct tyObject_TLexer_IOWqYAjEw106AHiXcZcUGg tyObject_TLexer_IOWqYAjEw106AHiXcZcUGg;
typedef struct tyObject_TBaseLexer_z9a7O76kH1tJ9aXJ3h2MdEzA tyObject_TBaseLexer_z9a7O76kH1tJ9aXJ3h2MdEzA;
typedef struct RootObj RootObj;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw;
typedef struct tyObject_TLineInfo_T9c3PM9bs7WZ4LIQfEici9cZw tyObject_TLineInfo_T9c3PM9bs7WZ4LIQfEici9cZw;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct tyObject_TToken_kLaEEPwLj8cag79cbYQIkHQ tyObject_TToken_kLaEEPwLj8cag79cbYQIkHQ;
typedef struct tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g;
typedef struct tyObject_TType_LTUWCZolpovw9cWE3JBWSUw tyObject_TType_LTUWCZolpovw9cWE3JBWSUw;
typedef struct tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw;
typedef struct tySequence_ehmV9bTklH2Gt9cXHV9c0HLeQ tySequence_ehmV9bTklH2Gt9cXHV9c0HLeQ;
typedef struct tyObject_TIdObj_raN9cHVgzmvaXisezY9aGg9cg tyObject_TIdObj_raN9cHVgzmvaXisezY9aGg9cg;
typedef struct tySequence_zuqP4Riz26Oi5fWgPYVEgA tySequence_zuqP4Riz26Oi5fWgPYVEgA;
typedef struct tySequence_iGkpo9aKQdr3NWelKC4cnJA tySequence_iGkpo9aKQdr3NWelKC4cnJA;
typedef struct tyObject_TLoc_EtHNvCB0bgfu9bFjzx9cb6aA tyObject_TLoc_EtHNvCB0bgfu9bFjzx9cb6aA;
typedef struct tyObject_RopeObj_HF4qJnb6xiOddgPmsxodtQ tyObject_RopeObj_HF4qJnb6xiOddgPmsxodtQ;
typedef struct tySequence_DXS6mEo7PVUFJkirsQ9bNQA tySequence_DXS6mEo7PVUFJkirsQ9bNQA;
typedef struct tyObject_TStrTable_f07aOS3dr28kGa5wcE29aFA tyObject_TStrTable_f07aOS3dr28kGa5wcE29aFA;
typedef struct tySequence_sksVpmPRIkNR9axiwtD1Guw tySequence_sksVpmPRIkNR9axiwtD1Guw;
typedef struct tyObject_TLib_NBMxlJ6g3utqUlplqTTHkA tyObject_TLib_NBMxlJ6g3utqUlplqTTHkA;
typedef struct tyTuple_a09bGTAl9ceOKTAytYdkbyKg tyTuple_a09bGTAl9ceOKTAytYdkbyKg;
typedef struct tyObject_TInstantiation_5LqgVn6Tq9ainQRK7TQAQxA tyObject_TInstantiation_5LqgVn6Tq9ainQRK7TQAQxA;
typedef NU8 tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw;
typedef NU8 tyEnum_TNimKind_jIBKr1ejBgsfM33Kxw4j7A;
typedef NU8 tySet_tyEnum_TNimTypeFlag_v8QUszD1sWlSIWZz7mC4bQ;
typedef N_NIMCALL_PTR(void, tyProc_ojoeKfW4VYIm36I9cpDTQIg) (void* p, NI op);
typedef N_NIMCALL_PTR(void*, tyProc_WSm2xU5ARYv9aAR4l0z9c9auQ) (void* p);
struct TNimType {
NI size;
tyEnum_TNimKind_jIBKr1ejBgsfM33Kxw4j7A kind;
tySet_tyEnum_TNimTypeFlag_v8QUszD1sWlSIWZz7mC4bQ flags;
TNimType* base;
TNimNode* node;
void* finalizer;
tyProc_ojoeKfW4VYIm36I9cpDTQIg marker;
tyProc_WSm2xU5ARYv9aAR4l0z9c9auQ deepcopy;
};
struct RootObj {
TNimType* m_type;
};
struct tyObject_TBaseLexer_z9a7O76kH1tJ9aXJ3h2MdEzA {
  RootObj Sup;
NI bufpos;
NCSTRING buf;
NI bufLen;
tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* stream;
NI lineNumber;
NI sentinel;
NI lineStart;
NI offsetBase;
};
typedef NU8 tyEnum_CursorPosition_moKbK9a5baLOKMP3AQAcKoQ;
typedef NU16 tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw;
struct TGenericSeq {
NI len;
NI reserved;
};
struct NimStringDesc {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
typedef struct {
N_NIMCALL_PTR(void, ClP_0) (tyObject_TLineInfo_T9c3PM9bs7WZ4LIQfEici9cZw info, tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw msg, NimStringDesc* arg, void* ClE_0);
void* ClE_0;
} tyProc_l9buWVPY1qenw5uCj2k2Uqg;
struct tyObject_TLexer_IOWqYAjEw106AHiXcZcUGg {
  tyObject_TBaseLexer_z9a7O76kH1tJ9aXJ3h2MdEzA Sup;
NI32 fileIdx;
NI indentAhead;
NI currLineIndent;
NIM_BOOL strongSpaces;
NIM_BOOL allowTabs;
tyEnum_CursorPosition_moKbK9a5baLOKMP3AQAcKoQ cursor;
tyProc_l9buWVPY1qenw5uCj2k2Uqg errorHandler;
tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* cache;
};
typedef NU8 tyEnum_TTokType_vw8YkgaVtNadqP8v5OpXKA;
typedef NU8 tyEnum_TNumericalBase_9cbxR9czWgoXwHHSzHtd9aV7Q;
struct tyObject_TToken_kLaEEPwLj8cag79cbYQIkHQ {
tyEnum_TTokType_vw8YkgaVtNadqP8v5OpXKA tokType;
NI indent;
tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* ident;
NI64 iNumber;
NF fNumber;
tyEnum_TNumericalBase_9cbxR9czWgoXwHHSzHtd9aV7Q base;
NI8 strongSpaceA;
NI8 strongSpaceB;
NimStringDesc* literal;
NI line;
NI col;
};
struct tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw {
NI currInd;
NIM_BOOL firstTok;
NIM_BOOL strongSpaces;
NIM_BOOL hasProgress;
tyObject_TLexer_IOWqYAjEw106AHiXcZcUGg lex;
tyObject_TToken_kLaEEPwLj8cag79cbYQIkHQ tok;
NI inPragma;
NI inSemiStmtList;
};
struct tyObject_TParsers_WENTuyElSRFloaVOQEDvMg {
tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw skin;
tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw parser;
};
typedef NU8 tyEnum_TNimNodeKind_unfNsxrcATrufDZmpBq4HQ;
struct TNimNode {
tyEnum_TNimNodeKind_unfNsxrcATrufDZmpBq4HQ kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
typedef NU8 tyEnum_FileMode_fVUBHvW79bXUw1j55Oo9avSQ;
struct tyObject_TLineInfo_T9c3PM9bs7WZ4LIQfEici9cZw {
NI16 line;
NI16 col;
NI32 fileIndex;
};
typedef NU32 tySet_tyEnum_TNodeFlag_jyh9acXHkhZANSSvPIY7ZLg;
typedef NU8 tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw;
struct tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw {
tyObject_TType_LTUWCZolpovw9cWE3JBWSUw* typ;
tyObject_TLineInfo_T9c3PM9bs7WZ4LIQfEici9cZw info;
tySet_tyEnum_TNodeFlag_jyh9acXHkhZANSSvPIY7ZLg flags;
tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw kind;
union{
struct {NI64 intVal;
} S1;
struct {NF floatVal;
} S2;
struct {NimStringDesc* strVal;
} S3;
struct {tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* sym;
} S4;
struct {tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* ident;
} S5;
struct {tySequence_ehmV9bTklH2Gt9cXHV9c0HLeQ* sons;
} S6;
} kindU;
NimStringDesc* comment;
};
struct tyObject_TIdObj_raN9cHVgzmvaXisezY9aGg9cg {
  RootObj Sup;
NI id;
};
struct tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g {
  tyObject_TIdObj_raN9cHVgzmvaXisezY9aGg9cg Sup;
NimStringDesc* s;
tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* next;
NI h;
};
typedef NU8 tySet_tyEnum_TRenderFlag_wrPgUo1ExBlHvFnXN2nSHw;
typedef NU8 tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg;
typedef NimStringDesc* tyArray_cM0k9buRoahrhdhCHJaeg8w[4];
typedef NimStringDesc* tyArray_8GOl8NvXQYALGK9b1NT1qPQ[4];
typedef NU64 tySet_tyEnum_TMsgKind_VhF2u8Sb9c3Fk8NMu6WUVoA;
typedef NU16 tyEnum_TMsgKind_VhF2u8Sb9c3Fk8NMu6WUVoA;
typedef NimStringDesc* tyArray_8ZvwQIddfpj2THRVPsFzIQ[1];
typedef NU8 tySet_tyEnum_MsgFlag_BzRTaQ6LrPDZKEKt9bswkOQ;
typedef NU8 tyEnum_TLLStreamKind_jVcKY16LbOamXE9bxXUD6pQ;
struct tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw {
  RootObj Sup;
tyEnum_TLLStreamKind_jVcKY16LbOamXE9bxXUD6pQ kind;
FILE* f;
NimStringDesc* s;
NI rd;
NI wr;
NI lineOffset;
};
typedef tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* tyArray_CBfZt49asUfAsBVM7a3Rc9cw[8192];
struct tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw {
tyArray_CBfZt49asUfAsBVM7a3Rc9cw buckets;
NI wordCounter;
tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* idAnon;
tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* idDelegator;
tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* emptyIdent;
};
typedef NU8 tyEnum_TTypeKind_9a3YiReNVD0IJHWFKgXRe9ag;
typedef NU8 tyEnum_TCallingConvention_yjAJ8w0h1PBaSwSGJ3P7IA;
typedef NU64 tySet_tyEnum_TTypeFlag_x2m5g1NpbmDig4wLT3Ylhw;
typedef NU8 tyEnum_TLocKind_O7PRFZKuiBBWbku09cayVBg;
typedef NU8 tyEnum_TStorageLoc_JK9cKMX3XnqHaUky9b6gkGEw;
typedef NU16 tySet_tyEnum_TLocFlag_o2bqJgR4ceIupnUSpxiudA;
struct tyObject_TLoc_EtHNvCB0bgfu9bFjzx9cb6aA {
tyEnum_TLocKind_O7PRFZKuiBBWbku09cayVBg k;
tyEnum_TStorageLoc_JK9cKMX3XnqHaUky9b6gkGEw storage;
tySet_tyEnum_TLocFlag_o2bqJgR4ceIupnUSpxiudA flags;
tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* lode;
tyObject_RopeObj_HF4qJnb6xiOddgPmsxodtQ* r;
tyObject_RopeObj_HF4qJnb6xiOddgPmsxodtQ* dup;
};
struct tyObject_TType_LTUWCZolpovw9cWE3JBWSUw {
  tyObject_TIdObj_raN9cHVgzmvaXisezY9aGg9cg Sup;
tyEnum_TTypeKind_9a3YiReNVD0IJHWFKgXRe9ag kind;
tyEnum_TCallingConvention_yjAJ8w0h1PBaSwSGJ3P7IA callConv;
tySet_tyEnum_TTypeFlag_x2m5g1NpbmDig4wLT3Ylhw flags;
tySequence_zuqP4Riz26Oi5fWgPYVEgA* sons;
tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* owner;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* sym;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* destructor;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* deepCopy;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* assignment;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* sink;
tySequence_iGkpo9aKQdr3NWelKC4cnJA* methods;
NI64 size;
NI16 align;
NI16 lockLevel;
tyObject_TLoc_EtHNvCB0bgfu9bFjzx9cb6aA loc;
tyObject_TType_LTUWCZolpovw9cWE3JBWSUw* typeInst;
};
typedef NU8 tyEnum_TSymKind_cNCW9acsSznmEccl1fgQwkw;
struct tyObject_TStrTable_f07aOS3dr28kGa5wcE29aFA {
NI counter;
tySequence_sksVpmPRIkNR9axiwtD1Guw* data;
};
typedef NU16 tyEnum_TMagic_shZhZOdbVC5nnFvcXQAImg;
typedef NU64 tySet_tyEnum_TSymFlag_K9ay6LWMat9bUiT9bIbMxpDHw;
typedef NU32 tySet_tyEnum_TOption_WspMeQySXNP2XoTWR5MTgg;
struct tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw {
  tyObject_TIdObj_raN9cHVgzmvaXisezY9aGg9cg Sup;
tyEnum_TSymKind_cNCW9acsSznmEccl1fgQwkw kind;
union{
struct {tySequence_zuqP4Riz26Oi5fWgPYVEgA* typeInstCache;
} S1;
struct {tySequence_DXS6mEo7PVUFJkirsQ9bNQA* procInstCache;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* gcUnsafetyReason;
} S2;
struct {tySequence_DXS6mEo7PVUFJkirsQ9bNQA* usedGenerics;
tyObject_TStrTable_f07aOS3dr28kGa5wcE29aFA tab;
} S3;
struct {tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* guard;
NI bitsize;
} S4;
} kindU;
tyEnum_TMagic_shZhZOdbVC5nnFvcXQAImg magic;
tyObject_TType_LTUWCZolpovw9cWE3JBWSUw* typ;
tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* name;
tyObject_TLineInfo_T9c3PM9bs7WZ4LIQfEici9cZw info;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* owner;
tySet_tyEnum_TSymFlag_K9ay6LWMat9bUiT9bIbMxpDHw flags;
tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* ast;
tySet_tyEnum_TOption_WspMeQySXNP2XoTWR5MTgg options;
NI position;
NI offset;
tyObject_TLoc_EtHNvCB0bgfu9bFjzx9cb6aA loc;
tyObject_TLib_NBMxlJ6g3utqUlplqTTHkA* annex;
tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* constraint;
};
struct tyTuple_a09bGTAl9ceOKTAytYdkbyKg {
NI Field0;
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* Field1;
};
struct tyObject_RopeObj_HF4qJnb6xiOddgPmsxodtQ {
  RootObj Sup;
tyObject_RopeObj_HF4qJnb6xiOddgPmsxodtQ* left;
tyObject_RopeObj_HF4qJnb6xiOddgPmsxodtQ* right;
NI length;
NimStringDesc* data;
};
typedef NU8 tyEnum_TLibKind_9b8v60kso59bBaw9cp8B9a9apKQ;
struct tyObject_TLib_NBMxlJ6g3utqUlplqTTHkA {
tyEnum_TLibKind_9b8v60kso59bBaw9cp8B9a9apKQ kind;
NIM_BOOL generated;
NIM_BOOL isOverriden;
tyObject_RopeObj_HF4qJnb6xiOddgPmsxodtQ* name;
tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* path;
};
struct tyObject_TInstantiation_5LqgVn6Tq9ainQRK7TQAQxA {
tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* sym;
tySequence_zuqP4Riz26Oi5fWgPYVEgA* concreteTypes;
NI compilesId;
};
struct tySequence_ehmV9bTklH2Gt9cXHV9c0HLeQ {
  TGenericSeq Sup;
  tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* data[SEQ_DECL_SIZE];
};
struct tySequence_zuqP4Riz26Oi5fWgPYVEgA {
  TGenericSeq Sup;
  tyObject_TType_LTUWCZolpovw9cWE3JBWSUw* data[SEQ_DECL_SIZE];
};
struct tySequence_iGkpo9aKQdr3NWelKC4cnJA {
  TGenericSeq Sup;
  tyTuple_a09bGTAl9ceOKTAytYdkbyKg data[SEQ_DECL_SIZE];
};
struct tySequence_DXS6mEo7PVUFJkirsQ9bNQA {
  TGenericSeq Sup;
  tyObject_TInstantiation_5LqgVn6Tq9ainQRK7TQAQxA* data[SEQ_DECL_SIZE];
};
struct tySequence_sksVpmPRIkNR9axiwtD1Guw {
  TGenericSeq Sup;
  tyObject_TSym_AXG7xcvKqaxY6koRX1xkCw* data[SEQ_DECL_SIZE];
};
N_NIMCALL(void, objectInit)(void* dest, TNimType* typ);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, toFullPathConsiderDirty_KZnzGw9baMUf9ad9aixRtHmqg_2)(NI32 fileIdx);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, open_sEp0GH2306oGo9bqBpj5oTQ)(FILE** f, NimStringDesc* filename, tyEnum_FileMode_fVUBHvW79bXUw1j55Oo9avSQ mode, NI bufSize);
N_LIB_PRIVATE N_NIMCALL(void, rawMessage_tBJ8mvo7MzzirsGkrHVc9cw)(tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw msg, NimStringDesc* arg);
N_LIB_PRIVATE N_NIMCALL(void, openParsers_zDBDS8Km3Tchi1ohPVieKQ)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p, NI32 fileIdx, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* inputstream, tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* cache);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parsePipe_bJSds72kKu77CwGx8lNYmA)(NimStringDesc* filename, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* inputStream, tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* cache);
N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, llStreamOpen_TMcHzC3C639c0ccC0wtKA2w)(NimStringDesc* filename, tyEnum_FileMode_fVUBHvW79bXUw1j55Oo9avSQ mode);
N_NIMCALL(NimStringDesc*, rawNewString)(NI space);
N_NIMCALL(NimStringDesc*, rawNewString)(NI cap);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, llStreamReadLine_Qwm1ilRhcaI3znjOGn4xBg)(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* s, NimStringDesc** line);
N_LIB_PRIVATE N_NIMCALL(NI, utf8Bom_h8LrhHxyp3nGeHzqCSFf9bg)(NimStringDesc* s);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, containsShebang_KmLpTlp0iQ7qLu2YAgAZhw)(NimStringDesc* s, NI i);
N_LIB_PRIVATE N_NIMCALL(void, openParser_xOo5exBZF46oOyrExM9a3yQ)(tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw* p, NimStringDesc* filename, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* inputStream, tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* cache, NIM_BOOL strongSpaces);
N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, llStreamOpen_HQSZA6kzdilYF0Pf022dhA)(NimStringDesc* data);
N_NIMCALL(NimStringDesc*, copyStr)(NimStringDesc* s, NI start);
N_NIMCALL(NimStringDesc*, copyStr)(NimStringDesc* s, NI first);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parseAll_x3UAdSvBfIIO33m4gWdOPg)(tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw* p);
N_LIB_PRIVATE N_NIMCALL(void, closeParser_Bv6bIlAg2H4GfVH07sPwUw)(tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw* p);
N_LIB_PRIVATE N_NIMCALL(void, llStreamClose_TQe1mwqs39ccgay5ywsr9azw)(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* s);
N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, evalPipe_nVUUGAijyBdiAxOhXa9atMg)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n, NimStringDesc* filename, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* start);
static N_INLINE(NIM_BOOL, eqStrings)(NimStringDesc* a, NimStringDesc* b);
static N_INLINE(NIM_BOOL, equalMem_fmeFeLBvgmAHG9bC8ETS9bYQropes)(void* a, void* b, NI size);
N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, applyFilter_9cHsu5TuPlpg9bEC9cADFtBCA)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n, NimStringDesc* filename, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* stdin_0);
N_LIB_PRIVATE N_NIMCALL(tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g*, getCallee_8v8U4rPUh2LEtUf9cZrto9bQ)(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, renderTree_ppjdh9aQ5L0SGPF8yz1gZ9cA)(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n, tySet_tyEnum_TRenderFlag_wrPgUo1ExBlHvFnXN2nSHw renderFlags);
N_LIB_PRIVATE N_NIMCALL(tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg, getFilter_VI3Fiobf4N9aSXR2Q8kXG0A)(tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* ident);
N_LIB_PRIVATE N_NIMCALL(NI, nsuCmpIgnoreStyle)(NimStringDesc* a, NimStringDesc* b);
N_LIB_PRIVATE N_NIMCALL(tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw, getParser_hTsVGKyR7WIUC8NJAMIjvQ)(tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* ident);
N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, filterTmpl_JvVu6X7Xrt789cwD0XA6mWg)(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* stdin_0, NimStringDesc* filename, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* call);
N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, filterStrip_8vZ6X8KZZNI4xsTx2A9bPBw)(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* stdin_0, NimStringDesc* filename, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* call);
N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, filterReplace_8vZ6X8KZZNI4xsTx2A9bPBw_2)(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* stdin_0, NimStringDesc* filename, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* call);
N_LIB_PRIVATE N_NIMCALL(void, rawMessage_wSQLHRsYvHJ4DSWgdFrFaA)(tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw msg, NimStringDesc** args, NI argsLen_0);
N_LIB_PRIVATE N_NIMCALL(void, msgWriteln_mpdiFCyqIWmTQYjT6Mj9c6A)(NimStringDesc* s, tySet_tyEnum_MsgFlag_BzRTaQ6LrPDZKEKt9bswkOQ flags);
N_LIB_PRIVATE N_NIMCALL(void, openParser_AytEkdefQ9bdVwGj33lUaUw)(tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw* p, NI32 fileIdx, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* inputStream, tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* cache, NIM_BOOL strongSpaces);
N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, llStreamOpen_8hTxoBHhwtwZR9cM9bBLMsCQ)(FILE* f);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parseAll_N9cl8bNz6TaGrhhLXmkyhrw)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parseAll_e6i72kHohchMxvc8wSe9a8Q)(tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw* p);
N_LIB_PRIVATE N_NIMCALL(void, internalError_5XY9cUy7hZmUusM38U9cYYdw)(NimStringDesc* errMsg);
N_LIB_PRIVATE N_NIMCALL(void, closeParsers_aZMERNSTUyTfW9aaFR9bAn9aQ)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parseTopLevelStmt_x3UAdSvBfIIO33m4gWdOPg_40)(tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw* p);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parseTopLevelStmt_e6i72kHohchMxvc8wSe9a8Q_42)(tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw* p);
TNimType NTI_WENTuyElSRFloaVOQEDvMg_;
TNimType NTI_wHYLpKaSFkZsAwL9crNQqGw_;
extern TNimType NTI_c38t9cDVS8o9b29cOovKwkANw_;
extern tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* emptyNode_69ccLGuQ2mITw7zylZYtWcA;
extern tySet_tyEnum_TMsgKind_VhF2u8Sb9c3Fk8NMu6WUVoA gNotes_ra0BBMaJz6cOxn1JA3c6Bg;
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_6, "|", 1);
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_7, "none", 4);
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_8, "stdtmpl", 7);
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_9, "replace", 7);
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_10, "strip", 5);
NIM_CONST tyArray_cM0k9buRoahrhdhCHJaeg8w filterNames_AxTRz7iBqkPgPfZx8TM0IQ = {((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_7),
((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_8),
((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_9),
((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_10)}
;
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_11, "standard", 8);
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_12, "strongspaces", 12);
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_13, "braces", 6);
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_14, "endx", 4);
NIM_CONST tyArray_8GOl8NvXQYALGK9b1NT1qPQ parserNames_IVRWib6Nt9c9cDYSS669cL5mA = {((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_11),
((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_12),
((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_13),
((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_14)}
;
STRING_LITERAL(TM_Furs9bKK6tVLoyofH3f4bRw_15, "parser to implement", 19);

N_LIB_PRIVATE N_NIMCALL(NI, utf8Bom_h8LrhHxyp3nGeHzqCSFf9bg)(NimStringDesc* s) {
	NI result;
	result = (NI)0;
	{
		NIM_BOOL T3_;
		NIM_BOOL T4_;
		T3_ = (NIM_BOOL)0;
		T4_ = (NIM_BOOL)0;
		T4_ = ((NU8)(s->data[((NI) 0)]) == (NU8)(239));
		if (!(T4_)) goto LA5_;
		T4_ = ((NU8)(s->data[((NI) 1)]) == (NU8)(187));
		LA5_: ;
		T3_ = T4_;
		if (!(T3_)) goto LA6_;
		T3_ = ((NU8)(s->data[((NI) 2)]) == (NU8)(191));
		LA6_: ;
		if (!T3_) goto LA7_;
		result = ((NI) 3);
	}
	goto LA1_;
	LA7_: ;
	{
		result = ((NI) 0);
	}
	LA1_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, containsShebang_KmLpTlp0iQ7qLu2YAgAZhw)(NimStringDesc* s, NI i) {
	NIM_BOOL result;
	result = (NIM_BOOL)0;
	{
		NIM_BOOL T3_;
		NI j;
		T3_ = (NIM_BOOL)0;
		T3_ = ((NU8)(s->data[i]) == (NU8)(35));
		if (!(T3_)) goto LA4_;
		T3_ = ((NU8)(s->data[(NI)(i + ((NI) 1))]) == (NU8)(33));
		LA4_: ;
		if (!T3_) goto LA5_;
		j = (NI)(i + ((NI) 2));
		{
			while (1) {
				if (!(((NU8)(s->data[j])) == ((NU8)(32)) || ((NU8)(s->data[j])) == ((NU8)(9)) || ((NU8)(s->data[j])) == ((NU8)(11)) || ((NU8)(s->data[j])) == ((NU8)(13)) || ((NU8)(s->data[j])) == ((NU8)(10)) || ((NU8)(s->data[j])) == ((NU8)(12)))) goto LA8;
				j += ((NI) 1);
			} LA8: ;
		}
		result = ((NU8)(s->data[j]) == (NU8)(47));
	}
	LA5_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parsePipe_bJSds72kKu77CwGx8lNYmA)(NimStringDesc* filename, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* inputStream, tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* cache) {
	tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* result;
	tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* s;
	result = (tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*)0;
	result = emptyNode_69ccLGuQ2mITw7zylZYtWcA;
	s = llStreamOpen_TMcHzC3C639c0ccC0wtKA2w(filename, ((tyEnum_FileMode_fVUBHvW79bXUw1j55Oo9avSQ) 0));
	{
		NimStringDesc* line;
		NIM_BOOL T5_;
		NI i;
		NI linenumber;
		if (!!((s == NIM_NIL))) goto LA3_;
		line = rawNewString(((NI) 80));
		T5_ = (NIM_BOOL)0;
		T5_ = llStreamReadLine_Qwm1ilRhcaI3znjOGn4xBg(s, (&line));
		T5_;
		i = utf8Bom_h8LrhHxyp3nGeHzqCSFf9bg(line);
		linenumber = ((NI) 1);
		{
			NIM_BOOL T8_;
			NIM_BOOL T11_;
			T8_ = (NIM_BOOL)0;
			T8_ = containsShebang_KmLpTlp0iQ7qLu2YAgAZhw(line, i);
			if (!T8_) goto LA9_;
			T11_ = (NIM_BOOL)0;
			T11_ = llStreamReadLine_Qwm1ilRhcaI3znjOGn4xBg(s, (&line));
			T11_;
			i = ((NI) 0);
			linenumber += ((NI) 1);
		}
		LA9_: ;
		{
			NIM_BOOL T14_;
			tyObject_TParser_c38t9cDVS8o9b29cOovKwkANw q;
			NimStringDesc* T20_;
			tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* T21_;
			T14_ = (NIM_BOOL)0;
			T14_ = ((NU8)(line->data[i]) == (NU8)(35));
			if (!(T14_)) goto LA15_;
			T14_ = ((NU8)(line->data[(NI)(i + ((NI) 1))]) == (NU8)(63));
			LA15_: ;
			if (!T14_) goto LA16_;
			i += ((NI) 2);
			{
				while (1) {
					if (!(((NU8)(line->data[i])) == ((NU8)(32)) || ((NU8)(line->data[i])) == ((NU8)(9)) || ((NU8)(line->data[i])) == ((NU8)(11)) || ((NU8)(line->data[i])) == ((NU8)(13)) || ((NU8)(line->data[i])) == ((NU8)(10)) || ((NU8)(line->data[i])) == ((NU8)(12)))) goto LA19;
					i += ((NI) 1);
				} LA19: ;
			}
			memset((void*)(&q), 0, sizeof(q));
			objectInit((&q), (&NTI_c38t9cDVS8o9b29cOovKwkANw_));
			T20_ = (NimStringDesc*)0;
			T20_ = copyStr(line, i);
			T21_ = (tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*)0;
			T21_ = llStreamOpen_HQSZA6kzdilYF0Pf022dhA(T20_);
			openParser_xOo5exBZF46oOyrExM9a3yQ((&q), filename, T21_, cache, NIM_FALSE);
			result = parseAll_x3UAdSvBfIIO33m4gWdOPg((&q));
			closeParser_Bv6bIlAg2H4GfVH07sPwUw((&q));
		}
		LA16_: ;
		llStreamClose_TQe1mwqs39ccgay5ywsr9azw(s);
	}
	LA3_: ;
	return result;
}

static N_INLINE(NIM_BOOL, equalMem_fmeFeLBvgmAHG9bC8ETS9bYQropes)(void* a, void* b, NI size) {
	NIM_BOOL result;
	int T1_;
	result = (NIM_BOOL)0;
	T1_ = (int)0;
	T1_ = memcmp(a, b, ((size_t) (size)));
	result = (T1_ == ((NI32) 0));
	return result;
}

static N_INLINE(NIM_BOOL, eqStrings)(NimStringDesc* a, NimStringDesc* b) {
	NIM_BOOL result;
	NIM_BOOL T11_;
{	result = (NIM_BOOL)0;
	{
		if (!(a == b)) goto LA3_;
		result = NIM_TRUE;
		goto BeforeRet_;
	}
	LA3_: ;
	{
		NIM_BOOL T7_;
		T7_ = (NIM_BOOL)0;
		T7_ = (a == NIM_NIL);
		if (T7_) goto LA8_;
		T7_ = (b == NIM_NIL);
		LA8_: ;
		if (!T7_) goto LA9_;
		result = NIM_FALSE;
		goto BeforeRet_;
	}
	LA9_: ;
	T11_ = (NIM_BOOL)0;
	T11_ = ((*a).Sup.len == (*b).Sup.len);
	if (!(T11_)) goto LA12_;
	T11_ = equalMem_fmeFeLBvgmAHG9bC8ETS9bYQropes(((void*) ((*a).data)), ((void*) ((*b).data)), ((NI) ((*a).Sup.len)));
	LA12_: ;
	result = T11_;
	goto BeforeRet_;
	}BeforeRet_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g*, getCallee_8v8U4rPUh2LEtUf9cZrto9bQ)(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n) {
	tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* result;
	result = (tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g*)0;
	{
		NIM_BOOL T3_;
		T3_ = (NIM_BOOL)0;
		T3_ = ((*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 27) || (*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 29) || (*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 30) || (*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 31) || (*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 26) || (*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 28) || (*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 32));
		if (!(T3_)) goto LA4_;
		T3_ = ((*(*n).kindU.S6.sons->data[((NI) 0)]).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 2));
		LA4_: ;
		if (!T3_) goto LA5_;
		result = (*(*n).kindU.S6.sons->data[((NI) 0)]).kindU.S5.ident;
	}
	goto LA1_;
	LA5_: ;
	{
		if (!((*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 2))) goto LA8_;
		result = (*n).kindU.S5.ident;
	}
	goto LA1_;
	LA8_: ;
	{
		NimStringDesc* T11_;
		T11_ = (NimStringDesc*)0;
		T11_ = renderTree_ppjdh9aQ5L0SGPF8yz1gZ9cA(n, 0);
		rawMessage_tBJ8mvo7MzzirsGkrHVc9cw(((tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw) 169), T11_);
	}
	LA1_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg, getFilter_VI3Fiobf4N9aSXR2Q8kXG0A)(tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* ident) {
	tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg result;
{	result = (tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg)0;
	{
		tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg i;
		NI res;
		i = (tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg)0;
		res = ((NI) 0);
		{
			while (1) {
				if (!(res <= ((NI) 3))) goto LA3;
				i = ((tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg) (res));
				{
					NI T6_;
					T6_ = (NI)0;
					T6_ = nsuCmpIgnoreStyle((*ident).s, filterNames_AxTRz7iBqkPgPfZx8TM0IQ[(i)- 0]);
					if (!(T6_ == ((NI) 0))) goto LA7_;
					result = i;
					goto BeforeRet_;
				}
				LA7_: ;
				res += ((NI) 1);
			} LA3: ;
		}
	}
	result = ((tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg) 0);
	}BeforeRet_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw, getParser_hTsVGKyR7WIUC8NJAMIjvQ)(tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* ident) {
	tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw result;
{	result = (tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw)0;
	{
		tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw i;
		NI res;
		i = (tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw)0;
		res = ((NI) 0);
		{
			while (1) {
				if (!(res <= ((NI) 3))) goto LA3;
				i = ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) (res));
				{
					NI T6_;
					T6_ = (NI)0;
					T6_ = nsuCmpIgnoreStyle((*ident).s, parserNames_IVRWib6Nt9c9cDYSS669cL5mA[(i)- 0]);
					if (!(T6_ == ((NI) 0))) goto LA7_;
					result = i;
					goto BeforeRet_;
				}
				LA7_: ;
				res += ((NI) 1);
			} LA3: ;
		}
	}
	rawMessage_tBJ8mvo7MzzirsGkrHVc9cw(((tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw) 31), (*ident).s);
	}BeforeRet_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, applyFilter_9cHsu5TuPlpg9bEC9cADFtBCA)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n, NimStringDesc* filename, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* stdin_0) {
	tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* result;
	tyObject_TIdent_4umxGerWTHGPwUms7Yqu3g* ident;
	tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg f;
	result = (tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*)0;
	ident = getCallee_8v8U4rPUh2LEtUf9cZrto9bQ(n);
	f = getFilter_VI3Fiobf4N9aSXR2Q8kXG0A(ident);
	switch (f) {
	case ((tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg) 0):
	{
		(*p).skin = getParser_hTsVGKyR7WIUC8NJAMIjvQ(ident);
		result = stdin_0;
	}
	break;
	case ((tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg) 1):
	{
		result = filterTmpl_JvVu6X7Xrt789cwD0XA6mWg(stdin_0, filename, n);
	}
	break;
	case ((tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg) 3):
	{
		result = filterStrip_8vZ6X8KZZNI4xsTx2A9bPBw(stdin_0, filename, n);
	}
	break;
	case ((tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg) 2):
	{
		result = filterReplace_8vZ6X8KZZNI4xsTx2A9bPBw_2(stdin_0, filename, n);
	}
	break;
	}
	{
		if (!!((f == ((tyEnum_TFilterKind_mET0MuvrWCLPKR0e9cWMjNg) 0)))) goto LA7_;
		{
			tyArray_8ZvwQIddfpj2THRVPsFzIQ T13_;
			tyArray_8ZvwQIddfpj2THRVPsFzIQ T14_;
			if (!((gNotes_ra0BBMaJz6cOxn1JA3c6Bg &((NU64)1<<((NU)((((tyEnum_TMsgKind_VhF2u8Sb9c3Fk8NMu6WUVoA) 281)- 241))&63U)))!=0)) goto LA11_;
			memset((void*)T13_, 0, sizeof(T13_));
			rawMessage_wSQLHRsYvHJ4DSWgdFrFaA(((tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw) 281), T13_, 0);
			msgWriteln_mpdiFCyqIWmTQYjT6Mj9c6A((*result).s, 0);
			memset((void*)T14_, 0, sizeof(T14_));
			rawMessage_wSQLHRsYvHJ4DSWgdFrFaA(((tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw) 282), T14_, 0);
		}
		LA11_: ;
	}
	LA7_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*, evalPipe_nVUUGAijyBdiAxOhXa9atMg)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n, NimStringDesc* filename, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* start) {
	tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* result;
{	result = (tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*)0;
	result = start;
	{
		if (!((*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 1))) goto LA3_;
		goto BeforeRet_;
	}
	LA3_: ;
	{
		NIM_BOOL T7_;
		NIM_BOOL T8_;
		T7_ = (NIM_BOOL)0;
		T8_ = (NIM_BOOL)0;
		T8_ = ((*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 29));
		if (!(T8_)) goto LA9_;
		T8_ = ((*(*n).kindU.S6.sons->data[((NI) 0)]).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 2));
		LA9_: ;
		T7_ = T8_;
		if (!(T7_)) goto LA10_;
		T7_ = eqStrings((*(*(*n).kindU.S6.sons->data[((NI) 0)]).kindU.S5.ident).s, ((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_6));
		LA10_: ;
		if (!T7_) goto LA11_;
		{
			NI i;
			NI res;
			i = (NI)0;
			res = ((NI) 1);
			{
				while (1) {
					if (!(res <= ((NI) 2))) goto LA15;
					i = res;
					{
						if (!((*(*n).kindU.S6.sons->data[i]).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 29))) goto LA18_;
						result = evalPipe_nVUUGAijyBdiAxOhXa9atMg(p, (*n).kindU.S6.sons->data[i], filename, result);
					}
					goto LA16_;
					LA18_: ;
					{
						result = applyFilter_9cHsu5TuPlpg9bEC9cADFtBCA(p, (*n).kindU.S6.sons->data[i], filename, result);
					}
					LA16_: ;
					res += ((NI) 1);
				} LA15: ;
			}
		}
	}
	goto LA5_;
	LA11_: ;
	{
		if (!((*n).kind == ((tyEnum_TNodeKind_G4E4Gxe7oI2Cm03rkiOzQw) 115))) goto LA22_;
		result = evalPipe_nVUUGAijyBdiAxOhXa9atMg(p, (*n).kindU.S6.sons->data[((NI) 0)], filename, result);
	}
	goto LA5_;
	LA22_: ;
	{
		result = applyFilter_9cHsu5TuPlpg9bEC9cADFtBCA(p, n, filename, result);
	}
	LA5_: ;
	}BeforeRet_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(void, openParsers_zDBDS8Km3Tchi1ohPVieKQ)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p, NI32 fileIdx, tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* inputstream, tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* cache) {
	tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* s;
	NimStringDesc* filename;
	tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* pipe;
	s = (tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*)0;
	(*p).skin = ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 0);
	filename = toFullPathConsiderDirty_KZnzGw9baMUf9ad9aixRtHmqg_2(fileIdx);
	pipe = parsePipe_bJSds72kKu77CwGx8lNYmA(filename, inputstream, cache);
	{
		if (!!((pipe == NIM_NIL))) goto LA3_;
		s = evalPipe_nVUUGAijyBdiAxOhXa9atMg(p, pipe, filename, inputstream);
	}
	goto LA1_;
	LA3_: ;
	{
		s = inputstream;
	}
	LA1_: ;
	switch ((*p).skin) {
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 0):
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 2):
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 3):
	{
		openParser_AytEkdefQ9bdVwGj33lUaUw((&(*p).parser), fileIdx, s, cache, NIM_FALSE);
	}
	break;
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 1):
	{
		openParser_AytEkdefQ9bdVwGj33lUaUw((&(*p).parser), fileIdx, s, cache, NIM_TRUE);
	}
	break;
	}
}

N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parseAll_N9cl8bNz6TaGrhhLXmkyhrw)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p) {
	tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* result;
	result = (tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*)0;
	switch ((*p).skin) {
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 0):
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 1):
	{
		result = parseAll_x3UAdSvBfIIO33m4gWdOPg((&(*p).parser));
	}
	break;
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 2):
	{
		result = parseAll_e6i72kHohchMxvc8wSe9a8Q((&(*p).parser));
	}
	break;
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 3):
	{
		internalError_5XY9cUy7hZmUusM38U9cYYdw(((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_15));
		result = emptyNode_69ccLGuQ2mITw7zylZYtWcA;
	}
	break;
	}
	return result;
}

N_LIB_PRIVATE N_NIMCALL(void, closeParsers_aZMERNSTUyTfW9aaFR9bAn9aQ)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p) {
	closeParser_Bv6bIlAg2H4GfVH07sPwUw((&(*p).parser));
}

N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parseFile_9cEZ7X5V9c6ooHZhVrYd0X7Q)(NI32 fileIdx, tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* cache) {
	tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* result;
	tyObject_TParsers_WENTuyElSRFloaVOQEDvMg p;
	FILE* f;
	NimStringDesc* filename;
	tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw* T6_;
{	result = (tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*)0;
	memset((void*)(&p), 0, sizeof(p));
	objectInit((&p), (&NTI_WENTuyElSRFloaVOQEDvMg_));
	f = (FILE*)0;
	filename = toFullPathConsiderDirty_KZnzGw9baMUf9ad9aixRtHmqg_2(fileIdx);
	{
		NIM_BOOL T3_;
		T3_ = (NIM_BOOL)0;
		T3_ = open_sEp0GH2306oGo9bqBpj5oTQ(&f, filename, ((tyEnum_FileMode_fVUBHvW79bXUw1j55Oo9avSQ) 0), ((NI) -1));
		if (!!(T3_)) goto LA4_;
		rawMessage_tBJ8mvo7MzzirsGkrHVc9cw(((tyEnum_TMsgKind_IGAWgv9aR2KqPKJfPZPEWaw) 3), filename);
		goto BeforeRet_;
	}
	LA4_: ;
	T6_ = (tyObject_TLLStream_IHsOGFu33dIY69a9bLlFHlHw*)0;
	T6_ = llStreamOpen_8hTxoBHhwtwZR9cM9bBLMsCQ(f);
	openParsers_zDBDS8Km3Tchi1ohPVieKQ((&p), fileIdx, T6_, cache);
	result = parseAll_N9cl8bNz6TaGrhhLXmkyhrw((&p));
	closeParsers_aZMERNSTUyTfW9aaFR9bAn9aQ((&p));
	}BeforeRet_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, parseTopLevelStmt_N9cl8bNz6TaGrhhLXmkyhrw_2)(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg* p) {
	tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* result;
	result = (tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*)0;
	switch ((*p).skin) {
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 0):
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 1):
	{
		result = parseTopLevelStmt_x3UAdSvBfIIO33m4gWdOPg_40((&(*p).parser));
	}
	break;
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 2):
	{
		result = parseTopLevelStmt_e6i72kHohchMxvc8wSe9a8Q_42((&(*p).parser));
	}
	break;
	case ((tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw) 3):
	{
		internalError_5XY9cUy7hZmUusM38U9cYYdw(((NimStringDesc*) &TM_Furs9bKK6tVLoyofH3f4bRw_15));
		result = emptyNode_69ccLGuQ2mITw7zylZYtWcA;
	}
	break;
	}
	return result;
}
NIM_EXTERNC N_NOINLINE(void, compiler_syntaxesInit000)(void) {
}

NIM_EXTERNC N_NOINLINE(void, compiler_syntaxesDatInit000)(void) {
static TNimNode* TM_Furs9bKK6tVLoyofH3f4bRw_2[2];
static TNimNode* TM_Furs9bKK6tVLoyofH3f4bRw_3[4];
NI TM_Furs9bKK6tVLoyofH3f4bRw_5;
static char* NIM_CONST TM_Furs9bKK6tVLoyofH3f4bRw_4[4] = {
"skinStandard", 
"skinStrongSpaces", 
"skinBraces", 
"skinEndX"};
static TNimNode TM_Furs9bKK6tVLoyofH3f4bRw_0[8];
NTI_WENTuyElSRFloaVOQEDvMg_.size = sizeof(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg);
NTI_WENTuyElSRFloaVOQEDvMg_.kind = 18;
NTI_WENTuyElSRFloaVOQEDvMg_.base = 0;
TM_Furs9bKK6tVLoyofH3f4bRw_2[0] = &TM_Furs9bKK6tVLoyofH3f4bRw_0[1];
NTI_wHYLpKaSFkZsAwL9crNQqGw_.size = sizeof(tyEnum_TParserKind_wHYLpKaSFkZsAwL9crNQqGw);
NTI_wHYLpKaSFkZsAwL9crNQqGw_.kind = 14;
NTI_wHYLpKaSFkZsAwL9crNQqGw_.base = 0;
NTI_wHYLpKaSFkZsAwL9crNQqGw_.flags = 3;
for (TM_Furs9bKK6tVLoyofH3f4bRw_5 = 0; TM_Furs9bKK6tVLoyofH3f4bRw_5 < 4; TM_Furs9bKK6tVLoyofH3f4bRw_5++) {
TM_Furs9bKK6tVLoyofH3f4bRw_0[TM_Furs9bKK6tVLoyofH3f4bRw_5+2].kind = 1;
TM_Furs9bKK6tVLoyofH3f4bRw_0[TM_Furs9bKK6tVLoyofH3f4bRw_5+2].offset = TM_Furs9bKK6tVLoyofH3f4bRw_5;
TM_Furs9bKK6tVLoyofH3f4bRw_0[TM_Furs9bKK6tVLoyofH3f4bRw_5+2].name = TM_Furs9bKK6tVLoyofH3f4bRw_4[TM_Furs9bKK6tVLoyofH3f4bRw_5];
TM_Furs9bKK6tVLoyofH3f4bRw_3[TM_Furs9bKK6tVLoyofH3f4bRw_5] = &TM_Furs9bKK6tVLoyofH3f4bRw_0[TM_Furs9bKK6tVLoyofH3f4bRw_5+2];
}
TM_Furs9bKK6tVLoyofH3f4bRw_0[6].len = 4; TM_Furs9bKK6tVLoyofH3f4bRw_0[6].kind = 2; TM_Furs9bKK6tVLoyofH3f4bRw_0[6].sons = &TM_Furs9bKK6tVLoyofH3f4bRw_3[0];
NTI_wHYLpKaSFkZsAwL9crNQqGw_.node = &TM_Furs9bKK6tVLoyofH3f4bRw_0[6];
TM_Furs9bKK6tVLoyofH3f4bRw_0[1].kind = 1;
TM_Furs9bKK6tVLoyofH3f4bRw_0[1].offset = offsetof(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg, skin);
TM_Furs9bKK6tVLoyofH3f4bRw_0[1].typ = (&NTI_wHYLpKaSFkZsAwL9crNQqGw_);
TM_Furs9bKK6tVLoyofH3f4bRw_0[1].name = "skin";
TM_Furs9bKK6tVLoyofH3f4bRw_2[1] = &TM_Furs9bKK6tVLoyofH3f4bRw_0[7];
TM_Furs9bKK6tVLoyofH3f4bRw_0[7].kind = 1;
TM_Furs9bKK6tVLoyofH3f4bRw_0[7].offset = offsetof(tyObject_TParsers_WENTuyElSRFloaVOQEDvMg, parser);
TM_Furs9bKK6tVLoyofH3f4bRw_0[7].typ = (&NTI_c38t9cDVS8o9b29cOovKwkANw_);
TM_Furs9bKK6tVLoyofH3f4bRw_0[7].name = "parser";
TM_Furs9bKK6tVLoyofH3f4bRw_0[0].len = 2; TM_Furs9bKK6tVLoyofH3f4bRw_0[0].kind = 2; TM_Furs9bKK6tVLoyofH3f4bRw_0[0].sons = &TM_Furs9bKK6tVLoyofH3f4bRw_2[0];
NTI_WENTuyElSRFloaVOQEDvMg_.node = &TM_Furs9bKK6tVLoyofH3f4bRw_0[0];
}
