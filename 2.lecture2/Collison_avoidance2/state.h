#ifndef STATE_H_
#define STATE_H_


//Automatic state function generated
#define STATE_DEFINE(_stateFUN_) void ST##_stateFUN_()
#define STATE(_stateFUN_) ST##_stateFUN_


//States connection
void US_Get_Distance(int distance);
void DC_Motor_Set(int speed);
#endif /* STATE_H_ */
