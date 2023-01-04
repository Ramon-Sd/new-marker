[![samp-include](https://img.shields.io/badge/SAMP_|-INCLUDE-5C2D91.svg?style=for-the-badge)](https://github.com/Ramon-Sd/new-marker)

<br><br>
<p align="left">
  <a href="https://www.sa-mp.com/">
    <img src="https://www.sa-mp.com/images/logo.gif" width="500" alt="SAMP Logo">
  </a>
</p>

<br><br>

# ―――――――――――――――――――――――――
<br>

[![installation](https://img.shields.io/badge/|-INSTALLATION_SAMPCTL_/_GIT-ffe600?style=for-the-badge&logo=none&logoColor=white)](https://github.com/Ramon-Sd/new-marker)
<br><br>

```bash
sampctl package install Ramon-Sd/new-marker
```

```bash
git clone https://github.com/Ramon-Sd/new-marker.git
```

# ―――――――――――――――――――――――――
<br>

[![functions](https://img.shields.io/badge/|-FUNCTIONS-0000FF?style=for-the-badge&logo=none&logoColor=white)](https://github.com/Ramon-Sd/new-marker)
<br><br>

```pawn

// * Natives

native CreateMarker(bool:call, Float:callradius, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 300.0, Float:drawdistance = 600.0);
native CreateStaticMarker(Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 300.0, Float:drawdistance = 600.0);
native CreateInvisibleMarker(Float:radius, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1);
native DestroyMarker(markerid);
native IsValidMarker(markerid);
native GetMarkerInterior(markerid);
native GetMarkerVirtualWorld(markerid);
native IsPlayerInMarker(playerid, markerid);

// * Callbacks

forward OnPlayerEnterMarker(playerid, markerid);
forward OnPlayerLeaveMarker(playerid, markerid);

```

# ―――――――――――――――――――――――――
<br>

[![screenshots](https://img.shields.io/badge/|-SCREENSHOTS-06d14d?style=for-the-badge&logo=none&logoColor=white)](https://github.com/Ramon-Sd/new-marker)
<br><br>

![sampctl](https://github.com/Ramon-Sd/new-marker/blob/main/imgs/img_01.png)
![sampctl](https://github.com/Ramon-Sd/new-marker/blob/main/imgs/img_02.png)
<br><br>
