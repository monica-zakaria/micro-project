
#include "stdint.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "UART.h"
float Atof_function(char* num);


float convert_to_float(char *raw);
float Radian(const float degree);
float calc(float lat1, float long1,
                     float lat2, float long2);
float convert_to_degrees(float coordinate);
float get_distance(float longitude[],float latitude[],char long_dir[],char lat_dir[]);

void send_uart(void);
