# DisconnectInventoryDiscordNotifier

Simple DayZ server-side only addon to notify a discord channel of your choice when a player disconnects from the server while having an item in their inventory which is listed to be notified upon.

## Installation

You need to open the file `.\DisconnectInventoryDiscordNotifier\Scripts\4_World\PLayerBase.c` and change the variables at the top of the `PlayerBase` class to whatever you want.
Afterwards, compile the addon with your favourite mod builder (e.g. the official Addon Builder from DayZ Tools).

Move the built pbo into a directory with your server mods (e.g. `.\ServerMods\Addons\`) and add the `.\ServerMods` to your `"-servermod="` option, if not done already.
Restart the server and you're done.
