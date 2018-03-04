
#if defined QuickTurn_Included
	#endinput
#endif

#define QuickTurn_Included

#include <a_samp>

/*=================================================
* 	Forwarding Hooks
===================================================*/
#if defined QuickTurn_OnPlayerUpdate
forward QuickTurn_OnPlayerUpdate(playerid);
#endif

#if defined QuickTurn_OnPlayerStateChange
forward QuickTurn_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

#if defined OnPlayerQuickTurn
forwrd OnPlayerQuickTurn(playerid, turntype);
#endif

/*=================================================
* 	Variable For Old Angle
===================================================*/
static 
	QuickTurn_OldAngle[MAX_PLAYERS];
/*=================================================
* 	InnerFunctions
===================================================*/

static QuickTurn_IsVehicleEmpty(playerid, vehicleid)
{
	for(new i, j = GetPlayerPoolSize(); i <= j; i++)
    {
   	 	if(!IsPlayerConnected(i)) continue;
    	if(i != playerid && GetPlayerVehicleID(i) == vehicleid) return 1;
    }
	return 0;
}
/*=================================================
* 	Callbacks
===================================================*/
public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		static Float:z_rot;

	   	GetVehicleZAngle(GetPlayerVehicleID(playerid), z_rot);
		QuickTurn_OldAngle[playerid] = floatround(z_rot, floatround_round);
	}
	#if defined QuickTurn_OnPlayerStateChange
		return QuickTurn_OnPlayerStateChange(playerid, newstate, oldstate);
	#else	
		return 1;
	#endif	
}

public OnPlayerUpdate(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))
    {
        static Float:z_rot, QT_Veh, z_rot_round;

        QT_Veh = GetPlayerVehicleID(playerid);
        z_rot = GetVehicleZAngle(QT_Veh, z_rot);
        z_rot_round = floatround(z_rot, floatround_round);

        if((QuickTurn_OldAngle[playerid] - z_rot_round) == 90 || (QuickTurn_OldAngle[playerid] - z_rot_round) == -90)
        {
        	switch(GetPlayerState(playerid))
        	{
        		case 2:
        		{
        			#if defined OnPlayerQuickTurn
        			OnPlayerQuickTurn(playerid, 1);
        			#endif
        		}
        		case 3:
        		{
        			if(QuickTurn_IsVehicleEmpty(playerid, QT_Veh))
        			{
        				#if defined OnPlayerQuickTurn
        				OnPlayerQuickTurn(playerid, 2);
        				#endif
        			}
        		}
        	}
        }
        QuickTurn_OldAngle[playerid] = z_rot_round;
    }

	#if defined QuickTurn_OnPlayerUpdate
        return QuickTurn_OnPlayerUpdate(playerid);
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

#define OnPlayerStateChange QuickTurn_OnPlayerStateChange

#if defined _ALS_OnPlayerUpdate
  #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate QuickTurn_OnPlayerUpdate
