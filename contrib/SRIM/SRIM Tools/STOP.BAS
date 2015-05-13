'***********************************************+************************
'****  STOP.BAS  -  Calculation of Stopping
'****  (C)1987 - J. F. Ziegler, Yorktown, NY, 10598                    *
'***********************************************************************
    OPTION BASE 1

     DIM  DYNAMIC ENERGY(1000), ZNAMES$(92)
     DIM  SEE(1000), SE(1000), SN(1000)
     DIM  DYNAMIC SCOEF(93,54), SCOEFGAS(24,11)       ' Shared with STOP96

     $INCLUDE "STOP96.BAS"

     CALL STOPCOEF                                   'Fills SCOEF and SCOEFGAS

01   COLOR 15,0,1: WIDTH 80: LOCATE ,,1,0,7: CLS
     B1$= "   ษออออออออออออออออออออออออออออออออออออออออออออออออออออป"
     B2$= "   บ                                                    บ"
     B3$= "   ฬออออออออออออออออออออออออออออออออออออออออออออออออออออน"
     B4$= "   ศออออออออออออออออออออออออออออออออออออออออออออออออออออผ"
     CB=12: CQ=14: CA=15: Z1=3
     COLOR CB: PRINT B1$: PRINT B2$: PRINT B3$: PRINT B2$: PRINT B4$
     LOCATE 2,7: COLOR CB
     PRINT "Special program to make lists of Stopping Powers."
     LOCATE 4,7: COLOR CQ
     PRINT "Stopping for ALL Ions ?   (N) ";   '--- Getting ION data
     A$=INPUT$(1): PRINT A$;
     IF A$="y" OR A$="Y" THEN ALLZ1=1: GOTO 100
  95 LOCATE 4,1: COLOR CB: PRINT B2$
     LOCATE 4,7: COLOR CQ
     PRINT "What ION Atomic Number ?        ";: COLOR CA: INPUT Z1
     IF Z1<1 OR Z1>92 THEN BEEP: GOTO 95
                                                    '--- Getting TARGET data
 100 LOCATE 5,1: COLOR CB: PRINT B3$: PRINT B2$: PRINT B4$
     LOCATE 6,7: COLOR CQ
     PRINT "Stopping for ALL Targets ?  (N) ";: COLOR CA
     A$=INPUT$(1): PRINT A$
     IF A$="y" OR A$="Y" THEN ALLZ2=1: GOTO 200
 115 LOCATE 6,1: COLOR CB: PRINT B2$
     LOCATE 6,7: COLOR CQ
     PRINT "What TARGET Atomic Number ?     ";: COLOR CA: INPUT Z2
     IF Z2<1 OR Z2>92 THEN BEEP: GOTO 115
                                                    '--- Getting SOLIDGAS data
     IF Z1>2 GOTO 200         ' Only for H and He
     SOLIDGAS=0: Z2FLAG=0
     FOR I=1 TO 8: IF Z2=SCOEFGAS(I,1) THEN Z2FLAG=1 ELSE NEXT I 'See if GAS target
     IF Z2FLAG=0 GOTO 200
     LOCATE 7,1: COLOR CB: PRINT B3$: PRINT B2$: PRINT B4$
     LOCATE 8,7: COLOR CQ
     PRINT "Stopping for GAS Target (Y/N) ?  [Y] ";: COLOR CA
     A$=INPUT$(1)
     IF A$="n" OR A$="N" THEN SOLIDGAS=0 ELSE SOLIDGAS=1: A$="Y"
     COLOR 15: PRINT A$
                                                    '--- Getting ENERGY data
 200 LOCATE 7,1: COLOR CB: PRINT B3$: PRINT B2$: PRINT B4$
     LOCATE 8,7: COLOR CQ
     PRINT "More than  ONE  Energy ?  (N)   ";: COLOR CA
 210 A$=INPUT$(1)
     IF A$="y" OR A$="Y" GOTO 300
     LOCATE 8,7: COLOR CQ
     PRINT "What ION Energy (kev) ?         ";: COLOR CA: INPUT ENERGY(1)
     IF ENERGY(1)=0 THEN BEEP: GOTO 200
     PRINT: EENUMB=1: GOTO 400
 300 LOCATE 9,1
     FOR EENUMB=1 TO 1000
     COLOR CB: PRINT B2$;: LOCATE ,7: COLOR CQ
     PRINT "Input an Energy (kev)  [0 ends] ";: COLOR CA: INPUT ENERGY(EENUMB)
     IF ENERGY(EENUMB)=0 THEN EENUMB=EENUMB-1: GOTO 400
     NEXT EENUMB

 400 LOCATE CSRLIN-1,1: COLOR CB: PRINT B3$: PRINT B2$;: COLOR CQ
     LOCATE ,7: PRINT "Units of Stopping Powers :"
