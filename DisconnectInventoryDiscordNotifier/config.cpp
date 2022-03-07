class CfgPatches {
	class DisconnectInventoryDiscordNotifier {
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={
			"DZ_Data"
		};
	};
};

class CfgMods {
	class DisconnectInventoryDiscordNotifier {
		dir="DisconnectInventoryDiscordNotifier";
		name="DisconnectInventoryDiscordNotifier";
		author="Florian Schmidt";
		version="0.1";
		extra=0;
		type="mod";
		dependencies[]={"World"};
		class defs {
			class worldScriptModule {
				value="";
				files[]={"DisconnectInventoryDiscordNotifier/Scripts/4_World"};
			};
		};
	};
};