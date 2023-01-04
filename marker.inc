/*------------------------------------------------------------------------------
 *                                                                            *
 * New Marker - 3.0.0                                                         *
 * Developer : Ramon (https://github.com/Ramon-Sd)                            *
 *                                                                            *
------------------------------------------------------------------------------*/

#if !defined _samp_included
#include <a_samp>
#endif

#if !defined _streamer_included
#include <streamer>
#endif

#if !defined INVALID_DYNAMIC_OBJECT_ID
    #define INVALID_DYNAMIC_OBJECT_ID (0xFFFF)
#endif

#if defined _lib_new_marker
	#endinput
#endif
#define _lib_new_marker

//------------------------------------------------------------------------------

/*

* Natives

native CreateMarker(bool:call, Float:callradius, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 300.0, Float:drawdistance = 600.0);
native CreateStaticMarker(Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 300.0, Float:drawdistance = 600.0);
native CreateInvisibleMarker(Float:radius, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1);
native DestroyMarker(markerid);
native IsValidMarker(markerid);
native GetMarkerInterior(markerid);
native GetMarkerVirtualWorld(markerid);
native IsPlayerInMarker(playerid, markerid);

* Callbacks

forward OnPlayerEnterMarker(playerid, markerid);
forward OnPlayerLeaveMarker(playerid, markerid);

*/

//------------------------------------------------------------------------------

#if !defined MAX_MARKERS
    #define MAX_MARKERS (1001)
#endif

#define INVALID_MARKER_ID (-1)

#define New_Marker::Loop(%0) for (new %0; %0 < MAX_MARKERS; %0++)

//------------------------------------------------------------------------------

static enum E_MARKER_DATA {

    E_MARKER_OBJ = INVALID_DYNAMIC_OBJECT_ID,
    bool:E_MARKER_CALL,
    STREAMER_TAG_AREA:E_MARKER_CALL_AREA,
    Float:E_MARKER_POS[3],
    E_MARKER_WORLDID,
    E_MARKER_INTERIORID

};
static e_MarkerData[MAX_MARKERS][E_MARKER_DATA];

// ------------------------------------------------------------------------------

stock CreateMarker(Float:radius, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 300.0, Float:drawdistance = 600.0) {
    new freeMarker_ID = getFreeMarker_ID();
    if (freeMarker_ID == INVALID_MARKER_ID) {
        printf("\n\n[New Marker -> Error]: Limit of marker's exceeded! MAX_MARKERS: %d\n", (MAX_MARKERS - 1));
        return 0;
    }
    e_MarkerData[freeMarker_ID][E_MARKER_OBJ] = CreateDynamicObject(19197, x, y, z - 1.240, 0.0, 0.0, 0.0, worldid, interiorid, playerid, streamdistance, drawdistance);
    e_MarkerData[freeMarker_ID][E_MARKER_CALL] = true;
    e_MarkerData[freeMarker_ID][E_MARKER_CALL_AREA] = CreateDynamicCircle(x, y, radius, worldid, interiorid, playerid);
    e_MarkerData[freeMarker_ID][E_MARKER_POS][0] = x;
    e_MarkerData[freeMarker_ID][E_MARKER_POS][1] = y;
    e_MarkerData[freeMarker_ID][E_MARKER_POS][2] = z;
    e_MarkerData[freeMarker_ID][E_MARKER_WORLDID] = worldid;
    e_MarkerData[freeMarker_ID][E_MARKER_INTERIORID] = interiorid;
    return freeMarker_ID;
}

stock CreateStaticMarker(Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 300.0, Float:drawdistance = 600.0) {
    new freeMarker_ID = getFreeMarker_ID();
    if (freeMarker_ID == INVALID_MARKER_ID) {
        printf("\n\n[New Marker -> Error]: Limit of marker's exceeded! MAX_MARKERS: %d\n", (MAX_MARKERS - 1));
        return 0;
    }
    e_MarkerData[freeMarker_ID][E_MARKER_OBJ] = CreateDynamicObject(19197, x, y, z - 1.240, 0.0, 0.0, 0.0, worldid, interiorid, playerid, streamdistance, drawdistance);
    e_MarkerData[freeMarker_ID][E_MARKER_CALL] = false;
    e_MarkerData[freeMarker_ID][E_MARKER_POS][0] = x;
    e_MarkerData[freeMarker_ID][E_MARKER_POS][1] = y;
    e_MarkerData[freeMarker_ID][E_MARKER_POS][2] = z;
    e_MarkerData[freeMarker_ID][E_MARKER_WORLDID] = worldid;
    e_MarkerData[freeMarker_ID][E_MARKER_INTERIORID] = interiorid;
    return freeMarker_ID;
}

