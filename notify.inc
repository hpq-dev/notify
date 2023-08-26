
// Notification system 1.0
// Creator: HPQ123#8114

// * Settings * //
#define 	MAX_NOTIFY 		(10) // max show notofication
#define 	MAX_NT_STRING 	(320)
#define 	MAX_NT_TITLE 	(64)
#define 	SECONDS_NT 		(10)

enum ntInfo { ntIcon[32], ntTitle[MAX_NT_TITLE], ntMessage[MAX_NT_STRING], ntLines }
static notifyInfo[MAX_PLAYERS][MAX_NOTIFY][ntInfo], PlayerText:notifyPTD[MAX_PLAYERS][MAX_NOTIFY * 6], notifyIndex[MAX_PLAYERS];

#define notify::%0(%1) forward %0(%1); public %0(%1)
#define InternalNotification_show InternalNotification_Show
#define notification.	InternalNotification_

static const TDTextCaracterWidth[] = {
	0,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
	12,12,12,12,12,12,12,13,13,28,28,28,28,8,17,17,30,28,28,12,9,21,28,14,28,28,
	28,28,28,28,28,28,13,13,30,30,30,30,10,25,23,21,24,22,20,24,24,17,20,22,20,
	30,27,27,26,26,24,23,24,31,23,31,24,23,21,28,33,33,14,28,10,11,12,9,11,10,
	10,12,12,7,7,13,5,18,12,10,12,11,10,12,8,13,13,18,17,13,12,30,30,37,35,37,
	25,25,25,25,33,21,24,24,24,24,17,17,17,17,27,27,27,27,31,31,31,31,11,11,11,
	11,11,20,9,10,10,10,10,7,7,7,7,10,10,10,10,13,13,13,13,27,12,30
};


// Get width for char //
stock getSizeMessage(const string:message[], maxWidth=500) {
	new size = 0, lines=1, i=-1, lastPoint = 0;

	while(message[++i]) {
		size += TDTextCaracterWidth[message[i]];

		switch(message[i]) {
			case ' ': 
				lastPoint = i;

			default: 
				if(size >= maxWidth) 
					++lines, 
					size -= maxWidth, 
					size += i - lastPoint;
		}
	}
	return lines;
}

