#include <stdio.h>
#include <windows.h>
#include "anim.h" 

static float  angle_in_revs;
static float  revs_per_minute;
static double old_time;
SYSTEMTIME    lt;

void anim_init(float initial_angle_in_revs, float initial_revs_per_minute)
{
   angle_in_revs   = initial_angle_in_revs;
   revs_per_minute = initial_revs_per_minute;
   GetLocalTime(&lt);
   old_time        = lt.wSecond * 1000.0 + lt.wMilliseconds;
}

void anim_set_revs_per_minute(float revs_per_minute_param)
{
   revs_per_minute = revs_per_minute_param; 
}

float anim_get_angle_in_revs()
{
   GetLocalTime(&lt);
   double new_time   = lt.wSecond * 1000.0 + lt.wMilliseconds;
   double msecs_diff = new_time - old_time;
   double mins_diff  = (msecs_diff / 1000.0) / 60.0; 
   angle_in_revs    += static_cast<float>(mins_diff) * revs_per_minute;
   angle_in_revs     = angle_in_revs - static_cast<int>(angle_in_revs);
   old_time          = new_time;
   return angle_in_revs;
}
