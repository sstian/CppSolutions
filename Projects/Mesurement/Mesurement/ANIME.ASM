  CODE	SEGMENT                  
	ASSUME   CS:CODE,DS:CODE
  START: MOV AX,CODE
         MOV DS,AX
         MOV AX,0B800H
         MOV ES,AX
         CLD
  AGAIN: MOV AX,3
         INT 10H
         LEA DX,MENU
         MOV AH,9
         INT 21H
  INPUT: MOV AH,0
         INT 16H
         CMP AL,'1'
         JNZ CP2
         CALL SUB01
         JMP INPUT
    CP2: CMP AL,'2'
         JNZ CP3
         CALL SUB02
         JMP AGAIN
    CP3: CMP AL,'3'
         JNZ INPUT
         LEA DX,MESG
         MOV AH,9
         INT 21H
         MOV AH,1
         INT 21H
         MOV AH,4CH
         INT 21H
  DELAY  PROC
         PUSH     CX
         PUSH     DX
         MOV DX,1000
     D1: MOV CX,0FFFFH
         LOOP $
         DEC DX
         JNZ D1
         POP DX
         POP CX
         RET
  DELAY  ENDP
  SUB01: MOV AX,0E0DH
         INT 10H
         MOV AL,0AH
         INT 10H
         LEA DX,STR
         MOV AH,0AH
         INT 21H
         MOV AX,0E0AH
         INT 10H
         RET
  SUB02: CMP STR+1,2
         JNB Y2
         JMP QUIT
     Y2: CALL LINE
    @Y2: XOR AX,AX
         MOV CNT1,AX
         MOV CNT5,AX
         MOV DL,60-2
         MOV AL,STR+1
         SUB DL,AL
         MOV DH,0
         MOV CNT3,DX
         MOV BL,AL
         INC AL
         SHR AL,1
         CBW
         MOV CNT2,AX
         SUB BL,AL
         MOV BH,0
         MOV CNT4,BX
     Y3: MOV BP,ES
         PUSH DS
         POP ES
         MOV DI,1000H
         MOV CX,CNT1
         JCXZ U1
         MOV AL,20H
         REP STOSB
     U1: LEA SI,BUF
         MOV CX,CNT2
         REP MOVSB
         MOV CX,CNT3
         JCXZ U2
         MOV AL,20H
         REP STOSB
     U2: MOV CX,CNT4
         REP MOVSB
         MOV CX,CNT5
         JCXZ U3
         MOV AL,20H
         REP STOSB
     U3:
   SHOW: MOV ES,BP
         MOV AH,0AH
         MOV SI,1000H
         MOV DI,LEFT
         MOV CX,60-2
    PPP: LODSB
         STOSW
         LOOP PPP
         CALL DELAY
         CMP CNT3,0
         JZ @INPUT
         INC CNT1
         INC CNT5
         DEC CNT3
         CMP CNT3,0
         JZ KK2
         DEC CNT3
    KK2: JMP Y3
 @INPUT: MOV AH,0
         INT 16H
         CMP AH,10H
         JZ SSS
         CMP AH,13H
         JNZ @INPUT
         CMP CNT3,0
         JNZ @REP
         JMP @Y2
   @REP: JMP Y3
    SSS: MOV STR+1,0
   QUIT: LEA SI,CNT1
         XOR AX,AX
         MOV CX,5
    KK3: MOV [SI],AX
         INC SI
         INC SI
         LOOP KK3
         XOR DI,DI
         MOV CX,80*25
         MOV AX,720H
         REP STOSW
         RET
   LINE: MOV DI,(18*80+10)*2
         MOV AL,201
         MOV AH,0EH
         STOSW
         MOV CX,60-2
         MOV AL,205
         REP STOSW
         MOV AL,187
         STOSW
         ADD DI,20*2
         MOV AL,186
         STOSW
         MOV LEFT,DI
         MOV CX,60-2
         MOV AL,20H
         REP STOSW
         MOV RIGHT,DI
         MOV AL,186
         STOSW
         ADD DI,20*2
         MOV AL,200
         STOSW
         MOV CX,60-2
         MOV AL,205
         REP STOSW
         MOV AL,188
         STOSW
         RET
         MENU   DB   5   DUP(0AH)
         DB   31 DUP(' '),'MAIN MENU',0DH,0AH
         DB   25 DUP(' '),201,21 DUP(205),187,0DH,0AH
         DB   25 DUP(' '),186,' 1.INPUT A STRING ...',186,0DH,0AH
         DB   25 DUP(' '),186,' 2.DISPLAY MODEL ....',186,0DH,0AH
         DB   25 DUP(' '),186,' 3.RETURN TO DOS ....',186,0DH,0AH
         DB   25 DUP(' '),200,21 DUP(205),188,0DH,0AH
         DB   28 DUP(' '),'CHOICE(1,2,3):$'
         MESG DB 0DH,0AH,0DH,0AH,9,'PRESS ANY KEY TO EXIT ...$'
         CNT1 DW 0
         CNT2 DW 0
         CNT3 DW 0
         CNT4 DW 0
         CNT5 DW 0
         NUM DW 2
         LEFT DW 0
         RIGHT DW 0
         STR DB 21
         DB 0
         BUF DB 0DH,20 DUP(0)
  CODE   ENDS
         END    START
