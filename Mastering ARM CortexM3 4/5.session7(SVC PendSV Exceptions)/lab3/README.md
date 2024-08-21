# LAB3 PendSV

## Output
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/change%20TaskA%20to%20TaskB%20in%20PendSV.gif)

## Details for the output
 

## sequence
sorry for the bad drawing :)
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/sequence.jpeg)

## Calling TaskA
we got to Os_Set_Task then the flag was set to TASKA
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/calling%20taskA.png)

## excuption stacking
after the SVC_Handler was called and we took a screenshot before going to it's ISR 
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/excuption%20stacking.png)

## sp->PSP of taskA
set it to TaskA start address 
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/set%20sp%20to%20PSP%20and%20unprivilege.png)

## LED0 is on
after we set the SP to point on start of PSP of TaskA we call function 
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/led%200%20is%20on.png)

## Rising edge detected
an Interrupt happeded caused the processor to go to the EXTI9 Handler there we we change to TaskB in pendSV hander by setting ICSR BIT28 when it detect that there is no ISR to works
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/led%200%20is%20on.png)

## set sp->PSP of taskB
in pendsv handler we change it to taskB and set psp to it's address
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/set%20sp%20to%20PSP%20taskB.png)

## LED1 is on
so when it return and switch context the flag is gonna be equal to TASKB 
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab3/led1%20is%20on.png)