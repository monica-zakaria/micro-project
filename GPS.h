
#include "stdint.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h> 

float Radian(const float degree);
float calc(float lat1, float long1,
                     float lat2, float long2);
float convert_to_degrees(float coordinate);
float get_distance(float longitude[],float latitude[],char long_dir[],char lat_dir[]);
