#ifndef __LED_DRIVE_H
#define __LED_DRIVE_H

typedef enum
{
	red,
	green,
	blue
}colour;

void LED_drive(colour LED_colour);

#endif /* __LED_DRIVE_H */
