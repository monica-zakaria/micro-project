#include "GPS.h"
    // distance
    uint8_t  index_point = 0 ;
	float R = 6371;
    float dlong = 0;
    float dlat = 0;
    float ans = 0;

		    float integer ;
    float fraction ;
    int divisorForFraction ;
    int sign ;
    bool inFraction ;

	char latitude_buffer[10];
	char longitude_buffer[10];
	char N;
	char E;
	short int lat_index = 0;
	short int long_index = 0;
	char GGA_string[70]; //save gga string
	char lat_arr[100][10];  //string_array
	char long_arr[100][10];  //string_array
	float long_distance[100]; //100point
	float lat_distance[100]; //100point
	char DIR_LANG_E[100]; //100 point
	char DIR_LAT_N[100]; //100 point
	char fix = '0';
	char GGA_pointers[20];
	char GGA_CODE[3] = { 0 };
	short int GGA_index;
	short int comma_counter;
	uint32_t COUNTER_GGA = 0;
	bool flag_counter_7 = false;
	bool ISITGGA = false;


float Atof_function(char* num)
{
    if (!num || !*num)
        return 0;
     integer = 0;
     fraction = 0;
     divisorForFraction = 1;
     sign = 1;
     inFraction = false;

    if (*num == '-')
    {
        ++num;
        sign = -1;
    }
    else if (*num == '+')
    {
        ++num;
    }
    while (*num != '\0')
    {
        if (*num >= '0' && *num <= '9')
        {
            if (inFraction)
            {
                fraction = fraction * 10 + (*num - '0');
                divisorForFraction *= 10;
            }
            else
            {
                integer = integer * 10 + (*num - '0');
            }
        }
        else if (*num == '.')
        {
            if (inFraction)
                return sign * (integer + fraction / divisorForFraction);
            else
                inFraction = true;
        }
        else
        {
            return sign * (integer + fraction / divisorForFraction);
        }
        ++num;
    }
    return sign * (integer + fraction / divisorForFraction);
}

float convert_to_float(char * raw){

	float value ;
	value = Atof_function(raw);    /* convert string into float for conversion */

	return value ;
}

///////////////////////////////////
void get_latitude(short int latpointer)
{
	short int index;
	for (index = latpointer + 1; GGA_string[index] != ','; index++) {
		latitude_buffer[lat_index] = GGA_string[index];
		++lat_index;
	}
}

void get_longitude(short int longpointer)
{
	short int index;
	for (index = longpointer + 1; GGA_string[index] != ','; index++) {
		longitude_buffer[long_index] = GGA_string[index];
		++long_index;
	}

}
void get_NS_indicator(short int NSpointer)
{
	short int index;
	for (index = NSpointer + 1; GGA_string[index] != ','; index++) {
		N = GGA_string[index];

	}
}
void get_EW_indicator(short int EWpointer)
{
	short int index;
	for (index = EWpointer + 1; GGA_string[index] != ','; index++) {
		E = GGA_string[index];
	}
}
////////////////////////////////////////
void get_fix_gps(short int fixpointer)
{
	short int index;
	for (index = fixpointer + 1; GGA_string[index] != ','; index++) {
		fix = GGA_string[index];
	}

}
void gps_string(uint8_t receive_char) {


	int i;

	if (receive_char == '$')
	{
		store = false;
		flag_counter_7 = false;
		GGA_index = 0;
		comma_counter = 0;
		ISITGGA = false;
		lat_index = 0;
		long_index = 0;

	}
	else if (GGA_CODE[0] == 'G' && GGA_CODE[1] == 'G' && GGA_CODE[2] == 'A')
	{
		++COUNTER_GGA;
		ISITGGA = true;
		GGA_CODE[0] = 0; GGA_CODE[1] = 0; GGA_CODE[2] = 0;
	}
	else if (ISITGGA == true)
	{
		if (receive_char == ',')
		{
			GGA_pointers[comma_counter++] = GGA_index;
		}
		if (comma_counter == 7)
		{


			get_fix_gps(GGA_pointers[4]);

			if (fix == '1' && flag_counter_7 == false) {
				flag_counter_7 = true;
				get_latitude(GGA_pointers[0]);
				get_NS_indicator(GGA_pointers[1]);
				get_longitude(GGA_pointers[2]);
				get_EW_indicator(GGA_pointers[3]);


				if (COUNTER_GGA == 1 || COUNTER_GGA % 4 == 0) {//each 4 GGA COUNTER_GGA %4 == 0  ||


					for (i = 0; i < lat_index; i++)
					{
						lat_arr[index_point][i] = latitude_buffer[i];
					}

					for (i = 0; i < long_index; i++)
					{
						long_arr[index_point][i] = longitude_buffer[i];
					}
					//NEW 
					long_distance[index_point] = convert_to_float(long_arr[index_point]);
					lat_distance[index_point] = convert_to_float(lat_arr[index_point]);

					DIR_LANG_E[index_point] = E;
					DIR_LAT_N[index_point] = N;
					++index_point;


				}
			}
		}



		if (comma_counter <= 8) {
			GGA_string[GGA_index++] = receive_char;
		}
	}

	else {

		GGA_CODE[0] = GGA_CODE[1]; GGA_CODE[1] = GGA_CODE[2]; GGA_CODE[2] = receive_char;
	}
}