'----------------------- Following converts from eV-A2 to various units
     COLOR CB: PRINT B2$;: COLOR 13: LOCATE ,7
     U1$="  eV / Angstrom "       : PRINT "1 - "+U1$
     COLOR CB: PRINT B2$;: COLOR 13: LOCATE ,7
     U2$=" keV / micron   "       : PRINT "2 - "+U2$
     COLOR CB: PRINT B2$;: COLOR 13: LOCATE ,7
     U3$=" MeV / mm       "       : PRINT "3 - "+U3$
     COLOR CB: PRINT B2$;: COLOR 13: LOCATE ,7
     U4$=" keV / (ug/cm2) "       : PRINT "4 - "+U4$
     COLOR CB: PRINT B2$;: COLOR 13: LOCATE ,7
     U5$=" MeV / (mg/cm2) "       : PRINT "5 - "+U5$
     COLOR CB: PRINT B2$;: COLOR 13: LOCATE ,7
     U6$=" keV / (mg/cm2) "       : PRINT "6 - "+U6$
     COLOR CB: PRINT B2$;: COLOR 13: LOCATE ,7
     U7$="  eV / (1E15 atoms/cm2)": PRINT "7 - "+U7$
     COLOR CB: PRINT B2$: PRINT B4$: COLOR CQ: LOCATE CSRLIN-2,7
     PRINT "Which Stopping Units ?    (7) ";: COLOR CA
 410 A$=INKEY$: IF A$="" GOTO 410 ELSE PRINT A$
     UNITS=VAL(A$): IF UNITS<1 OR UNITS>7 THEN UNITS=7

     LOCATE CSRLIN-1,1: COLOR CB
     PRINT B3$: PRINT B2$: PRINT B4$: COLOR CQ: LOCATE CSRLIN-2,7
     PRINT "What disk FileName  ?   (STOP) ";: COLOR CA: INPUT F$
     IF F$="" THEN F$="STOP"
     OPEN F$ FOR OUTPUT AS #2
     COLOR CB: PRINT B4$

'----------------------------- PRINT OUTPUT -----------------------------
     COLOR 15,0 : PRINT STRING$(79,"=")
     PRINT " Stopping Units = ";
     PRINT#2, " Stopping Units = ";
     IF UNITS=1 THEN PRINT#2, U1$: PRINT U1$
     IF UNITS=2 THEN PRINT#2, U2$: PRINT U2$
     IF UNITS=3 THEN PRINT#2, U3$: PRINT U3$
     IF UNITS=4 THEN PRINT#2, U4$: PRINT U4$
     IF UNITS=5 THEN PRINT#2, U5$: PRINT U5$
     IF UNITS=6 THEN PRINT#2, U6$: PRINT U6$
     IF UNITS=7 THEN PRINT#2, U7$: PRINT U7$
   IF ALLZ1=0 THEN PRINT   USING "Ion Mass =####.####";SCOEF(Z1,3)
   IF ALLZ1=0 THEN PRINT#2,USING "Ion Mass =####.####";SCOEF(Z1,3)
   IF ALLZ2=0 THEN
      PRINT   USING "Tgt Mass =####.####";SCOEF(Z2,4)
      PRINT#2,USING "Tgt Mass =####.####";SCOEF(Z2,4)
      RHO=SCOEF(Z2,5)                  '-------- Solid Density
      ATRHO=SCOEF(Z2,6)                '-------- Solid Atomic Density
         IF SOLIDGAS=1 THEN                    '-------- Special GAS density
           FOR I=1 TO 8
           IF Z2=SCOEFGAS(I,1) THEN RHO=SCOEFGAS(I,2):ATRHO=SCOEFGAS(I,3)
         NEXT I: END IF
      PRINT   USING "Target Density =###.##### g/cm3 =##.####^^^^ atoms/cm3";RHO,ATRHO
      PRINT#2,USING "Target Density =###.##### g/cm3 =##.####^^^^ atoms/cm3";RHO,ATRHO
    END IF
    IF SOLIDGAS=1 THEN PRINT"Target is a Gas."
    PRINT   ""
    PRINT    "  Z1   Z2    ENERGY       SE        SN        S-total    Ion     Fractional"
    PRINT    "              (keV)                                     Eff.Chg. Eff. Chg."
    PRINT    " ---- ----  --------   ---------  ---------  ---------  -------- --------"
    PRINT#2,""
    PRINT#2, "  Z1   Z2    ENERGY       SE        SN        S-total    Ion   . Fractional"
    PRINT#2, "                                                        Eff.Chg. Eff. Chg."
    PRINT#2, " ---- ----  --------   ---------  ---------  ---------  -------- --------"
    POUT$=   "  ##   ##   ########  ##.###^^^^ ##.###^^^^ ##.###^^^^   ##.###   #.#### "

    '----------------- Get Stopping Powers --------------------------------
    IF ALLZ1=1 THEN Z1=1
    IF ALLZ2=1 THEN Z2=1
    NUMB=0: IENERGY=1           'NUMB indexes SE and SN
    ENERGY=ENERGY(IENERGY)      'IENERGY indexes ENERGY

