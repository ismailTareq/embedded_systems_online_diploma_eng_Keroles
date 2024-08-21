# LAB2
SVC

## 1st Stacking
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab2/1st%20stacking.png)

## Exception Stacking
LR is loaded with info if it's MSP or PSP PAL or NPAL it's like a Screenshot from the last states of every register
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab2/exception%20stacking.png)

## saving address in R0
in order to accuss the stack we loaded R0 with address of the first byte in MSP stack
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab2/saving%20address%20in%20R0%20.png)

## Getting number from SVC
when switching from ISR to normal function it push an argument so it takes only one and it is the first register that's why we Put address in R0
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab2/Getting%20number%20from%20SVC.png)

## unstacking excepution stacking
the result is saved in the argument been passed to the function which is R0 then we read it to obtain the result
![gitHub](https://github.com/ismailTareq/embedded_systems_online_diploma_eng_Keroles/blob/main/Mastering%20ARM%20CortexM3%204/5.session7(SVC%20PendSV%20Exceptions)/lab2/unstacking%20excepution%20stacking.png)

