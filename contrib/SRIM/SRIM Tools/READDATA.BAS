10  'ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
20  'บ    Program to Read TRIM Data File COLLISON.TXT                        บ
30  'ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
40  '฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿   First dimension Arrays for Data Variables
50  DIM IONNUMB(1000),IONENERGY(1000),X(1000),Y(1000),Z(1000),SE(1000)
60  DIM ATOM2$(1000),RECOILENERGY(1000)
70  DIM DISPLACEMENT(1000),VACANCY(1000),REPLACEMENT(1000),INTERSTITIAL(1000)
80  CLS '฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿  Now open data file
90 OPEN "COLLISON.TXT" FOR INPUT AS #1
100 FOR I=1 TO 1000                      ' Cycle through data arrays
110 IF EOF(1)=-1 GOTO 290                ' End input if reach End-of-File
120 LOCATE 5,30:PRINT "Reading : " I     ' Show Data Increment on Screen
130 LINE INPUT#1,L$                      ' Input one line of characters
140 IONNUMB(I)=VAL(MID$(L$,2,5))         ' Convert first data field to a number
150 '฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿ The next line throws out Comment Lines in the Datafile
160 IF IONNUMB(I)=0 GOTO 110             ' If not number, ignore, get new line
170 IONENERGY(I)   = VAL(MID$(L$,8,9))   ' Getting Data
180 X(I)           = VAL(MID$(L$,18,10)) ' Getting Data
190 Y(I)           = VAL(MID$(L$,29,10)) ' Getting Data
200 Z(I)           = VAL(MID$(L$,40,10)) ' Getting Data
210 SE(I)          = VAL(MID$(L$,51,7))  ' Getting Data
220 ATOM2$(I)      =     MID$(L$,60,2)   ' Getting Data
230 RECOILENERGY(I)= VAL(MID$(L$,64,10)) ' Getting Data
240 DISPLACEMENT(I)= VAL(MID$(L$,75,6))  ' Getting Data
250 VACANCY(I)     = VAL(MID$(L$,82,6))  ' Getting Data
260 REPLACEMENT(I) = VAL(MID$(L$,89,6))  ' Getting Data
270 INTERSTITIAL(I)= VAL(MID$(L$,96,6))  ' Getting Data
280 NEXT I                               ' Go to next item in data array
290 CLOSE (1)                            ' Finished with data
300 DATANUMB=I-1                         ' This is number of lines of data
310 '฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿ Test that we have data
320 PRINT "Displaying Top of Data from COLLISON.TXT"
330 PRINT "ึฤฤฤฤฤยฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤยฤฤฤฤยฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤยฤฤฤฤฤฤยฤฤฤฤฤฤยฤฤฤฤฤฤท";
340 PRINT "บ Ion ณ  Energy ณ  Depth   ณ  Se   ณAtomณ Recoil   ณTargetณTargetณTargetณTargetบ";
350 PRINT "บ Numbณ  (keV)  ณ   (A)    ณ(eV/A) ณHit ณEnergy(eV)ณDISP. ณVAC.  ณREPLACณINTER บ";
360 PRINT "ฬอออออุอออออออออุออออออออออุอออออออุออออุออออออออออุออออออุออออออุออออออุออออออน";
370 F$=   "บ#####ณ##.##^^^^ณ#.####^^^^ณ####.##ณ \\ ณ#.####^^^^ณ######ณ######ณ######ณ######บ"
380 FOR J=1 TO 10                          ' Cycle through top of data array
390 PRINT USING F$;IONNUMB(J);IONENERGY(J);X(J);SE(J);ATOM2$(J);RECOILENERGY(J),DISPLACEMENT(J),VACANCY(J),REPLACEMENT(J),INTERSTITIAL(J);
400 NEXT J
