10 'ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»
20 'º   PLOTS  ----  Displays plots saved in TRIM as TRIMPLOT.xxx              º
30 'º   (C) 1990 - J. F. Ziegler, IBM - Research, Yorktown, NY, 10598,  USA    º
40 'ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼
50     DIM PLOT%(28110)
60     KEY OFF: SCREEN 9: WIDTH 80: COLOR 14,0: CLS
70     LOCATE  6,22: PRINT "ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»"
80     LOCATE   ,22: PRINT "º   TRIM plots stored as TRIMPLOT.n º"
90     LOCATE   ,22: PRINT "ÇÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¶"
100    LOCATE   ,22: PRINT "º   This program allows printers    º"
110    LOCATE   ,22: PRINT "º   to copy plots made during TRIM. º"
120    LOCATE   ,22: PRINT "ÇÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¶"
130    LOCATE   ,22: PRINT "º   Press any key to show Pictures  º"
140    LOCATE   ,22: PRINT "º     ( Press  ESC  key to End )    º"
150    LOCATE   ,22: PRINT "ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼"
160    COLOR 13
170    LOCATE CSRLIN-2,37: PRINT "ESC"
180    A$=INPUT$(1)
190    ON ERROR GOTO 340
200    NUMB = 0
210 'ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß  Loop Through Pictures ßßßßßßßßßßß
220    NUMB = NUMB + 1
230    P$=STR$(NUMB): P$=RIGHT$(P$,LEN(P$)-1)
240    PICTURE$="TRIMPLOT."+P$
250    A=VARPTR(PLOT%(0))
255  ''DEF SEG=VARSEG(PLOT%(0))        ' Use only in Compiled TurboBasic
260    BLOAD PICTURE$+"A",A
270    PUT (0,0),PLOT%,PSET
280    BLOAD PICTURE$+"B",A
290    PUT (320,0),PLOT%,PSET
300    DEF SEG
310    A$=INPUT$(1)
320    IF A$=CHR$(27) THEN SYSTEM
330    GOTO 210
340 'ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß  End of Pictures
350   IF NUMB = 1 GOTO 380
360   NUMB = 0
370   RESUME 210
380 'ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß  No Pictures Available
390   BEEP: COLOR 15
400   LOCATE 18,28: PRINT ">>>  ERROR IN STORED PLOTS !  <<<"
410   LOCATE 20,33: COLOR 12: PRINT"( Press  any  Key )"
420   A$=INPUT$(1)
430   END
