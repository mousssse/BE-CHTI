	PRESERVE8
	THUMB   
	export callbackson
	export SortieSon
	import flag
	import Son
	import LongueurSon
	include DriverJeuLaser.inc	

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
SortieSon dcw 0x0
index dcd 0
	
	
; ===============================================================================================
		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		

callbackson proc
	ldr r0, =SortieSon			;r0 = &SortieSon
	ldr r1, =Son				;r1 = &Son
	mov r3, #0					;r3 = index
	push{r4, r5, r6, r7, r8}
	ldr r4, =LongueurSon		;r4 = &LongueurSon
	ldr r5, [r4]				;r5 = LongueurSon
	
	cmp r3, r5					;if index >= LongueurSon
	bgt fin						;then jump to fin
	
	ldr r7, =flag
	ldr r8, [r7]
	cmp r8, #0
	bne fin;
	
	ldrsh r6, [r1, r3, lsl#1]	
	add r6, #32768
	mov r1, #719
	mul r6, r1
	lsr r6, r6, #16				;r6 = r6/65535 (65535 = 2^16-1)
	str r6, [r0]				;SortieSon = Son[index]
	
fin mov r0, r6					;r0 = SortieSon
	push{lr}
	bl PWM_Set_Value_TIM3_Ch3	;calling function with r0 as a parameter
	pop {lr}
	
	add r3, #1					;r3++
	pop {r4, r5, r6, r7, r8}
	
	bx lr
	endp
	END	