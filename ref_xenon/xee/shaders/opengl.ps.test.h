#if 0
//
// Generated by 2.0.21076.0
//
//   fxc /Fh opengl.ps.test.h /Tps_3_0 opengl.hlsl /Eps_test_main
//
//
// Parameters:
//
//   sampler2D texture0;
//
//
// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   texture0     s0       1
//

// Shader type: pixel 

xps_3_0
defconst texture0, sampler2d, object, [1, 1], s0
config AutoSerialize=false
config AutoResource=false
config PsMaxReg=2
// PsExportColorCount=1
// PsSampleControl=both

dcl_texcoord r0.xy
dcl_texcoord1 r1.xy
dcl_color_centroid r2


    exec
    tfetch2D r0, r0.xy, tf0
    alloc colors
    exece
    mov oC0, r0

// PDB hint 00000000-00000000-00000000

#endif

// This microcode is in native DWORD byte order.

const DWORD g_xps_ps_test_main[] =
{
    0x102a1100, 0x000000b4, 0x0000003c, 0x00000000, 0x00000024, 0x00000000, 
    0x00000088, 0x00000000, 0x00000000, 0x00000060, 0x0000001c, 0x00000053, 
    0xffff0300, 0x00000001, 0x0000001c, 0x00000000, 0x0000004c, 0x00000030, 
    0x00030000, 0x00010000, 0x0000003c, 0x00000000, 0x74657874, 0x75726530, 
    0x00ababab, 0x0004000c, 0x00010001, 0x00010000, 0x00000000, 0x70735f33, 
    0x5f300032, 0x2e302e32, 0x31303736, 0x2e3000ab, 0x00000000, 0x0000003c, 
    0x10000200, 0x00000008, 0x00000000, 0x00002063, 0x00030007, 0x00000001, 
    0x00003050, 0x00003151, 0x0000f2a0, 0x00011002, 0x00001200, 0xc4000000, 
    0x00001003, 0x00002200, 0x00000000, 0x10080001, 0x1f1ff688, 0x00004000, 
    0xc80f8000, 0x00000000, 0xe2000000, 0x00000000, 0x00000000, 0x00000000
};
