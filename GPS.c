#include "GPS.h"
    // distance
    uint8_t  index_point = 0 ;
	float R = 6371;
    float dlong = 0;
    float dlat = 0;
    float ans = 0;

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




