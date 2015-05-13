10      COLOR 15,0: CLS
20  PRINT "ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
30  PRINT "บ       SUM  =  Sums up ASCII outputs of TRIM calculation.       บ
40  PRINT "ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
50  PRINT "บ  (C)-1989, J. F. Ziegler, IBM-Research, Yorktown, NY 10598     บ
60  PRINT "ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
70  C1$=  "บ  Reading file VACANCY.TXT -- Distribution of Vacancies         บ
80  C2$=  "บ  Reading file IONIZ.TXT   -- Distribution of Ionization        บ
90  C3$=  "บ  Reading file PHONON.TXT  -- Distribution of Phonons           บ
100 C4$=  "บ  Reading file E2RECOIL.TXT-- Distribution of Energy to Recoils.บ
110 C5$=  "ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
120         DIM DEPTH(100), VAC1(100), VAC2(100), IONIZ1(100), IONIZ2(100)
130         DIM PHONON1(100), PHONON2(100), E2REC1(100), E2REC2(100)
140 '
150 'อออออออออออออออออออ Getting VACANCY.TXT  ออออออออออออออออออออ
160     OPEN "VACANCY.TXT" FOR INPUT AS #1
170  PRINT C1$
180  J=1                                      ' This input style is used to
190  FOR I=1 TO 200                           ' get rid of Comments in file.
200     A=EOF(1): IF A=-1 GOTO 250
210     LINE INPUT#1,A$
220     A=VAL(MID$(A$,1,11)): B=VAL(MID$(A$,13,12)): C=VAL(MID$(A$,26,12))
230     IF A>0 THEN  DEPTH(J)=A: VAC1(J)=B: VAC2(J)=C: J=J+1
240  NEXT I :
250  CLOSE #1
260 'อออออออออออออออออออ Getting IONIZ.TXT  ออออออออออออออออออออ
270  OPEN "IONIZ.TXT" FOR INPUT AS #1
280  PRINT C2$
290  J=1                                      ' This input style is used to
300  FOR I=1 TO 200                           ' get rid of Comments in file.
310     A=EOF(1): IF A=-1 GOTO 360
320     LINE INPUT#1,A$
330     A=VAL(MID$(A$,1,11)): B=VAL(MID$(A$,13,12)): C=VAL(MID$(A$,26,12))
340     IF A>0 THEN  DEPTH(J)=A: IONIZ1(J)=B: IONIZ2(J)=C: J=J+1
350  NEXT I :
360  CLOSE #1
370 'อออออออออออออออออออ Getting PHONON.TXT  ออออออออออออออออออออ
380     OPEN "PHONON.TXT" FOR INPUT AS #1
390  PRINT C3$
400  J=1                                      ' This input style is used to
410  FOR I=1 TO 200                           ' get rid of Comments in file.
420     A=EOF(1): IF A=-1 GOTO 470
430     LINE INPUT#1,A$
440     A=VAL(MID$(A$,1,11)): B=VAL(MID$(A$,13,12)): C=VAL(MID$(A$,26,12))
450     IF A>0 THEN  DEPTH(J)=A: PHONON1(J)=B: PHONON2(J)=C: J=J+1
460  NEXT I :
470  CLOSE #1
480 'อออออออออออออออออออ Getting E2RECOIL.TXT  ออออออออออออออออออออ
490     OPEN "E2RECOIL.TXT" FOR INPUT AS #1     'Energy Transferred to Recoils
500  PRINT C4$
510  J=1                                      ' This input style is used to
520  FOR I=1 TO 200                           ' get rid of Comments in file.
530     A=EOF(1): IF A=-1 GOTO 580
540     LINE INPUT#1,A$
550     A=VAL(MID$(A$,1,11)): B=VAL(MID$(A$,13,12)): C=VAL(MID$(A$,26,12))
560     IF A>0 THEN  DEPTH(J)=A: E2REC1(J)=B: E2REC2(J)=C: J=J+1
570  NEXT I :
580  CLOSE #1
590  PRINT C5$
600  COLOR 13  '฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿
610     INPUT "What was the Original Ion Energy (keV) ?   [100]  "; E0KEV
620     IF E0KEV = 0 THEN E0KEV=100
630     INPUT "What is the Target Binding Energy (eV) ?   [  2]"; EB
640     IF EB = 0 THEN EB=2
650     CW=DEPTH(2)-DEPTH(1)
660     FOR I= 1 TO 100
670        VAC1   = VAC1+VAC1(I)      : VAC2   = VAC2+VAC2(I)
680        IONIZ1 = IONIZ1+IONIZ1(I)  : IONIZ2 = IONIZ2+IONIZ2(I)
690        PHONON1= PHONON1+PHONON1(I): PHONON2= PHONON2+PHONON2(I)
700        E2REC1 = E2REC1+E2REC1(I)  : E2REC2 = E2REC2+E2REC2(I)
710        NEXT I
720     VAC1   =VAC1*CW*EB: VAC2=VAC2*CW*EB
730     IONIZ1 =IONIZ1*CW : IONIZ2=IONIZ2*CW
740     PHONON1=PHONON1*CW: PHONON2=PHONON2*CW
750     E2REC1 =E2REC1*CW : E2REC2=E2REC2*CW
760     TOTLOSS = VAC1+VAC2+IONIZ1+IONIZ2+PHONON1+PHONON2
770     TOTAL = E0KEV*1000
780  COLOR 14
790     PRINT      "ษออออออออออออออออออออออออออออหอออออออออออออออออออออออออป
800     PRINT      "บ           PERCENTAGE LOSS  บ     ENERGY LOSS (keV)   บ"
810     PRINT      "บ           IONS    RECOILS  บ    IONS      RECOILS    บ"
820     PRINT      "บ          ฤฤฤฤฤฤฤ  ฤฤฤฤฤฤฤ  บ  ฤฤฤฤฤฤฤฤฤฤ ฤฤฤฤฤฤฤฤฤฤ  บ"
830     I1=IONIZ1*100/TOTLOSS : I2=IONIZ2*100/TOTLOSS
840     V1=VAC1*100/TOTLOSS   : V2=VAC2*100/TOTLOSS
850     P1=PHONON1*100/TOTLOSS: P2=PHONON2*100/TOTLOSS
860     PRINT USING"บ Ioniz =   ##.###   ##.###  บ  ######.### ######.###  บ";I1;I2,IONIZ1/1000;IONIZ2/1000
870     PRINT USING"บ Vac.  =   ##.###   ##.###  บ  ######.### ######.###  บ";V1;V2;VAC1/1000;VAC2/1000
880     PRINT USING"บ Phonon=   ##.###   ##.###  บ  ######.### ######.###  บ";P1;P2;PHONON1/1000;PHONON2/1000
890     PRINT      "บ อออออออ  อออออออ  อออออออ  บ  ออออออออออ ออออออออออ  บ"
900     TOTAL1=(IONIZ1+VAC1+PHONON1)*100/TOTLOSS
910     TOTAL2=(IONIZ2+VAC2+PHONON2)*100/TOTLOSS
920     TOTAL3=(IONIZ1+VAC1+PHONON1)/1000
930     TOTAL4=(IONIZ2+VAC2+PHONON2)/1000
940     PRINT USING"บ Totals=  ###.###% ###.###% บ  ######.### ######.###  บ";TOTAL1;TOTAL2;TOTAL3;TOTAL4
950     PRINT      "ศออออออออออออออออออออออออออออสอออออออออออออออออออออออออผ"
960     PRINT      "        ษอออออออออออออออออออออออออออออออออออออออป"
970     PRINT USING"        บ   TOTAL ENERGY LOSS = ######.### keV  บ";TOTLOSS/1000
980     PRINT      "        ศอออออออออออออออออออออออออออออออออออออออผ"
990     VAC1=CINT(VAC1/EB) : VAC2=CINT(VAC2/EB)
1000     PRINT      "ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป"
1010     PRINT USING"บ  Energy Transferred to Recoils =######.### keV      บ";E2REC1/1000
1020 ''' PRINT USING"บ  Energy Received by Recoils    =######.### keV      บ";E2REC2/1000
1030     PRINT USING"บ  Ion Vacancies = ###### , Recoil Vacancies = ###### บ";VAC1;VAC2
1040     PRINT USING"บ  Total Vacancies/Ion =  #######                     บ";VAC1+VAC2
1050     PRINT      "ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ"
1060  COLOR 15: PRINT "NOTE : Totals may be in error if final ion is not yet stopped,"
1070  COLOR 15: PRINT "       or if Ions or Recoils leave the Plotting Wondow."
1080  COLOR 15: PRINT "NOTE : Summation currently valid only for single element targets."
