
typedef struct DrawVerticeFormats {
    float x, y, z, w;
    unsigned int color;
    float u, v;
} DrawVerticeFormats;

struct XenosDevice _xe, *xe;
struct XenosShader * pVertexShader;
struct XenosShader * pPixelShader;
struct XenosSurface * pVideoSurface;
struct XenosVertexBuffer * pVBSw;
