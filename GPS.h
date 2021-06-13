
#include "stdint.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
float Atof_function(char* num);


float convert_to_float(char *raw);
float Radian(const float degree);
float calc(float lat1, float long1,
                     float lat2, float long2);
float convert_to_degrees(float coordinate);
float get_distance(float longitude[],float latitude[],char long_dir[],char lat_dir[]);

void send_uart(void);

void get_latitude(short int latpointer);
void get_longitude(short int longpointer);
void get_NS_indicator(short int NSpointer);
void get_EW_indicator(short int EWpointer)
void get_fix_gps(short int fixpointer);
void gps_string(uint8_t receive_char);
float return_distance(void);