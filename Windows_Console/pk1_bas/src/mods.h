#ifndef MODS_H_INCLUDED
#define MODS_H_INCLUDED

extern int bExit();
extern void vError();
extern int vInfo(int);
extern int judgeExceptNumber(int[], int, int);
extern int code1BtoChar();
extern int mbToAsm(int, int []);
extern int codeToInfo(char*[], int, int[], int);
extern int readMbCode();
extern int CV_Code();
extern int Spls10();
extern int Spls16();
extern int codeComp(char*[], char[]);
extern int CodeFind();

#endif