//  Function to change from degree to radian
float Radian(const float degree){
    float rad = (3.14159265358979323846) / 180;
    return(degree*rad);
}
// function to calculate the distance
float calc(float lat1, float long1,float lat2, float long2)
{

    lat1 = Radian(lat1);
    long1 = Radian(long1);
    lat2 = Radian(lat2);
    long2 = Radian(long2);
    dlong = long2 - long1;
    dlat = lat2 - lat1;
    ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));
    ans = ans * R;
    return ans;
}
//Function to change the format of the latitude & longitude
float convert_to_degrees(float coordinate){

	float decimal_value,temp;

	int32_t degrees;

	float position;

	/* convert raw latitude/longitude into degree format */
	decimal_value = (coordinate/100);
	degrees       = (int)(decimal_value);
	temp          = (decimal_value - (int)decimal_value)/0.6;
	position      = (float)degrees + temp;
	return position;
}
//function to get the total distance of the coordinates
float get_distance(float longitude[],float latitude[],char long_dir[],char lat_dir[]){
    float distance = 0;
    //change format
	int i ;
      for ( i=0 ; i<index_point ; i++) {
        latitude[i]=convert_to_degrees(latitude[i]);
        longitude[i]=convert_to_degrees(longitude[i]);
   }
    //change from west & north to +ve & -ve

    for ( i=0 ; i<index_point ; i++) {
        if(long_dir[i] == 'W'){
            longitude[i] = longitude[i]*-1;
        }
        if(lat_dir[i]=='S'){
            latitude[i]= latitude[i]*-1;
        }
   }
    for ( i=0 ; i<index_point-1; i++) {
        distance += calc(latitude[i],longitude[i],latitude[i+1],longitude[i+1]);
   }
	distance = distance/1000;
  // printf("%lf m",distance);
    return distance;
}

//in main at final destination 
float return_distance(void) {
	float value;
	value = get_distance(long_distance, lat_distance, DIR_LANG_E, DIR_LAT_N);

	return value;

}

//SEND TO UART COORDINATES 
void send_uart(void)
{
	int i;
	int j;


	for (j = 1; j < index_point; j++)
	{
		for (i = 0; i < 10; i++) {
			UART5_TRANSMIT(lat_arr[j][i]);
		}
		UART5_TRANSMIT(' ');
		for (i = 0; i < 10; i++) {
			UART5_TRANSMIT(long_arr[j][i]);
		}
		UART5_TRANSMIT(' ');
		UART5_TRANSMIT(DIR_LAT_N[j]);
		UART5_TRANSMIT(' ');
		UART5_TRANSMIT(DIR_LANG_E[j]);

		UART5_TRANSMIT(',');

	}

}




