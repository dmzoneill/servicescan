//============================================================================
// Name        : servicescan.cpp
// Author      : David O Neill ( dave@feeditout.com )
// Version     : 1.0
// Copyright   : Copyright Intel Corporation 2011
// Description : php's lack of threads
//============================================================================

#include <iostream>
#include <string>
#include <stdio.h>
#include <pthread.h>
#include <sstream>

using namespace std;



void * exec( void * cmd );
pthread_t t1;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;



int main()
{
	string subnets[ 3 ];
	subnets[ 0 ] = "10.237.212.";
	subnets[ 1 ] = "10.237.213.";
	subnets[ 2 ] = "10.243.18.";

	for ( int cnt = 0 ; cnt < 3 ; cnt++ )
	{
		int fourthOctect = 1;

		while ( fourthOctect < 255 )
		{
			if ( counter < 5 )
			{
				cout << "Creating thread ";
				cout << fourthOctect;
				cout << "\n";

				std::stringstream out;
				out << fourthOctect;

				string command = "php /home/david/Desktop/wait.php "+ subnets[ cnt ] + out.str();

				pthread_create( &t1 , NULL , exec , ( void * ) command.c_str() );
				sleep( 1 );

				fourthOctect++;
			}
			else
			{
				sleep( 2 );
			}
		}
	}

	return 0;
}

void * exec( void * cmd )
{
	char * foo = ( char * ) cmd;

	int newcounter;

	pthread_mutex_lock( &mutex1 );
	newcounter = counter;
	newcounter++;
	counter = newcounter;
	pthread_mutex_unlock( &mutex1 );

	FILE* pipe = popen( foo , "r" );
	if ( pipe )
	{
		char buffer[ 128 ];
		std::string result = "";
		while ( !feof( pipe ) )
		{
			if ( fgets( buffer , 128 , pipe ) != NULL ) result += buffer;
		}
		pclose( pipe );
		cout << result;
	}

	pthread_mutex_lock( &mutex1 );
	newcounter = counter;
	newcounter--;
	counter = newcounter;
	pthread_mutex_unlock( &mutex1 );

}