'--------------------------- START OF LOOPING  -----------------------------
 500 NUMB=NUMB+1
      M1=SCOEF(Z1,3)           'SCOEF comes from CALL STOPCOEF at top.
      M2=SCOEF(Z2,4)
      IF M1=0 OR M2=0 GOTO STOPLOOP
      IF ALLZ2>0 THEN ATRHO=SCOEF(Z2,6)  'Must cycle through ATRHOs

 512 IF UNITS=1 THEN CORR = ATRHO*1E-24
     IF UNITS=2 THEN CORR = ATRHO*1E-23
     IF UNITS=3 THEN CORR = ATRHO*1E-23
     IF UNITS=4 THEN CORR = .060222/M2
     IF UNITS=5 THEN CORR = .060222/M2
     IF UNITS=6 THEN CORR = (.060222/M2)*1000
     IF UNITS=7 THEN CORR = 1/10

     EFLAG=1: ENUMB=1         ' EFLAG tells STOP to GIVEN Energy
     E0KEV=ENERGY(IENERGY): SEE(1)=E0KEV   ' SEE passes Energies to STOP

     CALL STOP96 (Z1,M1,Z2,E0KEV,SEE(),ENUMB,SOLIDGAS)

    '----------------- Convert (eV-A2) to Correct Units and put into SE
     SE(NUMB)=SEE(1)*CORR

    '----------------- Get proton stopping for Effective Charge
      Z=1: M=1: SEE(1)=E0KEV/M1
      CALL STOP96(Z,M,Z2,E,SEE(),ENUMB,SOLIDGAS)
      IF SEE(1)<1E-8 THEN PRINT "Z1=" Z1", Z2=" Z2", SEE(1)= " SEE(1): STOP
      EFFCHG=(SE(NUMB)/(SEE(1)*CORR))^0.5

'***** Calculate ZBL universal nuclear stopping powers *****************
'---------  Epsilon is the reduced energy of the ion/target combination.
      E=E0KEV
      EPSIL=32.53*M2*E/(Z1*Z2*(M1+M2)*(Z1^.23+Z2^.23))
      IF (EPSIL>=30) GOTO 600
      A=(.01321*EPSIL^.21226)+(.19593*EPSIL^.5)
      SN(NUMB)=.5*LOG(1+1.1383*EPSIL)/(EPSIL+A)
      GOTO 700
 600
      SN(NUMB)=LOG(EPSIL)/(2*EPSIL)
 700  '--------- convert from LSS reduced units to eV-cm2/1E15
      SN(NUMB)=SN(NUMB)*Z1*Z2*M1*8.462/((M1+M2)*(Z1^.23+Z2^.23))
      SN(NUMB)=SN(NUMB)*CORR*10  'Convert (eV-cm2) -> (eV-A2) -> Correct Units

      SE=SE(NUMB): SN=SN(NUMB): STOTAL=SE+SN

     PRINT    USING POUT$; Z1,Z2,ENERGY(IENERGY),SE,SN,STOTAL,EFFCHG,EFFCHG/Z1
     PRINT#2, USING POUT$; Z1,Z2,ENERGY(IENERGY),SE,SN,STOTAL,EFFCHG,EFFCHG/Z1

STOPLOOP: '---------- LOOPING -----------------------------------------------
     IF ALLZ1=1 AND Z1<92 THEN Z1=Z1+1: GOTO 500
     IF ALLZ1=1 AND Z1=92 THEN Z1=1
     IF ALLZ2=1 AND Z2<92 THEN Z2=Z2+1: GOTO 500
     IF ALLZ2=1 AND Z2=92 THEN Z2=1
     IF EENUMB>IENERGY THEN IENERGY=IENERGY+1: GOTO 500
'------------------------------------------------------------------------
     CLOSE
     COLOR 15: PRINT"Data stored in "+F$
     COLOR 14: PRINT"   ( Press SPACEBAR for new calculation )"
998  A$=INKEY$: IF A$<>"" GOTO 998       'Clear Keyboard
999  A$=INKEY$: IF A$="" GOTO 999        'Wait for Key
     IF A$=" " GOTO 01                   'Restart Program
     COLOR 15,0
     STOP