stock CreateInvisibleMarker(Float:radius, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1) {
    new freeMarker_ID = getFreeMarker_ID();
    if (freeMarker_ID == INVALID_MARKER_ID) {
        printf("\n\n[New Marker -> Error]: Limit of marker's exceeded! MAX_MARKERS: %d\n", (MAX_MARKERS - 1));
        return 0;
    }
    e_MarkerData[freeMarker_ID][E_MARKER_CALL] = true;
    e_MarkerData[freeMarker_ID][E_MARKER_CALL_AREA] = CreateDynamicCircle(x, y, radius, worldid, interiorid, playerid);
    e_MarkerData[freeMarker_ID][E_MARKER_POS][0] = x;
    e_MarkerData[freeMarker_ID][E_MARKER_POS][1] = y;
    e_MarkerData[freeMarker_ID][E_MARKER_POS][2] = z;
    e_MarkerData[freeMarker_ID][E_MARKER_WORLDID] = worldid;
    e_MarkerData[freeMarker_ID][E_MARKER_INTERIORID] = interiorid;
    return freeMarker_ID;
}

stock DestroyMarker(markerid) {
    if (getMarkerDynamicObjectID(markerid) != INVALID_DYNAMIC_OBJECT_ID)
        DestroyDynamicObject(e_MarkerData[markerid][E_MARKER_OBJ]);

    if (getMarkerDynamicArea(markerid) >= 0)
        DestroyDynamicArea(e_MarkerData[markerid][E_MARKER_CALL_AREA]);

    new markerDataVoid[E_MARKER_DATA];
    e_MarkerData[markerid] = markerDataVoid;
    return 1;
}

stock IsValidMarker(markerid) {
    return !(e_MarkerData[markerid][E_MARKER_POS][0] == 0.0 && e_MarkerData[markerid][E_MARKER_POS][1] == 0.0 && e_MarkerData[markerid][E_MARKER_POS][2] == 0.0);
}

stock GetMarkerInterior(markerid) {
    return e_MarkerData[markerid][E_MARKER_INTERIORID];
}

stock GetMarkerVirtualWorld(markerid) {
    return e_MarkerData[markerid][E_MARKER_WORLDID];
}

stock IsPlayerInMarker(playerid, markerid) {
    return (IsPlayerInDynamicArea(playerid, getMarkerDynamicArea(markerid)));
}

forward OnPlayerEnterMarker(playerid, markerid);
forward OnPlayerLeaveMarker(playerid, markerid);

// ------------------------------------------------------------------------------

static getMarkerDynamicObjectID(markerid) {
    return e_MarkerData[markerid][E_MARKER_OBJ];
}

static getMarkerDynamicArea(markerid) {
    return e_MarkerData[markerid][E_MARKER_CALL_AREA];
}

static getFreeMarker_ID() {
    New_Marker::Loop(id) {
        if (!IsValidMarker(id))
            return id;
    }
    return INVALID_MARKER_ID;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid) {
    New_Marker::Loop(id) {
        if (!IsValidMarker(id))
            continue;
        
        if (!e_MarkerData[id][E_MARKER_CALL])
            continue;

        if (areaid == getMarkerDynamicArea(id)) {
            CallRemoteFunction("OnPlayerEnterMarker", "ii", playerid, id);
        }
    }
    #if defined NM_OnPlayerEnterDynamicArea
        return NM_OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
    #undef OnPlayerEnterDynamicArea
#else
    #define _ALS_OnPlayerEnterDynamicArea
#endif

#define OnPlayerEnterDynamicArea NM_OnPlayerEnterDynamicArea
#if defined NM_OnPlayerEnterDynamicArea
    forward NM_OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid);
#endif

public OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid) {
    New_Marker::Loop(id) {
        if (!IsValidMarker(id))
            continue;
        
        if (!e_MarkerData[id][E_MARKER_CALL])
            continue;

        if (areaid == getMarkerDynamicArea(id)) {
            CallRemoteFunction("OnPlayerLeaveMarker", "ii", playerid, id);
        }
    }
    #if defined NM_OnPlayerLeaveDynamicArea
        return NM_OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerLeaveDynamicArea
    #undef OnPlayerLeaveDynamicArea
#else
    #define _ALS_OnPlayerLeaveDynamicArea
#endif

#define OnPlayerLeaveDynamicArea NM_OnPlayerLeaveDynamicArea
#if defined NM_OnPlayerLeaveDynamicArea
    forward NM_OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid);
#endif
