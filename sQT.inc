
#if defined sQt_Included
	#endinput
#endif

#define sQt_Included

#include <a_samp>

/*=================================================
* 	Forwarding Hooks
===================================================*/
#if defined sQt_OnPlayerUpdate
forward sQt_OnPlayerUpdate(playerid);
#endif

#if defined sQt_OnPlayerStateChange
forward sQt_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

#if defined OnPlayerQuickTurn
forward OnPlayerQuickTurn(playerid);
#endif

/*=================================================
* 	Variable For Old Angle
===================================================*/
new sQt_OldAngle[MAX_PLAYERS];

/*=================================================
* 	Callbacks
===================================================*/
public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		new Float:z_rot;
	    new vehicleid = GetPlayerVehicleID(playerid);
	   	GetVehicleZAngle(vehicleid, z_rot);
		sQt_OldAngle[playerid] = floatround(z_rot, floatround_round);
	}
	#if defined sQt_OnPlayerStateChange
		return sQt_OnPlayerStateChange(playerid, newstate, oldstate);
	#else	
		return 1;
	#endif	
}

public OnPlayerUpdate(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new Float:z_rot;
        new vid = GetPlayerVehicleID(playerid);
        GetVehicleZAngle(vid, z_rot);
        
        new z_rot_round = floatround(z_rot, floatround_round);

        if((sQt_OldAngle[playerid] - z_rot_round) == 90 || (sQt_OldAngle[playerid] - z_rot_round) == -90)
        {
        	#if defined OnPlayerQuickTurn
        	OnPlayerQuickTurn(playerid);
        	#endif
        }

        sQt_OldAngle[playerid] = z_rot_round;
        
    }
	#if defined sQt_OnPlayerUpdate
        return sQt_OnPlayerUpdate(playerid);
	#else
	    return 1;
	#endif
}


/*=================================================
* 	Hooked Functions
===================================================*/
#if defined _ALS_OnPlayerStateChange
  #undef OnPlayerStateChange
#else
    #define _ALSOnPlayerStateChange
#endif

#define OnPlayerStateChange sQt_OnPlayerStateChange

#if defined _ALS_OnPlayerUpdate
  #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate sQt_OnPlayerUpdate
