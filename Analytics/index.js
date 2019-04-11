var GoogleSpreadsheet = require('google-spreadsheet');
var creds = require('./YouthTechEvent-0c0f1d08ebdf.json');
var spreadsheet = new GoogleSpreadsheet('1qApQf9zQtNiXilDDyReZZael4i7CN6JCPHbUjxbQz-w');

var mqtt = require('mqtt');
var count = 0;
var client = mqtt.connect("mqtt://iot.miceline.com:1883", { clientId: "37aec926-991d-43f9-b952-97516690c712" });
console.log("connected flag  " + client.connected);
var messagesTimes = {};

spreadsheet.useServiceAccountAuth(creds, function (err) {
	spreadsheet.getInfo(function (err, info) {
		console.log('Loaded doc: ' + info.title + ' by ' + info.author.email);
		sheet = info.worksheets[0];
		console.log('sheet 1: ' + sheet.title + ' ' + sheet.rowCount + 'x' + sheet.colCount);
	});
});

//handle incoming messages
client.on('message', function (topic, message, packet) {
	try {
		message = JSON.parse(message);
		let badgeId = topic.substring(7, 15);

		sendInitialMessage(badgeId, message);

		if (messagesTimes[badgeId].message2 !== null && message.msg_type == '2') {
			if ((Date.now() - messagesTimes[badgeId].message2) > 60000) {
				sendMessage(badgeId, message);
				messagesTimes[badgeId].message2 = Date.now();
			}
		}
	}
	catch (error) {
		console.log('error', error);
		console.log('message', message);
	}
});


client.on("connect", function () {
	console.log("connected  " + client.connected);

})
//handle errors
client.on("error", function (error) {
	console.log("Can't connect" + error);
	process.exit(1)
});
//publish
function publish(topic, msg, options) {
	console.log("publishing", msg);

	if (client.connected == true) {

		client.publish(topic, msg, options);

	}
	count += 1;
	if (count == 2) //ens script
		clearTimeout(timer_id); //stop timer
	client.end();
}

function defineProperty(obj, key, value) {
	if (key in obj) {
		Object.defineProperty(obj, key, { value: value, enumerable: true, configurable: true, writable: true });
	} else {
		obj[key] = value;
	}
	return obj;
}

function sendInitialMessage(badgeId, message) {
	if (messagesTimes.hasOwnProperty(badgeId)) {
		if (messagesTimes[badgeId].message2 === null && message.msg_type == '2') {
			messagesTimes[badgeId].message2 = Date.now();
			sendMessage(badgeId, message);
		}
	} else {
		let time2 = null;
		if (message.msg_type == '2') {
			time2 = Date.now();
		}
		sendMessage(badgeId, message);
		defineProperty(messagesTimes, badgeId, {
			message2: time2
		});
	}
}

function sendMessage(badgeId, message) {
	let time = new Date().toLocaleTimeString('en-US');
	if (message.msg_type == '2') {
		spreadsheet.addRow(3, {
			badge_id: badgeId,
			wifi_station_mac: message.wifi_station_mac,
			wifi_rssi: message.wifi_rssi,
			time: time
		}, function (err) {
			if (err) {
				console.log(err);
			}
		});
	}
}

//////////////

var options = {
	retain: true,
	qos: 1
};
var topic = "/badge/#";
var message = "test message";
var topic_list = ["topic2", "topic3", "topic4"];
var topic_o = { "topic22": 0, "topic33": 1, "topic44": 1 };
console.log("subscribing to topics");
//client.subscribe(topic,{qos:1}); //single topic
//client.subscribe(topic_list,{qos:1}); //topic list
client.subscribe(topic); //object
//var timer_id=setInterval(function(){publish(topic,message,options);},5000);
//notice this is printed even before we connect
console.log("end of script");