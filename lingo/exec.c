#include "lingo.h"
static inline uint32_t getLong(lingo_ctx* ctx) // get the little endian 32-bit number following the opcode
{
  uint32_t pc=ctx->regs.pc;
  uint32_t ret=ctx->program[pc+4];
  ret |= ctx->program[pc+3] << 8;
  ret |= ctx->program[pc+2] << 16;
  ret |= ctx->program[pc+1] << 24;
  return ret;
}
static void exec_instr_00(lingo_ctx* ctx)
{
  asm volatile("nop");
}
static void exec_instr_01(lingo_ctx* ctx)
{
  ctx->regs.ra=getLong(ctx);
}
static void exec_instr_02(lingo_ctx* ctx)
{  
  ctx->regs.rb=getLong(ctx);
}
static void exec_instr_03(lingo_ctx* ctx)
{ 
  ctx->regs.rc=getLong(ctx);
}
static void exec_instr_04(lingo_ctx* ctx)
{
  ctx->regs.rd=getLong(ctx);
}
static void exec_instr_05(lingo_ctx* ctx)
{
  ctx->regs.ra=ctx->program[getLong(ctx)];
}
static void exec_instr_06(lingo_ctx* ctx)
{
  ctx->regs.rb=ctx->program[getLong(ctx)];
}
static void exec_instr_07(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->program[getLong(ctx)];
}
static void exec_instr_08(lingo_ctx* ctx)
{
  ctx->regs.rd=ctx->program[getLong(ctx)];
}

