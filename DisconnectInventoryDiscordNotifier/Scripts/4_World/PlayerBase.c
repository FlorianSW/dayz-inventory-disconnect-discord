/**
 * Notifies a discord channel when a player disconnects from the server while having one of the configured
 * items in their inventory. The inventory will be traversed, which also includes nested items (e.g. one of
 * the listed items in the a protection case within a bag will also trigger a notification when that item
 * in the case is listed in notifiedItems).
 *
 * Source: https://github.com/FlorianSW/dayz-inventory-disconnect-discord
 * License: MIT
 * Author: Florian Schmidt
 */
modded class PlayerBase {
	/**
	 * List of items that should trigger a notification when a player disconnects from the server with
	 * them in the inventory. If a player has multiple of the mentioned items in the inventory, only one
	 * notification will be triggered.
	 */
	private ref array<string> notifiedItems = {"Chemlight_Blue", "Chemlight_White"};
	/**
	 * The discord webhook URL where notifications should be posted to. Create one for the channel where
	 * the notifications should go to. For more information about discord webhooks, consult the discord
	 * documentation
	 */
	private string discordWebhookUrl = "https://discord.com/api/webhooks/.../...";

	void OnDisconnect() {
		super.OnDisconnect();

		auto item = notifiedItem(GetInventory());
		if (item != "") {
			notifyItemOnDisconnect(item);
		}
	}

	private string notifiedItem(GameInventory inventory) {
		array<EntityAI> itemsArray = new array<EntityAI>;
		inventory.EnumerateInventory(InventoryTraversalType.LEVELORDER, itemsArray);

		foreach(auto entity: itemsArray) {
			ItemBase item;
			Class.CastTo(item, entity);

			if (item && !item.IsInherited(SurvivorBase)) {
				if (isNotifiedItem(item.GetType())) {
					return item.GetType();
				} else if (item.GetInventory()) {
					auto notifyItem = notifiedItem(item.GetInventory());
					if (notifyItem != "") {
						return notifyItem;
					}
				}
			}
		}

		return "";
	}

	private bool isNotifiedItem(string typeName) {
		foreach(string item: notifiedItems) {
			if (item == typeName) {
				auto id = GetIdentity();
				GetGame().AdminLog(disallowedItemsOnDisconnectMessage(item));
				return true;
			}
		}
		return false;
	}

	private void notifyItemOnDisconnect(string item) {
		if (discordWebhookUrl == "") {
			return;
		}

		string sendData = "{\"text\": \"" + disallowedItemsOnDisconnectMessage(item) + "\"}";
		DIDNDiscordCB webHookCB = new DIDNDiscordCB();
		RestContext cURLCtx = GetRestApi().GetRestContext(discordWebhookUrl + "/slack");
		cURLCtx.SetHeader("application/json");
		cURLCtx.POST(webHookCB, "", sendData);
	}

	private string disallowedItemsOnDisconnectMessage(string item) {
		auto id = GetIdentity();
		return "Player " + id.GetName() + " (" + id.GetId() + ", " + id.GetPlainId() + ", position " + GetPosition() + ") has disallowed item (" + item + ") in their inventory on disconnect.";
	}
}

class DIDNDiscordCB: RestCallback {
	void DiscordCB() {};

	override void OnSuccess( string data, int dataSize ) {}

	override void OnError( int errorCode ) {
		Print("[DisconnectInventoryDiscordNotifier] Error sending webhook to Discord. Failed with error: " + errorCode);
	}

	override void OnTimeout() {}
};
