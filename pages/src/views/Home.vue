<template>
  <div class="home">

    <div class="container">

      <div class="well">
        <div class="row">
          <div class="col-sm-12 title-wrapper">
            <h2 class="title">ESP8266 Built-in OLED – Heltec WiFi Kit 8</h2>
            <p class="small">May 4, 2019</p>
          </div>
          <div class="text-left col-sm-8">
            <h4>A  set-up guide for the Heltec WiFi Kit 8 development board (an ESP8266 with built-in OLED display).</h4>
            <p>Follow the easy steps below to get up and running with this board using standard Arduino libraries.</p>

            <p>This board is based on the ESP8266 chip and has onboard WiFi,  a 0.96inch 128*32 OLED display, lithium battery 
              connector charging and a CP2014 USB to serial interface.</p>
          </div>

          <img class="col-sm-4 modal-image" v-bind:src="imageBadge.image" @click="showImage(imageBadge.image, imageBadge.title)">

        </div>
      </div>

      <div class="well">
        <h3>Setting Up the Arduino IDE for the ESP8266 Range</h3>
        <div class="row">
          <div class="text-left col-sm-12">
            <p>
              The ESP8266 boards are much easier to set up in the Arduino IDE than the ESP32 range. If you don’t already have 
              it installed, download and install the IDE from here: 
              <a target="_blank" href="https://www.arduino.cc/en/main/software">https://www.arduino.cc/en/main/software</a> (don’t use the Web version).
            </p>
          </div>
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">1.</span>
          <p class="instruction col-sm-8">
              In order to connect your machine to the driver you will need to install the appropriate driver for your system.
              Use the the link below and download the appropriate driver for your system.<br>
            <a target="_blank" href="https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers">Download page USB driver</a>
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="driverImage.image" @click="showImage(driverImage.image,driverImage.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">2.</span>
          <p class="instruction col-sm-8">
            In the IDE, open the File Menu and choose Preferences and enter:
            <strong>http://arduino.esp8266.com/stable/package_esp8266com_index.json</strong> into the Additional Board Manager URLs field.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde1.image" @click="showImage(arduinoIde1.image,arduinoIde1.title)">
        </div>


        <div class="instruction-wrapper row">
          <span class="instruction-number">3.</span>
          <p class="instruction col-sm-8">
            Go to Tools > Port and make sure COM4 is selected (It might not be COM4) <br> <br>
            If you experience any difficulty with your USB connection install the following driver: <br>
            <a target="_blank" href="https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers">USB driver</a>
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde2.image" @click="showImage(arduinoIde2.image,arduinoIde2.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">4.</span>
          <p class="instruction col-sm-8">
            Open the Boards Manager from Tools > Board:xxxxx menu
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde3.image" @click="showImage(arduinoIde3.image,arduinoIde3.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">5.</span>
          <p class="instruction col-sm-8">
            Search and install the following libraries:
            <ul>
              <li>esp8266 by ESP8266 Community</li>
              <li>PubSubClient by Nick O'Leary</li>
              <li>ArduinoJson by Benoit Blanchon (version 6.9.0 or higher)</li>
              <li>U8g2 by oliver</li>
              <li>TaskScheduler by Anatoli Arkhipenko</li>
            </ul>

            
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde4.image" @click="showImage(arduinoIde4.image,arduinoIde4.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">6.</span>
          <div class="col-sm-8 instruction">
            <p>
              In the Arduino IDE, in the Tools > Board menu choose NodeMCU 1.0 (ESP-12E Module).
            </p>
            <p>The ESP8266 Hardware Libraries are now configured and is ready for use.</p>
          </div>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde5.image" @click="showImage(arduinoIde5.image,arduinoIde5.title)">
        </div>

      </div><!-- well -->

      <div class="well">
        <h3>Connect to your own WIFI to communicate with Badge APP</h3>
        <div class="row">
          <div class="text-left col-sm-12">
            <p>
              This section section describes how to connect to your own WIFI at home so you can communicate with the YouthTechEvent App.
              In order to connect with the App you will first need to upload the badge firmware to the badge.
            </p>

            <p>
              There are two ways to upload the badge firmware to your app. 
              The first way is to clone the GitHub repository and open this in the Arduino IDE. (<a target="_blank" href="https://help.github.com/en/articles/cloning-a-repository">Info on cloning a repository</a>).
              The other ( and simpler ) way is to copy the code manually and save it in the Arduino IDE. For simplicity's sake well follow the second option.
            </p>
          </div>
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">1.</span>
          <p class="instruction col-sm-8">
            Go to the badge's GitHub repository. <a target="_blank" href="https://github.com/setar-nv/youthtechevent">Link to repository.</a> <br>
            Click on BadgeFirmware > BadgeFirmware.ino to view to firmware code.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde6.image" @click="showImage(arduinoIde6.image,arduinoIde6.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">2.</span>
          <p class="instruction col-sm-8">
            Select and copy all the code in BadgeFirmware.ino and copy this in a new file in the Arduino IDE.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde7.image" @click="showImage(arduinoIde7.image,arduinoIde7.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">3.</span>
          <p class="instruction col-sm-8">
            Edit the WIFI ssid (WIFI name) and password to match your WIFI settings at home. Edit the badgeName variable (optional) to view this text on your badge display.
            Save after editing.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde9.image" @click="showImage(arduinoIde9.image,arduinoIde9.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">4.</span>
          <p class="instruction col-sm-8">
            Go to Tools > Serial Monitor to open the Serial Monitor. Make sure the baud rate is set to 115200.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde10.image" @click="showImage(arduinoIde10.image,arduinoIde10.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">5.</span>
          <p class="instruction col-sm-8">
            Make sure your badge is connected to your machine first. Click on the upload button to upload the Badge firmware.
            If successfully connected you should be able to see your WIFI name on the top right corner of your badge display.
            After the upload process is done you will be able to find the Badge's unique id in the Serial Monitor.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde11.image" @click="showImage(arduinoIde11.image,arduinoIde11.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">6.</span>
          <p class="instruction col-sm-8">
            Open the App. In the main menu tap on badge. Fill in the unique ID in the MAC address field. Fill it in exactly the same as in the Serial Monitor, including colons and case sensitive.
          Fill in a desired name to show on the badge display.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde12.image" @click="showImage(arduinoIde12.image,arduinoIde12.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">6.</span>
          <p class="instruction col-sm-8">
            If everything went according to plan you should now be now able to communicate with the badge. You will now be able to control the LED lights individually or by running the demos. 
            You can also check the battery and change the display name on the badge display. Have Fun!
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde13.image" @click="showImage(arduinoIde13.image,arduinoIde13.title)">
        </div>

 

      </div><!-- well -->


    </div> <!-- /container -->
    <div class="well setar-code">
      <img v-bind:src="setarCode" alt="" srcset="">
    </div>
    <ImageModal v-bind:selectedImageUrl="selectedImageUrl" v-bind:title="selectedImageTitle" />
  </div>
</template>

<script>
// @ is an alias to /src
import ImageModal from '@/components/ImageModal.vue'
import imageBadge from '../assets/badge-image.jpg'
import driverImage from '../assets/driver-page.jpg'
import arduinoIde1 from '../assets/add-library-url.jpg'
import arduinoIde2 from '../assets/select-port.jpg'
import arduinoIde3 from '../assets/select-board-manager.jpg'
import arduinoIde4 from '../assets/library-download.jpg'
import arduinoIde5 from '../assets/select-nodemcu.jpg'
import arduinoIde6 from '../assets/github-page-01.png'
import arduinoIde7 from '../assets/github-page-02.png'
import arduinoIde9 from '../assets/edit-wifi.png'
import arduinoIde10 from '../assets/serial-monitor.png'
import arduinoIde11 from '../assets/upload.png'
import arduinoIde12 from '../assets/app-settings.png'
import arduinoIde13 from '../assets/app-connected.png'
import setarCode from '../assets/setar-code.png'
import JQuery from 'jquery'
let $ = JQuery

export default {
  name: 'home',
  data: function () {
    return {
      imageBadge: {
        image: imageBadge,
        title: 'Setar YTE 2019 badge'
      },
      driverImage: {
        image: driverImage,
        title: '1. Download and install appropriate driver'
      },
      arduinoIde1: {
        image: arduinoIde1,
        title: '2. Enter Additional Board Manager URL'
      },
      arduinoIde2: {
        image: arduinoIde2,
        title: '3. Go to Tools > Port and make sure COM4 is selected (It might not be COM4)'
      },
      arduinoIde3: {
        image: arduinoIde3,
        title: '4. Open the Boards Manager from Tools > Board:xxxxx menu'
      },
      arduinoIde4: {
        image: arduinoIde4,
        title: '5. Search and install the required libraries'
      },
      arduinoIde5: {
        image: arduinoIde5,
        title: '6. In the Arduino IDE, in the Tools > Board menu choose NodeMCU 1.0 (ESP-12E Module)'
      },
      arduinoIde6: {
        image: arduinoIde6,
        title: '1. Click on BadgeFirmware > BadgeFirmware.ino to view to firmware code'
      },
      arduinoIde7: {
        image: arduinoIde7,
        title: '2. Select and copy all the code in BadgeFirmware.ino'
      },
      arduinoIde9: {
        image: arduinoIde9,
        title: '3. Edit Badge Name and WIFI settings'
      },
      arduinoIde10: {
        image: arduinoIde10,
        title: '4. Go to Tools > Serial Monitor to open the Serial Monitor'
      },
      arduinoIde11: {
        image: arduinoIde11,
        title: '5. Edit Badge Name and WIFI settings'
      },
      arduinoIde12: {
        image: arduinoIde12,
        title: '6. Edit Badge Name and WIFI settings'
      },
      arduinoIde13: {
        image: arduinoIde13,
        title: '7. Comtrol the badge through the App'
      },
      setarCode,
      selectedImageUrl: null,
      selectedImageTitle: null
    }
  },
  components: {
    ImageModal
  },
  created: function(){


  },
  mounted: function(){

  },
  methods: {
    showImage(imageUrl,title){
      this.selectedImageUrl = imageUrl;
      this.selectedImageTitle = title;
      if(imageUrl)
        $('#ImageModal').modal();
    }

  },
}
</script>


<style scoped lang="scss">
  .well{
    margin-bottom: 40px;
    word-break: break-word;
  }
  .title-wrapper{    
    text-align: center;
    margin-bottom: 20px;
    h2.title,{
    }
  }
  .instruction-wrapper{
    margin-top: 30px;
    text-align: left;
    margin-left: 5px;
    border-bottom: 1px solid rgb(207, 207, 207);
    padding-bottom: 30px;
    .instruction-number{
      font-weight:700;
      font-size: 16px;
      position: absolute;
    }
    .instruction{
      padding-left: 26px;
      display: inline-block;
      //margin-top: -23px;
    }
  }
  .setar-code{
    margin-top: 40px;
    margin-bottom: 0;
    padding: 60px 0;
    background: #18bc9c;
    img{
      display: block;
      margin: 0 auto;
    }
  }
</style>