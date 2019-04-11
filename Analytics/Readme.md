# YouthTech Badge Wifi Analytics

Badge collects wifi information and distributes it to google sheet using [google-spreadsheet](https://www.npmjs.com/package/google-spreadsheet).

## Setup Service Account Authentication

1. Go to the [Google Developers Console](https://console.developers.google.com/cloud-resource-manager)
2. Select your project or create a new one (and then select it)
3. Enable the Drive API for your project

- In the sidebar on the left, expand APIs & auth > APIs
- Search for "drive"
- Click on "Drive API"
- click the blue "Enable API" button

4. Create a service account for your project

- In the sidebar on the left, expand APIs & auth > Credentials
- Click blue "Add credentials" button
- Select the "Service account" option
- Select "Furnish a new private key" checkbox
- Select the "JSON" key type option
- Click blue "Create" button
- your JSON key file is generated and downloaded to your machine (it is the only copy!)
- note your service account's email address (also available in the JSON key file)

5. Share the doc (or docs) with your service account using the email noted above

* For more information visit [google-spreadsheet](https://www.npmjs.com/package/google-spreadsheet) 

## Usage

```javascript
var GoogleSpreadsheet = require('google-spreadsheet');

//locate the json file you downloaded in step 4
var credential = require('./credential.json');                                              

// spreadsheet key is the long id in the sheets URL
var spreadsheet = new GoogleSpreadsheet('<spreadsheet key>');

// authenticate using service account authentication function
spreadsheet.useServiceAccountAuth(creds, function (err) {
	spreadsheet.getInfo(function (err, info) {
		console.log('Loaded doc: ' + info.title + ' by ' + info.author.email);
	});
});

```