// main function for show notification //
stock InternalNotification_Show(const playerid, const string:title[], const string:message[], const string:icon[] = "hud:radar_triads") {
	for(new x=-1;++x<notifyIndex[playerid];) {
		for(new i=-1;++i<6;) PlayerTextDrawDestroy(playerid, notifyPTD[playerid][(x*6) + i]);
		notifyInfo[playerid][notifyIndex[playerid]-x] = notifyInfo[playerid][(notifyIndex[playerid]-x)-1];
	}

	strmid(notifyInfo[playerid][0][ntTitle], title, 0, MAX_NT_TITLE);
	strmid(notifyInfo[playerid][0][ntMessage], message, 0, MAX_NT_STRING);
	strmid(notifyInfo[playerid][0][ntIcon], icon, 0, 20);
	notifyInfo[playerid][0][ntLines] = getSizeMessage(message);

	++notifyIndex[playerid];

	new Float:static_x=0.0;
	for(new x=-1;++x<notifyIndex[playerid];) {
		createNotifyTD(playerid, x, x * 6, static_x);
		static_x+=(notifyInfo[playerid][x][ntLines] * 7.5) + 25.0;
	}

	SetTimerEx(#destroy_notify, SECONDS_NT * 1000, false, #i, playerid);
	return 1;
}

// when the notification stops //
notify::destroy_notify(playerid) {
	if(!notifyIndex[playerid]) return 1;
	--notifyIndex[playerid];
	for(new i=-1;++i<6;) PlayerTextDrawDestroy(playerid, notifyPTD[playerid][(notifyIndex[playerid]*6) + i]);
	return 1;
}

// display notification //
stock createNotifyTD(const playerid, index, i, const Float:static_x) {
	new lines = notifyInfo[playerid][index][ntLines],Float:x = (lines * 7.5) + static_x;

	notifyPTD[playerid][i] = CreatePlayerTextDraw(playerid, 29.42, 292.73 - x, "box");
	PlayerTextDrawLetterSize(playerid, notifyPTD[playerid][i], 0.0, 2.0 + (lines *0.9));
	PlayerTextDrawTextSize(playerid, notifyPTD[playerid][i], 132.0, 0.0);
	PlayerTextDrawAlignment(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, notifyPTD[playerid][i], -1);
	PlayerTextDrawUseBox(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawBoxColor(playerid, notifyPTD[playerid][i], 113);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, notifyPTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, notifyPTD[playerid][i], 1); 
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, notifyPTD[playerid][i]);

	notifyPTD[playerid][++i] = CreatePlayerTextDraw(playerid, 27.84, 298.5 - x, "particle:lamp_shad_64");
	PlayerTextDrawLetterSize(playerid, notifyPTD[playerid][i], 0.0, 0.0);
	PlayerTextDrawTextSize(playerid, notifyPTD[playerid][i], 109.0, 15.0 + (lines * 7.2));
	PlayerTextDrawAlignment(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, notifyPTD[playerid][i], -16777184);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, notifyPTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, notifyPTD[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, notifyPTD[playerid][i]);

	notifyPTD[playerid][++i] = CreatePlayerTextDraw(playerid, 29.34, 292.7 - x, "box");
	PlayerTextDrawLetterSize(playerid, notifyPTD[playerid][i], 0.0, 1.428);
	PlayerTextDrawTextSize(playerid, notifyPTD[playerid][i], 44.0, 0.0);
	PlayerTextDrawAlignment(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, notifyPTD[playerid][i], -1);
	PlayerTextDrawUseBox(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawBoxColor(playerid, notifyPTD[playerid][i], 113);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, notifyPTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, notifyPTD[playerid][i]);

	notifyPTD[playerid][++i] = CreatePlayerTextDraw(playerid, 29.69, 292.83 - x, notifyInfo[playerid][index][ntIcon]);
	PlayerTextDrawLetterSize(playerid, notifyPTD[playerid][i], 0.0, 0.0);
	PlayerTextDrawTextSize(playerid, notifyPTD[playerid][i], 13.0, 13.0);
	PlayerTextDrawAlignment(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, notifyPTD[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, notifyPTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, notifyPTD[playerid][i], 4);
	PlayerTextDrawSetProportional(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, notifyPTD[playerid][i]);

	notifyPTD[playerid][++i] = CreatePlayerTextDraw(playerid, 47.47, 291.44 - x, notifyInfo[playerid][index][ntTitle]);
	PlayerTextDrawLetterSize(playerid, notifyPTD[playerid][i], 0.134, 0.861);
	PlayerTextDrawAlignment(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, notifyPTD[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, notifyPTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, notifyPTD[playerid][i], 2);
	PlayerTextDrawSetProportional(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, notifyPTD[playerid][i]);

	notifyPTD[playerid][++i] = CreatePlayerTextDraw(playerid, 30.61, 308.96 - x, notifyInfo[playerid][index][ntMessage]);
	PlayerTextDrawLetterSize(playerid, notifyPTD[playerid][i], 0.145, 0.887);
	PlayerTextDrawTextSize(playerid, notifyPTD[playerid][i], 132.0, 0.0);
	PlayerTextDrawAlignment(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawColor(playerid, notifyPTD[playerid][i], -1);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawSetOutline(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawBackgroundColor(playerid, notifyPTD[playerid][i], 255);
	PlayerTextDrawFont(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawSetProportional(playerid, notifyPTD[playerid][i], 1);
	PlayerTextDrawSetShadow(playerid, notifyPTD[playerid][i], 0);
	PlayerTextDrawShow(playerid, notifyPTD[playerid][i]);
	return true;
}

public OnPlayerConnect(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		notifyIndex[playerid] = 0;
	}
	#if defined NT_OnPlayerConnect
		return NT_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect NT_OnPlayerConnect
#if defined NT_OnPlayerConnect
	forward NT_OnPlayerConnect(playerid);
#endif