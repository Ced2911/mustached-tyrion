// in_null.c -- for systems without a mouse
#include <input/input.h>
#include <usb/usbmain.h>
#include <debug.h>
#include "../client/client.h"
#ifdef CAPS
#include <libcaps/lib.h>
#endif
#define SIDE_THRESHOLD	0.22f
#define LOOK_THRESHOLD	0.22f
#define LOOK_VALUE	35
#define SIDE_VALUE	7

void mini_do_poll(void);

#define usb_do_poll mini_do_poll

static struct controller_data_s ctrl, old_ctrl;

cvar_t	*in_joystick;

void IN_Init (void)
{
	memset(&ctrl, 0, sizeof(struct controller_data_s));
#ifdef CAPS
	static int init_caps = 0; 
	if (init_caps == 0) {
		xenon_caps_init("udb:/quake2.mp4");
		init_caps = 1;
	}
#endif
}

void IN_Shutdown (void)
{

}

void IN_Commands (void)
{
	
}

void IN_Frame (void)
{
	usb_do_poll();
}

void IN_Move (usercmd_t *cmd)
{
	float	speed, aspeed;
	float	fAxisValue;
	int		i;
 
	usb_do_poll();
	get_controller_data(&ctrl, 0);

	if ( (in_speed.state & 1) ^ (int)cl_run->value)
		speed = 2;
	else
		speed = 1;
		
	aspeed = speed * cls.frametime;
	
	float f1_x, f1_y, f2_x, f2_y;
	
	f1_x = (float)ctrl.s1_x / 32768.0f;
	f1_y = (float)ctrl.s1_y / 32768.0f;
	f2_x = (float)ctrl.s2_x / 32768.0f;
	f2_y = (float)ctrl.s2_y / 32768.0f;
	
	if (ctrl.rt > 64) {
		Key_Event(K_MOUSE1, 1, 0);
	}
	else if (ctrl.rt < 64) {
		Key_Event(K_MOUSE1, 0, 0);
	}
	
	if (ctrl.start && !old_ctrl.start) {
		Key_Event(K_ENTER, 1, 0);
	}
	else if (!ctrl.start && old_ctrl.start) {
		Key_Event(K_ENTER, 0, 0);
	}	
	
	if (ctrl.back && !old_ctrl.back) {
		Key_Event(K_ESCAPE, 1, 0);
	}
	else if (!ctrl.back && old_ctrl.back) {
		Key_Event(K_ESCAPE, 0, 0);
	}
	
	if (ctrl.up && !old_ctrl.up) {
		Key_Event(K_UPARROW, 1, 0);
	}
	else if (!ctrl.up && old_ctrl.up) {
		Key_Event(K_UPARROW, 0, 0);
	}
	
	if (ctrl.down && !old_ctrl.down) {
		Key_Event(K_DOWNARROW, 1, 0);
	}
	else if (!ctrl.down && old_ctrl.down) {
		Key_Event(K_DOWNARROW, 0, 0);
	}
#ifdef CAPS
	if (ctrl.a && !old_ctrl.a) {
		xenon_caps_start();
	} else if (ctrl.y && !old_ctrl.y) {
		xenon_caps_end();
	}
#endif
	// AxisSide
	if (fabs(f1_x) > SIDE_THRESHOLD)
	{
		cmd->sidemove += (f1_x * SIDE_VALUE) * speed * cl_sidespeed->value;
	}
	// AxisUp
	if (fabs(f1_y) > SIDE_THRESHOLD)
	{
		cmd->forwardmove += (f1_y * SIDE_VALUE) * speed * cl_forwardspeed->value;
	}
	// Look 
	if (fabs(f2_x) > LOOK_THRESHOLD)
	{
		cl.viewangles[YAW] -= (f2_x * LOOK_VALUE) * m_yaw->value;
	}
	if (fabs(f2_y) > LOOK_THRESHOLD)
	{
		cl.viewangles[PITCH] -= (f2_y * LOOK_VALUE) * m_pitch->value;
	}
#if 0
	// loop through the axes
	for (i = 0; i < JOY_MAX_AXES; i++)
	{
		// get the floating point zero-centered, potentially-inverted data for the current axis
		fAxisValue = (float) *pdwRawValue[i];
		// move centerpoint to zero
		fAxisValue -= 32768.0;

		// convert range from -32768..32767 to -1..1 
		fAxisValue /= 32768.0;

		switch (dwAxisMap[i])
		{
		case AxisForward:
			if ((joy_advanced->value == 0.0) && mlooking)
			{
				// user wants forward control to become look control
				if (fabs(fAxisValue) > joy_pitchthreshold->value)
				{		
					// if mouse invert is on, invert the joystick pitch value
					// only absolute control support here (joy_advanced is false)
					if (m_pitch->value < 0.0)
					{
						cl.viewangles[PITCH] -= (fAxisValue * joy_pitchsensitivity->value) * aspeed * cl_pitchspeed->value;
					}
					else
					{
						cl.viewangles[PITCH] += (fAxisValue * joy_pitchsensitivity->value) * aspeed * cl_pitchspeed->value;
					}
				}
			}
			else
			{
				// user wants forward control to be forward control
				if (fabs(fAxisValue) > joy_forwardthreshold->value)
				{
					cmd->forwardmove += (fAxisValue * joy_forwardsensitivity->value) * speed * cl_forwardspeed->value;
				}
			}
			break;

		case AxisSide:
			if (fabs(fAxisValue) > joy_sidethreshold->value)
			{
				cmd->sidemove += (fAxisValue * joy_sidesensitivity->value) * speed * cl_sidespeed->value;
			}
			break;

		case AxisUp:
			if (fabs(fAxisValue) > joy_upthreshold->value)
			{
				cmd->upmove += (fAxisValue * joy_upsensitivity->value) * speed * cl_upspeed->value;
			}
			break;

		case AxisTurn:
			if ((in_strafe.state & 1) || (lookstrafe->value && mlooking))
			{
				// user wants turn control to become side control
				if (fabs(fAxisValue) > joy_sidethreshold->value)
				{
					cmd->sidemove -= (fAxisValue * joy_sidesensitivity->value) * speed * cl_sidespeed->value;
				}
			}
			else
			{
				// user wants turn control to be turn control
				if (fabs(fAxisValue) > joy_yawthreshold->value)
				{
					if(dwControlMap[i] == JOY_ABSOLUTE_AXIS)
					{
						cl.viewangles[YAW] += (fAxisValue * joy_yawsensitivity->value) * aspeed * cl_yawspeed->value;
					}
					else
					{
						cl.viewangles[YAW] += (fAxisValue * joy_yawsensitivity->value) * speed * 180.0;
					}

				}
			}
			break;

		case AxisLook:
			if (mlooking)
			{
				if (fabs(fAxisValue) > joy_pitchthreshold->value)
				{
					// pitch movement detected and pitch movement desired by user
					if(dwControlMap[i] == JOY_ABSOLUTE_AXIS)
					{
						cl.viewangles[PITCH] += (fAxisValue * joy_pitchsensitivity->value) * aspeed * cl_pitchspeed->value;
					}
					else
					{
						cl.viewangles[PITCH] += (fAxisValue * joy_pitchsensitivity->value) * speed * 180.0;
					}
				}
			}
			break;

		default:
			break;
		}
	}
#endif

	old_ctrl = ctrl;
}

void IN_Activate (qboolean active)
{
}

void IN_ActivateMouse (void)
{
}

void IN_DeactivateMouse (void)
{
}
