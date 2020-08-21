#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifdef WIN32
#include <unistd.h>
#endif

#include <string.h>

/* hardware.h */
#ifndef PLL_HARDWARE
#define PLL_HARDWARE

/* leaf 1 */
/* edx */
#define PLL_HAS_MMX         1 << 23
#define PLL_HAS_SSE         1 << 25
#define PLL_HAS_SSE2        1 << 26

/* ecx */
#define PLL_HAS_SSE3        1
#define PLL_HAS_SSSE3       1 << 9
#define PLL_HAS_FMA         1 << 12
#define PLL_HAS_SSE41       1 << 19
#define PLL_HAS_SSE42       1 << 20
#define PLL_HAS_AVX         1 << 28

/* leaf 7 */
/* ebx */
#define PLL_HAS_AVX2        1 << 5

/* leaf 0x80000001 */
/* ecx */
#define PLL_HAS_SSE4A       1 << 6
#define PLL_HAS_FMA4        1 << 16

typedef struct
{
  int has_mmx;
  int has_sse;
  int has_sse2;
  int has_sse3;
  int has_ssse3;
  int has_sse41;
  int has_sse42;
  int has_sse4a;
  int has_avx;
  int has_avx2;
  int has_fma;
  int has_fma4;
  int cpu_sockets;
  int cores;
  char vendor[13];

} pllHardwareInfo;

#endif

#define PLL_FEAT_AVAIL(x,y) (((x) & (y)) == (y))
#define PLL_SYS_CPU_DIR_PATH "/sys/devices/system/cpu/"

static __inline void cpuid(unsigned int op, int count,
                        unsigned int *eax, unsigned int *ebx,
                        unsigned int *ecx, unsigned int *edx)
{
#ifdef WIN32
      __int32 regs[4];
      __cpuid((int*)regs, (int)op);
      *eax = regs[0];
      *ebx = regs[1];
      *ecx = regs[2];
      *edx = regs[3];
#else
      *eax = op;
  *ecx = count;
  asm volatile("cpuid"
        : "=a" (*eax),
          "=b" (*ebx),
          "=c" (*ecx),
          "=d" (*edx)

        : "0" (*eax), "2" (*ecx)
        : "memory");
#endif
}

void show_hardware_info(pllHardwareInfo * hw)
{
  printf ("MMX.........: %d\n"
          "SSE.........: %d\n"
          "SSE2........: %d\n"
          "SSE3........: %d\n"
          "SSSE3.......: %d\n"
          "FMA.........: %d\n"
          "SSE4.1......: %d\n"
          "SSE4.2......: %d\n"
          "AVX.........: %d\n"
          "AVX2........: %d\n"
          "SSE4A.......: %d\n"
          "FMA4........: %d\n"
          "Core(s).....: %d\n"
          "CPU Sockets.: %d\n",

          hw->has_mmx, hw->has_sse, hw->has_sse2, hw->has_sse3, hw->has_ssse3,
          hw->has_fma, hw->has_sse41, hw->has_sse42, hw->has_avx, hw->has_avx2,
          hw->has_sse4a, hw->has_fma4, hw->cores, hw->cpu_sockets);
}

static int pll_probe_cpu (pllHardwareInfo * hw)
{
  struct stat cpustat;
  char cpu[30];
  char cpupath[100];
  int i, id, max_physical_id = -1;
  char * physical_id_path = "/topology/physical_package_id";
  FILE * fd;

  /* check whether the sys cpu dir exist */
  if (stat(PLL_SYS_CPU_DIR_PATH, &cpustat)) return (0);

  /* and also check whether it is a dir */
  if (!S_ISDIR(cpustat.st_mode)) return (0);

  /* detect number of processors */
  for (i = 0; ; ++i)
  {
    sprintf(cpu, "cpu%d", i);
    strcpy (cpupath, PLL_SYS_CPU_DIR_PATH);
    strcat (cpupath, cpu);
    if (stat(cpupath, &cpustat)) break;

    strcat (cpupath, physical_id_path);
    if (!stat(cpupath, &cpustat))
    {
      fd = fopen (cpupath, "r");
      fscanf (fd, "%d", &id);
      /* printf ("Detected processor %d belonging to package %d\n", i, id); */
      if (id > max_physical_id) max_physical_id = id;
      fclose (fd);
    }
  }

  hw->cores = i;
  hw->cpu_sockets = max_physical_id + 1;

  return (1);
}

static void pll_probe_hardware (pllHardwareInfo * hw)
{
  unsigned int a, b, c, d;
  c = 0;
  cpuid(0,0,&a,&b,&c,&d);
  *((unsigned int *)(hw->vendor)    ) = b;
  *((unsigned int *)(hw->vendor + 4)) = d;
  *((unsigned int *)(hw->vendor + 8)) = c;
  hw->vendor[12] =0;

  printf ("%s\n", hw->vendor);

  cpuid(1,0,&a,&b,&c,&d);

  hw->has_mmx   = PLL_FEAT_AVAIL(d,PLL_HAS_MMX);
  hw->has_sse   = PLL_FEAT_AVAIL(d,PLL_HAS_SSE);
  hw->has_sse2  = PLL_FEAT_AVAIL(d,PLL_HAS_SSE2);

  hw->has_sse3  = PLL_FEAT_AVAIL(c,PLL_HAS_SSE3);
  hw->has_ssse3 = PLL_FEAT_AVAIL(c,PLL_HAS_SSSE3);
  hw->has_fma   = PLL_FEAT_AVAIL(c,PLL_HAS_FMA);
  hw->has_sse41 = PLL_FEAT_AVAIL(c,PLL_HAS_SSE41);
  hw->has_sse42 = PLL_FEAT_AVAIL(c,PLL_HAS_SSE42);
  hw->has_avx   = PLL_FEAT_AVAIL(c,PLL_HAS_AVX);

  cpuid(7,0,&a,&b,&c,&d);

  hw->has_avx2  = PLL_FEAT_AVAIL(b,PLL_HAS_AVX2);

  cpuid(0x80000001,0,&a,&b,&c,&d);

  hw->has_sse4a = PLL_FEAT_AVAIL(c,PLL_HAS_SSE4A);
  hw->has_fma4  = PLL_FEAT_AVAIL(c,PLL_HAS_FMA4);
}

int pllGetHardwareInfo (pllHardwareInfo * hw)
{
  pll_probe_hardware (hw);
  pll_probe_cpu (hw);

  return (1);
}