static void exec_instr_09(lingo_ctx* ctx)
{
  ctx->regs.rb=ctx->regs.ra;
}
static void exec_instr_0A(lingo_ctx* ctx)
{
  ctx->regs.ra=ctx->regs.rb;
}
static void exec_instr_0B(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->regs.ra;
}
static void exec_instr_0C(lingo_ctx* ctx)
{
  ctx->regs.ra=ctx->regs.rc;
}
static void exec_instr_0D(lingo_ctx* ctx)
{
  ctx->regs.rd=ctx->regs.ra;
}
static void exec_instr_0E(lingo_ctx* ctx)
{
  ctx->regs.ra=ctx->regs.rd;
}
static void exec_instr_0F(lingo_ctx* ctx)
{
  ctx->regs.rb=ctx->regs.rc;
}
static void exec_instr_10(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->regs.rb;
}
static void exec_instr_11(lingo_ctx* ctx)
{
  ctx->regs.rd=ctx->regs.rb;
}
static void exec_instr_12(lingo_ctx* ctx)
{
  ctx->regs.rb=ctx->regs.rd;
}
static void exec_instr_13(lingo_ctx* ctx)
{
  ctx->regs.rd=ctx->regs.rc;
}
static void exec_instr_14(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->regs.rd;
}
static void exec_instr_15(lingo_ctx* ctx)
{
  ctx->regs.rb=ctx->program[ctx->regs.ra];
}
static void exec_instr_16(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->program[ctx->regs.ra];
}
static void exec_instr_17(lingo_ctx* ctx)
{
  
  ctx->regs.rc=ctx->program[ctx->regs.ra];
}
static void exec_instr_18(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->program[ctx->regs.ra];
}
static void exec_instr_19(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->program[ctx->regs.ra];
}
static void exec_instr_1A(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->program[ctx->regs.ra];
}
static void exec_instr_1B(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->program[ctx->regs.ra];
}
static void exec_instr_1C(lingo_ctx* ctx)
{
  ctx->regs.rc=ctx->program[ctx->regs.ra];
}
static void exec_instr_1D(lingo_ctx* ctx)
{
}
static void exec_instr_1E(lingo_ctx* ctx)
{
}
static void exec_instr_1F(lingo_ctx* ctx)
{
}
static void exec_instr_20(lingo_ctx* ctx)
{
}
static void exec_instr_21(lingo_ctx* ctx)
{
}
static void exec_instr_22(lingo_ctx* ctx)
{
}
static void exec_instr_23(lingo_ctx* ctx)
{
}
static void exec_instr_24(lingo_ctx* ctx)
{
}
static void exec_instr_25(lingo_ctx* ctx)
{
}
static void exec_instr_26(lingo_ctx* ctx)
{
}
static void exec_instr_27(lingo_ctx* ctx)
{
}
static void exec_instr_28(lingo_ctx* ctx)
{
}
static void exec_instr_29(lingo_ctx* ctx)
{
}
static void exec_instr_2A(lingo_ctx* ctx)
{
}
static void exec_instr_2B(lingo_ctx* ctx)
{
}
static void exec_instr_2C(lingo_ctx* ctx)
{
}
static void exec_instr_2D(lingo_ctx* ctx)
{
}
static void exec_instr_2E(lingo_ctx* ctx)
{
}
static void exec_instr_2F(lingo_ctx* ctx)
{
}
static void exec_instr_30(lingo_ctx* ctx)
{
}
static void exec_instr_31(lingo_ctx* ctx)
{
}
static void exec_instr_32(lingo_ctx* ctx)
{
}
static void exec_instr_33(lingo_ctx* ctx)
{
}
static void exec_instr_34(lingo_ctx* ctx)
{
}
static void exec_instr_35(lingo_ctx* ctx)
{
}
static void exec_instr_36(lingo_ctx* ctx)
{
}
static void exec_instr_37(lingo_ctx* ctx)
{
}
static void exec_instr_38(lingo_ctx* ctx)
{
}
static void exec_instr_39(lingo_ctx* ctx)
{
}
static void exec_instr_3A(lingo_ctx* ctx)
{
}
static void exec_instr_3B(lingo_ctx* ctx)
{
}
static void exec_instr_3C(lingo_ctx* ctx)
{
}
static void exec_instr_3D(lingo_ctx* ctx)
{
}
static void exec_instr_3E(lingo_ctx* ctx)
{
}
static void exec_instr_3F(lingo_ctx* ctx)
{
}
static void exec_instr_40(lingo_ctx* ctx)
{
}
static void exec_instr_41(lingo_ctx* ctx)
{
}
static void exec_instr_42(lingo_ctx* ctx)
{
}
static void exec_instr_43(lingo_ctx* ctx)
{
}
static void exec_instr_44(lingo_ctx* ctx)
{
}
static void exec_instr_45(lingo_ctx* ctx)
{
}
static void exec_instr_46(lingo_ctx* ctx)
{
}
static void exec_instr_47(lingo_ctx* ctx)
{
}
static void exec_instr_48(lingo_ctx* ctx)
{
}
static void exec_instr_49(lingo_ctx* ctx)
{
}
static void exec_instr_4A(lingo_ctx* ctx)
{
}
static void exec_instr_4B(lingo_ctx* ctx)
{
}
static void exec_instr_4C(lingo_ctx* ctx)
{
}
static void exec_instr_4D(lingo_ctx* ctx)
{
}
static void exec_instr_4E(lingo_ctx* ctx)
{
}
static void exec_instr_4F(lingo_ctx* ctx)
{
}
static void exec_instr_50(lingo_ctx* ctx)
{
}
static void exec_instr_51(lingo_ctx* ctx)
{
}
static void exec_instr_52(lingo_ctx* ctx)
{
}
static void exec_instr_53(lingo_ctx* ctx)
{
}
static void exec_instr_54(lingo_ctx* ctx)
{
}
static void exec_instr_55(lingo_ctx* ctx)
{
}
static void exec_instr_56(lingo_ctx* ctx)
{
}
static void exec_instr_57(lingo_ctx* ctx)
{
}
static void exec_instr_58(lingo_ctx* ctx)
{
}
static void exec_instr_59(lingo_ctx* ctx)
{
}
static void exec_instr_5A(lingo_ctx* ctx)
{
}
static void exec_instr_5B(lingo_ctx* ctx)
{
}
static void exec_instr_5C(lingo_ctx* ctx)
{
}
static void exec_instr_5D(lingo_ctx* ctx)
{
}
static void exec_instr_5E(lingo_ctx* ctx)
{
}
static void exec_instr_5F(lingo_ctx* ctx)
{
}
static void exec_instr_60(lingo_ctx* ctx)
{
}
static void exec_instr_61(lingo_ctx* ctx)
{
}
static void exec_instr_62(lingo_ctx* ctx)
{
}
static void exec_instr_63(lingo_ctx* ctx)
{
}
static void exec_instr_64(lingo_ctx* ctx)
{
}
static void exec_instr_65(lingo_ctx* ctx)
{
}
static void exec_instr_66(lingo_ctx* ctx)
{
}
static void exec_instr_67(lingo_ctx* ctx)
{
}
static void exec_instr_68(lingo_ctx* ctx)
{
}
static void exec_instr_69(lingo_ctx* ctx)
{
}
static void exec_instr_6A(lingo_ctx* ctx)
{
}
static void exec_instr_6B(lingo_ctx* ctx)
{
}
static void exec_instr_6C(lingo_ctx* ctx)
{
}
static void exec_instr_6D(lingo_ctx* ctx)
{
}
static void exec_instr_6E(lingo_ctx* ctx)
{
}
static void exec_instr_6F(lingo_ctx* ctx)
{
}
static void exec_instr_70(lingo_ctx* ctx)
{
}
static void exec_instr_71(lingo_ctx* ctx)
{
}
static void exec_instr_72(lingo_ctx* ctx)
{
}
static void exec_instr_73(lingo_ctx* ctx)
{
}
static void exec_instr_74(lingo_ctx* ctx)
{
}
static void exec_instr_75(lingo_ctx* ctx)
{
}
static void exec_instr_76(lingo_ctx* ctx)
{
}
static void exec_instr_77(lingo_ctx* ctx)
{
}
static void exec_instr_78(lingo_ctx* ctx)
{
}
static void exec_instr_79(lingo_ctx* ctx)
{
}
static void exec_instr_7A(lingo_ctx* ctx)
{
}
static void exec_instr_7B(lingo_ctx* ctx)
{
}
static void exec_instr_7C(lingo_ctx* ctx)
{
}
static void exec_instr_7D(lingo_ctx* ctx)
{
}
static void exec_instr_7E(lingo_ctx* ctx)
{
}
static void exec_instr_7F(lingo_ctx* ctx)
{
}
static void exec_instr_80(lingo_ctx* ctx)
{
}
static void exec_instr_81(lingo_ctx* ctx)
{
}
static void exec_instr_82(lingo_ctx* ctx)
{
}
static void exec_instr_83(lingo_ctx* ctx)
{
}
static void exec_instr_84(lingo_ctx* ctx)
{
}
static void exec_instr_85(lingo_ctx* ctx)
{
}
static void exec_instr_86(lingo_ctx* ctx)
{
}
static void exec_instr_87(lingo_ctx* ctx)
{
}
static void exec_instr_88(lingo_ctx* ctx)
{
}
static void exec_instr_89(lingo_ctx* ctx)
{
}
static void exec_instr_8A(lingo_ctx* ctx)
{
}
static void exec_instr_8B(lingo_ctx* ctx)
{
}
static void exec_instr_8C(lingo_ctx* ctx)
{
}
static void exec_instr_8D(lingo_ctx* ctx)
{
}
static void exec_instr_8E(lingo_ctx* ctx)
{
}
static void exec_instr_8F(lingo_ctx* ctx)
{
}
static void exec_instr_90(lingo_ctx* ctx)
{
}
static void exec_instr_91(lingo_ctx* ctx)
{
}
static void exec_instr_92(lingo_ctx* ctx)
{
}
static void exec_instr_93(lingo_ctx* ctx)
{
}
static void exec_instr_94(lingo_ctx* ctx)
{
}
static void exec_instr_95(lingo_ctx* ctx)
{
}
static void exec_instr_96(lingo_ctx* ctx)
{
}
static void exec_instr_97(lingo_ctx* ctx)
{
}
static void exec_instr_98(lingo_ctx* ctx)
{
}
static void exec_instr_99(lingo_ctx* ctx)
{
}
static void exec_instr_9A(lingo_ctx* ctx)
{
}
static void exec_instr_9B(lingo_ctx* ctx)
{
}
static void exec_instr_9C(lingo_ctx* ctx)
{
}
static void exec_instr_9D(lingo_ctx* ctx)
{
}
static void exec_instr_9E(lingo_ctx* ctx)
{
}
static void exec_instr_9F(lingo_ctx* ctx)
{
}
static void exec_instr_A0(lingo_ctx* ctx)
{
}
static void exec_instr_A1(lingo_ctx* ctx)
{
}
static void exec_instr_A2(lingo_ctx* ctx)
{
}
static void exec_instr_A3(lingo_ctx* ctx)
{
}
static void exec_instr_A4(lingo_ctx* ctx)
{
}
static void exec_instr_A5(lingo_ctx* ctx)
{
}
static void exec_instr_A6(lingo_ctx* ctx)
{
}
static void exec_instr_A7(lingo_ctx* ctx)
{
}
static void exec_instr_A8(lingo_ctx* ctx)
{
}
static void exec_instr_A9(lingo_ctx* ctx)
{
}
static void exec_instr_AA(lingo_ctx* ctx)
{
}
static void exec_instr_AB(lingo_ctx* ctx)
{
}
static void exec_instr_AC(lingo_ctx* ctx)
{
}
static void exec_instr_AD(lingo_ctx* ctx)
{
}
static void exec_instr_AE(lingo_ctx* ctx)
{
}
static void exec_instr_AF(lingo_ctx* ctx)
{
}
static void exec_instr_B0(lingo_ctx* ctx)
{
}
static void exec_instr_B1(lingo_ctx* ctx)
{
}
static void exec_instr_B2(lingo_ctx* ctx)
{
}
static void exec_instr_B3(lingo_ctx* ctx)
{
}
static void exec_instr_B4(lingo_ctx* ctx)
{
}
static void exec_instr_B5(lingo_ctx* ctx)
{
}
static void exec_instr_B6(lingo_ctx* ctx)
{
}
static void exec_instr_B7(lingo_ctx* ctx)
{
}
static void exec_instr_B8(lingo_ctx* ctx)
{
}
static void exec_instr_B9(lingo_ctx* ctx)
{
}
static void exec_instr_BA(lingo_ctx* ctx)
{
}
static void exec_instr_BB(lingo_ctx* ctx)
{
}
static void exec_instr_BC(lingo_ctx* ctx)
{
}
static void exec_instr_BD(lingo_ctx* ctx)
{
}
static void exec_instr_BE(lingo_ctx* ctx)
{
}
static void exec_instr_BF(lingo_ctx* ctx)
{
}
static void exec_instr_C0(lingo_ctx* ctx)
{
}
static void exec_instr_C1(lingo_ctx* ctx)
{
}
static void exec_instr_C2(lingo_ctx* ctx)
{
}
static void exec_instr_C3(lingo_ctx* ctx)
{
}
static void exec_instr_C4(lingo_ctx* ctx)
{
}
static void exec_instr_C5(lingo_ctx* ctx)
{
}
static void exec_instr_C6(lingo_ctx* ctx)
{
}
static void exec_instr_C7(lingo_ctx* ctx)
{
}
static void exec_instr_C8(lingo_ctx* ctx)
{
}
static void exec_instr_C9(lingo_ctx* ctx)
{
}
static void exec_instr_CA(lingo_ctx* ctx)
{
}
static void exec_instr_CB(lingo_ctx* ctx)
{
}
static void exec_instr_CC(lingo_ctx* ctx)
{
}
static void exec_instr_CD(lingo_ctx* ctx)
{
}
static void exec_instr_CE(lingo_ctx* ctx)
{
}
static void exec_instr_CF(lingo_ctx* ctx)
{
}
static void exec_instr_D0(lingo_ctx* ctx)
{
}
static void exec_instr_D1(lingo_ctx* ctx)
{
}
static void exec_instr_D2(lingo_ctx* ctx)
{
}
static void exec_instr_D3(lingo_ctx* ctx)
{
}
static void exec_instr_D4(lingo_ctx* ctx)
{
}
static void exec_instr_D5(lingo_ctx* ctx)
{
}
static void exec_instr_D6(lingo_ctx* ctx)
{
}
static void exec_instr_D7(lingo_ctx* ctx)
{
}
static void exec_instr_D8(lingo_ctx* ctx)
{
}
static void exec_instr_D9(lingo_ctx* ctx)
{
}
static void exec_instr_DA(lingo_ctx* ctx)
{
}
static void exec_instr_DB(lingo_ctx* ctx)
{
}
static void exec_instr_DC(lingo_ctx* ctx)
{
}
static void exec_instr_DD(lingo_ctx* ctx)
{
}
static void exec_instr_DE(lingo_ctx* ctx)
{
}
static void exec_instr_DF(lingo_ctx* ctx)
{
}
static void exec_instr_E0(lingo_ctx* ctx)
{
}
static void exec_instr_E1(lingo_ctx* ctx)
{
}
static void exec_instr_E2(lingo_ctx* ctx)
{
}
static void exec_instr_E3(lingo_ctx* ctx)
{
}
static void exec_instr_E4(lingo_ctx* ctx)
{
}
static void exec_instr_E5(lingo_ctx* ctx)
{
}
static void exec_instr_E6(lingo_ctx* ctx)
{
}
static void exec_instr_E7(lingo_ctx* ctx)
{
}
static void exec_instr_E8(lingo_ctx* ctx)
{
}
static void exec_instr_E9(lingo_ctx* ctx)
{
}
static void exec_instr_EA(lingo_ctx* ctx)
{
}
static void exec_instr_EB(lingo_ctx* ctx)
{
}
static void exec_instr_EC(lingo_ctx* ctx)
{
}
static void exec_instr_ED(lingo_ctx* ctx)
{
}
static void exec_instr_EE(lingo_ctx* ctx)
{
}
static void exec_instr_EF(lingo_ctx* ctx)
{
}
static void exec_instr_F0(lingo_ctx* ctx)
{
}
static void exec_instr_F1(lingo_ctx* ctx)
{
}
static void exec_instr_F2(lingo_ctx* ctx)
{
}
static void exec_instr_F3(lingo_ctx* ctx)
{
}
static void exec_instr_F4(lingo_ctx* ctx)
{
}
static void exec_instr_F5(lingo_ctx* ctx)
{
}
static void exec_instr_F6(lingo_ctx* ctx)
{
}
static void exec_instr_F7(lingo_ctx* ctx)
{
}
static void exec_instr_F8(lingo_ctx* ctx)
{
}
static void exec_instr_F9(lingo_ctx* ctx)
{
}
static void exec_instr_FA(lingo_ctx* ctx)
{
}
static void exec_instr_FB(lingo_ctx* ctx)
{
}
static void exec_instr_FC(lingo_ctx* ctx)
{
}
static void exec_instr_FD(lingo_ctx* ctx)
{
}
static void exec_instr_FE(lingo_ctx* ctx)
{
}
static void exec_instr_FF(lingo_ctx* ctx)
{
}
static void (*lingoExecTable[256])(lingo_ctx*)={
&exec_instr_00, 
&exec_instr_01, 
&exec_instr_02, 
&exec_instr_03, 
&exec_instr_04, 
&exec_instr_05, 
&exec_instr_06, 
&exec_instr_07, 
&exec_instr_08, 
&exec_instr_09, 
&exec_instr_0A, 
&exec_instr_0B, 
&exec_instr_0C, 
&exec_instr_0D, 
&exec_instr_0E, 
&exec_instr_0F, 
&exec_instr_10, 
&exec_instr_11, 
&exec_instr_12, 
&exec_instr_13, 
&exec_instr_14, 
&exec_instr_15, 
&exec_instr_16, 
&exec_instr_17, 
&exec_instr_18, 
&exec_instr_19, 
&exec_instr_1A, 
&exec_instr_1B, 
&exec_instr_1C, 
&exec_instr_1D, 
&exec_instr_1E, 
&exec_instr_1F, 
&exec_instr_20, 
&exec_instr_21, 
&exec_instr_22, 
&exec_instr_23, 
&exec_instr_24, 
&exec_instr_25, 
&exec_instr_26, 
&exec_instr_27, 
&exec_instr_28, 
&exec_instr_29, 
&exec_instr_2A, 
&exec_instr_2B, 
&exec_instr_2C, 
&exec_instr_2D, 
&exec_instr_2E, 
&exec_instr_2F, 
&exec_instr_30, 
&exec_instr_31, 
&exec_instr_32, 
&exec_instr_33, 
&exec_instr_34, 
&exec_instr_35, 
&exec_instr_36, 
&exec_instr_37, 
&exec_instr_38, 
&exec_instr_39, 
&exec_instr_3A, 
&exec_instr_3B, 
&exec_instr_3C, 
&exec_instr_3D, 
&exec_instr_3E, 
&exec_instr_3F, 
&exec_instr_40, 
&exec_instr_41, 
&exec_instr_42, 
&exec_instr_43, 
&exec_instr_44, 
&exec_instr_45, 
&exec_instr_46, 
&exec_instr_47, 
&exec_instr_48, 
&exec_instr_49, 
&exec_instr_4A, 
&exec_instr_4B, 
&exec_instr_4C, 
&exec_instr_4D, 
&exec_instr_4E, 
&exec_instr_4F, 
&exec_instr_50, 
&exec_instr_51, 
&exec_instr_52, 
&exec_instr_53, 
&exec_instr_54, 
&exec_instr_55, 
&exec_instr_56, 
&exec_instr_57, 
&exec_instr_58, 
&exec_instr_59, 
&exec_instr_5A, 
&exec_instr_5B, 
&exec_instr_5C, 
&exec_instr_5D, 
&exec_instr_5E, 
&exec_instr_5F, 
&exec_instr_60, 
&exec_instr_61, 
&exec_instr_62, 
&exec_instr_63, 
&exec_instr_64, 
&exec_instr_65, 
&exec_instr_66, 
&exec_instr_67, 
&exec_instr_68, 
&exec_instr_69, 
&exec_instr_6A, 
&exec_instr_6B, 
&exec_instr_6C, 
&exec_instr_6D, 
&exec_instr_6E, 
&exec_instr_6F, 
&exec_instr_70, 
&exec_instr_71, 
&exec_instr_72, 
&exec_instr_73, 
&exec_instr_74, 
&exec_instr_75, 
&exec_instr_76, 
&exec_instr_77, 
&exec_instr_78, 
&exec_instr_79, 
&exec_instr_7A, 
&exec_instr_7B, 
&exec_instr_7C, 
&exec_instr_7D, 
&exec_instr_7E, 
&exec_instr_7F, 
&exec_instr_80, 
&exec_instr_81, 
&exec_instr_82, 
&exec_instr_83, 
&exec_instr_84, 
&exec_instr_85, 
&exec_instr_86, 
&exec_instr_87, 
&exec_instr_88, 
&exec_instr_89, 
&exec_instr_8A, 
&exec_instr_8B, 
&exec_instr_8C, 
&exec_instr_8D, 
&exec_instr_8E, 
&exec_instr_8F, 
&exec_instr_90, 
&exec_instr_91, 
&exec_instr_92, 
&exec_instr_93, 
&exec_instr_94, 
&exec_instr_95, 
&exec_instr_96, 
&exec_instr_97, 
&exec_instr_98, 
&exec_instr_99, 
&exec_instr_9A, 
&exec_instr_9B, 
&exec_instr_9C, 
&exec_instr_9D, 
&exec_instr_9E, 
&exec_instr_9F, 
&exec_instr_A0, 
&exec_instr_A1, 
&exec_instr_A2, 
&exec_instr_A3, 
&exec_instr_A4, 
&exec_instr_A5, 
&exec_instr_A6, 
&exec_instr_A7, 
&exec_instr_A8, 
&exec_instr_A9, 
&exec_instr_AA, 
&exec_instr_AB, 
&exec_instr_AC, 
&exec_instr_AD, 
&exec_instr_AE, 
&exec_instr_AF, 
&exec_instr_B0, 
&exec_instr_B1, 
&exec_instr_B2, 
&exec_instr_B3, 
&exec_instr_B4, 
&exec_instr_B5, 
&exec_instr_B6, 
&exec_instr_B7, 
&exec_instr_B8, 
&exec_instr_B9, 
&exec_instr_BA, 
&exec_instr_BB, 
&exec_instr_BC, 
&exec_instr_BD, 
&exec_instr_BE, 
&exec_instr_BF, 
&exec_instr_C0, 
&exec_instr_C1, 
&exec_instr_C2, 
&exec_instr_C3, 
&exec_instr_C4, 
&exec_instr_C5, 
&exec_instr_C6, 
&exec_instr_C7, 
&exec_instr_C8, 
&exec_instr_C9, 
&exec_instr_CA, 
&exec_instr_CB, 
&exec_instr_CC, 
&exec_instr_CD, 
&exec_instr_CE, 
&exec_instr_CF, 
&exec_instr_D0, 
&exec_instr_D1, 
&exec_instr_D2, 
&exec_instr_D3, 
&exec_instr_D4, 
&exec_instr_D5, 
&exec_instr_D6, 
&exec_instr_D7, 
&exec_instr_D8, 
&exec_instr_D9, 
&exec_instr_DA, 
&exec_instr_DB, 
&exec_instr_DC, 
&exec_instr_DD, 
&exec_instr_DE, 
&exec_instr_DF, 
&exec_instr_E0, 
&exec_instr_E1, 
&exec_instr_E2, 
&exec_instr_E3, 
&exec_instr_E4, 
&exec_instr_E5, 
&exec_instr_E6, 
&exec_instr_E7, 
&exec_instr_E8, 
&exec_instr_E9, 
&exec_instr_EA, 
&exec_instr_EB, 
&exec_instr_EC, 
&exec_instr_ED, 
&exec_instr_EE, 
&exec_instr_EF, 
&exec_instr_F0, 
&exec_instr_F1, 
&exec_instr_F2, 
&exec_instr_F3, 
&exec_instr_F4, 
&exec_instr_F5, 
&exec_instr_F6, 
&exec_instr_F7, 
&exec_instr_F8, 
&exec_instr_F9, 
&exec_instr_FA, 
&exec_instr_FB, 
&exec_instr_FC, 
&exec_instr_FD, 
&exec_instr_FE, 
&exec_instr_FF 
};
void lingo_exec(lingo_ctx* ctx)
{
  lingoExecTable[ctx->regs.pc](ctx);
  ++ctx->regs.pc;
}
