/* Generated by Nim Compiler v0.20.0 */
/*   (c) 2019 Andreas Rumpf */
/* The generated code is subject to the original license. */
#define NIM_INTBITS 32

#include "nimbase.h"
#include <string.h>
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
#undef far
#undef powerpc
#undef unix
#define nimfr_(x, y)
#define nimln_(x, y)
typedef struct tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw;
typedef struct tyObject_TContext_C9bB2okDBl3OKGUBiY5k5Ug tyObject_TContext_C9bB2okDBl3OKGUBiY5k5Ug;
typedef struct tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw;
typedef struct tyObject_TSym_JpsEh5i1AcKChGYbg7aV4w tyObject_TSym_JpsEh5i1AcKChGYbg7aV4w;
typedef struct tyTuple_POdQNEM9bqRXZxVjuyaP2MQ tyTuple_POdQNEM9bqRXZxVjuyaP2MQ;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef N_NIMCALL_PTR(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, tyProc_RcJNn9bSvWdJgUmA1O6sbHA) (tyObject_TContext_C9bB2okDBl3OKGUBiY5k5Ug* c, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n);
struct TGenericSeq {
NI len;
NI reserved;
};
struct NimStringDesc {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
struct tyTuple_POdQNEM9bqRXZxVjuyaP2MQ {
NimStringDesc* Field0;
NimStringDesc* Field1;
NimStringDesc* Field2;
tyProc_RcJNn9bSvWdJgUmA1O6sbHA Field3;
};
typedef tyTuple_POdQNEM9bqRXZxVjuyaP2MQ tyArray_hieh1IEVE9bl3WbZwL0hYdA[2];
static N_INLINE(void, nimZeroMem)(void* p, NI size);
static N_INLINE(void, nimSetMem_JE6t4x7Z3v2iVz27Nx0MRAmemory)(void* a, int v, NI size);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, iterToProcImpl_btx5NTZO5L9a6BLvqVh3UTw)(tyObject_TContext_C9bB2okDBl3OKGUBiY5k5Ug* c, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw*, semLocals_UZKPH7X5GcC9bXeyF6OaeNg)(tyObject_TContext_C9bB2okDBl3OKGUBiY5k5Ug* c, tyObject_TNode_bROa11lyF5vxEN9aYNbHmhw* n);
N_NIMCALL(NimStringDesc*, copyString)(NimStringDesc* src);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, pluginMatches_J9a0UG4F39czom3NeeNDFTow)(tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* ic, tyTuple_POdQNEM9bqRXZxVjuyaP2MQ p, tyObject_TSym_JpsEh5i1AcKChGYbg7aV4w* s);
static N_INLINE(NI, addInt)(NI a, NI b);
N_NOINLINE(void, raiseOverflow)(void);
STRING_LITERAL(TM_iLzrQjTMtHjOSlNDU8lfsw_2, "stdlib", 6);
STRING_LITERAL(TM_iLzrQjTMtHjOSlNDU8lfsw_3, "system", 6);
STRING_LITERAL(TM_iLzrQjTMtHjOSlNDU8lfsw_4, "iterToProc", 10);
STRING_LITERAL(TM_iLzrQjTMtHjOSlNDU8lfsw_5, "locals", 6);
NIM_CONST tyArray_hieh1IEVE9bl3WbZwL0hYdA plugins_6px53mvNYhxS9cwAd6iLcwg = {{((NimStringDesc*) &TM_iLzrQjTMtHjOSlNDU8lfsw_2),
((NimStringDesc*) &TM_iLzrQjTMtHjOSlNDU8lfsw_3),
((NimStringDesc*) &TM_iLzrQjTMtHjOSlNDU8lfsw_4),
iterToProcImpl_btx5NTZO5L9a6BLvqVh3UTw}
,
{((NimStringDesc*) &TM_iLzrQjTMtHjOSlNDU8lfsw_2),
((NimStringDesc*) &TM_iLzrQjTMtHjOSlNDU8lfsw_3),
((NimStringDesc*) &TM_iLzrQjTMtHjOSlNDU8lfsw_5),
semLocals_UZKPH7X5GcC9bXeyF6OaeNg}
}
;

