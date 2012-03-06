#include "AutoAim.hpp"
#include "WPILib.h"
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

using namespace std;

#define BUFLEN  50
#define PORT	3000

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; 

namespace vision
{
	int angle;
	float distance = 0;
	bool gotUpdate = true;
	int pixelDistance;
}
struct sockaddr_in si_me, si_other;
int s, i, slen=sizeof(si_other);
char buf[50];

void diePretty(char *s)
{
	perror(s);
	exit(1);
}


void *socketFunction(void*ptr)
{
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diePretty("socket");		
	
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, (sockaddr *)&si_me, sizeof(si_me))==-1)
		diePretty("bind");
	while(1)
	{
		int rValue = recvfrom(s, buf, BUFLEN, 0, (sockaddr*)&si_other, &slen);	
		int counter;
		int offset;
		char numberOne[5];
		char numberTwo[5];
		bool first = true;
		
		if(vision::gotUpdate && (rValue != -1))
		{
			cout << "Entered..." << endl;
			for(counter = 0; counter < BUFLEN; counter++)
			{
				if(first)
				{
					if(buf[counter] == '|')
					{
						numberOne[counter] = '\0';
						first = false;
						pthread_mutex_lock(&mutex1);
						vision::pixelDistance = atoi(numberOne);
						pthread_mutex_unlock(&mutex1);
						offset = counter + 1;
					}
					else
					{
						numberOne[counter] = buf[counter];
					}
				}
				else
				{
					if(buf[counter] == '|')
					{
						numberTwo[counter-offset] = '\0';
						pthread_mutex_lock(&mutex1);
						vision::distance = atof(numberTwo);
						pthread_mutex_unlock(&mutex1);
					}
					else
					{
						numberTwo[counter-offset] = buf[counter];
					}				
				}
			}
			pthread_mutex_lock(&mutex1);
			vision::gotUpdate = false;
			pthread_mutex_unlock(&mutex1);
			cout << numberOne << " : " << numberTwo << endl;
		}
		
	}
}

AutoAim::AutoAim(WaveTurretControl *turret)
{
	turret = turret;
	useAutoAim = false;
	pthread_create(&serverThread, NULL, socketFunction, (void*)NULL);
}
	
void AutoAim::autoAimOn()
{
	useAutoAim = true;
}

void AutoAim::autoAimOff()
{
	useAutoAim = false;
}

void AutoAim::autoAimRun()
{
	if(useAutoAim)
	{
		pthread_mutex_lock(&mutex1);
		vision::gotUpdate = true;
		pthread_mutex_unlock(&mutex1);
		cout << "Pixel Distance: " << vision::pixelDistance << endl;
		if(vision::pixelDistance < -5 && vision::pixelDistance > 5)
		{
			turret->moveTurret((320/vision::pixelDistance) + .1);
		}
	}
}
