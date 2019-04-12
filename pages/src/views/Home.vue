<template>
  <div class="home">
    <!-- <HelloWorld msg="Welcome to Your Vue.js App"/> -->
    <div class="container">
      <!-- Main component for a primary marketing message or call to action -->
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
              connector charging and a CP2014 USB to serial interface. It also works with the Arduino IDE!</p>
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
            In the IDE, open the File Menu and choose Preferences and enter:
            <strong>http://arduino.esp8266.com/stable/package_esp8266com_index.json</strong> into the Additional Board Manager URLs field.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde1.image" @click="showImage(arduinoIde1.image,arduinoIde1.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">2.</span>
          <p class="instruction col-sm-8">
            Open the Boards Manager from Tools > Board:xxxxx menu
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde2.image" @click="showImage(arduinoIde2.image,arduinoIde2.title)">
        </div>

        <div class="instruction-wrapper row">
          <span class="instruction-number">3.</span>
          <p class="instruction col-sm-8">
            Find esp8266 by ESP8266 Community in the list and click Install. 
            The ESP8266 Hardware Libraries are now installed and you can test your new board with a simple Sketch.
          </p>
          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde3.image" @click="showImage(arduinoIde3.image,arduinoIde3.title)">
        </div>

      </div><!-- well -->

      <ImageModal v-bind:selectedImageUrl="selectedImageUrl" v-bind:title="selectedImageTitle" />

    </div> <!-- /container -->
  </div>
</template>

<script>
// @ is an alias to /src
import ImageModal from '@/components/ImageModal.vue'
import imageBadge from '../assets/badge-image.jpg'
import arduinoIde1 from '../assets/add-library-url.jpg'
import arduinoIde2 from '../assets/select-board-manager.jpg'
import arduinoIde3 from '../assets/library-download.jpg'
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
      arduinoIde1: {
        image: arduinoIde1,
        title: '1. Enter Additional Board Manager URL'
      },
      arduinoIde2: {
        image: arduinoIde2,
        title: '2. Open the Boards Manager from Tools > Board:xxxxx menu'
      },
      arduinoIde3: {
        image: arduinoIde3,
        title: '3. Find esp8266 by ESP8266 Community in the list and click Install'
      },
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
    p.instruction{
      padding-left: 26px;
      display: inline-block;
      //margin-top: -23px;
    }
  }
</style>