#include "marker.inc"

new marker[3];

public OnGameModeInit() {
	marker[0] = CreateMarker(3.0, 0.0, 0.0, 3.0);
	marker[1] = CreateStaticMarker(6.0, 6.0, 3.0);
	marker[2] = CreateInvisibleMarker(3.0, 9.0, 9.0, 3.0);
	return 1;
}

public OnGameModeExit() {
	DestroyMarker(marker[0]);
	DestroyMarker(marker[1]);
	DestroyMarker(marker[1]);
	return 1;
}

main()  {
	print ("[New Marker -> Test]: Script Started!");
}
