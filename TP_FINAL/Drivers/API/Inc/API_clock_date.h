#ifndef API_INC_API_CLOCK_DATE_H_
#define API_INC_API_CLOCK_DATE_H_

#include "API_clock_date_port.h"

/* Exported functions ------------------------------------------------------- */
void clockInit(void);
void clockUpdateTimeDate(void);
void Clock_Error_Handler(void);

#define OK 0
#define ERROR 1

#endif /* API_INC_API_CLOCK_DATE_H_ */
