#include <cstdlib>
#include <iostream>
#include <cstring>
#include <mach/mach.h>
#include <mach/mach_time.h>

int
main( int argc, char **argv )
{
   auto curr_time( mach_absolute_time() );
   /** call this to get the conversion factor to nanoseconds **/
   static mach_timebase_info_data_t timebase_info;
   std::memset( &timebase_info, 0x0, sizeof( mach_timebase_info_data_t ) );

   if( timebase_info.denom == 0 )
   {
      (void)mach_timebase_info( &timebase_info );
   }

   double nano_seconds( (curr_time * (timebase_info.numer / timebase_info.denom)) );

   std::cout << nano_seconds << "\n";
   return( EXIT_FAILURE );
} 