static N_INLINE(void, nimSetMem_JE6t4x7Z3v2iVz27Nx0MRAmemory)(void* a, int v, NI size) {
	void* T1_;
	T1_ = (void*)0;
	T1_ = memset(a, v, ((size_t) (size)));
}

static N_INLINE(void, nimZeroMem)(void* p, NI size) {
	nimSetMem_JE6t4x7Z3v2iVz27Nx0MRAmemory(p, ((int) 0), size);
}

static N_INLINE(NI, addInt)(NI a, NI b) {
	NI result;
{	result = (NI)0;
	result = (NI)((NU32)(a) + (NU32)(b));
	{
		NIM_BOOL T3_;
		T3_ = (NIM_BOOL)0;
		T3_ = (((NI) 0) <= (NI)(result ^ a));
		if (T3_) goto LA4_;
		T3_ = (((NI) 0) <= (NI)(result ^ b));
		LA4_: ;
		if (!T3_) goto LA5_;
		goto BeforeRet_;
	}
	LA5_: ;
	raiseOverflow();
	}BeforeRet_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(tyProc_RcJNn9bSvWdJgUmA1O6sbHA, getPlugin_CPe4POy5nrj1aG8wD32ycw)(tyObject_IdentCachecolonObjectType__TzLHS09bRH9a0TYLs39cqcNaw* ic, tyObject_TSym_JpsEh5i1AcKChGYbg7aV4w* fn) {
	tyProc_RcJNn9bSvWdJgUmA1O6sbHA result;
{	result = (tyProc_RcJNn9bSvWdJgUmA1O6sbHA)0;
	{
		tyTuple_POdQNEM9bqRXZxVjuyaP2MQ p;
		NI i;
		nimZeroMem((void*)(&p), sizeof(tyTuple_POdQNEM9bqRXZxVjuyaP2MQ));
		i = ((NI) 0);
		{
			if (!(((NI) (i)) <= ((NI) 1))) goto LA4_;
			{
				while (1) {
					NI TM_iLzrQjTMtHjOSlNDU8lfsw_6;
					p.Field0 = copyString(plugins_6px53mvNYhxS9cwAd6iLcwg[(i)- 0].Field0);
					p.Field1 = copyString(plugins_6px53mvNYhxS9cwAd6iLcwg[(i)- 0].Field1);
					p.Field2 = copyString(plugins_6px53mvNYhxS9cwAd6iLcwg[(i)- 0].Field2);
					p.Field3 = plugins_6px53mvNYhxS9cwAd6iLcwg[(i)- 0].Field3;
					{
						NIM_BOOL T10_;
						T10_ = (NIM_BOOL)0;
						T10_ = pluginMatches_J9a0UG4F39czom3NeeNDFTow(ic, p, fn);
						if (!T10_) goto LA11_;
						result = p.Field3;
						goto BeforeRet_;
					}
					LA11_: ;
					{
						if (!(((NI) 1) <= ((NI) (i)))) goto LA15_;
						goto LA6;
					}
					LA15_: ;
					TM_iLzrQjTMtHjOSlNDU8lfsw_6 = addInt(i, ((NI) 1));
					if (TM_iLzrQjTMtHjOSlNDU8lfsw_6 < 0 || TM_iLzrQjTMtHjOSlNDU8lfsw_6 > 1) raiseOverflow();
					i = (NI)(TM_iLzrQjTMtHjOSlNDU8lfsw_6);
				}
			} LA6: ;
		}
		LA4_: ;
	}
	result = NIM_NIL;
	goto BeforeRet_;
	}BeforeRet_: ;
	return result;
}